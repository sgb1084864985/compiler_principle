// compiler.hpp

#include <functional>
#include <vector>
using std::vector;
using std::function;

template<class T>
class Iterator{
public:
    virtual const T& next()=0;
    virtual bool hasNext()=0;
};

class Context{
};

class SymbolValue{
public:
    virtual int getID()=0;
};

class EmptyValue: public SymbolValue{
    int id;
public:
    EmptyValue(int id):id(id){}
    int getID(){return id;}
};

class TerminalValue:public SymbolValue{
public:
    virtual const char* getText()=0;
    // contains keywords like "if","int"
    // operators: like "<=","<<","->","."
    // "id" ([_a-zA-Z][_0-9a-zA-Z]*)
    // "number"
};


class TokenInput :public Iterator<SymbolValue*>{
public:
    void untake(SymbolValue* val);
};

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

// class Production{
//     public:
//     virtual const char* getLeftHandSide()=0;// eg. "exp"
//     virtual const char* getRightHandSide()=0;// eg. "exp + term", must split by space
//     virtual SymbolValue action(Iterator<SymbolValue>& args,Context& context)=0;
//     // eg.
//     // args = [ exp, +, term ]
//     // you need to return exp(exp+term)
//     // if neccessary, add them to context (into member namespaces?)
// };

class Production{
private:
    int symbols_num;
public:
    const char* left_hand_side;
    const char* right_hand_side;
    int size(){return  symbols_num;}
    function<void(Iterator<SymbolValue>&,Context&)> action;
};