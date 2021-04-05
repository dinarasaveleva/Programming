import math
import copy

class Point: 
    def __init__(self, a1 = 0, a2 = 0, coord_system = "Cartesian"):
        if type(a1) == str:
            self.PrvCoords = "Cartesian"
            StrX = ""
            StrY = ""
            skobka = a1.index('(')
            dot = a1.index(',')
            skobka_obr = a1.index(')')

            for i in range((skobka+1), dot-1):
                StrX += a1[i]
            for i in range((dot+1), skobka_obr-1):
                StrY += a1[i]
            self.x = float(StrX)
            self.y = float(StrY)
        elif type(a1) == float or type(a1) == int:
            if coord_system == "Cartesian":
                self.PrvCoords = "Cartesian"
                self.x = float(a1)
                self.y = float(a2)
            elif coord_system == "Polar":
                self.PrvCoords = "Polar"
                self.x = float(a1)
                self.y = float(a2)

    def __eq__(self, point):
        if (round(point.get_x(), 10) == round(point.get_x(), 10)) and (round(point.get_y(), 10) == round(point.get_y(), 10)):
            return True
        else:
            return False

    def get_x(self):
        if self.PrvCoords == "Polar":
            x2 = self.x * math.cos(self.y)
        else:
            return self.x
        return x2
        
    def get_y(self):
        if self.PrvCoords == "Polar":
            y2 = self.x * math.sin(self.y)
        else:
            return self.y
        return y2

    def get_r(self):
        if self.PrvCoords == "Cartesian":
            if (self.x != 0) and (self.y != 0): x2 = math.sqrt(pow(self.x, 2) + pow(self.y, 2))
            elif self.x == 0: x2 = self.y
            elif self.y == 0: x2 = self.x
        else:
            return self.x
        return x2

    def get_phi(self):
        if self.PrvCoords == "Cartesian":
            if self.x > 0:
                y2 =  math.atan(self.y / self.x)
            elif (self.x < 0) and (self.y > 0):
                y2 =  math.atan(self.y / self.x) + math.pi
            elif (self.x < 0) and (self.y < 0):
                y2 =  math.atan(self.y / self.x) - math.pi
            elif (self.x == 0) and (self.y > 0):
                y2 =  math.pi/2
            elif (self.x == 0) and (self.y < 0):
                y2 =  math.pi/2
            else:
                y2 =  0
        else:
            return self.y
        return y2

    def set_x(self, x2):
        if self.PrvCoords == "Polar":
            if (self.x == 0) and (self.y == 0):
                self.x = x2
                self.PrvCoords = "Polar"
            else:
                self.set_r(x2)
        else:
            self.x = x2
            
    def set_y(self, y2):
        if self.PrvCoords == "Polar":
            if (self.x == 0) and (self.y == 0):
                self.y = y2
                self.PrvCoords = "Cartesian"
            else:
                self.set_phi(y2)
        else:
            self.y = y2

    def set_r(self, x2):
        if self.PrvCoords == "Cartesian":
            self.PrvCoords = "Polar"
            temp = self.get_phi()
            self.x = x2
            self.y = temp
        else:
            self.x = x2
            
    def set_phi(self, y2):
        if self.PrvCoords == "Cartesian":
            if (self.x == 0) and (self.y == 0):
                self.y = y2
                self.PrvCoords = "Polar"
            else:
                self.y = self.get_r() * math.sin(y2)
                self.x = self.get_r() * math.cos(y2)
        else:
            self.y = y2
            
    def __str__(self):
        return "({},{})".format(self.get_x(), self.get_y())
        
    def __repr__(self):
        return "({},{})".format(self.get_x(), self.get_y())
    
with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]
  
simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180*math.pi/180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)
  
print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')