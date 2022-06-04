//
// Created by zlz on 22-6-4.
//

#include "CProductions.h"

Production Production::default_production(nullptr, nullptr,function<symbol_ptr (Production& self,symbol_iterator &,Context&)>());
