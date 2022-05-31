//
// Created by 李金祥 on 2022/5/28.
//

#include "CompressionCodec.h"
#include <zlib.h>
#include <string>

namespace McProtocol {

std::unique_ptr<ByteData> CompressionCodec::decode(DecodeStream &in) {
  if (enable_) {
    auto dataLength = in.readVerInt();
    if (dataLength <= 0) {
      //datalength is zero without compression
      auto length = in.bytesAvailable();
      return ByteData::MakeWithoutCopy(in.readBytes(length).data(), length);
    } else {
      return deCompression(in, dataLength);
    }
  } else {
    auto length = in.bytesAvailable();
    return ByteData::MakeWithoutCopy(in.readBytes(length).data(), length);
  }
}

std::unique_ptr<McProtocol::ByteData> CompressionCodec::deCompression(DecodeStream& in, int uLength) {
  int ret;
  int chunk = 1024 * 6;
  unsigned have;
  z_stream strm;
  memset(&strm, 0, sizeof(strm));

  unsigned char input[in.bytesAvailable()];
  uint32_t avaliable = in.bytesAvailable();
  memcpy(input, in.readBytes(avaliable).data(), avaliable);

  strm.avail_in = avaliable;
  strm.next_in = input;

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    throw std::runtime_error("zlib init failed");
  }

  unsigned char output[chunk];
  McProtocol::EncodeStream outStream(uLength);
  do {
    strm.avail_out = chunk;
    strm.next_out = output;
    if (strm.avail_in == 0) {
      inflateEnd(&strm);
      return outStream.release();
    }
    ret = inflate(&strm, Z_NO_FLUSH);
    switch (ret) {
      case Z_OK:
      case Z_STREAM_END:have = chunk - strm.avail_out;
        outStream.writeBytes(output, have);
        break;
      default: {
        inflateEnd(&strm);
        throw std::runtime_error("zlib inflate error");
      }
    }
  } while (strm.avail_out == 0);
  inflateEnd(&strm);
  return outStream.release();
}
}