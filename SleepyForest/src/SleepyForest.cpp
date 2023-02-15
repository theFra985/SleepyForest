#include <iostream>
#include <GLFW/glfw3.h>
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"

class MainLayer : public Walnut::Layer {
public:
    MainLayer(const Walnut::Application *application) {
        _application = application;
    }

    void OnAttach() override {
        Walnut::Random::Init();
//        ImGui::NewFrame();
//        ImGui::SetNextWindowPos(ImVec2(4480, 29), ImGuiCond_Appearing);
//        ImGui::SetNextWindowSize(ImVec2(1920, 1051), ImGuiCond_Appearing);
//        ImGui::EndFrame();
#ifdef WL_DEBUG
        /*
         * Puts window on the secondary monitor for debugging environment
         */
        glfwWindowHint(GLFW_VISIBLE, 0);
        auto window = _application->GetWindowHandle();
        int monitorX, monitorY, monitorWidth, monitorHeight;
        int monitorsCount;
        glfwGetMonitorWorkarea(glfwGetMonitors(&monitorsCount)[monitorsCount - 1],
                               &monitorX, &monitorY, &monitorWidth, &monitorHeight);
        glfwSetWindowPos(window,
                         monitorX + monitorWidth / 2 - monitorWidth / 2,
                         monitorY + monitorHeight / 2 - monitorHeight / 2);
        glfwMaximizeWindow(window);
        glfwShowWindow(window);
#endif // WL_DEBUG
    }

    virtual void OnUIRender() override {
#ifdef DUMP_WINDOW
        auto viewport = ImGui::GetMainViewport();
        auto position = viewport->WorkPos; // ImGui::GetWindowPos();
        auto size = viewport->WorkSize; // ImGui::GetWindowSize();
        std::cout << "X: " << position.x << ", Y: " << position.y << ", Width: " << size.x << ", Height: " << size.y
                  << std::endl;
#endif // DUMP_WINDOW
        ImGui::Begin("Render View");
//        ImGui::Begin("Hello");
        RenderView();
        ImGui::End();

        ImGui::ShowDemoWindow();
    }

    void RenderView() {
        auto region = ImGui::GetContentRegionAvail();
        if (region.x == 0 || region.y == 0)
            return;
        if (_canvas && (region.x != (float) _canvas->GetWidth() || region.y != (float) _canvas->GetHeight())) {
            delete[] _buffer;
            _buffer = nullptr;
        }
        if (!_buffer) {
            delete[] _buffer;
            _buffer = new uint32_t[(ulong) (region.x * region.y)];
            _canvas = std::make_shared<Walnut::Image>(region.x, region.y, Walnut::ImageFormat::RGBA, _buffer);
        }
//        ImGui::Button("Button");
        ImGui::Image(_canvas->GetDescriptorSet(), ImVec2((float) _canvas->GetWidth(), (float) _canvas->GetHeight()));
    }

    void OnUpdate(float ts) override {
        if (!_buffer)
            return;

        /*std::ios_base::fmtflags f(std::cout.flags());  // save flags state
        std::cout << std::hex << color << std::endl;
        std::cout.flags(f);  // restore flags state*/
        for (ulong x = 0; x < _canvas->GetWidth(); x++) {
            auto color = 0xFF000000 + ((Walnut::Random::UInt(0, 0xFF)) << 16) + ((Walnut::Random::UInt(0, 0xFF)) << 8);
            for (ulong y = 0; y < _canvas->GetHeight(); y++)
                _buffer[x + (_canvas->GetWidth() * y)] = color;
        }
        _canvas->SetData(_buffer);
    }

    ~MainLayer() override {
        delete[] _buffer;
    }

private:
    uint32_t *_buffer = nullptr;
    std::shared_ptr<Walnut::Image> _canvas;
    const Walnut::Application *_application;
};

Walnut::Application *Walnut::CreateApplication(int argc, char **argv) {
    Walnut::ApplicationSpecification spec;
    spec.Name = "Sleepy Forest";
    spec.Width = 1920;
    spec.Height = 1051;

    Walnut::Application *app = new Walnut::Application(spec);
    app->PushLayer(std::make_shared<MainLayer>(app));
    app->SetMenubarCallback([app]() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                app->Close();
            }
            ImGui::EndMenu();
        }
    });
    return app;
}