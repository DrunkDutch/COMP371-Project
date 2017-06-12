//
// Created by Jeremy Brown on 2017-05-09.
//

#include "window.hpp"
#include "input.hpp"

int window_width = 800;
int window_height = 800;
const char *window_title = "COMP 371 - Assignment 2";


int main()
{
    Window window(window_title, window_height, window_width);
    input::set_active_window(&window);

    // Display the window until it is closed
    window.show_blocking();

    return 0;
}
