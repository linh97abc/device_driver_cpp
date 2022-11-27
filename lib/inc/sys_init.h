#ifndef __SYS_INIT_H__
#define __SYS_INIT_H__

#include <iostream>
#include <stdint.h>

namespace sys_init
{

    template <class T>
    class RegisteredResourceListBase;

    template <class T>
    class Iterator;

    template <class T>
    class CanbeRegisterItem
    {
        template <class _T>
        friend class RegisteredResourceListBase;

        template <class _T>
        friend class Iterator;

        T *next;

    public:
        CanbeRegisterItem() : next(nullptr) {}
    };

    template <class T>
    class Iterator
    {
        T *inst;

    public:
        Iterator(RegisteredResourceListBase<T> &list) : inst(list.GetFirstItem()) {}

        T *GetInst()
        {
            return this->inst;
        }

        T *operator->()
        {
            return this->inst;
        }

        bool IsEnd()
        {
            return this->inst == nullptr;
        }

        T *Next()
        {
            CanbeRegisterItem<T> *it = (CanbeRegisterItem<T> *)(this->inst);
            this->inst = it->next;

            return this->inst;
        }
    };

    template <class T>
    class RegisteredResourceListBase
    {
        T *first;

    public:
        T *GetFirstItem()
        {
            return this->first;
        }

        void Register(T &item)
        {
            CanbeRegisterItem<T> *it = (CanbeRegisterItem<T> *)(&item);

            it->next = this->first;
            this->first = &item;
        }
    };

    template <class T>
    class RegisteredResourceList : public RegisteredResourceListBase<T>
    {
        RegisteredResourceList() = default;

    public:
        static RegisteredResourceList *GetInst()
        {
            static RegisteredResourceList inst;

            return &inst;
        }
    };

    class CanbeInitResource;
    class SystemInitManager
    {
        friend class Application;
        using ResourceList = RegisteredResourceListBase<CanbeInitResource>;

    public:
        enum InitLevel : unsigned int
        {
            INIT_LEVEL_PRE_OS_0,
            INIT_LEVEL_PRE_OS_1,
            INIT_LEVEL_POST_OS_0,
            INIT_LEVEL_POST_OS_1,
            INIT_LEVEL_APPLICATION
        };

        void Register(CanbeInitResource &item, InitLevel level)
        {
            this->GetInitList(level).Register(item);
        }

        void InitAll(InitLevel level);

        static SystemInitManager *GetInst()
        {
            static SystemInitManager inst;
            return &inst;
        }

    private:
        ResourceList &GetInitList(InitLevel level)
        {
            switch (level)
            {
            case INIT_LEVEL_PRE_OS_0:
                return this->preOS0;
            case INIT_LEVEL_PRE_OS_1:
                return this->preOS1;
            case INIT_LEVEL_POST_OS_0:
                return this->postOS0;
            case INIT_LEVEL_POST_OS_1:
                return this->postOS1;
            case INIT_LEVEL_APPLICATION:
                return this->app;

            default:
                break;
            }

            return this->app;
        }

        ResourceList preOS0,
            preOS1,
            postOS0,
            postOS1,
            app;
    };

    class CanbeInitResource : public CanbeRegisterItem<CanbeInitResource>
    {
    public:
        CanbeInitResource(SystemInitManager::InitLevel level)
        {
            SystemInitManager::GetInst()->Register(*this, level);
        }

        virtual void Init() {}

        virtual ~CanbeInitResource() = default;
    };

    class Application
    {
        virtual void Main() = 0;
        SystemInitManager *sysInitManager;

        void StartOS()
        {
            this->sysInitManager->InitAll(SystemInitManager::INIT_LEVEL_POST_OS_0);
            this->sysInitManager->InitAll(SystemInitManager::INIT_LEVEL_POST_OS_1);
            this->sysInitManager->InitAll(SystemInitManager::INIT_LEVEL_APPLICATION);
            this->Main();
        }

    public:
        Application() : sysInitManager(SystemInitManager::GetInst())
        {
        }

        void Start()
        {
            this->sysInitManager->InitAll(SystemInitManager::INIT_LEVEL_PRE_OS_0);
            this->sysInitManager->InitAll(SystemInitManager::INIT_LEVEL_PRE_OS_1);
            this->StartOS();
        }
    };
} // namespace sys_init

#endif // __SYS_INIT_H__