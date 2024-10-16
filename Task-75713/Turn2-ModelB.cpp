#include <iostream>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <string>

// Function to generate a random initialization vector (IV)
std::string generateIV() {
  unsigned char iv[AES_GCM_IV_LEN];
  RAND_bytes(iv, AES_GCM_IV_LEN);
  return std::string((char *)iv, AES_GCM_IV_LEN);
}

// Function to encrypt data using AES-GCM
std::string encrypt(const std::string &plaintext, const std::string &key,
                    const std::string &iv) {
  EVP_CIPHER_CTX *ctx;

  int ciphertext_len = 0;
  unsigned char ciphertext[plaintext.length() + AES_GCM_TAG_LEN];

  ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);
  EVP_EncryptInit_ex(ctx, nullptr, nullptr, (const unsigned char *)key.data(),
                     (const unsigned char *)iv.data());
  EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len,
                    (const unsigned char *)plaintext.data(),
                    plaintext.length());
  EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len, &ciphertext_len);

  EVP_CIPHER_CTX_free(ctx);

  return std::string((char *)ciphertext, ciphertext_len + AES_GCM_TAG_LEN);
}

// Function to decrypt data using AES-GCM
std::string decrypt(const std::string &ciphertext, const std::string &key,
                    const std::string &iv) {
  EVP_CIPHER_CTX *ctx;

  int plaintext_len = 0;
  unsigned char plaintext[ciphertext.length() - AES_GCM_TAG_LEN];

  ctx = EVP_CIPHER_CTX_new();
  EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);
  EVP_DecryptInit_ex(ctx, nullptr, nullptr, (const unsigned char *)key.data(),
                     (const unsigned char *)iv.data());
  EVP_DecryptUpdate(ctx, plaintext, &plaintext_len,
                    (const unsigned char *)ciphertext.data(),
                    ciphertext.length() - AES_GCM_TAG_LEN);
  EVP_DecryptFinal_ex(ctx, plaintext + plaintext_len, &plaintext_len);

  EVP_CIPHER_CTX_free(ctx);

  return std::string((char *)plaintext, plaintext_len);
}

int main() {
  // Sample key and plaintext
  std::string key = "0123459748abcdef0123459748abcdef"; // 32 bytes for AES-256
  std::string plaintext = "Hello, this is a secret message!";

  // Generate a random IV
  std::string iv = generateIV();

  // Encryption
  std::string ciphertext = encrypt(plaintext, key, iv);

  // Decryption
  std::string decrypted_plaintext = decrypt(ciphertext, key, iv);

  std::cout << "Original Plaintext: " << plaintext << std::endl;
  std::cout << "Encrypted Ciphertext: " << ciphertext << std::endl;
  std::cout << "Decrypted Plaintext: " << decrypted_plaintext << std::endl;

  return 0;
}