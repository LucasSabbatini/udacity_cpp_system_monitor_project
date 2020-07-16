#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() { return _pid; }
  std::string User() { return _user; }
  std::string Command() { return _command; }
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process a);
  
  Process(int pid);
 private:
  int _pid;
  std::string _user;
  std::string _command;
};

#endif