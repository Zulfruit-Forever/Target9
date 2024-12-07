//Zulfat Zigangirov U234N1241 07/12/2024
//Java Course Changed me...

#include <iostream>
#include <iomanip>


class Board {
private:
    int counter = 0;
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


    bool Board::ValidationCheck(int row, int col) const  {
        //bool check=0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == row || j == col) {
               
                    if (Grid[i][j] == 9)
                         return 1;
                }
            }
        }


        return 0;
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
        int row = rand() % 3 + 1, col = rand() % 3 + 1;

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
            if (i == row || j == col) {
                if (seq == false) {
                    if (Grid[i][j] != 9)
                        Grid[i][j] += 1;
                }
                else
                    if (Grid[i][j] != 0)
                        Grid[i][j] -= 1;


            }  
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

    int counter = 0;
    Entry entry;

    Stack* next;

    Stack() { next = nullptr; }
    Stack(int r, int c, Stack* n) {
        entry.row = r;
        entry.col = c;
        next = n;
        counter++;
    }
    //is it empty?
    bool empty();
    //delete
    void pop();

    void push(int, int);
    //find size
    int size() const { return counter; }


    void Undo(Board& board) {

        if (this->empty()) {
            std::cout << "No moves to undo!\n";
            return;
        }


        //easter egg with printf
        printf("\nMethod Undo\n");


        board.changeGrid(this->next->entry.row-1, this->next->entry.col-1, 1);

        std::cout << "\n";

        board.ShowBoard();
        counter--;

    }
    void Redo() {
        std::cout << "Redo\n";

    }


    //check
    void printStack() {
        Stack* current = this->next;
        while (current != nullptr) {
            std::cout << "Row: " << current->entry.row << ", Col: " << current->entry.col << std::endl;
            current = current->next;
        }
    }

};


//Check for Stack is empty
bool Stack::empty() {

    if (this == nullptr) return 1;

    return 0;

}


void Stack::pop() {
    if (empty())return;
    //create new var, remove it from the sequince and delete
    Stack* temp = this->next;
    this->next = this->next->next;
    delete temp;

}
//Useless
void Stack::push(int row, int col) {

    this->next = new Stack(row, col, this->next); // Create a new node and link it to the previous
    this->counter++; // Increment the counter


}


/// Main Function

int main()
{    // Obj to main
    Board x1;

    // Obj to the Stack
    Stack* x2 = new Stack;

    char ans = 'y';

    std::cout << "#Select the Difficulty \\1-9\\\n";
    std::cin >> x1.difficultyVar;

    std::cout << "This is that You Must Get\n";
    x1.ShowBoard();
    std::cout << "\n";

    // Change the Grid by Difficulty
    x1.Difficulty();

    std::cout << "From this...Ehh...Good Luck Then!\n";
    x1.ShowBoard();

    /*
    do {
        if (ans == 'n') break;
        else if (ans == 'y') continue;
        else std::cout << "Undifined command";
    } while ((std::cin>>ans));
    */

    do {
        std::cout << std::endl;

        // x1.ShowBoard();

        do {
            std::cout << "\n#Select the row and cow \n#In the range of 1-3 # That Does not affect 9-s in the Grid#\n";
            std::cin >> x1.row >> x1.col;
        } while ((x1.row < 1 || x1.row > 3 || x1.col < 1 || x1.col > 3) || (x1.ValidationCheck(x1.row, x1.col) == 0));

        x1.changeGrid(x1.row - 1, x1.col - 1, 0);

        x1.ShowBoard();

        std::cout << std::endl;
        // Manual push 

        x2->next = new Stack(x1.row, x1.col, x2->next);

        std::cout << "Undo?\n#";
        std::cin >> ans;
        if (ans == 'y')
            x2->Undo(x1);
        else
            std::cout << "Oh\n";

    } while (x1.Finish() != 1);

    std::cout << "\n###Congrats!###\n\n";

    std::cout << "print\n";
    x2->printStack();

    x1.ShowBoard();
    delete x2;

    return 0;
}

