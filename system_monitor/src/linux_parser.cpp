#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

/* Reads and return the system memory utilization
 * Refer: https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
 * Rough calculation based on Availbale & Total
 */
float LinuxParser::MemoryUtilization() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename;
  std::ifstream filestream(filename);
  std::string line, key;
  float total = 1., avail = 0.0;
  if (filestream.is_open()) {
    if(std::getline(filestream, line))
    {
      //Get total memory 
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> total;
    }
    //Skip used memory section
    std::getline(filestream, line);
    //Get free memory
    if(std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> avail;
    }
  }
  auto used = (1. - (avail/ total));
  return used;
}

//Reads and returns the system uptime
long LinuxParser::UpTime() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename;
  std::ifstream filestream(filename);
  std::string line;
  long up_time = 0;
  if (filestream.is_open()) {
    if(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> up_time;
    }
  }
  return up_time;
}

//Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, dummy;
  long times[10];
  if (filestream.is_open()) {
    if(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> dummy;
      for (int i = 0; i < 10; i++){
        linestream >> times[i];
      }
      auto total_idle = times[CPUStates::kIdle_] + times[CPUStates::kIOwait_];
      auto total_user = times[CPUStates::kUser_] + times[CPUStates::kNice_] +
              times[CPUStates::kSystem_] + times[CPUStates::kIRQ_] +
              times[CPUStates::kSoftIRQ_] + times[CPUStates::kSteal_];
      total_user -= (times[CPUStates::kGuestNice_] + times[CPUStates::kGuest_]);
      return total_idle + total_user;
    }
  }
  return 0;
}

//Read and return the number of active jiffies for a PID
//Refer: https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599 
long LinuxParser::ActiveJiffies(int pid, bool include_child) {
  std::string fname = LinuxParser::kProcDirectory + std::to_string(pid)
                      + LinuxParser::kStatFilename;
  std::string line, key; 
  std::ifstream filestream(fname);
  long utime, stime, cutime, cstime, start_time;
  if (filestream.is_open()) {
    if(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for(int i = 0; i < 13; i++)
        linestream >> key;
      //Include child time also
      linestream >> utime >> stime >> cutime >> cstime; 
      for(int i = 0; i < 4; i++)
        linestream >> key;
      linestream >> start_time;
      //return jiffies from since boot
      if(include_child)
        return utime + stime + cutime + cstime;
      else
        return utime + stime;
    }
  }
  return 0;
}

long LinuxParser::StartTimeJiffies(int pid){
  std::string fname = LinuxParser::kProcDirectory + std::to_string(pid)
                      + LinuxParser::kStatFilename;
  std::string line, key; 
  std::ifstream filestream(fname);
  long start_time;
  if (filestream.is_open()) {
    if(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for(int i = 0; i < 21; i++)
        linestream >> key;
      linestream >> start_time;
      return start_time;
    }
  }
  return 0;
}

//Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, dummy;
  long times[10];
  if (filestream.is_open()) {
    if(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> dummy;
      for (int i = 0; i < 10; i++){
        linestream >> times[i];
      }
      auto total_user = times[CPUStates::kUser_] + times[CPUStates::kNice_] +
              times[CPUStates::kSystem_] + times[CPUStates::kIRQ_] +
              times[CPUStates::kSoftIRQ_] + times[CPUStates::kSteal_];
      total_user -= (times[CPUStates::kGuestNice_] + times[CPUStates::kGuest_]);
      return total_user;
    }
  }
  return 0;
}

//Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, dummy;
  long times[10];
  if (filestream.is_open()) {
    if(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> dummy;
      for (int i = 0; i < 10; i++){
        linestream >> times[i];
      }
      auto total_idle = times[CPUStates::kIdle_] + times[CPUStates::kIOwait_];
      return total_idle;
    }
  }
  return 0;
}

//Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  return {};
}

//Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, key;
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "processes") {
        int value;
        linestream >> value;
        return value;
      }
    }
  }
  return 0;
}

//Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  auto filename = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  std::ifstream filestream(filename);
  std::string line, key;
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "procs_running") {
        int value;
        linestream >> value;
        return value;
      }
    }
  }
  return 0;
}

//Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  auto filename = LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kCmdlineFilename;
  std::ifstream filestream(filename);
  string line;
  if (filestream.is_open()) {
    if(std::getline(filestream, line)){
      return line;
    }
  }

  return string();
}

/*
 * Read and return the memory used by a process
 * Refer: https://www.programmersought.com/article/41501160562/
 */
string LinuxParser::Ram(int pid) {
  std::string fname = LinuxParser::kProcDirectory + std::to_string(pid)
                      + LinuxParser::kStatusFilename;
  std::string line, key; 
  std::ifstream filestream(fname);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream  >> key;
      if(key == "VmRSS"){
        long value;
        linestream >> value;
        value /= 1024;
        return std::to_string(value);
      }
    }
  }
  return string();
}

//Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::string fname = LinuxParser::kProcDirectory + std::to_string(pid)
                      + LinuxParser::kStatusFilename;
  std::string line, key; 
  std::ifstream filestream(fname);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream  >> key;
      if(key == "Uid"){
        std::string value;
        linestream >> value;
        return value;
      }
    }
  }
  return string();
}

//Read and return the user associated with a process
string LinuxParser::User(int pid) {
  auto uid = LinuxParser::Uid(pid);
  std::string line, user, dummy; 
  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream  >> user;
      linestream >> dummy;
      linestream >> dummy;
      if(dummy == uid){
        return user;
      }
    }
  }
  return string();
}

//Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  auto hz = sysconf(_SC_CLK_TCK);
  auto stime = StartTimeJiffies(pid) / hz;
  return UpTime() - stime;
}
