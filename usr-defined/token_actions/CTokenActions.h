//
// Created by zlz on 22-4-25.
//

#ifndef COMPILER_CTOKENACTIONS_H
#define COMPILER_CTOKENACTIONS_H

#include "TokenActions.h"
class CTokenActions :public TokenActions{
    vector<TokenAction> lstTokenActions;
public:
    vector<TokenAction>& getTokenActions()override;
    void printTokens()override;
};


#endif //COMPILER_CTOKENACTIONS_H
