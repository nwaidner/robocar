#include "IRremote.h"                            
#include <Wire.h>                                          
#include <LiquidCrystal_I2C.h>                                
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


int receiver = 9;                                                                      
int  Ultratrigger=11;                               
int  Ultraecho=10;
long Ultradauer=0; 
long Ultraentfernung=0;
int  motorLV=5;                                      
int  motorLR=6;                                 
int  motorRR=7;                      
int  motorRV=8;                              
int  LED=12;                                                                                
boolean ein=false;
int programm=0;
                                    
IRrecv irrecv(receiver);    
decode_results results;    


void setup()
{ 
  lcd.begin(16,2);                                  
  
  irrecv.enableIRIn();                

  pinMode(Ultratrigger  , OUTPUT);  
  pinMode(Ultraecho     , INPUT);                
  pinMode(LED           , OUTPUT);                   
  pinMode(motorLV       , OUTPUT);                  
  pinMode(motorLR       , OUTPUT);                    
  pinMode(motorRV       , OUTPUT);                      
  pinMode(motorRR       , OUTPUT);    

  startanimation();         

}


void loop()
{                                                   
  if (irrecv.decode(&results)) 
  {
    translateIR(); 
    irrecv.resume();
  }  
  if (programm==1){autonomlinks();};
  if (programm==3){autonomrechts();};
}                                                     



void translateIR() 
{
switch(results.value)
  {
  case 0xFF629D: if (programm==2){                vorwaerts();        break;}
  case 0xFF22DD: if (programm==2){                drehunglinkscon();  break;}
  case 0xFF02FD: if (programm==2){                anhalten();         break;}
  case 0xFFC23D: if (programm==2){                drehungrechtscon(); break;}
  case 0xFFA857: if (programm==2){                rueckwaerts();      break;}
  case 0xFF52AD:                                  raute();  break;                  
  case 0xFF42BD: if (ein==true){                  stern();}  break;                        
  case 0xFF6897: if (ein==true){                  eins();}   break;                  
  case 0xFF9867: if (ein==true){                  zwei();}  break;                  
  case 0xFFB04F: if (ein==true){                  drei();;}  break;                         
  } 

}


void vorwaerts()
{
  digitalWrite(motorLV, HIGH);                     
  digitalWrite(motorRV, HIGH);                          
  digitalWrite(motorRR, LOW);
  digitalWrite(motorLR, LOW);
} 


void rueckwaerts()
{
  digitalWrite(motorLV, LOW);                        
  digitalWrite(motorRV, LOW);                           
  digitalWrite(motorRR, HIGH);
  digitalWrite(motorLR, HIGH); 
} 


void drehungrechts()
{
  digitalWrite(motorRV, LOW);
  digitalWrite(motorLR, LOW);
  digitalWrite(motorLV, HIGH);                
  digitalWrite(motorRR, HIGH);                       
  delay(650);  
  anhalten();   
}  

void drehungrechtscon()
{
  digitalWrite(motorRV, LOW);
  digitalWrite(motorLR, LOW);
  digitalWrite(motorLV, HIGH);                
  digitalWrite(motorRR, HIGH);                        
}  

void drehunglinks()
{
   digitalWrite(motorLV, LOW);                  
   digitalWrite(motorRR, LOW);
   digitalWrite(motorRV, HIGH);                 
   digitalWrite(motorLR, HIGH);                       
   delay(650);  
   anhalten(); 
} 

void drehunglinkscon()
{
   digitalWrite(motorLV, LOW);                  
   digitalWrite(motorRR, LOW);
   digitalWrite(motorRV, HIGH);                 
   digitalWrite(motorLR, HIGH);                        
} 

void anhalten()
{
  digitalWrite(motorLV, LOW);                          
  digitalWrite(motorRV, LOW);                 
  digitalWrite(motorRR, LOW);
  digitalWrite(motorLR, LOW); 
}


void autonomlinks()
{      
digitalWrite(Ultratrigger, LOW);                       
delay(5);                                                
digitalWrite(Ultratrigger, HIGH);                   
delay(10);                                            
digitalWrite(Ultratrigger, LOW);                     
Ultradauer = pulseIn(Ultraecho, HIGH);                  
Ultraentfernung = (Ultradauer/2) / 29.1; 
if (Ultraentfernung >= 21)
{                                                    
vorwaerts();
}

if (Ultraentfernung <= 20 && Ultraentfernung >=1)
{
drehunglinks();
}
} 


void autonomrechts()
{      
digitalWrite(Ultratrigger, LOW);                       
delay(5);                                                
digitalWrite(Ultratrigger, HIGH);                   
delay(10);                                            
digitalWrite(Ultratrigger, LOW);                     
Ultradauer = pulseIn(Ultraecho, HIGH);                  
Ultraentfernung = (Ultradauer/2) / 29.1; 
if (Ultraentfernung >= 21)
{                                                    
vorwaerts();
}

if (Ultraentfernung <= 20 && Ultraentfernung >=1)
{
drehungrechts();
}
} 

