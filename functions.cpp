#include <iostream>
#include "data_structures.h"
#include <stack>
#include <map>

using namespace std;

// these are added function for the file to compile
// DO NOT add them to the ypp file
void errorUndef(int lineno,string id){cout<< "errorUndef" <<endl;}
void errorUndefFunc(int lineno,string id){cout<< "errorUndefFunc" <<endl;}
void errorDef(int lineno,string id){cout<< "errorDef" <<endl;}
void errorMainMissing(){cout<< "errorMainMissing" <<endl;}


template<class input_class, class output_class>
void print_stack_of_maps(stack<map<input_class, output_class>> s) {
    stack<map<input_class, output_class>> *clone = new stack<map<input_class, output_class>>(s);
    while (!clone->empty()) {
        map<input_class, output_class> m = clone->top();
        clone->pop();
        cout << "[";
        for (const auto elem : m) {
            cout << "name: " << elem.first << ", value: " << elem.second.first << ", offset: " << elem.second.first
                 << endl;
        }
        cout << "]" << endl;
    }
    delete (clone);
}


bool name_exists_in_table(string *name,const stack<map<string, pair<int, int>>> &tables){
    /*
     * this function will get a pointer to a string representing a name and a stack of tables
     * the function will return true if the name is already in the tables and false otherwise
     */
    stack<map<string, pair<int, int>>> *tabels_clone = new stack<map<string, pair<int, int>>>(tables);
    while (!tabels_clone->empty()) {
        auto table = tabels_clone->top();
        tabels_clone->pop();
        // in c++11 table.contains doesnt exist yet, so to find if the key
        // exists in the table, we search an iterator, and if we got to the end
        // of the table, that means the value is not there
        if (table.find(*name) != table.end()) {
            // if reached here, that means the key already is in some table
            delete tabels_clone;
            return true;
        }
    }

    delete tabels_clone;
    return false;
}

bool legal_deceleration(string *name, stack<map<string, pair<int, int>>> &tables,int lineno) {
    /*
     * this function will return false if the declaration is illegal and tru of it's legal.
     * this function will also handle the calling of the error functions
     *
     * lineo = the line number for error handling functions
     */
    bool is_name_defined = name_exists_in_table(name,tables);
    if(is_name_defined){
        errorDef(lineno,*name);
    }
    // we return the opposite of is_name_defined because if the name already exists the definition is illegal
    return !is_name_defined;
}

enum Addressing {FUNC,VAR,MAIN} ;

bool legal_addressing(string *name, stack<map<string, pair<int, int>>> &tables,int lineno,Addressing addressing_type){
    /*
     * this function will handle addressing to the symbol table, and the errors that will accrue if addressing
     * a symbol that dos'ent exists yet
     *
     * lineo = the line number for error handling functions
     * addressing_type = addressing a variable or a function, used for calling the right function
     * possible values for addressing_type are VAL , FUNC or MAIN
     * send MAIN if the addressing is for a function that is named "main" AND also it's return type is void
     *
     */
    //TODO: remove this assert
    // if addressing_type is main it means that the called function is void main
    // the function should be called with addressing_type = main only if the function name is main
    // the function string.compare compares 2 strings and returns 0 if they are equal
    assert(name->compare("main")==0);

    //TODO: add check if the type of the function main (if it exists in the table is void)


    bool is_name_defined = name_exists_in_table(name,tables);
    if(!is_name_defined){
        switch(addressing_type) {

            case VAR : {
                errorUndef(lineno, *name);
                break;
            }
            case FUNC: {
                errorUndefFunc(lineno, *name);
                break;
            }
            case MAIN: {
                errorMainMissing();
                break;
            }

        }
    }

    return is_name_defined;
}

int main() {
    stack<map<string, pair<int, int>>> s;
    map<string, pair<int, int>> map;
    for (int i = 0; i < 10; i++) {
        map.insert({to_string(i), pair<int, int>(i, i)});
    }
    s.push(map);
    string *name = new string("ig");
    Addressing addressing_type = MAIN;
    bool leagal = legal_addressing(name,s,0,addressing_type);
    cout << boolalpha << "is \"" << *name << "\" a right addressing ? " << leagal << endl;
    leagal = legal_deceleration(name,s,0);
    cout << boolalpha << "is \"" << *name << "\" a legal deceleration ? " << leagal << endl;
    print_stack_of_maps(s);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


