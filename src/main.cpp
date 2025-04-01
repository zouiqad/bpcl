#include "WindowManager.h"
#include "components/Camera.h"
#include "systems/RenderSystem.h"
#include "systems/CameraControlSystem.h"
#include "systems/PointCloudSystem.h"
#include "components/Renderable.h"
#include "components/Transform.h"
#include "components/Geometry.h"
#include "core/Mediator.h"
#include <chrono>
#include "GUIManager.h"
#include "components/Cubemap.h"
#include "systems/SkyboxRenderSystem.h"


Mediator gMediator;

bool quit = false;

void QuitHandler(Event& event)
{
    quit = true;
}

int main() {
    gMediator.Init();

    WindowManager windowManager;
    windowManager.Init("BETTER PCL", 1920, 1080, 0, 0);

    gMediator.AddEventListener(FUNCTION_LISTENER(Events::Window::QUIT, QuitHandler));

    GUIManager guiManager;
    guiManager.Init(windowManager.getWindow());

    gMediator.RegisterComponent<Camera>();
    gMediator.RegisterComponent<Cubemap>();
    gMediator.RegisterComponent<Renderable>();
    gMediator.RegisterComponent<Transform>();
    gMediator.RegisterComponent<Geometry>();


    auto cameraControlSystem = gMediator.RegisterSystem<CameraControlSystem>();
    {
        Signature signature;
        signature.set(gMediator.GetComponentType<Camera>());
        signature.set(gMediator.GetComponentType<Transform>());
        gMediator.SetSystemSignature<CameraControlSystem>(signature);
    }

    cameraControlSystem->Init();

    auto renderSystem = gMediator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(gMediator.GetComponentType<Renderable>());
        signature.set(gMediator.GetComponentType<Transform>());
        gMediator.SetSystemSignature<RenderSystem>(signature);
    }

    renderSystem->Init();

    auto pointCloudSystem = gMediator.RegisterSystem<PointCloudSystem>();
    {
        Signature signature;
        signature.set(gMediator.GetComponentType<Renderable>());
        signature.set(gMediator.GetComponentType<Transform>());
        signature.set(gMediator.GetComponentType<Geometry>());
        gMediator.SetSystemSignature<PointCloudSystem>(signature);
    }

    pointCloudSystem->Init();

    auto skyboxRenderSystem = gMediator.RegisterSystem<SkyboxRenderSystem>();
    {
        Signature signature;
        signature.set(gMediator.GetComponentType<Cubemap>());
        gMediator.SetSystemSignature<SkyboxRenderSystem>(signature);
    }

    // Delta time
    float dt = 0.0f;

    while(!quit) {
        auto startTime = std::chrono::high_resolution_clock::now();

        guiManager.NewFrame();

        windowManager.ProcessEvents();

        cameraControlSystem->Update(dt);

        pointCloudSystem->Update(dt);

        renderSystem->Update(dt);

        guiManager.Update();

        windowManager.Update();

        auto stopTime = std::chrono::high_resolution_clock::now();

        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }

    // Clean resources
    guiManager.Shutdown();
    windowManager.Shutdown();

    return 0;
}