void stern()
{
  lcd.clear();            
  programm=0;
  schlussanimation();
}


void raute()
{ 
  lcd.clear();   
  programm=0;   
  startanimation();                                   
}


void eins()
{ 
  anhalten(); 
  programm=1;
  lcd.clear();
  lcd.setCursor(0,0);                                
  lcd.print("P1 selected");                           
  delay(1000);                                        
  lcd.setCursor(0,1);
  lcd.print("Autonomous left");
  delay(100);  
  lcd.setCursor(0,0);                                
  lcd.print("P1 starts in 3");                           
  delay(1000); 
  lcd.setCursor(0,0);                                
  lcd.print("P1 starts in 2");                           
  delay(1000); 
  lcd.setCursor(0,0);                                
  lcd.print("P1 starts in 1");                           
  delay(1000);                                         
  lcd.setCursor(0,0);                                
  lcd.print("P1 is running   ");                                   
}

void zwei()
{ 
  anhalten(); 
  programm=2;
  lcd.clear();  
  lcd.clear();   
  lcd.setCursor(0,0);                                
  lcd.print("P2 selected");                           
  delay(1000);                                        
  lcd.setCursor(0,1);
  lcd.print("Manual Mode ");                                   
}


void drei()
{ 
  anhalten();
  programm=3; 
  lcd.clear();  
  lcd.setCursor(0,0);                                
  lcd.print("P3 selected");                           
  delay(1000);                                        
  lcd.setCursor(0,1);
  lcd.print("Autonomous right ");
  delay(100);  
  lcd.setCursor(0,0);                                
  lcd.print("P3 starts in 3");                           
  delay(1000); 
  lcd.setCursor(0,0);                                
  lcd.print("P3 starts in 2");                           
  delay(1000); 
  lcd.setCursor(0,0);                                
  lcd.print("P3 starts in 1");                           
  delay(1000);                                         
  lcd.setCursor(0,0);                                
  lcd.print("P3 is running   ");                                               
}



void startanimation()
{ 
  lcd.clear();  
  programm=0;
  lcd.backlight(); 
              
  ein=true;
  digitalWrite(LED, HIGH);                       
  
  lcd.setCursor(0,0);                                 
  lcd.print("    Welcome!");                        
  delay(1000);                                       
  lcd.setCursor(0,1);
  lcd.print("               P");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("              Pl");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("             Ple");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("            Plea");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("           Pleas");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("          Please");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("         Please ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("        Please w");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("       Please wa");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("      Please wai");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("     Please wait");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("    Please wait ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("   Please wait  ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("  Please wait   ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print(" Please wait    ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("Please wait     ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("lease wait      ");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("ease wait       ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ase wait        ");
  delay(100);  
  
  lcd.setCursor(0,1);
  lcd.print("se wait         ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("e wait          ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print(" wait           ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("wait            ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ait             ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("it              ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("t               ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(100);  

  lcd.setCursor(0,0); 
  lcd.print("Ready for Input ");
  lcd.setCursor(0,1);
  lcd.print("  Select Mode");

} 



void schlussanimation()
{

  lcd.clear();        
  programm=0;
  
  lcd.setCursor(0,0);              
  lcd.print("NWRobotInterface");    
  delay(1000);                     
  lcd.setCursor(0,1);
  lcd.print("               P");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("              Pl");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("             Ple");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("            Plea");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("           Pleas");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("          Please");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("         Please ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("        Please w");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("       Please wa");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("      Please wai");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("     Please wait");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("    Please wait ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("   Please wait  ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("  Please wait   ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print(" Please wait    ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("Please wait     ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("lease wait      ");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("ease wait       ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ase wait        ");
  delay(100);  
  
  lcd.setCursor(0,1);
  lcd.print("se wait         ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("e wait          ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print(" wait           ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("wait            ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ait             ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("it              ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("t               ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(100);  

  lcd.setCursor(0,0); 
  lcd.print("by Nick Waidner ");
  lcd.setCursor(0,1);
  lcd.print("               P");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("              Pl");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("             Ple");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("            Plea");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("           Pleas");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("          Please");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("         Please ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("        Please w");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("       Please wa");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("      Please wai");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("     Please wait");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("    Please wait ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("   Please wait  ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("  Please wait   ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print(" Please wait    ");
  delay(100);

  lcd.setCursor(0,1);
  lcd.print("Please wait     ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("lease wait      ");
  delay(100); 

  lcd.setCursor(0,1);
  lcd.print("ease wait       ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ase wait        ");
  delay(100);  
  
  lcd.setCursor(0,1);
  lcd.print("se wait         ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("e wait          ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print(" wait           ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("wait            ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("ait             ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("it              ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("t               ");
  delay(100);  

  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(100);  

  lcd.clear();
  
  lcd.noBacklight();                              
  ein=false;
  digitalWrite(LED, LOW);                                                    

}
