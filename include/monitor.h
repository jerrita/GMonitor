#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <oled.h>

// print to screen
#define d_printf(f_, ...)              \
    display.printf(f_, ##__VA_ARGS__); \
    display.display()
// print to screen cache
#define c_printf(f_, ...) display.printf(f_, ##__VA_ARGS__)

struct PCStatus
{
    // CPU
    int cpu_usage;
    int cpu_freq;
    int cpu_temp;

    // GPU
    int gpu_usage;
    int gpu_freq;
    int gpu_temp;
};

// monitor.cpp
void render_screen();

// fetcher.cpp
void fetcher_init();
bool fetch_status();

extern OLED display;    // Main
extern WiFiClient cli;  // Fetcher
extern PCStatus status; // Monitor