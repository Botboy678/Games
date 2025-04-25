#include <iostream> 
using namespace std; 
#include <string> 
#include <unordered_map>

class makeBoard
{
    public: 
/* Hash map with to store number and index positions for the 
    board here I use pair so it can be deconstructed and used later*/
    unordered_map<int, pair<int,int>> number_to_place = 
    {
     {1, {0,0}},{2, {0,1}}, {3, {0,2}},
     {4, {1,0}},{5, {1,1}}, {6, {1,2}},
     {7, {2,0}},{8, {2,1}}, {9, {2,2}}
    };
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
    }; 
    //Dispaying the board
    void displayBoard(){
        for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        if(j == 2)
           cout << board[i][j] << '\n';
           else
           cout << board[i][j] << " | ";     
        }
        if ( i != 2 )
        cout << "--+---+--" << endl; 
    }
 };
};

//This is the horizontal state
//Checks if the chars in the row are equal 
char state1(char board[][3]){
    char winner = ' '; 
    //checking each row (3) and not each individual element
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            winner = board[i][0]; 
        }
    }
    return (winner != ' ') ? winner : ' '; 
}

//This is for the vertical state 
//Checks if the chars in a COLUMN are equal 
char state2(char board[][3]){
    char winner = ' '; 
    //For this one we only need to check the beginning of each column 
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            winner = board[0][i]; 
        }
    }
    return (winner != ' ') ? winner : ' '; 
}

//This is for the oblique state 
//Checks if the chars in a diagonal are equal 
char state3(char board[][3]){
    char winner = ' '; 
    //For this one we are checking the diagonal path for the first and last column 
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
            winner = board[0][0]; 
        } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
            winner = board[0][2]; 
        }
    return (winner != ' ') ? winner : ' '; 
}


char determineWinner(char board[][3]){
/*There are 3 possible win states for tictactoe
1. A Horizontal win, 2. A Vertical win, 3. An oblique win (across)*/
    if(state1(board) != ' '){
        return state1(board); 
    }
    else if (state2(board) != ' '){
        return state2(board); 
    } 
    else if (state3(board) != ' '){
        return state3(board); 
    }
    else return ' '; 
}; 


int main(){
    cout << "Welcome to my TicTacToe CLI Line game" << endl;
    cout << "-----------------" << endl; 
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX; 
    int position = -1; 
    
    //Creating an instance of the board object 
    makeBoard board1;
    board1.displayBoard();  

    //A for loop for each players turn 
    for(int i = 0; i < 9; i++){
    // Displaying the current player
    cout << "The Current Player is: " << currentPlayer << endl; 
    cout << "Choose a position number to make your move: "; 
    cin >> position; 
    if (position > 9 || cin.fail()){
        cout << "You entered an invalid input" << endl; 
        break; 
    }
    
    // I get the index stored in that postion and save it 
    // Deconstruct it so I can then pass it to that position 
    auto [row, col] = board1.number_to_place[position]; 
    board1.board[row][col] = currentPlayer; 
    //Displays the current state of the board after every move 
    board1.displayBoard();
    //switching the current players 
    currentPlayer = (currentPlayer == 'X') ? currentPlayer = 'O' : currentPlayer = 'X';

    //checks the state each time to determine if there's a winner
    if(determineWinner(board1.board) != ' '){
    //Read the board after to know winner (or if it's a draw)
    cout << "The winner is " << determineWinner(board1.board) << endl; 
    break; 
    } 
    else if (determineWinner(board1.board) == ' ' && i == 8){
        cout << "The game was a draw!" << endl; 
    }
    }
//This is just to prevent the executable from closing after the program stops running 
system("pause"); 
};