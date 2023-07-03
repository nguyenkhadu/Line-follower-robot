#define ptien 6  // động cơ phải tiến in1
#define plui 7  // động cơ phải lùi in2
#define ttien 8  //động cơ trái tiến in3
#define tlui 9  //động cơ trái lùi in4
#define EA 5  //kích hoạt pin EA động cơ phải
#define EB 10 //kích hoạt pin EB động cơ trái
#define sensor A0
#define sensor_right 12
#define sensor_left 11

// PID Constants
float Kp = 3;
float Ki = 0;
float Kd = 10;

int r=0;
int error = 0, error1=0;
int nguong=0;
int pos = 0;
float P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int initial_motor_speed = 180;
int test,count_left=0,count_right=0,count_r_l=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ptien, OUTPUT);
  pinMode(plui, OUTPUT);
  pinMode(ttien, OUTPUT);
  pinMode(tlui, OUTPUT);
  pinMode(EA, OUTPUT);
  pinMode(EB, OUTPUT);
  pinMode(sensor_right, INPUT);
  pinMode(sensor_left, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
    error1=read_sensor();
  switch(error1){
   case 0:
   {
      
      count_left++;
      if(count_left == 2){
        analogWrite(EA, 80);
        analogWrite(EB, 80);
        error1=read_sensor();
        forward();
        delay(300);
        break;
      }
      if(count_left==5 or count_left==6){
        error1=read_sensor();
        analogWrite(EA, 80);
        analogWrite(EB, 50);
        turnLeft();
        delay(500);
        break;
      }
      else if(count_left==7 or count_left==8  or count_left==9){
        error1=read_sensor();
        analogWrite(EA, 100);
        analogWrite(EB, 100);
        forward();
        delay(300);

        break;
      }
      else if( count_left==10   )
      {
        error1=read_sensor();
        analogWrite(EA, 80);
        analogWrite(EB, 50);
        turnLeft();
        delay(400);
        break;
      }
      else if(count_left == 12){
        analogWrite(EA, 100);
        analogWrite(EB, 100);
        forward();
        delay(300);

        break;
      }
      else if( count_left==13   )
      {
        error1=read_sensor();
        analogWrite(EA, 80);
        analogWrite(EB, 50);
        turnLeft();
        delay(400);
        break;
      }
       else if( count_left==14   )
      {
        error1=read_sensor();
        analogWrite(EA, 50);
        analogWrite(EB, 80);
        turnRight();
        delay(200);
        break;
      }
    
     break;  
  }
//
    case 1:
     {
       count_right++;
      if(count_right==1 )
      {
        analogWrite(EA, 80);
        analogWrite(EB, 100);

        turnLeft();
        delay(200);  
   
         break;

      }
      else if(count_right==2 or count_right==9 )
      {
        analogWrite(EA, 80);
        analogWrite(EB, 100);
        error1=read_sensor();
        turnRight();
        delay(400);
        break;
      }
//      else if(count_right==3 )
//      {
//        
//        analogWrite(EA, 80);
//        analogWrite(EB, 80);
//        error1=read_sensor();
//        forward();
//        delay(800);
//        break;
//      }
       else if(count_right==4)
      {
        analogWrite(EA, 80);
        analogWrite(EB, 80);
        forward();
        delay(200);
        
        analogWrite(EA, 50);
        analogWrite(EB, 80);
        turnLeft();
        delay(500);    
         
        break;
        }
            
     break;
  }

//    case 2://nga 3
//    {
//      count_r_l++;
//      if(count_r_l==1){
//        analogWrite(EA, 80);
//        analogWrite(EB, 80);
//        forward();
//        delay(200);    
//         break;
//
//      }
//      else if(count_r_l==2 or count_r_l==3){
//        analogWrite(EA, 80);
//        analogWrite(EB, 50);
//        turnLeft();
//        delay(500);    
//         break;
//      }
//    }
 
   case 3:
   {
  calculate_pid();
  motor_control();
  break;
  
   }

 }


}
int read_sensor()
{
  int sR = digitalRead(sensor_right);
  int sL = digitalRead(sensor_left);
   if(sR==1 )
    return 1;
   else if(sL==1 )
    return 0;
//   else if(sR==1 and sL==1)//nga 3
//    return 2;
   else if (sR==0 and sL==0) 
    return 3; 
    
    
} 
void calculate_pid()
{
  pos = analogRead(sensor);
  if(pos<10){
    PID_value=0;  
  }
  else{
  error = 500- pos;
  P = error;
  I = error + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
 
  previous_I = I;
  previous_error = error;
  }
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed =  initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 250);
  right_motor_speed = constrain(right_motor_speed, 0,250);

  analogWrite(EB, left_motor_speed); //Left Motor Speed
  analogWrite(EA, right_motor_speed); //Right Motor Speed

  //following lines of code are to make the bot move forward
  forward();
}

void forward()
{
  digitalWrite(ptien, HIGH);
  digitalWrite(plui, LOW);
  digitalWrite(ttien, HIGH);
  digitalWrite(tlui, LOW);
}

void turnRight(){
  digitalWrite(ptien, LOW);
  digitalWrite(plui, HIGH);
  digitalWrite(ttien, HIGH);
  digitalWrite(tlui, LOW);
}

void turnLeft(){
   digitalWrite(ptien, HIGH);
  digitalWrite(plui, LOW);
  digitalWrite(ttien, LOW);
  digitalWrite(tlui, HIGH);
}
void Stop(){
   digitalWrite(ptien, LOW);
  digitalWrite(plui, LOW);
  digitalWrite(ttien, LOW);
  digitalWrite(tlui, LOW);
}
