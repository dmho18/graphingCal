#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"
#include <iostream>
#include <string>
using namespace std;
class op: public token
{
public:
    op();
    op(string new_sign);
    op(string new_sign, int new_pre);
    void print(ostream &outs)const;
    string Sign();
    int Pre();
    void set_paren(bool value);
    bool paren();
private:
    string sign;
    int precedence;
    bool Is_Paren;
};

#endif // OPERATOR_H
