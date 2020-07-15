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
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  
  Process(int pid);
  // TODO: Declare any necessary private members
 private:
  int _pid;
  std::string _user;
  std::string _command;
};

#endif