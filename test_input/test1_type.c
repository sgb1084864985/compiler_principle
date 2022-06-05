int printf(char* format,...);

int i;
short s;
float f;
double d;
char e;
long l;

int main(){
    int I;
    short S;
    float F;
    double D;
    char E;
    long L;
    I=1;
    i=2;
    S=3;
    s=4;
    F=5;
    f=5;
    D=6;
    d=7;
    E=8;
    e=9;
    L=10;
    l=11;
    double result;
    result=I+i+S+s+F+f+D+d+E+e+L+l;
    printf("%lf\n",result);
}