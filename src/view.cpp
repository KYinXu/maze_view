#include "view.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>




void Polygon::rotate(GLdouble dx, GLdouble dy, GLdouble dz){
	for(Triangle tri: triList){
		tri.a.rotate(dx, dy, dz);
		tri.b.rotate(dx, dy, dz);
		tri.c.rotate(dx, dy, dz);
	}
}

void Polygon::transform(GLdouble dx, GLdouble dy, GLdouble dz){
	for(Triangle tri: triList){
		tri.a.transform(dx, dy, dz);
		tri.b.transform(dx, dy, dz);
		tri.c.transform(dx, dy, dz);
	}
}