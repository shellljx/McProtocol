//
// Created by 李金祥 on 2022/5/28.
//

#include "EncryptionCodec.h"
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

namespace McProtocol {

EncryptionCodec::EncryptionCodec() {

}

EncryptionCodec::~EncryptionCodec() {
  if (encryption_context != nullptr) {
    EVP_CIPHER_CTX_free(encryption_context);
    encryption_context = nullptr;
  }

  if (decryption_context != nullptr) {
    EVP_CIPHER_CTX_free(decryption_context);
    decryption_context = nullptr;
  }
}

void EncryptionCodec::setEnable() {
  enable = true;
}

void EncryptionCodec::encode(const unsigned char *in, int length, unsigned char *out, int &outLength) {
  if (encryption_context == nullptr) {
    throw std::runtime_error("encode openssl was not init");
  }
  out = new unsigned char[length + blocksize];
  EVP_EncryptUpdate(encryption_context, out, &outLength, in, length);
}

std::unique_ptr<ByteData> EncryptionCodec::decode(const unsigned char *in, int length) {
  if (decryption_context == nullptr || !enable) {
    return ByteData::MakeCopy(in, length);
  }

  unsigned char out[length + blocksize];
  int outLength = 0;
  EVP_DecryptUpdate(decryption_context, out, &outLength, in, length);
  if (outLength > 0) {
    return ByteData::MakeCopy(out, outLength);
  }
  return nullptr;
}
}