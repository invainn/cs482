#include <ostream>
#include <fstream>
#include <iostream>
#include <string.h>

#include "utils.h"

int main(int argc, char* argv[]) {

    std::string inputSpamName{};
    std::string inputHamName{};
    std::string inputDatasetName{};
    std::string outputClassificationName{};

    Utils::word_freq_map ham{};
    Utils::word_freq_map spam{};

    std::ofstream output;

    double hamWordCount{};
    double spamWordCount{};

    // Setup filenames through flags
    for(auto i = 0; i < argc; ++i) {
        if(strcmp(argv[i], "-i") == 0) {
            inputDatasetName= std::string{argv[i+1]};
        } else if(strcmp(argv[i], "-is") == 0) {
            inputSpamName= std::string{argv[i+1]};
        } else if(strcmp(argv[i], "-ih") == 0) {
            inputHamName= std::string{argv[i+1]};
        } else if(strcmp(argv[i], "-o") == 0) {
            outputClassificationName = std::string{argv[i+1]};
        }
    }

    Utils::parseFreqMap(spam, spamWordCount, inputSpamName);
    Utils::parseFreqMap(ham, hamWordCount, inputHamName);

    // Check if the file names are empty
    if(!inputDatasetName.empty()) {
        std::vector<std::string> inputMessages{};

        Utils::parseCsv(inputMessages, inputDatasetName);

        // Open classification file
        std::ofstream out{outputClassificationName, std::ios::trunc};

        double totalWords = hamWordCount + spamWordCount;

        for(const auto message : inputMessages) {

            std::vector<std::string> tokens{Utils::split(message)};

            double spamProb = spamWordCount / totalWords;
            double hamProb = hamWordCount / totalWords;

            double msgSpamProb{1.0};
            double msgHamProb{1.0};

            double spamOcc{};
            double hamOcc{};

            // Find out probability of each word and then multiply together for msg
            for(const auto word : tokens) {
                if(spam.find(word) != spam.end()) {
                    spamOcc = spam[word];
                } else {
                    spamOcc = 0.0001;
                }

                if(ham.find(word) != ham.end()) {
                    hamOcc = ham[word];
                } else {
                    hamOcc = 0.0001;
                }

                double totalOcc{spamOcc + hamOcc};
                double wordProb{totalOcc / totalWords};

                if(wordProb < 0.0000001) {
                    wordProb = 0.0001;
                }

                double wordSpamProb{spamOcc / spamWordCount};
                double wordHamProb{hamOcc / hamWordCount};

                msgSpamProb *= (spamProb * wordSpamProb);
                msgHamProb *= (hamProb * wordHamProb);
            }

            if(msgHamProb >= msgSpamProb) {
                out << "ham" << std::endl;
            } else {
                out << "spam" << std::endl;
            }
        }

        out.close();

    } else {
        std::cerr << "input dataset filename not specified" << std::endl;
    }
    
    return 0;
}
