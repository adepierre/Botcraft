#pragma once

#include "botcraft/AI/AsyncTask.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    class InterfaceClient;
}

namespace Botcraft::AI
{
    class Blackboard;

    // This emulates coroutines using thread. 
    // Everytime Step() is called, Process will be
    // run. Execution is paused each time Yield
    // is called inside Process(), and resumes on the
    // next Step() call.
    class PathfindingTask : public AsyncTask
    {
    public:
        PathfindingTask(InterfaceClient &client);
        PathfindingTask() = delete;
        PathfindingTask(const PathfindingTask&) = delete;
        ~PathfindingTask();

    protected:
        /// <summary>
        /// Overload with the logic, can call
        /// Yield() to pause the execution
        /// </summary>
        /// <returns>A Behaviour tree status</returns>
        virtual Status Process() override;

        /// <summary>
        /// Called once before the Process() function,
        /// can be used to initialize values
        /// </summary>
        virtual void Initialize() override;

        /// <summary>
        /// Called once after the Process() function,
        /// even if the execution was stopped using Stop()
        /// </summary>
        virtual void Finalize() override;

    private:
        /// <summary>
        /// Find a path between start and end as a succession of positions.
        /// Uses min_end_dist to check if we want to finish near the end
        /// but not inside it. If allow_jump is true, can jump above 1 wide gaps
        /// </summary>
        /// <param name="start">Start position</param>
        /// <param name="end">End position</param>
        /// <returns>The path, as a succession of pos to reach end from start</returns>
        const std::vector<Position> FindPath(const Position& start, const Position& end);

    private:
        Position goal;

        unsigned int dist_tolerance;
        unsigned int min_end_dist;
        float travel_speed;
        bool allow_jump;

        InterfaceClient& linked_client;
    };
} // namespace Botcraft::AI