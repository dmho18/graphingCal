#ifndef VARIABLE_H
#define VARIABLE_H
#include "token.h"
#include <iostream>
#include <string>

class variable: public token
{
public:
    variable();
    variable(string new_var);
    void print(ostream &outs) const;
    string Var();
private:
    string var;

};

#endif // VARIABLE_H
