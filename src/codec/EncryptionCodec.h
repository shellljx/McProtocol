//
// Created by 李金祥 on 2022/5/28.
//

#pragma once

#include "../io/EncodeStream.h"
#include "../io/DecodeStream.h"

typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

namespace McProtocol {

class EncryptionCodec {
 public:
  EncryptionCodec();
  ~EncryptionCodec();

  void setEnable();
  void encode(const unsigned char *in, int length, unsigned char *out, int &outLength);

  std::unique_ptr<ByteData> decode(const unsigned  char* in, int length);

 private:
  EVP_CIPHER_CTX* encryption_context;
  EVP_CIPHER_CTX* decryption_context;
  unsigned int blocksize = 0;
  bool enable = false;
};
}