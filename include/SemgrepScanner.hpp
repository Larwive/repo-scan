#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "issue.hpp"
#include "scanner.hpp"

namespace fs = std::filesystem;

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
        fs::path output_dir = fs::temp_directory_path() / "repo-scan" / "semgrep";
        fs::create_directories(output_dir);

        fs::path json_out = output_dir / "results.json";
        fs::path log_out = output_dir / "run.log";

        std::string semgrep_cmd =
            "semgrep scan --json -o " + json_out.string() + " " + repoPath + " > " + log_out.string() + " 2>&1";
        std::system(semgrep_cmd.c_str());

        std::vector<Issue> issues;
        std::ifstream file(json_out);
        if (file.is_open()) {
            nlohmann::json j;
            try {
                file >> j;
                for (const auto &result : j["results"]) {
                    issues.push_back({"semgrep", result["check_id"], result["extra"]["severity"], result["path"],
                                      result["extra"]["message"]});
                }
            } catch (const nlohmann::json::exception &e) {
                std::cerr << "Semgrep JSON parse error: " << e.what() << "\n";
            }
        }
        return issues;
    }
};
