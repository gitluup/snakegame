#include <cmath>
#include <utility>
#include <cassert>

#include "snake.h"
#include "event_manager.h"



extern const int BLOCK_SIZE;
extern const sf::Vector2i WORLD_SIZES;



Snake::Snake(EventManager& event_manager)
{
    std::function<void(const sf::Event&)> callback = std::bind(
        &Snake::HandleEvent, this,
        std::placeholders::_1
    );
    event_manager.Subscribe(
        sf::Event::KeyPressed,
        callback
    );
}



void Snake::Create(const sf::Vector2i& new_position)
{
    assert(0 <= new_position.x && new_position.x < WORLD_SIZES.x);
    assert(0 <= new_position.y && new_position.y < WORLD_SIZES.y);

    body_.clear();
    Spawn(new_position);

    lives_ = 3;
    speed_ = 10;
    score_ = 0;
}



void Snake::Spawn(const sf::Vector2i& new_position)
{
    assert(0 <= new_position.x && new_position.x < WORLD_SIZES.x);
    assert(0 <= new_position.y && new_position.y < WORLD_SIZES.y);

    body_.clear();
    body_.push_back(Segment{
        new_position,
        sf::RectangleShape(),
        sf::Color::Yellow
    });

    prev_tail_position_ = body_.back().position;
    direction_ = Direction::None;
}



sf::Vector2i Snake::GetHeadPosition() const
{
    assert(!body_.empty());
    return body_.front().position;
}



const std::vector<Snake::Segment>& Snake::GetBody() const
{
    return body_;
}



int Snake::GetSpeed() const
{
    return speed_;
}



void Snake::IncreaseSpeed(const int delta)
{
    speed_ += delta;
}



int Snake::GetLivesNumber() const
{
    return lives_;
}



void Snake::DecreaseLivesNumber()
{
    lives_--;
}



int Snake::GetScore() const
{
    return score_;
}



void Snake::IncreaseScore(const int delta)
{
    score_ += delta;
}



void Snake::DeleteBody()
{
    body_.clear();
}



void Snake::Grow()
{
    assert(!body_.empty());

    body_.push_back(Segment{
        prev_tail_position_,
        sf::RectangleShape(),
        sf::Color::Green
    });
}



void Snake::HandleEvent(const sf::Event& event)
{
    assert(event.type == sf::Event::KeyPressed);

    switch (event.key.code)
    {
        case sf::Keyboard::Up:
            new_directions_.push(Direction::Up);
            break;

        case sf::Keyboard::Right:
            new_directions_.push(Direction::Right);
            break;

        case sf::Keyboard::Down:
            new_directions_.push(Direction::Down);
            break;

        case sf::Keyboard::Left:
            new_directions_.push(Direction::Left);
            break;

        default:;
    }
}



void Snake::Update(const float dt)
{
    assert(!body_.empty());
    
    time_since_last_move_ += dt;
    const float one_move_time = 1.0f / static_cast<float>(speed_);
    while (time_since_last_move_ >= one_move_time)
    {
        SetNewDirection();
        if (direction_ != Direction::None)
        {
            MoveByOneCell();
        }

        time_since_last_move_ -= one_move_time;
    }
}



void Snake::SetNewDirection()
{
    while (!new_directions_.empty())
    {
        const Direction trial_new_direction = new_directions_.front();
        new_directions_.pop();

        if (trial_new_direction == Direction::Up &&
            direction_ != Direction::Up && direction_ != Direction::Down)
        {
            direction_ = Direction::Up;
            break;
        }

        if (trial_new_direction == Direction::Right &&
            direction_ != Direction::Right && direction_ != Direction::Left)
        {
            direction_ = Direction::Right;
            break;
        }

        if (trial_new_direction == Direction::Down &&
            direction_ != Direction::Down && direction_ != Direction::Up)
        {
            direction_ = Direction::Down;
            break;
        }

        if (trial_new_direction == Direction::Left &&
            direction_ != Direction::Left && direction_ != Direction::Right)
        {
            direction_ = Direction::Left;
            break;
        }
    }
}



void Snake::MoveByOneCell()
{
    assert(!body_.empty());
    assert(direction_ != Direction::None);

    prev_tail_position_ = body_.back().position;
    for (size_t i = body_.size() - 1; i > 0; i--)
    {
        body_[i].position = body_[i - 1].position;
    }

    Segment& head = body_.front();
    switch (direction_)
    {
        case Direction::Up:
            head.position.y--;
            break;

        case Direction::Right:
            head.position.x++;
            break;

        case Direction::Down:
            head.position.y++;
            break;

        case Direction::Left:
            head.position.x--;
            break;
    }
}



bool Snake::CheckSelfCollision() const
{
    const Segment& head = body_.front();

    for (size_t i = 1; i < body_.size(); i++)
    {
        if (head.position == body_[i].position)
        {
            return true;
        }
    }

    return false;
}



void Snake::Render(sf::RenderWindow& window)
{
    if (body_.empty())
    {
        return;
    }

    for (size_t i = 0; i < body_.size(); i++)
    {
        if (i == 0)
        {
            body_[i].shape.setFillColor(sf::Color::Yellow);
        }
        else
        {
            body_[i].shape.setFillColor(sf::Color::Green);
        }

        const float padding = 0.5f;  // in pixels
        body_[i].shape.setPosition(
            static_cast<float>(body_[i].position.x * BLOCK_SIZE) + padding,
            static_cast<float>(body_[i].position.y * BLOCK_SIZE) + padding
        );
        body_[i].shape.setSize(sf::Vector2f(
            static_cast<float>(BLOCK_SIZE) - 2.0f * padding,
            static_cast<float>(BLOCK_SIZE) - 2.0f * padding
        ));
        window.draw(body_[i].shape);
    }
}


