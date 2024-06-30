
#ifndef VIEW_HPP
#define VIEW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>




//ENCAPSULATE POINT AND TRIANGLE WITHIN POLYGON INSTEAD OF INHERITANCE

class Polygon {
    struct Point {
        GLdouble x, y, z;
    };
    struct Triangle {
        Point a, b, c;
    };
    Triangle triList[];
    
public:
    Polygon();
    void rotate(GLdouble dx, GLdouble dy, GLdouble dz);

};

#endif