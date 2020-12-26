
#include "token.h"
token::token(): face('\0')
{

}
token::token(char newface): face(newface)
{

}
void token::print(ostream &outs)const{
    outs<<"calling print in token ";
    outs<<face<<endl;
}
ostream& operator <<(ostream& outs, const token* printMe){
    if (printMe == NULL) {
        outs<<"is null"<<endl;
        return outs;
    }
//    std::cout<<printMe<<std::endl;
    printMe->print(outs); //because printMe is a pointer, it needs "->"
    return outs;
}
ostream& operator <<(ostream& outs, const token& printMe){
    printMe.print(outs);
//    outs<<printMe.Face()
    return outs;
}

char token::Face()
{
    return face;
}
istream& operator >>(istream& ins, const token* getMe){

}



//static_cast<child>(p)->c()
