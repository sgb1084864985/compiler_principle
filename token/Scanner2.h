//
// Created by zlz on 22-4-25.
//

#ifndef COMPILER_SCANNER2_H
#define COMPILER_SCANNER2_H

#include <istream>
#include <vector>

class TokenTable{
public:
    int start_state=0;
    std::vector<std::vector<int>>& status;
    std::vector<int>& tokens;

    TokenTable(std::vector<std::vector<int>> &status, std::vector<int> &tokens,int start) :
    status(status), tokens(tokens),start_state(start) {}
};

class Scanner2 {
    // members
    std::istream & input;
    std::string current_string;

    int current_token=0;
    char current_char=0;
    int current_state=0;

    TokenTable table;

    // constants
    static constexpr int END_TOKEN=0;
    static constexpr int ERROR_STATE=-1;
    static constexpr int UNRECOGNIZED_TOKEN=-2;
    static constexpr int MAX_TOKEN_SIZE=4096;
    static constexpr int CHAR_NUMS=128;

public:
//    int isDELIMITER(int token);
//    int isERROR(int token);

    Scanner2(std::istream & in, TokenTable t): table(t), input(in){
        startAnalyze();
    };

    void nextToken();
    [[nodiscard]] int getToken() const{
        return current_token;
    }

    [[nodiscard]] int isEOF() const{
        return current_char==EOF;
    }

    const char* getTokenString(){
        return current_string.c_str();
    }

//    const char* getTokenType(){
//        return nullptr;
//    }

private:
    void startAnalyze();

    void setStatus(std::vector<std::vector<int>>& states){
        table.status=states;
    }

    void nextChar(){
        input>>current_char;

        if(input.eof()){
            current_char=EOF;
        }
    }

    char getChar() const{
        return current_char;
    }

    static int isErrorState(int state){
        return state==ERROR_STATE;
    }

    static int isRecognizedToken(int token){
        return token>=END_TOKEN;
    }


    void clearString(){
        current_string.clear();
    }

    void pushChar(char c){
        current_string.push_back(c);
    }

    void setChar(int pos){
        current_string.resize(pos);
    }

    int getStrPos() const{
        return static_cast<int>(current_string.size());
    }

    int nextState(char c){
        if(c==EOF) return ERROR_STATE;
        return table.status[current_state][c];
    }

    int getStartState() const{
        return table.start_state;
    }
};


#endif //COMPILER_SCANNER2_H
