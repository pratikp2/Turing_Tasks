#include <iostream>
   #include <fstream>
   #include <stdexcept>

   class FileWrapper {
   public:
       explicit FileWrapper(const std::string& filename) {
           file_.open(filename);
           if (!file_.is_open()) {
               throw std::runtime_error("Could not open file");
           }
       }

       ~FileWrapper() {
           if (file_.is_open()) {
               file_.close();
           }
       }

       std::fstream& getFile() { return file_; }

   private:
       std::fstream file_;
   };

   int main() {
       try {
           FileWrapper file("example.txt");
           std::string content;
           std::getline(file.getFile(), content);
           std::cout << content << std::endl;
       } catch (const std::exception& e) {
           std::cerr << "An error occurred: " << e.what() << std::endl;
       }
       return 0;
   }
