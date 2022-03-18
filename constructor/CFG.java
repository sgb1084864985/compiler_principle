// CFG.java

import java.math.BigInteger;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.function.BiConsumer;
import java.util.function.Function;

public class CFG{
    int terminals;
    int start;
    static final int EOF=-1;
    ArrayList<NonTerminalInfo> nTermInfos=new ArrayList<>();

    public CFG(int terminals){
        this.terminals=terminals;
    }

    public void addNonterminal(NonTerminal nt){
        nTermInfos.add(new NonTerminalInfo(nt));
    }
    public void setStart(int start){
        this.start=start;
    }

    // int getNonTerminalIndex(int t){
    //     return t-terminals;
    // }

    // int getNonTerminalByIndex(int i){
    //     return i+terminals;
    // }
    public void addInitSymbol(){
        NonTerminal nt=new NonTerminal();
        NonTerminalInfo info=new NonTerminalInfo(nt);
        nTermInfos.add(info);
        production p=new production(getInitSymbol());
        nt.addProduction(p);
        p.add(start+terminals);
        info.followSet.add(EOF);
    }

    public NonTerminalInfo getInitSymbolInfo(){
        return nTermInfos.get(nTermInfos.size()-1);
    }
    public int getInitSymbol(){
        return nTermInfos.size()-1+terminals;
    }

    int getNonTerminalNum(){
        return nTermInfos.size();
    }

    NonTerminal getNTermByIndex(int i){
        return nTermInfos.get(i).nt;
    }
    NonTerminal getNTerm(int i){
        return nTermInfos.get(i-terminals).nt;
    }
    FirstSet gFirstSet(int i){
        return nTermInfos.get(i-terminals).firstSet;
    }
    void sFirstSet(int i,FirstSet fs){
        nTermInfos.get(i-terminals).firstSet=fs;
    }
    FirstSet gFirstSetByIndex(int i){
        return nTermInfos.get(i).firstSet;
    }
    FollowSet gFollowSet(int i){
        return nTermInfos.get(i-terminals).followSet;
    }

    int getInitState(){return 0;}

    class DFS implements Function<Integer,Integer>{
        int current;
        boolean []accessed;
        boolean []shared;
        int minSharedSymbol=nTermInfos.size()+terminals;
        LinkedList<Integer> sharedSymbols=new LinkedList<>();
        Function<Integer,FirstSet> accessMethod;

        DFS(int I,Function<Integer,FirstSet> aFunction){
            current=I;
            accessed=new boolean[I+1];
            shared=new boolean[I+1];
            accessMethod=aFunction;
        }

        @Override
        public Integer apply(Integer arg0) {
            int retval=0;
            FirstSet fSet=accessMethod.apply(arg0);
            FirstSet back=new FirstSet();
            Iterator<Integer> it=fSet.iterator();
            accessed[arg0]=true;
            while(it.hasNext()){
                Integer depend=it.next();
                if(depend>=terminals && depend<current){
                    if(!accessed[depend-terminals]){
                        apply(depend);
                    }
                    if(shared[depend-terminals]){
                        shared[arg0-terminals]=true;
                    }
                    back.unite(accessMethod.apply(depend));
                    it.remove();
                }
                else if(depend==current){
                    shared[arg0-terminals]=true;
                    it.remove();
                }
            }
            fSet.unite(back);
            if(shared[arg0-terminals]){
                if(arg0<minSharedSymbol){
                    arg0=minSharedSymbol;
                }
                sharedSymbols.add(arg0);
            }
            return retval;
        }
        public void share(){
            if(sharedSymbols.size()>0){
                FirstSet minSet=gFirstSet(minSharedSymbol);
                for(Integer symbol:sharedSymbols){
                    FirstSet s=gFirstSet(symbol);
                    if(minSet!=s){
                        minSet.unite(s);
                        sFirstSet(symbol, minSet);
                    }
                }
            }
        }
    }

