#include "tictactoe.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

//
// functii Player
//

Player::Player(string name, string symbol):name(name), symbol(symbol){}
Player::~Player(){}

string Player::get_name(){
    return this->name;
}

string Player::get_symbol(){
    return this->symbol;
}

void Player::play(Game& g, int player_move){
    int line = (player_move-1)/g.nr_columns ;
    int column = (player_move-1)%g.nr_columns ;

    if(player_move<=0 || player_move > g.nr_lines*g.nr_columns){
        cout << "Casuta aleasa este invalida. Alege alta.\n";
        int new_move;
        cin >> new_move;
        this->play(g, new_move);
    }
    else
        if(g.board[line][column] == (g.p1).get_symbol() || g.board[line][column] == (g.p2).get_symbol()){
            cout << "Casuta este deja ocupata. Alege alta.\n";
            int new_move;
            cin >> new_move;
            this->play(g, new_move);
        }
        else {
            g.board[line][column] = this->symbol;
            g.avaliable_moves--;
        }
}



//
// functii Game
//

Game::Game(string name1="1", string s1="X", string name2="2", string s2="0", int l=3, int c=3, int symbols_to_win=3):
                p1(name1, s1), p2(name2, s2), nr_lines(l), nr_columns(c), min_symbols_win(symbols_to_win){

    for(int i=0; i<l; ++i)
        for(int j=0; j<c; ++j){
            board[i][j] = to_string(i*c+j+1);
        }

    avaliable_moves = l*c;
    outcome = "-";
}

Game::~Game(){}

void Game::show_board(){
    for(int j=0; j<nr_columns; ++j)
            cout << " _____";
    cout << " \n";

    for(int i=0; i<nr_lines; ++i){

        for(int j=0; j<nr_columns; ++j)
            cout << "|     ";
        cout << "|\n";
        for(int j=0; j<nr_columns; ++j){
            cout << "|  " << board[i][j];
            if((i*nr_columns+j+1)<10 || board[i][j]==p1.get_symbol() || board[i][j]==p2.get_symbol())
                cout << "  ";
            else if((i*nr_columns+j+1)<100)
                cout << " ";
        }
        cout << "|\n";
        for(int j=0; j<nr_columns; ++j)
            cout << "|_____";
        cout << "|\n";

    }
}

bool Game::is_tie(){
    return (avaliable_moves==0);
}

bool Game::check_win_ai(Player p){
    bool win;

    //check column win
    for(unsigned int j=0; j<nr_columns; ++j){
        win = true;

        for(unsigned int i=0; i<nr_lines; ++i)
            if(board[i][j] != p.get_symbol())
                win = false;

        if(win)
            return true;
    }


    //check line win

    for(unsigned int i=0; i<nr_lines; ++i){
        win = true;

        for(unsigned int j=0; j<nr_columns; ++j)
            if(board[i][j] != p.get_symbol())
                win = false;

        if(win)
            return true;
    }




    //check main diagonal win
    win = true;
    for(unsigned int i=0; i<nr_lines; ++i)
        if(board[i][i] != p.get_symbol())
            win = false;

    if(win)
        return true;



    //check secondary diagonal win
    win = true;
    for(unsigned int i=0; i<nr_lines; ++i)
        if(board[i][nr_columns-1-i] != p.get_symbol())
            win = false;
    if(win)
        return true;



    return false;
}

bool Game::check_win(Player p, int last_move){
    int line = (last_move-1)/this->nr_columns ;
    int column = (last_move-1)%this->nr_columns;

    //check column win
    int s_in_column = 0;
    for(int i=max(line-min_symbols_win+1, 0); i<min(line+min_symbols_win, nr_lines); ++i){
        if(board[i][column] == p.get_symbol()){
            s_in_column++;
        }
        else {
            s_in_column = 0;
        }

        if(s_in_column == min_symbols_win){
            outcome = p.get_symbol();
            return true;
        }
    }

    //check line win
    int s_in_line = 0;
    for(int j=max(column-min_symbols_win+1,0); j<min(column+min_symbols_win, nr_columns); ++j){
        if(board[line][j] == p.get_symbol()){
            s_in_line++;
        }
        else {
            s_in_line = 0;
        }

        if(s_in_line == min_symbols_win){
            outcome = p.get_symbol();
            return true;
        }
    }

    //check main diagonal win
    int s_main_diag = 0;
    for(int i=-min_symbols_win+1; i<min_symbols_win;++i){
        if(line+i>=0 && line+i<nr_lines && column+i>=0 && column+i<nr_columns)
            if(board[line+i][column+i] == p.get_symbol()){
                s_main_diag++;
            }
            else {
                s_main_diag = 0;
            }

            if(s_main_diag == min_symbols_win){
                outcome = p.get_symbol();
                return true;
            }
    }

    //check secondary diagonal win
    int s_sec_diag = 0;
    for(int i=-min_symbols_win+1; i<min_symbols_win; ++i){
        if(line+i>=0 && line+i<nr_lines && column-i>=0 && column-i<nr_columns)
            if(board[line+i][column-i] == p.get_symbol()){
                s_sec_diag++;
            }
            else {
                s_sec_diag = 0;
            }

            if(s_sec_diag == min_symbols_win){
                outcome = p.get_symbol();
                return true;
            }
    }

    return false;
}

