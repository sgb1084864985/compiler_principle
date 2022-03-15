#include "compiler.h"

class TokenInput :public Iterator<SymbolValue*>{
public:
    void untake(SymbolValue* val);
};
