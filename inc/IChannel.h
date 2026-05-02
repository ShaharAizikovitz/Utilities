#pragma once
#include <string>
#include <memory>

class IChannel {
public:
    virtual ~IChannel() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual std::string name() const = 0;
};