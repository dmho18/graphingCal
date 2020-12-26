#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "mysidebar.h"
#include "function.h"
class Game{
public:
    Game();
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();
    void ShowShapes();
    void ChangeView();
    bool MouseInRectangle(sf::FloatRect r, sf::Vector2i mosuePos);      //if mouse is inside the box contains the text
    void MenuColors(Sidebar &sidebar, sf::Vector2i mousePos);     //change menu color

private:
    sf::Text menu;
    sf::RenderWindow window;
    sf::CircleShape mousePoint;
    sf::RectangleShape sideBar;
    
    
//    System system;
    bool isEquation;
    bool input;
    bool enter;
    int command;
    sf::Font font;
    sf::Text myTextLabel;
    bool mouseIn;
    bool mouseInSidebar;
    Sidebar sidebar;
    func graph;          //function initialized here

    double zoom = 100;

    bool del = false;
};


#endif // GAME_H
