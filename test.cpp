#include <iostream>
#include <string>

bool check_double(long long num) {
  if (num%2!=0) return 0;
  int num_length{static_cast<int>(std::to_string(num).length())};
  if (num_length == 1) return false;

  long long a{};
  long long b{};

  int index{};
  while (num>0) {
    if (index<num_length/2) {
      a+=num%10;
      a*=10;
      num/=10;
    } else  {
      b+=num%10;
      b*=10;
      num/=10;
    }
  }

  return (a==b); 
}

bool check_repeating(const long long num) {
  long long num_copy{num};
  int num_length{static_cast<int>(std::to_string(num).length())};

  for (int i{1}; i<=num_length/2; ++i) {
    if (num_length%i!=0) continue;

    int target{};
    long long n{num};
    
    for (int j{0}; j<i; ++j) {
      target*=10;
      target+=n%10;
      n/=10;
    }

    int test{};
    int len{};
    bool repeating{};
    while (n>0) {
      test*=10;
      test+=n%10;
      n/=10;
      ++len;
      if (len==i) {
        if (test==target && test!=0) {
          repeating = true;          
        } else {
          repeating = false;
          break;
        }
        test=0;
        len=0;
      }
    }
    if (repeating || test == target && test!=0) {
      std::cout << test;
      return true;
    }
  }

  return false;
}

int main() {
    std::cout << std::boolalpha;
    long long num{};
    std::cin >> num;
    std::cout << check_double(num) << "\n";
    std::cout << check_repeating(num) << "\n";

    return 0;
}
