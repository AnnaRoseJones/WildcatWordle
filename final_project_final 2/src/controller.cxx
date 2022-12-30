#include "controller.hxx"
#include <iostream>
//Constructor
Controller::Controller(const std::string filename)
        :model_(),
        view_(model_,
              filename,
              mixer()),
        enter_key(false)

{ }

//Call to Draw --> makes game interface
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, enter_key);
}

//Sets dimensions of the game display
View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

//Indicates whether enter key has been pressed (helper for on key)
void
Controller::set_enter_key(bool ek){
    enter_key = ek;
}

//Handles various keyboard inputs
void
Controller::on_key(ge211::Key key) {
    //1. Check if game is over
    if (model_.is_game_over()) {
        if(model_.correct_answer_guessed()){
            view_.play_win_sound();
        }
        if(!model_.correct_answer_guessed()){
            view_.play_lose_sound();
        }
        model_.set_game_over_();
        return;
    }

    //2. Handle return key events (incrementing letters, adding letters to board, determining correct positions)
    if (key == ge211::Key::code('\r')) {
        if (model_.total_letters(model_)) {
            if(!model_.real_word()){
                for(int i = 0; i < model_.columns; i++){
                    model_.remove_letter();
                }

            }
            else{
                for (int i = 0; i < model_.columns; i++) {
                    int current_guess = model_.get_current_guess();
                    auto word_solution = model_.get_word_solution();
                    model_.guess_arr[i] = model_.grid_at(current_guess, i);
                    if (word_solution[i] == model_.guess_arr[i]) {
                        model_.box_colors[current_guess][i] = "purple";
                    }

                }
                set_enter_key(true);
                model_.increment_current_guess();
                model_.reset_piw();
                return;
            }
        }
    }
    set_enter_key(false);

    //3. Handle backspace events (delete letter from board)
    if (key == ge211::Key::code('\b')) {
        if (0 < model_.get_piw() <= model_.columns - 1) {
            model_.remove_letter();
        }
    }

    //4. Add valid letters to board
    if (model_.get_piw() <= model_.columns - 1) {
        //columns - 1 because of 0 starting index
        std::cout << model_.grid_at(model_.get_piw(), 0) << "\n";
        if (isalpha(char(key.code()))) {
            auto letter = char(key.code());
            model_.set_key(letter);
            //call add_letter to increment piw_ and add the letter to the grid
            model_.add_letter(model_.get_key());
        }
    }

    //5. Generate hint
    if (key == ge211::Key::code('5')) {
        if (model_.get_hint_used()) {
            return;
        }
        int hint_index = model_.get_random(0, 4);
        int current_guess = model_.get_current_guess();
        auto word_solution = model_.get_word_solution();
        char hint_letter = word_solution[hint_index];
        if (model_.box_colors[current_guess][hint_index] == "purple") {
            return;
        }
        model_.set_key(hint_letter);
        model_.add_letter((model_.get_key()));
        model_.update_hint_used();

    }

    //5. Generate instructions page
    if(key == ge211::Key::code('4')){
        model_.set_instructions_called();
    }

    //6. Exit instructions page
    if(key == ge211::Key::code('0')){
        model_.set_instructions_called();
    }
    else{
        return;
    }
}

    
