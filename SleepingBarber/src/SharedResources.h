#pragma once

#include <mutex>
#include <queue>
#include <semaphore>

#define GREEN 10
#define BLUE 11
#define RED 12

class Customer;

struct SharedResources
{
	std::binary_semaphore	CustomersInStore{ 0 };
	std::binary_semaphore	BarberState{ 0 };
	std::mutex				SeatsMutex;
	std::mutex				CslPrint;
	std::queue<Customer*>	CustomersQueue;
	uint16_t				FreeChairs = 3;
};
