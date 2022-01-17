#include <stdio.h>
#include <stdlib.h>
# include <string.h>
int main()
{
    char morse[] = "... --- ... )";
    int length=sizeof(morse)/sizeof(char);
    char alphanumeric[]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
    char morse_alphanumeric[36][5] =
    {
        ".-",   // A
        "-...", // B
        "-.-.", // C
        "-..",  // D
        ".",    // E
        ".._.", // F
        "--.",  // G
        "....", // H
        "..",   // I
        ".---", // J
        "-.-",  // K
        ".-..", // L
        "--",   // M
        "-.",   // N
        "---",  // O
        ".--.", // P
        "--.-", // Q
        ".-.",  // R
        "...",  // S
        "-",    // T
        "..-",  // U
        "...-", // V
        ".--",  // W
        "-..-", // X
        "-.--", // Y
        "--..",  // Z

        "-----",// 0
        ".----",// 1
        "..---",// 2
        "...--",// 3
        "....-",// 4
        ".....",// 5
        "-....",// 6
        "--...",// 7
        "---..",// 8
        "----.",// 9
    };
    int start_morse = 0;

    for (int i=0; i<length; i++)
    {
        char c[10] = "";
        if(morse[i]==' ')
        {

            if (start_morse == 0)
            {
                strncpy(c,&morse[start_morse],(i)-(start_morse));
            }
            else
            {
                strncpy(c,&morse[start_morse],i-start_morse);
            }
            start_morse = i + 1;

            for (int j=0;j<36;j++)
            {

                int comp = strcmp(morse_alphanumeric[j],c);
                if (comp == 0)
                {
                    printf("%c",alphanumeric[j]);
                }
            }
        }
    }
    return 0;
}
