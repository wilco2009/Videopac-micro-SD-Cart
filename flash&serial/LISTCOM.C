#include <stdio.h>
#include <windows.h>
#include <winbase.h>

BOOL COM_exists( int port)
{
       char buffer[7];
       COMMCONFIG CommConfig;
       DWORD size;

       if (! (1 <= port && port <= 255))
       {
           return FALSE;
       }

       snprintf( buffer, sizeof buffer, "COM%d", port);
       size = sizeof CommConfig;

       // COM port exists if GetDefaultCommConfig returns TRUE
       // or changes <size> to indicate COMMCONFIG buffer too small.
       return (GetDefaultCommConfig( buffer, &CommConfig, &size)
                                                       || size > sizeof CommConfig);
}

int main()
{
       int i;

       for (i = 1; i < 256; ++i)
       {
           if (COM_exists( i))
           {
               printf( "COM%d exists\n", i);
           }
       }

       return 0;
}