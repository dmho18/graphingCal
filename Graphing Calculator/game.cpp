#include "game.h"
#include "constants.h"
#include <iostream>
#include "function.h"
#include "ResourcePath.hpp"

using namespace std;
//#include "system.h"

string Round(string s)
{
    size_t pos = 0;
    string r= "";
    pos = s.find('.');
    r += s.substr(0, pos);
    r += s.substr(pos, pos+2);
    return r;
}


Game::Game():sidebar(WORK_PANEL, SIDE_BAR)

{

    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.
//    system = System();
    window.setFramerateLimit(60);

    mouseIn = true;
    mouseInSidebar = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);
    
//    graph.Init(sidebar);

    
    
//    graph.setSidebar(sidebar);
//    sidebar.printString();
//    sidebar = sidebar;

    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration

    if (!font.loadFromFile(resourcePath() + "sansation.ttf")){
        cout<<"Game() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Initial String for myTextLabel", font);
    myTextLabel.setCharacterSize(12);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setColor(sf::Color::Red);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-5));
    
    isEquation = false;
    input = false;
    sidebar.str(11) = "Press Enter to enter the equation";
//    sidebar.str(11) = "y = " + graph.equa();
//    sidebar.str(11) = "Enter your equation";
    
    
}

void Game::Draw(){
    //Look at the data and based on the data, draw shapes on window object.

    //draw the ball
//    system.Draw(window);

    //drawing the function and the graph
    if(isEquation){
        graph.Draw(window, sidebar, zoom, del);
    }
    else{
        sidebar.Load("side.txt", false);
    }

    //Two cross lines
    sf::RectangleShape horizontal(sf::Vector2f(0,0));
    horizontal.setPosition(0, ORIGIN_Y);
    horizontal.setSize(sf::Vector2f(WORK_PANEL,2));
    window.draw(horizontal);

    sf::RectangleShape vertical(sf::Vector2f(0,0));
    vertical.setPosition(ORIGIN_X, 0);
    vertical.setSize(sf::Vector2f(2,SCREEN_HEIGHT));
    window.draw(vertical);

    //red dot on the mouse
    if (mouseIn){
        window.draw(mousePoint);
    }

    sidebar.draw(window);
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

}

void Game::update(){
    //cause changes to the data for the next frame
    //stop the ball from moving
//    system.Step(command);



    command = 0;
    if (!mouseInSidebar){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                               sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        string s;
        s= "(" +
            Round(to_string((sf::Mouse::getPosition(window).x - ORIGIN_X)/zoom)) +
            ", " +
            Round(to_string((ORIGIN_Y - sf::Mouse::getPosition(window).y)/zoom)) +
            ")";

        //setting the position of the mouse
        sidebar.str(10) = s;
    
    }
    else{
        sidebar.str(10) = "";
    }


}
void Game::render(){
       window.clear();
       Draw();
       window.display();
}



void Game::processEvents()
{
   sf::Event event;
   float mouseX, mouseY;
   while (window.pollEvent(event))//or waitEvent
       {

       sf::Vector2i position = sf::Mouse::getPosition(window);

       // check the type of the event...
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               break;

           // key pressed
           case sf::Event::KeyPressed:
               switch(event.key.code){
                   case sf::Keyboard::Left:
                       command = 4;
                       break;
                   case sf::Keyboard::Right:
                       command = 6;
                       break;

                   case sf::Keyboard::Escape:
                       window.close();
                       break;

                   case sf::Keyboard::Z:
                       zoom = zoom*10;
                       cout<<"zoom in ~~~~~~"<<endl;
                       break;
                   case sf::Keyboard::D:
                       del = true;
                       cout<<"deleting"<<endl;
                       break;
                   case sf::Keyboard::O:
                       if(zoom > 1)
                           zoom = zoom/10;
                       cout<<"zoom out"<<endl;
                       break;
                   case sf::Keyboard::Enter:
                       if(input){   //already input
                           //call graph to evaluate the text
                           graph.setUpGraph(sidebar.str(11), sidebar);
                           input = false;
                           isEquation = true;
                       }
                       else{        //start accepting input
                           enter = true;
                           input = true;
                       }
                       break;
               }
                   break;

            case sf::Event::TextEntered:{
                if(input){      //start accepting words
                    if (enter){ //skip the enter key
                        enter = false;
                        sidebar.str(11) = "y = ";
                    }
                    else{
                        sf::String in;
                        in =event.text.unicode;
                        sidebar.str(11) += in.toAnsiString();
                    }
                }
            }
                   break;
            case sf::Event::MouseEntered:
                   mouseIn = true;
                   cout<<"mouse in"<<endl;
                   break;
            case sf::Event::MouseLeft:
                   mouseIn = false;
                   cout<<"mouse out"<<endl;
                   break;

           case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                MenuColors(sidebar, position);
                mouseInSidebar = sidebar.inSideBar(position);

                //Do something with it if you need to...
               break;
           case sf::Event::MouseButtonReleased:
                   if (event.mouseButton.button == sf::Mouse::Right)
                   {
//                       std::cout << "Right Button: (" << event.mouseButton.x << ", "
//                                        << event.mouseButton.y << ")"<<std::endl;

                   }
                   else{
                       for(int num = 0; num<10; num++){
                           if (sidebar.MouseInRectangle(position, num)){
                               cout<<"graph equation: "<<graph.equa()<<endl;
                               
                               graph.myqueue(sidebar.LoadQueue(num));
                               std::cout<<"left!!!!!"<<endl;
//                               sidebar.MenuColor(num) = sf::Color::Yellow;  //set white if mouse is in the box
                           }
                       }
//                       std::cout<<"left button?"<<std::endl;
                    }
                   break;

               default:
                   break;
           }
       }
}
void Game::run()
{
   while (window.isOpen())
   {
       processEvents();
       
       update();
       
       render(); //clear/draw/display
   }
}
void Game::ChangeView(){

}
bool Game::MouseInRectangle(sf::FloatRect r, sf::Vector2i mousePos){    //check if mouse is in the region of of bounding box (text, sprite1...)
    //because r.contains() won't take vector2i, I change it to vector2f
    sf::Vector2f point;
    point.x=mousePos.x;
    point.y=mousePos.y;
    //if the bounding box contains mouse position
    if(r.contains(point)){
        return true;
    }
    return false;
}
void Game::MenuColors(Sidebar &sidebar,sf::Vector2i mousePos){
    //x and y are mouse pos.
    //change color of text for the menu items to white or blue
    //  depending if the mouse pointer is in the respective box.

    //calls MouseInRectangle()
    for(int num = 0; num<10; num++){
        if (sidebar.MouseInRectangle(mousePos, num)){
            sidebar.MenuColor(num) = sf::Color::Yellow;  //set white if mouse is in the box
        }
        else{
            sidebar.MenuColor(num) = sf::Color::White;    //else set it to dark blue
    }
    }


}

