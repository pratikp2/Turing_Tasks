#include <hiredis/hiredis.h>
#include <iostream>
#include <string>

int main() {
    redisContext* context = redisConnect("localhost", 6379);
    if (context == NULL || context->err) {
        if (context) {
            std::cout << "Error: " << context->errstr << std::endl;
            redisFree(context);
        } else {
            std::cout << "Connection error: can't allocate redis context." << std::endl;
        }
        return 1;
    }
    
    // Set a key-value pair
    redisReply* reply = (redisReply*)redisCommand(context, "SET key value");
    if (reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0) {
        std::cout << "Key-value pair set successfully." << std::endl;
    } else {
        std::cout << "Error setting key-value pair." << std::endl;
    }
    freeReplyObject(reply);
    
    // Get the value of a key
    reply = (redisReply*)redisCommand(context, "GET key");
    if (reply->type == REDIS_REPLY_STRING) {
        std::cout << "Value: " << reply->str << std::endl;
    } else if (reply->type == REDIS_REPLY_NIL) {
        std::cout << "Key not found." << std::endl;
    } else {
        std::cout << "Error getting key." << std::endl;
    }
    freeReplyObject(reply);
    
    redisFree(context);
    return 0;
}