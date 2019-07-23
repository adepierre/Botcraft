#pragma once

#include <tuple>

namespace Botcraft
{
    // This class is inspired by https://arobenko.gitbooks.io/comms-protocols-cpp/content/

    // TCommon is common interface class for all the messages
    // TAll is all the message types, that need to be handled, bundled in std::tuple
    template <typename TCommon, typename TAll>
    class GenericHandler;

    template <typename TCommon, typename TFirst, typename TSecond, typename TThird, typename... TRest>
    class GenericHandler<TCommon, std::tuple<TFirst, TSecond, TThird, TRest...> > : public GenericHandler<TCommon, std::tuple<TRest...> >
    {
        using Base = GenericHandler<TCommon, std::tuple<TRest...> >;
    public:
        using Base::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(TFirst &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
        virtual void Handle(TSecond &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
        virtual void Handle(TThird &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
    };

    template <typename TCommon, typename TFirst, typename TSecond>
    class GenericHandler<TCommon, std::tuple<TFirst, TSecond> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(TFirst &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
        virtual void Handle(TSecond &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
        virtual void Handle(TCommon&)
        {
            //Nothing to do
        }
    };

    template <typename TCommon, typename TFirst>
    class GenericHandler<TCommon, std::tuple<TFirst> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(TFirst &msg)
        {
            this->Handle(static_cast<TCommon&>(msg));
        }
        virtual void Handle(TCommon&)
        {
            //Nothing to do
        }
    };

    template <typename TCommon>
    class GenericHandler<TCommon, std::tuple<> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(TCommon&)
        {
            //Nothing to do
        }
    };
} //Botcraft