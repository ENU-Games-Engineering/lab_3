#include <iostream>
#include "ship.hpp"
#include "game_system.hpp"
#include "game.hpp"
#include "bullet.hpp"

bool Invader::direction = true;
float Invader::speed = 10.f;
float Invader::firetime = 0.0f;
float Player::firetime = 0.0f;

Ship::Ship(){}

Ship::Ship(sf::IntRect ir) : sf::Sprite() {
  _sprite = ir;
  setTexture(spritesheet);
  setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {
    if(_exploded)
      explosion_time-=dt;
    if(explosion_time <= 0)
      setPosition(-100,-100);
}
void Ship::Explode() {
	setTextureRect(sf::IntRect(sf::Vector2i(128, 32), sf::Vector2i(32, 32)));
    _exploded = true;
}
//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

bool Ship::is_exploded() const {
  return _exploded;
}

void Ship::move_down(){
  move(sf::Vector2f(0.0f, Invader::down));
}

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(Ship::width/2.f, Ship::height/2.f);;
    setPosition(pos);
}

void Invader::Update(const float &dt) {
  Ship::Update(dt);

  if(_exploded)
    return;

  firetime -= dt;

  move(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f);
    
  if ((direction && getPosition().x > game_width - 16) ||
      (!direction && getPosition().x < 16)) {
        direction = !direction;
        speed += Invader::acc;
        for (Ship* ship: GameSystem::ships) {
					 ship->move_down();
        }
    }
    
    if (firetime <= 0 && rand() % 100 == 0) {
      Bullet::Fire(getPosition(), false);
      firetime = 4.0f + (rand() % 60);
    }

}

Player::Player() : 
  Ship(sf::IntRect(sf::Vector2i(160, 32), 
       sf::Vector2i(Ship::width, Ship::height))){
  setOrigin(Ship::width/2.f, Ship::height/2.f);;
  setPosition(game_width/2.f, game_height - static_cast<float>(Ship::height));
}

void Player::Update(const float &dt) {
    Ship::Update(dt);

    if(_exploded)
      return;

    firetime -= dt;

    //Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
        getPosition().x > Ship::width/2.f) {
        move(-speed*dt,0);
    }
    //Move Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        getPosition().x < game_width - Ship::width/2.f) {
        move(speed*dt,0);
    }

    if (firetime <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      Bullet::Fire(getPosition(), true);
      firetime = 0.7f;
    }
}