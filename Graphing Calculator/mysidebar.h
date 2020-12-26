#ifndef MYSIDEBAR_H
#define MYSIDEBAR_H
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include <string>
#include "queue_class.h"
#include "token.h"
#include <sstream>
#include "number.h"
#include "operator.h"
#include "variable.h"
using namespace std;
class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    bool MouseInRectangle(sf::Vector2i mousePos, int num);    //check if mouse is in the region of of bounding box (text, sprite1...)
    bool inSideBar(sf::Vector2i mousePos);
    void printString();

    sf::Color& MenuColor(int i);
    string& str(int i);
    void Load(char fileName[], bool del);
    void Save(char fileName[], bool del, string equation);
    Queue<token *> LoadQueue(int numbr);

private:
    sf::RectangleShape rect;
    sf::RectangleShape input;
    Queue<token *> result;
    float _left;
    float _width;
    sf::Text menu[12];
    sf::Color color[10];
    sf::Font font;
    string s[12];

};
fstream& GotoLine(fstream& infile, int num);
#endif // MYSIDEBAR_H
