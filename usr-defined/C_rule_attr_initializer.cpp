//
// Created by zlz on 22-4-29.
//
#include <string>
#include <fstream>
#include <sstream>

using std::string;
int main(){
    string before=R"(
//
// Created by zlz on 22-4-29.
//

#include "C_rule_attr.h"

using std::unique_ptr;
using std::make_unique;
unique_ptr<ProductionInfo> C_RuleAttributesPool::ruleAttrTable[]={
)";
    string after=R"(
};
)";
    std::fstream file("cfg_rules.txt",std::ios::in);
    std::fstream obj("C_rule_attr_template.cpp",std::ios::out);
    obj<<before;

    string buf;
    std::getline(file,buf);
    while (true){
        std::getline(file,buf);
        if(file.eof()){
            break;
        }
        obj<<"\t//";
        obj<<buf;
        obj<<"->";
        std::getline(file,buf);
        obj<<buf<<std::endl;
        obj<<"\tmake_unique<ProductionInfo>(),"<<std::endl;
    }
    obj<<after;
    file.close();
    obj.close();
}