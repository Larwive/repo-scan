#include <filesystem>
#include <iostream>
#include <memory>

#include "SemgrepScanner.hpp"
#include "orchestrator.hpp"
#include "scanner.hpp"

namespace fs = std::filesystem;

ScanOrchestrator::ScanOrchestrator(const std::vector<std::string> &skip) {
    auto semgrep = std::make_unique<SemgrepScanner>();
    const bool skipped = std::find(skip.begin(), skip.end(), semgrep->name) != skip.end();
    if (!skipped && semgrep->isAvailable()) {
        scanners.push_back(std::move(semgrep));
        std::cout << "Semgrep scanner added to queue.\n";
    }
}

Report ScanOrchestrator::run(const std::string &target, const std::string &clone_dir) {
    std::string repo_path;

    if (fs::exists(target)) {
        repo_path = target; // local repository
    } else {
        const char *home = getenv("HOME");
        std::string base = clone_dir.empty() ? (home ? std::string(home) + "/repo-scanned/"
                                                     : fs::temp_directory_path().string() + "/repo-scanned/")
                                             : clone_dir;

        fs::create_directories(base);

        std::string stripped = target;
        if (!stripped.empty() && stripped.back() == '/')
            stripped.pop_back();
        if (stripped.size() >= 4 && stripped.compare(stripped.size() - 4, 4, ".git") == 0)
            stripped = stripped.substr(0, stripped.size() - 4);
        std::string repo_name = stripped.substr(stripped.find_last_of("/\\") + 1);
        repo_path = base + repo_name;

        if (fs::exists(repo_path)) {
            if (!fs::exists(repo_path + "/.git")) {
                std::cerr << "Error: '" << repo_path << "' exists but is not a git repository.\n";
                return {};
            }
            std::cout << "Repository already present, skipping clone.\n";
        } else {
            int ret = std::system(("git clone " + target + " " + repo_path).c_str()); // TODO: execvp
            if (ret != 0) {
                std::cerr << "Error: git clone failed for '" << target << "'\n";
                return {};
            }
        }
    }

    Report report(repo_path);
    for (auto &scanner : scanners)
        report.addIssues(scanner->scan(repo_path));
    return report;
}
