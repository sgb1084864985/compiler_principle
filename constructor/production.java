// production.java

import java.util.ArrayList;
import java.util.Iterator;

public class production implements Iterable<Integer>{
    ArrayList<Integer> right_hand_list=new ArrayList<>();

    static int id_cnt=0;
    int id;

    int start_symbol;

    production(int sTerminal){
        id=id_cnt;
        id_cnt++;
        start_symbol=sTerminal;
    }

    int getStartSymbol(){return start_symbol;}

    Integer get(int index){
        return right_hand_list.get(index);
    }
    int size(){
        return right_hand_list.size();
    }
    @Override
    public Iterator<Integer> iterator() {
        return right_hand_list.iterator();
    }
    void add(Integer i){
        right_hand_list.add(i);
    }

    public int getId() {
        return id;
    }
}