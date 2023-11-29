#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>


int main()
{
	char *locale = setlocale(LC_ALL, "");
    char c;
    int rowNumber = 1;
    int in = open("./OS09_05.txt",O_RDONLY);

    while (read(in,&c,1) == 1)
    {
        if(c == '\n')
        {
            rowNumber++;
        }
    }

    printf("Rows quantity: %d \n",rowNumber);
    return 0;
}