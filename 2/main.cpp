#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <assert.h>

using std::map;
using std::string;
using std::vector;

// 0 - Rock, 1 - Paper, 2 - Scissors
static const map<char, int> THEIR_HAND{{'A', 0}, {'B', 1}, {'C', 2}};

// Outcomes
static const map<char, int> OUTCOME{{'X', 0}, {'Y', 3}, {'Z', 6}};

// Game scores, rows - them, cols - us
static const int GAME_SCORE[3][3]{{3, 6, 0}, {0, 3, 6}, {6, 0, 3}};

// Hand scores
static const map<char, int> HAND_SCORE{{0, 1}, {1, 2}, {2, 3}};

int solve(std::istream &s)
{
    int score = 0;
    for (string line; std::getline(s, line);)
    {
        auto their_hand = THEIR_HAND.at(line[0]);
        auto outcome = OUTCOME.at(line[2]);

        auto response_scores = GAME_SCORE[their_hand];

        int our_hand = 0;
        for (; response_scores[our_hand] != outcome; ++our_hand)
        {
            if (our_hand > 2)
            {
                throw std::out_of_range("Cannot find respose score that matches outcome.");
            }
        }

        score += outcome;
        score += HAND_SCORE.at(our_hand);
    }
    std::cout << "Score: " << score << '\n';
    return score;
}

int main(int argc, char *argv[])
{
    string arg = "";
    if (argc == 2)
    {
        arg = argv[1];
    }

    if (arg == "test")
    {
        string s = "A Y\nC Z\nB X";
        std::istringstream ss{s};
        assert(solve(ss) == (1 + 3 + 1 + 6 + 1 + 0));
    }
    else
    {
        std::fstream f("2/input");
        if (!f.is_open())
        {
            std::cout << "Cannot open input file." << EOF;
            return 1;
        }
        solve(f);
        f.close();
    }

    return 0;
}
