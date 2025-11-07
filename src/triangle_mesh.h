#include "config.h"

class TriangleMesh {
public:
TriangleMesh();
void Bind() const;
~TriangleMesh();

private:
unsigned int VBO, VAO, EBO;
};