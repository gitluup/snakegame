#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "event_manager.h"
#include "snake.h"
#include "apple.h"
#include "wall.h"



class World
{
    friend class Game;

public:
    World(const sf::Vector2i& window_sizes, EventManager& event_manager);
    virtual ~World() = default;

    enum class Event
    {
        CollisionWithWall,
        CollisionWithSnake,
        CollisionWithApple
    };

    void Create();

    void Update(const float dt);
    void Render(sf::RenderWindow& window);


private:
    void AddNewEvent(const Event event_type);

    void HandleCollisions();
    sf::Vector2i FindRandomFreeCell() const;
    bool CheckIsCellInWalls(const sf::Vector2i& cell) const;
    bool CheckIsCellInSnake(const sf::Vector2i& cell) const;

    sf::Vector2i world_sizes_;

    std::vector<Event> events_;

    Snake snake_;
    Apple apple_;
    std::vector<Wall> walls_;
};

