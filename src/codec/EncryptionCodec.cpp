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

void EncryptionCodec::encode(const EncodeStream *in, const EncodeStream **out) {

}

void EncryptionCodec::decode(const unsigned char *in, int length, unsigned char *out, int &outLength) {
  if (decryption_context == nullptr) {
    throw std::runtime_error("openssl was not init");
  }

  out = new unsigned char[length + blocksize];
  EVP_DecryptUpdate(decryption_context, out, &outLength, in, length);
}
}