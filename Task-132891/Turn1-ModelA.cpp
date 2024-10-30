#include<iostream>
using namespace std;

// Subject class - The class whose functionality we want to proxy
class Image {
public:
	void load(const string& filename) {
		cout << "Loading image: " << filename << endl;
	}

	void display() {
		cout << "Displaying the image." << endl;
	}
};

// Proxy class
class ImageProxy {
public:
	ImageProxy(const string& filename) {
		image = new Image;
		image->load(filename);
	}

	~ImageProxy() {
		delete image;
	}

	void display() {
		image->display();
	}

private:
	Image* image;
};

int main() {
	string image_path = "example.jpg";
	
	{
		cout << "Using Direct Image:" << endl;
		Image img;
		img.load(image_path);
		img.display();
	}

	cout << "\nUsing Image Proxy:" << endl;
	ImageProxy proxy(image_path);
	proxy.display();

	return 0;
}