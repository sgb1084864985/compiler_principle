import java.io.File;
import java.io.FileOutputStream;

public class Constructor{
    public static void main(String args[])throws Exception{
        System.out.println("It's Java");
        FileOutputStream out=new FileOutputStream(new File("token_data.cpp"));
        out.close();

        out=new FileOutputStream(new File("CFG_data.cpp"));
        out.close();
    }
}