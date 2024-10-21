#include <iostream>
#include <string>
#include <mysql/mysql.h>

int main() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    MYSQL mysql;
    mysql_init(&mysql);