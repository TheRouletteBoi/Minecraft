#pragma once

#include "PacketSender.h"

class BatchedPacketSender : public PacketSender
{
public:
	virtual ~BatchedPacketSender();
	virtual void send(const Packet &);
	virtual void send(const RakNet::RakNetGUID &, const Packet &);
	virtual void sendBroadcast(const RakNet::RakNetGUID &, const Packet &);
};
