#include <stdlib.h>
#include <stdio.h>

int main()
{
    const int message_len = 10;
    char message[10] = "at";
    char Letters[36][2][6] = {{"a",".-"},{"b","-..."},{"c","-.-."},{"d","-.."},{"e","."},
        {"f","..-."},{"g","--."},{"h","...."},{"i",".."},{"j",".---"},
        {"k","-.-"},{"l",".-.."},{"m","--"},{"n","-."},{"o","---"},
        {"p",".--."},{"q","--.-"},{"r",".-."},{"s","..."},{"t","-"},
        {"u","..-"},{"v","...-"},{"w",".--"},{"x","-..-"},{"y","-.--"},
        {"z","--.."},{"0","-----"},{"1",".--."},{"2","..-.."},{"3","...-."},
        {"4","....-"},{"5","---"},{"6","......"},{"7","--.."},{"8","-...."},
        {"9","-..-"}
    };

    for (int i=0; i<message_len; i++)
    {
        for (int j=0; j<36; j++)
        {
            if(Letters[j][0][0] == message[i])
            {
                printf(Letters[j][1]);
            }
        }
    }

}
