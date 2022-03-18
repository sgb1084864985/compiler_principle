// abstractState.java

public abstract class abstractState{
    tokenInfo finalInfo;
    void addInfo(tokenInfo info){
        if(finalInfo==null || finalInfo.compareTo(info)==-1){
            finalInfo=info;
        }
    }
    tokenInfo getInfo(){
        return finalInfo;
    }
    boolean isFinite(){
        return finalInfo!=null;
    }
}