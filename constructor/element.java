import java.util.Iterator;

// lexeme.java

public interface element extends Comparable<element>,Iterator<element>{
    Object clone() throws CloneNotSupportedException;
    element increase();
    element begin();
}

class lexChar implements element{
    lexChar(char c){
        this.c=c;
    }
    char c;
    @Override
    public int compareTo(element arg0) {
        lexChar l=(lexChar)arg0;
        if(c<l.c) return -1;
        else if(c==l.c) return 0;
        return 1;
    }
    @Override
    public element begin() {
        return new lexChar('\0');
    }
    @Override
    public Object clone() throws CloneNotSupportedException {
        return new lexChar(c);
    }
    @Override
    public boolean equals(Object obj) {
        if(obj==null) return false;
        lexChar l=(lexChar)obj;
        return c==l.c;
    }
    @Override
    public int hashCode() {
        return c;
    }

    @Override
    public String toString() {
        if(Character.isISOControl(c)){
            return "\\"+Integer.toString(c);
        }
        return String.valueOf(c);
    }
    @Override
    public element next() {
        return new lexChar((char)(c+1));
    }
    @Override
    public element increase() {
        c++;
        return this;
    }
    @Override
    public boolean hasNext() {
        return c<128 && c>=0;
    }
}