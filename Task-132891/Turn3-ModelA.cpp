#include <iostream>
#include <string>

// Subject interface declares the operations that real subjects and proxies will support.
class Image {
public:
	virtual void display() = 0;
	virtual ~Image() = default;
};

// RealSubject defines the operations that clients request of the subject.
class RealImage : public Image {
public:
	RealImage(const std::string& fileName) : fileName_(fileName) {
		loadImageFromDisk();
	}

	void display() override {
		std::cout << "Displaying " << fileName_ << std::endl;
	}

private:
	void loadImageFromDisk() {
		std::cout << "Loading image " << fileName_ << " from disk..." << std::endl;
		// Simulate loading time
		for (int i = 0; i < 5; ++i) {
			std::cout << ". ";
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		std::cout << std::endl;
	}

private:
	std::string fileName_;
};

// Proxy implements the same interface as RealSubject so that clients can use it interchangeably.
class ProxyImage : public Image {
public:
	ProxyImage(const std::string& fileName) : fileName_(fileName) {}

	void display() override {
		if (realImage_ == nullptr) {
			realImage_ = std::make_unique<RealImage>(fileName_);
		}
		realImage_->display();
	}

private:
	std::unique_ptr<RealImage> realImage_;
	std::string fileName_;
};

int main() {
	std::string imageFile = "high_resolution_photo.jpg";

	{
		std::cout << "\nUsing RealImage directly:\n";
		Image* realImage = new RealImage(imageFile);
		realImage->display();
		delete realImage;
	}

	{
		std::cout << "\nUsing ProxyImage:\n";
		Image* proxyImage = new ProxyImage(imageFile);

		std::cout << "First display via proxy:" << std::endl;
		proxyImage->display(); // Loads the image

		std::cout << "\nSecond display via proxy:" << std::endl;
		proxyImage->display(); // Image is already loaded, no need to reload

		delete proxyImage;
	}

	return 0;
}