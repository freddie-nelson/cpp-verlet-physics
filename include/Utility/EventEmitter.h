#pragma once

#include <string>
#include <functional>
#include <unordered_map>

template <typename T>
class EventEmitter
{
public:
    EventEmitter();

    void on(std::string event, std::function<void(T)> listener);
    void emit(std::string event, T data);

private:
    std::unordered_map<std::string, std::vector<std::function<void(T)>>> listeners;
};

template <typename T>
EventEmitter<T>::EventEmitter()
{
}

template <typename T>
void EventEmitter<T>::on(std::string event, std::function<void(T)> listener)
{
    if (!listeners[event])
    {
        listeners[event] = std::vector<std::function<void(T)>>();
    }

    listeners[event].push_back(listener);
}

template <typename T>
void EventEmitter<T>::emit(std::string event, T data)
{
    for (auto listener : listeners[event])
    {
        listener(data);
    }
}