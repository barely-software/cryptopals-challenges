#pragma once

#include <map>
#include <string>

static std::map<uint8_t, float> english_frequencies = {
  { 'a', 0.017 }, 
  { 'b', 0.044 }, 
  { 'c', 0.052 }, 
  { 'd', 0.032 }, 
  { 'e', 0.028 }, 
  { 'f', 0.040 }, 
  { 'g', 0.016 }, 
  { 'h', 0.042 }, 
  { 'i', 0.073 }, 
  { 'j', 0.0051 }, 
  { 'k', 0.0086 }, 
  { 'l', 0.024 }, 
  { 'm', 0.038 }, 
  { 'n', 0.023 }, 
  { 'o', 0.076 }, 
  { 'p', 0.043 }, 
  { 'q', 0.0022 }, 
  { 'r', 0.028 }, 
  { 's', 0.067 }, 
  { 't', 0.16 }, 
  { 'u', 0.012 }, 
  { 'v', 0.0082 }, 
  { 'w', 0.055 }, 
  { 'x', 0.00045 }, 
  { 'y', 0.0076 }, 
  { 'z', 0.00045 }
};

std::map<uint8_t,float> compute_frequencies(const std::string& input);
float compare_frequencies(std::map<uint8_t, float> m1, std::map<uint8_t, float> m2);
