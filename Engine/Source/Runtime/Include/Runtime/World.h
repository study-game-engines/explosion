//
// Created by johnk on 2023/9/5.
//

#pragma once

#include <Common/Memory.h>
#include <Runtime/ECS.h>

namespace Runtime {
    class World;

    class RUNTIME_API SystemSchedule {
    public:
        SystemSchedule(World& inWorld, SystemSignature inTarget);
        ~SystemSchedule();

        template <typename S>
        SystemSchedule& ScheduleAfter();

        SystemSchedule& ScheduleAfter(const Mirror::Class& clazz);

    private:
        SystemSchedule& ScheduleAfterInternal(const SystemSignature& depend);

        World& world;
        SystemSignature target;
    };

    class RUNTIME_API EventSlot {
    public:
        EventSlot(World& inWorld, EventSignature inTarget);
        ~EventSlot();

        template <typename S>
        EventSlot& Connect();

        EventSlot& Connect(const Mirror::Class& clazz);

    private:
        EventSlot& ConnectInternal(const SystemSignature& systemSignature, EventSystem* systemInstance);

        World& world;
        EventSignature target;
    };

    class RUNTIME_API World : public ECSHost {
    public:
        explicit World(std::string inName = "");
        ~World();

        template <typename S>
        SystemSchedule AddSetupSystem()
        {
            return AddSetupSystemInternal(Internal::SignForClass<S>(), new S());
        }

        template <typename S>
        SystemSchedule AddTickSystem()
        {
            return AddTickSystemInternal(Internal::SignForClass<S>(), new S());
        }

        template <typename E>
        EventSlot Event()
        {
            return EventInternal(Internal::SignForClass<E>());
        }

        SystemSchedule AddSetupSystem(const Mirror::Class& clazz);
        SystemSchedule AddTickSystem(const Mirror::Class& clazz);
        EventSlot Event(const Mirror::Class& clazz);

        void Setup();
        void Shutdown();
        void Tick();

    protected:
        void BroadcastEvent(EventSignature eventSignature, const Mirror::Any& eventRef) override;

    private:
        friend class SystemSchedule;
        friend class EventSlot;
        friend class WorldTestHelper;

        void RegisterSystem(const SystemSignature& systemSignature, System* systemInstance);
        void ExecuteWorkSystems(const std::vector<SystemSignature>& targets);

        SystemSchedule AddSetupSystemInternal(const SystemSignature& systemSignature, SetupSystem* systemInstance);
        SystemSchedule AddTickSystemInternal(const SystemSignature& systemSignature, TickSystem* systemInstance);
        EventSlot EventInternal(const EventSignature& eventSignature);

        bool setuped;
        std::string name;
        entt::registry registry;
        std::vector<SystemSignature> setupSystems;
        std::vector<SystemSignature> tickSystems;
        std::unordered_map<SystemSignature, Common::UniqueRef<System>> systems;
        std::unordered_map<SystemSignature, std::vector<SystemSignature>> systemDependencies;
        std::unordered_map<EventSignature, std::vector<SystemSignature>> eventSlots;
    };

    // used for test only
#if BUILD_TEST
    class RUNTIME_API WorldTestHelper {
    public:
        explicit WorldTestHelper(World& inWorld);
        ~WorldTestHelper();

        SystemCommands HackCreateSystemCommands();

    private:
        World& world;
    };
#endif
}

namespace Runtime {
    template <typename S>
    SystemSchedule& SystemSchedule::ScheduleAfter()
    {
        return ScheduleAfterInternal(Internal::SignForClass<S>());
    }

    template <typename S>
    EventSlot& EventSlot::Connect()
    {
        return ConnectInternal(Internal::SignForClass<S>(), new S());
    }
}
