#ifndef __UTILS_HW3__
#define __UTILS_HW3__


#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Node{};
struct Expression: public Node{
   string id_name;
   string type;
   bool bool_value;
   int number;
   string str;
   string op;
   Expression() : id_name{""}, type{""}, bool_value{false}, number{0}, str{""}, op{""} {}
   // Expression(string* type): type{type} {}
   // Expression(bool bool_value): bool_value{bool_value} {}
   // Expression(int number): number{number} {}
   // Expression(string* str): str{str} {}
   // Expression(string* op): op{op} {}
};
#define YYSTYPE Expression*
typedef struct Expression Expression;

#endif