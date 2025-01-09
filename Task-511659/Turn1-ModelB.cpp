#include <iostream>
#include <string>
#include <cstdlib>

enum class UserAction {
    LIKE,
    SHARE,
    COMMENT,
    SCROLL
};

UserAction getRandomUserAction() {
    int random_number = rand() % 4;
    switch (random_number) {
        case 0:
            return UserAction::LIKE;
        case 1:
            return UserAction::SHARE;
        case 2:
            return UserAction::COMMENT;
        default:
            return UserAction::SCROLL;
    }
}

UserAction predictUserAction(const std::string& user_profile, const std::string& post_content) {
    printf("Predicting user action for user '%s' and post '%s'\n", user_profile.c_str(), post_content.c_str());

    // Simple prediction logic based on user profile and post content (for demonstration purposes)
    if (user_profile == "tech_enthusiast" && post_content.find("tech") != std::string::npos) {
        printf("Prediction: User is likely to LIKE the post.\n");
        return UserAction::LIKE;
    } else if (user_profile == "fashion_lover" && post_content.find("fashion") != std::string::npos) {
        printf("Prediction: User is likely to SHARE the post.\n");
        return UserAction::SHARE;
    } else {
        printf("Prediction: User is likely to SCROLL past the post.\n");
        return UserAction::SCROLL;
    }
}

void analyzeUserBehavior(const std::string& user_profile, const std::string& post_content) {
    UserAction actual_action = getRandomUserAction();
    printf("Actual user action: %s\n", 
           actual_action == UserAction::LIKE ? "LIKE" : 
           actual_action == UserAction::SHARE ? "SHARE" : 
           actual_action == UserAction::COMMENT ? "COMMENT" : "SCROLL");

    UserAction predicted_action = predictUserAction(user_profile, post_content);

    if (actual_action == predicted_action) {
        printf("Prediction aligned with user choice!\n");
    } else {
        printf("Prediction mismatch. Actual: %s, Predicted: %s\n",
               (actual_action == UserAction::LIKE ? "LIKE" : actual_action == UserAction::SHARE ? "SHARE" : actual_action == UserAction::COMMENT ? "COMMENT" : "SCROLL"),
               (predicted_action == UserAction::LIKE ? "LIKE" : predicted_action == UserAction::SHARE ? "SHARE" : predicted_action == UserAction::COMMENT ? "COMMENT" : "SCROLL")
               );
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    const std::string user_profiles[] = { "tech_enthusiast", "fashion_lover", "sports_fan", "foodie" };
    const std::string post_contents[] = { "New smartphone launch!", "Latest fashion trends", "Highlights from the football match", "Delicious recipe to try" };

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) { 
            analyzeUserBehavior(user_profiles[i], post_contents[j]);
            printf("\n");
        }
    }

    return 0;
}
