//Copyright Grigory Ponomarenko 2016 (c)

#include "Balash.h"
#include <cstring>

void printHelp();

int main(int argc, char* argv[]) {
  Balash balash;
  if (argc > 1) {
    if (!(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) {
      /* If argument is 'help' print help. */
      printHelp();
      exit(0);
    }
  }


  if (argc > 4) {
    if (strcmp(argv[1], "-i") && strcmp(argv[1], "--input")) {
      /* If 1 argument isn't -i or --input stop and exit. */
      std::cout << "Incorrect first argument." << std::endl;
      std::cout << "First argument must be \"-i <path>\" or \"--input <path>." << std::endl;
      std::cout << "Use \"-h\" or \"--help\" to print help." << std::endl;
      exit(0);
    } else if (strcmp(argv[3], "-o") && strcmp(argv[3], "--output")) {
      /* If 1 argument isn't -o or --output stop and exit. */
      std::cout << "Incorrect second argument." << std::endl;
      std::cout << "Second argument must be \"-i <path>\" or \"--input <path>." << std::endl;
      std::cout << "Use \"-h\" or \"--help\" to print help." << std::endl;
      exit(0);
    } else {
      try {
        /* If correct arguments try to read input. */
        balash.initialize(argv[2], argv[4]);

        /* If input files are seccesfully read try to calculate. */
        balash.compute();
      }
      catch (BalashException except) {
        std::cout << except.what() << std::endl;
        exit(0);
      }
    }
  } else {
    printHelp();
    exit(0);
  }
  return 0;
}

void printHelp() {
  /* Print help message. */
  std::cout << "First argument must be \"-i <path>\" or \"--input <path>." << std::endl;
  std::cout << "Second argument must be \"-o <path>\" or \"--output <path>." << std::endl;
  std::cout << "Use \"-h\" or \"--help\" to print help." << std::endl;
}
