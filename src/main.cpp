#include "config.h"
#include "triangle_mesh.h"
#include "shaders.h"

using namespace std;

int main(){

    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    }
/*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
*/                                                            
    window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    int w,h; //get widht and height of window to double check
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0,0,w,h);

    TriangleMesh* triangle = new TriangleMesh();

    Shader shader = Shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragments.txt"
    );
    

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        triangle->draw();

        glfwSwapBuffers(window);
    }
    
    shader.~Shader();
    delete triangle;
    glfwTerminate();
    return 0;
}