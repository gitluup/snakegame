#include <cassert>

#include "wall.h"



extern const int BLOCK_SIZE;



Wall::Wall(const sf::Vector2i& top_left, const sf::Vector2i& bottom_right)
    : top_left_(top_left)
    , bottom_right_(bottom_right)
{
    assert(top_left.x <= bottom_right.x);
    assert(top_left.y <= bottom_right.y);
}



bool Wall::CheckIsCellInWall(const sf::Vector2i& point) const
{
    if (top_left_.x <= point.x && point.x <= bottom_right_.x &&
        top_left_.y <= point.y && point.y <= bottom_right_.y)
    {
        return true;
    }

    return false;
}



void Wall::Update(const float dt)
{
}



void Wall::Render(sf::RenderWindow& window)
{
    shape_.setPosition(
        static_cast<float>(top_left_.x * BLOCK_SIZE),
        static_cast<float>(top_left_.y * BLOCK_SIZE)
    );

    shape_.setSize(sf::Vector2f(
        static_cast<float>((bottom_right_.x + 1 - top_left_.x) * BLOCK_SIZE),
        static_cast<float>((bottom_right_.y + 1 - top_left_.y) * BLOCK_SIZE)
    ));

    shape_.setFillColor(sf::Color::Magenta);

    window.draw(shape_);
}

