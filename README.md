# repo-scan

A CLI tool to scan GitHub repositories for potential security threats.

This project helps both maintainers and users identify risks in a repository:

- For maintainers, it detects potential vulnerabilities such as injections, leaked secrets, or unsafe subprocess usage.
- For users, it provides a quick check before cloning or using a repository to spot malicious code or other dangers.

## Features

- Runs security scanners on repositories with minimal setup.
- Currently supports Semgrep.
- Compatibility with other scanners will be added in the future.
- Generates a simple risk report including a security score and detected issues.
- CLI-based, lightweight, and easily extensible.

## Usage

Clone this repository and build using:

```bash
mkdir build
cd build
cmake ..
make
```

Ensure scanners are installed and available in your PATH. **The tool does not automatically install or configure scanners. You must install them yourself.**

## Upcoming Features

- Support for additional scanners.
- Scan local repositories.
- Scan specific commits.
