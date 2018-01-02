#include <iostream>
#include <string>
#include <vector>
#include <tuple>

/** The Challenge
Given a string S and a set of words D, find the longest word in D that is a subsequence of S.

Word W is a subsequence of S if some number of characters, possibly zero, can be deleted from S to form W, without reordering the remaining characters.

Note: D can appear in any format (list, hash table, prefix tree, etc.

For example, given the input of S = "abppplee" and D = {"able", "ale", "apple", "bale", "kangaroo"} the correct output would be "apple"

- The words "able" and "ale" are both subsequences of S, but they are shorter than "apple".
- The word "bale" is not a subsequence of S because even though S has all the right letters, they are not in the right order.
- The word "kangaroo" is the longest word in D, but it isn't a subsequence of S.    
 */
int main() {
    std::string S = "abppplee";
    std::vector<std::string> D = {"able", "ale", "apple", "bale", "kangaroo"};

    std::tuple<int, std::string> result = {0, ""};
    for (auto &&word : D) {
        std::cout << "word is " << word << std::endl;
        int count = 0;
        int pos = 0;
        for (auto &&x : word) {
            auto ret = S.find(x, pos);
            std::cout << "  ret: " << ret << " x " << x << std::endl;
            if (ret == std::string::npos)
                break;
            pos = ret;
            count++;
        }
        printf("word: %s is %d\n", word.c_str(), count);

        if (std::get<0>(result) < count) {
            std::get<0>(result) = count;
            std::get<1>(result) = word;
        }

    }

    std::cout << "count: " << std::get<0>(result) << " word: " << std::get<1>(result) << std::endl;

    return 0;
}
