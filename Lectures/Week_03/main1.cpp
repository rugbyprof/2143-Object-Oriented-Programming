#include <iostream>
// #include <fstream> 
#include <vector>

using namespace std;


class Point{
    int x;
    int y;
public:
    Point():x(0),y(0){}
    Point(int x,int y):x(x),y(y){}
    friend ostream& operator<<(ostream& banana,const Point& p){
        return banana<<"["<<p.x<<","<<p.y<<"]";
    }
    Point operator+(const Point &rhs){
        return Point(x+rhs.x,y+rhs.y);
    }
    Point operator-(const Point &rhs){
        return Point(x-rhs.x,y-rhs.y);
    }
};

int main(){
    int x,y;

    vector<Point> pointv;

    // Point p1(6,9);
    // Point p2(8,3);

    while(cin>>x>>y){
        cout<<x<<" "<<y<<endl;
        pointv.push_back(Point(x,y));
    }

    cout<<pointv.size()<<endl;


    // p1 = p1 + p2;

    // Point p3 = p2 - p2;

    // cout<<p1<<endl;
    // cout<<p3<<endl;

    return 0;
}