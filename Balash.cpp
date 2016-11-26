#include "Balash.h"

/* Initialize pointers by nulls. */
Balash::Balash() {
  oldOrder = NULL;
  cost = NULL;
  cov = NULL;
}

/* Free pointers. */
Balash::~Balash() {
  /* Free array of indexes before sort. */
  if (oldOrder != NULL) {
    delete[] oldOrder;
  }

  /* Free array of costs. */
  if (cost != NULL) {
    delete[] cost;
  }

  /* Free matrix of coverage. */
  if (cov != NULL) {
    for (int i = 0; i < threats; i++) {
      if (cov[i] != NULL) {
        delete[] cov[i];
      }
    }
    delete[] cov;
  }
}

void Balash::initialize(char* input, char* output) {
  /* Initializing balash method solving class. */

  /* Save input and output paths. */
  inputPath = input;
  outputPath = output;
  /* Try to open input file. */
  inFile = std::fstream(inputPath, std::ios::in);
  if (!inFile.fail()) {
    /* Input file is opened seccesfully. */
    /* Read tools count from input file. */
    getToolsCount();
    /* Read cost vector from input file. */
    getCostVector();
    /* Read threats count from input file. */
    getThreatsCount();
    /* Read coverage matrix from input file. */
    getCoverageMatrix();

    inFile.close();
  } else {
    /* Can't open input file. */
    throw BalashException("Can't open input file " + inputPath);
  }
}

void Balash::getToolsCount() {
  /* Temporary string to read lines from input file. */
  std::string temp;

  /* Read cost count from input file. */
  std::getline(inFile, temp);

  /* Try to convert string with cost count to int. */
  try {
    tools = std::stoi(temp);
  } catch (std::invalid_argument ex) {
    throw BalashException("Tools count is incorrect.");
  } catch (std::out_of_range ex) {
    throw BalashException("Tools count is to big.");
  }
  /* Check that cost count is from 1 to 32. */
  if (tools <= 0 || tools > 32) {
    throw BalashException("Tools count must be from 1 to 32");
  }
}

void Balash::getCostVector() {
  /* Temporary string to read lines from input file. */
  std::string temp;

  /* Temporary vector for costs. */
  std::vector<int> vec;

  /* Read cost line from input file. */
  std::getline(inFile, temp);

  /* Check input cost string. */
  checkInputCostString(temp);

  /* Create dynamic array for costs. */
  cost = new int[tools];
  int i = 0;

  /* If string begins with wite space delete it. */
  if (temp.find(' ') == 0) {
    temp = temp.substr(temp.find(' ') + 1, temp.length() - 1);
  }

  /* Loop while cost vector string isn't empty. */
  while(temp.length() > 0) {
    /* Try to convert string with cost to int. */
    try {
      vec.push_back(std::stoi(temp));
    } catch (std::invalid_argument ex) {
      throw BalashException("Cost vector is incorrect.");
    } catch (std::out_of_range ex) {
      throw BalashException("Cost is to big.");
    }

    /* If there are no more numbers clear string. */
    if (temp.find(' ') == std::string::npos) {
      temp.clear();
    } else if (temp.find(' ') == temp.length() - 1) {
      temp.clear();
    } else {
      temp = temp.substr(temp.find(' ') + 1, temp.length() - 1);
      i++;
    }
  }

  /* Check that vector size coincides with tools count. */
  if (vec.size() > tools) {
    throw BalashException("Cost vector is bigger than tools count.");
  } else if (vec.size() < tools) {
    throw BalashException("Cost vector is less than tools count.");
  }

  /* Copy costs from temporary vector to class. */
  for (int i = 0; i < tools; i++) {
    cost[i] = vec[i];
  }

}

void Balash::getThreatsCount() {
  /* Temporary string to read lines from input file. */
  std::string temp;

  /* Read cost count from input file. */
  std::getline(inFile, temp);

  /* Try to convert string with cost count to int. */
  try {
    threats = std::stoi(temp);
  }
  catch (std::invalid_argument ex) {
    throw BalashException("Threats count is incorrect.");
  }
  catch (std::out_of_range ex) {
    throw BalashException("Threats count is to big.");
  }
  /* Check that cost count is from 1 to 32. */
  if (threats <= 0 || threats > 32) {
    throw BalashException("Threats count must be from 1 to 32");
  }
}

