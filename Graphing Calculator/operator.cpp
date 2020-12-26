#include "operator.h"

op::op():token('o')
{
    precedence = 0;
}
op::op(string new_sign): token('o'), sign(new_sign){
    if((new_sign == "sin") || (new_sign == "cos") || (new_sign == "tan")){
        precedence = 3;
    }
    if(new_sign == "^"){
        precedence = 2;
    }
    if(new_sign == "+" || new_sign == "-")
        precedence = 0;
    if(new_sign == "*" || new_sign == "/")
        precedence = 1;
    if(new_sign == "(")
        precedence = 4;
    if(new_sign == ")")
        precedence = 5;
}
op::op(string new_sign, int new_pre):token('o'), sign(new_sign), precedence(new_pre){

}

void op::print(ostream &outs) const{

    outs<<sign;
}
string op::Sign(){
    return sign;
}
int op::Pre(){
    return this->precedence;
}
void op::set_paren(bool value){
    Is_Paren = value;
}
bool op::paren(){
    return Is_Paren;
}
