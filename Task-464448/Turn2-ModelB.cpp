enum class ShapeType {
      CIRCLE,
      SQUARE,
      TRIANGLE
  };

  std::string createShapeDescription(ShapeType shape) {
      switch (shape) {
          case ShapeType::CIRCLE:
              return "Circle";
          case ShapeType::SQUARE:
              return "Square";
          case ShapeType::TRIANGLE:
              return "Triangle";
          default:
              return "Unknown shape";
      }
  }

  void main() {
      ShapeType shape = ShapeType::SQUARE;
      std::cout << createShapeDescription(shape) << std::endl;
  }
