#include <driver/deviceA.h>
#include <iostream>

namespace device
{
    class devA : public DeviceA
    {
        virtual void Init() override
        {
            std::cout << "Init dev A" << std::endl;
        }

        virtual void Print() override
        {
            std::cout << "dev A:: " << this->Name() << std::endl;
        }

    public:
        devA(const char *name) : DeviceA(name, sys_init::SystemInitManager::INIT_LEVEL_PRE_OS_0) {}
    };

    static devA de1("devA1"), de2("devA2");
}
