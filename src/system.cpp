#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() {
  vector<int> processes_ids = LinuxParser::Pids();
  for (int i: processes_ids) {
    _processes.push_back(Process(i));
  }
  _operating_system = LinuxParser::OperatingSystem();
  _kernel  = LinuxParser::Kernel();
}

std::vector<Process>& System::Processes() {
  std::sort(_processes.begin(), _processes.end(),  [](Process& a, Process& b) {
    return a < b;
  });
  return _processes;
}

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }