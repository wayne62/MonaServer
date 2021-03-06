#pragma once

#include "Mona/HTTP/HTTProtocol.h"

namespace Mona 
{
    class CSystemProxy;
    class PAC : public HTTProtocol
    {
    public:
        PAC(const char* name, Invoker& invoker, Sessions& sessions);
        ~PAC();

    public:
        bool load(Exception& ex, SocketAddress& address);

    private:

        std::unique_ptr<CSystemProxy> _spSystemProxy;
    };
} // MyVPN