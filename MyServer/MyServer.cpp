#include "MyServer.h"

namespace Mona
{
    MyServer::MyServer(const Mona::Parameters& configs, Mona::TerminateSignal& terminateSignal):
        Server(configs.getNumber<UInt32>("socketBufferSize"), configs.getNumber<UInt16>("threads")),
        _terminateSignal(terminateSignal)
    {
        std::string pathApp("./");
        configs.getString("application.dir", pathApp);
        _workPath = pathApp + "www";
    }


    MyServer::~MyServer()
    {
        stop();
    }

    void MyServer::manage()
    {
        Server::manage();
    }

    void MyServer::onStart()
    {
    }

    void MyServer::onStop()
    {
    }

    const std::string& MyServer::rootPath() const
    {
        return _workPath;
    }
}
