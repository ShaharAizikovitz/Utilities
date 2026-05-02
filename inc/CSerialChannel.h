#pragma once
#include "IChannel.h"
#include <iostream>

class SerialChannel : public IChannel {
public:
    std::string port;
    int baudRate;

    SerialChannel(const std::string& p, int baud)
        : port(p), baudRate(baud) {
    }

    void open() override {
        std::cout << "Opening Serial: " << port
            << " @ " << baudRate << "\n";
    }

    void close() override {
        std::cout << "Closing Serial\n";
    }

    std::string name() const override {
        return "Serial";
    }
};