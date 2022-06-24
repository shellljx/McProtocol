cmake_minimum_required(VERSION 3.19)
project(socket)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

#glfw
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.7/lib-x86_64")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.7/include")
#stb
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb/include)
#json
include_directories("/usr/local/Cellar/nlohmann-json/3.10.5/include")
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
        src/renderer/McRenderer.cpp
        src/renderer/McRenderer.h
        src/renderer/ShaderLoader.h
        src/protocol/ingame/clientbound/chunk/ServerChunkDataPacket.cpp
        src/protocol/ingame/clientbound/chunk/ServerChunkDataPacket.h
        src/model/world/Column.cpp src/model/world/Column.h
        src/model/world/Section.cpp src/model/world/Section.h
        src/model/nbt/TagCompound.cpp src/model/nbt/TagCompound.h
        src/model/nbt/Tag.cpp
        src/model/nbt/Tag.h
        src/io/ReadWriteable.h
        src/model/nbt/TagByte.cpp
        src/model/nbt/TagByte.h
        src/model/nbt/TagShort.cpp
        src/model/nbt/TagShort.h
        src/model/nbt/TagInt.cpp
        src/model/nbt/TagInt.h
        src/model/nbt/TagLong.cpp
        src/model/nbt/TagLong.h
        src/model/nbt/TagFloat.cpp
        src/model/nbt/TagFloat.h
        src/model/nbt/TagDouble.cpp
        src/model/nbt/TagDouble.h
        src/model/nbt/TagByteArray.cpp
        src/model/nbt/TagByteArray.h
        src/model/nbt/TagString.cpp
        src/model/nbt/TagString.h
        src/model/nbt/TagList.cpp
        src/model/nbt/TagList.h
        src/model/nbt/TagIntArray.cpp
        src/model/nbt/TagIntArray.h
        src/model/nbt/TagLongArray.cpp
        src/model/nbt/TagLongArray.h
        src/model/world/BlockEntityInfo.cpp
        src/model/world/BlockEntityInfo.h
        src/model/world/LightUpdateData.cpp
        src/model/world/LightUpdateData.h
        src/renderer/model/Model.cpp
        src/renderer/model/Model.h
        src/renderer/Face.cpp
        src/renderer/Face.h
        src/renderer/Atlas.h
        src/renderer/Atlas.cpp src/renderer/AssetManager.cpp src/renderer/AssetManager.h src/renderer/file.h src/renderer/core/Box.h src/renderer/model/Element.cpp src/renderer/model/Element.h src/renderer/model/FaceInfo.cpp src/renderer/model/FaceInfo.h)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake")
target_link_libraries(${PROJECT_NAME} libglfw3.dylib)
target_link_libraries(${PROJECT_NAME} libz.a)
find_package(glm REQUIRED)
include_directories("/usr/local/Cellar/glm/0.9.9.8/include")
target_link_libraries(${PROJECT_NAME} glm::glm)

set(ASSET_DIR ./assets)
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${ASSET_DIR}")