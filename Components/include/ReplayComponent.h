#pragma once
#include <Types.h>

namespace Krooz2D
{
    struct SnapShots
    {
        Vec2 Position;
        Ref<TextureDescription> desc;
        float timestamp;
    };

    class ReplayComponent
    {
    private:
        std::vector<SnapShots> _SnapData;
				size_t _maxSnapshots = 1000; 
        bool _recording = false;
        bool _playing = false;
        size_t _index = 0;
        float _global = 0.0f;
        float _duration = 0.0f;

    public:
				float _playbackTimer = 0.0f;
        bool start_recordind();
        bool end_recording();

        bool start_playing();
        bool is_recording() const { return _recording; }
        bool is_playing() const { return _playing; }
				void reset();

				void update(SnapShots& Data, float dt);
				std::vector<SnapShots>& Get();
				int get_index();
				int advance_index();

    };
}
