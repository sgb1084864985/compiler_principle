import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;
import java.util.function.BiFunction;

// Constructor.java

public class Constructor{
    public static void main(String[] args)throws Exception{
        if(args.length<2){
            throw new Exception("too few arguments");
        }
        HashMap<String,tokenLabel> map=new HashMap<>();
        BufferedOutputStream out=new BufferedOutputStream(new FileOutputStream(new File("token_data")));
        Scanner input=new Scanner(new File(args[0]));
        ScannerBuilder builder=new ScannerBuilder();

        counter cnt=new counter();
        int num_regx=input.nextInt();
        Iterator<tokenInfo> info_it=new Iterator<tokenInfo>() {
            @Override
            public boolean hasNext() {
                return input.hasNext();
            }
            @Override
            public tokenInfo next() {
                String label=input.next();
                tokenLabel info=new tokenLabel(label,cnt.curInteger());
                map.put(label, info);
                cnt.Inc();
                return info;
            };
        };

        builder.build(new Iterator<String>() {
            @Override
            public String next() {
                return input.next();
            }
            @Override
            public boolean hasNext() {
                return cnt.curInteger()<num_regx;
            }
        }, info_it, map,out);

        while(info_it.hasNext()){
            info_it.next();
        }

        input.close();
        out.close();

        System.out.println("scanner build done");

        Scanner input2=new Scanner(new File(args[1]));
        PrintWriter writer=new PrintWriter(new File("CFG_data.cpp"));

        final int terminals=cnt.curInteger();
        CFG cfg=new CFG(terminals);

        BiFunction<String,tokenLabel,tokenLabel> func=(String k,tokenLabel v)->{
            if(v==null){
                v=new tokenLabel(k,cnt.curInteger());
                cnt.Inc();
                cfg.addNonterminal(new NonTerminal(k));
            }
            return v;
        };
        
        final int n=Integer.valueOf(input2.nextLine());
        ArrayList<production> table=new ArrayList<>();
        for(int i=0;i<n;i++){
            String nString=input2.nextLine();
            int id=map.compute(nString,func).ord();
            NonTerminal nonTerminal=cfg.getNTerm(id);
            String right_hand_side=input2.nextLine();
            String[] symbols=right_hand_side.split(" +");
            production product=new production(id,symbols);
            table.add(product);
            nonTerminal.addProduction(product);
            if(symbols.length==0){
                nonTerminal.setMayEmpty();
            }
            for(String symbol:symbols){
                product.add(map.compute(symbol,func).ord());
            }
        }

        boolean legal=true;
        for(NonTerminalInfo info:cfg.nTermInfos){
            if(info.notLegal()){
                legal=false;
                System.out.println("symbol "+info.nt.label+":no production");
            }
        }
        if(!legal){
            throw new Exception("error occured");
        }
        // final int symbols=cfg.getNonTerminalNum()+terminals;
        cfg.LALR_to_DFA();
        System.out.println("parser build done");
        writeCFG(cfg,writer,table);
        System.out.println("write parser table done");
        input2.close();
        writer.close();
    }

    static void writeCFG(CFG cfg,PrintWriter out,ArrayList<production> table)throws Exception{
        int array[][]=cfg.genArray();
        out.println("#include \"MyParser.hpp\"\n");
        
        out.println("void MyParser::getCFG_data(){");
        out.println(String.format("\tstatic int array[][%d]={",array[0].length));
        for(int i=0;i<array.length;i++){
            out.print("\t\t");
            for(int j=0;j<array[i].length;j++){
                out.printf("%4d,",array[i][j]);
            }
            out.print("\n");
        }
        out.println("\t};");

        out.printf("\tstatic int _p_size[]={");
        for(int i=0;i<table.size();i++){
            if(i%12==0){
                out.printf("\n\t\t");
            }
            production p=table.get(i);
            out.print(p.size()+",");
        }
        out.println("\n\t};");

        out.printf("\tstatic int _p_nonterm[]={");
        for(int i=0;i<table.size();i++){
            if(i%12==0){
                out.printf("\n\t\t");
            }
            production p=table.get(i);
            out.print(p.getStartSymbol()+",");

        }
        out.println("\n\t};");

        out.println("\tp_size=_p_size;");
        out.println("\tnon_term=_p_nonterm;");
        out.println("\ttransitions=(int*)array;");
        out.printf("\tstart_state=%d;\n",cfg.getInitState());
        out.printf("\tsymbols=%d;\n",cfg.terminals+cfg.getNonTerminalNum());
        out.println("}");
    }
}