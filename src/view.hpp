
#ifndef VIEW_HPP
#define VIEW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>

class Transformable {
public:
    virtual void rotate(GLdouble dx, GLdouble dy, GLdouble dz) = 0;
};

class Point : public Transformable {
    GLdouble x, y, z;
    void rotate(GLdouble dx, GLdouble dy, GLdouble dz) override;
};

class Triangle : public Transformable {
    Point a, b, c;
    void rotate(GLdouble dx, GLdouble dy, GLdouble dz) override;
};

class Polygon : public Transformable {
    //Start with static array for now
    Triangle triList[];
    void rotate(GLdouble dx, GLdouble dy, GLdouble dz) override;
};

#endif

//ENCAPSULATE POINT AND TRIANGLE WITHIN POLYGON INSTEAD OF INHERITANCE