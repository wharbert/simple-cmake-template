#pragma once

#include "engine/core/EventHandler.hpp"
#include "engine/core/Events.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>


class EventManager {
public:
    using Callback = EventHandler::Callback;

    void Init();
    void Subscribe(const EventId id,Callback callback);
    void Unsubscribe(const EventId id, Callback callback);
    void Notify(std::shared_ptr<EventData> event);
    void SetLogger(std::string log);

private:
    std::unordered_map<EventId, std::vector<Callback>> handlers;
    std::string m_log;
};

