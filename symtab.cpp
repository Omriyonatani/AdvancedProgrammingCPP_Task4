#include "symtab.h"
#include "scanner.h"

Attributes& Symbol_table::get(string name){
    if(is_declared(name)){
        return sym_tab.at(name);
    }
}

void Symbol_table::set(string name, double nv){
    if(is_declared(name)){
        sym_tab.at(name).value=nv;
    }
}

bool Symbol_table::is_declared(string name){
    if(sym_tab.find(name) == sym_tab.end()){
        return false;
    }
    return true;
}

void Symbol_table::declare(string name, double nv, bool ic){
    sym_tab.emplace(name, Attributes(nv,ic));
}
