#include <sys_init.h>

void sys_init::SystemInitManager::InitAll(InitLevel level)
{
    ResourceList &rsList = this->GetInitList(level);

    sys_init::Iterator<CanbeInitResource> it(rsList);

    for (; !it.IsEnd(); it.Next())
    {
        it->Init();
    }
}