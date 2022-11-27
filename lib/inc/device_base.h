#ifndef __DEVICE_BASE_H__
#define __DEVICE_BASE_H__
#include <sys_init.h>

namespace device
{

    template <class T>
    class DeviceBase : public sys_init::CanbeRegisterItem<T>, public sys_init::CanbeInitResource
    {
        using DeviceList = sys_init::RegisteredResourceList<T>;
        using DeviceIterator = sys_init::Iterator<T>;
        virtual void Init() {}
        const char *name;

    public:
        DeviceBase(const char *name, sys_init::SystemInitManager::InitLevel initLevel, T &dev)
            : CanbeInitResource(initLevel), name(name)
        {
            DeviceList::GetInst()->Register(dev);
        }

        virtual ~DeviceBase() = default;

        const char *Name()
        {
            return this->name;
        }

        static T *GetInstance(const char *name)
        {
            for (DeviceIterator it(*DeviceList::GetInst()); !it.IsEnd(); it.Next())
            {
                if (strcmp(it->name, name) == 0)
                {
                    return it.GetInst();
                }
            }

            return nullptr;
        }
    };
} // namespace device

#endif // __DEVICE_BASE_H__