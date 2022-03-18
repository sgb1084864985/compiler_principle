//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H
namespace SCANNER{

#define END_TOKEN (0)
#define ERROR_STATE (-1)
#define UNRECOGNIZED_TOKEN (-2)
#define MAX_TOKEN_SIZE (4096)
#define CHAR_NUMS (128)

    extern int status[][CHAR_NUMS];
    extern int tokens[];

    void startAnalyze();
    int getToken();
    int isEOF();
    int isDELIMITER(int token);
    int isERROR(int token);
    int getStartState();
    const char* getTokenString();
    const char* getTokenType();
    void nextToken();
}

#endif //COMPILER_SCANNER_H
