#pragma once

#include <string>
#include <vector>

#include "issue.hpp"

class Scanner {
public:
  Scanner(const std::string &name) : name(name) {}

  std::string name;

  virtual bool isAvailable() const = 0;

  virtual std::vector<Issue> scan(const std::string &repoPath) = 0;
};
