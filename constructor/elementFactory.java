// elementFactory.java

public class elementFactory{
    element getElementByChar(char c,String type){
        if(type.equals("char")){
            return new lexChar(c);
        }
        return null;
    }
}