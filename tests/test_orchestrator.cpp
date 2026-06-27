#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>
#include "orchestrator.hpp"

namespace fs = std::filesystem;

class OrchestratorTest : public ::testing::Test {
protected:
  fs::path fixture_path;

  void SetUp() override {
      fixture_path = fs::temp_directory_path() / "repo-scan-test-fixture";
      fs::create_directories(fixture_path);
  
      // Initialize a git repo.
      std::system(("git init " + fixture_path.string()).c_str());
      std::system(("git -C " + fixture_path.string() + " config user.email 'test@test.com'").c_str());
      std::system(("git -C " + fixture_path.string() + " config user.name 'Test'").c_str());
  
      // Create a file with a known vulnerability.
      std::ofstream f(fixture_path / "vuln.py");
      f << "import subprocess\nsubprocess.call(input(), shell=True)\n";
      f.close();
  
      // Stage and commit it so git ls-files sees it.
      std::system(("git -C " + fixture_path.string() + " add vuln.py").c_str());
      std::system(("git -C " + fixture_path.string() + " commit -m 'fixture'").c_str());
  }

  void TearDown() override {
    fs::remove_all(fixture_path);
  }
};

TEST_F(OrchestratorTest, LocalRepoIsScanned) {
  ScanOrchestrator orchestrator;
  auto report = orchestrator.run(fixture_path.string());
  EXPECT_FALSE(report.getIssues().empty());
}

TEST_F(OrchestratorTest, SkippedScannerProducesNoResults) {
  ScanOrchestrator orchestrator({"semgrep"});
  auto report = orchestrator.run(fixture_path.string());
  EXPECT_TRUE(report.getIssues().empty());
}