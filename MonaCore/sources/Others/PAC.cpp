#include "Mona/Others/PAC.h"
#include "Mona/Others/SystemProxy.h"

namespace Mona
{
    PAC::PAC(const char* name, Invoker& invoker, Sessions& sessions):
        HTTProtocol(name, invoker, sessions),
        _spSystemProxy(new CSystemProxy)
    {

    }

    PAC::~PAC()
    {

    }

    bool PAC::load(Exception& ex, SocketAddress& address)
    {
        if (!HTTProtocol::load(ex, address))
        {
            return false;
        }

        return _spSystemProxy->EnableProxyWithPAC(ex, address.toString());
    }

}
