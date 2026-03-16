#include <iostream>
#include <string>

#include "orchestrator.hpp"
#include "report.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) // TODO: Take more arguments for the tools. Allow local
                // repository scanning.
  {
    std::cerr << "Usage: repo-scan <repository_url>\n";
    return 1;
  }

  std::string repoUrl = argv[1];

  try {
    ScanOrchestrator orchestrator;

    Report report = orchestrator.run(repoUrl);

    report.print();

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
