#include <iostream>

#include "botcraft/AI/AsyncTask.hpp"

namespace Botcraft::AI
{
    AsyncTask::AsyncTask()
    {
        quit = false;
    }

    AsyncTask::~AsyncTask()
    {
        Stop();
    }

    Status AsyncTask::Step()
    {
        // No valid future, starting the task
        if (!future.valid())
        {
            Start();
            return Status::Running;
        }
        // Thread has finished, returning the final value
        else if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        {
            if (thread->joinable())
            {
                thread->join();
            }

            Status return_value = future.get();
            future = std::future<Status>();

            return return_value;
        }
        // Still processing
        else
        {
            std::unique_lock<std::mutex> lock(mutex);
            if (!quit)
            {
                // Resume Process()
                cond_var.notify_all();
                // Wait for the next call to Yield() or
                // the end of Run()
                cond_var.wait(lock);
            }
            return Status::Running;
        }
    }

    void AsyncTask::Stop()
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            quit = true;
        }
        cond_var.notify_all();
        thread->join();
    }

    void AsyncTask::Yield()
    {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.notify_all();
        cond_var.wait(lock);
        if (quit)
        {
            throw InterruptedException();
        }
    }

    void AsyncTask::Initialize()
    {

    }

    void AsyncTask::Finalize()
    {
    }

    Status AsyncTask::Run()
    {
        Initialize();
        try
        {
            Process();
        }
        catch (InterruptedException& e)
        {
            Finalize();
            return Status::Failure;
        }
        std::lock_guard<std::mutex> lock(mutex);
        Finalize();
        quit = true;
        cond_var.notify_all();
        return Status::Success;
    }

    void AsyncTask::Start()
    {
        // Already running, we need to Stop the execution first
        // (should not happen as Start is not public)
        if (future.valid())
        {
            Stop();
        }

        std::unique_lock<std::mutex> lock(mutex);
        quit = false;
        std::packaged_task<Status()> task(std::bind(&AsyncTask::Run, this));
        future = task.get_future();
        thread.reset(new std::thread(std::move(task)));
        cond_var.wait(lock);
    }
}
