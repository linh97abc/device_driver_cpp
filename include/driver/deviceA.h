#ifndef __DEVICEA_H__
#define __DEVICEA_H__

#include <device_base.h>

namespace device
{
    class DeviceA : public DeviceBase<DeviceA>
    {
    public:
        DeviceA(const char *name, sys_init::SystemInitManager::InitLevel level)
            : DeviceBase(name, level, *this) {}

        virtual void Print() = 0;

        virtual ~DeviceA() = default;
    };
} // namespace device

#endif // __DEVICEA_H__