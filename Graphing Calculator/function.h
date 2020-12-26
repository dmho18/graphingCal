#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include "queue_class.h"
#include "stack_class.h"
#include "token.h"
#include "number.h"
#include "operator.h"
#include "variable.h"
#include <sstream>
#include <math.h>
#include "mysidebar.h"
#include <fstream>
#include "mysidebar.h"
#include <SFML/Graphics.hpp>

using namespace std;

class func
{

public :
    func();
    void setSidebar(Sidebar& sidebar);
    void Init(Sidebar& sidebar);
    void Draw(sf::RenderWindow &window, Sidebar &sidebar, double zoom, bool del);
    void myqueue(Queue<token *> temp);
    string& myequation();
    string equa();
    void Input(Queue<token*> &queue, string &equation, Sidebar& sidebar);
    void setUpGraph(string s, Sidebar& sidebar);
    

private:
    Sidebar sidebar;
    Queue<token*> queue;
    Queue<token*> result;
    string equation;
    double min = -WORK_PANEL/2;  //for x coor
    double max = WORK_PANEL/2;
    string fileName;
};

void Save(char fileName[], string equation);
void Load(char fileName[], Sidebar &sidebar, bool del);
void Save(char fileName[]); // Save can't be in draw

double RPN(Queue<token*> input, double value);
void ShuntingYard(Queue<token *> input, Queue<token *> &result);
void ErrorMesg();
double combine(double a, double b);
void BuildQueue(Queue<token*> &queue);

#endif // FUNCTION_H
