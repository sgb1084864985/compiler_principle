// MyParser.hpp

#include "compiler.h"
#include "TokenInput.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

using std::vector;
using std::unordered_map;

class MyParser{
public:
//    constexpr static int terminal_num=0;
//    constexpr static int symbol_num=0;
//    constexpr static int state_num=0;
//    constexpr static int production_num=0;

//    constexpr static int init_symbol=0;

    constexpr static int VALID=0x1;
    constexpr static int SHIFT_REDUCE=0x2;
    constexpr static int FINISHED=0x4;

    // TODO:implement
    void getCFG_data();

    explicit MyParser(vector<Production>&actions):actions(actions){
        getCFG_data();
    }
private:
    // const char* symbol_table[symbol_num];
//    int nTermToProd[symbol_num-terminal_num];
    vector<Production>& actions;

    int start_state=0;
    int symbols=0;
    int* transitions= nullptr;

    class SymbolArgs :public Iterator<SymbolValue*>{
    private:
        int begin;
        vector<SymbolValue*>& stack;
    public:
        SymbolArgs(vector<SymbolValue*>& stack,int begin):begin(begin),stack(stack){}
        SymbolValue* next() override{
            return stack[begin++];
        }
        bool hasNext() override{
            return begin==stack.size();
        }
    };

public:
    void parse(TokenInput& input,Context& con){
        vector<SymbolValue*> value_stack;
        vector<int> state_stack;

        state_stack.push_back(start_state);

        int current_state;
        while (input.hasNext()){
            current_state=state_stack.back();
            SymbolValue& symbol=input.next();
            int transition=transitions[symbols*current_state+symbol.getID()];

            if(!(transition&VALID)){
                // TODO:error
                std::cout<<"error"<<std::endl;
            }
            if(transition&FINISHED){
                break;
                // TODO:end
            }
            if(transition&SHIFT_REDUCE){
                value_stack.push_back(&symbol);
                state_stack.push_back(transition>>4);
            }
            else{
                Production& p=actions[transition>>12];
                int len=(transition>>4)&0xff;
                SymbolArgs args(value_stack,(int)value_stack.size()-len);
                input.unput(p(args, con));
                value_stack.resize(value_stack.size()-len);
                state_stack.resize((value_stack.size()-len));
            }
        }
        if(!(transitions[current_state*symbols+EOF]&FINISHED)){
            std::cout<<"error"<<std::endl;
        }
        // TODO:error
    }
};


