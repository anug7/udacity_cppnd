#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds){ 
  unsigned int hours = seconds / 3600;
  unsigned char minutes = (seconds % 3600) / 60;
  unsigned char sec = (seconds % 3600) % 60;
  return std::to_string(hours) +  ":" + std::to_string(minutes) + ":" + std::to_string(sec);
}
