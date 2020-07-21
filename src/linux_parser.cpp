#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

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
  string os, version, kernel;
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

float LinuxParser::MemoryUtilization() {
  float utilization;
  float mem_total_int;
  float mem_free_int;
  string line;
  string key;
  string value;
  string kb;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kb) {
        if (key == "MemTotal:") {
          mem_total_int = std::stof(value);
        }
        if (key == "MemFree:") {
          mem_free_int = std::stof(value);
        }
      }
    }
    utilization = (mem_total_int - mem_free_int) / mem_total_int;
  }
  return utilization;
}

long int LinuxParser::UpTime() {
  long int uptime;
  string suptime;
  string sidle_time;
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> suptime >> sidle_time) {
        uptime = std::stoi(suptime);
        return uptime;
      }
    }
  }
  return 0;
}

vector<string> LinuxParser::CpuUtilization() {
  string line;
  
  string cpu;
  string user;
  string nice;
  string system;
  string idle;
  string iowait;
  string irq;
  string softirq;
  string steal;
  string guest;
  string guest_nice;

  vector<string> cpu_info = {};

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
     while (std::getline(filestream, line)) {
       std::istringstream linestream(line);
       while (linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
         cpu_info.push_back(user);
         cpu_info.push_back(nice);
         cpu_info.push_back(system);
         cpu_info.push_back(idle);
         cpu_info.push_back(iowait);
         cpu_info.push_back(irq);
         cpu_info.push_back(softirq);
         cpu_info.push_back(steal);
         cpu_info.push_back(guest);
         cpu_info.push_back(guest_nice);
         return cpu_info;
       }
     } 
  }
  return cpu_info;
}

int LinuxParser::TotalProcesses() {
  int total_processes;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          total_processes = std::stoi(value);
          return total_processes;
        } else {
          break;
        }
      }
    }
  }
  return 0;
}

int LinuxParser::RunningProcesses() { 
  int running_processes;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          running_processes = std::stoi(value);
          return running_processes;
        } else {
          break;
        }
      }
    }
  }
  return 0;
}

string LinuxParser::Command(int pid) { 
  string command;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, command)) {
      return command;
    }
  }
  return string();
}

string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  float value_;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          value_ = std::stof(value);
          value_ = value_ / 1000;
          std::stringstream ss;
          ss << std::fixed << std::setprecision(2) << value_;
          value = ss.str();
          // return std::to_string(value_);
          return value;
        }
      }
    }
  }
  return string();
}

string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string();
 }

string LinuxParser::User(int pid) { 
  string proc_uid = Uid(pid);
  
  string line;
  string user;
  string x;
  string uid;

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> user >> x >> uid) {
        if (uid == proc_uid) {
          return user;
        }
      }
    }
  }
  return string();
}

long LinuxParser::UpTime(int pid) { 
  long system_uptime = UpTime();
  string line;
  string value;
  
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      int counter = 1;
      while (linestream >> value) {
        if (counter == 22) {
          long starttime = std::stoi(value);
          long puptime = starttime/sysconf(_SC_CLK_TCK);
          return system_uptime - puptime;
        }
        counter++;
      }
    }
  }
  return 0;
}

vector<string> LinuxParser::ParseStat(int pid) {
  string line;
  string value;
  vector<string> words;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      int counter = 1;
      while (linestream >> value) {
        if (counter == 14) {
          words.push_back(value);
        }
        if (counter == 15) {
          words.push_back(value);
        }
        if (counter == 16) {
          words.push_back(value);
        }
        if (counter == 17) {
          words.push_back(value);
        }
        if (counter == 22) {
          words.push_back(value);
        }
        counter++;
      }
    }
  }
  return words;
}


