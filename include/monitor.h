#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <oled.h>

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

// display.cpp
size_t d_printf(const char *, ...);

// monitor.cpp
void render_screen();

// fetcher.cpp
void fetcher_init();
bool fetch_status();

extern OLED display;    // Main
extern WiFiClient cli;  // Fetcher
extern PCStatus status; // Monitor