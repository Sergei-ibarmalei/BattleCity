#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_windowSizeX{ 640 };
int g_windowSizeY{ 480 };

//изменение размера экрана
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeX = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
    
}

//обработка нажатий клавиш
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode,
    int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{


    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed! Abort.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, 
                                           g_windowSizeX, 
                                           "Battle City",
                                           nullptr,
                                           nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed, abort." << std::endl;
        glfwTerminate();
        return -1;
    }

    //регистрация коллбэка для изменения размера экрана
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    //регистрация коллбека нажатия клавиш
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return 1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	
	glClearColor(1, 1, 0, 1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
