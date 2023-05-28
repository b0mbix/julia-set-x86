#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "julia.h"


ALLEGRO_DISPLAY *display;
int x;

int draw() {
//    whole julia operations is to be done here, rn it's one coloured screen
    al_clear_to_color(al_map_rgb(x, x, x));
    al_flip_display();
}


int main(int argc, char * argv[]) {
    ALLEGRO_EVENT_QUEUE * queue;
    x = 0;

//    init allegro and modules
    al_init();
    al_install_keyboard();
    al_install_mouse();

    display = al_create_display(640, 480);

//    events
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));



    bool running = true;
    int mouse_interaction = 0;
    draw();
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

//        quiting when window is closed or esc is pressed
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN
            && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            running = false;

//        mouse operations
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // 1 - left button
            // 2 - right button
            mouse_interaction = event.mouse.button;
        }
        // stopping interaction from mouse
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_interaction = 0;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (mouse_interaction == 1)
                printf("left button pressed\n");
            if (mouse_interaction == 2)
                printf("right button pressed\n");
            // scroll - zoom in for 1, zoom out for -1
            if (event.mouse.dz != 0) {
                printf("scroll: %d\n", event.mouse.dz);
                x += event.mouse.dz;
                draw();
            }
        }
    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_uninstall_mouse();

    return 0;
}