//
// Created by zlz on 22-5-7.
//

#include "GlobalContext.h"

#include <utility>

GlobalContext::GlobalContext(std::ostream &out):error_out(out) {

}

GlobalContext::GlobalContext(std::ostream &out, std::string file_out):error_out(out),file_out(std::move(file_out)) {

}
