#include "compiler"

class TokenInput :public Iterator<SymbolValue*>{
public:
    void untake(SymbolValue* val);
};
