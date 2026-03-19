#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include "issue.hpp"
#include "scanner.hpp"

class SemgrepScanner : public Scanner {
public:
  SemgrepScanner() : Scanner("semgrep") {}

  bool isAvailable() const override {
#ifdef _WIN32
    std::string cmd = "where " + name + " >nul 2>&1";
#else
    std::string cmd = "which " + name + " >/dev/null 2>&1";
#endif
    return std::system(cmd.c_str()) == 0;
  }

  std::vector<Issue> scan(const std::string &repoPath) override {
    std::string semgrep_cmd = "semgrep scan --json -o " + repoPath + "/repo-scan/semgrep.json " + repoPath;
    std::system(semgrep_cmd.c_str());

    std::vector<Issue> issues;
    std::ifstream file(repoPath + "/repo-scan/semgrep.json");
    if (file.is_open()) {
      nlohmann::json j;
      file >> j;
      for (const auto &result : j["results"]) {
        issues.push_back({
            "semgrep",
            result["check_id"],
            result["extra"]["severity"],
            result["path"],
            result["extra"]["message"]
        });
      }
    }
    return issues;
  }
};
