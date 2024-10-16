#include <iostream>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <string>

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext) {
  AES_KEY enc_key;
  AES_set_encrypt_key(key, 256, &enc_key);

  int ciphertext_len =
      ((plaintext_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

  AES_cbc_encrypt(plaintext, ciphertext, ciphertext_len, &enc_key, iv,
                  AES_ENCRYPT);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext) {
  AES_KEY dec_key;
  AES_set_decrypt_key(key, 256, &dec_key);

  AES_cbc_encrypt(ciphertext, plaintext, ciphertext_len, &dec_key, iv,
                  AES_DECRYPT);

  return ciphertext_len;
}

int main() {
  const std::string plaintext = "This is a secret message!";
  unsigned char key[32], iv[16];

  // Generate random key and IV
  RAND_bytes(key, sizeof(key));
  RAND_bytes(iv, sizeof(iv));

  // Allocate memory for ciphertext
  int ciphertext_len = encrypt((unsigned char *)plaintext.data(),
                               plaintext.length(), key, iv, nullptr);
  unsigned char *ciphertext = new unsigned char[ciphertext_len];

  // Encrypt
  encrypt((unsigned char *)plaintext.data(), plaintext.length(), key, iv,
          ciphertext);

  // Allocate memory for decrypted text
  unsigned char *decryptedtext = new unsigned char[plaintext.length()];

  // Decrypt
  int decrypted_len =
      decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

  // Output results