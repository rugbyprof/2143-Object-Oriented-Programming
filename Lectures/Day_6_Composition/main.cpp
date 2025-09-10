#include <iostream>
#include <vector>

using namespace std;

//definition
class Point{
private:
    int x;
    int y;
public:
    Point():x(0),y(0){}
    Point(int x,int y):x(x),y(x){}
    friend ostream& operator<<(ostream& pout,const Point& p){
        return pout<<"["<<p.x<<","<<p.y<<"]";
    }
};

class Line{
private:
    Point p1;
    Point p2;
public:
    Line():p1(Point()),p2(Point()){}
    Line(Point p1,Point p2):p1(p1),p2(p2){}
    friend ostream& operator<<(ostream& lout,const Line& ln){
        return lout<<"["<<ln.p1<<","<<ln.p2<<"]";
    }
};

class Poly{
private:
    vector<Line> lines;
public:
    Poly() : lines() {}  // or just Poly() = default;
    Poly(const std::vector<Line>& lines) : lines(lines) {}
    friend ostream& operator<<(ostream& pout,const Poly& poly){
        // vector<Line> lines = poly.lines;
        pout<<"["<<endl;
        for (const auto& line : poly.lines) {
            pout << line << " ";
        }
        pout<<"]";
        return pout;
    }
};

// class Poly {
// private:
//     std::vector<Line> lines;

// public:
//     // Default constructor (creates empty Poly)
//     Poly() : lines() {}  // or just Poly() = default;

//     // Constructor with vector of lines
//     Poly(const std::vector<Line>& lines) : lines(lines) {}

//     // Optional: move constructor
//     Poly(std::vector<Line>&& lines) : lines(std::move(lines)) {}

//     void print() const {
//         for (const auto& line : lines) {
//             std::cout << "Line from (" << line.start.x << ", " << line.start.y << ") to ("
//                       << line.end.x << ", " << line.end.y << ")\n";
//         }
//     }
// };

int main(){
    // instance / object
    Point p1(3,4);
    Point p2(6,6);

    vector<Line> lines;

    Line l1;
    Line l2(p1,p2);

    lines.push_back(l1);
    lines.push_back(l2);
    Poly po1(lines);
    cout<<endl;
    cout<<p1<<endl;
    cout<<p2<<endl;
    cout<<l1<<endl;
    cout<<l2<<endl;
    cout<<po1<<endl;


    return 0;
}