#pragma once

#include <cstdio>
#include <string>

class Issue {
public:
  Issue(const std::string &scanner, const std::string &type,
        const std::string &severity, const std::string &file,
        const std::string &description)
      : scanner(scanner), type(type), severity(severity), file(file),
        description(description) {}

  const std::string scanner;
  const std::string type;
  const std::string severity;
  const std::string file;
  const std::string description;

  void print() const {
    printf("%s: %s (%s) in %s\n", scanner.c_str(), type.c_str(),
           severity.c_str(), file.c_str());
    printf("%s\n", description.c_str());
  }
};
