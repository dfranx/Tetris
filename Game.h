#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Field.h"

namespace te
{
	class Game
	{
	public:
		Game(int w, int h);

		void OnEvent(sf::Event e);
		void OnUpdate();
		void Render(sf::RenderTarget& wnd);

	private:
		int wndWidth;
		int wndHeight;

		Field field;
		sf::Clock fieldClock;
		float updateSpeed = 0.20f; // NOTE: to future me, you could keep track of score and lower this value to speed up the gameplay
		float timePassed = 0.0f;
	};
}