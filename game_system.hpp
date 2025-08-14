#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ship.hpp"

struct GameSystem{
    static std::vector<Ship *> ships;
    static sf::Texture spritesheet;

    static void Load();
    static void Clean();
    static void Update(sf::RenderWindow &window);
    static void Render(sf::RenderWindow &window);
};