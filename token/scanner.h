//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H
namespace SCANNER{
    void startAnalyze();
    int getToken();
    int isEOF();
    int isWhite();
    const char* getTokenString();
    const char* getTokenType();
    void nextToken();
}

#endif //COMPILER_SCANNER_H
