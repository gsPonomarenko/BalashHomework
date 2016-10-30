//Copyright Ponomarenko Grigory 2016 (c)
#pragma once

#include "BalashHomeworkTest.h"

void main() {
  std::string inputPath = "commands.txt";
  std::string command;
  std::fstream inFile(inputPath, std::ios::in);

  system("mkdir output");
  system("mkdir terminal");

  if (!inFile.fail()) {
    /* Input file is opened seccesfully. */

    /* Read coomands from file. */
    /* Launch BalashHomework for testing. */
    int i = 0;
    std::getline(inFile, command);
    for (int i = 0; i < COMMANDS_COUNT; i++) {
      /* Save terminal output into file. */
      command = command + " > terminal/terminal" + std::to_string(i+1) + ".txt";
      system(command.c_str());
      std::getline(inFile, command);
    }

    inFile.close();
  } else {
    /* Can't open input file. */
    std::cout << ("Can't open file.");
  }

  std::string sampleTerminalPath;
  std::fstream sampleTerminalFile;
  std::string terminalPath;
  std::fstream terminalFile;

  std::string sampleOutputPath;
  std::fstream sampleOutputFile;
  std::string outputPath;
  std::fstream outputFile;

  /* Compare terminal input and input file with samples. */
  /* If files are equal test is complete. */
  for (int i = 0; i < COMMANDS_COUNT; i++) {
    sampleTerminalPath = "samples/terminal/terminal";
    sampleTerminalPath = sampleTerminalPath + std::to_string(i + 1) + ".txt";
    sampleTerminalFile = std::fstream(sampleTerminalPath, std::ios::in);

    terminalPath = "terminal/terminal";
    terminalPath = terminalPath + std::to_string(i + 1) + ".txt";
    terminalFile = std::fstream(terminalPath, std::ios::in);

    sampleOutputPath = "samples/output/output";
    sampleOutputPath = sampleOutputPath + std::to_string(i + 1) + ".txt";
    sampleOutputFile = std::fstream(sampleOutputPath, std::ios::in);

    outputPath = "output/output";
    outputPath = outputPath + std::to_string(i + 1) + ".txt";
    outputFile = std::fstream(outputPath, std::ios::in);

    if (terminalFile.is_open() && sampleTerminalFile.is_open()) {
      if (equalFiles(terminalFile, sampleTerminalFile)) {
        if (outputFile.is_open() && sampleOutputFile.is_open()) {
          if (equalFiles(outputFile, sampleOutputFile)) {
            std::cout << "Test " + std::to_string(i + 1);
            std::cout << " is passed.\n";
          } else {
            std::cout << "Test " + std::to_string(i + 1);
            std::cout << " is not passed.\n";
          }
        } else if (outputFile.fail() && sampleOutputFile.fail()) {
          std::cout << "Test " + std::to_string(i + 1);
          std::cout << " is passed.\n";
        } else {
          std::cout << "Test " + std::to_string(i + 1);
          std::cout << " is not passed.\n";
        }
      } else {
        std::cout << "Test " + std::to_string(i + 1);
        std::cout << " is not passed.\n";
      }
    } else {
      std::cout << "Test " + std::to_string(i + 1);
      std::cout << " is not passed.\n";
    }
  } system("pause");
}

bool equalFiles(std::fstream& in1, std::fstream& in2) {
  /* Compare two filestreams function. */
  std::fstream::pos_type size1, size2;

  size1 = in1.seekg(0, std::fstream::end).tellg();
  in1.seekg(0, std::fstream::beg);

  size2 = in2.seekg(0, std::fstream::end).tellg();
  in2.seekg(0, std::fstream::beg);

  if (size1 != size2)
    return false;

  static const size_t BLOCKSIZE = 4096;
  size_t remaining = size1;

  while (remaining) {
    char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
    size_t size = std::min(BLOCKSIZE, remaining);

    in1.read(buffer1, size);
    in2.read(buffer2, size);

    if (0 != memcmp(buffer1, buffer2, size))
      return false;

    remaining -= size;
  }

  return true;
}