    void calculateFirstSets(){
        final int n=nTermInfos.size();

        int[][]relys=new int[n][];
        for(int i=0;i<n;i++){
            int m=getNTermByIndex(i).productions.size();
            relys[i]=new int[m];
        }

        boolean change=false;
        do{// check for empty strings and its transtion
            change=false;
            for(int i=0;i<n;i++){
                NonTerminal nt=getNTermByIndex(i);
                Iterator<production> it=nt.productions.iterator();
                for(int j=0;j<relys[i].length;j++){
                    int k=relys[i][j];
                    production p=it.next();
                    final int p_len=p.size();
                    while(k<p_len){
                        int id=p.get(k);
                        if( id<terminals || !gFirstSet(id).nullable()){
                            break;
                        }
                        k++;
                    }
                    if(k!=relys[i][j]){
                        relys[i][j]=k;
                        if(k>=p_len){
                            change=true;
                            // nt.setMayEmpty();
                            gFirstSetByIndex(i).setMayEmpty();
                        }
                    }
                }
            }
        }while(change==true);

        for(int i=0;i<n;i++){// add teminals to first set and solve correlative dependence
            NonTerminal nt=getNTermByIndex(i);
            FirstSet fs=gFirstSetByIndex(i);
            Iterator<production> it=nt.productions.iterator();
            for(int j=0;j<relys[i].length;j++){
                int k=relys[i][j];
                production p=it.next();
                if(k==p.size()){
                    k--;
                }
                for(int v=0;v<=k;v++){
                    int symbol=p.get(v);
                    if(symbol!=i+terminals){// equals itself
                        fs.add(symbol);
                    }
                }
            }


            DFS dfs=new DFS(i+terminals,id->gFirstSet(id));
            dfs.apply(i+terminals);
            dfs.share();
        }
        for(int i=n-2;i>=0;i--){
            FirstSet s=gFirstSetByIndex(i);
            FirstSet back=new FirstSet();
            Iterator<Integer> it=s.iterator();
            while(it.hasNext()){
                Integer symbol=it.next();
                if(symbol>=terminals){
                    it.remove();
                    back.unite(gFirstSet(symbol));
                }
            }
            s.unite(back);
        }
    }

    void calculateFollowSets(){
        gFollowSet(start).add(EOF);
        final int symbolLimit=terminals+nTermInfos.size();
        for(int i=terminals;i<symbolLimit;i++){
            Iterator<production> it=getNTerm(i).productions.iterator();
            while(it.hasNext()){
                production p=it.next();
                final int len=p.size();

                int symbol=p.get(len-1);
                int last_symbol=symbol;
                if(symbol>=terminals){
                    gFollowSet(p.get(len-1)).add(i);
                }
                for(int j=len-2;j>=0;j--){
                    symbol=p.get(j);
                    if(symbol>=terminals){
                        FollowSet followSet=gFollowSet(symbol);
                        if(last_symbol>=terminals){
                            FirstSet fSet=gFirstSet(last_symbol);
                            followSet.unite(fSet);
                            if(fSet.nullable()){
                                followSet.unite(gFollowSet(last_symbol));
                            }
                        }
                        else{
                            followSet.add(last_symbol);
                        }
                    }
                    last_symbol=symbol;
                }
            }
        }
        for(int i=terminals;i<symbolLimit;i++){
            DFS dfs=new DFS(i, id->gFollowSet(id));
            dfs.apply(i);
            dfs.share();
        }
        for(int i=symbolLimit-1;i>=terminals;i--){
            FollowSet s=gFollowSet(i);
            FollowSet back=new FollowSet();
            Iterator<Integer> it=s.iterator();
            while(it.hasNext()){
                Integer symbol=it.next();
                if(symbol>=terminals){
                    it.remove();
                    back.unite(gFollowSet(symbol));
                }
            }
            s.unite(back);
        }
    }

    class LR0Term{
        int nonTerminal;
        int position;
        int production_index;
        // TODO: add empty string

