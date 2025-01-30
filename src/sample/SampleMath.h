#pragma once
#include <cmath>

class SampleMath 
{
  public:
    SampleMath() = default;
    ~SampleMath () = default;

    double Add(double a, double b);

    double Result() const;

  private:
    double result_;
};