#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "utils.h"

void Utils::parseCsv(csv_pairs& result, const std::string fileName) {
    std::string line{};
    std::ifstream in{fileName};

    while(std::getline(in, line, '\n')) {
        const auto token = line.substr(0, line.find(",,,"));
        const auto type = token.substr(0, token.find(","));
        auto message = token.substr(token.find(",")+1, token.length());

        formatMessage(message);

        result.push_back(std::make_pair(type, message));
    }

    in.close();
}

void Utils::parseCsv(std::vector<std::string>& result, const std::string fileName) {
    std::string line{};
    std::ifstream in{fileName};

    while(std::getline(in, line, '\n')) {
        const auto token = line.substr(0, line.find(",,,"));
        auto message = token.substr(token.find(",")+1, token.length());
        formatMessage(message);

        result.push_back(message);
    }

    in.close();
}

void Utils::parseFreqMap(word_freq_map& map, double& wordCount, const std::string fileName) {
    if(!fileName.empty()) {
        std::string line{};
        std::ifstream in{fileName};

        while(std::getline(in, line, '\n')) {
            const auto word = line.substr(0, line.find(" "));
            const int freq = std::stoi(line.substr(line.find(" ")+1, line.length()));

            map.emplace(word, freq);

            wordCount++;
        }

        in.close();
    } else {
        std::cerr << "a file name was not specified!" << std::endl;
    }
}

void Utils::fillFreqMap(word_freq_map& freqMap, const std::vector<std::string> tokens) {
    for(const auto word : tokens) {
        if(freqMap.find(word) == freqMap.end()) {
            freqMap.emplace(std::make_pair(word, 1));
        } else {
            freqMap[word]++;
        }
    }
}

void Utils::outputMap(const word_freq_map freqMap, const std::string fileName) {
    std::ofstream out{fileName, std::ios::trunc};

    for(const auto pair : freqMap) {
        if(pair.second > 1) {
            out << pair.first << " " << pair.second << std::endl;
        }
    }

    out.close();
}

void Utils::formatMessage(std::string& src) {
    src.erase(std::remove_if(src.begin(), src.end(), ispunct), src.end());
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
}

std::vector<std::string> Utils::split(const std::string src) {
    std::vector<std::string> tokens{};
    std::istringstream ss{src};
    std::string token{};

    while(std::getline(ss, token, ' ')) {
        if(token.compare("") != 0) {
            tokens.push_back(token);
        }
    }
    return tokens;
}
