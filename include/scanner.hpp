#pragma once

#include <string>

#include "issue.hpp"

class Scanner {
public:
  Scanner(const std::string &name) : name(name) {}

  std::string name;

  virtual bool isAvailable() const = 0;

  virtual Issue scan(const std::string &repoPath) = 0;
};
