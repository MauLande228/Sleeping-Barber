#include "Barber.h"
#include "Customer.h"
#include "Random.h"

#include <iostream>
#include <Windows.h>

Barber::Barber(SharedResources& sResources) :
	g_Resources(sResources)
{
	m_BarberTh = std::thread(&Barber::BarberProc, this);
}

Barber::~Barber()
{
	//m_BarberTh.join();
}

void Barber::BarberProc()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		// Wait for customers signal to wake up
		g_Resources.CustomersInStore.acquire();
		
		g_Resources.SeatsMutex.lock();
		//auto currentCustomer = g_Resources.CustomersQueue.front().get();
		auto currentCustomer = g_Resources.CustomersQueue.front();
		//g_Resources.CustomersQueue.pop();
		g_Resources.FreeChairs += 1;

		g_Resources.CslPrint.lock();

		SetConsoleTextAttribute(hConsole, GREEN);
		std::cout << "El barbero ha comenzado a atender al cliente -- " << currentCustomer->GetId();
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << "\t\t\t\t\tAsientos libres: -- " << g_Resources.FreeChairs << std::endl;
		
		g_Resources.CslPrint.unlock();
		g_Resources.SeatsMutex.unlock();

		int haircutTime = Random::RandInt(5, 15);
		std::this_thread::sleep_for(std::chrono::seconds(haircutTime));
		

		g_Resources.CslPrint.lock();
		SetConsoleTextAttribute(hConsole, GREEN);
		std::cout << "El barbero ha terminado de cortar el cabello del cliente -- " << currentCustomer->GetId() << std::endl;
		g_Resources.CslPrint.unlock();

		g_Resources.SeatsMutex.lock();
		g_Resources.CustomersQueue.pop(); //TODO: Fix this shit
		g_Resources.SeatsMutex.unlock();

		g_Resources.BarberState.release();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
