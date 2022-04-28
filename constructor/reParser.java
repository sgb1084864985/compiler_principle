import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.function.BiConsumer;

// reParser.java

public class reParser{
    public static void main(String[] args)throws Exception{
        reParser p=new reParser();
        String []patterns={"[\\n\\t\\sε]"};
        tokenLabel []labels={new tokenLabel("identifier"),new tokenLabel("number")};
        DFA dfa=p.parseToDfaWithMultiPattern(patterns, labels, "char");
        System.out.println(dfa);
    }
    DFA parseToDfaWithMultiPattern(String[]ss,tokenInfo[]infos,String type)throws Exception{
        NFA start=parseToNfaWithInfo(ss[0], infos[0], type);
        for(int i=1;i<ss.length;i++){
            start.union(parseToNfaWithInfo(ss[i], infos[i], type));
        }
        return start.toDFA().getMinimizedDFA();
    }
    DFA parseToDfaWithMultiPattern(Iterator<String>ss,Iterator<tokenInfo>infos,String type)throws Exception{
        if(!ss.hasNext()) return null;
        NFA start=parseToNfaWithInfo(ss.next(), infos.next(), type);
        while(ss.hasNext()){
            String reg=ss.next();
            tokenInfo tInfo=infos.next();
            start.union(parseToNfaWithInfo(reg,tInfo,type));
        }
        return start.toDFA().getMinimizedDFA();
    }
    DFA parseToDFA(String s,tokenInfo info,String type)throws Exception{
        return parseToNfaWithInfo(s, info, type).toDFA();
    }
    NFA parseToNfaWithInfo(String s,tokenInfo info,String type)throws Exception{
        NFA nfa=parse2NFA(s, type);
        nfa.setInfo(info);
        return nfa;
    }
    NFA parse2NFA(String s,String type) throws Exception{
        LinkedList<NFA> operandStack=new LinkedList<>();
        LinkedList<Operator> operatorStack=new LinkedList<>();

        elementFactory eFactory=new elementFactory();
        nfaFactory nFactory=new nfaFactory();        
        OpContext context=new OpContext();

        boolean lastOpRight=true;
        boolean opLeft=false;
        boolean opRight=false;
        int i=0;
        while(i<s.length()){
            char c=s.charAt(i);
            Operator op=null;
            Operator lastOp=null;

            opLeft=false;
            opRight=false;

            if((op=Operator.getOp(c))!=null){
                opLeft=op.opLeft();
                opRight=op.opRight();
            }

            if(lastOpRight || opLeft){
                i++;
            }
            else{
                op=context.getSeparator();
                opLeft=op.opLeft();
                opRight=op.opRight();
            }

            if(op!=null){
                while(true){
                    lastOp=operatorStack.peekLast();
                    int cmp=0;
                    if(lastOp!=null){
                        cmp=Operator.compareTo(lastOp, op);
                    }
                    if(cmp>=0){
                        if(cmp==1){
                            lastOp.op(operandStack);
                            operatorStack.removeLast();
                            continue;
                        }
                        operatorStack.addLast(op);
                    }
                    else{
                        operatorStack.removeLast();
                    }
                    break;
                }
                context.addContext(op);
            }
            else{
                NFA n=null;
                if(c=='\\'){
                    char escape_c=s.charAt(i);
                    i++;
                    switch(escape_c){
                        case 's': c=' ';break;
                        case 'n': c='\n';break;
                        case 't': c='\t';break;
                        case 'f': c='\f';break;
                        case 'v': c=0x0b;break;
                        case '0': c=0;break;
                        case 'a': c=0x7;break;
                        case 'b': c=0x8;break;
                        case 'r': c=0x0d;break;
                        case 'e': c=0x1b;break;
                        default: c=escape_c;
                    }
                }
                
                if(c=='ε'){
                    n=nFactory.getNFAByElement(null);
                }
                else{
                    n=nFactory.getNFAByElement(eFactory.getElementByChar(c,type));
                }
                operandStack.addLast(n);
            }
            lastOpRight=opRight;
        }

        while(!operatorStack.isEmpty()){
            Operator lastOp=operatorStack.pollLast();
            lastOp.op(operandStack);
        }

        if(operandStack.size()!=1){
            throw new Exception("regular expression not correct");
        }

        return operandStack.get(0);
    }

    NFA parseToNFA(String s,String type){    
        ArrayList<NFA> toParse=new ArrayList<>();
        elementFactory eFactory=new elementFactory();
        nfaFactory nFactory=new nfaFactory();
        for(int i=0;i<s.length();){
            switch(s.charAt(i)){
                case '|':
                    return toCat(toParse).union(parseToNFA(s.substring(i+1),type));
                case '(':
                    int j=i+1;
                    int cnt=0;
                    for(;j<s.length();j++){
                        char c=s.charAt(j);
                        if(c=='('){
                            cnt--;
                        }
                        else if(c==')'){
                            if(cnt==0){
                                break;
                            }
                            cnt++;
                        }
                    }
                    toParse.add(parseToNFA(s.substring(i+1, j),type));
                    i=j+1;
                    break;
                case '*':
                    NFA nStar=toParse.get(toParse.size()-1);
                    toParse.set(toParse.size()-1, nStar.star());
                    i++;
                    break;
                default:
                    NFA n=nFactory.getNFAByElement(eFactory.getElementByChar(s.charAt(i),type));
                    toParse.add(n);
                    i++;
                    break;
            }
        }
        return toCat(toParse);
    }
    static NFA multiOp2(Iterator<NFA> it,BiConsumer<NFA,NFA> func){
        if(!it.hasNext()) return null;
        NFA start=it.next();
        while(it.hasNext()){
            func.accept(start, it.next());
        }
        return start;
    }
    NFA toUnion(ArrayList<NFA> list){
        if(list.isEmpty()) return null;
        NFA start=list.get(0);
        for(int i=1;i<list.size();i++){
            start.union(list.get(i));
        }
        return start;
    }
    NFA toCat(ArrayList<NFA> list){
        if(list.isEmpty()) return null;
        NFA start=list.get(0);
        for(int i=1;i<list.size();i++){
            start.cat(list.get(i));
        }
        return start;
    }
}