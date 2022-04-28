//
// Created by zlz on 22-4-25.
//

#include "Scanner2.h"

void Scanner2::startAnalyze() {
    current_state=getStartState();
    nextChar();
    nextToken();
}

void Scanner2::nextToken() {
    int state;
    int lastToken=-1;
    static const int NOT_RECOGNIZED=-1;
    std::istream::pos_type lastRecognized;
    int lastPos=NOT_RECOGNIZED;
//    int token;

    clearString();

    if(getChar()==EOF){
        current_token=EOF;
        return;
    }
    while(true){
        state=nextState(getChar());
        if(isErrorState(state)){
            if(lastPos==NOT_RECOGNIZED){
                if(!isEOF()) pushChar(getChar());
//                pushChar('\0');
                printf("%s:unrecognized\n",getTokenString());
                exit(0);
            }
            setChar(lastPos);
            current_token=lastToken;
            current_state=getStartState();
            if(input.tellg()!=lastRecognized){
                input.seekg(lastRecognized);
            }
            break;
        }

        pushChar(getChar());
        nextChar();
        current_state=state;

        if(isRecognizedToken(table.tokens[state])){
            lastRecognized= input.tellg();
            lastPos=getStrPos();
            lastToken=table.tokens[state];
        }

    }
}
