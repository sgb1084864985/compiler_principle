import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;

// DFA.java

public interface DFA{
    void addState();
    int size();
    void putEdge(int src,element e,int dst);
    void removeEdge(int src,element e);
    Integer getEdge(int src,element e);
    void putFinal(int state,tokenInfo info);
    void removeFinal(int state);
    void clearFinal();
    void setStart(int state);
    DFA getMinimizedDFA();
    String toGraph();
}

class DFA_Impl implements DFA{
    ArrayList<state> table=new ArrayList<>();
    int start;
    LinkedList<Integer> finite = new LinkedList<>();
    HashSet<element> allInputs=new HashSet<>();

    @Override
    public DFA getMinimizedDFA() {
        for(state st:table){
            allInputs.addAll(st.rule.keySet());
        }
        LinkedList<stateSet> work=new LinkedList<>();
        LinkedList<stateSet> back=new LinkedList<>();
        ArrayList<stateInfo> sInfos=new ArrayList<>();
        HashMap<tokenInfo,stateSet> finals=new HashMap<>();

        for(counter i=new counter();i.curInteger()<size();i.Inc()){
            Integer I=i.curInteger();
            tokenInfo tI=table.get(I).getInfo();
            stateInfo si=new stateInfo();
            sInfos.add(si);
            finals.compute(tI,(k,v)->{
                if(v==null){
                    v=new stateSet();
                    v.addInfo(tI);
                }
                v.set.add(I);
                si.owner=v;
                return v;
            });
        }
        
        for(stateSet S:finals.values()){
            work.addLast(S);
        }

        boolean splitable=false;

        do{
            splitable=false;
            while(!work.isEmpty()){
                stateSet S=work.getFirst();
                work.removeFirst();
                splitable|=spilitSet(S, back,sInfos);
            }
            LinkedList<stateSet> t=work;
            work=back;
            back=t;
        }
        while(splitable);

        int i=0;
        Iterator<stateSet> it=work.iterator();
        HashMap<stateSet,Integer> code=new HashMap<>();
        DFA_Impl dfa=new DFA_Impl();
        while(it.hasNext()){
            stateSet S=it.next();
            code.put(S, i);
            dfa.addState();
            dfa.table.get(i).addInfo(S.getInfo());
            i++;
        }
        it=work.iterator();
        while(it.hasNext()){
            stateSet S=it.next();
            int delegation=S.set.peek();
            table.get(delegation).rule.forEach((k,v)->{
                dfa.putEdge(code.get(S), k, code.get(sInfos.get(v).owner));
            });
        }
        dfa.setStart(code.get(sInfos.get(start).owner));
        return dfa;
    }

    boolean spilitSet(stateSet s,LinkedList<stateSet> back,ArrayList<stateInfo> sInfos){
        if(s.set.size()<=1) {
            back.addLast(s);
            return false;
        }
        boolean distinct=false;
        for(element input:allInputs){
            HashMap<stateSet,LinkedList<Integer>> map=new HashMap<>();
            for(int item:s.set){
                Integer var=table.get(item).getEdge(input);
                stateSet dstSet=null;
                if(var!=null){
                    dstSet=sInfos.get(var).owner;
                }
                map.compute(dstSet, (k,v)->{
                    if(v==null){
                        v=new LinkedList<>();
                    }
                    v.add(item);
                    return v;
                });
            }
            if(map.size()>1){
                distinct=true;
                for(LinkedList<Integer> list:map.values()){
                    stateSet S=new stateSet();
                    S.set=list;
                    S.addInfo(s.getInfo());
                    back.addLast(S);
                    for(int index:list){
                        sInfos.get(index).owner=S;
                    }
                }
            }
            map=null;
            if(distinct){
                break;
            }
        }
        if(!distinct){
            back.addLast(s);
        }
        return distinct;
    }

    static class stateInfo{
        stateSet owner;
    }

    static class stateSet extends abstractState{
        LinkedList<Integer> set=new LinkedList<>();
    }
    boolean isFinite(int st){
        return table.get(st).isFinite();
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
                out.append("    %d -> %d [label=\"".formatted(i.curInteger()+1,var+1));
                out.append(key+"\"]\n");
            });
        }
        out.append("}\n");
        return out.toString();
    }

    @Override
    public void addState() {
        table.add(new state());
    }
    @Override
    public int size() {
        return table.size();
    }
    @Override
    public void putEdge(int src, element e, int dst) {
        table.get(src).addEdge(e, dst);        
    }
    @Override
    public Integer getEdge(int src, element e) {
        return table.get(src).getEdge(e);
    }
    @Override
    public void removeEdge(int src, element e) {
        table.get(src).removeEdge(e);
    }
    @Override
    public void setStart(int st) {
        start=st;
    }
    @Override
    public void putFinal(int st,tokenInfo info) {
        finite.add(st);
        table.get(st).addInfo(info);
    }
    @Override
    public void removeFinal(int st) {
        finite.remove(st);
    }
    @Override
    public void clearFinal() {
        finite.clear();
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
        out.append("Class DFA:\n");
        out.append("start from "+start+getFiniteStateString(start)+"\n");
        counter i=new counter();
        for(;i.curInteger()<table.size();i.Inc()){
            table.get(i.curInteger()).rule.forEach((key,var)->{
                out.append(i.curInteger()+"-"+key+"->"+var+getFiniteStateString(var)+"\n");
            });
        }

        return out.toString();
    }

    static class state extends abstractState{
        HashMap<element,Integer> rule=new HashMap<>();
        void addEdge(element e,Integer s){
            rule.put(e, s);
        }
        Integer getEdge(element e){
            return rule.get(e);
        }
        void removeEdge(element e){
            rule.remove(e);
        }
    }
}