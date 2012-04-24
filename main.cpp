#include <cstdio>
#include <iostream>
#include <conio.h>

#include <sensor.pb.h>


#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include "2de_Vector3.h"

#include <winioctl.h>

#include "IAccelDataReceiver.hpp"
#include "VirtualJoy.hpp"


using boost::asio::ip::udp;

boost::asio::io_service iosrv;

class udp_server
{

public:
	udp_server(IAccelDataReceiver& arecv, boost::asio::io_service& io_service)
		: socket_(io_service, udp::endpoint(udp::v4(), 48912)),
		arecv(arecv)
	{
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from(
			boost::asio::buffer(recv_buffer_),
			remote_endpoint_,
			boost::bind(&udp_server::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(const boost::system::error_code& error,
		std::size_t size)
	{
		//std::cout << "handle_receive size " << size << std::endl;

		if (!error)
		{
			sensor::Accel ac;
			if (!ac.ParseFromArray(recv_buffer_.c_array(), size))
			{
				std::cerr << "handle_receive ParseFromArray error: " << std::endl;
			}
			else
			{
				arecv.receive(ac);
			}
		}
		else
		{
			std::cerr << "handle_receive error: " << error.message() << std::endl;
		}
		start_receive();
	}

	void handle_send(boost::shared_ptr<std::string> /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/)
	{
	}

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	boost::array<char, 512> recv_buffer_;

	IAccelDataReceiver& arecv;
};

struct LowPassFilter : public IAccelDataReceiver
{
	LowPassFilter(IAccelDataReceiver* adr) :
		adr(adr),
		prev(0,0,0),
		k(0.2)
	{}

	virtual void receive(sensor::Accel& a)
	{
		Vector3 va(a.x(), a.y(), a.z());

		//std::cout << "k = " << k << "\n";

		prev = prev + k * ( va - prev);
		a.set_x(prev.x);
		a.set_y(prev.y);
		a.set_z(prev.z);

		if (adr) adr->receive(a);
	}

	IAccelDataReceiver* adr;
	Vector3 prev;
	double k;
};


struct Printer : public IAccelDataReceiver
{
	Printer(IAccelDataReceiver* adr) :
		adr(adr)
	{}

	virtual void receive(sensor::Accel& a)
	{
		std::cout	<< " x = " << a.x()
					<< " y = " << a.y()
					<< " z = " << a.z()
					<< std::endl;

		if (adr) adr->receive(a);
	}

	IAccelDataReceiver* adr;
};



int main() try
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	VirtualJoy joy(NULL);
	Printer rec(&joy);
	LowPassFilter fil(&rec);
	udp_server serv(fil, iosrv);

	//iosrv.run();
	while (!kbhit())
	{
		boost::system::error_code error;
		iosrv.poll(error);
		if (error)
		{
			std::cerr << "frameRenderingQueued error: " << error.message() << std::endl;
		}
	}

	return 0;
}
catch(std::exception& e)
{
	std::cerr << "Got exception\n" << e.what() << std::endl;
	return 1;
}
catch(...)
{
	fputs("Got unknow exception. Something awful. Exiting", stderr);
	return 1;
}