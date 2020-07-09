#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "format.h"

using std::string;

// TODO: Complete this helper function Convert 
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hour = seconds/3600;
  seconds = seconds%3600;
  int min = seconds/60;
  seconds = seconds%60;
  int secs = seconds;
  std::stringstream sstream;
  sstream << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << min << ':' << std::setw(2) << secs;  
  return sstream.str();
}