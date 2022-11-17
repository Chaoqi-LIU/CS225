/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    std::ifstream wordsFile {filename};
    std::string word, sorted_word;
    if (wordsFile.is_open()) {
        while (std::getline(wordsFile, word)) {
            sorted_word = word;
            std::sort(sorted_word.begin(), sorted_word.end());
            dict[sorted_word].push_back(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    std::string sorted_word;
    for (auto & word : words) {
        sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        dict[sorted_word].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    std::string sorted_word = word;
    std::sort(sorted_word.begin(), sorted_word.end());
    if (dict.find(sorted_word) == dict.end()) {
        return {};
    }   
    return dict.at(sorted_word);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    std::vector<std::vector<std::string>> res;
    for (auto & anagram_siblings : dict) {
        if (anagram_siblings.second.size() >= 2)
            res.push_back(anagram_siblings.second);
    }
    return res;
}
