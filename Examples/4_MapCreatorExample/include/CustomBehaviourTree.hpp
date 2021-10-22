#pragma once

#include <botcraft/AI/BehaviourTree.hpp>

/// <summary>
/// A Decorator that ticks its child until
/// it successes. If ticked n times with no
/// success, return failure.
/// </summary>
/// <typeparam name="Context">The tree context type</typeparam>
template<class Context>
class RepeatUntilSuccess : public Botcraft::AI::Decorator<Context>
{
public:
    RepeatUntilSuccess(const size_t n_)
    {
        n = n_;
    }

    virtual const Botcraft::AI::Status Tick(Context& context) const override
    {
        for (size_t i = 0; i < n; ++i)
        {
            Botcraft::AI::Status child_return = child->Tick(context);
            if (child_return == Botcraft::AI::Status::Success)
            {
                return Botcraft::AI::Status::Success;
            }
        }
        return Botcraft::AI::Status::Failure;
    }

private:
    size_t n;
};