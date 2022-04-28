// scanner.cpp

#include "scanner.h"
#include <cstdio>
#include <cstdlib>

namespace SCANNER{

static int current_token;
static char current_char;
static int current_state;

static char current_string[MAX_TOKEN_SIZE];
static int string_pointer;

static inline void pushChar(char c){
    if(string_pointer>=MAX_TOKEN_SIZE){
        printf("token too long");
        exit(0);
    }
    current_string[string_pointer++]=c;
}

static inline void setChar(int pos){
    string_pointer=pos;
    current_string[string_pointer]='\0';
}

static inline int getStrPos(){
    return string_pointer;
}

static inline void clearString(){
    string_pointer=0;
}

static inline int nextState(char c){
    if(c==EOF) return ERROR_STATE;
    return status[current_state][c];
}
static inline void nextChar(){
    current_char=getchar();
}
static inline char getChar(){
    return current_char;
}
static inline int isFinalState(int state){
    return tokens[state]>=END_TOKEN;
}

static inline int isErrorState(int state){
    return state==ERROR_STATE;
}
static inline int isRecognizedToken(int token){
    return token>=END_TOKEN;
}
static inline int isUnRecognizedToken(int token){
    return token==UNRECOGNIZED_TOKEN;
}
int isEOF(){
    return current_char==EOF;
}

const char* getTokenType(){
    return nullptr;
}

void nextToken(){
    int state;
    int lastToken=-1;
    off_t lastRecognized=EOF;
    int lastPos;
    int token;

    clearString();

    if(getChar()==EOF){
        pushChar('\0');
        current_token=EOF;
        return;
    }
    while(true){
        state=nextState(getChar());
        if(isErrorState(state)){
            if(lastRecognized==EOF){
                if(!isEOF()) pushChar(getChar());
                pushChar('\0');
                printf("%s:unrecognized\n",getTokenString());
                exit(0);
            }
            setChar(lastPos);
            current_token=lastToken;
            current_state=getStartState();
            if(ftello(stdin)!=lastRecognized){
                fseeko(stdin,lastRecognized,SEEK_SET);
            }
            break;
        }

        pushChar(getChar());
        nextChar();
        current_state=state;

        if(isRecognizedToken(tokens[state])){
            lastRecognized= ftello(stdin);
            lastPos=getStrPos();
            lastToken=tokens[state];
        }

    }
}

void startAnalyze(){
    current_state=getStartState();
    nextChar();
    nextToken();
}

const char* getTokenString(){
    return current_string;
}

int getToken(){
    return current_token;
}

}