#include "HexBoard.hpp"

using namespace std;

int main()
{
    //test 1, red wins
    int n = 5;
    HexBoard boardA = HexBoard(n);
    boardA.markCellAt(0,0, HexBoard::Color::Red);
    boardA.markCellAt(0,0, HexBoard::Color::Blue);
    boardA.markCellAt(1,0, HexBoard::Color::Red);
    boardA.markCellAt(0,2, HexBoard::Color::Blue);
    boardA.markCellAt(2,0, HexBoard::Color::Red);
    boardA.markCellAt(1,4, HexBoard::Color::Blue);
    boardA.markCellAt(3,0, HexBoard::Color::Red);
    boardA.markCellAt(2,3, HexBoard::Color::Blue);
    boardA.markCellAt(4,0, HexBoard::Color::Red);
    cout << "Board A:";
    boardA.printBoard();

    //test 2, blue wins
    n = 7;
    HexBoard boardB = HexBoard(n);
    boardB.markCellAt(0,1, HexBoard::Color::Red);
    boardB.markCellAt(2,0, HexBoard::Color::Blue);
    boardB.markCellAt(1,0, HexBoard::Color::Red);
    boardB.markCellAt(2,1, HexBoard::Color::Blue);
    boardB.markCellAt(2,0, HexBoard::Color::Red);
    boardB.markCellAt(2,2, HexBoard::Color::Blue);
    boardB.markCellAt(2,1, HexBoard::Color::Red);
    boardB.markCellAt(2,3, HexBoard::Color::Blue);
    boardB.markCellAt(3,1, HexBoard::Color::Red);
    boardB.markCellAt(2,4, HexBoard::Color::Blue);
    boardB.markCellAt(4,1, HexBoard::Color::Red);
    boardB.markCellAt(2,5, HexBoard::Color::Blue);
    boardB.markCellAt(5,0, HexBoard::Color::Red);
    boardB.markCellAt(2,6, HexBoard::Color::Blue);
    boardB.markCellAt(6,0, HexBoard::Color::Red);
    boardB.markCellAt(2,6, HexBoard::Color::Blue);
    cout << "Board B:";
    boardB.printBoard();

    //generated random game
    n = 11;
    HexBoard boardC = HexBoard(n);
    boardC.generateRandomGame();
    cout << "Board C:" << endl;
    boardC.printBoard();
}












