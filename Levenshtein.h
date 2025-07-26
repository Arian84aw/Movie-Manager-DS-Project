#pragma once
/// Levenshtein :

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Levenshtein {
public:
    int minDistance(string w1, string w2) {
        vector<int> prev(w2.length() + 1, 0);
        vector<int> curr(w2.length() + 1, 0);

        for (int j = 0; j <= w2.length(); j++)
            prev[j] = j;

        for (int i = 1; i <= w1.length(); i++) {
            curr[0] = i;

            for (int j = 1; j <= w2.length(); j++) {
                if (w1[i - 1] == w2[j - 1]) {
                    curr[j] = prev[j - 1];
                }
                else {
                    int _replace = 1 + prev[j - 1];
                    int _insert = 1 + curr[j - 1];
                    int _delete = 1 + prev[j];

                    curr[j] = min(_insert, min(_delete, _replace));
                }
            }
            prev = curr;
        }
        return prev[w2.length()];
    }
};