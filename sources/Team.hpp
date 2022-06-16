#include <string>
#include <map>
#include <iostream>
#include <vector>
namespace ball
{
    const int MAX_TEAM_NUM = 20;

    class Team
    {
    private:
        std::string name;
        double skill;
        int index;

    public:
        Team()
        {
        }
        Team(const std::string &name, const double &skill, const int &index)
        {
            this->name = name;
            this->skill = skill;
            this->index = index;
        };
        std::string getName()
        {
            return this->name;
        };
        int getSkill()
        {
            return this->skill;
        };

        int getIndex()
        {
            return this->index;
        }
    };

    class Game
    {
    private:
        Team *home;
        Team *away;
        int h_score;
        int a_score;

    public:
        Game(Team &home, Team &away)
        {
            this->home = &home;
            this->away = &away;
            this->h_score = -1;
            this->a_score = -1;
        }

        void play()
        {
            int h = ((rand() % 50) + 55);
            int a = ((rand() % 50) + 50);

            h += home->getSkill() * 10;
            a += away->getSkill() * 10;

            this->h_score = h;
            this->a_score = a;
        }

        int getWinnerIndex()
        {
            return h_score > a_score ? h_score : a_score;
        }

        int getLoserIndex()
        {
            return h_score < a_score ? h_score : a_score;
        }

        friend std::ostream &operator<<(std::ostream &out, const Game &game)
        {
            out << game.home->getName() << " VS " << game.away->getName() << std::endl;
            return out;
        }
    };

    class Leauge
    {
    private:
        std::map<std::string, Team> teams;

    public:
        Leauge()
        {
            double r;
            std::string str;
            for (size_t i = 0; i < MAX_TEAM_NUM; i++)
            {
                str = "A";
                str += std::to_string(i + 1);
                r = ((double)rand() / (RAND_MAX)) + 1;
                this->teams[str] = Team(str, r, i);
            }
        }

        Leauge(std::map<std::string, Team> teams)
        {
            if (teams.size() > MAX_TEAM_NUM)
            {
                throw std::invalid_argument("Max team number is ");
            }
            this->teams = teams;
        }

        std::vector<Team *> getTeams()
        {

            std::vector<Team *> teams;
            std::map<std::string, Team>::iterator it;
            for (it = this->teams.begin(); it != this->teams.end(); it++)
            {
                teams.push_back(&it->second);
            }
            return teams;
        }
    };

    ////////////////////////////////

    class Schedule
    {

    private:
        std::vector<Game> games;
        Leauge *leauge;

        void rotateVector(std::vector<Team *> &teams)
        {
            if (teams.size() < 2)
            {
                return;
            }

            Team *temp = teams[teams.size() - 1];
            for (size_t i = teams.size() - 1; i >= 2; i--)
            {
                teams[i] = teams[i - 1];
            }
            teams[1] = temp;
        }

        void makeGames(Leauge &leauge, bool reverse = false)
        {

            std::vector<Team *> teams = leauge.getTeams();

            for (size_t j = 0; j < teams.size() - 1; j++)
            {
                for (size_t i = 0; i < teams.size() / 2; i++)
                {
                    if (reverse)
                    {
                        this->games.push_back(Game(*teams[i + teams.size() / 2], *teams[i]));
                    }
                    else
                    {
                        this->games.push_back(Game(*teams[i], *teams[i + teams.size() / 2]));
                    }
                }
                rotateVector(teams);
            }
        }

    public:
        Schedule(Leauge &leauge)
        {
            this->leauge = &leauge;
            makeGames(leauge);
            makeGames(leauge, true);
        }

        void printRounds()
        {
            std::cout << "Number of games " << this->games.size() << std::endl;
            int round = 1;
            for (size_t i = 0; i < this->games.size(); i++)
            {
                if (i % (MAX_TEAM_NUM / 2) == 0)
                {
                    std::cout << "Round " << round << std::endl;
                    round++;
                }
                std::cout << this->games[i] << std::endl;
            }
        }

        void playSeason()
        {
            for (size_t i = 0; i < this->games.size(); i++)
            {
                this->games[i].play();
            }
        }

        void stats()
        {
        }

        int longestWinStreak()
        {
            int *arr = new int[this->leauge->getTeams().size()];
            for (size_t i = 0; i < this->games.size(); i++)
            {
                arr[i] = 0;
            }
            int round = 1;

            for (size_t i = 0; i < this->games.size(); i++)
            {
                if (arr[i] >= 0)
                {
                    arr[this->games[i].getWinnerIndex()]++;
                    arr[this->games[i].getLoserIndex()] = -1;
                }

                if (i % (MAX_TEAM_NUM / 2) == 0)
                {
                    round++;
                }
            }

            int max = arr[0];
            for (size_t i = 0; i < this->leauge->getTeams().size(); i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                }
            }

            std::cout << "Longest Win Streak " << max << std::endl;

            delete[] arr;
            return max;
        }
    };

};