        LR0Term(int nonTerminal,int position,int production_index){
            this.nonTerminal=nonTerminal;
            this.position=position;
            this.production_index=production_index;
        }
        boolean completed(){
            return
                position==getNTerm(nonTerminal).productions.get(production_index).size();
        }
        int nextSymbol(){
            return getNTerm(nonTerminal).productions.get(production_index).get(position);
        }
        LR0Term getShifted(){
            if(completed()){
                return null;
            }
            return new LR0Term(nonTerminal,position+1,production_index);
        }
        int getProductionId(){
            return getNTerm(nonTerminal).productions.get(production_index).getId();
        }
        int getProductionSize(){
            return getNTerm(nonTerminal).productions.get(production_index).size();
        }
        @Override
        public boolean equals(Object obj) {
            LR0Term term=(LR0Term)obj;
            return
                term.nonTerminal==nonTerminal &&
                term.position==position &&
                term.production_index==production_index;
        }
        @Override
        public int hashCode() {
            return
                ((nonTerminal&0xffff)<<16) |
                ((position&0xff)<<8) |
                (production_index&0xff);
        }
    }

    class LALR_Term{
        LR0Term core;
        HashSet<Integer> lookaheads;
        Boolean followFirstNullable=null;
        @Override
        public boolean equals(Object obj) {
            return core.equals(((LALR_Term)obj).core);
        }
        @Override
        public int hashCode() {
            return core.hashCode();
        }
        LALR_Term(LR0Term core){
            this.core=core;
        }
        public void setFollowFirstNullable(Boolean followFirstNullable) {
            this.followFirstNullable = followFirstNullable;
        }
        public Boolean getFollowFirstNullable() {
            return followFirstNullable;
        }
    }
    class tempRecord{
        LALR_Set src;
        int symbol;
        LinkedList<LALR_Term> dst=new LinkedList<>();
        tempRecord(LALR_Set src,int symbol,LinkedList<LALR_Term>dst){
            this.src=src;
            this.symbol=symbol;
            this.dst=dst;
        }
    }

    class LALR_Set extends AbstractSet<LALR_Term>{
        HashMap<LR0Term,LALR_Term> set=new HashMap<>();

        BigInteger ntId=BigInteger.ZERO,proId=BigInteger.ZERO,posId=BigInteger.ZERO;
        @Override
        public int size() {
            return set.size();
        }
        @Override
        public Iterator<LALR_Term> iterator() {
            return set.values().iterator();
        }
        @Override
        public boolean add(LALR_Term e) {
           set.put(e.core,e);
           return true;
        }
        @Override
        public boolean contains(Object o) {
            return set.containsKey(((LALR_Term)o).core);
        }
        void calculate(){
            for(LALR_Term item:set.values()){
                LR0Term lr0=item.core;
                ntId=ntId.or(BigInteger.ONE.shiftLeft(lr0.nonTerminal));
                proId=proId.or(BigInteger.ONE.shiftLeft(lr0.production_index+1));
                posId=posId.or(BigInteger.ONE.shiftLeft(lr0.position));
            }
        }
        LALR_Term get(LR0Term core){
            return set.get(core);
        }
        @Override
        public int hashCode() {
            return ntId.intValue();
        }
        @Override
        public boolean equals(Object arg0) {
            LALR_Set other=(LALR_Set)arg0;
            return
                ntId.equals(other.ntId)&&
                proId.equals(other.proId)&&
                posId.equals(other.posId);
        }
    }

    LALR_Set E_Closure(LinkedList<LALR_Term> kernel){
        LALR_Set s=new LALR_Set();

        s.addAll(kernel);
        while(!kernel.isEmpty()){
            LALR_Term item=kernel.pollFirst();
            LR0Term lr=item.core;

            if(lr.completed()){
                continue;
            }

            int pos=lr.position;

            production p=getNTerm(lr.nonTerminal).productions.get(lr.production_index);

            int symbol=p.get(pos);
            if(symbol>=terminals){
                NonTerminal nTerminal=getNTerm(symbol);
                int len=nTerminal.productions.size();
                for(int i=0;i<len;i++){
                    LALR_Term new_term=new LALR_Term(new LR0Term(symbol,0,i));
                    if(!s.contains(new_term)){
                        kernel.addLast(new_term);
                        s.add(new_term);
                    }
                }
            }
        }
        s.calculate();
        return s;
    }

