#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>



class EventManager
{
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    using SubscriptionID = int;

    SubscriptionID Subscribe(
        const sf::Event::EventType event_type,
        std::function<void(const sf::Event&)> callback
    );
    bool Unsubscribe(
        const sf::Event::EventType event_type,
        const SubscriptionID subscription_id
    );

    void HandleEvent(const sf::Event& event);
    void Update() const;


private:
    struct Subscription
    {
        SubscriptionID id;
        std::function<void(const sf::Event&)> callback;
    };

    SubscriptionID next_subscription_id_ = 0;

    std::unordered_map<
        sf::Event::EventType, std::vector<Subscription>
    > subscriptions_;
};

