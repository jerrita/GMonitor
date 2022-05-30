#include "monitor.h"

PCStatus status;

// Render screen with PCStatus status
void render_screen()
{
    c_printf(WiFi.localIP().toString().c_str());
    c_printf("\n\nCPU: %d %%\n     %d MHz\n     %d Celsius", status.cpu_freq, status.cpu_freq, status.cpu_temp);
    c_printf("\nGPU: %d %%\n     %d MHz\n     %d Celsius\n", status.gpu_usage, status.gpu_freq, status.gpu_temp);
}