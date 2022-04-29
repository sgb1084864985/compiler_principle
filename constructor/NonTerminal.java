
import java.util.ArrayList;

public class NonTerminal {
    ArrayList<production> productions=new ArrayList<>();
    String label;
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

    NonTerminal(String label){
        this.label=label;
    }
    @Override
    public String toString() {
        return label;
    }

    boolean notLegal(){
        return productions.size()<=0;
    }
}
