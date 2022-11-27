#include <iostream>
#include <driver/deviceA.h>

class App : public sys_init::Application
{
	virtual void Main() final
	{
		std::cout << "Hello world!" << std::endl;

		device::DeviceA *dev = device::DeviceA::GetInstance("devA2");

		dev->Print();

		dev = device::DeviceA::GetInstance("devB1");
		dev->Print();
	}
};

int main(int argc, char *argv[])
{

	static App app;
	app.Start();

	return 0;
}