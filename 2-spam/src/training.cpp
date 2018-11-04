#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <string.h>

#include "utils.h"

int main(int argc, char* argv[]) {

    std::string outputSpamName{};
    std::string outputHamName{};
    std::string inputSpamName{};

    Utils::word_freq_map ham{};
    Utils::word_freq_map spam{};

    std::ofstream output;

    // Setup filenames through flags
    for(auto i = 0; i < argc; ++i) {
        if(strcmp(argv[i], "-i") == 0) {
            inputSpamName = std::string{argv[i+1]};
        } else if(strcmp(argv[i], "-os") == 0) {
            outputSpamName = std::string{argv[i+1]};
        } else if(strcmp(argv[i], "-oh") == 0) {
            outputHamName = std::string{argv[i+1]};
        }
    }

    // Check if the file names are empty
    if(!inputSpamName.empty()) {
        std::vector<std::pair<std::string, std::string> > csv_pairs{};

        Utils::parseCsv(csv_pairs, inputSpamName);

        for(const auto pair : csv_pairs) {
            // We'll break down the string into words
            std::vector<std::string> tokens{Utils::split(pair.second)};

            if(pair.first.compare("ham") == 0) {
                // Now, we'll iterate through the vector, add them to the map along with the count
                Utils::fillFreqMap(ham, tokens);
            } else {
                // Do the same for spam
                Utils::fillFreqMap(spam, tokens);
            }
        }

    } else {
        std::cerr << "input spam filename not specified" << std::endl;
    }

    // Output to respective files
    Utils::outputMap(ham, outputHamName);
    Utils::outputMap(spam, outputSpamName);

    return 0;
}

