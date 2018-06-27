#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
using namespace std;


struct Coordinate{
    int x;
    int y;
};

class Move {

private:
    Coordinate start,stop;
    string color;
public:
    Move(){
        start;
        stop;
        color = "none";
    }
    Move(Coordinate start,Coordinate stop,string color){
        this->start = start;
        this->stop = stop;
        this -> color = color;
    }
    Coordinate getStartCoordinate(){
        return this->start;
    }
    Coordinate getStopCoordinate(){
        return this->stop;
    }
    string getColor(){
        return this->color;
    }
    
    void setStartCoordinate(Coordinate start){
        this -> start = start;
    }
    
    void setStopCoordinate(Coordinate stop){
        this -> stop = stop;
    }
    
    void setColor(string color){
        this -> color = color;
    }
    
    void display(){
        cout<<"start: x= "<<start.x<<" y= "<<start.y<<endl;
        cout<<"stop: x= "<<stop.x<<" y= "<<stop.y<<endl;
    }
};

/*
main(){
    
    vector<Move*> moves;
    
    Move *ruch = new Move();
    
    parse("partia_testowa.txt",&moves);
    
    for(int i=0;i<moves.size();i++){
        moves[i]->display();
        delete moves[i];
    }
    
    
    
    delete ruch;
   
}*/
