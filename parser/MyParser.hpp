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
    int* p_size= nullptr;
    int* nonterm= nullptr;

    class SymbolArgs :public Iterator<symbol_ptr>{
    private:
        int begin;
        vector<symbol_ptr>& stack;
    public:
        SymbolArgs(vector<symbol_ptr>& stack,int begin):begin(begin),stack(stack){}
        symbol_ptr next() override{
            return stack[begin++];
        }
        bool hasNext() override{
            return begin==stack.size();
        }
    };

public:
    symbol_ptr parse(TokenInput& input,Context& con){
        vector<symbol_ptr> value_stack;
        vector<int> state_stack;

        state_stack.push_back(start_state);

        int current_state;
        while (true){
            current_state=state_stack.back();
            symbol_ptr symbol=input.top();
            int transition=transitions[symbols*current_state+symbol->getID()+1]; //+1: for EOF(-1)

            if(!(transition&VALID)){
                // TODO:error
                std::cout<<"error"<<std::endl;
                exit(0);
            }
            if(transition&FINISHED){
                std::cout<<"success!"<<std::endl;
                break;
                // TODO:end
            }
            if(transition&SHIFT_REDUCE){
                value_stack.push_back(symbol);
                state_stack.push_back(transition>>4);
                input.next();
            }
            else{
                int pro_index=transition>>4;
                Production& p=actions[pro_index];
                int len=p_size[pro_index];
                SymbolArgs args(value_stack,(int)value_stack.size()-len);
                symbol_ptr reducedSymbol=p(args,con);
                reducedSymbol->setID(nonterm[pro_index]);
                input.unget(reducedSymbol);
                value_stack.resize(value_stack.size()-len);
                state_stack.resize((state_stack.size()-len));
            }
        }
        return value_stack.back();
    }
};


