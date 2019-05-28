#include <cassert>

#include "apple.h"
#include "event_manager.h"



extern const int BLOCK_SIZE;
extern const sf::Vector2i WORLD_SIZES;



Apple::Apple(EventManager& event_manager)
{
}



void Apple::Create(const sf::Vector2i& new_position)
{
    Spawn(new_position);
}



void Apple::Spawn(const sf::Vector2i& new_position)
{
    position_ = new_position;
}



sf::Vector2i Apple::GetPosition() const
{
    return position_;
}



void Apple::HandleEvent(const sf::Event& event)
{
}



void Apple::Update(const float dt)
{
}



void Apple::Render(sf::RenderWindow& window)
{
    shape_.setPosition(sf::Vector2f(
        static_cast<float>(position_.x * BLOCK_SIZE),
        static_cast<float>(position_.y * BLOCK_SIZE)
    ));
    shape_.setRadius(static_cast<float>(BLOCK_SIZE) / 2.0f);

    shape_.setFillColor(sf::Color::Red);

    window.draw(shape_);
}
