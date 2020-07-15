#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu() { return _cpu; }                  // TODO: See src/system.cpp
  std::vector<Process>& Processes() { return _processes; }  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp DONE
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel() const { return _kernel; }               // TODO: See src/system.cpp
  std::string OperatingSystem() const { return _operating_system; }      // TODO: See src/system.cpp
  System();
  // TODO: Define any necessary private members
 private:
  Processor _cpu = {};
  std::vector<Process> _processes = {};
  std::string _operating_system;
  std::string _kernel;
};

#endif