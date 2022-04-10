#include <iostream> 

struct BoardPosition
{
    char board[3][3];
};

class Board
{
public:
    BoardPosition board;
public:
    Board() = default;
    
    void Reset()
    {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                board.board[x][y] = (char)((x*3) + y + '1');
            }
        }
    }   

    void Display() {    
        std::cout << "\n-----------\n";
        for (int x = 0; x < 3; x++) {
            
            for (int y = 0; y < 3; y++) {
                std::cout << " " << board.board[x][y] << " ";
                if (y != 2) std::cout << "|";
            }
            std::cout << "\n-----------\n";
        }
    }
};

struct Node
{
    BoardPosition data;
    BoardPosition* children;

    int line;

    Node() = default;

    Node(int _line, BoardPosition &_value) {
        line = _line;
        data = _value;
        children = (BoardPosition*)malloc((9 - line) * sizeof(BoardPosition)); 
    }
    void GenerateNode() {
        
    }
};

class AI
{
public:
    Node rootNodes[9];
public:
    AI() {
        
    }
    void Generate() {
        
    }
    static inline void DisplayBoard(BoardPosition &board)
    {
        std::cout << "\n-----------\n";
        for (int x = 0; x < 3; x++) {
            
            for (int y = 0; y < 3; y++) {
                std::cout << " " << board.board[x][y] << " ";
                if (y != 2) std::cout << "|";
            }
            std::cout << "\n-----------\n";
        }
    }
};

int main()
{
    Board board;
    board.Reset();

    return 0;
}