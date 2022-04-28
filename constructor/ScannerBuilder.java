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

        int start=dfa.start;
        int size=dfa.size();
        int []tokens=new int[size];

        writer.print(size+"\n"+CHAR_SIZE+"\n"+size+"\n"+start+"\n");

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

            for(int state:table){
                writer.println(state);
            }
        }
        for(int token:tokens){
            writer.println(token);
        }

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