#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>

void perrAndDie(std::string_view err) {
    std::cout << err << std::endl;
    std::terminate();
}

std::string makeNthRow(int n) {
    std::stringstream s;

    int curr = 1;
    s << curr;

    for (int k = 1; k != n + 1; ++k) {
        curr = curr * (n + 1 - k) / k;
        s << " " << curr;
    }

    return s.str();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        perrAndDie("Invalid args");
    }

    int rows_num = 0;

    try {
        rows_num = std::stoi(argv[1]);
    } catch (std::exception &) {
        perrAndDie("Invalid args");
    }

    if (rows_num < 1) {
        perrAndDie("Invalid args");
    }

    auto last = makeNthRow(rows_num - 1);

    for (int n = 0; n != rows_num - 1; ++n) {
        auto curr = makeNthRow(n);
        std::string spaces((last.size() - curr.size()) / 2, ' ');

        std::cout << spaces << curr << std::endl;
    }

    std::cout << last << std::endl;

    return 0;
}
