#include "monitor.h"

OLED display(D2, D1, NO_RESET_PIN, OLED::W_128, OLED::H_64);

// Manage wifi and loop logic

// WiFi Config
const char *WiFi_SSID = "CQUPT-3G";
const char *WiFi_Password = "pa5sw0rd";
// Aida64 Config
const char *PC_HOSTNAME = "Jerrita-MSI";
const int PC_PORT = 888;

void setup()
{
    // Initialize
    display.begin();
    display.setTTYMode(true);
    Serial.begin(9600); // For debug

    WiFi.mode(WIFI_STA);
    WiFi.begin(WiFi_SSID, WiFi_Password);
    WiFi.setAutoReconnect(true);

    d_printf("WiFi Connecting...\n");

    int i = 0;
    while (!WiFi.isConnected())
    {
        delay(500);
        d_printf(".");
        if (++i % 16 == 0)
            d_printf("\n");
    }

    d_printf("\nConnected. Init fetcher...");
    cli.connect(PC_HOSTNAME, PC_PORT);
    fetcher_init();
    d_printf("\nFetcher initialized.\nGo mainlogic");
    display.setTTYMode(false);
}

void loop()
{
    delay(500);
    display.clear();
    if (WiFi.isConnected())
    {
        cli.connect(PC_HOSTNAME, PC_PORT);
        if (fetch_status())
            render_screen();
        else
            d_printf("Fetch failed.\n");
    }
    else
    {
        d_printf("WiFi loose.\nWaiting for reconnect.");
    }
    display.display();
}