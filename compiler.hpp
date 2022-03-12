// compiler.hpp

template<class T>
class Iterator{
    const T& next();
    bool hasNext();
};

class Context{
};

class SymbolValue{
};

class TerminalValue:public SymbolValue{
    public:
    virtual const char* getText()=0;
    // contains keywords like "if","int"
    // operators: like "<=","<<","->","."
    // "id" ([_a-zA-Z][_0-9a-zA-Z]*)
    // "number"
};

class Production{
    public:
    static const char* start_symbol;
    virtual const char* getLeftHandSide()=0;// eg. "exp"
    virtual const char* getRightHandSide()=0;// eg. "exp + term", must split by space
    virtual SymbolValue action(Iterator<SymbolValue>& args,Context& context)=0;
    // eg. 
    // args = [ exp, +, term ]
    // you need to return exp(exp+term)
    // if neccessary, add them to context (into member namespaces?)
};
