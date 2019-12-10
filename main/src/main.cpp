#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

#include "tins/tins.h"

int main(int argc, char *argv[])
{
	auto networkInterfaces = Tins::NetworkInterface::all();
	auto usedNetworkInterface = std::find_if(networkInterfaces.begin(), networkInterfaces.end(), [](const Tins::NetworkInterface &netInt) { return netInt.is_up(); });

	if (usedNetworkInterface == networkInterfaces.end())
	{
		std::cout << "No network interface up!"
				  << "\n";
		return 1;
	}
	std::cout << "Used network interface: " << usedNetworkInterface->name() << "\n";

	Tins::SnifferConfiguration snifferConfig;
	snifferConfig.set_filter("port 23");
	snifferConfig.set_promisc_mode(true);

	Tins::Sniffer sniffer(usedNetworkInterface->name(), snifferConfig);
	while (usedNetworkInterface->is_up())
	{
		Tins::Packet packet = sniffer.next_packet();
		std::unique_ptr<Tins::PDU> packetPDU(packet.pdu());
		if (packetPDU)
		{
			auto packetTimestamp = packet.timestamp();
			std::cout << "Packet received at: " << packetTimestamp.seconds() << ":" << packetTimestamp.microseconds() << "|" << (packetPDU->pdu_type() == Tins::PDU::PDUType::TCP ? "TCP" : "OTHER") << "\n";
		}
	}

	return 0;
}