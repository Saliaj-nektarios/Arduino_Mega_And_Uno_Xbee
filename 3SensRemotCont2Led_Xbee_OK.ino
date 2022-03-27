// defines side variables
int analogMSB1 = 0;
int analogLSB1 = 0;
int Val_SoilHygro = 0;

int analogMSB2 = 0;
int analogLSB2 = 0;
int Val_InLdr = 0;

int analogMSB3 = 0;
int analogLSB3 = 0;
int Val_Mq07Gas = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("."));
  Serial.println(F(".."));
  Serial.println(F("..."));
  Serial.println(F("...."));
  Serial.println(F("....."));
  Serial.println(F("start"));
}
void loop() {
  Read_RemoteXbee_Loop();
  Print_Serial_loop();
}   

void Read_RemoteXbee_Loop() {
  //checks for Xbee
  if (Serial.available() >= 29) { // ean einai to frame me 29 bits
    if (Serial.read() == 0x7E) { // ean to frame ksekina me to 7E
      for (int i = 1; i < 21; i++) {
        byte discardbyte = Serial.read();
      }
      //Read Soil hygro
      analogMSB1 = Serial.read();
      analogLSB1 = Serial.read();
      Val_SoilHygro = analogLSB1 + (analogMSB1 * 256);
      Val_SoilHygro =   map(Val_SoilHygro, 0, 1030, 100, 0);
      
      //Read LDR SENSOR
      analogMSB2 = Serial.read();
      analogLSB2 = Serial.read();
      Val_InLdr = analogLSB2 + (analogMSB2 * 256);
      Val_InLdr =   map(Val_InLdr, 0, 1030, 0, 100);
      
      //Read Gas Sensor Mq07
      analogMSB3 = Serial.read();
      analogLSB3 = Serial.read();
      Val_Mq07Gas = analogLSB3 + (analogMSB3 * 256);
      Val_Mq07Gas =   map(Val_Mq07Gas, 0, 1030, 0, 100);
    }
  }
}
void testcontrol(){
  if (Val_SoilHygro > 650 ){
    setRemBlue_Hygro_DIO11(0x5);Serial.println(F("Led Blue on_Dont have Water"));
  }
  else {
    setRemBlue_Hygro_DIO11(0x4);Serial.println(F("Led Blue off_He have Water")); 
  } 
  if (Val_InLdr < 400 ){
    setRemYellow_Mov_Ldr_DIO12(0x5);Serial.println(F("Led Green ON_Den exei Fws")); 
  }
  else {
    setRemYellow_Mov_Ldr_DIO12(0x4);  Serial.println(F("Led Green OFF_Exei fws")); 
  }  
  if (Val_Mq07Gas > 800 ){
    setRemRed_Org_GasMq07_DIO4(0x5); Serial.println(F("Led Red on_DANGER GAS")); 
  }
  else {
    setRemRed_Org_GasMq07_DIO4(0x4);Serial.println(F("Led Red Off_Mq07 it is OK")); 
  } 
}
void Print_Serial_loop() {
  Serial.println(F("================================="));
  Serial.print(F("Value of SoilHygro sensor is: ")); Serial.println(Val_SoilHygro);
  Serial.println(F("****************************"));
  Serial.print(F("ValLdr is: ")); Serial.println(Val_InLdr);
  Serial.println(F("****************************"));
  Serial.print(F("Value of gas Mq07 is: ")); Serial.println(Val_Mq07Gas);
  Serial.println(F("================================="));
}  

void setRemRed_Org_GasMq07_DIO4(char value){
  Serial.write(0x7E);
  Serial.write(byte(0x0));
  Serial.write(0x10);
  Serial.write(0x17);
  Serial.write(byte(0x0));
          
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFE);
          
  Serial.write(0x02);
  Serial.write('D');
  Serial.write('4');
  Serial.write(value);
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'D' + '4' + value;
  Serial.write(0xFF - (sum & 0xFF));
}
void setRemBlue_Hygro_DIO11(char value){
  Serial.write(0x7E);
  Serial.write(byte(0x0));
  Serial.write(0x10);
  Serial.write(0x17);
  Serial.write(byte(0x0));
          
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFE);
  
  Serial.write(0x02);
  Serial.write('P');
  Serial.write('1');
  Serial.write(value);
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'P' + '1' + value;
  Serial.write(0xFF - (sum & 0xFF));
}
void setRemYellow_Mov_Ldr_DIO12(char value){
  Serial.write(0x7E);
  Serial.write(byte(0x0));
  Serial.write(0x10);
  Serial.write(0x17);
  Serial.write(byte(0x0));
        
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFE);
          
  Serial.write(0x02);
  Serial.write('P');
  Serial.write('2');
  Serial.write(value);
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'P' + '2' + value;
  Serial.write(0xFF - (sum & 0xFF));
}      
