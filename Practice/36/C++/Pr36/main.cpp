#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

const auto PI = 3.141592653589793;

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

double round(double value, int count)
{
    double x = pow(10, count);
    return floor(value*x)/x;
}

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

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    } else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180*PI/180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
