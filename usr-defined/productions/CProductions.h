//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_CPRODUCTIONS_H
#define COMPILER_CPRODUCTIONS_H

#include "compiler.h"

class CProductions{
public:
    static void addRules();
    static std::vector<Production>& getProductions(){
        return productions;
    }
    static std::vector<Production>& getAndAdd(){
        addRules();
        return productions;
    }
private:
    static vector<Production> productions;
};

#endif //COMPILER_CPRODUCTIONS_H
