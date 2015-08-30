#include "MyServer.h"

namespace Mona
{
    MyServer::MyServer(const Mona::Parameters& configs, Mona::TerminateSignal& terminateSignal):
        Server(configs.getNumber<UInt32>("socketBufferSize"), configs.getNumber<UInt16>("threads")),
        _terminateSignal(terminateSignal)
    {
        std::string pathServer("./");
        configs.getString("application", pathServer);
        _workPath = pathServer + "server";
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
