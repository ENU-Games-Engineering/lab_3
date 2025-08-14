#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
    sf::IntRect _sprite;
    //Default constructor is hidden
    Ship();

    bool _exploded = false;
public:
    //Constructor that takes a sprite
    explicit Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float &dt);
    virtual void Explode();
    virtual void move_down();

    bool is_exploded() const;
    
    float explosion_time = 0.1f;

    constexpr static int width = 32;
    constexpr static int height = 32;
};

class Invader : public Ship {
public:
    Invader(sf::IntRect ir, sf::Vector2f pos);
    Invader();
    void Update(const float &dt) override;

    static bool direction;
    static float speed;
    static float firetime;


    constexpr static int spacing = 18;
    constexpr static int rows = 5;
    constexpr static int columns = 12;
    constexpr static int down = 24;
    constexpr static float acc = 10.f;
};

class Player : public Ship {
public:
  Player();
  void Update(const float &dt) override;
  void move_down() override{}
  static float firetime;

  constexpr static uint16_t speed = 100.f;
};