void Balash::getCoverageMatrix() {
  /* Temporary string to read lines from input file. */
  std::string temp;
  /* Temporary vector for coverage matrix lines. */
  std::vector<int> vec;

  /* Create dynamic array for coverage matrix. */
  cov = new int*[threats];
  for (int k = 0; k < threats; k++) {
    cov[k] = NULL;
  }

  /* Read coverage matrix line from input file. */
  std::getline(inFile, temp);

  /* Coverage matrix lines counter. */
  int i = 0;

  /* Loop while coverage matrix string isn't empty. */
  while (temp != "") {
    /* Check input coverage matrix string. */
    checkInputCoverageString(temp);
    /* If string begins with wite space delete it. */
    if (temp.find(' ') == 0) {
      temp = temp.substr(temp.find(' ') + 1, temp.length() - 1);
    }

    /* Check if input coverage matrix strings are more then threats count. */
    if (i == threats) {
      std::string msg = "Cost matrix contains " + std::to_string(i + 1);
      msg = msg + " lines. It is bigger than threats count.";
      throw BalashException(msg);
    }
    /* Create dynamic array for coverage matrix line. */
    cov[i] = new int[tools];
    /* Loop while coverage matrix line string isn't empty. */
    while (temp.length() > 0) {
      /* Try to convert string with coverage flag (0 or 1) to int. */
      try {
        vec.push_back(std::stoi(temp));
      } catch (std::invalid_argument ex) {
        throw BalashException("Coverage vector is incorrect.");
      } catch (std::out_of_range ex) {
        throw BalashException("Coverage matrix item is to big.");
      }

      /* If there are no more coverage flags (0 or 1) clear string. */
      if (temp.find(' ') == std::string::npos) {
        temp.clear();
      } else if (temp.find(' ') == temp.length() - 1) {
        temp.clear();
      } else {
        temp = temp.substr(temp.find(' ') + 1, temp.length() - 1);
      }
    }

    /* Check that vector size coincides with tools count. */
    if (vec.size() > tools) {
      std::string msg = "Cost matrix line " + std::to_string(i);
      msg = msg + " is bigger than tools count.";
      throw BalashException(msg);
    } else if (vec.size() < tools) {
      std::string msg = "Cost matrix line " + std::to_string(i);
      msg = msg + " is less than tools count.";
      throw BalashException(msg);
    }

    /* Copy numbers from temporary vector to coverage matrix. */
    for (int j = 0; j < tools; j++) {
      cov[i][j] = vec[j];
    }

    /* Clear temporary vector. */
    vec.clear();

    i++;
    std::getline(inFile, temp);
  }

  /* Check if input coverage matrix strings are less then threats count. */
  if (i < threats) {
    std::string msg = "Cost matrix contains " + std::to_string(i);
    msg = msg + " lines. It is less than threats count.";
    throw BalashException(msg);
  }
}

void Balash::checkInputCostString(std::string str) {
  /* Check that cost string contains only positive numbers. */
  for (int i = 0; i < str.length() - 1; i++) {
    if (str[i] < '0' || str[i] > '9') {
      if (str[i] == '-') {
        throw BalashException("Input cost vector must contain only positive numbers.");
      }
      if (str[i] != ' ') {
        throw BalashException("Input cost vector must contain only digits from 1 to 9.");
      }
    }
  }

  /* Check that cost string does not contain double white spaces. */
  if (str.find("  ") != std::string::npos) {
    throw BalashException("There are more then one white space bettween counts in input file.");
  }
}

void Balash::checkInputCoverageString(std::string str) {
  /* Check that coverage matrix string contains only 0 and 1. */
  for (int i = 0; i < str.length() - 1; i++) {
    if (!(str[i] == '1' || str[i] == '0')) {
      if (str[i] != ' ') {
        throw BalashException("Input file coverage matrix must contain only digits 0 or 1.");
      }
    }
  }

  /* Check that coverage matrix string does not contain double white spaces. */
  if (str.find("  ") != std::string::npos) {
    throw BalashException("There are more then one white space bettween counts in input file.");
  }
}

/* Predicate for sorting pair cost+index by cost. */
bool sortPredicate(std::pair<int, int> i, std::pair<int, int> j) {
  return (i.first < j.first);
}

/* Sort costs from low to high. */
void Balash::sortByCost() {
  /* Initialize vector by pairs cost+index. */
  std::vector<std::pair<int,int>> vec;
  for (int i = 0; i < tools; i++) {
    vec.push_back(std::make_pair(cost[i], i));
  }

  /* Sort vector of pairs cost+index by cost. */
  std::sort(vec.begin(), vec.end(), sortPredicate);

  /* Create array for old indexes in new order. */
  oldOrder = new int[tools];
  /* Create coverage matrix for new order. */
  int** newCov = new int*[threats];
  for (int i = 0; i < threats; i++) {
    newCov[i] = new int[tools];
  }

  /* Initialize new coverage matrix in new order. */
  for (int j = 0; j < tools; j++) {
    std::pair<int, int> pair = vec[j];
    cost[j] = pair.first;
    oldOrder[j] = pair.second;
    for (int i = 0; i < threats; i++) {
      newCov[i][j] = cov[i][pair.second];
    }
  }

  /* Free old coverage matrix. */
  for (int i = 0; i < threats; i++) {
    delete[] cov[i];
  }
  delete[] cov;

  cov = newCov;
}

