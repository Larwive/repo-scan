#include <iostream>
#include <memory>

#include "SemgrepScanner.hpp"
#include "orchestrator.hpp"
#include "scanner.hpp"

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

  std::string repo_path =
      repo_scan_path + repoUrl.substr(repoUrl.find_last_of("/") + 1);
  std::string cmd = "cd " + repo_scan_path + ";git clone " + repoUrl;
  std::system(cmd.c_str());

  Report report;

  for (auto &scanner : scanners) {
    auto issue = scanner->scan(repo_path);
    report.addIssue(issue);
  }

  return report;
}
