#include <vector>
#include <Maths.h>
#include <unordered_map>
#include <string>
#include <utility>

struct AnimData
{
    int mStart;
    int mEnd;
    bool Blooping;
};


class Animator
{
    private:
    int mcols = 0;
    int mrows = 0;
    int mCurrentFrame = 0;
    float mAnimTime = 0.0f;
    Vec2 FrameDim = Vec2(0,0);
    Vec2 TexDim = Vec2(0,0);

    Vec2 scale;
    Vec2 offset;

    std::unordered_map<std::string, AnimData> animations;
    const AnimData* mcurrent = nullptr;

    void UpdateUvsO();
        
    public:
    Animator(int cols, int rows, Vec2 texSize);
    void AddAnim(std::string Name, AnimData data);
    bool SetAnim(std::string Name);
    void Update(float deltatime);

    std::pair<Vec2 , Vec2>GetAnimData(){
        return {scale , offset};
    }
};
