#include <set>
#include <fstream>
#include <string>

auto safeToFile(const std::set<int> &bestScores, std::string fileName) -> void {
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    for (auto score: bestScores) {
        file << score << " ";
    }
}

auto readFromFile(std::set<int> &bestScores, std::string fileName) -> void {
    auto file = std::fstream(fileName);
    for (auto score = std::string(); file >> score;) {
        bestScores.insert(std::stoi(score));
    }
}