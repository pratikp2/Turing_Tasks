#include <iostream>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string>

const int keyLength = 32; // 256 bits
const int ivLength = AES_BLOCK_SIZE;

// Function to generate a random key and IV
void generateKeyAndIV(unsigned char *key, unsigned char *iv) {
  RAND_bytes(key, keyLength);
  RAND_bytes(iv, ivLength);
}

// Function to encrypt data
int encrypt(const unsigned char *plaintext, int plaintext_len,
            unsigned char *ciphertext, unsigned char *key, unsigned char *iv) {
  AES_KEY enc_key;
  AES_set_encrypt_key(key, keyLength * 8, &enc_key);

  int ciphertext_len =
      ((plaintext_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

  AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &enc_key, iv,
                  AES_ENCRYPT);

  return ciphertext_len;
}

// Function to decrypt data
int decrypt(const unsigned char *ciphertext, int ciphertext_len,
            unsigned char *plaintext, unsigned char *key, unsigned char *iv) {
  AES_KEY dec_key;
  AES_set_decrypt_key(key, keyLength * 8, &dec_key);

  AES_cbc_decrypt(ciphertext, plaintext, ciphertext_len, &dec_key, iv,
                  AES_DECRYPT);

  // Remove padding bytes
  int plaintext_len = ciphertext_len;
  while (plaintext[plaintext_len - 1] == 0) {
    plaintext_len--;
  }

  return plaintext_len;
}

int main() {
  std::string plaintext = "Welcome to remotask";
  unsigned char key[keyLength], iv[ivLength];
  unsigned char ciphertext[plaintext.size() + AES_BLOCK_SIZE];
  unsigned char decryptedtext[plaintext.size() + AES_BLOCK_SIZE];

  // Generate a random key and IV
  generateKeyAndIV(key, iv);

  // Encrypt data
  int ciphertext_len =
      encrypt(reinterpret_cast<const unsigned char *>(plaintext.data()),
              plaintext.size(), ciphertext, key, iv);

  // Decrypt data
  int decryptedtext_len =
      decrypt(ciphertext, ciphertext_len, decryptedtext, key, iv);

  // Output the decrypted text
  std::cout << "Decrypted Text: "
            << std::string(reinterpret_cast<char *>(decryptedtext),
                           decryptedtext_len)
            << std::endl;

  return 0;
}