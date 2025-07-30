# Krooz2D

**Krooz2D** is a lightweight, modular 2D game engine built using modern C++.  
This project is primarily a **learning-focused engine**, created to explore key concepts in game engine development — including rendering pipelines, input management, resource loading, scene transitions, and minimal architecture.

---

## 🔧 Build Requirements

- C++20-compatible compiler (MSVC or Clang recommended)
- CMake ≥ 3.20
- OpenGL (provided by your system)
- **libcurl** – required for using the `NetworkHandler` module
---

---

## Cool Example:

```cpp
#include <Krooz2d.h>
#include <iostream>

class Main : public Scene{
    private:
    Quad* quad = nullptr;
    Texture* tex = nullptr;
    public:
    Main(){
        tex = new Texture("Assets/Ken.jpg");
        quad = new Quad(Vec2(60,60) , Vec2(100,100) ,tex);
    }
    void Update(float dt) override{
        auto pos = quad->GetPos();
        pos.x += 10 * dt;
        quad->SetPosition(pos);
    }
    void Draw() override{
        quad->Draw();
    }

    void HandleInput() override{
        if(Input::IsJustPressed(87)){
            std::cout<< "Worked\n";
        }
    }
    ~Main(){
        delete quad;
        delete tex;
    }
};

class NewClass : public Scene {
private:
    Quad* quad = nullptr;
    Texture* tex = nullptr;
    std::atomic<bool> isdone = false;

public:
    NewClass() {
        tex = new Texture("Assets/tex.jpg");
        quad = new Quad(Vec2(70, 100), Vec2(100, 100), tex);
    }

    void Update(float dt) override {
        if (isdone.exchange(false)) { 
            tex->CommitUpload();
        }
    }

    void Draw() override {
        quad->Draw();
    }

    void HandleInput() override {
        if (Input::IsJustPressed(49)) {
            std::thread([this]() {
                NetworkHandler net;
                net.GetRequest("http://localhost:8000/home");
                std::vector<unsigned char> result = net.GetBuffer();

                if (!result.empty()) {
                    tex->ReplaceAsync(std::move(result));
                    std::cout << "Trying to change the texture...\n";
                    isdone = true;
                }
            }).detach(); 
        }
    }

    ~NewClass() {
        delete quad;
        delete tex;
    }
};

int main() {
    Engine Eng;
    Eng.Init(1280, 720, "Krooz");

    SceneManager manager;
    std::shared_ptr<Scene> mainScene = std::make_shared<Main>();
    std::shared_ptr<Scene> Newc = std::make_shared<NewClass>();
   manager.AddScene("Main", []() {
    return std::make_shared<Main>();
    });
    manager.AddScene("New", []() {
        return std::make_shared<NewClass>();
    });
    
    manager.SetScene("Main");
    Input::Init(Eng.GetWindow());
    while (Eng.IsValid())
    {
        float dt = Engine::GetDeltaTime();
        if(Input::IsJustPressed(87)){
            manager.SetScene("Main");
        }
        if(Input::IsJustPressed(83)){
            manager.SetScene("New");
        }

        manager.Update(0.016f); 
        Eng.BeginDraw();
        manager.Update(dt);
        Eng.EndDraw();
    }
    
}
