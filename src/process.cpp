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

// #include <time.h>
// std::cout << "Clocks per second: " << CLOCKS_PER_SEC << "\n";
int clock_hz = 100;
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

  long int uptime = LinuxParser::UpTime();
  vector<string> stat_data = LinuxParser::ParseStat(_pid);
//   if (true) {
//     return 0.0;
//   }
  int utime = std::stoi(stat_data[0]);
  int stime = std::stoi(stat_data[1]);
  int cutime = std::stoi(stat_data[2]);
  int cstime = std::stoi(stat_data[3]);
  int starttime = std::stoi(stat_data[4]);

  float total_time = utime + stime + cutime + cstime;
  long int process_uptime = uptime - (starttime/clock_hz);
  float cpu_utilization = 100 * ((total_time/clock_hz)/process_uptime);
  return cpu_utilization;

}

string Process::Ram() { return LinuxParser::Ram(_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }