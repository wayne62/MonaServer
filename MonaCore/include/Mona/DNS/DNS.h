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

#pragma once

#include "Mona/Mona.h"
#include "Mona/SocketAddress.h"
#include "Mona/BinaryReader.h"
#include "Mona/BinaryWriter.h"
#include "Mona/Time.h"

namespace Mona {

class DNS : virtual Static {
public:
    static std::string GetHostFromPacket(const char* pBuf, size_t sz);

    static std::string GetResponseIPs(const char* pBuf, size_t sz);

    static bool FlushDNS();

    static bool NotifyIPChanged(const std::string& strAdapterName);
};

}  // namespace Mona
