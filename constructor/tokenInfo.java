// tokenInfo.java

// to distinguish different classes finite state, give them different info;
public interface tokenInfo extends Comparable<tokenInfo>{
    int ord();
}

class tokenInt implements tokenInfo{
    int id;
    tokenInt(int id){
        this.id=id;
    }
    @Override
    public int compareTo(tokenInfo arg0) {
        tokenInt a0=(tokenInt)arg0;
        if(id<a0.id) return 1;
        if(id==a0.id) return 0;
        return -1;
    }
    @Override
    public int ord() {
        return id;
    }
}

class tokenLabel implements tokenInfo{
    String info;
    int priority;// the smaller, the bigger
    tokenLabel(String str){
        this(str, 0);
    }
    tokenLabel(String str,int pri){
        info=str;
        priority=pri;
    }
    @Override
    public int compareTo(tokenInfo arg0) {
        tokenLabel a0=(tokenLabel)arg0;
        if(priority<a0.priority) return 1;
        if(priority==a0.priority) return 0;
        return -1;
    }
    @Override
    public String toString() {
        return info;
    }
    @Override
    public int ord() {
        return priority;
    }
}