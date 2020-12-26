#include "mysidebar.h"
#include <fstream>
#include <iomanip>
#include "ResourcePath.hpp"
#include <string>
#include <algorithm>
#include <wchar.h>

Sidebar::Sidebar()
{

}
Sidebar::Sidebar(float left, float width):_left(left), _width(width)
{
    sf::Color blue = sf::Color(51, 54, 82);
    rect.setFillColor(blue); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    for (int i= 0; i<12; i++){
        s[i] = "";
    }


}
void Sidebar::draw(sf::RenderWindow& window){
//    window.clear();       //no clear or won't draw anything
    window.draw(rect);

//    printString();

    //position text
    menu[10].setFont(font);
    if (true){       //mouse is in the main work panel
        menu[10].setString(s[10]);
    }
    else{
        menu[10].setString("(0, 0)");
    }
    menu[10].setCharacterSize(20u);
    menu[10].setColor(sf::Color::White);
    int mid = WORK_PANEL + SIDE_BAR/2;
    int w_mid = menu[10].getGlobalBounds().width/2;
    
    menu[10].setPosition(sf::Vector2f(mid-w_mid,30));
    window.draw(menu[10]);

    //function text
    menu[11].setFont(font);
    menu[11].setString(s[11]);
    menu[11].setCharacterSize(20u);
    menu[11].setColor(sf::Color::Yellow);
    w_mid = menu[11].getGlobalBounds().width/2;
    menu[11].setPosition(sf::Vector2f(mid-w_mid,80));
    window.draw(menu[11]);

    int inc = 10;

    //menu text
    for(int i = 0; i < 10; i++ ){
//        color[i] = sf::Color::White;
//        s[i] = "danhe";
//        cout<<i<<", "<<s[i]<<endl;
        menu[i].setFont(font);
        menu[i].setString(s[i]);
        menu[i].setColor(color[i]);
        
        w_mid = menu[i].getGlobalBounds().width/2;
        menu[i].setPosition(sf::Vector2f(mid-w_mid, 200 + inc));   //set position
        menu[i].setCharacterSize(20u);
        inc = inc + 50;
        window.draw(menu[i]);
    }

}
bool Sidebar::MouseInRectangle( sf::Vector2i mousePos, int num){    //check if mouse is in the region of of bounding box (text, sprite1...)
    //because r.contains() won't take vector2i, I change it to vector2f
    sf::FloatRect r = menu[num].getGlobalBounds();

    sf::Vector2f point;

    point.x=mousePos.x;
    point.y=mousePos.y;

    //if the bounding box contains mouse position
    if(r.contains(point)){
        return true;
    }
    return false;
}
sf::Color& Sidebar::MenuColor(int i){
    return color[i];
}
string& Sidebar::str(int i){
    return s[i];
}

void Sidebar::Load(char fileName[], bool del){
    ifstream infile;
    infile.open(fileName);
    string func;
    if(infile.fail()){
        cout<<"could not open file...."<<endl;
        exit(0);
    }
    int i = 0;
//    cout<<"Printing from load"<<endl;
    while(getline(infile, func) ){
//        getline(infile, func);  //don't skip white space;
        s[i] = func;
//        cout<<i<<": "<<s[i]<<endl;
        i++;
        if(i == 10) break;
//        infile.clear();
//        infile.ignore();  //just comment this
    }
    infile.close();
    if(del == true){
        for(int i = 0; i<10; i++){
            s[i] = "";
        }
    }

}
Queue<token *> Sidebar::LoadQueue(int numbr){
    Queue<token*> queue;
    string temp = s[numbr];
    string equation = "";
    string str;   // first char
    string o;   // another char
    string r;   // result string
    bool done = false;
    double num = 0; //the number
    stringstream ss_str;    //string stream for string
    stringstream ss_num;    //string stream for number
    stringstream ss;        //regular string stream
    int i = 0;
    int end = temp.size();
    str = temp[i];
    i++;
    int space = 0;
    equation = equation + str;
    while(!done){
        o = temp[i];
        if(o != " " ){
            equation = equation + o;
        }
        if(o == " "){
            space++;
            ss<<str;
            ss>>num;
            if(!ss.fail()){
                ss_num<<str;
                ss_num>>num;
                ss_num.str("");
                ss_num.clear();
                queue.EnQ(new number(num));

            }
            else{
                ss_str<<str;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else if(r == "e")
                    queue.EnQ(new number(E));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            str = " ";
        }
        if(i >= end ){
            ss<<str;
            ss>>num;
            if(!ss.fail()){
                ss_num<<str;
                ss_num>>num;
                queue.EnQ(new number(num));
                ss_num.str("");
                ss_num.clear();

            }
            else{
                ss_str<<str;
                ss_str>>r;
                if(r == "x")
                    queue.EnQ(new variable(r));
                else
                    queue.EnQ(new op(r));
                ss_str.str("");
                ss_str.clear();
            }
            ss.str("");
            ss.clear();
            str = " ";
            done = true;            //stop everything when "return" found
         }
        str = str + o;  //concantenate
        i++;
    }
//    equation = str;
    cout<<" temp: "<<temp<<endl;
    temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
    s[11] = "y = " + temp;
//    cout<<"queue day~~~~ "<<queue<<endl;
    return queue;
}
fstream& GotoLine(fstream& infile, int num){    //go to a specific line in a txt file
    infile.seekg(ios::beg);
    for(int i=0; i < num-1; i++){
        infile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return infile;
}

bool Sidebar::inSideBar(sf::Vector2i mousePos){
    return rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void addString(string a[], string equation){

    for(int i=0;i<9;i++){
//        cout<<"spot "<<i<<": "<<endl;
//        cout <<"previous: "<<a[i]<<endl;
        a[i]=a[i+1];
//        cout <<"after: "<<a[i]<<endl;
    }
    a[9] = equation;

//    cout<<"finish product: "<<endl;
//    for(int i = 0; i<10; i++){
//        cout<<i<<": "<<a[i]<<endl;
//    }
}

void Sidebar::Save(char fileName[], bool del, string equation){
    

    Load(fileName, false);
    ofstream outfile;

    outfile.open(fileName);    //append at the end
//    outfile.open(fileName, outfile);    //append at the end

    if(outfile.fail()){
        cout<<"couldn't open input file....."<<endl;
        exit(0);
    }
    
    if(del){        //delete the file and recreate it
        return;
    }
    bool added = false;
    if (s[9] != ""){   //check if every spot is taken
//        cout<<"no more empty spot"<<endl;
        addString(s, equation);
        for (int i= 0; i<10; i++){
            outfile<<s[i]<<endl;
        }
    }
    else{                   //there is spot available
//        cout<<"there are empty spot"<<endl;
        for (int i=0; i<10; i++){
            if(s[i] != ""){      //ocupied spot
                outfile<<s[i]<<endl;
//                cout<<"adding to file "<<s[i]<<endl;
            }
            else{
                if (added){
                    outfile<<""<<endl;
//                    cout<<"adding to file empty"<<endl;
                    continue;
                }

                added = true;
                s[i] = equation;        //find an emppty spot
//                cout<<i<<", "<<s[i]<<endl;
                outfile<<s[i]<<endl;
//                cout<<"adding to file 2: "<<s[i]<<endl;
            }
            
        }
    }
//    cout<<"equation : "<<equation<<endl;
//    equation += "\n";

    outfile.close();
    
    Load(fileName, false);

}
void Sidebar::printString(){
    for(int i = 0; i<10; i++){
        cout<<s[i]<<endl;
    }
}
