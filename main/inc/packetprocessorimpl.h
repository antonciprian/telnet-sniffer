#ifndef PACKETPROCESSORIMPL_H
#define PACKETPROCESSORIMPL_H
#include <tins/tins.h>

#include "packetprocessor.h"

class PacketProcessorImpl : public PacketProcessor
{
public:
    bool process(const Tins::Packet& aPacket) override;
    void onDataExchange(Tins::TCPStream& aStream) override;
    void onStreamEnd(Tins::TCPStream& aStream) override;
};

#endif // PACKETPROCESSORIMPL_H