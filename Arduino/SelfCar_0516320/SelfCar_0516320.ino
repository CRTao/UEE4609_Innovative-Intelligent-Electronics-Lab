const int motorIn1 = 5;
const int motorIn2 = 6;
const int motorIn3 = 9;
const int motorIn4 = 11;
const int IRL = A2;
const int IRR = A0;
int ld, rd,k=1;

void setup()
{
  Serial.begin(9600);
  pinMode(IRL, INPUT);
  pinMode(IRR, INPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
}

void loop()
{
  ld = analogRead(IRL);
  rd = analogRead(IRR);
  selfTest();
  
  if ((rd >= 700) && (ld >= 700))
  {
    forward();
    //delay(50);
  }
  else if ((rd <= 700) && (ld >= 700))
  {
    turnleft();
    k=1;
    //delay(100);
  }
  else if ((rd >= 700) && (ld <= 700))
  {
    k=0;
    turnright();
    
    //delay(100);
  }
  else if((rd <= 700) && (ld <= 700))
  {   backward();
      delay(500);
      if(k==1)turnright();
      else if (k==0)turnleft();
      delay(500);
      //delay(100);
  }
  else{}

}


void selfTest()
{
  Serial.print("L:");
  Serial.println(ld);
  Serial.print("R:");
  Serial.println(rd) ;

}

void forward(void)
{ analogWrite(motorIn1, 58);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, 55);
  analogWrite(motorIn4, 0);
}

void backward(void)
{ analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 45);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 45  );
}

void turnright(void)//decelares the turnright() void
{ analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 55);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 30);
}

void turnleft(void)//decelares the turnleft() void
{ analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 30);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 55);
}



