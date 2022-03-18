import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;

// NFA.java

public interface NFA{
    // would change itself
    NFA cat(NFA other);
    NFA star();
    NFA union(NFA other);
    NFA getSingleElement(element l);
    NFA getEmptyNFA();
    element getSingElement(); // return null if not a single element
    NFA plus();
    DFA toDFA();
    void setInfo(tokenInfo info);
    Object clone() throws CloneNotSupportedException;
    String toGraph();
}

class NFA_impl implements NFA{
    state start;
    LinkedList<state> finite = new LinkedList<>();

    NFA_impl(element e){
        if(e==null){
            state s=new state();
            start=s;
            finite.add(s);
        }
        else{
            state s=new state();
            state f=new state();
            s.addEdge(e,f);
            start=s;
            finite.add(f);
        }

    }
    NFA_impl(){
        this(null);
    }

    @Override
    public NFA getEmptyNFA() {
        return new NFA_impl();
    }

    @Override
    public element getSingElement(){
        if(start.rule.size()!=1 || finite.size()!=1 || !finite.get(0).rule.isEmpty()){
            return null;
        }
        for(element key:start.rule.keySet()){
            ArrayList<state> list=start.rule.get(key);
            if(list.size()!=1){
                return null;
            }
            if(list.get(0)!=finite.get(0)){
                return null;
            }
            return key;
        }
        return null;
    }

    @Override
    public void setInfo(tokenInfo info) {
        for(state st:finite){
            st.addInfo(info);
        }
    }

    @Override
    public String toString() {
        return tOrd().toString();
    }
    public String toGraph(){
        return tOrd().toGraph();
    }


    NFA_ord tOrd(){
        HashMap<state,Integer> table=new HashMap<>();
        LinkedList<state> queue=new LinkedList<>();
        NFA_ord ret=new NFA_ord();

        ret.addState();
        ret.setStart(0);
        queue.addLast(start);
        table.put(start, 0);
        counter i=new counter();

        while(!queue.isEmpty()){
            state p=queue.getFirst();
            queue.removeFirst();
            int num=table.get(p);
            if(p.isFinite()){
                ret.addFinite(num,p.getInfo());
            }
            
            p.rule.forEach((key,list)->{
                for(state item:list){
                    if(!table.containsKey(item)){
                        ret.addState();
                        table.put(item, i.Inc());
                        queue.addLast(item);
                    }
                    ret.putEdge(num, key, table.get(item));
                }
            });
        }
        return ret;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        NFA_impl ret=new NFA_impl();
        ret.start=(state)start.clone();
        return ret;
    }

    @Override
    public NFA cat(NFA other) {
        state mid=new state();
        NFA_impl o=(NFA_impl)other;
        for(state s:finite){
            s.addNoInputEdge(mid);
        }
        mid.addNoInputEdge(o.start);
        finite=o.finite;
        return this;
    }

    @Override
    public NFA star() {
        plus();
        finite.add(start);
        return this;
    }

    @Override
    public NFA plus() {
        state new_start=new state();
        for(state s:finite){
            s.addNoInputEdge(new_start);
        }
        new_start.addNoInputEdge(start);
        start=new_start;
        return this;
    }

    @Override
    public NFA union(NFA other) {
        NFA_impl o=(NFA_impl)other;
        state new_start=new state();
        new_start.addNoInputEdge(start);
        new_start.addNoInputEdge(o.start);
        finite.addAll(o.finite);
        start=new_start;
        return this;
    }

    @Override
    public NFA getSingleElement(element l) {
        return new NFA_impl(l);
    }

    static class state extends abstractState{
        HashMap<element,ArrayList<state>> rule=new HashMap<>();
        void addEdge(element e,state s){
            ArrayList<state> list=rule.get(e);
            if(list==null){
                list=new ArrayList<>();
                rule.put(e, list);
            }
            list.add(s);
        }
        void addNoInputEdge(state s){
            addEdge(null, s);
        }
        @Override
        public Object clone() throws CloneNotSupportedException {
            // TODO Auto-generated method stub
            return super.clone();
        }
    }

    @Override
    public DFA toDFA() {
        return tOrd().toDFA();
    }

}

class EqualitySet extends abstractState implements Iterable<Integer>{
    BigInteger id;
    HashSet<Integer> set=new HashSet<>();
    void add(Integer e){set.add(e);}
    BigInteger getID(){
        return id;
    }
    @Override
    public Iterator<Integer> iterator() {
        return set.iterator();
    }
    boolean contains(Integer e){return set.contains(e);}
    void calculate(){
        id=BigInteger.ZERO;
        BigInteger one=BigInteger.ONE;
        for(Integer i:set){
            id=id.or(one.shiftLeft(i));
        }
    }
    @Override
    public boolean equals(Object obj) {
        EqualitySet another=(EqualitySet)obj;
        return id.equals(another.id);
    }
}

class NFA_ord{
    ArrayList<state> table=new ArrayList<>();
    int start;
    LinkedList<Integer> finite = new LinkedList<>();

