#pragma once

#include <thread>
#include "SharedResources.h"

class Customer
{
public:
	using id_t = unsigned int;

	Customer(SharedResources& sResources);
	~Customer();

	void ClientProc();

	uint32_t GetId() const { return m_Id; }

private:
	std::thread m_CustomerTh;
	id_t m_Id;
	SharedResources& g_Resources;
};

