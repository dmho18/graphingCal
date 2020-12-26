#include "variable.h"

variable::variable():token('v')
{
   //left blank
}
variable::variable(string new_var): token('v'),var(new_var){
    //left blank
}
void variable::print(ostream &outs) const{
    outs<<var;
}
string variable::Var(){
    return var;
}
