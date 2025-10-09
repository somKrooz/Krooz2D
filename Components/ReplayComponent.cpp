#include "ReplayComponent.h"

namespace Krooz2D
{
    bool ReplayComponent::start_recordind()
    {
        if(!_SnapData.empty())
            _SnapData.clear();

        _recording = true;
        _playing = false;
        _index = 0;
        _duration = 0.0f;
        _global = 0.0f;

        return true;
    }

    bool ReplayComponent::end_recording(){
        _recording = false;
        _playing = false;
        _index = 0;

        return true;
    }

    bool ReplayComponent::start_playing()
    {
        if (_SnapData.empty())
            return false;

        _recording = false;
        _playing = true;
				_playbackTimer = 0.0f;
        _index = 0;
        return true;
    }

    void ReplayComponent::update(SnapShots& Data, float dt)
    {
        if (!_recording) return;

        _global += dt;
        _duration += dt;
        
        if (_global >= 0.1f)
        {
            _SnapData.push_back({ Data.Position , Data.desc, _duration});
							if (_SnapData.size() >= _maxSnapshots)
							{
								_SnapData.erase(_SnapData.begin());
							}
            _global = 0.0f;
        }

    }

    std::vector<SnapShots>& ReplayComponent::Get(){
        return _SnapData;
    }
    
    int ReplayComponent::advance_index()
    {
        if (_SnapData.empty())
            return -1;

        _index++;
        return _index;
    }

    int ReplayComponent::get_index(){
        return _index;
    }
		void ReplayComponent::reset()
		{
			_playbackTimer = 0.0f;
			_index = 0;
		}
}
