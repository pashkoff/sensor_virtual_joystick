
#include <windows.h>

#include <winioctl.h>

#include "VirtualJoy.hpp"

#include "proto/cpp_src/sensor.pb.h"

#include "ppjoy/ppjioctl.h"
#include "ppjoy/ppjioctl_devname.h"

#include <boost/format.hpp>

namespace b = boost;

const size_t NUM_ANALOG = 2;
const size_t NUM_DIGITAL = 1;

#pragma pack(push,1)		/* All fields in structure must be byte aligned. */
struct JOYSTICK_STATE
{
	unsigned long   Signature;				/* Signature to identify packet to PPJoy IOCTL */
	char            NumAnalog;				/* Num of analog values we pass */
	long            Analog[NUM_ANALOG];		/* Analog values */
	char            NumDigital;				/* Num of digital values we pass */
	char            Digital[NUM_DIGITAL];	/* Digital values */
}	;
#pragma pack(pop)

template<typename T>
std::unique_ptr<T> make_unique( )
{
    return std::unique_ptr<T>( new T );
}

struct VirtualJoy::Impl : public IAccelDataReceiver
{
	HANDLE h;
	JOYSTICK_STATE state;

	Impl()
	{
		const auto DevName = TEXT(PPJOY_IOCTL_DEVNAME);
		h = CreateFile(DevName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (INVALID_HANDLE_VALUE == h)
		{
			throw std::runtime_error(b::str(
				b::format("CreateFile failed with error code %1% trying to open %2% device") %
					GetLastError() % DevName));
		}

		state.Signature = JOYSTICK_STATE_V1;
		state.NumAnalog = NUM_ANALOG;
		state.NumDigital = NUM_DIGITAL;
	}

	~Impl()
	{
		if (INVALID_HANDLE_VALUE != h)
		{
			CloseHandle(h);
		}
	}


	virtual void receive(sensor::Accel& a)
	{
		std::fill_n(state.Analog, NUM_ANALOG, (PPJOY_AXIS_MIN+PPJOY_AXIS_MAX)/2);
		std::fill_n(state.Digital, NUM_DIGITAL, 0);

		double xdeg = a.x() * (90. / (-10.));
		double ydeg = a.y() * (90. / (-10.));

		std::cout << b::str(b::format("xdeg = %1% ydeg = %2%") % xdeg % ydeg) << std::endl;

		const double degmin = -90.;
		const double degmax =  90.;

		auto convert = [=](double deg)
		{
			return ((deg - degmin) / (degmax - degmin)) * (PPJOY_AXIS_MAX - PPJOY_AXIS_MIN);
		};

		state.Analog[0] = static_cast<long>(convert(xdeg));
		state.Analog[1] = static_cast<long>(convert(ydeg));

		DWORD RetSize;
		if (!DeviceIoControl(h, IOCTL_PPORTJOY_SET_STATE, &state, sizeof(state), NULL, 0, &RetSize, NULL))
		{
			auto rc = GetLastError();
			if (2 == rc)
			{
				throw std::runtime_error("Underlying joystick device deleted.");
			}

			std::cerr << b::str(b::format("DeviceIoControl error %1%") % rc) << std::endl;
		}
	}
};




VirtualJoy::VirtualJoy(IAccelDataReceiver* adr) try :
	adr(adr),
	pimpl(nullptr)
{
	pimpl.swap(make_unique<Impl>());
	return;	
}
catch (...)
{
	pimpl.reset();
	throw;
}


VirtualJoy::~VirtualJoy(void)
{
}


void VirtualJoy::receive(sensor::Accel& a)
{
	pimpl->receive(a);
	if (adr) adr->receive(a);
}