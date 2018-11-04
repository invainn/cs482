#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <unordered_map>


class Utils {

    public:
        typedef std::unordered_map<std::string, uint16_t> word_freq_map;
        typedef std::vector<std::pair<std::string, std::string> > csv_pairs;

        static void parseCsv(csv_pairs&, const std::string);
        static void parseCsv(std::vector<std::string>&, const std::string);
        static void parseFreqMap(word_freq_map&, double&, const std::string);
        static void fillFreqMap(word_freq_map&, const std::vector<std::string>);
        static void outputMap(const word_freq_map, const std::string);
        static void formatMessage(std::string&);

        static std::vector<std::string> split(const std::string);

};

#endif
