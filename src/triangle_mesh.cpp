#include "triangle_mesh.h"

TriangleMesh::TriangleMesh() {
    
    std::vector<float> data = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //VERTEX -> with 2 atrributes position and color (3D)
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    vertex_count = 3;

    glGenVertexArrays(1, &VAO); //VERTEX Array Object (array of pointers to attributes)
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO); //VERTEX Buffer Object (the data and attribute pointers (how to interpert the data))
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    //position         atrribute                   stride
    //                  number                    in bytes
    //                    |                          |
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    //                       |                              |
    //                    Dimension                  offset to the
    //                 of the attribute             start of attribute
    
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);

}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}