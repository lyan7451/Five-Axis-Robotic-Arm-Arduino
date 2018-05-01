//專題
//三軸按鍵顛倒

//pos1 = ,pos2 = ,pos3 = ,pos4 = ,pos5 = 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h>
#include  <SoftwareSerial.h>
//藍芽baud rate 改為 57600
//TxD傳送 RxD接收
SoftwareSerial BTSerial(0,1); // RX | TX

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//bluetooth using javascript
int AxisNum = 0;
int AxisAngle = 0;
String readstring;
char StringAry[20];

//setup angle
//第一軸
//角度越大 越往左
int pos1 = 60;

//第二軸
//pos2 & pos3 
//極限角:pos2 = 154.5 pos3 = 25
//pos2 = 9.5 pos3 = 180
int a = -60 ;
float pos2 = 99.5-a;
int pos3 = 90+a;

//第三軸
//90~120 往下
//
int pos4 = 150;

//第四軸
int pos5 = 80;

//第五軸
//最大0 
//範圍35~95
//張開35
//抓起95
int pos6 = 35;



void ServoWrite2(){
  //第二軸
  servo2.write(pos2);
  servo3.write(pos3);
}


void PrintAxis1Angle(){
  //第一軸
  Serial.print("pos1 = ");
  Serial.println(pos1);  
}
void PrintAxis2Angle(){
  //第二軸
  Serial.print("pos2 = ");
  Serial.println(pos2);
  Serial.print("pos3 = ");
  Serial.println(pos3);
}
void PrintAxis3Angle(){
  //第三軸
  Serial.print("pos4 = ");
  Serial.println(pos4);
}
void PrintAxis4Angle(){
  //第四軸
  Serial.print("pos5 = ");
  Serial.println(pos5);
}
void PrintAxis5Angle(){
  //第五軸
  Serial.print("pos6 = ");
  Serial.println(pos6);
}

void reset(){
  pos1 = 60;
  pos2 = 99.5-a;
  pos3 = 90+a;
  pos4 = 150;
  pos5 = 80;
  pos6 = 35;
  
  servo1.write(pos1);
  ServoWrite2();
  servo4.write(pos4);
  servo5.write(pos5);
  servo6.write(pos6);
  
  PrintAxis1Angle();
  PrintAxis2Angle();
  PrintAxis3Angle();
  PrintAxis4Angle();
  PrintAxis5Angle();
  
}

void judge(){
      if(readstring == "l1"){
        //第一軸
        //左 角度增加
        //servo1        
        pos1 += 10;
        servo1.write(pos1);
        
        PrintAxis1Angle();
      }
      else if(readstring == "r1"){
        //第一軸
        //右 角度減少
        //servo1
        pos1 -= 10;
        servo1.write(pos1);
              
        PrintAxis1Angle();
      }
      else if(readstring == "u2"){
        //第二軸
        //上
        //servo2 & servo3
        pos2 += 10;
        pos3 -= 10;
        
        ServoWrite2();
        PrintAxis2Angle();
      }
      else if(readstring == "d2"){
        //第二軸
        //下
        //servo2 & servo3
        pos2 -= 10;
        pos3 += 10;
        ServoWrite2();
        PrintAxis2Angle();
      } 
      else if(readstring == "u3"){
        //第三軸 與其他軸相反
        //上
        //servo4
        pos4 -= 10;
        servo4.write(pos4);
        
        PrintAxis3Angle();
      }
      else if(readstring == "d3"){
        //第三軸 與其他軸相反
        //servo4
        //下
        pos4 += 10;
        servo4.write(pos4);
        
        PrintAxis3Angle();
      }
      else if(readstring == "u4"){
        //第四軸
        //servo5
        //
        pos5 += 10;
        servo5.write(pos5);

        PrintAxis4Angle();
      }
      else if(readstring == "d4"){
        //第四軸
        //servo5
        //
        pos5 -= 10;
        servo5.write(pos5);
        
        PrintAxis4Angle();
      }
      else if(readstring == "G"){
        // servo6
        //第五軸
        pos6 = 75;
        servo6.write(pos6);
        
        
        PrintAxis5Angle();
      }
      else if(readstring == "L"){
        // servo6
        //第五軸
        pos6 = 35;
        
        servo6.write(pos6);
        
        PrintAxis5Angle();
      }
      else if(readstring == "M"){
        //指定動作
        
        
      }
}

void inputangle(){
  //輸入角度 
  //1~4軸適用
  //AxisNum AxisAngle
  if(AxisNum == 1){
    pos1 += AxisAngle;
    servo1.write(pos1);
    PrintAxis1Angle();
  }
  else if(AxisNum == 2){
    pos2 += AxisAngle;
    pos3 -= AxisAngle;
    servo2.write(pos2);
    servo3.write(pos3);
    PrintAxis2Angle();
  }
  else if(AxisNum == 3){
    pos4 += AxisAngle;
    servo4.write(pos4);
    PrintAxis3Angle();
  }
  else if(AxisNum == 4){
    pos5 += AxisAngle;
    servo5.write(pos5);
    PrintAxis4Angle();
  }
  
  
}




void setup() {
  

  //setup servo pin position
   servo1.attach(8);
   servo2.attach(9);
   servo3.attach(10);
   servo4.attach(11);
   servo5.attach(12);
   servo6.attach(13);
   
  //serup servo angle
   servo1.write(pos1);
   servo2.write(pos2);
   servo3.write(pos3);
   servo4.write(pos4);
   servo5.write(pos5);
   servo6.write(pos6);

   
  Serial.begin(9600);
  //定義藍芽Serial
  BTSerial.begin(57600);



  
}



void loop() {
  
  //Read from HC05 and send to Arduino Serial Monitor
  
  if(BTSerial.available() > 0){
    //Read String from Serial Port
    //BTSerial.write(Serial.read());
    
    readstring = BTSerial.readString();
    Serial.print("readstring = ");
    Serial.println(readstring);
    
    //convert string to char array 
      strcpy(StringAry,readstring.c_str());
      
      if(readstring == "l1" || readstring == "r1" || readstring == "u2" || readstring == "d2"|| 
      readstring == "u3" || readstring == "d3" || readstring == "u4" || readstring == "d4" || 
      readstring == "G" || readstring == "L" || readstring == "Ma"){
        Serial.println("A");
        judge();
      }
      else if(readstring == "re"){
        reset();
      }
      else{
        //輸入角度
        //字串分割
        char *pch;
        int cnt = 0;
        pch = strtok(StringAry,"#");
        while(pch != NULL){
                char *temp; 
                if(cnt == 1){
                    temp = pch;
                    AxisAngle = atoi(temp);
                    Serial.print("1 AxisAngle = ");
                    Serial.println(AxisAngle);
                    delay(5);
                    break;
                }
                else if(cnt == 0){
                    temp = pch;
                    AxisNum = atoi(temp);
                    Serial.print("0 AxisNum = ");
                    Serial.println(AxisNum);
                    delay(5);
                }
                pch = strtok(NULL, "#");
                cnt++; 
            }//分割結束
              
              if(cnt != 0){
                inputangle();
              }
        
        
        
      }

        
    }
    
    
  
    
}
