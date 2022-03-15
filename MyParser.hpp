// MyParser.hpp

#include "compiler.h"
#include <unordered_map>
#include <vector>
#include <memory>

using std::vector;
using std::unordered_map;

class MyParser{
public:
//    constexpr static int terminal_num=0;
//    constexpr static int symbol_num=0;
//    constexpr static int state_num=0;
//    constexpr static int production_num=0;

//    constexpr static int init_symbol=0;

    constexpr static int UNDEFINED=-1;
    constexpr static int FINISHED=-2;

    void setStartState();
    void setTransitions();

    MyParser(vector<Production>&actions):actions(actions){
        setStartState();
        setTransitions();
    }
private:
    // const char* symbol_table[symbol_num];
//    int nTermToProd[symbol_num-terminal_num];
    vector<Production>& actions;

    int start_state=0;
    int** transitions= nullptr;

    class SymbolArgs :public Iterator<SymbolValue*>{
    private:
        int begin;
        vector<SymbolValue*>& stack;
    public:
        SymbolArgs(vector<SymbolValue*>& stack,int begin):begin(begin),stack(stack){}
        const SymbolValue& next() override{
            return stack[begin];
            begin++;
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

        while (input.hasNext()){
            int current_state=state_stack.back();
            SymbolValue& symbol=*(input.next());
            int transition=transitions[current_state][symbol.getID()];

            if(UNDEFINED==transition){
                // TODO:error
            }
            if(FINISHED==transition){
                // TODO:end
            }
            if(transition<FINISHED){
                value_stack.push_back(&symbol);
                state_stack.push_back(-transition+FINISHED-1);
            }
            else{
                Production& p=actions[transition];
                int len=p.size();
                SymbolArgs args(value_stack,value_stack.size()-len);
                auto  f= p.action;
                input.untake(f(args,con));
                value_stack.resize(value_stack.size()-len);
                state_stack.resize((value_stack.size()-len));
            }
        }
        // TODO:error
    }
};


