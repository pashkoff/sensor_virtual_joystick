#pragma once


namespace sensor
{
	class Accel;
}

class IAccelDataReceiver
{
public:

	virtual void receive(sensor::Accel& a) = 0;

protected: 

	virtual ~IAccelDataReceiver(void)
	{
	}
};

