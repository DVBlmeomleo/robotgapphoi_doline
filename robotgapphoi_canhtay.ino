#include <Servo.h>
#include <SoftwareSerial.h>

Servo base, arm1, arm2, arm3, grip, junior_grip;
SoftwareSerial blt_data;
int pwm[6] = [1100, 1100, 1100, 1100, 1100, 1100];
int setpoint[10] = [1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100];
bool imu_grip = false;
//xung PWM từ 1100 đến 1900 (0 - 180 độ)
//base và grip thì tự điều khiển
//cần setpoint cho arm
//junior_grip: nếu active thì chỉnh cân bằng theo IMU, ko thì thôi 
float accX, accY, accZ;

void setup() {
  base.attach(base, 3); //xung PWM
  arm1.attach(base, 4);
  arm2.attach(base, 5);
  arm3.attach(base, 6);
  grip.attach(base, 7);
  Serial.begin(9600);
  blt_data.begin(8, 9);

  //IMU MP6050
  Wire.beginTransmission(0x68); //lọc nhiễu hoặc gì đấy ?
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  
  Wire.beginTransmission(0x68); //tra cứu accel
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
}

void loop() {
  char data = get_data();
  //w là nâng cánh tay lên, s là hạ cánh tay xuống
  //a là xoay base sang trái, d là sang phải
  //g là kẹp grip vào, h là dãn ra
  //junior_grip nhận xung từ IMU, còn nếu ko thì gộp vào arm, gửi tín hiệu là 1
  switch (data){
    case '0':
      //nothing
      break;
    case 'w':
      up();
      break;
    case 'd':
      down();
      break;
    case 'a':
      left();
      break;
    case 'd':
      right();
      break;
    case 'g':
      grab();
      break;
    case 'h':
      grab();
      break;
    case '1':
      if (imu_grip == false){
        imu_grip = true;
        move_1();
      }else{
        imu_grip = false;
      }
      break;
  }
}

char get_data(){
  if (blt_data.available() > 0){
    data = blt_data.read();
    return data;
  }
  return '0';
}
//hàm up down left right kệ nó đi :))
void up(){
  int a;
  if (imu_grip == false){
    a = 6;
  }else{
    a = 5
  }
  for (int i = 0; i < a; i++){
    pwm[i]++;
    if (pwm[i] > setpoint[i]){
      pwm[i]--;
    }
  }
}

void up(){
  int a;
  if (imu_grip == false){
    a = 6;
  }else{
    a = 5
  }
  for (int i = 0; i < a; i++){
    pwm[i]++;
    if (pwm[i] > setpoint[i]){
      pwm[i]--;
    }
  }
}
void down(){
  int a;
  if (imu_grip == false){
    a = 6;
  }else{
    a = 5
  }
  for (int i = 0; i < a; i++){
    pwm[i]++;
    if (pwm[i] > setpoint[i]){
      pwm[i]--;
    }
  }
}
void left(){
  pwm[0]++;
  if (pwm[0] > setpoint[6]){
    pwm[0] = setpoint[6];
  }
}
void right(){
  pwm[0]--;
  if (pwm[0] < setpoint[0]){
    pwm[0] = setpoint[0];
  }
}

void grab(){
  if (data == 'g'){
    pwm[5]++;
  }else if (data == 'h'){
    pwm[5]--;
  }
  if (pwm[5] > setpoint[11]){
    pwm[5] = setpoint[11];
  }else if (pwm[5] < setpoint[5]){
    pwm[5] = setpoint[5];
  }
}
void move_1(){
  float roll = get_data_imu();
  if (roll > 7){
    pwm[4]--;
  }else if (roll < -7){
    pwm[4]++;
  }
}

float get_data_imu(){
  Wire.beginTransmission(0x68); //đọc accel
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);

  float fAccX = Wire.read() << 8 | Wire.read();
  float fAccY = Wire.read() << 8 | Wire.read();
  float fAccZ = Wire.read() << 8 | Wire.read();

  accX = fAccX / 4096;
  accY = fAccY / 4096;
  accZ = fAccZ / 4096;

  return atan(accY/sqrt(pow(accX, 2) + pow(accZ, 2)))/(3.142/180);
}