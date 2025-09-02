#pragma once

#include "Maths.h"
#include "vector"

struct NodeCache{
    Vec2 mPos;
};

class ReplayDriver
{
private:
    std::vector<NodeCache> mCache;
    bool recording = false;
    bool playing = false;
    size_t playbackIndex = 0;

public:
    void StartRecording() {
        mCache.clear();
        recording = true;
        playing = false;
    }

    void EndRecording() {
        recording = false;
    }

    void RecordFrame(const Vec2& pos) {
        if (recording) {
            mCache.insert(mCache.begin(), {pos});
        }
    }

    void StartPlayback() {
        playing = true;
        recording = false;
        playbackIndex = 0;
    }

    bool GetNextPlaybackFrame(Vec2& outPos) {
        if (!playing || playbackIndex >= mCache.size())
            return false;

        outPos = mCache[playbackIndex++].mPos;
        return true;
    }

    bool isReloading(){return recording;}
    bool isPlaying(){return playing;}
    void isShit(){return;}
};
