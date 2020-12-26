////
////  system.cpp
////  Graphing Calculator
////
////  Created by Danh Ho on 12/19/20.
////  Copyright © 2020 Danh Ho. All rights reserved.
////
//
//#include <stdio.h>
//
//#include "system.h"
//#include "random.h"
//#include "time.h"
//#include "cmath"
//#include <iostream>
//
//#include <constants.h>
//
//System::System()
//{
//
//    x_axis=sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH*4/5, 5));
//    x_axis.setPosition(sf::Vector2f(0, 400));
//    x_axis.setFillColor(sf::Color::Blue);
//
//    y_axis=sf::RectangleShape(sf::Vector2f(5, 800));
//    y_axis.setPosition(sf::Vector2f(560, 0));
//    y_axis.setFillColor(sf::Color::Blue);
//
//}
//
//
////------------------------------------------------------------------
////------------------------------------------------------------------
//
//void System::Step(string function,double center_x,double center_y,double low,double high,bool polar,double zoomin){
//
//    _center_x=center_x;
//    _center_y=center_y;
//
//    zoominsize=zoomin;
//    _polar=polar;
//    while(!_screen_circle.empty())
//    {
//        _screen_circle.pop_back();
//    }
//    _function=function;
//    _low=low;
//    _high=high;
//    x_axis=sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH*4/5, 5));
//    x_axis.setPosition(sf::Vector2f(0, _center_y));
//    x_axis.setFillColor(sf::Color::Blue);
//
//    y_axis=sf::RectangleShape(sf::Vector2f(5, 800));
//    y_axis.setPosition(sf::Vector2f(center_x, 0));
//    y_axis.setFillColor(sf::Color::Blue);
//
//    _increment=(abs(low)+abs(high))/_numberofdot;
//     _size=SCREEN_WIDTH*4/5/(abs(low)+abs(high));
//     try {
//         _points = PlotExpression(_function,_low,_high,_increment);
//     } catch (...) {
//         cout<<"invalid input"<<endl;
//
//     }
//
//      while(!_points.empty())
//      {
////          Point* p=_points.pop();
////          _screen_circle.push_back(new Circle(p->getX(),p->getY()));
//      }
//}
//
//
//void System::Draw(sf::RenderWindow& window){
////    window.clear();
//   // window.draw(shape);
//    window.draw(x_axis);
//    window.draw(y_axis);
//
//   for(int i=0;i<_screen_circle.size();i++)
//   {
//       _screen_circle[i]->Draw(window);
//   }
//
//
//}
//
//
//Queue<Point*> System:: PlotExpression (string expression, double low, double high, double increments)
//{
//    Queue<Point*> _graph;
//    Evaluate a(expression);
//
//    double r,x,y;
//    for(double i = low; i< high; i+=increments)
//    {
//        if(_polar)
//        {
//            r=a.eval(i);
//            x=r*cos(i);
//            y=r*sin(i);
//           // _graph.push(new Point(x*zoominsize+_center_x,-y*zoominsize+_center_y));
//            _graph.push(new Point(x*_size+_center_x,-y*_size+_center_y));
//        }else
////            _graph.push(new Point(i*zoominsize+_center_x,
////                                  (_center_y-(a.eval(i))*zoominsize)
////                                  ));
//            _graph.push(new Point(i*_size+_center_x,
//                                  (_center_y-(a.eval(i))*_size)
//                                  ));
//    }
//    return _graph;
//}
