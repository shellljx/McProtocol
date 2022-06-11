cmake_minimum_required(VERSION 3.19)
project(socket)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

#glfw
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.7/lib-x86_64")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.7/include")
#stb
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb/include)
#include source header
include_directories(${CMAKE_SOURCE_DIR}/src)
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
        src/protocol/ingame/clientbound/ServerKeepAlivePacket.cpp
        src/protocol/ingame/clientbound/ServerKeepAlivePacket.h
        src/protocol/ingame/serverbound/ClientKeepAlivePacket.cpp
        src/protocol/ingame/serverbound/ClientKeepAlivePacket.h
        src/protocol/ingame/serverbound/ClientStatusPacket.cpp
        src/protocol/ingame/serverbound/ClientStatusPacket.h
        src/protocol/ingame/serverbound/ClientChatPacket.cpp
        src/protocol/ingame/serverbound/ClientChatPacket.h
        src/renderer/RendererManager.cpp
        src/renderer/RendererManager.h
        src/renderer/ShaderLoader.h
        src/protocol/ingame/clientbound/chunk/ServerChunkDataPacket.cpp
        src/protocol/ingame/clientbound/chunk/ServerChunkDataPacket.h
        src/bean/ChunkColumn.cpp src/bean/ChunkColumn.h
        src/bean/ChunkSection.cpp src/bean/ChunkSection.h
        src/bean/nbt/TagCompound.cpp src/bean/nbt/TagCompound.h
        src/bean/nbt/Tag.cpp
        src/bean/nbt/Tag.h
        src/io/ReadWriteable.h
        src/bean/nbt/TagByte.cpp
        src/bean/nbt/TagByte.h
        src/bean/nbt/TagShort.cpp
        src/bean/nbt/TagShort.h
        src/bean/nbt/TagInt.cpp
        src/bean/nbt/TagInt.h
        src/bean/nbt/TagLong.cpp
        src/bean/nbt/TagLong.h
        src/bean/nbt/TagFloat.cpp
        src/bean/nbt/TagFloat.h
        src/bean/nbt/TagDouble.cpp
        src/bean/nbt/TagDouble.h
        src/bean/nbt/TagByteArray.cpp
        src/bean/nbt/TagByteArray.h
        src/bean/nbt/TagString.cpp
        src/bean/nbt/TagString.h
        src/bean/nbt/TagList.cpp
        src/bean/nbt/TagList.h
        src/bean/nbt/TagIntArray.cpp
        src/bean/nbt/TagIntArray.h
        src/bean/nbt/TagLongArray.cpp
        src/bean/nbt/TagLongArray.h
        src/bean/BlockEntityInfo.cpp
        src/bean/BlockEntityInfo.h
        src/bean/LightUpdateData.cpp
        src/bean/LightUpdateData.h
        )

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake")
target_link_libraries(${PROJECT_NAME} libglfw3.dylib)
target_link_libraries(${PROJECT_NAME} libz.a)
find_package(glm REQUIRED)
include_directories("/usr/local/Cellar/glm/0.9.9.8/include")
target_link_libraries(${PROJECT_NAME} glm::glm)

set(ASSET_DIR ./assets)
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${ASSET_DIR}")