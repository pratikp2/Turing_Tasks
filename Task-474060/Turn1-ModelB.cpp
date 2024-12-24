#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Event types
enum EventType {
    EVENT_TYPE_NONE,
    EVENT_TYPE_BUTTON_CLICK,
    EVENT_TYPE_KEY_PRESS
};

// Event structure
typedef struct {
    enum EventType type;
    void *data;
} Event;

// Button click event data
typedef struct {
    int button_id;
} ButtonClickEvent;

// Key press event data
typedef struct {
    char key;
} KeyPressEvent;

// Function to create a new button click event
Event* create_button_click_event(int button_id) {
    Event* event = (Event*)malloc(sizeof(Event));
    ButtonClickEvent* data = (ButtonClickEvent*)malloc(sizeof(ButtonClickEvent));
    event->type = EVENT_TYPE_BUTTON_CLICK;
    event->data = data;
    data->button_id = button_id;
    return event;
}

// Function to create a new key press event
Event* create_key_press_event(char key) {
    Event* event = (Event*)malloc(sizeof(Event));
    KeyPressEvent* data = (KeyPressEvent*)malloc(sizeof(KeyPressEvent));
    event->type = EVENT_TYPE_KEY_PRESS;
    event->data = data;
    data->key = key;
    return event;
}

// Function to handle button click events
void handle_button_click_event(Event* event) {
    ButtonClickEvent* data = (ButtonClickEvent*)event->data;
    printf("Button %d clicked.\n", data->button_id);
}

// Function to handle key press events
void handle_key_press_event(Event* event) {
    KeyPressEvent* data = (KeyPressEvent*)event->data;
    printf("Key '%c' pressed.\n", data->key);
}

// Function to process an event
void process_event(Event* event) {
    switch (event->type) {
        case EVENT_TYPE_BUTTON_CLICK:
            handle_button_click_event(event);
            break;
        case EVENT_TYPE_KEY_PRESS:
            handle_key_press_event(event);
            break;
        default:
            break;
    }
}

// Function to free an event's memory
void free_event(Event* event) {
    free(event->data);
    free(event);
}

// Main event loop
int main() {
    Event** events = NULL;
    size_t event_count = 0;

    // Push some sample events into the array
    events = realloc(events, sizeof(Event*) * (event_count + 1));
    events[event_count] = create_button_click_event(1);
    event_count++;

    events = realloc(events, sizeof(Event*) * (event_count + 1));
    events[event_count] = create_key_press_event('A');
    event_count++;

    events = realloc(events, sizeof(Event*) * (event_count + 1));
    events[event_count] = create_button_click_event(2);
    event_count++;

    // Process each event
    for (size_t i = 0; i < event_count; i++) {
        process_event(events[i]);
        free_event(events[i]);
    }

    // Free the event array
    free(events);

    return 0;
}
