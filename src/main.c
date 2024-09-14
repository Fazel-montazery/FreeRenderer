#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>

#include "shader.h"

static int winWidth = 800;
static int winHeight = 600;

static bool polyView = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char** argv)
{
        // Initializing glfw
        glfwInit();
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // Creating window
        GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "FuckingOpenGL", NULL, NULL);
        if (!window)
        {
                printf("Failed to create GLFW window\n");
                glfwTerminate();
                return FAILURE;
        }
        glfwMakeContextCurrent(window);

        // Set callbacks
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, keyCallback);

        // Loading OpenGl functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
                printf("Failed to initialize GLAD\n");
                return FAILURE;
        }

        // Creating the GPU program
        GLuint shaderProgram;
        if(create_program_from_shaders("shaders/vertex.glsl", "shaders/fragment.glsl", &shaderProgram) != SUCCESS) {
 	glfwDestroyWindow(window);
 	glfwTerminate();
 	return FAILURE;
        }

        // Main loop
        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                // **************
                glClearColor(0.2, 0.2, 0.2, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                // **************
                
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        // CleanUp
        glDeleteProgram(shaderProgram);
        glfwDestroyWindow(window);
        glfwTerminate();
        return SUCCESS;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	winWidth = width;
	winHeight = height;
        glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
        // For low latancy inputs
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
        if (action == GLFW_PRESS) {
                if (key == GLFW_KEY_P) {
                        glPolygonMode(GL_FRONT_AND_BACK, ((polyView) ? GL_FILL : GL_LINE));
                        polyView = !polyView;
                }

                if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) {
                        glfwSetWindowShouldClose(window, true);
                }
        }
}

