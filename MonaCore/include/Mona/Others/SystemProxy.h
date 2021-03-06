#pragma once

#include "Mona/WinRegistryKey.h"

namespace Mona 
{
    class CSystemProxy
    {
    public:
        CSystemProxy(void);
        ~CSystemProxy(void);

        bool EnableGlobalProxy(Exception& ex, const std::string& address = "127.0.0.1:1080");
        bool EnableProxyWithPAC(Exception& ex, const std::string& address);
        bool DisableProxy(Exception& ex);
        bool IsProxyDisabled();

    private:
        bool RestoreProxyConnectionSettings(Exception& ex);
        bool NotifyIE(Exception& ex);

        static const std::string sm_IESettingsRootKey;

    private:

        WinRegistryKey m_reg;
    };
}