    void addTranstionsToQueue(LALR_Set s,LinkedList<tempRecord> queue){
        HashMap<Integer,LinkedList<LALR_Term>> map=new HashMap<>();
        for(LALR_Term item:s){
            LR0Term lr=item.core;

            int pos=lr.position;
            production p=getNTerm(lr.nonTerminal).productions.get(lr.production_index);

            if(lr.completed()){
                continue;
            }

            int symbol=p.get(pos);

            map.compute(symbol, (k,v)->{
                if(v==null){
                    v=new LinkedList<>();
                }
                v.add(new LALR_Term(lr.getShifted()));
                return v;
            });
        }

        map.forEach((k,v)->{
            queue.add(new tempRecord(s, k, v));
        });
    }

    static class state<KEY,VAL>{
        HashMap<KEY,VAL> rule=new HashMap<>();
        int id;
        VAL self;
        state(int id,VAL self){
            this.id=id;
            this.self=self;
        }
        state(){this(0,null);}
        int getID(){return id;}
        VAL getSelf(){return self;}
        void addEdge(KEY e,VAL s){
            rule.put(e, s);
        }
        VAL getEdge(KEY e){
            return rule.get(e);
        }
        void removeEdge(KEY e){
            rule.remove(e);
        }

        void forEach(BiConsumer<? super KEY, ? super VAL> arg0){
            rule.forEach(arg0);
        }
    }

    HashMap<LALR_Set,state<Integer,LALR_Set>> setMap=new HashMap<>();
    int state_array[][];

    void LALR_to_DFA(){
        addInitSymbol();
        calculateFirstSets();
        final int init_symbol=getInitSymbol();
        LALR_Term init_term=new LALR_Term(new LR0Term(init_symbol, 0, 0));
        LALR_Set init_set=null;
        boolean init=true;

        LinkedList<LALR_Term> kernel=new LinkedList<>();
        kernel.add(init_term);
        LinkedList<tempRecord> queue=new LinkedList<>();
        queue.addLast(new tempRecord(null,-1,kernel));


        counter cnt=new counter();

        while(!queue.isEmpty()){
            tempRecord tmp=queue.pollFirst();
            LALR_Set s=E_Closure(tmp.dst);

            if(init){
                init_set=s;
                init=false;
            }

            LALR_Set self=setMap.compute(s, (k,v)->{
                if(v==null){
                    v=new state<>(cnt.curInteger(),s);
                    cnt.Inc();
                    addTranstionsToQueue(s, queue);
                }
                return v;
            }).getSelf();

            if(tmp.src!=null){
                setMap.get(tmp.src).addEdge(tmp.symbol, self);
            }
        }

        LinkedList<Integer> init_lookaheads=new LinkedList<>();
        init_lookaheads.add(EOF);
        broadcastLookaheads(init_term, init_lookaheads, init_set);
    }

    int [][] genArray()throws Exception{
        state_array=new int[setMap.size()][getNonTerminalNum()+terminals];
        final int VALID=0x1;
        final int SHIFT_REDUCTION=0x2; // shift=2,reduction=0
        final int FINISHED=0x4;
        // 0x8: reserved
        // other: reduction: which production ; shift: next state
        for(LALR_Set set:setMap.keySet()){
            state<Integer,LALR_Set> st=setMap.get(set);
            for(LALR_Term item:set){
                LR0Term core=item.core;
                if(core.completed()){
                    for(int lookahead:item.lookaheads){

                        if(core.nonTerminal==getInitSymbol() && lookahead==EOF){
                            state_array[st.getID()][lookahead+1]=VALID|FINISHED;
                            continue;
                        }

                        if(state_array[st.getID()][lookahead+1]!=0){
                            throw new Exception("reduce-reduce conflict!");
                        }
                        state_array[st.getID()][lookahead+1]=
                        // pro_id,nonterminal  flags
                        //    28                 4
                            VALID|
                            (core.getProductionId()<<4);
                    }
                }
            }
            st.forEach((k,v)->{
                int symbol=k;
                int next_state=setMap.get(v).getID();
                if(state_array[st.getID()][symbol+1]!=0){
                    System.out.println("shift-reduce conflict!");
                    System.out.printf("before:%d,after:%d\n",state_array[st.getID()][symbol+1],VALID|SHIFT_REDUCTION|(next_state<<4));
                }
                state_array[st.getID()][symbol+1]=VALID|SHIFT_REDUCTION|(next_state<<4);
            });
        }
        return state_array;
    }

