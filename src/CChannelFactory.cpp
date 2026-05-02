#include "CChannelFactory.h"
#include "CUdpChannel.h"
#include "CSerialChannel.h"

using namespace tinyxml2;

std::unique_ptr<IChannel>
ChannelFactory::create(XMLElement* node)
{
    if (!node) return nullptr;

    const char* typeAttr = node->Attribute("type");
    if (!typeAttr) return nullptr;

    std::string type = typeAttr;

    // -------------------------
    // UDP
    // -------------------------
    if (type == "UDP") {
        auto* udp = node->FirstChildElement("UDP");
        if (!udp) return nullptr;

        const char* localIP = getText(udp, "LocalIP", "0.0.0.0");
        int localPort = getInt(udp, "LocalPort", 0);
        const char* remoteIP = getText(udp, "RemoteIP", "127.0.0.1");
        int remotePort = getInt(udp, "RemotePort", 0);

        return std::make_unique<CUdpChannel>(
            localIP, localPort,
            remoteIP, remotePort
        );
    }

    // -------------------------
    // Serial
    // -------------------------
    if (type == "Serial") {
        auto* serial = node->FirstChildElement("Serial");
        if (!serial) return nullptr;

        const char* port = getText(serial, "Port", "COM1");
        int baud = getInt(serial, "BaudRate", 9600);

        return std::make_unique<SerialChannel>(port, baud);
    }

    return nullptr;
}

// -------------------------
// Helpers
// -------------------------

const char*
ChannelFactory::getText(XMLElement* parent,
    const char* name,
    const char* defaultValue)
{
    if (!parent) return defaultValue;

    auto* el = parent->FirstChildElement(name);
    if (!el || !el->GetText()) return defaultValue;

    return el->GetText();
}

int
ChannelFactory::getInt(XMLElement* parent,
    const char* name,
    int defaultValue)
{
    if (!parent) return defaultValue;

    auto* el = parent->FirstChildElement(name);
    if (!el) return defaultValue;

    int value;
    if (el->QueryIntText(&value) != XML_SUCCESS)
        return defaultValue;

    return value;
}