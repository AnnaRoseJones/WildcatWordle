#pragma once

#include "model.hxx"
#include "view.hxx"
#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(const std::string);

    void on_key(ge211::Key key) override;

    void set_enter_key(bool ek);


protected:

    void draw(ge211::Sprite_set& set) override;

    View::Dimensions initial_window_dimensions() const override;

private:

    Model model_;

    View view_;

    bool enter_key;


};
