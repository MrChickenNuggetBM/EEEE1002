#include <Wire.h>

//defines the alphanumeric letters and their morse equivalent
char alphanumeric[36][2][6] =
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
  //Starts the link to the I2C communication and the link to the computer via the serial
  Wire.begin(0x08);
  Wire.onReceive(received);
  Serial.begin(9600);
}
//-------------------------------------------------------------------------------------------------------------------------------
void loop()
{

}
//-------------------------------------------------------------------------------------------------------------------------------
void received()
{

  String newMessage;

  while (Wire.available())
  {
    char Read = Wire.read();
    newMessage += Read;
  }

  //defines the morse message, its length
  char message_morse[newMessage.length() + 1];
  newMessage.toCharArray(message_morse, newMessage.length() + 1);
  int message_length = sizeof(message_morse) / sizeof(char);



  //defines the first letter of the first morse's position
  int start_morse = 0;

  //finds the spaces in the morse code, and splits the morse into it's components as a result
  for (int i = 0; i < message_length; i++)
  {
    char morse_element[10] = "";
    if (message_morse[i] == ' ')
    {

      strncpy(morse_element, &message_morse[start_morse], i - start_morse);

      //Serial.print(morse_element);
      start_morse = i + 1;

      if (strcmp("*", morse_element) == 0)
      {
        Serial.print(" ");
      }
      else
      {
        for (int j = 0; j < 36; j++)
        {

          //finds the morse code's equivalent letter
          if (strcmp(alphanumeric[j][1], morse_element) == 0)
          {
            Serial.print(alphanumeric[j][0]);
          }
        }
      }
    }
  }
  Serial.println("");
}
