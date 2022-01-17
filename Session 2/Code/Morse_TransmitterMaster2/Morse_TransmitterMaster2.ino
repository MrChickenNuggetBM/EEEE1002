#include <Wire.h>

//setting the message and finding the size of the message
//declaring morse message array
char message_normal[] = "at an";
const int message_len = sizeof(message_normal) / sizeof(char);
char message_morse[6 * (message_len - 1) + 1];

//variable is true if the entered letter is found in the Letters array
int found_alphanumeric;

//A 3D array which groups each letter with its morse code equivalent
char Letters[36][2][6] =
{
  {"a", ".-"},
  {"b", "-..."},
  {"c", "-.-."},
  {"d", "-.."},
  {"e", "."},
  {"f", "..-."},
  {"g", "--."},
  {"h", "...."},
  {"i", ".."},
  {"j", ".---"},
  {"k", "-.-"},
  {"l", ".-.."},
  {"m", "--"},
  {"n", "-."},
  {"o", "---"},
  {"p", ".--."},
  {"q", "--.-"},
  {"r", ".-."},
  {"s", "..."},
  {"t", "-"},
  {"u", "..-"},
  {"v", "...-"},
  {"w", ".--"},
  {"x", "-..-"},
  {"y", "-.--"},
  {"z", "--.."},
  {"0", "-----"},
  {"1", ".--."},
  {"2", "..-.."},
  {"3", "...-."},
  {"4", "....-"},
  {"5", "....."},
  {"6", "-...."},
  {"7", "--.."},
  {"8", "-...."},
  {"9", "-..-"}
};
//-------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  //establishes the connection to the main bus, and establishes a serial connection between the Arduino and the computer
  Wire.begin();
  Serial.begin(9600);
}
//-------------------------------------------------------------------------------------------------------------------------------
void loop()
{

  //goes through each letter of the message
  for (int i = 0; i < (message_len - 1); i++)
  {

    //goes through the letter array to find the matching letter
    for (int j = 0; j < 36; j++)
    {

      found_alphanumeric = 0;

      //if the correct letter is found, sends the morse code equivalent of that letter to the SendToSlave function, and declares that it found the letter, and breaks the loop
      if (message_normal[i] == Letters[j][0][0])
      {

        strcat(message_morse, Letters[j][1]);
        //SendToSlave(Letters[j][1]);
        found_alphanumeric = 1;
        break;
      }
    }

    //if the letter examined is not found in the alphanumeric array, it is sent as a *
    if (found_alphanumeric == 0)
    {
      if (message_normal[i] == " ")
      {
        strcat(message_morse, "#");
      }

      else
      {
        strcat(message_morse, "*");
        //SendToSlave("*");
      }
    }

    //places a # after each letter's morse code equivalent
    strcat(message_morse, " ");
    //SendToSlave("#");
  }

  //sends the final string, and puts in infinite loop
  SendToSlave(strcat(message_morse," "));

  //int finish = 1;
  //while (finish == 1);
}
//-------------------------------------------------------------------------------------------------------------------------------
void SendToSlave(char ToSend[])
{
  Wire.beginTransmission(0x08);
  Wire.write(ToSend);
  Wire.endTransmission();
  Serial.println(ToSend);
}
