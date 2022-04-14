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
    bool CheckForWin(short turnInt) {
        bool won = false;
        char turn;
        if ((turnInt) % 2 == 1) turn = 'X';
        else turn = 'O';

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
    static const signed char BLOCK = 5;
    static const signed char TIE = 0;
public:
    int numNodes = 0;
    std::vector<Node*> nodes;
    Node* position = nullptr;
public:
    AI() = default;
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
    bool CheckForBlock(BoardPosition &board) {
        //check horizontal
        for (int y = 0; y < 3; y++) {
            if (board.board[0][y] == 'X' && board.board[1][y] == 'X' && board.board[2][y] == 'O') return true;
            else if (board.board[0][y] == 'O' && board.board[1][y] == 'X' && board.board[2][y] == 'X') return true;
        }
        //check vertical
        for (int x = 0; x < 3; x++) {
            if (board.board[x][0] == 'X' && board.board[x][1] == 'X' && board.board[x][2] == 'O') return true;
            if (board.board[x][2] == 'X' && board.board[x][1] == 'X' && board.board[x][0] == 'O') return true;
        }
        
        //diagonally
        if (board.board[0][0] == 'X' && board.board[1][1] == 'X' && board.board[2][2] == 'O') return true;
        else if (board.board[2][0] == 'X' && board.board[1][1] == 'X' && board.board[0][2] == 'O') return true;
        else if (board.board[2][0] == 'O' && board.board[1][1] == 'X' && board.board[0][2] == 'X') return true;
        else if (board.board[2][0] == 'O' && board.board[1][1] == 'X' && board.board[0][2] == 'X') return true;
        return false;
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
            else if (CheckForBlock(board)) board.value = BLOCK;
            else board.value = 0;
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
        if (currentNode->line == 9) DisplayBoard(currentNode);  
        for (Node* node : currentNode->children) DisplayTree(node);
    }

    static inline void DisplayBoard(Node* board) {
        std::cout << "\nLine: " << (short)board->line << " Node " << board << std::endl;
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

    bool CompareBoard(BoardPosition &pos1, BoardPosition &pos2) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (pos1.board[x][y] != pos2.board[x][y]) {
                    return false;
                }
            }
        }
        //std::cout << "Found Right Node" << std::endl;
        return true;
    }

    Node* FindNode(Node* node, BoardPosition &searchedPos) {
        if (CompareBoard(node->data, searchedPos)) return node; 
        else for (Node* child : node->children) FindNode(child, searchedPos);
    }

    Node* SearchNodes(BoardPosition &searchedPos) {
        for (Node* node : nodes) {
            if (CompareBoard(node->data, searchedPos)) return node;
        }
        return nullptr;
    }

    Node* FindNodeInChildren(Node* node, BoardPosition &searchedPos) {
        for (Node* child : node->children) {
            if (CompareBoard(child->data, searchedPos)) return child;
        }
        return nullptr;
    }

    Node* FindBestMove(Node* currentNode) {
        Node* bestNode;
        int bestValue = -1;
        for (Node* node : currentNode->children) {
            if (node->data.value > bestValue) {
                bestNode =  node;
                bestValue = bestNode->data.value;
            }
        }
        return bestNode;
    }

    void Play(Board &board) {
        std::cout << "AI Move: " << std::endl;
        if (position == nullptr) position = SearchNodes(board.board);
        else position = FindNodeInChildren(position, board.board);
        Node* bestMove = FindBestMove(position);
        //set position to the best play
        board.board = bestMove->data;
        position = bestMove;
        std::cout << "Current Node " << position << " from line " << (short)position->line <<" with a value of " << (short)position->data.value << std::endl;
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

    //ai.DisplayTree(ai.nodes[8]);

    do {
        turn ++;
        board.Display();
        board.GetInput();
        gameWon = board.CheckForWin(turn);
        if (!gameWon || turn >= 8) {
            turn++;
            ai.Play(board);
            gameWon = board.CheckForWin(turn);
        } else std::cout << "\nGAME WON!\n";
    } while (!gameWon && turn < 9); 

    board.Display();

    std::cout << "GAME OVER" << std::endl;
    system("Pause");
    return 0;
}