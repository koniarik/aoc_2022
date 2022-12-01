#include <emlabcpp/algorithm.h>

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <tuple>

namespace em = emlabcpp;

uint32_t read_stash(std::ifstream& is, std::string& input) {
  uint32_t i = 0;
  while (std::getline(is, input)) {
    if (input.empty()) {
      return i;
    }
    i += std::stol(input);
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Give 1 argument - input file" << std::endl;
    return 1;
  }

  std::ifstream ifile{argv[1]};
  std::string input;

  std::array<uint32_t, 4> top4{
    read_stash(ifile, input),
    read_stash(ifile, input),
    read_stash(ifile, input),
    read_stash(ifile, input)
  };

  std::sort(top4.begin(), top4.end());

  while (ifile) {
    top4[0] = read_stash(ifile, input);
    std::sort(top4.begin(), top4.end());
  }

  em::view top3{top4.begin() + 1, top4.end()};
  std::cout << em::sum(top3) << std::endl;
}
