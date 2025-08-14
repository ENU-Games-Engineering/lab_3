#include <iostream>
#include "game_system.hpp"
#include "game.hpp"
#include "bullet.hpp"

std::vector<Ship *> GameSystem::ships;

void GameSystem::Load() {
  if (!spritesheet.loadFromFile("/home/leni/git/set09121_labs/lab_3/resources/img/invaders_sheet.png")) {
    std::cerr << "Failed to load spritesheet!" << std::endl;
  }
  Bullet::Init();
  Ship *player = new Player();
  ships.push_back(player);
  for (int r = 0; r < Invader::rows; ++r) {
    sf::IntRect rect(sf::Vector2i(32*r, 0), sf::Vector2i(32, 32));
    for (int c = 0; c < Invader::columns; ++c) {
        sf::Vector2f position(c*(Ship::width+Invader::spacing)+Ship::width/2.f,
                              r*(Ship::height+Invader::spacing)+Ship::height/2.f);
        Invader *inv = new Invader(rect, position);
        ships.push_back(inv);
    }
  }
}

void GameSystem::Clean(){
  for(Ship *ship: ships)
    delete ship;
  ships.clear();
}

void GameSystem::Update(sf::RenderWindow &window){
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
        window.close();
        return;
    }
  }
  for (Ship *s : ships) 
    s->Update(dt);
  Bullet::Update(dt);
}

void GameSystem::Render(sf::RenderWindow &window){
    for (const Ship *s : ships) 
      window.draw(*s);
    Bullet::Render(window);
}
