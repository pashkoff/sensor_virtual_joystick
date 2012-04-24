#pragma once
#include <memory>
#include "IAccelDataReceiver.hpp"


struct VirtualJoy : public IAccelDataReceiver
{
	VirtualJoy(IAccelDataReceiver* adr);

	virtual ~VirtualJoy();

	virtual void receive(sensor::Accel& a);

	IAccelDataReceiver* adr;

	struct Impl;
	std::unique_ptr<Impl> pimpl;
};

