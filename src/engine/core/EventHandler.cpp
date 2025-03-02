#include "EventHandler.hpp"
#include "engine/managers/EventManager.hpp"
#include "engine/core/Engine.hpp"
#include <optional>
#include <memory>

void EventHandler::Subscribe(const EventId id) {
    EVENTMAN.Subscribe(id, [this](std::shared_ptr<EventData> event) { this->QueueEvent(event); });
}

void EventHandler::QueueEvent(std::shared_ptr<EventData> event) {
    m_eventQueue.push(event);        
}

std::optional<std::shared_ptr<EventData>> EventHandler::GetEvent() {
    if (!m_eventQueue.empty()) {
        auto ret = m_eventQueue.front();
        m_eventQueue.pop();
        return ret;
    }
    return std::nullopt;
}