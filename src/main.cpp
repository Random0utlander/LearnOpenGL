#include "config.h"
#include "triangle_mesh.h"

using namespace std;

//Prototypes
unsigned int make_shader(const string& vertex_filepath, const string& fragment_filepath);
unsigned int make_module(const string& filepath, unsigned int module_type);
//

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

    unsigned int shader =make_shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragments.txt"
    );
    

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        triangle->draw();

        glfwSwapBuffers(window);
    }
    
    glDeleteProgram(shader);
    delete triangle;
    glfwTerminate();
    return 0;
}

unsigned int make_shader(const string& vertex_filepath, const string& fragment_filepath){
    vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader,  1024, NULL, errorLog);
        cout << "Shader Linking Error:\n" << errorLog << endl;
    }

    for(unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }

    return shader;
}

unsigned int make_module(const string& filepath, unsigned int module_type){
    /*
    ifstream file;
    stringstream bufferedlines;
    string line;

    file.open(filepath);
    while (getline(file, line))
    {
        bufferedlines << line << "\n";
    }
    string shaderSource = bufferedlines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedlines.str("");
    file.close();
*/
    std::string shaderCode;
    std::ifstream ShaderFile;
    // ensure ifstream objects can throw exceptions:
    ShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        ShaderFile.open(filepath);
        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();
        // close file handlers
        ShaderFile.close();
        // convert stream into string
        shaderCode   = ShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* ShaderCode = shaderCode.c_str();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &ShaderCode, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule,  1024, NULL, errorLog);
        cout << "Shader Module Compilation Error:\n" << errorLog << endl;
    }

    return shaderModule;
} 