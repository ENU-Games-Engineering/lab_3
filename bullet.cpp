#include <iostream>
#include "bullet.hpp"
#include "game_parameters.hpp"
#include "game_system.hpp"

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet(){}

void Bullet::Update(const float &dt){
    for(int i = 0; i < 256; i++)
        bullets[i]._Update(dt);
}

void Bullet::Render(sf::RenderWindow &window){
    for(int i = 0; i < 256; i++)
        window.draw(bullets[i]);
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode){
    Bullet &bullet = bullets[++bulletPointer];
    if(mode)
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(32,32),sf::Vector2i(32,32)));
    else
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(64,32),sf::Vector2i(32,32)));
    bullet.setPosition(pos);
    bullet._mode = mode;
}
void Bullet::Init(){
    for(int i = 0; i < 256; i++){
        bullets[i].setTexture(GameSystem::spritesheet);
        bullets[i].setOrigin(Ship::width/2.f,Ship::height/2.f);
        bullets[i].setPosition(-100,-100);   
    }
}

void Bullet::_Update(const float &dt) {
    if (getPosition().y < -32 || getPosition().y > game_height + 32) {
        //off screen - do nothing
        return;
    } else {
        move(sf::Vector2f(0, dt * 200.0f * (_mode ? -1.0f : 1.0f)));
        const sf::FloatRect boundingBox = getGlobalBounds();
        Ship *player = GameSystem::ships[0];
        for (Ship *s : GameSystem::ships) {
            if (_mode && s == player) {
                //player bullets don't collide with player
                continue;
            }
            if (!_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() && 
                s->getGlobalBounds().intersects(boundingBox)) {
                  //Explode the ship
                  s->Explode();
                  //warp bullet off-screen
				  setPosition(sf::Vector2f(-100, -100));
                  return;
            }
        }
    }
};