//Zulfat Zigangirov U234N1241 07/12/2024


#include <iostream>
#include <iomanip>


class Board {
private:
    int Grid[3][3] = { {9,9,9},{9,9,9},{9,9,9} };
    
public:
    //Will change mod to see past and future
    bool seq = 0;
    int row, col;
    int difficultyVar;

    //int entry[2];
 
    //Methods
    void ShowBoard() const;
    void changeGrid(int row, int col ,bool seq);
    void Difficulty();
    bool Finish() const;
    bool ValidationCheck(int row, int col) const;


};

// Check the specified row or column to not be = 9;
bool Board::ValidationCheck(int row, int col) const {
    for (int i = 0; i < 3; i++) {
        if (Grid[row][i] == 9 || Grid[i][col] == 9) {
            return true; //One of them is a 9
        }
    }
    return false;
}

bool Board::Finish() const {
    int reference[3][3] = { {9,9,9},{9,9,9},{9,9,9} };

    for (int i = 0; i < 3; i++) {
     
        for (int j = 0; j < 3; j++)
            if (Grid[i][j]!=reference[i][j])
                return 0;
      
    }
    return 1;
}

void Board::Difficulty() {

    srand(time(0));

    for (int k = 0; k < difficultyVar; k++) {
        int row = rand() % 3 , col = rand() % 3 ;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == row || j == col)
                    Grid[i][j] -= 1;

            }
        }

    }

}


void Board::changeGrid(int row, int col, bool seq) {
    /*
    * seq==0 func works as it must by default Grid[i][j]+=1;
    * seq==1 funk works to see the past Grid[i][j]-=1;
    */


    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (seq == false) {
                if (i == row || j == col)
                    Grid[i][j] += 1;
            }
            else
                if (i == row || j == col)
                    Grid[i][j] -= 1; 
        }
    }
}

//
//Shows The Board
//
void Board::ShowBoard() const {
    std::cout << "* # " <<  "# " << "#\n";

    for (int i = 0; i < 3; i++) {
        std::cout << "#" << std::setw(2);
        for (int j = 0; j < 3; j++) 
            std::cout << Grid[i][j] << std::setw(2);
        
        std::cout << '\n';
    }
        
}

struct Entry {
    int row;
    int col;
};


//Our Stack
struct Stack {
private:
    Stack* topnode;
    Stack* currentNode;
    Stack* next = nullptr;
public:
    Entry entry;

    Stack() { topnode = nullptr; currentNode = nullptr;}
    
    Stack(int r, int c, Stack* n) {
        entry.row = r;
        entry.col = c;
        next = n;
    }
    //is it empty?
    bool empty();
    //delete 
    void pop();
    //Do you really need comments for that?
    void push(int, int);

    //
    //void clearAfterUndo();


    void Undo(Board& board) {
        if (currentNode == nullptr) {
            std::cout << "No moves to undo!\n";
            return;
        }

        //easter egg with printf
        printf("\nMethod Undo\n");

        // Apply undo action
        board.changeGrid(currentNode->entry.row, currentNode->entry.col, 1);

        // Move currentNode to the next in the sequence
        currentNode = currentNode->next;

        std::cout << "\n";
        board.ShowBoard();
    }

    void Redo(Board& board) {

        if (topnode == nullptr || currentNode == topnode) {
            std::cout << "No moves to redo!\n";
            return;
        }

        //we need to find a node before the current
        //    ___         ___
        //      ||   v   ||
        //      ||  temp ||
        //      ||   v   ||
        //      ||current||
        //      ||   v   ||
        //      ||  next ||
        //         
        printf("\nMethod Redo\n");

        // Move currentNode back to the previous node
        if (currentNode == nullptr) {
            currentNode = topnode;
        }
        else {
            currentNode = currentNode->next;
        }

        //if ((board.ValidationCheck(currentNode->entry.row, currentNode->entry.row)))
        board.changeGrid(currentNode->entry.row, currentNode->entry.col, 0);
        //else
        //   std::cout << "Cannot procced, 9-s being affected\n";

        board.ShowBoard();
    }


