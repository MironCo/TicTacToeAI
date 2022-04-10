#include <iostream> 
#include <vector>

struct BoardPosition
{
    char board[3][3];
    
    void Reset()
    {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                board[x][y] = (char)((x*3) + y + '1');
            }
        }
    }  
};

class Board
{
public:
    BoardPosition board;
public:
    Board() {
        board.Reset();
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

    int line;

    Node() = default;

    Node(int _line, BoardPosition &_data) {
        line = _line;
        data = _data;
        //GenerateNodes();
    }
    void GenerateNodes() {
        char turn;
        if ((line+1) % 2 == 1) turn = 'X';
        else turn ='O';

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                Node* newNode = new Node(line+1, data);
                
                if (newNode->data.board[x][y] != 'X' && newNode->data.board[x][y] != 'O')
                {
                    newNode->data.board[x][y] = turn;
                    children.push_back(newNode);
                } else delete(newNode);
            }
        }

        if (line < 9) for (Node* &node : children) node->GenerateNodes();
    }

    void DisplayTree()
    {
        /*std::cout << "\nLine: " << line << std::endl;
        std::cout << "-----------\n";
        for (int x = 0; x < 3; x++) {
            
            for (int y = 0; y < 3; y++) {
                std::cout << " " << data.board[x][y] << " ";
                if (y != 2) std::cout << "|";
            }
            std::cout << "\n-----------\n";
        }*/
        std::cout << "Line " << line << ": " << "Size " << children.size();
        for(Node* &node : children) node->DisplayTree();
    }
};

class AI
{
public:
    std::vector<Node*> nodes;
public:
    AI() {
        
    }
    void Generate() {
        int x = 0, y = 0;
        //for (int x = 0; x < 1; x++) {
        //    for (int y = 0; y < 1; y++) {
                BoardPosition newPos;
                newPos.Reset();
                newPos.board[x][y] = 'X';

                int line = 1;
                Node* node = new Node(line, newPos);
                nodes.push_back(node);
                for (Node* &node : nodes) node->GenerateNodes();
        //    }
        //}
    }
    static inline void DisplayBoard(Node &board)
    {
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

    ai.nodes[0]->DisplayTree();

    return 0;
}