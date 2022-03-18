// nfaFactory.java

public class nfaFactory{
    NFA getNFAByElement(element e){
        return new NFA_impl(e);
    }
    NFA getEmptyNFA(){
        return new NFA_impl();
    }
}