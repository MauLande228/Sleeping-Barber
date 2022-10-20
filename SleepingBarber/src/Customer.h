#pragma once

#include <thread>
#include "SharedResources.h"

class Customer
{
public:
	using id_t = unsigned int;

	Customer(SharedResources& sResources);
	virtual ~Customer();

	void ClientProc();
	void JoinCustomerThread();

	uint32_t GetId() const { return m_Id; }

private:
	std::jthread m_CustomerTh;
	id_t m_Id;
	SharedResources& g_Resources;
};

