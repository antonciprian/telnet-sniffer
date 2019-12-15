#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H
#include <tins/tins.h>

class PacketProcessor
{
public:
    virtual ~PacketProcessor() = default;
    virtual bool process(const Tins::Packet&) = 0;
    virtual void onDataExchange(Tins::TCPStream&) = 0;
    virtual void onStreamEnd(Tins::TCPStream&) = 0;
};

#endif // PACKETPROCESSOR_H
