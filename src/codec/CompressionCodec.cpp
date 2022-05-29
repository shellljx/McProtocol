//
// Created by 李金祥 on 2022/5/28.
//

#include "CompressionCodec.h"
#include <zlib.h>
#include <string>

namespace McProtocol {
const unsigned long MAX_COMPRESSED_PACKET_LEN = 200 * 1024;

void compress() {

}

void decompress() {
  int ret;
  unsigned have;
  z_stream strm;
  unsigned char out[16384];

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    throw std::runtime_error("zlib init failed");
  }


}

}