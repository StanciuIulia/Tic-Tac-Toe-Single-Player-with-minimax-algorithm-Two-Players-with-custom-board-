#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED

#include <string>
using namespace std;

class Player;
class Game;

class Player{
private:
    string name;
    string symbol;
public:
    Player(string, string);
    ~Player();

    string get_name();
    string get_symbol();

    void play(Game&, int);
};


class Game{
private:
    Player p1;
    Player p2;
    int nr_lines;
    int nr_columns;
    int min_symbols_win;
    int avaliable_moves;
    string board[10][10];
    string outcome;

public:
    Game(string, string, string, string, int, int, int);
    ~Game();
    void show_board();

    bool is_tie();
    bool check_win_ai(Player);
    bool check_win(Player, int);
    void show_outcome();

    int minimax();
    int max_search(int);
    int min_search(int);
    void play_with_computer();

    void play_two_players();
friend class Player;
};

#endif // TICTACTOE_H_INCLUDED
