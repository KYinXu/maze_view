
#ifndef VIEW_HPP
#define VIEW_HPP
#define PI 3.1415926

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>




//ENCAPSULATE POINT AND TRIANGLE WITHIN POLYGON INSTEAD OF INHERITANCE
struct matrix4x4{
    GLdouble matrix[4][4] = {0};
};
class Polygon {
    bool visible;
    struct Point {
        GLdouble x, y, z;
        void rotate(GLdouble dx, GLdouble dy, GLdouble dz){
            GLdouble dx_R = dx / 180.0f * PI;
            GLdouble dy_R = dy / 180.0f * PI;
            GLdouble dz_R = dz / 180.0f * PI;

            const GLdouble oldx = x;
            const GLdouble oldy = y;

            //can combine these
			y = (cosf(dx_R) * oldy) - (sinf(dx_R) * z);
			z = (sinf(dx_R) * oldy) + (cosf(dx_R) * z);

            x = cosf(dy_R) * oldx + sinf(dy_R) * z;
			z = -sinf(dy_R) * oldx + cosf(dy_R) * z;

            x = cosf(dz_R) * oldx - sinf(dz_R) * y;
			y = sinf(dz_R) * oldx + cosf(dz_R) * y;
        }
        void transform(GLdouble dx, GLdouble dy, GLdouble dz){
            x += dx;
            y += dy;
            z += dz;
        }
    };
    struct Triangle {
        Point a, b, c;
    };
    std::vector<Triangle> triList;
    
public:
//constructor
    void append(Triangle tri);
    void rotate(GLdouble dx, GLdouble dy, GLdouble dz);
    void transform(GLdouble dx, GLdouble dy, GLdouble dz);
    bool visible() {return visible;}

};


void processInput(GLFWwindow *window);
void scaleToScreen();
void projectPoints(Polygon poly, matrix4x4 proj);


#endif