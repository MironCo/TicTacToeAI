#include <iostream> 
#include <vector>
#include <cstdint>

struct BoardPosition
{
    char board[3][3];
    signed char value;
};

class Board
{
public:
    BoardPosition board;
    bool turn;
    bool gameWon = false;
public:
    Board() = default;
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
    void Reset() {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                board.board[x][y] = (char)((x*3) + y + '1');
            }
        }
    }
    bool ValidateMove(int input) {
        char checkedPos = board.board[(input-1)/3][(input-1)%3];

        if (input < 1 || input > 9) return false;
        if (checkedPos == 'X' || checkedPos == 'O') return false;
        return true;
    }
    void SetBox(int index, char turn) {
        board.board[(index-1)/3][(index-1)%3] = turn;
    }
    void GetInput() {
        if (turn == 0) {
            int input;
            
            do {
                std::cout << "Player One - Chooses a box from 1 - 9: ";
                std::cin >> input;
            } while(!ValidateMove(input));

            SetBox(input, 'X');
        }
        
        turn != turn;
    }
    void PlayAgain() {
    
    }
};

struct Node
{
    BoardPosition data;
    std::vector<Node*> children;

    uint8_t line;

    Node(short _line, BoardPosition &_data) {
        line = _line;
        data = _data;
    }
};

class AI
{
private:
    static const signed char LOSE = -10;
    static const signed char WIN = 10;
    static const signed char TIE = 0;
public:
    int numNodes = 0;
    std::vector<Node*> nodes;
public:
    AI() {
        
    }
    void ResetBoard(BoardPosition &board) {
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
        else if (board.board[0][0] == turn && board.board[0][1] == turn && board.board[0][2] == turn) won = true;
        else if (board.board[1][0] == turn && board.board[1][1] == turn && board.board[1][2] == turn) won = true;
        else if (board.board[2][0] == turn && board.board[2][1] == turn && board.board[2][2] == turn) won = true;

        //diagonally
        else if (board.board[0][0] == turn && board.board[1][1] == turn && board.board[2][2] == turn) won = true;
        else if (board.board[0][2] == turn && board.board[1][1] == turn && board.board[2][0] == turn) won = true;

        return won;
    }

    void Evaluate(BoardPosition &board, int line) {
        char turn;
        if (line % 2 == 1) turn = 'X';
        else turn ='O';

        if (CheckForWin(board, turn)){
            if (turn == 'O') board.value = WIN;
            else if (turn == 'X') board.value = LOSE;
        } else {
            if (line >= 9) board.value = TIE;
            
        }
    }

    bool CompareBoard(BoardPosition &pos1, BoardPosition &pos2) {
        for (int x = 3; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (pos1.board[x][y] == pos2.board[x][y]) continue;
                else return false; 
            }
        }
        return true;
    }

    Node* FindNode(Node* node, BoardPosition &searchedPos) {
        if (CompareBoard(node->data, searchedPos)) return node; 
        else for (Node* child : node->children) FindNode(child, searchedPos);
        return nullptr;
    }

    Node* SearchNodes(BoardPosition &searchedPos) {
        Node* foundNode;
        for (Node* node : nodes) foundNode = FindNode(node, searchedPos);
        return foundNode;
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
        if (currentNode->line == 5 && (currentNode->data.value == WIN || currentNode->data.value == LOSE)) DisplayBoard(currentNode);  
        for (Node* node : currentNode->children) DisplayTree(node);
    }

    static inline void DisplayBoard(Node* board) {
        std::cout << "\nLine: " << (short)board->line << std::endl;
        if(board->data.value == AI::WIN) std::cout << "Won Position" << std::endl;
        else if(board->data.value == AI::LOSE) std::cout << "LOSE Position" << std::endl;
        std::cout << "-----------\n";   
        for (int x = 0; x < 3; x++) {
            
            for (int y = 0; y < 3; y++) {
                std::cout << " " << board->data.board[x][y] << " ";
                if (y != 2) std::cout << "|";
            }
            std::cout << "\n-----------\n";
        }
    }
};

int main()
{
    bool gameWon = false;

    Board board;

    AI ai;
    ai.Generate();

    board.Reset();
    int turn = 0;

    do {
        turn ++;
        board.Display();
        board.GetInput();

        Node* currentNode = ai.SearchNodes(board.board);
        ai.DisplayBoard(currentNode);

    } while (!gameWon && turn < 9); 

    board.Display();

    return 0;
}