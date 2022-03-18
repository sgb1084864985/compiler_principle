
import java.util.ArrayList;

public class NonTerminal {
    ArrayList<production> productions=new ArrayList<>();
    boolean may_be_empty=false;
    boolean nullable(){
        return may_be_empty;
    }
    void setMayEmpty(){
        may_be_empty=true;
    }
    void addProduction(production p){
        productions.add(p);
    }
}
