//This program was written by Alexander Liman and modified by Daniel Romila
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <LiquidCrystal.h>
#include <RDSParser.h>
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// RS,E,D4,D5,D6,D7
 byte a1[8]={0b00000,0b11011,0b11011,0b11011,0b11011,0b11011,0b11011,0b00000};
#define FIX_BAND    RADIO_BAND_FM   
 
RDA5807M radio; 
RADIO_INFO info;
RDSParser rds;
char s[12];
int menu,k,f_scan[50],f=9290,i1=8800;
int var, af, fo;
byte vol,z,w,start,start1,t;
unsigned long time;
void DisplayServiceName(char *name){lcd.setCursor(0,1);lcd.print("    ");lcd.print(name);lcd.print("           ");} 
void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {rds.processData(block1, block2, block3, block4);}

 
void setup() {  
vol=2;
var=0;
af=0;
fo=0;
for(int c=0;c<50;c++)
  {f_scan[c]=0;}
  start=0;
  lcd.begin(16, 2);
  Serial.begin(9600);
  radio.init();
  radio.debugEnable();
  pinMode(8,INPUT);// menu
  pinMode(7,INPUT);// plus
  pinMode(6,INPUT);// minus
  lcd.createChar(0,a1);
  radio.setBandFrequency(FIX_BAND, f);
  radio.setVolume(vol);
  radio.setMono(false);
  radio.setMute(false);
  radio.attachReceiveRDS(RDS_process);
  rds.attachServicenNameCallback(DisplayServiceName);
delay(400);
} 
 
