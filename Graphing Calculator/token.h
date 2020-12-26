#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
using namespace std;
class token
{
public:
    token();
    token(char newface);
    virtual void print(ostream& outs) const; //print without the printMe, otherwise it will not call the child function
    friend ostream& operator <<(ostream& outs, const token* printMe);
    friend ostream& operator <<(ostream& outs, const token& printMe);
    friend istream& operator >>(istream& ins, const token* getMe);
    char Face();

private:
    char face;
};

#endif // TOKEN_H

