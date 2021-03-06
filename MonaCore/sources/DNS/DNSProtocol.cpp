/*
Copyright 2014 Mona
lang.xiong.sc[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#include "Mona/DNS/DNSProtocol.h"
#include "Mona/DNS/DNS.h"
#include "Mona/DNS/DNSSession.h"
#include "Mona/DNS/DNSHelper.h"

using namespace std;

namespace Mona {

DNSProtocol::DNSProtocol(const char* name, Invoker& invoker, Sessions& sessions) : 
    UDProtocol(name, invoker, sessions) {

	// timesBeforeTurn, no by default

    std::string blockListFilePath;
    if (!invoker.getString("blockListFilePath", blockListFilePath))
    {
        FATAL("No block list file configure");
    }
    _pDNSHelper.reset(new DNSHelper(blockListFilePath));
	onPacket = [this](PoolBuffer& pBuffer,const SocketAddress& address) {
        auto host(DNS::GetHostFromPacket((const char*)pBuffer->data(), pBuffer->size()));
        SocketAddress DNSServerAddress;
        Exception e;
        DNSServerAddress.set(e, _pDNSHelper->GetDNSServerAddress(host), 53);
        this->sessions.create<DNSSession>(*this, this->invoker, pBuffer, address, DNSServerAddress);
	};

	OnPacket::subscribe(onPacket);
}

DNSProtocol::~DNSProtocol() {
	OnPacket::unsubscribe(onPacket);
}

bool DNSProtocol::load(Exception& ex, SocketAddress& address) {

	if (!UDProtocol::load(ex,address))
		return false;

    return _pDNSHelper->ChangeDefaultAdpaterDNSSetting();
}



} // namespace Mona
