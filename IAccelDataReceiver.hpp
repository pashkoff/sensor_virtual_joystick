#pragma once

#include "2de_Vector3.h"

class IAccelDataReceiver
{
public:

	virtual void receive(Vector3& a) = 0;

protected: 

	virtual ~IAccelDataReceiver(void)
	{
	}
};

