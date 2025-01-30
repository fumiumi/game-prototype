#include  "SampleMath.h"

/// @brief gtestが正しく実行されるか試すための関数。
/// @param a 
/// @param b 
/// @return 
double SampleMath::Add(double a, double b) {
  double result = a + b;

  // メンバ変数に結果が保存されているかもテストするため
  result_ = result;

  return result;
}

double SampleMath::Result() const {
  return result_;
}