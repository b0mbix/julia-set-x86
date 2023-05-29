#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "julia.h"


ALLEGRO_DISPLAY *display;
double c_real = 0, c_imaginary = 0, scale = 0.005;
double center_x = 0, center_y = 0;

void draw() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    ALLEGRO_LOCKED_REGION *locked = al_lock_bitmap(al_get_backbuffer(display), ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    double left_x = center_x - width * scale / 2.0;
    double up_y = center_y + height * scale / 2.0;


//    debug info
    printf("left_x = %f\n", left_x);
    printf("up_y = %f\n", up_y);
    printf("scale = %.16f\n", scale);
    printf("c = %f + %fi\n", c_real, c_imaginary);

    julia(width, height, left_x, up_y, scale, c_real, c_imaginary, locked->data, locked->pitch);
    al_unlock_bitmap(al_get_backbuffer(display));

    al_flip_display();
}


int main() {
    ALLEGRO_EVENT_QUEUE * queue;

//    init allegro and modules
    al_init();
    al_install_keyboard();
    al_install_mouse();

    display = al_create_display(500, 500);
    al_set_window_title(display, "Julia set");

//    events
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));



    bool running = true;
    bool to_draw = true;
    int mouse_interaction = 0;
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
            if (mouse_interaction == 1) {
                center_x -= event.mouse.dx * scale;
                center_y += event.mouse.dy * scale;
                to_draw = true;
            }
            if (mouse_interaction == 2) {
                c_real += event.mouse.dx * scale / 2;
                c_imaginary += event.mouse.dy * scale / 2;
                to_draw = true;
            }
            // scroll - zoom in - dz=1, zoom out - dz=-1
            if (event.mouse.dz != 0) {
                scale -= scale * event.mouse.dz * 0.1;
                to_draw = true;
            }
            if (to_draw && al_is_event_queue_empty(queue)) {
                to_draw = false;
                if (scale < 1e-15)
                    scale = 1e-15;
                draw();
            }
        }
    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_uninstall_mouse();

    return 0;
}