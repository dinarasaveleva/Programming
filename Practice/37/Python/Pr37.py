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
    
class Vector:
    def __init__(self, begin = None, end = None):
        if (begin is None) and (end is None):
            self.x = 1
            self.y = 0
        elif (begin is not None) and (end is None):
            self.x = begin.get_x()
            self.y = begin.get_y()
        elif (begin is not None) and (end is not None):
            self.x = end.get_x()-begin.get_x()
            self.y = end.get_y()-begin.get_y()
    
    def __eq__(self, b):
        if (round(self.x, 10) == round(b.x, 10)) and (round(self.y, 10) == round(b.y, 10)):
            return 1
        else:
            return 0
    
    def __neg__(self):
        deployed = Vector()
        deployed.x = -self.x
        deployed.y = -self.y
        return deployed
    
    def __add__(self, b):
        counted = Vector()
        counted.x = self.x + b.x
        counted.y = self.y + b.y
        return counted
    
    def __sub__(self, b):
        counted = Vector()
        counted.x = self.x - b.x
        counted.y = self.y - b.y
        return counted
    
    def __mul__(self, b):
        if type(b) == Vector:
            return (self.x * b.x) + (self.y * b.y)
        elif (type(b) == int) or (type(b) == float):
            counted = Vector()
            counted.x = self.x * b
            counted.y = self.y * b
            return counted
    
    def length(self):
        return math.sqrt(pow(self.x,2)+pow(self.y,2))        



def equal(a, b, e=1E-10):
    if -e < a - b < e: return True
    else: return False
  
a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))
if a == b and b == a: print('Equality test passed')
else: print('Equality test failed')
  
na  = Vector(Point(-1, -2))
ox  = Vector(Point( 1,  0))
nox = Vector(Point(-1,  0))
oy  = Vector(Point( 0,  1))
noy = Vector(Point( 0, -1))
if a == -na and na == -a and -ox == nox and -oy == noy: print('Invert test passed')
else: print('Invert test failed')
  
if ox + oy + oy == a and -ox == -a + oy + oy: print('Summation test passed')
else: print('Summation test failed')
  
if -ox + oy == oy - ox and -oy + ox == ox - oy: print('Subtraction test passed')
else: print('Subtraction test failed')
  
if (ox * 3 == ox + ox + ox and
    oy * 3 == oy + oy + oy and
    ox * (-3) == -ox - ox - ox and
    oy * (-3) == -oy - oy - oy): print('Multiplication by number test passed')
else: print('Multiplication by number test failed')
  
if (equal(ox.length(), 1) and
    equal(oy.length(), 1) and
    equal((ox * 3 + oy * 4).length(), 5)): print('Length test passed')
else: print('Length test failed')
  
if (equal(ox*ox, ox.length()**2) and
    equal(oy*oy, oy.length()**2) and
    equal((ox*3 + oy*4)*(ox*3 + oy*4), (ox*3 + oy*4).length()**2)): print('Multiplication by Vector test passed')
else: print('Multiplication by Vector test failed')