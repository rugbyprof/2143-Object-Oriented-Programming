#include <iostream>
// #include <fstream> 
#include <vector>

using namespace std;

// copy constructor not needed for classes without pointers.

class Point{
    int x;
    int y;
public:
    Point():x(0),y(0){} // default constructor
    Point(int x,int y):x(x),y(y){} // overloaded constructor
    Point(const Point& p):x(p.x),y(p.y) {} // copy constructor
    friend ostream& operator<<(ostream& banana,const Point& p){
        return banana<<"["<<p.x<<","<<p.y<<"]";
    }
    Point operator+(const Point &rhs){
        return Point(x+rhs.x,y+rhs.y);
    }
    Point operator-(const Point &rhs){
        return Point(x-rhs.x,y-rhs.y);
    }
    // Setters & Getters
    void setX(int x){
        this->x = x;
    }
    void setY(int y){
        this->y = y;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
};


// void print_array(Point p[],int size){

// }

int main(){
    int x,y;

    vector<Point> pointv;

    Point p1(6,9);
    Point p2(8,3);

    Point p3 = p1+p2;

    Point p4(3,4);

    //Point p5 = (p1+p2+p3);
    Point p5 = p1;



    while(cin>>x>>y){
        cout<<x<<" "<<y<<endl;
        pointv.push_back(Point(x,y));
    }

    cout<<pointv.size()<<endl;
    cout<<pointv[67]<<endl;
    cout<<pointv[pointv.size()-1]<<endl;
    cout<<p3<<endl;
    cout<<p5<<endl;





    return 0;
}