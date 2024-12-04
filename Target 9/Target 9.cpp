//Zulfat Zigangirov U234N1241 04/12/2024

#include <iostream>
#include <iomanip>


class Board {
private:
    int Grid[3][3] = {{9,9,9},{9,9,9},{9,9,9}};
       
public:
    
    void ShowBoard() const;

    void changeGrid(int row, int col);
       
    

};



void Board::changeGrid(int row, int col) {
    
    for (int i = 0; i < 3; i++) {
        //std::cout << "#" << std::setw(2);
        for (int j = 0; j < 3; j++) {
            if (i == row or j == col)
                Grid[i][j] -= 1;
        }
        //std::cout << '\n';

    }
    
}


class Move {
public:
    int row, col;
    //Object to the Class Board
    Board x;
    //Constructors
    Move()=default;
    //Move(int row, int col);
    
public:    
    void ChGrid()
    {
        x.changeGrid(row, col);
    };

};


void Board::ShowBoard() const {
    std::cout << "* # " <<  "# " << "#\n";

    for (int i = 0; i < 3; i++) {
        std::cout << "#" << std::setw(2);
        for (int j = 0; j < 3; j++) 
            std::cout << Grid[i][j] << std::setw(2);
        
        std::cout << '\n';
    }
        
}



class Undo {


};
class Redo {


};
int main()
{
    Board x1;
    Move x2;
    x1.ShowBoard();
    std::cout << "\n";
    x2.col = 2; x2.col = 1;
    x2.ChGrid();
    x1.ShowBoard();


    return 0;
}

