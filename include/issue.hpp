#pragma once

#include <cstdio>
#include <string>


/*
 * I had to remove the const from the member variables and add getters because the operator= would be implicitly deleted while being used by vectors.
 */
class Issue {
public:
  Issue(const std::string &scanner, const std::string &type,
        const std::string &severity, const std::string &file,
        const std::string &description)
      : scanner_(scanner), type_(type), severity_(severity), file_(file),
        description_(description) {}

  const std::string &scanner() const { return scanner_; }
  const std::string &type() const { return type_; }
  const std::string &severity() const { return severity_; }
  const std::string &file() const { return file_; }
  const std::string &description() const { return description_; }

  void print() const {
    printf("%s: %s (%s) in %s\n", scanner_.c_str(), type_.c_str(),
           severity_.c_str(), file_.c_str());
    printf("%s\n", description_.c_str());
  }

private:
  std::string scanner_;
  std::string type_;
  std::string severity_;
  std::string file_;
  std::string description_;
};
