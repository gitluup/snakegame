#include "world.h"



extern const sf::Vector2i WORLD_SIZES;
extern const int BLOCK_SIZE;



World::World(const sf::Vector2i& world_size, EventManager& event_manager)
    : world_sizes_(WORLD_SIZES)
    , snake_(event_manager)
    , apple_(event_manager)
{
    Create();
}



void World::Create()
{
    walls_.push_back(Wall(
        { 0, 0 },
        { world_sizes_.x - 1, 0 }
    ));
    walls_.push_back(Wall(
        { 0, 0 },
        { 0, world_sizes_.y - 1 }
    ));
    walls_.push_back(Wall(
        { 0, world_sizes_.y - 1 },
        { world_sizes_.x - 1, world_sizes_.y - 1 }
    ));
    walls_.push_back(Wall(
        { world_sizes_.x - 1, 0 },
        { world_sizes_.x - 1, world_sizes_.y - 1 }
    ));

    apple_.Create(FindRandomFreeCell());
    snake_.Create(FindRandomFreeCell());
}



void World::Update(const float dt)
{
    events_.clear();
    HandleCollisions();

    apple_.Update(dt);
    snake_.Update(dt);
    for (Wall& wall : walls_)
    {
        wall.Update(dt);
    }
}



void World::Render(sf::RenderWindow& window)
{
    sf::RectangleShape cell_shape;
    cell_shape.setSize(sf::Vector2f(
        static_cast<float>(BLOCK_SIZE),
        static_cast<float>(BLOCK_SIZE)
    ));

    for (int x = 0; x < WORLD_SIZES.x; x++)
    {
        for (int y = 0; y < WORLD_SIZES.y; y++)
        {
            if ((x + y) % 2 == 1)
            {
                cell_shape.setFillColor(sf::Color(0, 0, 0));
            }
            else
            {
                cell_shape.setFillColor(sf::Color(16, 16, 16));
            }

            cell_shape.setPosition(
                static_cast<float>(x * BLOCK_SIZE),
                static_cast<float>(y * BLOCK_SIZE)
            );
            window.draw(cell_shape);
        }
    }

    for (Wall& wall : walls_)
    {
        wall.Render(window);
    }

    apple_.Render(window);
    snake_.Render(window);
}



void World::HandleCollisions()
{
    if (snake_.CheckSelfCollision())
    {
        snake_.DeleteBody();
        snake_.Spawn(FindRandomFreeCell());
        apple_.Spawn(FindRandomFreeCell());
        snake_.DecreaseLivesNumber();
        events_.push_back(Event::CollisionWithSnake);
    }

    for (Wall& wall : walls_)
    {
        if (wall.CheckIsCellInWall(snake_.GetHeadPosition()))
        {
            snake_.DeleteBody();
            snake_.Spawn(FindRandomFreeCell());
            apple_.Spawn(FindRandomFreeCell());
            snake_.DecreaseLivesNumber();
            events_.push_back(Event::CollisionWithWall);
        }
    }

    if (snake_.GetHeadPosition() == apple_.GetPosition())
    {
        snake_.Grow();
        apple_.Spawn(FindRandomFreeCell());
        snake_.IncreaseScore(10);
        snake_.IncreaseSpeed(1);
        events_.push_back(Event::CollisionWithApple);
    }
}



sf::Vector2i World::FindRandomFreeCell() const
{
    const int max_iter_number = 1000;
    for (int i = 0; i < max_iter_number; i++)
    {
        const sf::Vector2i random_cell_position(
            std::rand() % world_sizes_.x,
            std::rand() % world_sizes_.y
        );

        if (!CheckIsCellInWalls(random_cell_position) &&
            !CheckIsCellInSnake(random_cell_position) &&
            random_cell_position != apple_.GetPosition())
        {
            return random_cell_position;
        }
    }

    // We haven't found any free cell. Maybe all cells are busy?
    // Now we are going to find a free cell by checking all existing cells.
    for (int x = 0; x < WORLD_SIZES.x; x++)
    {
        for (int y = 0; y < WORLD_SIZES.y; y++)
        {
            const sf::Vector2i checking_cell(x, y);
            if (!CheckIsCellInWalls(checking_cell) &&
                !CheckIsCellInSnake(checking_cell) &&
                checking_cell != apple_.GetPosition())
            {
                return checking_cell;
            }
        }
    }

    const int poison_coord = -1;
    return sf::Vector2i(poison_coord, poison_coord);
}



bool World::CheckIsCellInWalls(const sf::Vector2i& cell) const
{
    for (const Wall& wall : walls_)
    {
        if (wall.CheckIsCellInWall(cell))
        {
            return true;
        }
    }

    return false;
}



bool World::CheckIsCellInSnake(const sf::Vector2i& cell) const
{
    const auto& snake_body = snake_.GetBody();
    for (const auto& snake_segment : snake_body)
    {
        if (snake_segment.position == cell)
        {
            return true;
        }
    }

    return false;
}

