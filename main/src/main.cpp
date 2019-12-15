#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <memory>
#include <tins/tins.h>

#include "packetprocessor.h"
#include "packetprocessorimpl.h"

int main(int argc, char *argv[])
{
	auto networkInterface = Tins::NetworkInterface::default_interface();
	std::cout << "Default network interface's ipv4: " << networkInterface.ipv4_address() << "\n";

	Tins::SnifferConfiguration snifferConfig;
	snifferConfig.set_promisc_mode(true);

	Tins::Sniffer sniffer(networkInterface.name(), snifferConfig);
    PacketProcessorImpl packetProcessor;
    Tins::TCPStreamFollower tcpStreamFollower;
    //sniffer.sniff_loop(std::bind(&PacketProcessorImpl::process, &packetProcessor, std::placeholders::_1));
    tcpStreamFollower.follow_streams(sniffer, std::bind(&PacketProcessorImpl::onDataExchange, &packetProcessor, std::placeholders::_1), std::bind(&PacketProcessorImpl::onStreamEnd, &packetProcessor, std::placeholders::_1));

	return 0;
}