//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_PRODUCTIONS_H
#define COMPILER_PRODUCTIONS_H

#include "compiler.h"

class Productions{
public:
    vector<Production>& getProductions();

private:
    vector<Production> productions;
};

#endif //COMPILER_PRODUCTIONS_H
