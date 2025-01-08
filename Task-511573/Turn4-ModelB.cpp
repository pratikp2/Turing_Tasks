// Example using polymorphism
   #include <iostream>
   #include <string>
   #include <memory>

   class StringEncoding {
   public:
       virtual ~StringEncoding() = default;
       virtual void printString(const std::string& str) const = 0;
   };

   class UTF8Encoding : public StringEncoding {
   public:
       void printString(const std::string& str) const override {
           std::cout << "UTF-8: " << str << std::endl;
       }
   };

   class UTF16Encoding : public StringEncoding {
   public:
       void printString(const std::string& str) const override {
           std::wstring wstr(str.begin(), str.end());
           std::wcout << L"UTF-16: " << wstr << std::endl;
       }
   };

   int main() {
       std::unique_ptr<StringEncoding> encoding;

#ifdef ENCODING_UTF8
       encoding = std::make_unique<UTF8Encoding>();
#elif defined(ENCODING_UTF16)
       encoding = std::make_unique<UTF16Encoding>();
#endif

       if (encoding) {
           std::string sampleString = "Hello, World!";
           encoding->printString(sampleString);
       } else {
           std::cout << "Unknown Encoding" << std::endl;
       }
       return 0;
   }
