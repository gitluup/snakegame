#include "event_manager.h"



EventManager::SubscriptionID EventManager::Subscribe(
    const sf::Event::EventType event_type,
    std::function<void(const sf::Event&)> callback)
{
    const SubscriptionID subscription_id = next_subscription_id_;
    subscriptions_[event_type].push_back(Subscription{
        subscription_id,
        callback
    });

    next_subscription_id_++;
    return subscription_id;
}



bool EventManager::Unsubscribe(
    const sf::Event::EventType event_type,
    const SubscriptionID subscription_id)
{
    if (subscriptions_.count(event_type) == 0)
    {
        return false;
    }

    auto& event_subscriptions = subscriptions_.at(event_type);
    for (auto it = event_subscriptions.begin();
        it != event_subscriptions.end();
        it++)
    {
        if (it->id == subscription_id)
        {
            event_subscriptions.erase(it);
            return true;
        }
    }

    return false;
}



void EventManager::HandleEvent(const sf::Event& event)
{
    if (subscriptions_.count(event.type) == 0)
    {
        return;
    }

    for (const Subscription& subscription : subscriptions_.at(event.type))
    {
        subscription.callback(event);
    }
}



void EventManager::Update() const
{
}

