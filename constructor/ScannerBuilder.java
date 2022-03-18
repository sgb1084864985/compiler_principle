import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.Scanner;

// ScannerBuilder.java

public class ScannerBuilder{
    static final int CHAR_SIZE=128;
    static final int ERROR_STATE=-1;
    static final int UNRECOGNIZED_TOKEN=-2;
    static final int MAX_TOKEN_SIZE=80;
    static final int END_TOKEN=0;

    String scanner1="scanner_part1.txt";
    String scanner2="scanner_part2.txt";
    public static void main(String[] args)throws Exception{
        ScannerBuilder builder=new ScannerBuilder();
        InputStream in=System.in;
        OutputStream out=new FileOutputStream("scanner.cpp");
        if(args!=null){
            if(args.length>=1){
                in=new FileInputStream(args[0]);
            }
        }
        builder.build(in, out);
    }

    void setInputFile(String s1,String s2){
        scanner1=s1;
        scanner2=s2;
    }

    public void build(InputStream in,OutputStream out)throws Exception{
        Scanner reader=new Scanner(in);
        build(new Iterator<String>() {
            @Override
            public String next() {
                return reader.nextLine();
            }
            @Override
            public boolean hasNext() {
                return reader.hasNextLine();
            }
        },new Iterator<tokenInfo>() {
            int i=0;
            @Override
            public boolean hasNext() {
                return true;
            }
            @Override
            public tokenInfo next() {
                tokenInfo ret=new tokenInt(i);
                i++;
                return ret;
            }
        },new BufferedOutputStream(out)
        );
        reader.close();
    }

    public void build(Iterator<String> ss,Iterator<tokenInfo> tt, OutputStream out)throws Exception{
        copy(new BufferedInputStream(new FileInputStream(scanner1)),out);
        out.flush();
        reParser parser=new reParser();
        DFA_Impl dfa=(DFA_Impl)parser.parseToDfaWithMultiPattern(ss,tt,"char");

        PrintWriter writer=new PrintWriter(out);

        int start=dfa.start;
        int size=dfa.size();
        int tokens[]=new int[size];

        writer.print('\n');
        writer.println("#define STATES_SIZE ("+size+")");
        writer.println("#define CHAR_NUMS ("+CHAR_SIZE+")");
        writer.println("#define START_STATE ("+start+")");
        writer.println("#define END_TOKEN ("+END_TOKEN+")");
        writer.println("#define ERROR_STATE ("+ERROR_STATE+")");
        writer.println("#define UNRECOGNIZED_TOKEN ("+UNRECOGNIZED_TOKEN+")");
        writer.println("#define MAX_TOKEN_SIZE ("+MAX_TOKEN_SIZE+")\n");

        writer.println("int status[][CHAR_NUMS]={");

        for(int i=0;i<size;i++){
            tokens[i]=UNRECOGNIZED_TOKEN;
        }

        for(int i=0;i<size;i++){
            int [] table=new int[CHAR_SIZE];
            for(int j=0;j<table.length;j++){
                table[j]=ERROR_STATE;
            }
            tokenInfo tI=dfa.table.get(i).getInfo();
            if(tI!=null){
                tokens[i]=tI.ord();
            }
            dfa.table.get(i).rule.forEach((k,v)->{
                int token=((lexChar)k).c;
                table[token]=v;
            });
            writer.print("    ");

            for(int state:table){
                writer.print(state+",");
            }
            writer.print('\n');
        }
        writer.println("};");
        writer.println("int tokens[]={");
        writer.print("    ");
        for(int token:tokens){
            writer.print(token+",");
        }
        writer.println("\n};");
        writer.flush();
        copy(new BufferedInputStream(new FileInputStream(scanner2)),out);
        out.close();
    }

    void copy(InputStream is,OutputStream os)throws IOException{
        int c;
        while(true){
            c=is.read();
            if(c==-1) break;
            os.write(c);
        }
        is.close();
    }
}