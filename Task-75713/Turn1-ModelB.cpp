#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string>
#include <vector>

// Function to generate a random key
std::vector<uint8_t> generateRandomKey(size_t length) {
  std::vector<uint8_t> key(length);
  RAND_bytes(&key[0], length);
  return key;
}

// Function to encrypt data using AES-256-GCM
std::vector<uint8_t> encryptData(const std::vector<uint8_t> &key,
                                 const std::vector<uint8_t> &plaintext) {
  std::vector<uint8_t> ciphertext;
  ciphertext.resize(plaintext.size() + AES_GCM_TAG_SIZE);

  EVP_CIPHER_CTX *ctx;

  ctx = EVP_CIPHER_CTX_new();
  if (ctx == nullptr) {
    throw std::runtime_error("EVP_CIPHER_CTX_new failed");
  }

  int ret =
      EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, &key[0], nullptr);
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_EncryptInit_ex failed");
  }

  size_t ciphertext_len = 0;
  ret = EVP_EncryptUpdate(ctx, &ciphertext[0], &ciphertext_len, &plaintext[0],
                          plaintext.size());
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_EncryptUpdate failed");
  }

  ret = EVP_EncryptFinal_ex(ctx, &ciphertext[ciphertext_len], &ciphertext_len);
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_EncryptFinal_ex failed");
  }

  ciphertext.resize(ciphertext_len);
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext;
}

// Function to decrypt data using AES-256-GCM
std::vector<uint8_t> decryptData(const std::vector<uint8_t> &key,
                                 const std::vector<uint8_t> &ciphertext) {
  std::vector<uint8_t> plaintext;
  plaintext.resize(ciphertext.size() - AES_GCM_TAG_SIZE);

  EVP_CIPHER_CTX *ctx;

  ctx = EVP_CIPHER_CTX_new();
  if (ctx == nullptr) {
    throw std::runtime_error("EVP_CIPHER_CTX_new failed");
  }

  int ret =
      EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, &key[0], nullptr);
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptInit_ex failed");
  }

  size_t plaintext_len = 0;
  ret = EVP_DecryptUpdate(ctx, &plaintext[0], &plaintext_len, &ciphertext[0],
                          ciphertext.size() - AES_GCM_TAG_SIZE);
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptUpdate failed");
  }

  ret = EVP_DecryptFinal_ex(ctx, &plaintext[plaintext_len], &plaintext_len);
  if (ret != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptFinal_ex failed");
  }

  plaintext.resize(plaintext_len);
  EVP_CIPHER_CTX_free(ctx);

  return plaintext;
}

int main() {
  // Original data to be encrypted
  std::string plaintextData = "Welcome to the Secret World!";
  std::vector<uint8_t> plaintext(plaintextData.begin(), plaintextData.end());

  // Generate a random 256-bit key
  std::vector<uint8_t> key = generateRandomKey(32);

  // Encryption
  std::vector<uint8_t> ciphertext = encryptData(key, plaintext);

  // Decryption
  std::vector<uint8_t> decryptedData = decryptData(key, ciphertext);

  // Display the decrypted result
  std::string decryptedString(decryptedData.begin(), decryptedData.end());
  std::cout << "Decrypted Data: " << decryptedString << std::endl;

  return 0;
}