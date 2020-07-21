#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : _pid(pid) {
  _user = LinuxParser::User(_pid);
  _command = LinuxParser::Command(_pid);
}

float Process::CpuUtilization() { 

  long int uptime = LinuxParser::UpTime();
  vector<string> stat_data = LinuxParser::ParseStat(_pid);
  int utime = std::stoi(stat_data[0]);
  int stime = std::stoi(stat_data[1]);
  int starttime = std::stoi(stat_data[4]);
  float total_time = utime + stime;
  long int process_uptime = uptime - (starttime/sysconf(_SC_CLK_TCK)); // total time (active+ idle)
  float cpu_utilization = 100 * ((total_time/sysconf(_SC_CLK_TCK))/process_uptime);
  return cpu_utilization;
}

string Process::Ram() { return LinuxParser::Ram(_pid); }

long int Process::UpTime() { return LinuxParser::UpTime(_pid); }

#include <iostream>
bool Process::operator<(Process a) {
  return this->CpuUtilization() > a.CpuUtilization();
}