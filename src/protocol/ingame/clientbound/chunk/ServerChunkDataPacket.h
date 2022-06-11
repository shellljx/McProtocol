//
// Created by 李金祥 on 2022/6/7.
//

#pragma once
#include <vector>
#include "../../../Packet.h"
#include "../../../../bean/nbt/TagCompound.h"
#include "bean/BlockEntityInfo.h"
#include "bean/LightUpdateData.h"

namespace McProtocol {
class ServerChunkDataPacket : public Packet {
 public:
  ServerChunkDataPacket();
  ~ServerChunkDataPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int x_;
  int z_;
  std::shared_ptr<TagCompound> heightMaps_ = nullptr;
  std::unique_ptr<ByteData> chunkData_ = nullptr;
  std::vector<std::unique_ptr<BlockEntityInfo>> blockEntities_;
  std::unique_ptr<LightUpdateData> lightUpdateData_;
};
}