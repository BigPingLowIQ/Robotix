// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;

String last_move = "D";

void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Serial.begin(9600);
}

void quarter_rotation_clockwise()
{
  digitalWrite(dirPin, LOW);
  for(int x = 0; x < stepsPerRevolution/4; x++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}

void quarter_rotation_counterclockwise(){
  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < stepsPerRevolution/4; x++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}

void double_rotation(){
  for(int x = 0; x < stepsPerRevolution/2; x++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}

void do_move(String arg){
   //get rotations to get the face to be the down facing one
   //execute the rotations
   //lower the thing that's going to hold the first 2 layers
   if(arg[1] == '\''){
     quarter_rotation_counterclockwise();
   }  
   else if(arg[1] == '2') {
     double_rotation();
   }
   else {
     quarter_rotation_clockwise(); 
   }
}

void loop()
{
  String moves;
  while (Serial.available() == 0)   { }  
  moves = Serial.readString(); 
  String move="";
  for(int i = 0;i<moves.length();i++){
      if(moves[i] !=' '){
        move += moves[i];
      }
      else {
        Serial.println(move);
        do_move(move);
        last_move = move;
        move = "";
      }
  }
  Serial.println(move);
  do_move(move);
  
}
