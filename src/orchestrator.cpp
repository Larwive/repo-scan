#include <filesystem>
#include <iostream>
#include <memory>

#include "SemgrepScanner.hpp"
#include "orchestrator.hpp"
#include "scanner.hpp"

namespace fs = std::filesystem;

ScanOrchestrator::ScanOrchestrator() {
  auto semgrep = std::make_unique<SemgrepScanner>();
  if (semgrep->isAvailable()) {
    scanners.push_back(std::move(semgrep));
    std::cout << "Semgrep scanner added to queue.\n";
  } else {
    std::cout << "Semgrep scanner skipped.\n";
  }
}

Report ScanOrchestrator::run(const std::string &repoUrl) {
  std::string repo_scan_path = std::string(getenv("HOME")) + "/repo-scanned/";
  std::string mkdir_command = "mkdir -p " + repo_scan_path;
  std::system(mkdir_command.c_str());

  std::string repo_name = repoUrl.substr(repoUrl.find_last_of("/") + 1);
  std::string repo_path = repo_scan_path + repo_name;

  if (fs::exists(repo_path)) {
    if (fs::exists(repo_path + "/.git")) {
      std::cout << "Repository already present, skipping clone.\n";
    } else {
      std::cerr << "Error: '" << repo_path
                << "' exists but is not a git repository. Naming error ?\n";
      return {};
    }
  } else {
    std::string cmd = "git clone " + repoUrl + " " + repo_path;
    std::system(cmd.c_str());
  }

  Report report;
  for (auto &scanner : scanners) {
    auto issues = scanner->scan(repo_path);
    report.addIssues(issues);
  }
  return report;
}
