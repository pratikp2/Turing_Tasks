#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Database {
public:
    virtual ~Database() = default;
    virtual std::string fetchUserById(int id) = 0;
};

class UserService {
public:
    explicit UserService(Database* database) : database_(database) {}

    std::string getUserById(int id) {
        return database_->fetchUserById(id);
    }

private:
    Database* database_;
};

class UserServiceTest : public ::testing::Test {
protected:
    std::unique_ptr<Database> mockDatabase_;
    UserService userService_;

    void SetUp() override {
        mockDatabase_ = std::make_unique<testing::NiceMock<Database>>();
        userService_ = UserService(mockDatabase_.get());
    }
};

TEST_F(UserServiceTest, GetUserById_ShouldReturnUserFromDatabase) {
    EXPECT_CALL(*mockDatabase_, fetchUserById(123))
        .WillOnce(testing::Return("User 123"));

    std::string result = userService_.getUserById(123);

    EXPECT_EQ("User 123", result);
}

TEST_F(UserServiceTest, GetUserById_ShouldReturnEmptyStringForNonExistentUser) {
    EXPECT_CALL(*mockDatabase_, fetchUserById(456))
        .WillOnce(testing::Return(""));

    std::string result = userService_.getUserById(456);

    EXPECT_STREQ("", result.c_str());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}