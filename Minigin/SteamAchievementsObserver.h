#pragma once
#include "Observer.h"

namespace dae
{
	class CSteamAchievements;
	class TextComponent;
	class SteamAchievementsObserver final : public Observer
	{
	public:
		explicit SteamAchievementsObserver(CSteamAchievements* steamAchievements);

		~SteamAchievementsObserver() override = default;
		SteamAchievementsObserver(const SteamAchievementsObserver& other) = delete;
		SteamAchievementsObserver(SteamAchievementsObserver&& other) = delete;
		SteamAchievementsObserver& operator=(const SteamAchievementsObserver& other) = delete;
		SteamAchievementsObserver& operator=(SteamAchievementsObserver&& other) = delete;

		void OnNotify(BaseComponent* component, Event event) override;

	private:
		CSteamAchievements* m_SteamAchievements;

	};
}
