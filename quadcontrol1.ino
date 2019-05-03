#include<Wire.h>
#include <MPU6050.h>

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float ax, ay, az, wx, wy, wz;
float roll=0, pitch=0, yaw=0;
float t,r,p,y;
float m1,m2,m3,m4;
unsigned long timer = 0;
float timestep=0.9;
float height;
float kp1,ky1,kr1;
float crit_thrust;
float ref_h;
float trust;  //put some initial rpm thrust value here


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
  timer = millis();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read(); 
  Tmp=Wire.read()<<8|Wire.read(); 
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  ax=AcX*9.81/16384;
  ay=AcY*9.81/16384;
  az=AcZ*9.81/16384;
  wx=GyX/131;
  wy=GyY/131;
  wz=GyZ/131;

  // m1:front right, m2: front left, m3: back right, m4: back left;

  //t=(m1+m2+m3+m4)/4;
  //p=(m1+m2-m3-m4)/4;
  //y=(m1-m2-m3+m4)/4;
  //r=(m1-m2+m3-m4)/4;

  
  
  //following three are from sensors
  roll = roll + timestep*wx;
  pitch = pitch + timestep*wy;
  yaw = yaw + timestep*wz;

  


  //here we are decreasing values
  y=yaw-ky1*(yaw-0);
  p=pitch-kp1*(pitch-0);
  r=roll-kr1*(roll-0);



  t=crit_thrust-kt1*(h-ref_h); 
  
  //these are motor values
  m1= t+y+p+r;
  m2= t-y+p-r;
  m3= t-y-p+r;
  m4= t+y-p-r;

  



  

  
  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(roll);
  Serial.print(" | Y = "); Serial.print(pitch);
  Serial.print(" | Z = "); Serial.println(yaw); 

  //Serial.print("Temp = "); Serial.print(Tmp/350+36);
  
 /* Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(wx);
  Serial.print(" | Y = "); Serial.print(wy);
  Serial.print(" | Z = "); Serial.println(wz);
  Serial.println(" ");
  */
  //delay(300);
  delay((timestep*1000) - (millis() - timer));  //i think some problem is here
}
