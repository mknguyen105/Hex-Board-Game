#ifndef HEXBOARD_HPP
#define HEXBOARD_HPP

#include <vector>
#include <cstdlib>
#include <list>
#include <map>
#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;

class HexBoard
{
public:
    enum Color
    {
        Red,
        Blue,
        Blank
    };
    struct CellObj
    {
        int cellNum;
        int x;
        int y;
        Color cellColor;
        list<int> adjCells;
    };
	//constructor
	HexBoard(int s = 11);
	//destructor
	~HexBoard();
	//returns cell number
	int getCellNum(int x, int y);
	//find adjacent vertices of vertex
	list<int> getAdjCells(int x, int y);
	//fill in board at passed coordinates with color
	void markCellAt(int x, int y, Color color);
	//check if cell is empty
	bool isValidCell(int x, int y);
	void switchPlayer();
	//return winner color
	string findWinner();
	//depth first traversal
	void visitAdjCell(int cellNum, map<int, bool>& visited, Color color);
	void generateRandomGame();
	void printBoard();

private:
	//(cellNum, CellObj)
	map<int,CellObj> board;
	//cellNum of red cells
	vector<int> redCells;
	//cellNum of blue cells
	vector<int> blueCells;
	int boardSize;
	//current player
	Color player;
};

HexBoard::HexBoard(int s)
{
	boardSize = s;
	//first player is red
	player = Red;
	//initialize board
	for(int x=0; x<boardSize; x++)
	{
		for(int y=0; y<boardSize; y++)
		{
			//labeled 0 to [(n^2)-1]
			int cellNum = getCellNum(x, y);

			//find adjacent cells
			list<int> adjCells = getAdjCells(x, y);

			CellObj newCell{cellNum, x, y, Blank, adjCells};
			board[cellNum] = newCell;
		}
	}
}

HexBoard::~HexBoard()
{

}

int HexBoard::getCellNum(int x, int y)
{
	return x * boardSize + y;
}

list<int> HexBoard::getAdjCells(int x, int y)
{
	list<int> adjCells;
	//northwest corner
	if(x==0 && y==0)
	{
		adjCells.push_back(x*boardSize+y+1);
		adjCells.push_back((x+1)*boardSize+y);
	}
	//north edge
	else if(x==0 && y>0 && y<boardSize-1)
	{
		adjCells.push_back(x*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y);
		adjCells.push_back(x*boardSize+y+1);
	}
	//northeast corner
	else if(x==0 && y==boardSize-1)
	{
		adjCells.push_back(x*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y);
	}
	//west edge
	else if(y==0 && x>0 && x<boardSize-1)
	{
		adjCells.push_back((x-1)*boardSize+y);
		adjCells.push_back((x-1)*boardSize+y+1);
		adjCells.push_back(x*boardSize+y+1);
		adjCells.push_back((x+1)*boardSize+y);
	}
	//east edge
	else if(y==boardSize-1 && x>0 && x<boardSize-1)
	{
		adjCells.push_back((x-1)*boardSize+y);
		adjCells.push_back(x*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y-1);
		adjCells.push_back((x+1)*boardSize+y);
	}
	//southwest corner
	else if(x==boardSize-1 && y==0)
	{
		adjCells.push_back((x-1)*boardSize+y);
		adjCells.push_back((x-1)*boardSize+y+1);
		adjCells.push_back(x*boardSize+y+1);
	}
	//south edge
	else if(x==boardSize-1 && y>0 && y<boardSize-1)
	{
		adjCells.push_back(x*boardSize+y-1);
		adjCells.push_back((x-1)*boardSize+y);
		adjCells.push_back((x-1)*boardSize+y+1);
		adjCells.push_back(x*boardSize+y+1);
	}
	//southeast corner
	else if(x==boardSize-1 && y==boardSize-1)
	{
		adjCells.push_back((x-1)*boardSize+y);
		adjCells.push_back(x*boardSize+y-1);
	}
	//middle
	else
	{
		adjCells.push_back((x-1)*boardSize+y+1);
		adjCells.push_back(x*boardSize+y+1);
		adjCells.push_back((x+1)*boardSize+y);
		adjCells.push_back((x+1)*boardSize+y-1);
		adjCells.push_back(x*boardSize+y-1);
		adjCells.push_back((x-1)*boardSize+y);
	}
	return adjCells;
}

