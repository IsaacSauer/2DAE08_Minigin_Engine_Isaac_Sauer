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
#include "ScoreComponent.h"
#include "ScoreObserverComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Timer.h"
#include "UIButton.h"
#include "UITextBox.h"

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

		TIMER.SetFixedTimeStep(1 / MsPerUpdate);
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

			while (lag >= MsPerUpdate)
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
	std::shared_ptr<GameObject> go = scene.CreateGameObjectInScene("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));

	//Title
	go = scene.CreateGameObjectInScene("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Programming 4 assignment");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);

	//Logo
	go = scene.CreateGameObjectInScene("Logo");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("logo.png")));

	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 104, RENDERER.GetCurrentWindowDimensions().y * 0.18f, 0);
	go->SetTransform(pos);

	//MainMenu
	auto mainMenu = scene.CreateGameObjectInScene("MainMenu");
	auto uiComp = std::make_shared<RenderComponentUI>();
	uiComp->SetRenderFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.4 }, CreateCommand(ActivateSingleplayer), "Singleplayer", false));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.5 }, CreateCommand(ActivateCoop), "Co-op", false));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.6 }, CreateCommand(ActivateVersus), "Versus", false));
	uiComp->AddUIElement(std::make_shared<UITextBox>(glm::vec2{0.1, 0.4}, 200.f, "Info:\n"
		"Currently only Singleplayer and Co-op is available.\n"
		"\n"
		"Controls:\n"
		"All the gameplay controls are currently with placeholder buttons.\n"
		"\n"
		"\"Escape\" to go back to main menu.\n"
		"PAD_A: Fire\n"
		"PAD_B: Duck\n"
		"PAD_Y: Jump\n"
		"PAD_X: Fart\n"
		"SHARE(PS4)/BACK(xbox): quit"));

	mainMenu->AddComponent(uiComp);
}

void InitSceneSinglePlayer()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Singleplayer", false);

	//Background
	std::shared_ptr<GameObject> go = scene.CreateGameObjectInScene("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));

	//Title
	go = scene.CreateGameObjectInScene("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Singleplayer");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);

	//FPS Counter
	go = scene.CreateGameObjectInScene("FPS");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("FPS: -");
	go->AddComponent(textComp);
	auto FPSComp = std::make_shared<FPSComponent>();
	FPSComp->SetTextComponent(textComp);
	go->AddComponent(FPSComp);
	pos.SetPosition(0, 0, 0);

#pragma region Player 1
	//Health Observer (renderComp2D, TextComp, HealthObserver -> Attach to QBert)
	go = scene.CreateGameObjectInScene("QBertHealthObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("PlayerAlive");
	go->AddComponent(textComp);
	auto healthObsComp = std::make_shared<HealthObserverComponent>();
	healthObsComp->SetTextComponent(textComp);
	go->AddComponent(healthObsComp);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 74, RENDERER.GetCurrentWindowDimensions().y * 0.9f, 0);
	go->SetTransform(pos);
	//QBert (health comp)
	auto health = scene.CreateGameObjectInScene("QBert");
	scene.Add(health);
	auto healthComp = std::make_shared<HealthComponent>();
	health->AddComponent(healthComp);
	healthComp->AddObserver(healthObsComp);
	healthComp->SetLives(3);

	//Score observer
	go = scene.CreateGameObjectInScene("QBertScoreObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("Score: -");
	go->AddComponent(textComp);
	auto scoreObsComp = std::make_shared<ScoreObserverComponent>();
	scoreObsComp->SetTextComponent(textComp);
	go->AddComponent(scoreObsComp);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x / 2 - 74, RENDERER.GetCurrentWindowDimensions().y * 0.8f, 0);
	go->SetTransform(pos);
	//Score subject
	auto score = scene.CreateGameObjectInScene("QBertScoreSubject");
	auto scoreComp = std::make_shared<ScoreComponent>();
	scoreComp->AddObserver(scoreObsComp);
	scoreComp->SetScore(0);
	score->AddComponent(scoreComp);
