#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> cpu_info = LinuxParser::CpuUtilization();
  
  long int user_int = std::stoi(cpu_info[0]);
  long int nice_int = std::stoi(cpu_info[1]);
  long int system_int = std::stoi(cpu_info[2]);
  long int idle_int = std::stoi(cpu_info[3]);
  long int iowait_int = std::stoi(cpu_info[4]);
  long int irq_int = std::stoi(cpu_info[5]);
  long int softirq_int = std::stoi(cpu_info[6]);
  long int steal_int = std::stoi(cpu_info[7]);

  float total_idle = idle_int + iowait_int;
  float total_non_idle = user_int + nice_int + system_int + irq_int + softirq_int + steal_int;

  float total = total_idle + total_non_idle;
  
  
//   calculate differences from current
  float total_diff = total  - this->current_total;
  float total_idle_diff = total_idle - this->current_total_idle;

  float cpu_utilization = (total_diff - total_idle_diff) / total_diff;

  this->current_total = total;
  this->current_total_idle = total_idle;
  
  return cpu_utilization;
}