void HexBoard::markCellAt(int x, int y, Color color)
{
	int cellNum = getCellNum(x, y);
	//if cell is empty, fill cell with color
	if(isValidCell(x, y))
	{
		board.at(cellNum).cellColor = color;
		if(color == Red)
		{
		    cout << "Red  played: (" << x << ", " << y << ")" << endl;
			redCells.push_back(cellNum);
		}
		else if(color == Blue)
		{
		    cout << "Blue played: (" << x << ", " << y << ")" << endl;
			blueCells.push_back(cellNum);
		}
	}
	else
		return;
}

bool HexBoard::isValidCell(int x, int y)
{
	//cell is empty
	if(board.at(getCellNum(x, y)).cellColor == Blank)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HexBoard::switchPlayer()
{
	if(player == Red)
	{
		player = Blue;
	}
	else if(player == Blue)
	{
		player = Red;
	}
}

string HexBoard::findWinner()
{
	//boolean map for whether each cell is visited
	//(cellNum, boolean)
	map<int, bool> visitedRed;
	int i, j, k;
	//mark cells as not visited
	for(i=0; i<redCells.size(); i++)
	{
		visitedRed.insert(pair<int, bool>(redCells[i], false));
	}
	//visit every red cell
	for(i=0; i<redCells.size(); i++)
	{
		//j = cell number of north side
		for(j=0; j<boardSize; j++)
		{
			//found red cell on north edge
			if(redCells[i] == j)
			{
				//visit adjacent cells
				visitAdjCell(redCells[i], visitedRed, Red);
			}
		}
		//check if cell from north reaches south
		//k = cell number of south side
		for(k=(boardSize-1)*boardSize; k<(boardSize*boardSize); k++)
		{
			//found red cell on south edge and cell is visited
			if(redCells[i] == k && visitedRed[k] == true)
			{
				//red wins
				return "Red wins!";
			}
		}
	}
	map<int, bool> visitedBlue;
	for(i=0; i<blueCells.size(); i++)
	{
		visitedBlue.insert(pair<int, bool>(blueCells[i], false));
	}
	//visit every blue cell
	for(i=0; i<blueCells.size(); i++)
	{
		//j = cell number of west side
		for(int j=0; j<(boardSize*boardSize); j=j+boardSize)
		{
			if(blueCells[i] == j)
			{
				//visit adjacent cells
				visitAdjCell(blueCells[i], visitedBlue, Blue);
			}
		}
		//check if cell from west reaches east
		//k = cell number of east size
		for(k=boardSize-1; k<(boardSize*boardSize); k=k+boardSize)
		{
			//found blue cell on east edge and cell is visited
			if(blueCells[i] == k && visitedBlue[k] == true)
			{
				//blue wins
				return "Blue wins!";
			}
		}
	}
	//no winner
	return "No winner yet!";
}

void HexBoard::visitAdjCell(int cellNum, map<int, bool>& visited, Color color)
{
	//mark cell as visited
	visited[cellNum] = true;
	//check adjacent vertices from vertex
	for(auto i=board.at(cellNum).adjCells.begin(); i!=board.at(cellNum).adjCells.end(); i++)
	{
		//recurse if adjacent vector is same color and is not visited
		if(visited[*i] == false && board.at(*i).cellColor == color)
		{
			visitAdjCell(*i, visited, color);
		}
	}
}

void HexBoard::generateRandomGame()
{
	srand(time(NULL));
	int x, y;
	//while no one has won
	while(findWinner() == "No winner yet!")
	{
		//generate random x and y from 0 to size until we find empty cell
		do{
			x = rand() % boardSize;
			y = rand() % boardSize;
		} while(!isValidCell(x, y));
		//red player's turn
		if(player == Red)
		{
			markCellAt(x, y, Red);
			switchPlayer();
		}
		//blue player's turn
		else
		{
			markCellAt(x, y, Blue);
			switchPlayer();
		}
	}
}

void HexBoard::printBoard()
{
	string tab = "";
	cout << "\n";
	for(int x=0; x<boardSize; x++)
	{
		tab += "  ";
		cout << tab << "\\ ";
		for(int y=0; y<boardSize; y++)
		{
			Color cellColor = board.at(getCellNum(x, y)).cellColor;
			if(cellColor == Red)
			{
				cout << "r \\ ";
			}
			else if(cellColor == Blue)
			{
				cout << "b \\ ";
			}
			else
			{
				cout << "  \\ ";
			}
		}
		cout << endl;
	}
	cout << findWinner() << endl;
}

#endif //HEXBOARD_HPP
