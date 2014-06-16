#include <pebble.h>
#include <stdlib.h> //should work, but may not be part of Pebble structure

//Pebble documentation: https://developer.getpebble.com/2/api-reference/index.html

static Window *window;
static TextLayer *text_layer;

int random_number = -1;
int random(time_t);

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    //from main menu, should bring up the options screen OR roll the dice
    //text_layer_set_text(text_layer, "Sellect");
    
    text_layer_set_text(text_layer, (char *)time(NULL)); //test to see what the time_t output is
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    //changes the dice
    text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    //changes the dice
    text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}