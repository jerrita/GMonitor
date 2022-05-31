#include "monitor.h"

WiFiClient cli;
String http_request;

void fetcher_init()
{
    http_request = String("GET /sse") + " HTTP/1.1\r\n" +
                   "Host: " + cli.remoteIP().toString() + "\r\n" +
                   "User-Agent: GMonitor v1.0 \r\n" +
                   "Connection: close\r\n" +
                   "\r\n";
}

// Fetch computer status from aida64
bool fetch_status()
{
    if (!cli.connected())
        return false;

    cli.print(http_request);
    Serial.println("Request send.");

    while (!cli.available())
        delay(100); // Wait for data
    
    char buffer[512];
    cli.readBytes(buffer, 512);
    String s = String(buffer);
    Serial.println("Recv.");

    // Parse buffer to PCStatus status
    // and fill status body
    int datStart = 0, datEnd = 0;
    String datstr;

    char cpu_freq[] = "CPU_FREQ";
    datStart = s.indexOf(cpu_freq) + strlen(cpu_freq);
    datEnd = s.indexOf("MHz", datStart);
    datstr = s.substring(datStart, datEnd);
    status.cpu_freq = datstr.toInt();

    char gpu_freq[] = "GPU_FREQ";
    datStart = s.indexOf(gpu_freq) + strlen(gpu_freq);
    datEnd = s.indexOf("MHz", datStart);
    datstr = s.substring(datStart, datEnd);
    status.gpu_freq = datstr.toInt();

    char cpu_temp[] = "CPU_TEMP";
    datStart = s.indexOf(cpu_temp) + strlen(cpu_temp);
    datEnd = s.indexOf("℃", datStart);
    datstr = s.substring(datStart, datEnd);
    status.cpu_temp = datstr.toInt();

    char gpu_temp[] = "GPU_TEMP";
    datStart = s.indexOf(gpu_temp) + strlen(gpu_temp);
    datEnd = s.indexOf("℃", datStart);
    datstr = s.substring(datStart, datEnd);
    status.gpu_temp = datstr.toInt();

    char cpu_use[] = "CPU_USE";
    datStart = s.indexOf(cpu_use) + strlen(cpu_use);
    datEnd = s.indexOf("%", datStart);
    datstr = s.substring(datStart, datEnd);
    status.cpu_usage = datstr.toInt();

    char gpu_use[] = "GPU_USE";
    datStart = s.indexOf(gpu_use) + strlen(gpu_use);
    datEnd = s.indexOf("%", datStart);
    datstr = s.substring(datStart, datEnd);
    status.gpu_usage = datstr.toInt();

    char cpu_power[] = "CPU_POWER";
    datStart = s.indexOf(cpu_power) + strlen(cpu_power);
    datEnd = s.indexOf("%", datStart);
    datstr = s.substring(datStart, datEnd);
    status.cpu_power = datstr.toFloat();

    char gpu_power[] = "GPU_POWER";
    datStart = s.indexOf(gpu_power) + strlen(gpu_power);
    datEnd = s.indexOf("%", datStart);
    datstr = s.substring(datStart, datEnd);
    status.gpu_power = datstr.toFloat();

    Serial.println("Processed.\n");

    return true;
}