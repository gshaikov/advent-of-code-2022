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
static const map<char, int> OUR_HAND{{'X', 0}, {'Y', 1}, {'Z', 2}};

// Game scores, rows - them, cols - us
static const int SCORES[3][3]{{3, 6, 0}, {0, 3, 6}, {6, 0, 3}};

// Hand scores
static const map<char, int> HAND_SCORE{{0, 1}, {1, 2}, {2, 3}};

int compute_score(std::istream &s)
{
    int score = 0;
    for (string line; std::getline(s, line);)
    {
        auto their_hand = THEIR_HAND.at(line[0]);
        auto our_hand = OUR_HAND.at(line[2]);
        score += HAND_SCORE.at(our_hand);
        score += SCORES[their_hand][our_hand];
    }
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
        std::stringstream ss;
        ss.str(s);
        int score = compute_score(ss);
        assert(score == (2 + 6 + 3 + 3 + 1 + 0));
    }
    else
    {
        std::fstream f("2/input");
        if (!f.is_open())
        {
            std::cout << "Cannot open input file." << EOF;
            return 1;
        }
        int score = compute_score(f);
        std::cout << "Score: " << score << '\n';
        f.close();
    }

    return 0;
}
