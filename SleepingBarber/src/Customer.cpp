#include "Customer.h"

#include <iostream>
#include <Windows.h>

Customer::Customer(SharedResources& sResources) :
	g_Resources(sResources)
{
	static id_t currentId = 0;
	m_Id = currentId++;

	m_CustomerTh = std::thread(&Customer::ClientProc, this);
}

Customer::~Customer()
{
	//m_CustomerTh.join();
}

void Customer::ClientProc()
{
	using namespace std::literals::chrono_literals;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//g_Resources.SeatsMutex.lock();
	if (g_Resources.FreeChairs > 0)
	{
		g_Resources.SeatsMutex.lock();

		g_Resources.FreeChairs -= 1;
		//g_Resources.CustomersQueue.push(shared_from_this());
		g_Resources.CustomersQueue.push(this);
		//g_Resources.CustomersInStore.release();

		g_Resources.CslPrint.lock();
		SetConsoleTextAttribute(hConsole, BLUE);
		std::cout << "El cliente -- " << m_Id << " toma asiento para esperar su turno con el barbero.";
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << "\t\t\tAsientos libres: -- " << g_Resources.FreeChairs << std::endl;
		g_Resources.CustomersInStore.release();
			
		g_Resources.CslPrint.unlock();
		g_Resources.SeatsMutex.unlock();

		// Wait for this client's turn 
		//while (g_Resources.CustomersQueue.front() != shared_from_this());
		while (g_Resources.CustomersQueue.front() != this);

		g_Resources.BarberState.acquire();
		g_Resources.CslPrint.lock();
		SetConsoleTextAttribute(hConsole, BLUE);
		std::cout << "El cliente -- " << m_Id - 1 << " ha finalizado su corte y se retira de la peluqueria feliz" << std::endl;
		g_Resources.CslPrint.unlock();
	}
	else
	{
		//g_Resources.SeatsMutex.unlock();
		g_Resources.CslPrint.lock();
		SetConsoleTextAttribute(hConsole, BLUE);
		std::cout << "El cliente -- " << m_Id << " se retiro de la peluqueria porque no hay espacio" << std::endl;
		g_Resources.CslPrint.unlock();
	}
	
}

