//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CNAMESPACE_H
#define COMPILER_CNAMESPACE_H

#include "C_type.h"
#include "Csymbols.hpp"
#include "C_constant.h"
#include "NameSpace.h"
#include <string>
#include <memory>
#include <list>
#include <utility>
#include <vector>
#include <unordered_map>

using std::string;
using CTS::ptr_func;
using CTS::ptr_struct;
using CTS::func_item;
using CTS::struct_item;

class CNameSpace: public NameSpace{
public:
	using ptrNamespace = std::shared_ptr<CNameSpace>;

	struct name_item{
		static constexpr int NO_ALLOC=-1;
		ptrType type;

		// empty if it is not a function
		ptr_func func;

		// empty if extern
		// else it is the alloc order in current namespace
		// start from 0
		int alloc_order=NO_ALLOC;

		//        dType dt=dType::SIGNED_INTEGER;
		//        unsigned char dTypeSize{}; // use byte, eg. 1,2,4,8

		explicit name_item(ptrType& type):type(type){}
		name_item(ptrType& type,ptr_func& f):type(type),func(f){}

		bool hasFuncDefinition(){return type->isFunction() && ~!func;};
		void setFuncDefinition(ptr_func& ptrFunc){ this->func=ptrFunc;}
        [[nodiscard]] bool isDeclaration() const{return alloc_order==NO_ALLOC;}
		[[nodiscard]] bool getAllocOrder() const{return alloc_order;}
		[[nodiscard]] ptrType getType() const{return type;}
	};

	using ptr_name=std::shared_ptr<name_item>;

public:
	// this list would follow the declaration order
	const vector<string>& getDeclarationList(){return declaration_list;};
    ptrNamespace getParentSpace(){return parentNamespace;}

	ptr_name get(const string &name); // if not found, goto parent name_table
	ptr_name get(const string &&name){return get(name);} // if not found, goto parent name_table

    ptr_name getLocal(const string& name);

	// can only change local name_table
	void insert(string& name,ptr_name& val,bool alloc=true);
	void insert(string&& name,ptr_name& val,bool alloc=true){return insert(name,val,alloc);}

	void remove(string& name);
	void remove(string&& name){ return remove(name);}

	unsigned getAllocatedNumber() const{return allocated_number;}

	explicit CNameSpace(symbol_ptr& tree_node, ptrNamespace parent={});

private:
	// follows the order of declaration
	vector<string> declaration_list;

	// corresponding ast tree
	symbol_ptr tree_node;

	std::unordered_map<std::string ,ptr_name> name_table;

	// empty if it is root name space(that is, global namespace)
	ptrNamespace parentNamespace;

	unsigned allocated_number=0;

//    std::list<ptrCNamespace> subNamespaces;
};

using ptrCNamespace = std::shared_ptr<CNameSpace>;
using ptr_name=std::shared_ptr<CNameSpace::name_item>;

#endif //COMPILER_CNAMESPACE_H
