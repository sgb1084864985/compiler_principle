//
// Created by zlz on 22-4-27.
//

#ifndef COMPILER_AST_H
#define COMPILER_AST_H
#include "compiler.h"
#include "NameSpace.h"
namespace AST {

    class NonTerminal : public SymbolValue {
    public:
        vector<symbol_ptr> children;
        std::string label;
        Production production;

        // which namespace this tree_node is in
        ptrAbstractNameSpace owner;

        bool error= false;

        void print(std::ostream &out_port) override {
            out_port << label;
        }

        bool hasError()override{
            return error;
        }

        NonTerminal(Production &production, std::string label) : production(production), label(std::move(label)) {}

    };

    using nLeafPtr = std::shared_ptr<NonTerminal>;
    using leafPtr = std::shared_ptr<TerminalValue>;

    // if not leaf, return false; else return ture;
    bool leafOrNotLeaf(symbol_ptr &src, leafPtr &l, nLeafPtr &nl);

    class AST_Printer {
        std::ostream &out;
        unsigned int cnt = 0;

    public:
        explicit AST_Printer(std::ostream &out) : out(out) {}


        void print(symbol_ptr &root) {
            cnt = 0;
            out << "graph{" << std::endl;
            // TODO: handle back slash, like '\x33', should be '\\x33'
            _print(cnt++, root);
            out << "}";
        }

        void _print(unsigned int ord, symbol_ptr &root);
    };

    template<class T>
    symbol_ptr genTree(Production& p, symbol_iterator&it, Context&con){
        auto ret = std::make_shared<T>(p,p.left_hand_side);
        while (it.hasNext()){
            (ret->children).push_back(it.next());
        }
        return ret;
    }
}

#endif //COMPILER_AST_H
