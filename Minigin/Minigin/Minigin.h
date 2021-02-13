#pragma once
#include <chrono>
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

	protected:
		friend class Timer;
		static const int MsPerUpdate = 2; //16 for 60 fps, 33 for 30 fps

	private:
		const std::chrono::duration<float> MsPerFrame = std::chrono::duration<float>(1000.0 / 60.0 / 1000.0);
		//static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps


		const float SecPerUpdate = 0.016f;
		SDL_Window* m_Window{};
	};
}