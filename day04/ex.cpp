#include <iostream>
#include <string>
#include <string_view>

std::string ask_name(int person) {
  std::cout << "Enter the name of person #" << person << ": ";
  std::string name{};
  std::getline(std::cin >> std::ws, name);
  return name;
}

int ask_age(std::string_view name) {
  std::cout << "Enter the age of " << name << ": ";
  int age{};
  std::cin >> age;
  return age;
}

void compare_ages(std::string_view name1, int age1, std::string_view name2,
                  int age2) {
  if (age1 > age2) {
    std::cout << name1 << " (age " << age1 << ") is older than " << name2
              << " (age " << age2 << "). \n";
  }

  else {
    std::cout << name2 << " (age " << age2 << ") is older than " << name1
              << " (age " << age1 << "). \n";
  }
}

int main() {
  const std::string name1{ask_name(1)};
  const int age1{ask_age(name1)};

  const std::string name2{ask_name(2)};
  const int age2 = {ask_age(name2)};

  compare_ages(name1, age1, name2, age2);

  return 0;
}
