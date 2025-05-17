// barkeep.hpp (versión con namespace barkeep)
#pragma once

#include <iostream>
#include <string>
#include <cmath>

namespace barkeep {

class ProgressBar {
public:
    ProgressBar(size_t total_steps, size_t bar_width = 50)
        : total_steps_(total_steps), bar_width_(bar_width), current_step_(0) {}

    void update(size_t step) {
        current_step_ = step;
        float progress = static_cast<float>(current_step_) / total_steps_;
        int pos = static_cast<int>(bar_width_ * progress);

        std::cout << "[";
        for (int i = 0; i < bar_width_; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << "%\r";
        std::cout.flush();
    }

    void done() {
        update(total_steps_);
        std::cout << std::endl;
    }

private:
    size_t total_steps_;
    size_t bar_width_;
    size_t current_step_;
};

} // namespace barkeep
