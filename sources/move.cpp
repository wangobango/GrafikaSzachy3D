#include "../headers/move.h"
#include <iostream>
using namespace std;

move::move(coordinate start, coordinate stop, std::string color ){
    this->start = start;
    this->stop = stop;
    this->color = color;
}

coordinate move::getStartCoordinate(){
    return this->start;
}
    
coordinate move::getStopCoordinate(){
    return this->stop;
}
    
string move::getColor(){
    return this->color;
}

void move::setStartCoordinate(coordinate start){
    this->start = start;
}
    
void move::setStopCoordinate(coordinate stop){
    this -> stop = stop;
}
    
void move::setColor(std::string color){
    this -> color = color;
}
    
void move::display(){
    cout<<"start: x= "<<start.x<<" y= "<<start.y<<endl;
    cout<<"stop: x= "<<stop.x<<" y= "<<stop.y<<endl;
}