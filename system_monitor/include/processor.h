#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <fstream>
#include <regex>
#include <string>

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();

  //Declare any necessary private members
 private:
  long prev_idle{0}, prev_used{0};
};

#endif
