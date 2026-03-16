#pragma once

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "report.hpp"
#include "scanner.hpp"

class ScanOrchestrator {
public:
  ScanOrchestrator();

  Report run(const std::string &repoUrl);

private:
  std::vector<std::unique_ptr<Scanner>> scanners;
};
