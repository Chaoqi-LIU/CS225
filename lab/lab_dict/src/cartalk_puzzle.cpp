/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    std::ifstream wordsFile {word_list_fname};
    std::string word, word_without_1st_char, word_without_2nd_char;
    if (wordsFile.is_open()) {
        while (std::getline(wordsFile, word)) {
            if (word.length() < 2) continue;
            word_without_1st_char = word;
            word_without_2nd_char = word;
            word_without_1st_char.erase(word_without_1st_char.begin());
            word_without_2nd_char.erase(word_without_2nd_char.begin() + 1);
            if (d.homophones(word, word_without_1st_char) &&
                d.homophones(word, word_without_2nd_char) &&
                d.homophones(word_without_1st_char, word_without_2nd_char)) {
                ret.push_back({word, word_without_1st_char, word_without_2nd_char});
            }
        }
    }
    return ret;
}
