#pragma once

#include <string>
#include <vector>

#include "issue.hpp"

class Report {
  private:
    std::vector<Issue> issues;

  public:
    const std::string repoUrl;

    Report() = default;
    explicit Report(const std::string &url) : repoUrl(url) {}

    void addIssues(const std::vector<Issue> &new_issues) { issues.insert(issues.end(), new_issues.begin(), new_issues.end()); }

    void print() const {
        for (const auto &issue : issues) {
            issue.print();
        }
    };

    const std::vector<Issue> &getIssues() const { return issues; }
};
