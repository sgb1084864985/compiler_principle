import java.util.HashMap;
import java.util.LinkedList;

public enum Operator{
    rightParent{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return false;
        }
    },
    union{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return true;
        }
        @Override
        void op(LinkedList<NFA> operandStack) {
            NFA op2=operandStack.getLast();
            operandStack.removeLast();
            NFA op1=operandStack.getLast();
            op1.union(op2);
        }
    },
    star{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return false;
        }
        @Override
        void op(LinkedList<NFA> operandStack) {
            operandStack.getLast().star();
        }
    },
    cat{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return true;
        }
        @Override
        void op(LinkedList<NFA> operandStack) {
            NFA op2=operandStack.getLast();
            operandStack.removeLast();
            NFA op1=operandStack.getLast();
            op1.cat(op2);
        }        
    },
    leftParent{
        @Override
        boolean opLeft() {
            return false;
        }
        @Override
        boolean opRight() {
            return true;
        }  
    },

    leftBracket{
        @Override
        boolean opLeft() {
            return false;
        }
        @Override
        boolean opRight() {
            return true;
        }
    },

    rightBracket{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return false;
        }
    },

    rail{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return true;
        }
        @Override
        void op(LinkedList<NFA> operandStack)throws Exception{
            NFA op2=operandStack.pollLast();
            NFA op1=operandStack.getLast();
            element start=(element)op1.getSingElement().next();
            element end=op2.getSingElement();
            while(start.compareTo(end)<=0){
                op1.union(op1.getSingleElement(start));
                start=start.next();
            }
        }
    },
    plus{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return false;
        }
        @Override
        void op(LinkedList<NFA> operandStack) {
            operandStack.getLast().plus();
        }
    },
    question{
        @Override
        boolean opLeft() {
            return true;
        }
        @Override
        boolean opRight() {
            return false;
        }
        @Override
        void op(LinkedList<NFA> operandStack) {
            NFA n=operandStack.getLast();
            n.union(n.getEmptyNFA());
        }
    },
    dot
    ;

    static HashMap<Character,Integer> opMap=new HashMap<>();
    static{
        char[] opList={')','|','*','\3','(','[',']','-','+','?','.'};
        for(int i=0;i<opList.length;i++){
            opMap.put(opList[i], i);
        }
    }
    static int[][] pre={
      //  ) | * @ ( [  ] - + ? .
        { 1,1,1,1,1,0, 1,1,1,1,0},//)
        { 1,1,0,0,0,0, 1,0,0,0,0},//|
        { 1,1,1,1,1,1, 1,1,1,1,0},//*
        { 1,1,0,1,0,0, 1,0,0,0,0},//@
        {-1,0,0,0,0,0, 1,0,0,0,0},//(
        { 1,0,0,0,0,0,-1,0,0,0,0},//[
        { 1,1,1,1,1,1, 1,1,1,1,0},//]
        { 1,1,1,1,1,0, 1,1,1,1,0},//-
        { 1,1,1,1,1,1, 1,1,1,1,0},//?
        { 1,1,1,1,1,1, 1,1,1,1,0},//.
    };
    static boolean isOp(char c){
        return opMap.containsKey(c);
    }
    static Integer getOpId(char c){
        return opMap.get(c);
    }
    static Operator getOp(char c){
        Integer id=getOpId(c);
        if(id==null) return null;
        return values()[id];
    }
    static int compareTo(Operator op1,Operator op2){//0:op1<op2, 1:op1>op2, -1:op1=op2, -2:error
        return pre[op1.ordinal()][op2.ordinal()];
    }

    // static void opByInt(LinkedList<NFA> operandStack,int i){
    //     Operator.values()[i].op(operandStack);
    // }

    // static void opByChar(LinkedList<NFA> operandStack,char c){
    //     Operator.values()[getOpId(c)].op(operandStack);
    // }
    
    Operator(){
    }
    
    boolean opLeft(){return false;}
    boolean opRight(){return true;}

    void op(LinkedList<NFA> operandStack)throws Exception{}

    public static void main(String[] args) {
    }
}

class OpContext{
    LinkedList<Operator> leftOps=new LinkedList<>();
    void addContext(Operator op) throws Exception{
        if(op==Operator.leftBracket || op==Operator.leftParent){
            leftOps.add(op);
        }
        else{
            if(op==Operator.rightBracket){
                Operator op_=leftOps.pollLast();
                if(op_!=Operator.leftBracket){
                    throw new Exception("parenthesis mismatch");
                }
            }
            else if(op==Operator.rightParent){
                Operator op_=leftOps.pollLast();
                if(op_!=Operator.leftParent){
                    throw new Exception("parenthesis mismatch");
                }                
            }
        }
    }
    Operator getSeparator(){
        Operator op=leftOps.peekLast();
        if(op==null){
            return Operator.cat;
        }
        switch(op){
            case leftBracket:
                return Operator.union;
            case leftParent:
                return Operator.cat;
            default:
                return Operator.cat;
        }
    }
}