#include "EventSystem.h"

namespace Eagle
{
namespace Events
{
EventSystem *EventSystem::m_instance = nullptr;

std::once_flag  EventSystem::initInstanceFlag;

EventSystem::EventSystem()
{
}
}
}