#pragma endregion
	
	//Buttons
	auto buttons = scene.CreateGameObjectInScene("buttons");
	auto uiComp = std::make_shared<RenderComponentUI>();
	uiComp->SetRenderFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.4 }, CreateCommandToObject(Kill, health), "Kill"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.45 }, CreateCommandToObject(Respawn, health), "Respawn"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.5 }, CreateCommandToObject(ChangeColor, score), "On ChangeColor"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.55 }, CreateCommandToObject(DefeatCoilyWithFlyingDisc, score), "On Defeat Coily with flying disc"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.6 }, CreateCommandToObject(RemainingDiscsAtTheEndOfAStage, score), "On Remaining Discs At End Of Stage"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.5, 0.65 }, CreateCommandToObject(CatchSlickAndSam, score), "On Catch Slick And Sam"));

	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.99, 0.05 }, CreateCommand(ActivateMenu), "Menu"));
	buttons->AddComponent(uiComp);

}

void InitSceneCoop()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Coop", false);

	//Background
	std::shared_ptr<GameObject> go = scene.CreateGameObjectInScene("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));

	//Title
	go = scene.CreateGameObjectInScene("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Co-op");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);

	//FPS Counter
	go = scene.CreateGameObjectInScene("FPS");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("FPS: -");
	go->AddComponent(textComp);
	auto FPSComp = std::make_shared<FPSComponent>();
	FPSComp->SetTextComponent(textComp);
	go->AddComponent(FPSComp);
	pos.SetPosition(0, 0, 0);

#pragma region Player 1
	//Health Observer (renderComp2D, TextComp, HealthObserver -> Attach to QBert)
	go = scene.CreateGameObjectInScene("QBertHealthObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("PlayerAlive");
	go->AddComponent(textComp);
	auto healthObsComp1 = std::make_shared<HealthObserverComponent>();
	healthObsComp1->SetTextComponent(textComp);
	go->AddComponent(healthObsComp1);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x * 0.1f, RENDERER.GetCurrentWindowDimensions().y * 0.9f, 0);
	go->SetTransform(pos);
	//QBert (health comp)
	auto health1 = scene.CreateGameObjectInScene("Player 1");
	scene.Add(health1);
	auto healthComp1 = std::make_shared<HealthComponent>();
	health1->AddComponent(healthComp1);
	healthComp1->AddObserver(healthObsComp1);
	healthComp1->SetLives(3);

	//Score observer
	go = scene.CreateGameObjectInScene("QBertScoreObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("Score: -");
	go->AddComponent(textComp);
	auto scoreObsComp1 = std::make_shared<ScoreObserverComponent>();
	scoreObsComp1->SetTextComponent(textComp);
	go->AddComponent(scoreObsComp1);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x * 0.1f, RENDERER.GetCurrentWindowDimensions().y * 0.8f, 0);
	go->SetTransform(pos);
	//Score subject
	auto score1 = scene.CreateGameObjectInScene("QBertScoreSubject");
	auto scoreComp1 = std::make_shared<ScoreComponent>();
	scoreComp1->AddObserver(scoreObsComp1);
	scoreComp1->SetScore(0);
	score1->AddComponent(scoreComp1);
#pragma endregion
	
#pragma region Player 2
	//Health Observer (renderComp2D, TextComp, HealthObserver -> Attach to QBert)
	go = scene.CreateGameObjectInScene("QBertHealthObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("PlayerAlive");
	go->AddComponent(textComp);
	auto healthObsComp2 = std::make_shared<HealthObserverComponent>();
	healthObsComp2->SetTextComponent(textComp);
	go->AddComponent(healthObsComp2);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x * 0.6f, RENDERER.GetCurrentWindowDimensions().y * 0.9f, 0);
	go->SetTransform(pos);
	//QBert (health comp)
	auto health2 = scene.CreateGameObjectInScene("Player 2");
	scene.Add(health2);
	auto healthComp2 = std::make_shared<HealthComponent>();
	health2->AddComponent(healthComp2);
	healthComp2->AddObserver(healthObsComp2);
	healthComp2->SetLives(3);

	//Score observer
	go = scene.CreateGameObjectInScene("QBertScoreObserver");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("Score: -");
	go->AddComponent(textComp);
	auto scoreObsComp2 = std::make_shared<ScoreObserverComponent>();
	scoreObsComp2->SetTextComponent(textComp);
	go->AddComponent(scoreObsComp2);
	pos.SetPosition(RENDERER.GetCurrentWindowDimensions().x * 0.6f, RENDERER.GetCurrentWindowDimensions().y * 0.8f, 0);
	go->SetTransform(pos);
	//Score subject
	auto score2 = scene.CreateGameObjectInScene("QBertScoreSubject");
	auto scoreComp2 = std::make_shared<ScoreComponent>();
	scoreComp2->AddObserver(scoreObsComp2);
	scoreComp2->SetScore(0);
	score2->AddComponent(scoreComp2);
