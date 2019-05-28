#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "world.h"



class MessageBox
{
public:
    MessageBox(
        const sf::Vector2i& position, const sf::Vector2i& sizes,
        const int char_size
    );
    virtual ~MessageBox() = default;

    void Setup(
        const sf::Vector2i& position, const sf::Vector2i& sizes,
        const int char_size
    );
    void Add(const std::string& message);
    void Clear();

    void Update();
    void Render(sf::RenderWindow& window);


private:
    std::vector<std::string> messages_;

    sf::RectangleShape background_;
    sf::Font font_;
    sf::Text all_messages_;
    const float text_padding_ = 4.0f;  // in pixels
};

