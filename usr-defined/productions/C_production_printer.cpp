//
// Created by zlz on 2022/3/16.
//
#include <fstream>
#include "CProductions.h"
int main(){
    CProductions p;
    auto action=p.getProductions();
    std::ofstream output;
    output.open("cfg_rules.txt",std::ios::out);
    output<<action.size()<<std::endl;
    for(auto&pro:action){
        output<<pro.left_hand_side<<std::endl;
        output<<pro.right_hand_side<<std::endl;
    }
    output.close();
    return 0;
}
