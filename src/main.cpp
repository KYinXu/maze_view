#include <iostream>

#include "view.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>

#define SCREEN_WIDTH 1600.0f
#define SCREEN_HEIGHT 1200.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


//Shaders

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.02f, 1.0f);\n"
"}\n\0";



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C++ 3D RayTracer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//DEFINE VARIABLES FOR PROJECTION MATRIX
	matrix4x4 projection;
	GLfloat aspect = SCREEN_HEIGHT / SCREEN_WIDTH;
	GLfloat fov = 90;
	GLfloat fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * PI);
	GLfloat zfar = 100.0f;
	GLfloat znear = 0.1f;
	GLfloat q = zfar/(zfar-znear);
	Polygon cube;
	int transVal = 3.0f;

	projection.matrix[0][0] = aspect * fovRad;
	projection.matrix[1][1] = fovRad;
	projection.matrix[2][2] = zfar/(zfar-znear);
	projection.matrix[3][2] = (-zfar * znear)/(zfar-znear);
	
	projection.matrix[2][3] = 1.0f;
	
	point points[] = 
	{
		
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 1.0f},
		{-0.5f, 0.5f, 1.0f},
		{0.5f, 0.5f, 1.0f},
		{0.5f, -0.5f, 1.0f}
		
		
		/*
		{0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		*/
		
	};
	//update below
	cube.definePoints(points);
	//cube.rotatePoints(0.0f, 0.0f, 20.0f);
	cube.transform(0.0, 0.0, transVal);
	//cube.translatePoints(0.0f, 0.0f, transVal);
	
	//cube.projectPoints(projection);
	projectPoints(cube, projection);
	//cube.scaleToScreen();
	//cube.defineTriangles();

	
	triangle meshArray[12]; 
	
	copy(cube.triangles.begin(), cube.triangles.end(), meshArray);
	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(meshArray), meshArray, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glMatrixMode(GL_PROJECTION);
	// Variables to be changed in the ImGUI window
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	// Exporting variables to shaders
	glUseProgram(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//TAKE THIS OUTSIDE IF STATEMENTS AND PUT AT BOTTOM
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// Export variables to shader
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);
		
		/*
		std::cout << "\nPrinting Projected Points \n\n";
			for(int i = 0; i < 8; i++){
				std::cout << "x: " << cube.projectedPoints[i].x << " y: " << cube.projectedPoints[i].y << " z: " << cube.projectedPoints[i].z << "\n";
			}
		*/
		
		//Find way to convert to switch case
		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(0.0f, -1.0f, 0.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);
				
		}
		else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(0.0f, 1.0f, 0.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(1.0f, 0.0f, 0.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);
		}
		else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(-1.0f, 0.0f, 0.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(0.0f, 0.0f, -1.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);	
		}	
		else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			cube.translatePoints(0.0f, 0.0f, -transVal);
			cube.rotatePoints(0.0f, 0.0f, 1.0f);
			cube.translatePoints(0.0f, 0.0f, transVal);
		}

		cube.projectPoints(projection);
		cube.defineTriangles();
		copy(cube.triangles.begin(), cube.triangles.end(), meshArray);
		glClearColor(0.07f, 0.13f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(meshArray), meshArray, GL_STATIC_DRAW);
		for(int i = 0; i < sizeof(meshArray); i+=3){
			glDrawArrays(GL_LINE_LOOP, i, 3);
		}

		processInput(window);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}