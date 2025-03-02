#pragma once

#include "Events.hpp"
#include <functional>
#include <queue>
#include <optional>
#include <memory>

class EventHandler {
public:
    using Callback = std::function<void(std::shared_ptr<EventData>)>;

    void Subscribe(const EventId id);

    void QueueEvent(std::shared_ptr<EventData> event);

    std::optional<std::shared_ptr<EventData>> GetEvent();

private:
    std::queue<std::shared_ptr<EventData>> m_eventQueue;
};


