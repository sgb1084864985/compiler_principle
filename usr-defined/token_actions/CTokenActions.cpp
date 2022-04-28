//
// Created by zlz on 22-4-25.
//

#include "CTokenActions.h"
#include "Token.hpp"

// reference: http://www.quut.com/c/ANSI-C-grammar-l-2011.html

// hex prefix
#define HP "0[xX]"
#define HEX "[a-fA-F0-9]"
#define OCT "[0-7]"

// integer size
#define IS "(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))"
#define CP "(u|U|L)"

// string prefix
#define SP "(u8|u|U|L)"

#define ASCII R"([\0\a\b\t\n\v\f\r\e\s!"#$%&'\(\)\*\+\,\-\.\/0123456789:;<=>\?\@\`ABCDEFGHIJKLMNOPQRSTUVWXYZ\[\\\]\^_abcdefghijklmnopqrstuvwxyz\{\}\|\~])"
#define NO_BACK_SLASH R"([\0\a\b\t\n\v\f\r\e\s!"#$%&'\(\)\*\+\,\-\.\/0123456789:;<=>\?\@\`ABCDEFGHIJKLMNOPQRSTUVWXYZ\[\]\^_abcdefghijklmnopqrstuvwxyz\{\}\|\~])"
#define NO_QUOTE R"([\s!"#$%&\(\)\*\+\,\-\.\/0123456789:;<=>\?\@\`ABCDEFGHIJKLMNOPQRSTUVWXYZ\[\\\]\^_abcdefghijklmnopqrstuvwxyz\{\}\|\~])"
#define NO_D_QUOTE R"([\0\a\b\t\n\v\f\r\e\s!#$%&'\(\)\*\+\,\-\.\/0123456789:;<=>\?\@\`ABCDEFGHIJKLMNOPQRSTUVWXYZ\[\\\]\^_abcdefghijklmnopqrstuvwxyz\{\}\|\~])"
#define NO_NEW_LINE R"([\0\a\b\t\v\f\r\e\s!"#$%&'\(\)\*\+\,\-\.\/0123456789:;<=>\?\@\`ABCDEFGHIJKLMNOPQRSTUVWXYZ\[\\\]\^_abcdefghijklmnopqrstuvwxyz\{\}\|\~])"

// escape
#define ES R"((\\(['"\?\\abfnrtv]|[0-7]|[0-7][0-7]|[0-7][0-7][0-7]|x[a-fA-F0-9]+)))"

#define DIGIT "[0-9]"
#define NON_ZERO "[1-9]"
#define LITERAL "[a-zA-Z_]"
#define DELIMITER R"([\t\s\n\v\f]+)"
#define ID LITERAL "(" LITERAL "|" DIGIT ")*"
#define INTEGER1 HP HEX "+" IS "?"
#define INTEGER2 NON_ZERO DIGIT "*" IS "*"
#define INTEGER3 "0" OCT "*" IS "?"
#define INTEGER4 CP "?'(" NO_QUOTE "|" NO_BACK_SLASH "|" NO_NEW_LINE "|" ES ")+'"
#define INTEGER "(" INTEGER1 ")|(" INTEGER2 ")|(" INTEGER3 ")|(" INTEGER4 ")"

#define E R"(([Ee][\+\-]?)" DIGIT "+)"
#define P R"(([Pp][\+\-]?)" DIGIT "+)"
#define FS "(f|F|l|L)"

#define FLOAT1 DIGIT "+" E FS "?"
#define FLOAT2 DIGIT "*\\." DIGIT "+" E "?" FS "?"
#define FLOAT3 DIGIT "+\\." E "?" FS "?"
#define FLOAT4 HP HEX "+" P FS "?"
#define FLOAT5 HP HEX "*\\." HEX "+" P FS "?"
#define FLOAT6 HP HEX "+\\." P FS "?"

#define FLOAT FLOAT1 "|" FLOAT2 "|" FLOAT3 "|" FLOAT4 "|" FLOAT5 "|" FLOAT6
#define STR "(" SP "?\"(" NO_D_QUOTE "|" NO_BACK_SLASH "|" NO_NEW_LINE "|" ES ")*\"" DELIMITER "*)+"


using std::string;
vector<TokenAction> &CTokenActions::getTokenActions() {

//    using func = function<symbol_ptr (TokenAction& self,const char* text, Scanner2&scan, TokenContext& con)>;
    auto normal_func=[](TokenAction& self,const char* text, Scanner2&scan, TokenContext& con){
        return std::make_shared<Token>(self.id,text,self.name.c_str());
    };
    constexpr int buf_len=80;
    vector<string> regx=
            {DELIMITER,ID,INTEGER,FLOAT,STR,"\\+","\\-","\\*","/","\\(","\\)","\\[","\\]",
             "\\{","\\}","\\->","\\+\\+","\\-\\-","\\."};

    vector<string > names =
            {"delimiter","id","integer","float","str","+","-","*","/","(",")","[","]",
             "{","}","->","++","--","."};

    for(int i=0;i<regx.size();i++){
        lstTokenActions.emplace_back(names[i],regx[i],normal_func,i);
    }

    lstTokenActions[0].action=[](TokenAction& self,const char* text, Scanner2&scan, TokenContext& con){
        return std::shared_ptr<Token>();
    };
    return lstTokenActions;
}

void CTokenActions::printTokens() {
    for(auto & item:lstTokenActions){
        std::cout<<item.regx<<" "<<item.name<<std::endl;
    }
}
