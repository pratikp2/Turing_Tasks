#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace rapidjson;

int main() {
  // Load JSON data from a file
  std::ifstream ifs("news_data.json");
  IStreamWrapper isw(ifs);
  Document d;
  d.ParseStream(isw);

  // Check if the JSON parsing was successful
  if (d.HasParseError()) {
    std::cout << "Error parsing JSON: " << GetParseErrorDesc(d.GetParseError())
              << std::endl;
    return 1;
  }

  // Access news articles from the JSON data
  const Value &articles = d["articles"];
  for (SizeType i = 0; i < articles.Size(); i++) {
    const Value &article = articles[i];
    const char *title = article["title"].GetString();
    const char *author = article["author"].GetString();
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    // ... Process other article details ...
  }

  return 0;
}