    DFA toDFA(){
        HashMap<BigInteger,Integer> IDs=new HashMap<>();
        LinkedList<tempRecord> queue=new LinkedList<>();
        LinkedList<Integer> init=new LinkedList<>();
        DFA_factory fac=new DFA_factory();
        DFA dfa=fac.getDFA();
        dfa.setStart(0);

        counter i=new counter();
        init.add(start);
        queue.addLast(new tempRecord(0, null, init));

        while(!queue.isEmpty()){
            tempRecord p=queue.getFirst();
            queue.removeFirst();
            EqualitySet eSet=getESet(p.dst);
            BigInteger id=eSet.getID();
            Integer state_id=IDs.get(id);
            
            if(state_id==null){
                state_id=i.curInteger();
                i.Inc();
                dfa.addState();

                if(eSet.isFinite()){
                    dfa.putFinal(state_id,eSet.getInfo());
                }

                IDs.put(id, state_id);
                addToQueue(state_id, eSet, queue);
            }

            if(p.edge!=null){
                dfa.putEdge(p.src, p.edge, state_id);
            }
        }

        return dfa;
    }

    void addToQueue(int id, EqualitySet set,LinkedList<tempRecord> queue){
        state eState=new state();
        for(int item:set){
            table.get(item).rule.forEach((key,value)->{
                eState.addEdges(key, value);
            });
        }
        eState.rule.forEach((key,value)->{
            if(key!=null)
                queue.addLast(new tempRecord(id, key, value));
        });
    }

    EqualitySet getESet(LinkedList<Integer> queue){
        EqualitySet set=new EqualitySet();
        LinkedList<Integer> empty=new LinkedList<>();
        while(!queue.isEmpty()){
            Integer head=queue.getFirst();
            queue.removeFirst();
            set.add(head);
            if(isFinite(head)){
                set.addInfo(table.get(head).getInfo());
            }
            for(Integer neigh:table.get(head).rule.getOrDefault(null,empty)){
                if(!set.contains(neigh)){
                    queue.addLast(neigh);
                }
            }
        }
        empty=null;
        set.calculate();
        return set;
    }
    boolean isFinite(int st){
        return table.get(st).isFinite();
    }

    String getFiniteStateString(int st){
        state s=table.get(st);
        tokenInfo info=s.getInfo();
        if(info==null)return "";
        return " is final state:"+info.toString();
    }

    @Override
    public String toString() {
        StringBuilder out=new StringBuilder();
        out.append("Class NFA:\n");
        counter i=new counter();

        out.append("start from "+start+getFiniteStateString(start)+"\n");

        for(;i.curInteger()<table.size();i.Inc()){
            table.get(i.curInteger()).rule.forEach((key,var)->{
                out.append(i.curInteger()+"-"+key+"->{");
                for(Integer dst:var){
                    out.append(" "+dst+getFiniteStateString(dst));
                }
                out.append(" }\n");
            });
        }

        return out.toString();
    }

    public String toGraph(){
    //     digraph {
    //         0 [label="" shape=none]
    //         1 [label=1 shape=circle]
    //         2 [label=2 shape=doublecircle]
    //         3 [label=3 shape=circle]
    //         4 [label=4 shape=doublecircle]
    //         0 -> 1
    //         1 -> 2 [label="ε"]
    //         1 -> 3 [label="[13579]"]
    //         1 -> 4 [label="[2468]"]
    //         3 -> 3 [label="[13579]"]
    //         3 -> 4 [label="[02468]"]
    //         4 -> 3 [label="[13579]"]
    //         4 -> 4 [label="[02468]"]
    //      }
    
        StringBuilder out=new StringBuilder();
        String circle="circle";
        String dcircle="doublecircle";
        out.append("digraph {\n");
        out.append("    0 [label=\"\" shape=none]\n");

        for(int st=0;st<size();st++){
            out.append("    %d [label=%d shape=%s]\n".formatted(st+1,st+1,isFinite(st)?dcircle:circle));
        }

        counter i=new counter();
        out.append("    0 -> %d\n".formatted(start+1));
        for(;i.curInteger()<table.size();i.Inc()){
            table.get(i.curInteger()).rule.forEach((key,var)->{
                for(Integer dst:var){
                    out.append("    %d -> %d [label=\"".formatted(i.curInteger()+1,dst+1));
                    out.append(((key==null)?"ε":key.toString())+"\"]\n");
                }
            });
        }
        out.append("}\n");
        return out.toString();
    }

    int size(){return table.size();}

    void putEdge(int src,element e,int dst){
        table.get(src).addEdge(e, dst);
    }
    void addState(){
        table.add(new state());
    }
    void setStart(int st){
        start=st;
    }
    void addFinite(int st,tokenInfo info){
        finite.add(st);
        table.get(st).addInfo(info);
    }

    static class tempRecord{
        int src;
        element edge;
        LinkedList<Integer> dst=new LinkedList<>();
        tempRecord(int src,element edge,LinkedList<Integer> dst){
            this.src=src;
            this.edge=edge;
            this.dst=dst;
        }
    }

    static class state extends abstractState{
        HashMap<element,LinkedList<Integer>> rule=new HashMap<>();
        void addEdge(element e,Integer s){
            LinkedList<Integer> list=rule.get(e);
            if(list==null){
                list=new LinkedList<>();
                rule.put(e, list);
            }
            list.add(s);
        }
        
        void addEdges(element e,LinkedList<Integer> edges){
            LinkedList<Integer> list=rule.get(e);
            if(list==null){
                list=new LinkedList<>();
                rule.put(e, list);
            }
            list.addAll(edges);      
        }
        void addNoInputEdge(Integer s){
            addEdge(null, s);
        }
    }
}

class counter{
    Integer cnt;
    counter(Integer i){
        cnt=i;
    }
    counter(){
        this(0);
    }
    Integer Inc(){
        cnt++;
        return cnt;
    }
    Integer Dec(){
        cnt--;
        return cnt;
    }
    Integer curInteger(){return cnt;}
}