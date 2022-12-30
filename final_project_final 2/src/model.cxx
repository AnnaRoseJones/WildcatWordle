#include "model.hxx"
#include <iostream>
#include <string>

//Constructor
Model::Model()
    :word_solution_("guess"), //this is hard coded in for debugging purposes
     current_guess_ (0),
     piw_(0),
     game_over_(false),
     hint_used_(false),
     instructions_called_(false)
{
    for(int c = 0; c < columns; c++){
        for (int r = 0; r < rows; r++){
            grid_[r][c]  = ' ';
        }
    }
}


//Getter function for the character at grid position [i][j]
char Model::grid_at(int i, int j) const{
    return grid_[i][j];
}

//Adds a letter to the game board (as the user types)
void Model::add_letter(char actual){
    grid_[current_guess_][piw_] = tolower(actual);
    piw_++;
}

//Removes a letter from the board (called on backspace keyboard input)
void Model::remove_letter(){
    piw_--;
    grid_[current_guess_][piw_] = ' ';

}

//Is the row filled
bool Model::total_letters(Model model) const{
    if(model.get_piw() == model.columns){
        return true;
    }
    return false;
}

//generates random int
int Model::get_random(int lower, int upper) {
    int num = (rand() % (upper - lower +  1)) + lower;
    return num;
}

//checks whether input word is in the dictionary
bool Model::real_word(){
    bool real = false;
    std::string line;
    std::string guess = "";
    std::ifstream Dictfile = ge211::open_resource_file("dictionary.txt");

    for(int i = 0; i < columns; i++) {
        guess = guess + grid_at(current_guess_, i);
    }

    while(std::getline(Dictfile, line)){
        if(line.compare(guess) == 0){
            real = true;
        }
    }
    Dictfile.close();
    return real;
}


void
Model::set_game_over_() {
    if (is_game_over()){
        game_over_ = true;
    }
}

bool
Model::is_game_over() {
    if(current_guess_ > 5 || correct_answer_guessed()){
        return true;
    }
    return false;
}

bool
Model::correct_answer_guessed(){
    int count = 0;
    for(int i = 0; i < columns; i++){
        if(guess_arr[i] == word_solution_[i]){
            count++;
        }
    }
    return count == 5;
}

void
Model::set_instructions_called() {
    if(!instructions_called_){
        instructions_called_ = true;
    }
    else{
        instructions_called_ = false;
    }
}