void Balash::checkCoverageMatrix() {
  /* Check that any threat is covered (no empty lines). */
  int sum = 0;
  for (int i = 0; i < threats; i++) {
    for (int j = 0; j < tools; j++) {
      sum += cov[i][j];
    }
    if (sum == 0) {
      std::string msg = "Threat " + std::to_string(i + 1);
      msg = msg + " is not covered.";
      throw BalashException(msg);
    }
    sum = 0;
  }

  /* Check that any tool cover an threat (no empty rows). */
  sum = 0;
  for (int j = 0; j < tools; j++) {
    for (int i = 0; i < threats; i++) {
      sum += cov[i][j];
    }
    if (sum == 0) {
      std::string msg = "Tool " + std::to_string(j + 1);
      msg = msg + " don't cover any threat.";
      throw BalashException(msg);
    }
    sum = 0;
  }
}

void Balash::printResult(int set) {
  /* Send solution to the output file. */
  int mask = 1;
  int sum = 0;

  /* Try to open output file. */
  std::fstream fs(outputPath, std::ios::out | std::ios::trunc);
  if (!fs.fail()) {
    /* Output file opened seccesfully. */
    /* Print optimal products set with costs. */
    fs << "Optimal solution:\n";
    for (int i = 0; i < tools; i++) {
      if (set & (mask << i)) {
        fs << "Product " + std::to_string(oldOrder[i] + 1);
        fs << " costed " + std::to_string(cost[i]) << std::endl;
        sum += cost[i];
      }
    }

    /* Print total solution cost. */
    fs << "\nTotal solution cost: ";
    fs << std::to_string(sum) << std::endl;

    /* Close output file. */
    fs.close();
  } else {
    /*Output file can't be opened. */
    throw BalashException("Can't open output file " + outputPath);
  }
}

void Balash::compute() {
  /* Solving function. */

  /* Create subsets array. */
  unsigned int subsetsCount = pow(2, tools);
  subsets = new int[subsetsCount];
  for(int i = 0; i < subsetsCount; i++) {
    subsets[i] = 0;
  }

  /* Initialize record and recordSet. */
  record = INT32_MAX;
  recordSet = 0;

  /* Check coverage matrix. */
  checkCoverageMatrix();
  /* Sort cost vector by cost. */
  sortByCost();

  /* Begin branching with value = 0 */
  branch(0);

  delete subsets;

  /* Print solution. */
  printResult(recordSet);
}

void Balash::branch(unsigned int value) {
  int result = 0;

  /* Check subset is not marked as unavailable. */
  if(subsets[value] == 0) {\
    /* Mark that solution for current subset is computed. */
    subsets[value] = 1;
    if(checkSolutionPermissible(value) == true) {
      /* If solution is permissible compute the solution. */
      result = getResultFunction(value);
      if(result < record) {
        /* If result < record then save new record */
        record = result;
        recordSet = value;
      }
      /* Find solutions in branch that are bigger thaen record *
       * and mark then as unavailable.                         */
      checkSolutionsBiggerThenRecord(value, result);
    }

    unsigned int mask = 1;
    /* Getting indexes of tools aren't included in set. */
    for (int i = 0; i < tools; i++) {
      if((mask & value) == 0){
        /* Compute solutions in branch recousively. */
        branch(value | mask);
      }
      mask = mask << 1;
    }
  }
}

bool Balash::checkSolutionPermissible(unsigned int value) {
  unsigned int mask = 1;
  int sum = 0;

  /* Getting indexes of tools included in set. */
  for(int i = 0; i < threats; i++) {
    for (int j = 0; j < tools; j++) {
      if((mask & value) != 0){
        /* Add elem from coverage matrix to summary. */
        sum = sum + cov[i][j];
      }
      mask = mask << 1;
    }

    if(sum == 0) {
      /* If sum == 0 current subset doesn't cover threat 'i'.*/
      return false;
    } else {
      /* Else continue loop. */
      sum = 0;
      mask = 1;
    }
  }

  return true;
}

int Balash::getResultFunction(unsigned int value) {
  unsigned int mask = 1;
  int sum = 0;

  /* Getting indexes of tools included in set. */
  for (int j = 0; j < tools; j++) {
    if((mask & value) != 0){
      /* Add cost of included tool to summary. */
      sum = sum + cost[j];
    }
    mask = mask << 1;
  }

  return sum;
}

void Balash::markBranchAsUnavailable(unsigned int value) {
  /* Mark solution as unavailable. */
  if(subsets[value] == 0) {
    subsets[value] = -1;
  } else {
    return;
  }

  unsigned int mask = 1;
  /* Getting tools that aren't included in set. */
  for (int i = 0; i < tools; i++) {
    if((mask & value) == 0){
      /* Fix the tool and continue recursively. */
      markBranchAsUnavailable(value | mask);
    }
    mask = mask << 1;
  }
}

void Balash::checkSolutionsBiggerThenRecord(unsigned int value, int result) {
  unsigned int mask = 1;
  int sum = result;

  /* Getting tools that aren't included in set. */
  for (int j = 0; j < tools; j++) {
    if((mask & value) == 0){
      /* If sum + tool[j] cost are bigger then record *
       * mark this branch as unavailable.             */
      if(sum + cost[j] > record) {
        markBranchAsUnavailable(value | mask);
      }
    }
    mask = mask << 1;
  }
}
