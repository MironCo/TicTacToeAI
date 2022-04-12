#include <iostream> 
#include <vector>

struct BoardPosition
{
    char board[3][3];
    signed char value;
};

class Board
{
public:
    BoardPosition board;
public:
    Board() {
        
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
    std::vector<Node*> children;

    unsigned char line;

    Node(unsigned char _line, BoardPosition &_data) {
        line = _line;
        data = _data;
    }
};

class AI
{
private:
    const signed char LOSE = -10;
    const signed char WIN = 10;
public:
    int numNodes = 0;
    std::vector<Node*> nodes;
public:
    AI() {
        
    }

    void ResetBoard(BoardPosition &board){
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                board.board[x][y] = (char)((x*3) + y + '1');
            }
        }
    } 
    
    bool CheckForWin(BoardPosition &board, char turn) {
        bool won = false;
        
        //check horizontal
        if (board.board[0][0] == turn && board.board[1][0] == turn && board.board[2][0] == turn) won = true;
        else if (board.board[0][1] == turn && board.board[1][1] == turn && board.board[2][1] == turn) won = true;
        else if (board.board[0][2] == turn && board.board[1][2] == turn && board.board[2][2] == turn) won = true;
        
        //check vertical
        else if (board.board[0][0] == turn && board.board[1][0] == turn && board.board[2][0] == turn) won = true;
        else if (board.board[0][1] == turn && board.board[1][1] == turn && board.board[2][1] == turn) won = true;
        else if (board.board[0][2] == turn && board.board[1][2] == turn && board.board[2][2] == turn) won = true;

        //diagonally
        else if (board.board[0][0] == turn && board.board[1][1] == turn && board.board[2][2] == turn) won = true;
        else if (board.board[0][2] == turn && board.board[1][1] == turn && board.board[2][0] == turn) won = true;

        //if (won) std::cout << "Won Position" << std::endl;
        return won;
    }

    void Evaluate(BoardPosition &board, int line) {
        char turn;
        if (line % 2 == 1) turn = 'X';
        else turn ='O';

       if (CheckForWin(board, turn)){
           if (turn == 'O') board.value = WIN;
           else if (turn == 'X') board.value = LOSE;
       }
    }

    void Generate() {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                BoardPosition newPos;
                ResetBoard(newPos);
                newPos.board[x][y] = 'X';

                unsigned char line = 1;
                Evaluate(newPos, line);
                Node* node = new Node(line, newPos);
                nodes.push_back(node);
                numNodes ++;
            }
        }
        for (Node* node : nodes) GenerateNodes(node);
    }

     void GenerateNodes(Node* currentNode) {
        
        char turn;
        if ((currentNode->line+1) % 2 == 1) turn = 'X';
        else turn ='O';

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                Node* newNode = new Node(currentNode->line+1, currentNode->data);
                
                if (newNode->data.board[x][y] != 'X' && newNode->data.board[x][y] != 'O') {
                    newNode->data.board[x][y] = turn;
                    Evaluate(newNode->data, currentNode->line+1);
                    currentNode->children.push_back(newNode);
                    numNodes ++;
                } else delete(newNode);
            }
        }
        
        
        if (currentNode->line+1 < 9) {
            for (Node* node : currentNode->children) {
                if (node->data.value == LOSE || node->data.value == WIN) return;
                else GenerateNodes(node);
            }
        }
    }

    void DisplayTree(Node* currentNode) {
        if (currentNode->data.value == WIN || currentNode->data.value == LOSE){
           DisplayBoard(*currentNode);  
        }
        for (Node* node : currentNode->children) DisplayTree(node);
    }

    static inline void DisplayBoard(Node &board) {
        std::cout << "\nLine: " << board.line << std::endl;
        std::cout << "-----------\n";   
        for (int x = 0; x < 3; x++) {
            
            for (int y = 0; y < 3; y++) {
                std::cout << " " << board.data.board[x][y] << " ";
                if (y != 2) std::cout << "|";
            }
            std::cout << "\n-----------\n";
        }
    }
};

int main()
{
    Board board;

    AI ai;
    ai.Generate();
    //ai.DisplayTree(ai.nodes[0]);
    std::cout << "Number Nodes: " << ai.numNodes << std::endl;

    while(true);
    
    return 0;
}