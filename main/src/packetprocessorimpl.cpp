#include "packetprocessorimpl.h"
#include <iostream>
#include <string>
#include <vector>

std::string bytesToString(const std::vector<uint8_t>& bytes)
{
    if (bytes.empty())
    {
        return std::string();
    }

    std::string characters;
    for (auto byte : bytes)
    {
        characters += (char) byte;
    }

    return characters;
}

bool PacketProcessorImpl::process(const Tins::Packet& aPacket)
{
    const Tins::TCP& tcpPacket = aPacket.pdu()->rfind_pdu<Tins::TCP>();
    std::cout << "TCP packet from port " << tcpPacket.sport() << " to port " << tcpPacket.dport() << "\n";

    return true;
}

void PacketProcessorImpl::onDataExchange(Tins::TCPStream& aStream)
{
    std::cout << "Client payload: " << bytesToString(aStream.client_payload()) << "\n";
}

void PacketProcessorImpl::onStreamEnd(Tins::TCPStream& aStream)
{
    std::cout << "TCP Stream: " << aStream.id() << " ended.\n";
}