
#include <iostream>
#include <string>
#include <jwt-cpp/jwt.h>

class TokenAuthenticator {
private:
  std::string secretKey;

public:
  TokenAuthenticator(const std::string& secretKey) : secretKey(secretKey) {}

  bool authenticateToken(const std::string& token) {
    try {
      Jwt::decode(token, secretKey, true);
      return true;
    } catch (const Jwt::Exception& e) {
      std::cout << "Invalid token: " << e.what() << std::endl;
      return false;
    }
  }

  std::string generateToken(const std::string& userId) {
    Jwt::Claims claims;
    claims.set_iss("your_load_balancer_issuer");
    claims.set_sub(userId);
    claims.set_aud("your_backend_server_audience");
    claims.set_exp(std::chrono::system_clock::now() + std::chrono::seconds(3600)); // Token expires after 1 hour

    return Jwt::encode(claims, secretKey);
  }
};

int main() {
  // Secret key used for signing the tokens
  const std::string secretKey = "your_super_secret_key";
  TokenAuthenticator authenticator(secretKey);

  // Example client request
  std::string clientRequest = "GET /api/data HTTP/1.1\r\nHost: example.com\r\nAuthorization: Bearer YOUR_TOKEN_HERE\r\n\r\n";

  // Extract the token from the request header
  size_t tokenStart = clientRequest.find("Bearer ") + 7;