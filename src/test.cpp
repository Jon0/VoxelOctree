#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "buffer/Buffer.h"
#include "buffer/Octree.h"
#include "components/Camera.h"
#include "pipeline/Pipeline.h"
#include "render/Renderer.h"
#include "shader/Shader.h"

using namespace std;

void error_callback(int error, const char* description) {
	cerr << description << endl;
}

int main(int argc, char *argv[]) {
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    if (glewInit() != GLEW_OK) {
    	cerr << "Failed to initialize GLEW" << endl;
        exit(EXIT_FAILURE);
    }

	/* Init vao */
    GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    Renderer r;

    /*
     * gl error check
     */
    if (int error = glGetError()) cout << "error = " << error << endl;

    /*
     * start loop
     */
    bool mDown = false;
    double mousex, mousey;
	while (!glfwWindowShouldClose(window))
	{
	    int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);
		r.draw();

		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
