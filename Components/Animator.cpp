#include "Animator.h"

Animator::Animator(int cols, int rows, Vec2 texSize)
{
    FrameDim.x = static_cast<int>(texSize.x / cols);
    FrameDim.y = static_cast<int>(texSize.y / rows);

    TexDim = texSize;
}

void Animator::AddAnim(std::string Name, AnimData data){
    animations[Name] = data;
}

bool Animator::SetAnim(std::string Name){
    auto it = animations.find(Name);
    if(it != animations.end()){
        mcurrent = &it->second;
        mCurrentFrame = 0;
        UpdateUvsO();
        return true; 
    }
    return false;
}


void Animator::Update(float deltaTime) {
    if (!mcurrent) return;

    mAnimTime += deltaTime;

    if (mAnimTime >= 0.1f) {
        mAnimTime = 0.0f; 

        mCurrentFrame++;

        if (mCurrentFrame >= mcurrent->mEnd) {
            if (mcurrent->Blooping) {
                mCurrentFrame = mcurrent->mStart; 
            } else {
                mCurrentFrame = mcurrent->mEnd - 1; 
            }
        }
        UpdateUvsO();
    }
}


void Animator::UpdateUvsO()
{
    if (!mcurrent) return;
    
    // Calculate scale (size of each frame relative to texture)
    scale.x = static_cast<float>(FrameDim.x) / TexDim.x;
    scale.y = static_cast<float>(FrameDim.y) / TexDim.y;

    // Calculate which column and row the current frame is in
    int totalCols = static_cast<int>(TexDim.x / FrameDim.x);
    int mcols = mCurrentFrame % totalCols;
    int mrows = mCurrentFrame / totalCols;

    // Calculate offset (position of current frame in texture coordinates)
    offset.x = static_cast<float>(mcols * FrameDim.x) / TexDim.x;
    offset.y = static_cast<float>(mrows * FrameDim.y) / TexDim.y;
}
