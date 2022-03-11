#include "tictactoe.h"
#include <iostream>

using namespace std;

int main()
{
    string name1, name2;
    string s1, s2;

    cout << "Joaca X si O!\n\n";

    cout << "Alege optiunea de joc (Single Player/Two Players): \n";
    cout << "Tasta 1 -> Single Player (Joc contra calculatoruli. Atentie! Dificultate mare!)\n";
    cout << "Tasta 2 -> Two Players (Joaca impreuna cu un prieten.)\n\n";

    int nr_players=0;

    while(nr_players < 1 || nr_players > 2){
        cout << "Introdu numarul de jucatori: ";
        cin >> nr_players;
        cin.ignore();
    }


    switch(nr_players){
        //play with ai
        case 1:{
            cout << "Ai ales modul de joc Single Player (You vs AI).\n\n";

            cout << "Adauga numele jucatorului... ";
            getline(cin, name1);


            Game tictactoe(name1, "X", "calculatorul", "O", 3, 3, 3);
            tictactoe.play_with_computer();

            break;
            exit;
            }
        //play with friend
        case 2:{
            cout << "Ai ales modul de joc Two Players.\n\n";

            cout << "Adauga numele primului jucator... ";
            getline(cin, name1);
            cout << "Adauga simbolul de joc al primului jucator(X sau 0)... "<< endl;
            cin >> s1;
            cout << "Adauga numele celui de-al doilea jucator... ";
            cin.ignore();
            getline(cin, name2);
            cout << "Adauga simbolul de joc al celui de-al doilea jucator(X sau 0)... "<< endl;
            cin >> s2;

            cout << "Alege optiunea de board de joc (Normal/Custom): \n";
            cout << "-> Normal (3x3 cu 3 simboluri in linie pentru a castiga)\n";
            cout << "-> Custom (tu alegi numarul de linii si de coloane (>=3, <=10) si numarul se simboluri in linie care genereaza castigul (>=3, <=min(linii, coloane))\n";

            string mod_joc;
            cin >> mod_joc;

            int x;
            if(mod_joc == "Normal")
            x=0;
            if(mod_joc == "Custom")
            x=1;


            switch(x){
                case 0:{
                    Game tictactoe(name1, s1, name2, s2, 3, 3, 3);
                    tictactoe.play_two_players();

                    break;
                    exit;
                }

                case 1:{
                    int lines, columns, nr_s;
                    cout << "Introduceti numarul de linii... ";
                    cin >> lines;
                    cout << "Introduceti numarul de coloane... ";
                    cin >> columns;
                    cout << "Introduceti numarul de simboluri... ";
                    cin >> nr_s;
                    Game tictactoe(name1, s1, name2, s2, lines, columns, nr_s);
                    tictactoe.play_two_players();

                    break;
                    exit;
                }
            }

            break;
        }
    }

    return 0;
}
