#include "monitor.h"

WiFiClient cli;
String http_request;

void fetcher_init()
{
    http_request = String("GET /") + " HTTP/1.1\r\n" +
                   "Host: " + cli.remoteIP().toString() + "\r\n" +
                   "Connection: close\r\n" +
                   "\r\n";
}

// Fetch computer status from aida64
bool fetch_status()
{
    cli.print(http_request);
    Serial.println("Send request: ");
    Serial.println(http_request);

    while (cli.connected() || cli.available())
    {
        if (cli.available())
        {
            String line = cli.readStringUntil('\n');
            Serial.println(line);
        }
    }
    
    return true;
}