#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "ship.hpp"

sf::Texture spritesheet;

int main(){
  sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "SPACE Invaders");
  
  GameSystem::Load();
	while(window.isOpen()){
		window.clear();
		GameSystem::Update(window);
		GameSystem::Render(window);
		//Wait for Vsync
    window.display();
	}
  GameSystem::Clean();
  return 0;
}