void loop () { 
  radio.formatFrequency(s, sizeof(s));
 
  if(start==0){radio.setBandFrequency(FIX_BAND, f);delay(400);radio.getRadioInfo(&info); start=1;}
  if(digitalRead(8)==HIGH){menu++;lcd.clear();time=millis();radio.getRadioInfo(&info);start=0;w=1;delay(300);if(menu>5){menu=0;}}
 
   if(menu==0) // volume
   {

   if(digitalRead(7)==HIGH){vol++;if(vol>15){vol=15;}w=1;time=millis();radio.setVolume(vol);delay(200);lcd.clear();}
   if(digitalRead(6)==HIGH){vol--;if(vol>16){vol=0;}w=1;time=millis();radio.setVolume(vol);delay(200);lcd.clear();}
    lcd.setCursor(0,0);lcd.print(s); radio.getRadioInfo(&info); lcd.print(info.tuned  ? " t"  : " -"); lcd.print(info.rssi);
        if(fo==0)
           lcd.print(info.stereo ? "S" : "M");
        else
           lcd.print("M"); 

        if(var==0)
           lcd.print("n");
        else
           lcd.print("b"); 
    
    lcd.setCursor(0,1);
  if(millis()-time<3000){for(z=0;z<=vol;z++){lcd.setCursor(z,1);lcd.write((uint8_t)0);}}
 
  if(millis()-time>3000){radio.checkRDS();}  // RDS
   }

   
 
   if(menu==1) //access of memorized stations
   {
    
    if(af==0)
     { 
       lcd.setCursor(0,0);lcd.print("Push UP or DOWN ");
       lcd.setCursor(0,1);lcd.print("to access memory");
     }
    
    
    if(start1==0){f=f_scan[k];start=0;start1=1;}

    if(digitalRead(7)==HIGH){k++;if(k>49){k=0;}delay(200);f=f_scan[k];w=1;time=millis();start=0;lcd.clear();
      lcd.setCursor(0,0);lcd.print("M");lcd.print(k+1);af=1;}
    if(digitalRead(6)==HIGH){k--;if(k<0){k=49;}delay(200);f=f_scan[k];w=1;time=millis();start=0;lcd.clear();
      lcd.setCursor(0,0);lcd.print("M");lcd.print(k+1);af=2;}
    if(f_scan[k]!=0){lcd.print(" ");lcd.print((float)f_scan[k]/100);lcd.print(" MHz   ");}else{lcd.print(" N/A            ");}
      radio.getRadioInfo(&info);
      if(af>0)
      {
      lcd.setCursor(0,1);lcd.print(info.tuned  ? "TUNED"  : "-----");
      lcd.print("  SIGNAL ");lcd.print(info.rssi);
      }
   }   
 
    if(millis()-time>5000 and menu==1){menu=0;time=millis();lcd.clear();}
    
    
    
    
    if(menu==2)// auto scan for stations
    {
      lcd.setCursor(0,0);lcd.print("AUTOSCAN if you");
      lcd.setCursor(0,1);lcd.print("push UP or DOWN");  
    if(digitalRead(7)==HIGH || digitalRead(6)==HIGH){
    for(int i=0;i<50;i++){
    for(i1;i1<=10800;i1=i1+10){
      radio.setBandFrequency(FIX_BAND, i1);delay(300);
      radio.getRadioInfo(&info);delay(500);
    if(info.tuned==1 and info.rssi>20){f_scan[i]=i1;i1=f_scan[i]+10;if(i1>=10800){f_scan[i]=0;}break;} 
      lcd.setCursor(0,0); lcd.print("AUTOSCAN"); lcd.setCursor(9,0); lcd.print((float)i1/100);
  }
 lcd.clear(); lcd.print("AUTOSCAN"); lcd.setCursor(9,0); lcd.print((float)i1/100);
 lcd.setCursor(0,1);lcd.print(i+1);lcd.print(" ");lcd.print((float)f_scan[i]/100);lcd.print(" MHz   "); 
  }delay(1000);time=millis();i1=8800;

  k=0;start1=0;menu=1;}}   
 
 if(millis()-time>5000 and menu==2){menu=0;time=millis();lcd.clear();}
 
  if(menu==3)// manual adjustment of frequencies
  {
      
      radio.getRadioInfo(&info);
      if(f<8800){f=8800;}; if(f>10800){f=10800;}
      
      lcd.setCursor(0,1);lcd.print(info.tuned  ? "TUNED"  : "-----");
      lcd.print("  SIGNAL ");lcd.print(info.rssi);
      
      if(digitalRead(7)==HIGH)
          {start=0;
          f=f+10;t=1;
          if(f>10800){f=8800;}
          time=millis();
          delay(300);
          
                if(digitalRead(7)==HIGH)
                    {start=0;
                     f=f+90;t=1;
                     if(f>10800){f=10800;}
                     time=millis();
                     delay(300);
                    }
          lcd.setCursor(0,0);lcd.print("manual ");lcd.print((float)f/100);lcd.print("MHz");
          }
    
    if(digitalRead(6)==HIGH)
          {start=0;
          f=f-10;t=1;
          if(f<8800){f=8800;}
          time=millis();
          delay(300);
 
                if(digitalRead(6)==HIGH)
                    {start=0;
                     f=f-90;t=1;
                     if(f<8800){f=8800;}
                     time=millis();
                     delay(300);
                    }
          lcd.setCursor(0,0);lcd.print("manual ");lcd.print((float)f/100);lcd.print("MHz");
       
          }
    
     lcd.setCursor(0,0);lcd.print("manual ");lcd.print((float)f/100);lcd.print("MHz");
    
  }
 
 if(millis()-time>5000 and menu==3){menu=0;time=millis();lcd.clear();}



   if(menu==4)// bass boost
   {
    lcd.setCursor(0,0);lcd.print("Bass Boost");
    lcd.setCursor(0,1); 
    if(var==0)lcd.print("           OFF");
    if(var==1)lcd.print("           ON ");
       if(digitalRead(7)==HIGH) 
           {
           radio.setBassBoost(true);
           var=1; 
           lcd.setCursor(0,1);
           lcd.print("           ON ");
           }
       if(digitalRead(6)==HIGH)
           { 
           radio.setBassBoost(false);
           var=0;
           lcd.setCursor(0,1);
           lcd.print("           OFF");
           }
   } 
   
if(millis()-time>5000 and menu==4){menu=0;time=millis();lcd.clear();}

    if(menu==5)// force mono
   {       
    lcd.setCursor(0,0);lcd.print("Force MONO");
    lcd.setCursor(0,1); 
    if(fo==1)lcd.print("           ON ");
    if(fo==0)lcd.print("           OFF");
       if(digitalRead(7)==HIGH) 
           {
           time=millis(); radio.setMono(true); delay(200);
           fo=1; 
           lcd.setCursor(0,1);
           lcd.print("           ON ");
           }
       if(digitalRead(6)==HIGH)
           { 
           time=millis(); radio.setMono(false); delay(200);
           fo=0;
           lcd.setCursor(0,1);
           lcd.print("           OFF");
           }
   } 
   
if(millis()-time>5000 and menu==5){lcd.clear(); menu=0; time=millis();}
 
} // LOOP
