#pragma once

#include <tuple>

namespace ProtocolCraft
{
    // This class is inspired by https://arobenko.gitbooks.io/comms-protocols-cpp/content/

    // TCommon is common interface class for all the messages
    // TAll is all the message types, that need to be handled, bundled in std::tuple
    template <typename TCommon, typename TAll>
    class GenericHandler;

    // Big boy to process packets 20 by 20, preventing needlessly copying vtable many times at each inheritance stage
    template <typename TCommon,
        typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename... TRest>
    class GenericHandler<TCommon, std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T11, T13, T14, T15, T16, T17, T18, T19, T20, TRest...> > : public GenericHandler<TCommon, std::tuple<TRest...> >
    {
        using Base = GenericHandler<TCommon, std::tuple<TRest...> >;
    public:
        using Base::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(T1& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T3& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T4& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T5& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T6& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T7& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T8& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T9& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T10& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T11& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T12& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T13& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T14& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T15& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T16& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T17& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T18& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T19& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T20& msg) { this->Handle(static_cast<TCommon&>(msg)); }
    };

    // 10 by 10
    template <typename TCommon,
        typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename... TRest>
    class GenericHandler<TCommon, std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TRest...> > : public GenericHandler<TCommon, std::tuple<TRest...> >
    {
        using Base = GenericHandler<TCommon, std::tuple<TRest...> >;
    public:
        using Base::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(T1& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T3& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T4& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T5& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T6& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T7& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T8& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T9& msg)  { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T10& msg) { this->Handle(static_cast<TCommon&>(msg)); }
    };

    // 5 by 5
    template <typename TCommon,
        typename T1, typename T2, typename T3, typename T4, typename T5,
        typename... TRest>
    class GenericHandler<TCommon, std::tuple<T1, T2, T3, T4, T5, TRest...> > : public GenericHandler<TCommon, std::tuple<TRest...> >
    {
        using Base = GenericHandler<TCommon, std::tuple<TRest...> >;
    public:
        using Base::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(T1& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T3& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T4& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T5& msg) { this->Handle(static_cast<TCommon&>(msg)); }
    };

    // Deal with rest with 4 types
    template <typename TCommon, typename T1, typename T2, typename T3, typename T4>
    class GenericHandler<TCommon, std::tuple<T1, T2, T3, T4> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(T1& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T3& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T4& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(TCommon&) { } //Nothing to do
    };

    // Deal with rest with 3 types
    template <typename TCommon, typename T1, typename T2, typename T3>
    class GenericHandler<TCommon, std::tuple<T1, T2, T3> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(T1& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T3& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(TCommon&) { } //Nothing to do
    };

    // Deal with rest with 2 types
    template <typename TCommon, typename T1, typename T2>
    class GenericHandler<TCommon, std::tuple<T1, T2> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(T1& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(T2& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(TCommon&) { } //Nothing to do
    };

    // Deal with rest with 1 type
    template <typename TCommon, typename T1>
    class GenericHandler<TCommon, std::tuple<T1> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(T1& msg) { this->Handle(static_cast<TCommon&>(msg)); }
        virtual void Handle(TCommon&) { } //Nothing to do
    };

    // Deal with rest with 0 type
    template <typename TCommon>
    class GenericHandler<TCommon, std::tuple<> >
    {
    public:
        virtual ~GenericHandler() {}
        virtual void Handle(TCommon&) { } //Nothing to do
    };
} //ProtocolCraft
