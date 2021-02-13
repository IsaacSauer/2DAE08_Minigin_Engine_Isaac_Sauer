#pragma once
#include <unordered_map>

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;

		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures{};
		std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts{};
	};

	//Macros
	#define RESOURCEMANAGER dae::ResourceManager::GetInstance()
}

