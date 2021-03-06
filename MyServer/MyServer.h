#pragma once

#include "Mona/Server.h"
#include "Mona/TerminateSignal.h"

namespace Mona 
{
    class MyServer : public Mona::Server
    {
    public:
        MyServer(const Mona::Parameters& configs, Mona::TerminateSignal& terminateSignal);
        ~MyServer();

        virtual void manage();

        virtual void onStart();

        virtual void onStop();

        virtual const std::string& rootPath() const;

    private:
        Mona::TerminateSignal&	_terminateSignal;
        std::string _workPath;

    };
} // MyVPN