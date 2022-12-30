#include "model.hxx"
#include <catch.hxx>
#include <iostream>


//
// These tests should demonstrate your functional requirements.

//Test 1: is game over?
TEST_CASE("is game over?"){
    Model model = Model();
    CHECK_FALSE( model.get_game_over());
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.increment_current_guess();
    model.set_game_over_();
    CHECK_FALSE(model.correct_answer_guessed());
    CHECK(model.get_game_over());
}

//Test 2: Check real word
TEST_CASE("Check Real Word"){
    Model model = Model();
    model.add_letter('d');
    model.add_letter('d');
    model.add_letter('d');
    model.add_letter('d');
    model.add_letter('d');
    CHECK_FALSE(model.real_word());

    model.increment_current_guess();
    model.reset_piw();

    model.add_letter('d');
    model.add_letter('r');
    model.add_letter('e');
    model.add_letter('a');
    model.add_letter('m');
    CHECK(model.real_word());
}

//Test 3: Check correct answer
TEST_CASE("Check correct"){
    Model model = Model();
    std::string guess;
    model.add_letter('g');
    model.add_letter('u');
    model.add_letter('e');
    model.add_letter('s');
    model.add_letter('s');
    for(int i = 0; i < model.columns; i++){
        guess +=  model.grid_at(model.get_current_guess(), i);
    }
    CHECK(guess == model.get_word_solution());
}

//Test 4: Hint unused/hint used
TEST_CASE("hint has been used"){
    Model model = Model();
    CHECK_FALSE(model.get_hint_used());
    model.update_hint_used();
    CHECK(model.get_hint_used());

}

//Test 5: Check Instructions
TEST_CASE(" instructions have been used"){
    Model model = Model();
    CHECK_FALSE(model.get_instructions_called());
    model.set_instructions_called();
    CHECK(model.get_instructions_called());
    //exit instructions window
    model.set_instructions_called();
    CHECK_FALSE(model.get_instructions_called());
}
