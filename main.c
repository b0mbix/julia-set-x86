#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "julia.h"


ALLEGRO_DISPLAY *display;


int draw() {
//    whole julia operations is to be done here, rn it's black screen
    al_flip_display();
}


int main(int argc, char * argv[]) {
    ALLEGRO_EVENT_QUEUE * queue;

//    init allegro and modules
    al_init();
    al_install_keyboard();

    display = al_create_display(640, 480);

//    events
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
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

//        redrawing when enter is pressed
        if (event.type == ALLEGRO_EVENT_KEY_DOWN
            && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            draw();
    }

    al_destroy_display(display);
    al_uninstall_keyboard();

    return 0;
}