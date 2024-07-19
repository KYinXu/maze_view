#include "view.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>


Polygon::Polygon(GLdouble center, GLdouble l, GLdouble w, GLdouble h) :
	//define points
	pArr{
		{center-l/2, (GLdouble)0.0, center-w/2},
		{center-l/2, (GLdouble)0.0, center+w/2},
		{center+l/2, (GLdouble)0.0, center+w/2},
		{center+l/2, (GLdouble)0.0, center-w/2},
		{center-l/2, h, center-w/2},
		{center-l/2, h, center+w/2},
		{center+l/2, h, center+w/2},
		{center+l/2, h, center-w/2},
	}

{}



void Polygon::rotate(GLdouble dx, GLdouble dy, GLdouble dz){
	for(Point p: pArr){
		p.rotate(dx, dy, dz);
	}
}

void Polygon::transform(GLdouble dx, GLdouble dy, GLdouble dz){
	for(Point p: pArr){
		p.transform(dx, dy, dz);
	}
}


void processInput(GLFWwindow *window){
	//project points here
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		std::cout << "left" << std::endl;
	}
}
/*
void scaleToScreen(){

}
*/

std::vector<Triangle> projectPoints(Polygon poly, matrix4x4 proj){
	std::vector<Triangle> triList;
	//define triangles;

}

//when processing input, rotate points first and then re-project them
//in the future, can separate polygons as visible/invisible