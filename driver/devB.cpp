#include <driver/deviceA.h>
#include <iostream>

namespace device
{
    class devB : public DeviceA
    {
    private:
        virtual void Init() override
        {
            std::cout << "Init dev B" << std::endl;
        }

        virtual void Print() override
        {
            std::cout << "dev B:: " << this->Name() << std::endl;
        }

    public:
        devB(const char *name) : DeviceA(name, sys_init::SystemInitManager::INIT_LEVEL_PRE_OS_1) {}
    };

    static devB de1("devB1"), de2("devB2");
}