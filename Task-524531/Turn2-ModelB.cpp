#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

template<typename T>
class Image {
public:
    int width, height;
    std::unique_ptr<T[]> data;

    Image(int w, int h) : width(w), height(h) {
        data = std::make_unique<T[]>(w * h);
    }

    T& operator()(int x, int y) {
        return data[y * width + x];
    }
};

template<typename T>
void apply_filter(const Image<T>& img, const std::vector<T>& filter, Image<T>& output) {
    int filterSize = filter.size();
    int halfFilterSize = filterSize / 2;

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            T pixelValue = 0;
            int filterIndex = 0;

            for (int f = -halfFilterSize; f <= halfFilterSize; ++f) {
                int px = std::clamp(x + f, 0, img.width - 1);
                pixelValue += img(px, y) * filter[filterIndex++];
            }

            output(x, y) = pixelValue;
        }
    }
}

template<typename T>
void apply_geometric_transform(const Image<T>& img, T scaleX, T scaleY, Image<T>& output) {
    for (int y = 0; y < output.height; ++y) {
        for (int x = 0; x < output.width; ++x) {
            int srcX = static_cast<int>(x / scaleX);
            int srcY = static_cast<int>(y / scaleY);
            output(x, y) = img(std::clamp(srcX, 0, img.width - 1), std::clamp(srcY, 0, img.height - 1));
        }
    }
}

typedef std::function<void(const Image<int>&, const std::vector<int>&, Image<int>&)> FilterFunction;
typedef std::function<void(const Image<int>&, T, T, Image<int>&)> GeometricTransformFunction;

class TransformationPipeline {
private:
    std::vector<FilterFunction> filters;
    std::vector<GeometricTransformFunction> transforms;

public:
    void add_filter(FilterFunction filter) {
        filters.push_back(filter);
    }

    void add_transform(GeometricTransformFunction transform) {
        transforms.push_back(transform);
    }

    void process(Image<int>& img) {
        Image<int> output(img.width, img.height);

        for (const auto& filter : filters) {
            std::vector<int> kernel = {1, 2, 1}; // Example filter
            filter(img, kernel, output);
            img = std::move(output);
            output = Image<int>(img.width, img.height);
        }

        for (const auto& transform : transforms) {
            T scaleX = 1.5;
            T scaleY = 1.5;
            transform(img, scaleX, scaleY, output);
            img = std::move(output);
        }
    }
};

int main() {
    Image<int> img(800, 600);

    // Initialize image data...

    TransformationPipeline pipeline;
    pipeline.add_filter(std::bind(&apply_filter<int>, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    pipeline.add_transform(std::bind(&apply_geometric_transform<int>, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    pipeline.process(img);

    return 0;
}
