#include <Buffer.h>
#include "glad/glad.h"

Buffer::Buffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

void Buffer::UploadData(std::vector<float>& vertices , int CPV , uint DrawMode)
{
    m_vertexcout = vertices.size() / CPV;
    m_mode = DrawMode;
    glBindVertexArray(VAO);
    
    //Populate With Data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER , vertices.size() * sizeof(float) , vertices.data() ,GL_STATIC_DRAW);

    //Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, CPV * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //TextureCoordinate
    if(CPV >= 4)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, CPV * sizeof(float) , (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    glBindVertexArray(0);
}
void Buffer::Bind()
{
    glBindVertexArray(VAO);
}
void Buffer::UnBind(){
    glBindVertexArray(0);
}

void Buffer::Draw() const{
    if(!m_mode) return;

    if (m_vertexcout > 0)
    {
        glDrawArrays(m_mode, 0, m_vertexcout);
    }
}

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
