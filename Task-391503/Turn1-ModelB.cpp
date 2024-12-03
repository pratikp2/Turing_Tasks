#include <iostream>
#include <memory>

class Document; // Forward declaration

class DocumentState {
public:
    virtual ~DocumentState() = default;
    virtual void publish(Document* doc) = 0;
    virtual void edit(Document* doc) = 0;
};

class DraftState : public DocumentState {
public:
    void publish(Document* doc) override;
    void edit(Document* doc) override {
        std::cout << "Draft: Editing document.\n";
    }
};

class ModerationState : public DocumentState {
public:
    void publish(Document* doc) override;
    void edit(Document* doc) override {
        std::cout << "Moderation: Changes need approval before publishing.\n";
    }
};

class PublishedState : public DocumentState {
public:
    void publish(Document* doc) override {
        std::cout << "Published: Document is already published.\n";
    }
    void edit(Document* doc) override {
        std::cout << "Published: Can't edit a published document. Please revert to draft.\n";
    }
};

class Document {
private:
    std::unique_ptr<DocumentState> state_;

public:
    Document() : state_(std::make_unique<DraftState>()) {}

    void setState(std::unique_ptr<DocumentState> state) {
        state_ = std::move(state);
    }

    void publish() {
        state_->publish(this);
    }

    void edit() {
        state_->edit(this);
    }
};

// Implement the methods that transition between states
void DraftState::publish(Document* doc) {
    std::cout << "Draft: Submitting document for moderation.\n";
    doc->setState(std::make_unique<ModerationState>());
}

void ModerationState::publish(Document* doc) {
    std::cout << "Moderation: Document approved and published.\n";
    doc->setState(std::make_unique<PublishedState>());
}

int main() {
    Document doc;

    doc.edit();      // Output: Draft: Editing document.
    doc.publish();   // Output: Draft: Submitting document for moderation.
    doc.edit();      // Output: Moderation: Changes need approval before publishing.
    doc.publish();   // Output: Moderation: Document approved and published.
    doc.edit();      // Output: Published: Can't edit a published document.

    return 0;
}
