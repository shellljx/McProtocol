//
// Created by 李金祥 on 2022/6/7.
//

#pragma once
#include <vector>
#include "../../../Packet.h"
#include "model/nbt/TagCompound.h"
#include "model/world/BlockEntityInfo.h"
#include "model/world/LightUpdateData.h"

namespace McProtocol {
class ServerChunkDataPacket : public Packet {
 public:
  ServerChunkDataPacket();
  ~ServerChunkDataPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  DecodeStream getChunkData() const {
    return DecodeStream(chunkData_->data(), chunkData_->length());
  }

  int getX() const{
    return x_;
  }

  int getZ() const{
    return z_;
  }

 private:
  int x_;
  int z_;
  std::shared_ptr<TagCompound> heightMaps_ = nullptr;
  std::unique_ptr<ByteData> chunkData_ = nullptr;
  std::vector<std::unique_ptr<BlockEntityInfo>> blockEntities_;
  std::unique_ptr<LightUpdateData> lightUpdateData_;
};
}