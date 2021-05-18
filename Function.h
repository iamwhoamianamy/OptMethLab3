#pragma once
#include <vector>

class Function
{
public:
   virtual double GetValue(const std::vector<double>&) const = 0;
};