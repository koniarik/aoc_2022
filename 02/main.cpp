#include <emlabcpp/algorithm.h>

#include <charconv>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <tuple>

namespace em = emlabcpp;

extern const char _binary_02_input_start;
extern const char _binary_02_input_end;

enum moves {
  rock = 0,
  paper = 1,
  scissors = 2,
};

int32_t play(moves a, moves b) {
  if (a == b) {
    return 0;
  }
  if (a == (b + 1) % 3) {
    return 1;
  }
  return -1;
}

int32_t reward(int32_t result) { return result * 3 + 3; }

std::string_view readline(std::string_view& sv) {
  std::size_t j = sv.find_first_of('\n');
  if (j == std::string_view::npos) {
    sv = std::string_view{};
    return sv;
  }
  std::string_view result = sv.substr(0, j);
  sv = sv.substr(j + 1);
  return result;
}

int main() {
  std::string_view input{&_binary_02_input_start,
                         static_cast<std::size_t>(&_binary_02_input_end -
                                                  &_binary_02_input_start)};

  std::size_t score = 0;
  while (true) {
    std::string_view sv = readline(input);
    if (sv.empty()) {
      break;
    }
    moves opponent = static_cast<moves>(sv[0] - 'A');
    int32_t desired_result = sv[2] - 'Y';
    moves me = static_cast<moves>((opponent + desired_result + 3) % 3);

    std::size_t round_score = me + 1 + reward(play(me, opponent));
    score += round_score;
  }
  std::cout << "score: " << score << std::endl;
}
