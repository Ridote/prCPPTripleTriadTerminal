#include <stdio.h>
#include <Windows.h>
#include <string.h>

void pintaDegradado(int filas, int columnas)
{

    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            SetPixel(mydc, j,i,RGB((int)i*255/filas,(int)j*255/columnas, abs((i*255/filas) - (j*255/columnas))));
        }
    }
}
