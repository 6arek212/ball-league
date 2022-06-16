#include <iostream>
#include <string>
#include <vector>
#include "Team.hpp"
using namespace ball;
using namespace std;

int main(int argc, char const *argv[])
{
    
    Leauge g;

    Schedule s(g);

    s.printRounds();
    s.longestWinStreak();
    return 0;
}
