# Cli Comment

A CLI app for Linux to create a file and write custom comments for multiple programming languages.

## Features

- Create a new file and write custom comments for more than 10 programming languages
- Supported languages:
  - Python
  - Java
  - JavaScript
  - Go
  - C
  - C++
  - C#
  - Ruby
  - Swift
  - PHP
  - Rust

## Installation

1. Download the latest release from the GitHub repository
2. Extract the downloaded file to a directory on your system
3. Add the extracted directory to your system's `PATH` environment variable
4. Make the `clicomment.sh` script executable with the command `chmod +x clicomment.sh`

## Usage

Run the `clicomment.sh` script with the `-l` flag followed by the desired programming language. For example, to create a new Python file with comments, run the following command:
```bash
./clicomment.sh -l python -o myfile.py
