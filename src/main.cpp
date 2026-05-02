#include "CLoader.h"

int main() {
    auto channels = ChannelLoader::load("../data/channels.xml");

    for (auto& ch : channels) {
        ch->open();
    }

    return 0;
}