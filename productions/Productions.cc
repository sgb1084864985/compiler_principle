#include "compiler.h"
#include "Productions.h"
#include <vector>

using std::vector;

vector<Production> &Productions::getActions() {
    return *new vector<Production>;
}