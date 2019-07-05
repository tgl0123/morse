#define dottime 250
#define pin 13
char MORSE[][4] = {
  {'.', '-', '*', '*'}, //A
  {'-', '.', '.', '.'}, //B
  {'-', '.', '-', '.'}, //C
  {'-', '.', '.', '*'}, //D
  {'.', '*', '*', '*'}, //E
  {'.', '.', '-', '.'}, //F
  {'-', '-', '.', '*'}, //G
  {'.', '.', '.', '.'}, //H
  {'.', '.', '*', '*'}, //I
  {'.', '-', '-', '-'}, //J
  {'-', '.', '-', '*'}, //K
  {'.', '-', '.', '.'}, //L
  {'-', '-', '*', '*'}, //M
  {'-', '.', '*', '*'}, //N
  {'-', '-', '-', '*'}, //O
  {'.', '-', '-', '.'}, //P
  {'-', '-', '.', '-'}, //Q
  {'.', '-', '.', '*'}, //R
  {'.', '.', '.', '*'}, //S
  {'-', '*', '*', '*'}, //T
  {'.', '.', '-', '*'}, //U
  {'.', '.', '.', '-'}, //V
  {'.', '-', '-', '*'}, //W
  {'-', '.', '.', '-'}, //X
  {'-', '.', '-', '-'}, //Y
  {'-', '-', '.', '.'}  //Z
};

void dot() {
  digitalWrite(pin, HIGH);
  delay(dottime);
  digitalWrite(13, LOW);
  delay(dottime);
}

void dash() {
  digitalWrite(pin, HIGH);
  delay(dottime * 4);
  digitalWrite(13, LOW);
  delay(dottime);
}

void c_space() {
  digitalWrite(pin, LOW);
  delay(dottime * 3);
}

void w_space() {
  digitalWrite(pin, LOW);
  delay(dottime * 7);
}

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  String str = ""; 
  String morse_s = "";  
  int i, t , temp = 0;
  int n = 0;  
  while (Serial.available() > 0)
  {
    temp = 1;  
    str += char(Serial.read());  
    delay(2); 
    n++;
  }

  if (temp)
  {
    for (i = 0; i < n; i++)
    {
      if (str[i] >= 97 && str[i] <= 122)
      {
        for (t = 0; t < 4; t++)
        {
          morse_s += char(MORSE[int(str[i] - 97)][t]);
        }
      }
      if (int(str[i]) != 32) {
        morse_s += '/';
      } else {
        morse_s += ' ';
      }
    }
    Serial.println(morse_s); 
    for (i = 0; morse_s[i] != '\0' ; i++)
    {
      if (morse_s[i] == '.')dot();
      else if (morse_s[i] == '-')dash();
      else if (morse_s[i] == ' ')w_space();
      else if (morse_s[i] == '/')c_space();
    }
    Serial.println("发送完毕");
    delay(2);
  }
}