    //check
    void printStack() {
        Stack* current = topnode;
        while (current != nullptr) {
            std::cout << "Row: " << current->entry.row << ", Col: " << current->entry.col << std::endl;
            current = current->next;
        }
    }

};


//Check for Stack is empty
//Useless
bool Stack::empty() {

    if (topnode== nullptr) return 1;

    return 0;

}

//didnt implemented that
void Stack::pop() {
    if (empty())return;
    //create new var, remove it from the sequince and delete
    Stack* temp = topnode;
    topnode = topnode->next;
    delete temp;

}
//Pushing the new entitis to the stack;
void Stack::push(int row, int col) {

    /*This double loop must :
    *
    Check if there is something next from the current node, if yes  :
        topNode          current
           v                v //that next!=nullptr||that next too||that next==nullptr , this is the end
           v                v        V               V              V
       | x   y |   ->   | x   y |   ->   | x  y |   ->   | x  y |  -> nullptr;

       We have to find the last NODE and delete it and every other node until current node to prevent the memory leak
    */

    // If there are nodes after the currentNode, clean them up to avoid memory leaks
    if (currentNode != nullptr) {
        Stack* cleaner = currentNode->next;
        while (cleaner != nullptr) {
            Stack* toDelete = cleaner;
            cleaner = cleaner->next; // Move to the next node.
            delete toDelete;         // Delete the current node.
        }
        currentNode->next = nullptr; // Ensure no dangling pointers.
    }

    // Create a new node for the new move
    Stack* temp = new Stack(row, col, topnode); 
    topnode = temp; // Update topnode to point to the new node.
    currentNode = topnode; 
}

/// Main Function

int main() {
    // Obj to main
    Board x1;

    // Obj to the Stack
    Stack* x2 = new Stack;

    //char ans ;
    int choice;

    std::cout << "#Select the Difficulty \\1-9\\\n";
    std::cin >> x1.difficultyVar;

    std::cout << "This is that You Must Get\n";
    x1.ShowBoard();
    std::cout << "\n";

    // Change the Grid by Difficulty
    x1.Difficulty();

    std::cout << "From this...Ehh...Good Luck Then!\n";
    x1.ShowBoard();

    do {
        std::cout << "\n#Menu#\n";
        std::cout << "1. Undo Last Move\n";
        std::cout << "2. Redo Last Move\n";
        std::cout << "3. Exit Game\n";
        std::cout << "4. Make a Move\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: // Undo last move
            x2->Undo(x1);
            break;

        case 2: // Redo last move
            x2->Redo(x1);
            break;

        case 3: // Exit game
            std::cout << "Exiting game. Goodbye!\n";
            delete x2;
            return 0;

        case 4: // Make a move
            do {
                std::cout << "\n#Select the row and cow \n#In the range of 1-3 # That Does not affect 9-s in the Grid#\n";

                x1.ShowBoard(); std::cout << "\n\n";

                std::cin >> x1.row >> x1.col;
                x1.row--; x1.col--;
            } while ((x1.row < 0 || x1.row > 2 || x1.col < 0 || x1.col > 2) || (x1.ValidationCheck(x1.row, x1.col) ));

            x1.changeGrid(x1.row , x1.col , 0);

            x1.ShowBoard();

            std::cout << std::endl;

            // Manual push 
            x2->push(x1.row, x1.col);

            //x2->next = new Stack(x1.row, x1.col, x2->next);

            break;

        default:
            std::cout << "Invalid choice! Try again.\n";
        }

    } while (x1.Finish() != 1);

    std::cout << "\n###Congrats!###\n\n";

    std::cout << "print\n";
    x2->printStack();

    x1.ShowBoard();

    //Clean memory

    delete x2;

    return 0;
}
