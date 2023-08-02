
#define left 0
#define right !left

#define ligneCapteurLeft 6
#define ligneCapteurRight 2 
#define ligneCapteurMiddle 10

int vitesse =130;
int turningDelay =10;
int turningSpeed =120;

struct Motor{
  int brake,direction_,speed_;
};
struct Motor motor2,motor1;


void setup() {
  Serial.begin(9600);
  initMotor(&motor1,9,12,3);
  initMotor(&motor2,8,13,11);
  pinMode(ligneCapteurRight,INPUT);
  pinMode(ligneCapteurLeft,INPUT);
  pinMode(ligneCapteurMiddle,INPUT);
}
void initMotor(Motor* motor,int br,int dir,int spd){
  //initialiser le moteur
  motor->brake = br;
  motor->direction_= dir;
  motor->speed_ = spd;
  
  pinMode(motor->brake, OUTPUT); 
  pinMode(motor->direction_, OUTPUT);
  pinMode(motor->speed_, OUTPUT);
}

void loop() {
  int leftCap = digitalRead(ligneCapteurLeft);
  int rightCap = digitalRead(ligneCapteurRight);
  int middleCap = !digitalRead(ligneCapteurMiddle);
  
  
  
  if(middleCap){
    avancer(vitesse);
  }else{
    arreter();
    leftCap = !digitalRead(ligneCapteurLeft);
    rightCap = !digitalRead(ligneCapteurRight);
    Serial.print("Left :");
    Serial.print((bool)leftCap);
    Serial.print(",right :");
    Serial.println((bool)rightCap);
    if(leftCap && rightCap){
      int dir = random(0,1) ? right : left;
      tourner(100,dir,turningSpeed);
      while(digitalRead(ligneCapteurMiddle)){}
    }else if(leftCap){
      tourner(100,left,turningSpeed);
      while(digitalRead(ligneCapteurMiddle)){}
    }else{
      tourner(100,right,turningSpeed);
      while(digitalRead(ligneCapteurMiddle)){}
    }
  }
}
void moveBack(int spd){
  //Permettera de reculer le robot
  Serial.println("Moving back");
  digitalWrite(motor1.brake,LOW);
  digitalWrite(motor2.brake,LOW);
  digitalWrite(motor1.direction_,LOW);
  digitalWrite(motor2.direction_,LOW);
  analogWrite(motor1.speed_,spd);
  analogWrite(motor2.speed_,spd);
}
void avancer(int spd){
  //Permettera d'avancer le robot
  digitalWrite(motor1.brake,LOW);
  digitalWrite(motor2.brake,LOW);
  digitalWrite(motor1.direction_,HIGH);
  digitalWrite(motor2.direction_,HIGH);
  analogWrite(motor1.speed_,spd);
  analogWrite(motor2.speed_,spd);
}
void arreter(){
  //Permettera d'arreter le robot
  digitalWrite(motor1.brake,HIGH);
  digitalWrite(motor2.brake,HIGH);
}

void tourner(int duration,int dir,int spd){
  //Permettera de tourner le robot
  digitalWrite(motor1.brake,LOW);
  digitalWrite(motor2.brake,LOW);
  digitalWrite(motor1.direction_,dir?HIGH:LOW);
  digitalWrite(motor2.direction_,!dir?HIGH:LOW);
  analogWrite(motor1.speed_,spd);
  analogWrite(motor2.speed_,spd);
  delay(duration);
}
