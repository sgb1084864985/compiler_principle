// production.java

import java.util.ArrayList;
import java.util.Iterator;

public class production implements Iterable<Integer>{
    ArrayList<Integer> right_hand_list=new ArrayList<>();

    static int id_cnt=0;
    static ArrayList<production> id_map=new ArrayList<>();
    static production getById(int i){
        return id_map.get(i);
    }

    int id;

    int start_symbol;

    String[] text;

    production(int sTerminal){
        id=id_cnt;
        id_map.add(this);

        id_cnt++;
        start_symbol=sTerminal;
    }
    production(int sTerminal,String[] text){
        this(sTerminal);
        this.text=text;
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
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return String.join(" ",text);
    }
}