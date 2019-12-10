#include <iostream>
#include <algorithm>
#include <vector>

#include "tins/tins.h"

int main(int argc, char *argv[])
{
	auto networkInterfaces = Tins::NetworkInterface::all();
	auto usedNetworkInterface = std::find_if(networkInterfaces.begin(), networkInterfaces.end(), [](const Tins::NetworkInterface& netInt) { return netInt.is_up();});

	if (usedNetworkInterface == networkInterfaces.end())
	{
		std::cout << "No network interface up!" << "\n";
		return 1;
	}

	Tins::SnifferConfiguration snifferConfig;
	snifferConfig.set_filter("port 23");

	Tins::Sniffer sniffer(usedNetworkInterface->name(), snifferConfig);
	while (usedNetworkInterface->is_up())
	{
		Tins::Packet newPacket = sniffer.next_packet();
		auto packetTimestamp = newPacket.timestamp();
		auto packetPDU = newPacket.pdu();
		std::cout << packetTimestamp.seconds() << ":" << packetTimestamp.microseconds() << "|" << (packetPDU && packetPDU->pdu_type() == Tins::PDU::PDUType::TCP ? "TCP" : "OTHER") << "\n";
	}

	return 0;
}