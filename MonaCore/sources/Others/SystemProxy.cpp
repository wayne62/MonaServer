#include "Mona/Others/SystemProxy.h"
#include "Mona/Time.h"
#include <Wininet.h>

#pragma comment(lib, "Wininet.lib")

namespace Mona
{
    const std::string CSystemProxy::sm_IESettingsRootKey("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");

    CSystemProxy::CSystemProxy(void) :
        m_reg(HKEY_CURRENT_USER, sm_IESettingsRootKey)
    {

    }

    CSystemProxy::~CSystemProxy(void)
    {
        Exception ex;
        DisableProxy(ex);
    }

    bool CSystemProxy::EnableGlobalProxy(Exception& ex, const std::string& address)
    {
        if (!m_reg.setInt(ex, "ProxyEnable", 1))
        {
            return false;
        }

        if (!m_reg.setString(ex, "ProxyServer", address))
        {
            return false;
        }

        if (!m_reg.setString(ex, "AutoConfigURL", ""))
        {
            return false;
        }
        return NotifyIE(ex);
    }

    bool CSystemProxy::EnableProxyWithPAC(Exception& ex, const std::string& address)
    {
        if (!m_reg.setInt(ex, "ProxyEnable", 1))
        {
            return false;
        }

        if (!m_reg.setString(ex, "ProxyServer", address))
        {
            return false;
        }

        Time time;
        std::string pacUrl(std::string("http://") + address + "/pac");
        if (!m_reg.setString(ex, "AutoConfigURL", pacUrl))
        {
            return false;
        }
        return NotifyIE(ex);
    }

    bool CSystemProxy::DisableProxy(Exception& ex)
    {
        if (!m_reg.setInt(ex, "ProxyEnable", 0))
        {
            return false;
        }

        if (!m_reg.setString(ex, "ProxyServer", ""))
        {
            return false;
        }

        if (!m_reg.setString(ex, "AutoConfigURL", ""))
        {
            return false;
        }
        return NotifyIE(ex) && RestoreProxyConnectionSettings(ex);
    }

    bool CSystemProxy::NotifyIE(Exception& ex)
    {
        BOOL ret1 = ::InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, NULL);
        if (!ret1)
        {
            if (GetLastError() == ERROR_INVALID_PARAMETER)
            {
                ex.set(Exception::ARGUMENT, "INTERNET_OPTION_SETTINGS_CHANGED option flag cannot be set is specified");
            }
            else
            {
                ex.set(Exception::SYSTEM, "INTERNET_OPTION_SETTINGS_CHANGED option flag cannot be set is specified");
            }
            return false;
        }
        BOOL ret2 = ::InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, NULL);
        if (!ret2)
        {
            if (GetLastError() == ERROR_INVALID_PARAMETER)
            {
                ex.set(Exception::ARGUMENT, "INTERNET_OPTION_REFRESH option flag cannot be set is specified");
            }
            else
            {
                ex.set(Exception::SYSTEM, "INTERNET_OPTION_REFRESH option flag cannot be set is specified");
            }
            return false;
        }
        return true;
    }

    bool CSystemProxy::RestoreProxyConnectionSettings(Exception& ex)
    {
        WinRegistryKey key(HKEY_CURRENT_USER, sm_IESettingsRootKey + "\\Connections");
        key.deleteValue("DefaultConnectionSettings");
        return NotifyIE(ex);
    }
}
