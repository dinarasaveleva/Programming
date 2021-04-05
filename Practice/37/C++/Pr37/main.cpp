#include <iostream>
#include <cmath>

using namespace std;

enum CoordSys: int {
    Cartesian,
    Polar
};

class Point {
private:

    double x, y;
    CoordSys PrvCoords;

public:
    Point(int a1 = 0, int a2 = 0, CoordSys coord_system = CoordSys::Cartesian): x(a1), y(a2), PrvCoords(coord_system){}

    double get_x() {
        double x2;
        if (PrvCoords == CoordSys::Polar) {
            x2 = x * cos(y);
        }
        else {
            return x;
        }
        return x2;
    }
    double get_y() {
        double y2;
        if (PrvCoords == CoordSys::Polar) {
            y2 = x * sin(y);
        }
        else {
            return y;
        }
        return y2;
    }

    double get_r() {
        double x2;
        if (PrvCoords == CoordSys::Cartesian) {
            if (x != 0 && y != 0) x2 = sqrt(pow(x, 2) + pow(y, 2));
            else if (x == 0) x2 = y;
            else if (y == 0) x2 = x;
        }
        else {
            return x;
        }
        return x2;
    }
    double get_phi() {
        double y2;
        if (PrvCoords == CoordSys::Cartesian) {
            if (x > 0){
                y2 =  atan(y / x);
            }
            else if (x < 0 && y > 0){
                y2 =  atan(y / x) + M_PI;
            }
            else if (x < 0 && y < 0){
                y2 =  atan(y / x) - M_PI;
            }
            else if (x == 0 && y > 0){
                y2 =  M_PI/2;
            }
            else if (x == 0 && y < 0){
                y2 =  M_PI/2;
            }
            else{
                y2 =  0;
            }
        }
        else {
            return y;
        }
        return y2;
    }

    void set_x(double x2) {
        if (PrvCoords == CoordSys::Polar) {
            if (x == 0 && y == 0){
                x = x2;
                PrvCoords = CoordSys::Polar;
            }
            else{
                set_r(x2);
            }
        }
        else {
            x = x2;
        }
    }
    void set_y(double y2) {
        if (PrvCoords == CoordSys::Polar) {
            if (x == 0 && y == 0){
                y = y2;
                PrvCoords = CoordSys::Cartesian;
            }
            else{
                set_phi(y2);
            }
        }
        else {
            y = y2;
        }
    }

    void set_r(double x2) {
        if (PrvCoords == CoordSys::Cartesian) {
            PrvCoords = CoordSys::Polar;
            double temp = get_phi();
            x = x2;
            y = temp;
        }
        else {
            x = x2;
        }
    }
    void set_phi(double y2) {
        if (PrvCoords == CoordSys::Cartesian) {
            if (x == 0 && y == 0){
                y = y2;
                PrvCoords = CoordSys::Polar;
            }
            else{
                y = get_r() * sin(y2);
                x = get_r() * cos(y2);

            }
        }
        else {
            y = y2;
        }

    }

    friend bool operator== (Point& a, Point& b);
    friend bool operator!= (Point& a, Point& b);
    friend std::ostream& operator<< (std::ostream& out, Point& a);
    friend std::istream& operator>> (std::istream& in, Point& a);

};

bool operator== (Point& a, Point& b) {
    if ((round(a.get_x() * 10000000000) / 10000000000) == (round(b.get_x() * 10000000000) / 10000000000) && (round(a.get_y() * 10000000000) / 10000000000) == (round(b.get_y() * 10000000000) / 10000000000)) {
        return 1;
    }
    else{
        return 0;
    }
}
bool operator!= (Point& a, Point& b) {
    if ((round(a.get_x() * 10000000000) / 10000000000) != (round(b.get_x() * 10000000000) / 10000000000) && (round(a.get_y() * 10000000000) / 10000000000) != (round(b.get_y() * 10000000000) / 10000000000)) {
        return 1;
    }
    else{
        return 0;
    }
}

std::ostream& operator<< (std::ostream& out, Point& a) {
    out << "(" << a.get_x() << "," << a.get_y() << ")\n";
    return out;
}
std::istream& operator>> (std::istream& in, Point& a) {
    double x, y;
    std::string Str, StrY="", StrX="";
    in >> Str;

    int skobka = Str.find('(');
    int dot = Str.find(',');
    int skobka_obr = Str.find(')');

    for (int i = skobka+1; i < dot; i++){
        StrX += Str[i];
    }
    for (int i = dot+1; i < skobka_obr; i++){
        StrY += Str[i];
    }

    x = atoi(StrX.c_str());
    y = atoi(StrY.c_str());

    a.set_x(x);
    a.set_y(y);

    return in;
}

class Vector{
private:
    double x, y;
public:
    Vector(){
        x = 1;
        y = 0;
    }

    Vector(Point end){
        x = end.get_x();
        y = end.get_y();
    }

    Vector(Point begin, Point end){
        x = end.get_x()-begin.get_x();
        y = end.get_y()-begin.get_y();
    }

    double length(){
        double len = sqrt(x * x + y * y);
        return len;
    }

    friend bool operator== (const Vector& a, const Vector& b);
    friend Vector operator*(const Vector& a1, const double a2);
    friend double operator*(const Vector& a1, const Vector& a2);
    friend Vector operator-(const Vector& a1);
    friend Vector operator-(const Vector& a1, const Vector& a2);
    friend Vector operator+(const Vector& a1, const Vector& a2);

};

bool operator==(const Vector& a, const Vector& b) {
    if (((round(a.x * 10000000000) / 10000000000) == (round(b.x * 10000000000) / 10000000000)) && ((round(a.y * 10000000000) / 10000000000) == (round(b.y * 10000000000) / 10000000000))) {
        return true;
    }
    else{
        return false;
    }
}

Vector operator-(const Vector& a1){
    Vector deployed;
    deployed.x = -a1.x;
    deployed.y = -a1.y;
    return deployed;
}

Vector operator-(const Vector& a1, const Vector& a2){
    Vector counted;
    counted.x = a1.x - a2.x;
    counted.y = a1.y - a2.y;
    return counted;
}

Vector operator+(const Vector& a1, const Vector& a2){
    Vector counted;
    counted.x = a1.x + a2.x;
    counted.y = a1.y + a2.y;
    return counted;
}

Vector operator*(const Vector& a1, const double a2){
    Vector counted;
    counted.x = a1.x * a2;
    counted.y = a1.y * a2;
    return counted;
}

double operator*(const Vector& a1, const Vector& a2){
    return (a1.x * a2.x) + (a1.y * a2.y);
}

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox*ox, sqr(ox.length())) &&
        equal(oy*oy, sqr(oy.length())) &&
        equal((ox*3 + oy*4)*(ox*3 + oy*4), sqr((ox*3 + oy*4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";

}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}
