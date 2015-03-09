/*
  inSquare

  Copyright 2015 Theo Browne
  Author: Theo Browne
  Website: TheoBrowne.com
  Github: Github.com/TheoBr
*/

#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer_top;
static TextLayer *s_time_layer_bottom;
static GFont s_time_font_top;
static GFont s_time_font_bottom;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void update_time() {
  
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00";
  static char bufferbottom[] = "00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00"), "%H", tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00"), "%I", tick_time);
  }
  
  strftime(bufferbottom, sizeof("00"), "%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_top, buffer);
  text_layer_set_text(s_time_layer_bottom, bufferbottom);
}

static void main_window_load(Window *window) {
  
  //Create GBitmap, then set to created BitmapLayer
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND_IMAGE);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  s_time_font_top = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Font_72));
  s_time_font_bottom = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Font_Light_72));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
  
  // Create time TextLayerTop
  s_time_layer_top = text_layer_create(GRect(0, 4, 144, 82));
  text_layer_set_background_color(s_time_layer_top, GColorClear);
  text_layer_set_text(s_time_layer_top, "00");
  
  //Create time TextLayerBottom
  s_time_layer_bottom = text_layer_create(GRect(0, 74, 144, 152));
  text_layer_set_background_color(s_time_layer_bottom, GColorClear);
  text_layer_set_text(s_time_layer_bottom, "00");

  #ifdef PBL_COLOR
    text_layer_set_text_color(s_time_layer_top, GColorElectricUltramarine);
    text_layer_set_text_color(s_time_layer_bottom, GColorElectricUltramarine);
  #else
    text_layer_set_text_color(s_time_layer_top, GColorWhite);
    text_layer_set_text_color(s_time_layer_bottom, GColorWhite);
  #endif

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_top));
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_bottom));
  
  // Make sure the time is displayed from the start
  update_time();

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer_top, s_time_font_top);
  text_layer_set_text_alignment(s_time_layer_top, GTextAlignmentCenter);
  
  //Same for bottom layer
  text_layer_set_font(s_time_layer_bottom, s_time_font_bottom);
  text_layer_set_text_alignment(s_time_layer_bottom, GTextAlignmentCenter);

  #ifdef PBL_COLOR
    text_layer_set_text_color(s_time_layer_top, GColorElectricUltramarine);
    text_layer_set_text_color(s_time_layer_bottom, GColorElectricUltramarine);
  #else
    text_layer_set_text_color(s_time_layer_top, GColorWhite);
    text_layer_set_text_color(s_time_layer_bottom, GColorWhite);
  #endif

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_top));
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_bottom));
  
  // Make sure the time is displayed from the start
  update_time();

}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer_top);
  text_layer_destroy(s_time_layer_bottom);
  // Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  // Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  fonts_unload_custom_font(s_time_font_top);
  fonts_unload_custom_font(s_time_font_bottom);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}