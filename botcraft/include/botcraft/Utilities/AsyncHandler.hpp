#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    // A proxy handler that duplicate every packets and resend them
    // asynchronously to a main handler on another thread
    class AsyncHandler : public ProtocolCraft::Handler
    {
    public:
        AsyncHandler(ProtocolCraft::Handler* handler);
        AsyncHandler() = delete;
        ~AsyncHandler();

    protected:
        virtual void Handle(ProtocolCraft::Message& msg) override;

    private:
        void DequeueMsg();
    private:
        std::thread processing_thread;
        std::queue<std::shared_ptr<ProtocolCraft::Message> > msg_to_process;
        std::mutex processing_mutex;
        std::condition_variable processing_condition_variable;
        bool processing;

        ProtocolCraft::Handler* main_handler;
    };
}