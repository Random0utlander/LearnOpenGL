#define STB_IMAGE_IMPLEMENTATION
#include "config.h"
#include "triangle_mesh.h"
#include "shaders.h"
#include "textures.h"

using namespace std;

//prototipes
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Create Shader Program 
    Shader shader = Shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragments.txt"
    );
    
    // Create Textures from image
    int img_w, img_h, img_nChannels;
    stbi_set_flip_vertically_on_load(true);
    Texture2D* texture1 = new Texture2D();
    Texture2D* texture2 = new Texture2D();
    unsigned char* img = stbi_load("../src/img/awesomeface.png", &img_w, &img_h, &img_nChannels, 0);
    if(img)
    {        
        texture1->Image_Format = GL_RGBA;
        texture1->Internal_Format = GL_RGBA;
        texture1->Generate(img_w, img_h, img);
    }
    else
    {
        cout << "Failed to load texture 1" << std::endl;
    }
    
    stbi_image_free(img);
    img = stbi_load("../src/img/container.jpg", &img_w, &img_h, &img_nChannels, 0);
    if(img)
    {        
        texture2->Generate(img_w, img_h, img);
    }
    else
    {
        cout << "Failed to load texture 2" << std::endl;
    }
    
    stbi_image_free(img);



    // Create triangle
    TriangleMesh* mesh = new TriangleMesh();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader.use();
    shader.setInt("Texture0", 0);
    shader.setInt("Texture1", 1);

    //-------------------------------------------------------------------------------------------
    //                  RENDER LOOP
    //-------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture1->Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2->Bind();
        mesh->Bind();
        shader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete mesh;
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}