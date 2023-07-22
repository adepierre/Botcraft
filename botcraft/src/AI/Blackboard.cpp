#include "botcraft/AI/Blackboard.hpp"

namespace Botcraft
{
    Blackboard::Blackboard()
    {

    }

    Blackboard::~Blackboard()
    {

    }

    void Blackboard::Copy(const std::string& src, const std::string& dst)
    {
        const std::any& source = blackboard.at(src);
        blackboard[dst] = source;
        NotifyKeyChanged(dst, source);
    }

    void Blackboard::Erase(const std::string& key)
    {
        blackboard.erase(key);
        NotifyKeyRemoved(key);
    }

    void Blackboard::Reset(const std::map<std::string, std::any>& values)
    {
        blackboard.clear();
        NotifyCleared();
        for (const auto& [k, v] : values)
        {
            blackboard[k] = v;
            NotifyKeyChanged(k, v);
        }
    }

    void Blackboard::Subscribe(BlackboardObserver* observer)
    {
        observers.push_back(observer);
    }

    void Blackboard::Unsubscribe(BlackboardObserver* observer)
    {
        for (auto it = observers.begin(); it != observers.end(); )
        {
            if (*it == observer)
            {
                it = observers.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void Blackboard::NotifyCleared() const
    {
        for (auto o : observers)
        {
            if (o != nullptr)
            {
                o->OnReset();
            }
        }
    }

    void Blackboard::NotifyKeyRemoved(const std::string& key) const
    {
        for (auto o : observers)
        {
            if (o != nullptr)
            {
                o->OnValueRemoved(key);
            }
        }
    }

    void Blackboard::NotifyKeyChanged(const std::string& key, const std::any& value) const
    {
        for (auto o : observers)
        {
            if (o != nullptr)
            {
                o->OnValueChanged(key, value);
            }
        }
    }
}
