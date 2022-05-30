#include "monitor.h"

PCStatus status;

const int max_line = 19;

// a is [0, 100]
void show_persentage(int a)
{
    c_printf("[");
    a = max(a, 0);
    a = min(a, 100);
    int need = max_line * (a / 100.0);
    for (int i = 0; i < need; i++)
        c_printf("-");
    for (int i = 0; i < max_line - need; i++)
        c_printf(" ");
    c_printf("]");
}

// Render screen with PCStatus status
void render_screen()
{
    c_printf("CPU: %d %%\n     %d MHz\n     %d Cel\n", status.cpu_usage, status.cpu_freq, status.cpu_temp);
    show_persentage(status.cpu_usage);
    c_printf("\nGPU: %d %%\n     %d MHz\n     %d Cel\n", status.gpu_usage, status.gpu_freq, status.gpu_temp);
    show_persentage(status.gpu_usage);
    // c_printf(WiFi.localIP().toString().c_str());
}