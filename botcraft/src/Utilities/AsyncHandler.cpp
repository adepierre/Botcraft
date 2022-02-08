#include <stdexcept>

#include "botcraft/Utilities/AsyncHandler.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    AsyncHandler::AsyncHandler(ProtocolCraft::Handler* handler)
    {
        if (handler == nullptr)
        {
            throw(std::runtime_error("Trying to assign a nullptr to AsyncHandler"));
            return;
        }
        main_handler = handler;

        processing = true;
        processing_thread = std::thread(&AsyncHandler::DequeueMsg, this);
    }

    AsyncHandler::~AsyncHandler()
    {
        processing = false;
        processing_condition_variable.notify_all();

        if (processing_thread.joinable())
        {
            processing_thread.join();
        }
    }

    void AsyncHandler::Handle(ProtocolCraft::Message& msg)
    {
        std::unique_lock<std::mutex> lck(processing_mutex);
        msg_to_process.push(msg.Clone());
        processing_condition_variable.notify_all();
    }

    void AsyncHandler::DequeueMsg()
    {
        Logger::GetInstance().RegisterThread("AsyncHandlerMsgProcessing");
        while (processing)
        {
            // Wait for the signal that there is
            // some chunk data
            {
                std::unique_lock<std::mutex> lck(processing_mutex);
                processing_condition_variable.wait(lck);
            }
            while (!msg_to_process.empty())
            {
                std::shared_ptr<ProtocolCraft::Message> msg;
                // Get the data from the queue
                {
                    std::lock_guard<std::mutex> process_guard(processing_mutex);
                    msg = std::move(msg_to_process.front());
                    msg_to_process.pop();
                }

                msg->Dispatch(main_handler);
            }
        }
    }


}