    void broadcastLookaheads(LALR_Term src,LinkedList<Integer> lookaheads,LALR_Set currentSet){
        if(src.lookaheads==null){
            src.lookaheads=new HashSet<>();
        }
        if(src.lookaheads.addAll(lookaheads)){
            LR0Term lr=src.core;

            if(lr.completed()){
               return; 
            }

            int pos=lr.position;
            
            production p=getNTerm(lr.nonTerminal).productions.get(lr.production_index);

            int symbol=p.get(pos);
            if(symbol>=terminals){
                LinkedList<Integer> reducedLookaheads=new LinkedList<>();
                NonTerminal nTerminal=getNTerm(symbol);
                int pro_num=nTerminal.productions.size();

                if(src.getFollowFirstNullable()==null){
                    int p_size=p.size();
                    int index=pos+1;// the first not nullable symbol after pos
                    for(;index<p_size;index++){
                        int symbol_term=p.get(index);
                        if(symbol_term>=terminals){
                            FirstSet fSet=gFirstSet(symbol_term);
                            reducedLookaheads.addAll(fSet.set);
                            if(!fSet.nullable()){
                                break;
                            }
                        }
                        else{
                            reducedLookaheads.add(symbol_term);
                        }
                    }
                    if(index==p_size){// all might be null
                        src.setFollowFirstNullable(true);
                    }
                    else{
                        src.setFollowFirstNullable(false);
                    }
                }

                if(src.getFollowFirstNullable()){
                    reducedLookaheads.addAll(src.lookaheads);
                }

                if(reducedLookaheads.size()>0){
                    for(int i=0;i<pro_num;i++){
                        LR0Term new_term=new LR0Term(symbol,0,i);
                        LALR_Term nextSrc=currentSet.get(new_term);
                        broadcastLookaheads(nextSrc,reducedLookaheads,currentSet);
                    }
                }
            }
            LALR_Set nextSet=setMap.get(currentSet).getEdge(symbol);
            LALR_Term nextSrc=nextSet.get(lr.getShifted());
            broadcastLookaheads(nextSrc, lookaheads, nextSet);  
        }
    }
}

interface SymbolSet extends Iterable<Integer>{
    void add(Integer i);
    boolean contains(Integer i);
    void remove(Integer i);
    void addAll(Collection<Integer> collect);
}


class NonTerminalInfo{
    NonTerminal nt;
    FirstSet firstSet=new FirstSet();
    FollowSet followSet=new FollowSet();

    NonTerminalInfo(NonTerminal nt){
        this.nt=nt;
        if(nt.nullable()){
            firstSet.setMayEmpty();
        }
    }
}

class FirstSet implements SymbolSet{
    HashSet<Integer> set=new HashSet<>();
    boolean may_be_empty;
    boolean nullable(){
        return may_be_empty;
    }
    void setMayEmpty(){
        may_be_empty=true;
    }

    @Override
    public void add(Integer i) {
        set.add(i);
    }
    @Override
    public boolean contains(Integer i) {
        return set.contains(i);
    }
    @Override
    public void remove(Integer i) {
        set.remove(i);
    }
    @Override
    public void addAll(Collection<Integer> collect) {
        set.addAll(collect);
    }
    public void unite(FirstSet other){
        set.addAll(other.set);
    }
    public boolean hasSameSet(FirstSet other){
        return set==other.set;
    }
    @Override
    public Iterator<Integer> iterator() {
        return set.iterator();
    }
}

class FollowSet extends FirstSet{

}

