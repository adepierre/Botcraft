#pragma once

#include <exception>
#include <memory>
#include <thread>
#include <mutex>
#include <future>

#include "botcraft/AI/BehaviourTree.hpp"

namespace Botcraft::AI
{
    class InterruptedException : public std::exception
    {
    };

    // This emulates coroutines using thread. 
    // Everytime Step() is called, Process will be
    // run. Execution is paused each time Yield
    // is called inside Process(), and resumes on the
    // next Step() call.
    class AsyncTask
    {
    public:
        AsyncTask();
        ~AsyncTask();

        // If the thread is not started, starts it
        // Runs the process function until it reaches a
        // Yield() call.
        Status Step();

        // Stop execution
        void Stop();

    protected:
        /// <summary>
        /// To be called in Process() to pause
        /// the execution until the next call
        /// to Step()
        /// </summary>
        void Yield();

        /// <summary>
        /// Overload with the logic, can call
        /// Yield() to pause the execution
        /// </summary>
        /// <returns>A Behaviour tree status</returns>
        virtual Status Process() = 0;

        /// <summary>
        /// Called once before the Process() function,
        /// can be used to initialize values
        /// </summary>
        virtual void Initialize();

        /// <summary>
        /// Called once after the Process() function,
        /// even if the execution was stopped using Stop()
        /// </summary>
        virtual void Finalize();

    private:
        /// <summary>
        /// Internal function called on the thread
        /// </summary>
        /// <returns>A behaviour tree status</returns>
        Status Run();

        /// <summary>
        /// Starts the internal thread
        /// </summary>
        void Start();

    private:
        std::unique_ptr<std::thread> thread;
        std::condition_variable cond_var;
        std::mutex mutex;
        std::future<Status> future;
        bool quit;
    };
} // namespace Botcraft::AI