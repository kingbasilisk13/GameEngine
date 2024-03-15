//#pragma once
//#include "BaseComponent.h"
//
////opmerking: command en component zijn 2 paterns die je niet mag mixen.
//class Command
//{
//public:
//	virtual ~Command() = default;
//	virtual void Execute() = 0;
//};
//
//class GameActorCommand : public Command
//{
//	dae::BaseComponent* m_actor;
//protected:
//	dae::BaseComponent* GetGameActor() const { return m_actor; }
//public:
//	GameActorCommand(dae::BaseComponent* actor);
//	virtual ~GameActorCommand();
//};
//
//class Fire : public GameActorCommand
//{
//public:
//	void Execute() override
//	{
//		GetGameActor()->Fire();
//		// additional code is possible too, of course
//	}
//};

