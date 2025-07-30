#include <unordered_map>
#include <string>
#include <memory> 

struct Scene {
    virtual ~Scene() = default;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void HandleInput() = 0;
};

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

class SceneManager {
private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Scene>()>> factories;
    std::shared_ptr<Scene> CurrentScene = nullptr;

public:
    void AddScene(const std::string& name, std::function<std::shared_ptr<Scene>()> factory) {
        factories[name] = factory;
    }

    void SetScene(const std::string& name) {
        auto it = factories.find(name);
        if (it != factories.end()) {
            CurrentScene = it->second(); 
        }
    }

    void Update(float dt) {
        if (CurrentScene) {
            CurrentScene->HandleInput();
            CurrentScene->Update(dt);
            CurrentScene->Draw();
        }
    }
};

