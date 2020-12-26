#ifndef NUMBER_H
#define NUMBER_H
#include "token.h"

class number: public token
{
public:
    number();
    number(double new_val);
    void print(ostream &outs)const;// every arguments have to be the same with parent
    double Value();
private:
    double value;
};

#endif // NUMBER_H
