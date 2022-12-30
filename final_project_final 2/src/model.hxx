#pragma once

#include <ge211.hxx>



class Model
{
public:

    Model();

    const int rows = 6;
    const int columns = 5;

    std::string box_colors[6][7] = {""};

    char grid_at(int i, int j) const;

    int get_piw() const{
        return piw_;
    }

    int get_current_guess() const{
        return current_guess_;
    }

    bool real_word();

    bool get_game_over() const{
        return game_over_;
    }

    std::string
    get_word_solution() const{
        return word_solution_;
    }

    void reset_piw(){
        piw_ = 0;
    }

    void increment_current_guess(){
        current_guess_++;
    }


    void add_letter(char actual);

    void remove_letter();

    void set_key(char k){
        key_pressed_ = k;
    }

    char get_key()const{
        return key_pressed_;
    }

    bool total_letters(Model model) const;

    int get_random(int lower, int upper);

    void update_hint_used(){
        hint_used_ = true;
    }

    bool get_hint_used() const{
        return hint_used_;
    }

    char guess_arr[5];

    bool correct_answer_guessed();

    bool is_game_over();

    void set_instructions_called();

    bool get_instructions_called() const{
        return instructions_called_;
    }

    void set_game_over_();

private:

    char grid_[6][7];

    std::string word_solution_;

    std::vector<std::string> dictionary_;

    int current_guess_;

    int piw_; //piw stands for position in word (corresponds to the index of a specific row on the board)

    char key_pressed_;

    bool game_over_;

    bool hint_used_;

    bool instructions_called_;

};

