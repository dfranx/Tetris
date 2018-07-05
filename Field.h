#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>
#include "Settings.h"
#include "Block.h"

namespace te
{
	class Field
	{
	public:
		Field(int tileSize);

		void SetPosition(int x, int y);
		void Spawn(Block::Type t);
		void PlaceBlock();
		inline std::queue<Block::Type> GetQueue() { return queue; }
		void Reset();

		void OnEvent(sf::Event e);
		void OnUpdate();
		void Render(sf::RenderTarget& wnd);

	private:
		sf::VertexBuffer grid;
		sf::RenderStates position;
		int translateX, translateY, tileSize;
		Block::Type map[FIELD_WIDTH][FIELD_HEIGHT];
			
		std::queue<Block::Type> queue;
		Block::Type current;
		int currentRotation = 0;
		int blockOffset = 3;
		int blockHeight = -4;

		bool checkLeftBounds();
		bool checkRightBounds();
		inline Block::Type getRandomBlock() { return (Block::Type)(rand() % Block::Type::Count); }
	};
}