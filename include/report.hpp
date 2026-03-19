#pragma once

#include <string>
#include <vector>

#include "issue.hpp"

class Report {
private:
  std::vector<Issue> issues;

public:
  const std::string repoUrl;

  void addIssue(const std::vector<Issue> &new_issues) { issues.insert(issues.end(), new_issues.begin(), new_issues.end()); }

  void print() const {
    for (const auto &issue : issues) {
      issue.print();
    }
  };
};
