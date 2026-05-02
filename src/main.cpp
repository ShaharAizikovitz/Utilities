#include "CLoader.h"

int main() {
    auto channels = ChannelLoader::load("channels.xml");

    for (auto& ch : channels) {
        ch->open();
    }

    return 0;
}