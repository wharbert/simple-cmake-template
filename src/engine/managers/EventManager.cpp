#include "EventManager.hpp"
#include "engine/core/Events.hpp"
#include "engine/core/Logger.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>
#include "engine/core/Engine.hpp"


void EventManager::Init() 
{
    SetLogger("CORE");
}

void EventManager::Subscribe(const EventId id,Callback callback) {
    handlers[id].push_back(callback);
    LOG_TRACE(m_log, "Subscribed Listener : {}", Events::EventMap[id]);
}

void EventManager::Unsubscribe(const EventId id, Callback callback){
    //NYI - More complicated than anticipated 
}

void EventManager::Notify(std::shared_ptr<EventData> event) {
    LOG_TRACE(m_log,"Published Event : {}", Events::EventMap[event->id]);
    auto it = handlers.find(event->id);
    if (it != handlers.end()) {
        for (const auto& handler : it->second) {
            handler(event);
        }
    }
}

void EventManager::SetLogger(std::string log)
{
    assert(log != "");
    m_log = log;
}
