#pragma once

#include <string>

namespace high_scores {
    int print();
    int save(std::string user_name, int attempts_count);
}
