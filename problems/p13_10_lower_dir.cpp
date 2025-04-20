#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <string>

void perrAndDie(std::string_view err) {
    std::cout << err << std::endl;
    std::terminate();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        perrAndDie("Invalid args");
    }

    std::filesystem::path dir;

    try {
        dir = argv[1];
    } catch (std::exception &) {
        perrAndDie("Invalid args");
    }

    if (!std::filesystem::is_directory(dir)) {
        perrAndDie("Not a directory");
    }

    for (auto &&entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_directory()) {
            continue;
        }

        auto new_entry = entry;

        auto f = entry.path().filename().string();
        std::transform(f.begin(), f.end(), f.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        new_entry.replace_filename(f);

        if (entry != new_entry) {
            std::cout << entry.path() << " -> " << new_entry.path()
                      << std::endl;
            std::filesystem::rename(entry, new_entry);
        }
    }

    return 0;
}