#pragma once

//todo: de feedback zegt van als je wilt sneller lopen als je bijvoorbeeld shift indrukt dat je een nieuw commando maakt dat de button combination gebruikt int plaats van enkel 1 key
//aka er is geen correcte manier denk er eens over na.

namespace dae
{
	class Command
	{
	public:
		Command() = default;

		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};
}