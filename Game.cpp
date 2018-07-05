#include "Game.h"
#include "Settings.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace te
{
	Game::Game(int w, int h) :
		field((h - BG_MARGIN * 2) / FIELD_HEIGHT)
	{
		wndWidth = w;
		wndHeight = h;
	}
	void Game::OnEvent(sf::Event e)
	{
		if (e.type == sf::Event::KeyPressed) {
			sf::Keyboard::Key kc = e.key.code;

			if (kc == sf::Keyboard::Down || kc == sf::Keyboard::S)
				updateSpeed = NORMAL_SPEED / SPEED_UP_DIVIDER;
		} else if (e.type == sf::Event::KeyReleased) {
			sf::Keyboard::Key kc = e.key.code;

			if (kc == sf::Keyboard::Down || kc == sf::Keyboard::S)
				updateSpeed = NORMAL_SPEED;
		}

		field.OnEvent(e);
	}
	void Game::OnUpdate()
	{
		timePassed += fieldClock.restart().asSeconds();
		while (timePassed >= updateSpeed) {
			field.OnUpdate();
			timePassed -= updateSpeed;
		}
	}
	void Game::Render(sf::RenderTarget& wnd)
	{
		sf::RectangleShape bg;
		bg.setFillColor(sf::Color(30, 30, 30));

		// next figures bg
		bg.setPosition(BG_MARGIN, BG_MARGIN);
		bg.setSize(sf::Vector2f(1.f / 3.f * (wndWidth - BG_MARGIN*3), wndHeight - BG_MARGIN*2));
		wnd.draw(bg);

		// figure queue
		sf::Vector2f qOffset = bg.getPosition();
		std::queue<Block::Type> blocks = field.GetQueue();
		int queueTileSize = bg.getSize().x / 6.f; // 1 margin + 4 tiles + 1 margin == 6 (horizontal)
		int vertSlots = (bg.getSize().y / queueTileSize) / 5; // 1 margin + 4 tiles == 5 (vertical)
		for (int i = 0; i <= std::min<int>(vertSlots, QUEUE_SIZE); i++) {
			Block::Type type = blocks.front();
			blocks.pop();
			
			// simple hack to center all block types
			float multiplier = 1.f;
			if (type != Block::Type::I && type != Block::Type::O)
				multiplier = 0.5f;

			Block::Render(wnd, type, qOffset.x + queueTileSize * multiplier, qOffset.y + i * queueTileSize * 5, queueTileSize, 0);
		}

		// field bg
		bg.setPosition(20 + bg.getSize().x + BG_MARGIN, BG_MARGIN);
		bg.setSize(sf::Vector2f(2.f / 3.f * (wndWidth - BG_MARGIN*3), wndHeight - BG_MARGIN*2));
		wnd.draw(bg);

		// draw field
		field.SetPosition(bg.getPosition().x, bg.getPosition().y);
		field.Render(wnd);
	}
}