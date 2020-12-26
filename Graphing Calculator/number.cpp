#include "number.h"

number::number():token('n'), value(0)
{

}
number::number(double new_val):token('n'), value(new_val)
{

}
void number::print(ostream& outs) const{
//    cout<<"calling print in number ";
    outs<<value;
}
double number::Value(){
    return value;
}
