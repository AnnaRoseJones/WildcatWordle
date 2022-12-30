#pragma once

#include "model.hxx"

static int cell_size = 100;//this is in screen pixels rn

class View
{
public:
    using Dimensions = ge211::Dims<int>;

    Dimensions initial_window_dimensions() const;

    explicit View(Model const& model,
                  const std::string filename,
                  ge211::Mixer& mixer);

    void draw(ge211::Sprite_set& set, bool ek);

    void play_win_sound() const;

    void play_lose_sound() const;

private:
    Model const& model_;
    ge211::Font sans75_{"sans.ttf", 75};
    ge211::Font sans30_{"sans.ttf", 30};
    ge211::Text_sprite letter_sprite_[6][7];
    ge211::Text_sprite game_over_sprite;
    ge211::Text_sprite correct_word_sprite;
    ge211::Text_sprite timer_sprite_;
    int counter = 0;
    ge211::sprites::Rectangle_sprite const new_guess;
    ge211::sprites::Rectangle_sprite const white_sprite;
    ge211::sprites::Rectangle_sprite const purple_sprite;
    ge211::sprites::Rectangle_sprite const answer_box_sprite;
    ge211::sprites::Image_sprite instructions_;

    void load_audio_();
    ge211::Mixer& mixer_;
    ge211::Sound_effect win_sound_;
    ge211::Sound_effect lose_sound_;
    ge211::Sound_effect_handle success_handle_;

};