void Game::show_outcome(){
    if(outcome==p1.get_symbol())
        cout << "Castigatorul este " << p1.get_name() << ", cu simbolul " << p1.get_symbol() << ".\n";

    if(outcome==p2.get_symbol())
        cout << "Castigatorul este " << p2.get_name() << ", cu simbolul " << p2.get_symbol() << ".\n";

    if(outcome=="-")
        cout << "Remiza.\n";
}


int Game::minimax(){

    int score = 99999;
    int best_move = 0;

    for (unsigned int i = 0; i < nr_lines; ++i){
        for (unsigned int j = 0; j < nr_columns; ++j){
            if( board[i][j] != p1.get_symbol() && board[i][j] != p2.get_symbol()){
                string aux = board[i][j];
                board[i][j] = p2.get_symbol();
                avaliable_moves--;

                int temp = this->max_search(1);

                    if (temp < score){

                        score = temp;
                        best_move = i*nr_columns+j+1;
                    }

                board[i][j] = aux;
                avaliable_moves++;
                }
            }
        }
    return best_move;
}


int Game::max_search(int level){
    if(check_win_ai(p1)){
        return 10;
    }
    else if(check_win_ai(p2)){
        return -10;
    }
    else if(is_tie()){
        return 0;
    }
    else {
    int score = -9999;

    for (unsigned int i = 0; i < nr_lines; i++){
        for (unsigned int j = 0; j < nr_columns; j++){
            if( board[i][j] != p1.get_symbol() && board[i][j] != p2.get_symbol()){
                string aux = board[i][j];
                board[i][j] = p1.get_symbol();
                avaliable_moves--;
                score = max(score, this->min_search(level+1)-level);

                board[i][j] = aux;
                avaliable_moves++;
            }
        }
    }
    return score;
    }
}

int Game::min_search(int level){
    if(check_win_ai(p1)){
        return 10;
    }
    else if(check_win_ai(p2)){
        return -10;
    }
    else if(is_tie()){
        return 0;
    }
    else {
    int score = 9999;

    for (unsigned int i = 0; i < nr_lines; i++){
        for (unsigned int j = 0; j < nr_columns; j++){
            if( board[i][j] != p1.get_symbol() && board[i][j] != p2.get_symbol()){
                string aux = board[i][j];
                board[i][j] = p2.get_symbol();
                avaliable_moves--;
                score = min(score, this->max_search(level+1)+level);

                board[i][j] = aux;
                avaliable_moves++;
            }
        }
    }
    return score;
    }
}

void Game::play_with_computer(){
    unsigned int turn = 0;
    bool exit = false;

    int player_move=1;

    do{
        this->show_board();
        if(turn==0){
            cout << "Este randul jucatorului " << p1.get_name() << ", cu simbolul " << p1.get_symbol() << ". Alege o casuta prin tastarea indicativului numeric.\n";
            cin >> player_move;
            p1.play(*this, player_move);

            if(this->check_win_ai(p1)){
                outcome = p1.get_symbol();
                exit = true;
            }
        }
        else{
            cout << "Este randul calculatorului, cu simbolul " << p2.get_symbol() << ".\n";

            int ai_move = this->minimax();
            p2.play(*this, ai_move);

            if(this->check_win_ai(p2)){
                outcome = p2.get_symbol();
                exit = true;
            }

        }

        if(is_tie()){
            exit = true;
        }

        turn ^=1;

    }while(!exit);

    this->show_board();
    this->show_outcome();
    return;
}



void Game::play_two_players(){
    int player_move=1;

    while(avaliable_moves > 0){
        this->show_board();
        cout << "Este randul jucatorului " << p1.get_name() << ", cu simbolul " << p1.get_symbol() << ". Alege o casuta prin tastarea indicativului numeric.\n";
        cin >> player_move;
        p1.play(*this, player_move);
        if(this->check_win(p1,player_move)==true || avaliable_moves == 0){
            this->show_board();
            this->show_outcome();
            exit;
            break;
        }
        else{
            this->show_board();
            cout << "Este randul jucatorului " << p2.get_name() << ", cu simbolul " << p2.get_symbol() << ". Alege o casuta prin tastarea indicativului numeric.\n";
            cin >> player_move;
            p2.play(*this, player_move);
            if(this->check_win(p2,player_move)==true){
                this->show_board();
                this->show_outcome();
                exit;
                break;
            }
        }
    }
}
