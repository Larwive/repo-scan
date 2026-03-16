#pragma once

#include <string>
#include <vector>

#include "issue.hpp"

class Report {
private:
  std::vector<Issue> issues;

public:
  const std::string repoUrl;

  void addIssue(const Issue &issue) { issues.push_back(issue); }

  void print() const {
    for (const auto &issue : issues) {
      issue.print();
    }
  };
};
