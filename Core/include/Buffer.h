#pragma once

#include "vector"
using uint  = unsigned int;

class Buffer{
private:
    uint VBO, VAO;
    uint m_mode ;
    int m_vertexcout;

public:
    Buffer();
    void Bind();
    void UnBind();
    void UploadData(std::vector<float>& vertices , int CPV , uint DrawMode);
    void Draw() const;
    ~Buffer();
};
