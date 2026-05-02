#pragma once
#include "IChannel.h"
#include <iostream>

class CUdpChannel : public IChannel {
public:
    std::string localIP;
    int localPort;
    std::string remoteIP;
    int remotePort;

    CUdpChannel(const std::string& lip, int lport,
        const std::string& rip, int rport)
        : localIP(lip), localPort(lport),
        remoteIP(rip), remotePort(rport) {
    }

    void open() override {
        std::cout << "Opening UDP: " << localIP << ":" << localPort
            << " -> " << remoteIP << ":" << remotePort << "\n";
    }

    void close() override {
        std::cout << "Closing UDP\n";
    }

    std::string name() const override {
        return "UDP";
    }
};