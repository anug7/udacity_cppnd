#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:

  Process(int _p): _pid(_p){
    _cmd = LinuxParser::Command(_pid);
    _user = LinuxParser::User(_pid);
  }
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization() const;                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

  //Declare any necessary private members
 private:
   int _pid{0};
   std::string _cmd, _user;
};

#endif
