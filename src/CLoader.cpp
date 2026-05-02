#include "CLoader.h"
#include "CChannelFactory.h"
#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

std::vector<std::unique_ptr<IChannel>>
ChannelLoader::load(const std::string& file)
{
    std::vector<std::unique_ptr<IChannel>> channels;

    XMLDocument doc;

    if (doc.LoadFile(file.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML: " << file << "\n";
        return channels;
    }

    auto* root = doc.FirstChildElement("Channels");
    if (!root) {
        std::cerr << "Missing <Channels>\n";
        return channels;
    }

    for (auto* ch = root->FirstChildElement("Channel");
        ch != nullptr;
        ch = ch->NextSiblingElement("Channel"))
    {
        auto channel = ChannelFactory::create(ch);
        if (channel) {
            channels.push_back(std::move(channel));
        }
    }

    return channels;
}