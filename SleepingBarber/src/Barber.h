#pragma once

#include <thread>
#include "SharedResources.h"

class Barber
{
public:
	Barber(SharedResources& sResources);
	~Barber();

	void BarberProc();

private:
	std::thread m_BarberTh;
	SharedResources& g_Resources;
};

