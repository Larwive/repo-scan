#include <cstdio>
#include <cstdlib>
#include <string>

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

  Issue scan(const std::string &repoPath) override {
    std::string semgrep_cmd = "semgrep scan --json -o " + repoPath + "/repo-scan/semgrep.json " + repoPath;
    std::system(semgrep_cmd.c_str());

    Issue semgrep_result = {
        "semgrep", // scanner
        "",        // type
        "",        // severity
        "",        // file
        ""         // description
    };
    return semgrep_result;
  }
};
