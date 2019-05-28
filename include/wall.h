#pragma once

#include <SFML/Graphics.hpp>



class Wall
{
public:
    Wall(const sf::Vector2i& top_left, const sf::Vector2i& bottom_right);
    virtual ~Wall() = default;

    bool CheckIsCellInWall(const sf::Vector2i& point) const;

    void Update(const float dt);
    void Render(sf::RenderWindow& window);


private:
    sf::Vector2i top_left_;
    sf::Vector2i bottom_right_;

    sf::RectangleShape shape_;
};

