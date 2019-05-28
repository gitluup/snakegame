#include "message_box.h"



MessageBox::MessageBox(
    const sf::Vector2i& position, const sf::Vector2i& sizes,
    const int char_size)
{
    font_.loadFromFile("../data/fonts/FreeSerif.ttf");
    all_messages_.setFont(font_);

    Setup(position, sizes, char_size);
}



void MessageBox::Setup(
    const sf::Vector2i& position, const sf::Vector2i& sizes,
    const int char_size)
{
    background_.setPosition(
        static_cast<float>(position.x),
        static_cast<float>(position.y)
    );
    background_.setSize(sf::Vector2f(
        static_cast<float>(sizes.x),
        static_cast<float>(sizes.y)
    ));
    background_.setFillColor(sf::Color(16, 16, 16));

    all_messages_.setPosition(
        static_cast<float>(position.x) + text_padding_,
        static_cast<float>(position.y) + text_padding_
    );
    all_messages_.setCharacterSize(char_size);
    all_messages_.setFillColor(sf::Color::White);
}



void MessageBox::Add(const std::string& message)
{
    messages_.push_back(message);
}



void MessageBox::Clear()
{
    messages_.clear();
}



void MessageBox::Update()
{
    const float vertical_size = background_.getSize().y;  // in pixels
    const float line_height = font_.getLineSpacing(  // in pixels
        all_messages_.getCharacterSize()
    );
    const size_t visible_messages_count = static_cast<size_t>(
        (vertical_size - 2.0f * text_padding_) / line_height
    );

    while (messages_.size() > visible_messages_count)
    {
        messages_.erase(messages_.begin());
    }
}



void MessageBox::Render(sf::RenderWindow& window)
{
    window.draw(background_);

    std::string all_visible_messages;
    for (const std::string& message : messages_)
    {
        all_visible_messages += (message + "\n");
    }

    all_messages_.setString(all_visible_messages);
    window.draw(all_messages_);
}

