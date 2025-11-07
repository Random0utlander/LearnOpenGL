#include "triangle_mesh.h"

TriangleMesh::TriangleMesh() {
    
    float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &this->VAO); //VERTEX Array Object (array of pointers to attributes)
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->EBO); //Index Buffer Array with the order to draw vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->VBO); //VERTEX Buffer Object (the vertices and attribute pointers (how to interpert the vertices))
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position         atrribute                      stride
    //                  number                       in bytes
    //                    |                              |
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    //                       |                                            |
    //                    Dimension                                 offset to the
    //                 of the attribute                            start of attribute
    
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TriangleMesh::Bind() const{
    glBindVertexArray(this->VAO);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}