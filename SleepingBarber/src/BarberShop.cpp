#include "BarberShop.h"
#include "Barber.h"
#include "Customer.h"
#include "Random.h"

#include <iostream>
#include <Windows.h>

void BarberShop::Run()
{
	Random::Init();

	SharedResources sharedResources = SharedResources();

	Barber barber(sharedResources);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true)
	{
		sharedResources.CslPrint.lock();
		//auto newCustomer = std::make_shared<Customer>(sharedResources);
		auto newCustomer = new Customer(sharedResources);
		//auto nc = newCustomer.get();
		SetConsoleTextAttribute(hConsole, BLUE);
		std::cout << "El cliente -- " << newCustomer->GetId() << " entra a la barberia " << std::endl;
		sharedResources.CslPrint.unlock();

		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(5s);

		
	}
}
