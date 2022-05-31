cmake_minimum_required(VERSION 3.19)
project(socket)

set(CMAKE_CXX_STANDARD 11)

add_executable(socket
        main.cpp
        src/io/ByteData.cpp
        src/io/ByteData.h
        src/io/DecodeStream.cpp
        src/io/DecodeStream.h
        src/io/EncodeStream.cpp
        src/io/EncodeStream.h
        src/io/ByteOrder.cpp
        src/io/ByteOrder.h
        src/protocol/Packet.h
        src/protocol/handshake/HandshakePacket.cpp
        src/protocol/handshake/HandshakePacket.h
        src/protocol/status/client/StatusRequestPacket.cpp
        src/protocol/status/client/StatusRequestPacket.h
        src/protocol/status/server/StatusResponsePacket.cpp
        src/protocol/status/server/StatusResponsePacket.h
        src/codec/EncryptionCodec.cpp
        src/codec/EncryptionCodec.h
        src/codec/SizerCodec.cpp
        src/codec/SizerCodec.h
        src/codec/CompressionCodec.cpp
        src/codec/CompressionCodec.h
        src/codec/PacketCodec.cpp
        src/codec/PacketCodec.h
        src/codec/aese/AESEncrypter.h
        src/codec/aese/AESEncrypter.cpp
        src/protocol/PacketFactory.cpp
        src/protocol/PacketFactory.h
        src/protocol/status/client/StatusPingPacket.cpp
        src/protocol/status/client/StatusPingPacket.h
        src/protocol/status/server/StatusPongPacket.cpp
        src/protocol/status/server/StatusPongPacket.h
        src/protocol/login/client/LoginStartPacket.cpp
        src/protocol/login/client/LoginStartPacket.h
        src/protocol/login/server/LoginSuccess.cpp
        src/protocol/login/server/LoginSuccess.h
        src/protocol/login/server/SetCompressionPacket.cpp
        src/protocol/login/server/SetCompressionPacket.h
        src/protocol/ingame/server/ServerKeepAlivePacket.cpp
        src/protocol/ingame/server/ServerKeepAlivePacket.h
        src/protocol/ingame/client/ClientKeepAlivePacket.cpp
        src/protocol/ingame/client/ClientKeepAlivePacket.h
        src/protocol/ingame/client/ClientStatusPacket.cpp
        src/protocol/ingame/client/ClientStatusPacket.h
        src/protocol/ingame/client/ClientChatPacket.cpp src/protocol/ingame/client/ClientChatPacket.h)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake")