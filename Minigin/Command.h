#pragma once

//opmerking: command en component zijn 2 paterns die je niet mag mixen.
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