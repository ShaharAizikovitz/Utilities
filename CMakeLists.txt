cmake_minimum_required(VERSION 3.16)

project(ChannelFactoryTinyXML VERSION 1.0 LANGUAGES CXX)

# -----------------------------
# C++ Standard
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# TinyXML-2 (local source)
# -----------------------------
add_library(tinyxml2
    tinyxml2/tinyxml2.cpp
)

target_include_directories(tinyxml2 PUBLIC
    tinyxml2
)

# -----------------------------
# Channels library (optional but clean)
# -----------------------------
add_library(channels inc/CLoader.h inc/CSerialChannel.h inc/CUdpChannel.h inc/CChannelFactory.h src/CLoader.cpp src/CChannelFactory.cpp
)

target_include_directories(channels PUBLIC inc)

target_link_libraries(channels PUBLIC tinyxml2)

# -----------------------------
# Main executable
# -----------------------------
add_executable(channel_app
    src/main.cpp
)

target_link_libraries(channel_app
    PRIVATE channels
)

# -----------------------------
# Platform-specific (UDP sockets on Windows)
# -----------------------------
if (WIN32)
    target_link_libraries(channel_app PRIVATE ws2_32)
endif()

# -----------------------------
# Warnings
# -----------------------------
if (MSVC)
    target_compile_options(channel_app PRIVATE /W4)
else()
    target_compile_options(channel_app PRIVATE -Wall -Wextra -Wpedantic)
endif()

# -----------------------------
# Copy XML config to build dir
# -----------------------------
configure_file(
    ${CMAKE_SOURCE_DIR}/data/channels.xml
    ${CMAKE_BINARY_DIR}/data/channels.xml
    COPYONLY
)