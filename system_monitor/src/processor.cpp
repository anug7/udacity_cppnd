#include "processor.h"

/*
 * Return the aggregate CPU utilization
 * Refer: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
 * 
 */
float Processor::Utilization() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, cpu;
  int user, nice, system, irq, softirq, steal;
  int idle, iowait;
  if (filestream.is_open()) {
      if(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> cpu;
        linestream >> user >> nice >> system;
        linestream >> idle >> iowait;
        linestream >> irq >> softirq >> steal;
        auto total_used = (user + nice + system + irq + softirq + steal);
        float total_idle = (idle + iowait);
        float val = (total_used - prev_used) / (total_used - prev_used + total_idle - prev_idle);
        prev_idle = total_idle;
        prev_used = total_used;
        return val;
      }
  }
  return 0.0;
}
