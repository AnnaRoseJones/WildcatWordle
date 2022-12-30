#include "view.hxx"
#include "iostream"

//type alias
using Color = ge211::Color;

//Constructor
View::View(Model const& model,
           const std::string filename,
           ge211::Mixer& mixer)
        : model_(model),
        letter_sprite_(),
        game_over_sprite(),
        correct_word_sprite(),
        new_guess({cell_size-2, cell_size-2}, Color::black().blend(.2, Color::white())),
        white_sprite({cell_size - 2, cell_size - 3}, Color::medium_yellow()),
        purple_sprite({cell_size - 2, cell_size - 3}, Color::medium_red().blend(.45, Color::medium_blue())),
        answer_box_sprite({cell_size * model_.columns, cell_size*model_.rows + cell_size}, Color::black()),
        instructions_(filename),
        mixer_(mixer)

{
    load_audio_();
}

//Sets the size of the game display
View::Dimensions
View::initial_window_dimensions() const
{
    return {cell_size * model_.columns,  cell_size + cell_size * model_.rows};
}

//Loads sound effects into game mixer
void
View::load_audio_()
{
    win_sound_.try_load("win.wav", mixer_);
    lose_sound_.try_load("lose.wav", mixer_);
}

//Plays winning sound
void
View::play_win_sound() const
{
    mixer_.try_play_effect(win_sound_);
}

//Plays losing sound
void
View::play_lose_sound() const
{
    mixer_.try_play_effect(lose_sound_);
}

//Draws game interface
void
View::draw(ge211::Sprite_set& set, bool ek) {

    //1. Timer in upper right corner (put it in center because I think it looks better this way)
    counter++;
    ge211::Text_sprite::Builder time_builder(sans30_);
    time_builder << "elapsed time (sec): " << std::to_string(counter/60);
    timer_sprite_.reconfigure(time_builder);
    set.add_sprite(timer_sprite_, {100,50}, 5);

    //2. Show correct answer when game ends
    ///TO DO: MAKE PRETTIER!
    if(model_.get_game_over()){

        set.add_sprite(answer_box_sprite, {0, 0}, 12);
        ge211::Text_sprite::Builder message_builder(sans30_);
        message_builder.color(Color::white()) << "the correct answer was:";
        correct_word_sprite.reconfigure(message_builder);
        set.add_sprite(correct_word_sprite, {80, 250}, 15);

        ge211::Text_sprite::Builder endgame_builder(sans30_);
        endgame_builder.color(Color::white()) << model_.get_word_solution();
        game_over_sprite.reconfigure(endgame_builder);
        set.add_sprite(game_over_sprite, {200, 300}, 15);
    }

    //3. Add letters to grid display
    for (int c = 0; c < model_.columns; c++) {
        for (int r = 0; r < model_.rows; r++) {
            ge211::Text_sprite::Builder letter_builder(sans75_);
            letter_builder << model_.grid_at(r, c);
            letter_sprite_[r][c].reconfigure(letter_builder);
            //default tile on grid
            set.add_sprite(new_guess, {c * cell_size, r * cell_size + cell_size}, 5);
            //fill text sprite with keyboard input
            set.add_sprite(letter_sprite_[r][c],
                           {(c * cell_size) + 30, (r * cell_size + cell_size) - 15}, 10);
        }
    }

    //helped with enter key handling
    if (model_.total_letters(model_)){}

    //4. Update square colors where the letters are in the correct position
    for(int r = 0; r < model_.rows; r++){
        for (int c = 0; c < model_.columns; c++){
            if(model_.box_colors[r][c] == "purple"){
                set.add_sprite(purple_sprite, {c * cell_size, r* cell_size +cell_size}, 6);
            }
        }
    }

    //5. Display instructions page
    if(model_.get_instructions_called()){
        ge211::Transform my_transform =
                ge211::Transform{}
                        .scale(0.65);
        set.add_sprite(instructions_, {0,0}, 20, my_transform);
    }

}


