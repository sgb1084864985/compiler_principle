import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Iterator;

// ScannerBuilder.java

public class ScannerBuilder{
    static final int CHAR_SIZE=128;
    static final int ERROR_STATE=-1;
    static final int UNRECOGNIZED_TOKEN=-2;
    static final int MAX_TOKEN_SIZE=80;
    static final int END_TOKEN=0;

    public void build(Iterator<String> ss,Iterator<tokenInfo> tt,HashMap<String,tokenLabel>map,OutputStream out)throws Exception{

        reParser parser=new reParser();

        PrintWriter writer=new PrintWriter(out);

        DFA_Impl dfa=(DFA_Impl)parser.parseToDfaWithMultiPattern(ss,tt,"char");

        writer.println("#include \"scanner.h\"");
        writer.println("namespace SCANNER{");

        writer.println("\nenum class TokenLabel{");

        for(tokenLabel label:map.values()){
            String str=label.toString();
            if(str.matches("[_a-zA-Z][_a-zA-Z0-9]*")){
                str=str.toUpperCase();
                writer.printf("\t%s=%d,\n",str,label.ord());
            }
        }

        writer.println("};\n");

        for(tokenLabel label:map.values()){
            String str=label.toString();
            if(str.matches("[_a-zA-Z][_a-zA-Z0-9]*")){
                str=str.toUpperCase();
                writer.printf("int is%s(int token){return token==(int)(TokenLabel::%s);}\n",str,str);
            }
        }

        int start=dfa.start;
        int size=dfa.size();
        int tokens[]=new int[size];

        writer.print('\n');
        writer.println("const int START_STATE ="+start+";");
        writer.println("int getStartState(){return START_STATE;}");
        writer.println("int status[][CHAR_NUMS]={");

        for(int i=0;i<size;i++){
            tokens[i]=UNRECOGNIZED_TOKEN;
        }

        for(int i=0;i<size;i++){
            int [] table=new int[CHAR_SIZE];
            for(int j=0;j<table.length;j++){
                table[j]=ERROR_STATE;
            }
            tokenInfo info=dfa.table.get(i).getInfo();
            if(info!=null){
                tokens[i]=info.ord();
            }
            dfa.table.get(i).rule.forEach((k,v)->{
                int token=((lexChar)k).c;
                table[token]=v;
            });
            writer.print("\t");

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

        writer.println("}");
        writer.flush();
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