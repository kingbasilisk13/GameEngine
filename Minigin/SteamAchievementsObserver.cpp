#include "SteamAchievementsObserver.h"

#include "CSteamAchievements.h"
#include "ScoreComponent.h"

dae::SteamAchievementsObserver::SteamAchievementsObserver(CSteamAchievements* steamAchievements)
: m_SteamAchievements(steamAchievements)
{
}

void dae::SteamAchievementsObserver::OnNotify(BaseComponent* component, Event event)
{
	switch (event) {
	case Event::ScoreIncreased:

		if (dynamic_cast<ScoreComponent*>(component)->GetScore() >= 500)
		{
			m_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
		}
		break;
	default: ;
	}
}
