#include <iostream>
#include <climits>

using namespace std;

class Point{
private:
    int X;
    int Y;
public:
    Point();            // required
    Point(int,int);     // optional to set x,y when a point is created

    // General Instructions said to include Setters and Getters
    void setX(int);     // required setter
    void setY(int);     // required setter
    void setXY(int,int);// optional setter

    int getX();         // required getter
    int getY();         // required getter

};

Point::Point(){
  X=0;
  Y=0;
}

Point::Point(int x,int y){
  X = x;
  Y = y;
}

int Point::getX(){
  return X;
}

int Point::getY(){
  return Y;
}

void Point::setXY(int x,int y){
  X = x;
  Y = y;
}


class Line{
private:
    Point Start;            // required
    Point End;              // required

public:
    Line(int,int,int,int);  // required
    Line(Point,Point);      // required
    double length();        // required

    // General Instructions said to include Setters and Getters

    void setStart(Point);   // one of these setters required
    void setStart(int,int);  

    void setEnd(Point);     // one of these setters required
    void setEnd(int,int);   

    Point getStart();       // getter
    Point getEnd();         // getter

};

Line::Line(int x1, int y1, int x2, int y2){
  Start.setXY(x1,y1);
  End.setXY(x2,y2);
}

Line::Line(Point p1, Point p2){

}

Point Line::getStart(){
  return Start;
}

Point Line::getEnd(){
  return End;
}

double Line::length(){
  return 0.0;
}

class Polygon{
private:
    Line *poly;                     // required data member
                                    // to hold sides (lines)

    int numSides;                   // size of array of lines

public:
    Polygon();                      // required constructor
    Polygon(Point*,int);            // required constructor
    Polygon(Line*,int);             // required constructor
    double perimeter();             // required method
    double bboxArea();              // required method   

    // General Instructions said to include Setters and Getters

    void setLines(Line*,int);      // setter
    Line* getLines();               // getter
};

Polygon::Polygon(){

}

Polygon::Polygon(Point*,int num_points){
  
}
Polygon::Polygon(Line*, int num_lines){
  
}

void Polygon::setLines(Line* lines,int num_lines){

}

Line* Polygon::getLines(){
  Line* L;

  return L;
}

double Polygon::perimeter(){
    double sum = 0.0;
    for(int i=0 ; i <numSides ; i++){
        sum += poly[i].length();
    }
    return sum;
}

double Polygon::bboxArea(){
    // Init Min Max vars to be compared to
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    // Vars to hold each points values
    int x1,y1,x2,y2;
    // Vars to hold points pulled from a line in the polygon
    Point S,E;


    for (int i=0 ; i < numSides ; i++){
        S = poly[i].getStart();
        E = poly[i].getEnd();
        x1 = S.getX();
        y1 = S.getY();
        x2 = E.getX();
        y2 = E.getY();
        if(x1>maxX) maxX = x1;
        if(y1>maxY) maxY = y1;
        if(x1<minX) minX = x1;
        if(y1<minY) minY = y1;
        if(x2>maxX) maxX = x2;
        if(y2>maxY) maxY = y2;
        if(x2<minX) minX = x2;
        if(y2<minY) minY = y2;       
    }

    // Lines to be used to calculate the area (width x height)
    Line Width(Point(minX,minY),Point(maxX,minY));
    Line Height(Point(minX,minY),Point(minX,maxY));

    return Width.length() * Height.length();
}

int main(){

  return 0;
}
