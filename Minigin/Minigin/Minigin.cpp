#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "FPSComponent.h"
#include "GameObject.h"
#include "RenderComponent2D.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Timer.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	Transform pos{};

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	//Background
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));
	scene.Add(go);

	//Title
	go = std::make_shared<GameObject>("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Programming 4 assignment");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);
	scene.Add(go);

	//Logo
	go = std::make_shared<GameObject>("Logo");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));

	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y / 2 - 37, 0);
	go->SetTransform(pos);
	scene.Add(go);

	//FPS Counter
	go = std::make_shared<GameObject>("FPS");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("FPS: -");
	go->AddComponent(textComp);
	auto FPSComp = std::make_shared<FPSComponent>();
	FPSComp->SetTextComponent(textComp);
	go->AddComponent(FPSComp);
	scene.Add(go);
	
	pos.SetPosition(0, 0, 0);
	//go = std::make_shared<GameObject>();
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag{};

		TIMER.SetFixedTimeStep( 1 / MsPerUpdate);
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			//Update timer
			TIMER.SetDeltaTime(deltaTime);

			doContinue = input.ProcessInput();

			while(lag >= MsPerUpdate)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerUpdate;
			}

			sceneManager.Update();

			renderer.Render();
			//auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());

			//duration<float> deltaT = std::chrono::duration<float>(deltaTime);

			//auto sleepTime = duration_cast<duration<float>>(currentTime - high_resolution_clock::now()) + MsPerFrame;
			//this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
