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
#include "HealthObserverComponent.h"
#include "RenderComponent2D.h"
#include "RenderComponentUI.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Timer.h"
#include "UIButton.h"

using namespace std;
using namespace std::chrono;

void InitSceneMenu();
void InitSceneSinglePlayer();
void InitSceneCoop();
void InitSceneVersus();

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

	//Initialize Controller
	auto& input = InputManager::GetInstance();

	int id = input.AddController();
	input.AddControllerCommand(InputManager::ControllerKey(id, Controller::ControllerButton::PAD_A,
		Controller::ButtonState::REPEAT), CreateCommand(Fire));
	input.AddControllerCommand(InputManager::ControllerKey(id, Controller::ControllerButton::PAD_B,
		Controller::ButtonState::KEYUP), CreateCommand(Duck));
	input.AddControllerCommand(InputManager::ControllerKey(id, Controller::ControllerButton::PAD_Y,
		Controller::ButtonState::KEYDOWN), CreateCommand(Jump));
	input.AddControllerCommand(InputManager::ControllerKey(id, Controller::ControllerButton::PAD_X,
		Controller::ButtonState::KEYDOWN), CreateCommand(Fart));

	//Initialize keyboard
	input.AddKeyboardCommand({ SDLK_ESCAPE, InputManager::SDLEvent::KEYPRESSED }, CreateCommand(ActivateMenu));
	input.AddKeyboardCommand({ SDLK_p, InputManager::SDLEvent::KEYDOWN }, CreateCommand(Fire));
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	InitSceneMenu();
	InitSceneSinglePlayer();
	InitSceneCoop();
	InitSceneVersus();

	//Transform pos{};
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	//
	////Background
	//std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	//go->AddComponent(std::make_shared<RenderComponent2D>());
	//go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));
	//scene.Add(go);
	////Title
	//go = std::make_shared<GameObject>("Title");
	//go->AddComponent(std::make_shared<RenderComponent2D>());
	//auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	//textComp->SetText("Programming 4 assignment");
	//go->AddComponent(textComp);
	//pos.SetPosition(80, 20, 0);
	//go->SetTransform(pos);
	//scene.Add(go);
	////Logo
	//go = std::make_shared<GameObject>("Logo");
	//go->AddComponent(std::make_shared<RenderComponent2D>());
	//go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));
	//pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y * 0.18f, 0);
	//go->SetTransform(pos);
	//scene.Add(go);
	////FPS Counter
	//go = std::make_shared<GameObject>("FPS");
	//go->AddComponent(std::make_shared<RenderComponent2D>());
	//textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	//textComp->SetText("FPS: -");
	//go->AddComponent(textComp);
	//auto FPSComp = std::make_shared<FPSComponent>();
	//FPSComp->SetTextComponent(textComp);
	//go->AddComponent(FPSComp);
	//scene.Add(go);
	//pos.SetPosition(0, 0, 0);
	//
	//InputManager::GetInstance().AddControllerCommand(InputManager::ControllerKey(0, Controller::ControllerButton::PAD_LTRIGGER,
	//	Controller::ButtonState::KEYDOWN), CreateCommandToObject(ChangeText, go));
	////Health Observer (renderComp2D, TextComp, HealthObserver -> Attach to QBert)
	//go = std::make_shared<GameObject>("QBertHealthObserver");
	//go->AddComponent(std::make_shared<RenderComponent2D>());
	//textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	//textComp->SetText("PlayerAlive");
	//go->AddComponent(textComp);
	//auto healthObsComp = std::make_shared<HealthObserverComponent>();
	//healthObsComp->SetTextComponent(textComp);
	//go->AddComponent(healthObsComp);
	//pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 74, RENDERER.GetCurrentWindowDimensions().y * 0.9f, 0);
	//go->SetTransform(pos);
	//scene.Add(go);
	////QBert (health comp)
	//go = std::make_shared<GameObject>("QBert");
	//auto healthComp = std::make_shared<HealthComponent>();
	//healthComp->AddObserver(healthObsComp);
	//healthComp->SetLives(3);
	//go->AddComponent(healthComp);
	//scene.Add(go);
	////MainMenu
	//auto mainMenu = std::make_shared<GameObject>("MainMenu");
	//auto uiComp = std::make_shared<RenderComponentUI>();
	//uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.4 }, CreateCommand(Fire), "Fire"));
	//uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.5 }, CreateCommand(Fart), "Fart"));
	//uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.6 }, CreateCommand(Jump), "Jump"));
	//uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.7 }, CreateCommandToObject(Kill, go), "Kill"));
	//uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.8 }, CreateCommandToObject(Respawn, go), "Respawn"));
	//mainMenu->AddComponent(uiComp);
	//scene.Add(mainMenu);
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

			INPUTMANAGER.ProcessInput();
			doContinue = !INPUTMANAGER.CheckSDLEvent(SDLK_ESCAPE, InputManager::QUIT);

			if (input.IsButtonPressed(Controller::ControllerButton::PAD_BACK, 0))
				doContinue = false;

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

void InitSceneMenu()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Menu");

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

	//MainMenu
	auto mainMenu = std::make_shared<GameObject>("MainMenu");
	auto uiComp = std::make_shared<RenderComponentUI>();
	uiComp->SetRenderFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.4 }, CreateCommand(ActivateSingleplayer), "Singleplayer"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.5 }, CreateCommand(ActivateCoop), "Co-op"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.6 }, CreateCommand(ActivateVersus), "Versus"));
	mainMenu->AddComponent(uiComp);
	scene.Add(mainMenu);

}
void InitSceneSinglePlayer()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Singleplayer", false);

	//Background
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));
	scene.Add(go);

	//Title
	go = std::make_shared<GameObject>("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Singleplayer");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);
	scene.Add(go);

	//Logo
	go = std::make_shared<GameObject>("Logo");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));

	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y * 0.18f, 0);
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


	//Health Observer (renderComp2D, TextComp, HealthObserver -> Attach to QBert)
	go = std::make_shared<GameObject>("QBertHealthObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("PlayerAlive");
	go->AddComponent(textComp);
	auto healthObsComp = std::make_shared<HealthObserverComponent>();
	healthObsComp->SetTextComponent(textComp);
	go->AddComponent(healthObsComp);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 74, RENDERER.GetCurrentWindowDimensions().y * 0.9f, 0);
	go->SetTransform(pos);
	scene.Add(go);
	//QBert (health comp)
	go = std::make_shared<GameObject>("QBert");
	auto healthComp = std::make_shared<HealthComponent>();
	healthComp->AddObserver(healthObsComp);
	healthComp->SetLives(3);
	go->AddComponent(healthComp);
	scene.Add(go);

}
void InitSceneCoop()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Coop", false);

	//Background
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));
	scene.Add(go);

	//Title
	go = std::make_shared<GameObject>("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Co-op");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);
	scene.Add(go);

	//Logo
	go = std::make_shared<GameObject>("Logo");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));

	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y * 0.18f, 0);
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

}
void InitSceneVersus()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Versus", false);

	//Background
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));
	scene.Add(go);

	//Title
	go = std::make_shared<GameObject>("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Versus");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);
	scene.Add(go);

	//Logo
	go = std::make_shared<GameObject>("Logo");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));

	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y * 0.18f, 0);
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

}
