struct Systems
{
    void Sumbit() {};  
    virtual void Update(float deltaTime) = 0;  
    ~Systems() = default;
};
