
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.


#include <iostream>
#include "game.h"
//#include "MyVector.h"
//#include "random.h"
#include <fstream>
#include "function.h"
#include "constants.h"

using namespace std;

int main()
{


//    cout<<tan(PI*1/2)<<endl;
//    return 0;
//    Random r;
//    r.Seed();
//    Vector v;
    Game game;
    game.run();
    return 0;
}




//=================================this is previous one===========================


//#include "term.h"
//#include "linked_list_templated_functions.h"
//#include "poly.h"
//using namespace std;
//void test_add();
//void test_mul();
//void test_sub();
//void test_negate();
//void test_cin_cout();
//
//int main(int argc, char *argv[])
//{
//    cout << endl << endl<< "=====================" << endl << endl;
//
//
//    test_add();
//    test_mul();
//    test_sub();
//    test_cin_cout();
//
//
//
//    cout << endl << endl<< "=====================" << endl << endl;
//
//    return 0;
//}
//
//void test_add(){
//    double b[] = {3,5,2};
//    Poly p1(b,2);
//    double a[] = {5,0,4,2};
//    Poly p2(a,3);
//    cout<<"p1: "<<p1<<endl;
//    cout<<"p2: "<<p2<<endl;
//    cout<<"add: ";
//    cout<<p1+p2<<endl;
//}
//void test_mul(){
//    double b[] = {3,5,2};
//    Poly p1(b,2);
//    double a[] = {5,0,4,2};
//    Poly p2(a,3);
//    cout<<"multiply: ";
//    cout<<p1*p2<<endl;
//}
//void test_negate(){
//    double b[] = {3,5,2};
//    Poly p1(b,2);
//    cout<<p1<<endl;
//    p1 = -p1;
//    cout<<p1<<endl;
//
//}
//void test_sub(){
//    double b[] = {3,5,2};
//    Poly p1(b,2);
//    double a[] = {5,0,4,2};
//    Poly p2(a,3);
//    cout<<"subtract: ";
//
//    cout<<p1-p2<<endl;
//}
//void test_cin_cout(){
//    Poly p;
//    cout<<"p: ";
//    cin>>p;
//    cout<<p<<endl;
//}
