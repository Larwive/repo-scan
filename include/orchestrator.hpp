#pragma once

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "report.hpp"
#include "scanner.hpp"

class ScanOrchestrator {
  public:
    ScanOrchestrator(const std::vector<std::string> &skip = {});

    Report run(const std::string &target, const std::string &clone_dir = "");

  private:
    std::vector<std::unique_ptr<Scanner>> scanners;
};
