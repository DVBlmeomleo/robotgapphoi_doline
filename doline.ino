#define il 1
#define ol 0

#define ir_1 2
#define ir_2 3
#define ir_3 4
#define ir_4 5
#define ir_5 6

#define motor_in1 7
#define motor_in2 8
#define motor_in3 9
#define motor_in4 10
#define motor_ena 11
#define motor_enb 12

int speed = 500;
int v1, v2, v3, v4, v5;
int direction = 0;
int turn = 0;
int pre_error;
int P,I,D, kp, ki, kd;

void setup() {
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  pinMode(ir_5, INPUT);

  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);
  pinMode(motor_in3, OUTPUT);
  pinMode(motor_in4, OUTPUT);
  pinMode(motor_ena, OUTPUT);
  pinMode(motor_enb, OUTPUT);
}


//mấy hàm dưới này cứ để đấy đã, sửa sau, nhìn tên hàm ra chức năng để xem logic đã
void dithang(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void dung(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void retrai(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void rephai(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void dilui(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void quaydau(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void dichphai(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}
void dichtrai(){
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, HIGH);
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, HIGH);
  analogWrite(motor_ena, speed);
  analogWrite(motor_enb, speed);
}

void check_ir(){
  v1 = digitalRead(ir_1); //1 la ngoai line, 0 la trong line  (hoac nguoc lai, tuy de)
  v2 = digitalRead(ir_2);
  v3 = digitalRead(ir_3);
  v4 = digitalRead(ir_4);
  v5 = digitalRead(ir_5);
}

int turn_3 = 0, turn_4 = 0, turn_7 = 0, turn_11 = 0, turn_12_a = 0, turn_12_b = 0, turn_13_a = 0, turn_13_b = 0, turn_14 = 0, turn_14_a = 0;
void move_direction(int error){
  switch (turn){
    case 0:
      if (error == 10){
        dithang();
      }else{
        turn++;
      }
      break;
    case 1:
      if (error == 12){
        rephai();
        turn++;
      }else if (error == 13){
        quaydau();
      }else{
        dithang();
      }
      break;
    case 2:
      if (error == 12){
        rephai();
      }else if (error == 13){
        quaydau();
      }else if(v1 == il && v5 == il){
        rephai();
        turn++;
      }else{
        dithang();
      }
      break;
    case 3:
      if (v5 == il){
        if (turn_3 == 0){
          rephai();
          turn_3++;
        }else{
          dithang();
          turn++;
        }
      }else if(error == 13){
        quaydau();
      }else{
        dithang();
      }
      break;
    case 4:
      if (v5 == il){
        turn_4++;
        if (turn_4 == 3){
          rephai();
        }
      }else if(v1 == il){
        retrai();
        turn++;
      }
      break;
    case 5:
      if (error != 13){
        turn++;
      }
      dithang();
      break;
    case 6:
      if (error == 13){
        quaydau();
      }else if(v5 == il){
        rephai();
        turn++;
      }else{
        dithang();
      }
      break;
    case 7:
      if (v5 == il){
        if (turn_7 == 0){
          turn_7++;
        }else{
          turn++;
        }
        rephai();
      }else if (error == 13){
        quaydau();
      }else{
        dithang();
      }
      break;
    case 8:
      if (v5 == il){
        if (v1 == il){
          retrai();
          turn++;
        }else{
          rephai();
        }
      }else if (error == 13){
        quaydau();
      }else{
        dithang();
      }
      break;
    case 9:
      if (v1 == il && v5 == il){
        rephai();
        turn++;
      }
      break;
    case 10:
      if (error != 13){
        turn++;
      }
      dithang();
      break;
    case 11:
      if (v5 == il){
        if (v1 == il){
          retrai();
        }else{
          if (turn_11 == 0){
            turn_11++;
          }else{
            turn++;
          }
          rephai();
        }
      }else{
        dithang();
      }
      break;
    case 12:
      if (v1 == il && v5 == il){
        if (turn_12_a == 0){
          turn_12_a++;
          rephai();
        }else if (turn_12_a == 1){
          turn_12_a++;
          dithang();
        }else{
          rephai();
        }
      }else if(error == 13){
        if (turn_12_b == 0){
          turn_12_b++;
        }else{
          turn++;
        }
        quaydau();
      }else{
        dithang();
      }
      break;
    case 13:
      if (v1 == il){
        if (v5 == il){
          turn_13_a++;
          if (turn_13_a == 3){
            rephai();
          }
        }
        retrai();
      }else if (error == 13){
        if (turn_13_b == 1){
          turn++;
        }
        turn_13_b++;
        quaydau();
      }else{
        dithang();
      }
      break;
    case 14:
      if (v1 == il){
        if (v5 == il){
          if (turn_14 == 0){
            retrai();
            turn_14++;
          }else{
            rephai();
          }
        }else if (v5 == il){
          rephai();
        }else if(error == 13){
          if (turn_14_a == 1){
            turn++;
          }
          turn_14_a++;
          quaydau();
        }else{
          dithang();
        }
      }
      break;
    case 15:
      if (v1 == il && v5 == il){
        rephai();
      }else if(v5 == il){
        rephai();
      }else if(error == 13){
        quaydau(); //done
        turn++;
      }
      break;
  }
}

int error_calc(){
  if (v1 == ol && v2 == ol && v3 == ol && v4 == ol && v5 == il){return -4;}
  else if (v1 == ol && v2 == ol && v3 == ol && v4 == il && v5 == il){return -3;}
  else if (v1 == ol && v2 == ol && v3 == ol && v4 == il && v5 == ol){return -2;}
  else if (v1 == ol && v2 == ol && v3 == il && v4 == il && v5 == ol){return -1;}
  else if (v1 == ol && v2 == ol && v3 == il && v4 == ol && v5 == ol){return 0;}
  else if (v1 == ol && v2 == il && v3 == il && v4 == ol && v5 == ol){return 1;}
  else if (v1 == ol && v2 == il && v3 == ol && v4 == ol && v5 == ol){return 2;}
  else if (v1 == il && v2 == il && v3 == ol && v4 == ol && v5 == ol){return 3;}
  else if (v1 == il && v2 == ol && v3 == ol && v4 == ol && v5 == ol){return 4;}
  else if (v1 == ol && v2 == ol && v3 == ol && v4 == ol && v5 == ol){return 9;}
  else if (v1 == il && v5 == il){return 10;}
  else if (v1 == il && v2 == il && v3 == il && v4 == ol && v5 == ol){return 11;}
  else if (v1 == ol && v2 == ol && v3 == il && v4 == il && v5 == il){return 12;}
  else{return 50;}
}

void loop() {
  check_ir();
  int error = error_calc();
  if (pre_error != error){
    move_direction(error);
  }
  pre_error = error;
  delay(500);
}
