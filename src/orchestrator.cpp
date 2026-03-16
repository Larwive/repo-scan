#include <memory>

#include "SemgrepScanner.hpp"
#include "orchestrator.hpp"
#include "scanner.hpp"

ScanOrchestrator::ScanOrchestrator() {
  auto semgrep = std::make_unique<SemgrepScanner>();
  if (semgrep->isAvailable()) {
    scanners.push_back(std::move(semgrep));
  }
}

Report ScanOrchestrator::run(const std::string &repoUrl) {
  std::string repo_path = std::string(getenv("HOME")) + "/tmp/repo-scan";
  std::string cmd = "git clone " + repoUrl + " " + repo_path;
  std::system(cmd.c_str());

  Report report;

  for (auto &scanner : scanners) {
    auto issue = scanner->scan(repo_path);
    report.addIssue(issue);
  }

  return report;
}
