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
  auto min_str = std::to_string(minutes);
  auto sec_str = std::to_string(sec);
  min_str.insert(0, 2 - min_str.length(), '0');
  sec_str.insert(0, 2 - sec_str.length(), '0');

  return std::to_string(hours) +  ":" + min_str + ":" + sec_str;
}
