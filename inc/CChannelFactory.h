#pragma once

#include <memory>
#include "IChannel.h"
#include "tinyxml2.h"

class ChannelFactory {
public:
    static std::unique_ptr<IChannel>
        create(tinyxml2::XMLElement* node);

private:
    static const char* getText(tinyxml2::XMLElement* parent,
        const char* name,
        const char* defaultValue);

    static int getInt(tinyxml2::XMLElement* parent,
        const char* name,
        int defaultValue);
};