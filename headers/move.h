#include<cstdlib>
#include<vector>
struct coordinate{
    int x;
    int y;
};

class move {
private:
    coordinate start,stop;
    std::string color;
public:
    move();
    move(coordinate start, coordinate stop, std::string color );
    
    coordinate getStartCoordinate();
    
    coordinate getStopCoordinate();
    
    std::string getColor();

    void setStartCoordinate(coordinate start);
    
    void setStopCoordinate(coordinate stop);
    
    void setColor(std::string color);
    
    void display();
};