#pragma endregion

	//Buttons
	auto buttons = scene.CreateGameObjectInScene("buttons");
	auto uiComp = std::make_shared<RenderComponentUI>();
	uiComp->SetRenderFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.99, 0.05 }, CreateCommand(ActivateMenu), "Menu"));
	buttons->AddComponent(uiComp);

	//player 1
	uiComp = std::make_shared<RenderComponentUI>();
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.15, 0.3 }, CreateCommandToObject(Kill, health1), "Player 1:\nKill"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.35, 0.3 }, CreateCommandToObject(Respawn, health1), "Player 1:\nRespawn"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.15, 0.4 }, CreateCommandToObject(ChangeColor, score1), "Player 1:\nOn ChangeColor"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.15, 0.5 }, CreateCommandToObject(DefeatCoilyWithFlyingDisc, score1), "Player 1:\nOn Defeat Coily with flying disc"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.15, 0.6 }, CreateCommandToObject(RemainingDiscsAtTheEndOfAStage, score1), "Player 1:\nOn Remaining Discs At End Of Stage"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.15, 0.7 }, CreateCommandToObject(CatchSlickAndSam, score1), "Player 1:\nOn Catch Slick And Sam"));
	buttons->AddComponent(uiComp);

	//player 2
	uiComp = std::make_shared<RenderComponentUI>();
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.65, 0.3 }, CreateCommandToObject(Kill, health2), "Player 2:\nKill"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.85, 0.3 }, CreateCommandToObject(Respawn, health2), "Player 2:\nRespawn"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.65, 0.4 }, CreateCommandToObject(ChangeColor, score2), "Player 2:\nOn ChangeColor"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.65, 0.5 }, CreateCommandToObject(DefeatCoilyWithFlyingDisc, score2), "Player 2:\nOn Defeat Coily with flying disc"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.65, 0.6 }, CreateCommandToObject(RemainingDiscsAtTheEndOfAStage, score2), "Player 2:\nOn Remaining Discs At End Of Stage"));
	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.65, 0.7 }, CreateCommandToObject(CatchSlickAndSam, score2), "Player 2:\nOn Catch Slick And Sam"));
	buttons->AddComponent(uiComp);
}

void InitSceneVersus()
{
	using namespace dae;
	Transform pos{};
	auto& scene = SceneManager::GetInstance().CreateScene("Versus", false);

	//Background
	std::shared_ptr<GameObject> go = scene.CreateGameObjectInScene("Background");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	go->AddComponent(std::make_shared<TextureComponent>(RESOURCEMANAGER.LoadTexture("background.jpg")));

	//Title
	go = scene.CreateGameObjectInScene("Title");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	auto textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 36));
	textComp->SetText("Versus");
	go->AddComponent(textComp);
	pos.SetPosition(80, 20, 0);
	go->SetTransform(pos);

	//FPS Counter
	go = scene.CreateGameObjectInScene("FPS");
	go->AddComponent(std::make_shared<RenderComponent2D>());
	textComp = std::make_shared<TextComponent>(RESOURCEMANAGER.LoadFont("Lingua.otf", 20));
	textComp->SetText("FPS: -");
	go->AddComponent(textComp);
	auto FPSComp = std::make_shared<FPSComponent>();
	FPSComp->SetTextComponent(textComp);
	go->AddComponent(FPSComp);
	pos.SetPosition(0, 0, 0);

	//Buttons
	auto buttons = scene.CreateGameObjectInScene("buttons");
	auto uiComp = std::make_shared<RenderComponentUI>();
	uiComp->SetRenderFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);

	uiComp->AddUIElement(std::make_shared<UIButton>(glm::vec2{ 0.99, 0.05 }, CreateCommand(ActivateMenu), "Menu"));
	buttons->AddComponent(uiComp);
}