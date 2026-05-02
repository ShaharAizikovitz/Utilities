#pragma once

#include <vector>
#include <memory>
#include <string>
#include "IChannel.h"

class ChannelLoader {
public:
    static std::vector<std::unique_ptr<IChannel>>
        load(const std::string& file);
};