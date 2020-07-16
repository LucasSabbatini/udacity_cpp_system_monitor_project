#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu() { return _cpu; }
  std::vector<Process>& Processes();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel() const { return _kernel; }
  std::string OperatingSystem() const { return _operating_system; }
  System();
  
 private:
  Processor _cpu = {};
  std::vector<Process> _processes = {};
  std::string _operating_system;
  std::string _kernel;
};

#endif