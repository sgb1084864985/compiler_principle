#include "compiler.h"

#include "TokenInput.h"

#include "Token.hpp"

void TokenInput::unget(const symbol_ptr& val) {
    unputCache.push_back(val);
}

symbol_ptr TokenInput::next() { // pop top, return new top
    _next();
    return top();
}

void TokenInput::_next() {

    if(!unputCache.empty()){
        unputCache.pop_back();
    }
    else{
        symbol_ptr new_token;
        int tid;

        do{
            if(!hasNext()) {
                new_token=std::make_shared<Token>(EOF,"","$");
                break;
            }
            scanner2.nextToken();
            tid=scanner2.getToken();
        }while (!(new_token=actions[tid](scanner2.getTokenString(),scanner2,con)).use_count());
        cache=new_token;
    }
}

symbol_ptr TokenInput::top() {
    if(!unputCache.empty()){
        return unputCache.back();
    }
    return cache;
}

bool TokenInput::hasNext() {
    return !scanner2.isEOF();
}

TokenInput::TokenInput(TokenActions &actions_obj, Scanner2 &scanner2, TokenContext &con)
        : actions(actions_obj.getTokenActions()), scanner2(scanner2), con(con) {
    symbol_ptr new_token;

    int tid=scanner2.getToken();
    if(tid==EOF){
        cache= std::make_shared<Token>(EOF,"","$");
        return;
    }

    // is delimiter
    if(!(new_token=actions[tid](scanner2.getTokenString(),scanner2,con)).use_count()){
        _next();
    }
    else{
        cache=new_token;
    }
}