#include "compiler.h"

#include "TokenInput.h"

void TokenInput::unput(SymbolValue *val) {

}

SymbolValue & TokenInput::next() {
    return *((SymbolValue*) nullptr);
}

bool TokenInput::hasNext() {
    return false;
}