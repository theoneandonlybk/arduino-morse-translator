#include <stdio.h>
#include <string.h>
#include <ctype.h>

char acceptableCharacters[37] = {
'0',
'1',
'2',
'3',
'4',
'5',
'6',
'7',
'8',
'9',
'a',
'b',
'c',
'd',
'e',
'f',
'g',
'h',
'i',
'j',
'k',
'l',
'm',
'n',
'o',
'p',
'q',
'r',
's',
't',
'u',
'v',
'w',
'x',
'y',
'z',
' '
};

char morse_characters[37][8] = {
{'-','-','-','-','-','$'},
{'.','-','-','-','-','$'},
{'.','.','-','-','-','$'},
{'.','.','.','-','-','$'},
{'.','.','.','.','-','$'},
{'.','.','.','.','.','$'},
{'-','.','.','.','.','$'},
{'-','-','.','.','.','$'},
{'-','-','-','.','.','$'},
{'-','-','-','-','.','$'},
{'.','-','$'},
{'-','.','.','.','$'},
{'-','.','-','.','$'},
{'-','.','.','$'},
{'.','$'},
{'.','.','-','.','$'},
{'-','-','.','$'},
{'.','.','.','.','$'},
{'.','.','$'},
{'.','-','-','-','$'},
{'-','.','-','$'},
{'.','-','.','.','$'},
{'-','-','$'},
{'-','.','$'},
{'-','-','-','$'},
{'.','-','-','.','$'},
{'-','-','.','-','$'},
{'.','-','.','$'},
{'.','.','.','$'},
{'-','$'},
{'.','.','-','$'},
{'.','.','.','-','$'},
{'.','-','-','$'},
{'-','.','.','-','$'},
{'-','.','-','-','$'},
{'-','-','.','.','$'},
{' '}
};


void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

int unit = 100;
int current_character;

void loop() {
  // put your main code here, to run repeatedly:
  char message[50] = "I want to ride my bicycle";
  char morse_message[250] = "";

  //Convert to lowercase
  for(current_character = 0; current_character < strlen(message); ++current_character){
    message[current_character] = tolower(message[current_character]);
    //Replace "." with "stop"
    if(message[current_character] == '.'){
      memmove(&message[current_character + 4], &message[current_character + 1], strlen(&message[current_character + 1]) + 1);
      strncpy(&message[current_character], "stop", 4);
    }

    //Convert to morse
    for(int sought_character_index = 0; sought_character_index < sizeof(acceptableCharacters) / sizeof(acceptableCharacters[0]); ++sought_character_index){
      if(message[current_character] == acceptableCharacters[sought_character_index]){
        strcat(morse_message, morse_characters[sought_character_index]);
      }
    }

  }

  Serial.println(morse_message);

  for(current_character = 0; current_character < strlen(morse_message); ++current_character){
    buzz(morse_message[current_character]);
  }

  strcpy(morse_message, "");
  delay(1000);

} //MAIN


/*
dot = 1 unit
dash = 3 units
space between dots and dahses in one LETTER = 1 unit
space between letters = 3 units
space between words = 7 units

For example, A AA (.- .-.-), would be equal to:
B = Beep 1 unit
_ = silent 1 unit
B_BBB_______B_BBB___B_BBB

*/


void buzz(char character){
  switch (character){
    case '.':
      digitalWrite(3, HIGH);
      delay(unit);
      digitalWrite(3, LOW);
      delay(unit);
      break;
    case '-':
      digitalWrite(3, HIGH);
      delay(unit*3);
      digitalWrite(3, LOW);
      delay(unit);
      break;
    case '$':
      delay(unit*2);
      break;
    case ' ':
      delay(unit*6);
      break;
  }
}
