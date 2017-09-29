#include "LedControl.h"
byte Code[4][50] = {{
B00000011,B00000001,B00000010,// Setze Led VN1 VN2 auf true
B00000100,B01111111,          //Warte 1280ms
B01000001,B00010000,B00000001,//Setze Variable B00010000 auf B00000001
B01000010,B00000001,B00010000,B00000001,//addiere 1 und 10000 zu
B01000010,B00000010,B00010000,B00000010,
B00000010 //Restart current Codeblock
  }};
byte Variablen[255];
  
int CodeBlock = 0;
int CodeLine = 0;

LedControl lc=LedControl(12,11,10,1);
unsigned long delaytime1=500;
unsigned long delaytime2=50;
void setup() {
  Serial.begin(9600);
 lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

}
//GeneralCommands
//00000001 prints next Byte to Serial and goes 2 Bytes further
//00000010 restarts executing the Codeblock at line 0
//00000011 sets an Led (xy(Variablen) in next lines) to true;
//00000100 Waits for nextline Miliseconds*10
//00000101 Jump to Codeline written in next Line + Line+2 so to bytes

//SpeicherOperationen
//01000001 setzt byte[Nächsterzeile] = Inhalt von übernächster
//01000010 Addiert Variale[nächsterZeile] mit Variable[übernächsterzeile] und speichert dass Ergebniss in Variable[Zeile+3]
//01000011 Variale[nächsterZeile] - Variable[übernächsterzeile] und speichert dass Ergebniss in Variable[Zeile+3]
//01000100 Variale[nächsterZeile] / Variable[übernächsterzeile] und speichert dass Ergebniss in Variable[Zeile+3]
//01000101 Variale[nächsterZeile] * Variable[übernächsterzeile] und speichert dass Ergebniss in Variable[Zeile+3]
void ExecuteCommand(){
if(Code[CodeBlock][CodeLine]<=B10000000){
  if(Code[CodeBlock][CodeLine]<=B01000000){
    
  if(Code[CodeBlock][CodeLine]==B00000001){
Serial.println(Code[CodeBlock][CodeLine+1]);
CodeLine+=2;
return;
  }
    if(Code[CodeBlock][CodeLine]==B00000010){
CodeLine=0;
return;
  }
      if(Code[CodeBlock][CodeLine]==B00000011){
lc.setLed(0,Variablen[Code[CodeBlock][CodeLine+1]],Variablen[Code[CodeBlock][CodeLine+2]],true);
CodeLine+=3;
return;
  }
       if(Code[CodeBlock][CodeLine]==B00000100){
delay(Code[CodeBlock][CodeLine+1]*10);
CodeLine+=2;
return;
  }
         if(Code[CodeBlock][CodeLine]==B00000101){


union TwoBytesInt {
unsigned char fd[2];
float GG;
unsigned int AD; 
}NUM;


          
NUM.AD=0;
NUM.fd[0]=Code[CodeBlock][CodeLine+1];
NUM.fd[1]=Code[CodeBlock][CodeLine+2];
CodeLine = NUM.AD;
return;
  }
  }else{
      if(Code[CodeBlock][CodeLine]==B01000001){
Variablen[Code[CodeBlock][CodeLine+1]]=Code[CodeBlock][CodeLine+2];
CodeLine+=3;
return;
  }
       if(Code[CodeBlock][CodeLine]==B01000010){
Variablen[Code[CodeBlock][CodeLine+3]]=Variablen[Code[CodeBlock][CodeLine+1]]+Variablen[Code[CodeBlock][CodeLine+2]];
CodeLine+=4;
return;
  } 
         if(Code[CodeBlock][CodeLine]==B01000011){
Variablen[Code[CodeBlock][CodeLine+3]]=Variablen[Code[CodeBlock][CodeLine+1]]-Variablen[Code[CodeBlock][CodeLine+2]];
CodeLine+=4;
return;
  } 
           if(Code[CodeBlock][CodeLine]==B01000100){
Variablen[Code[CodeBlock][CodeLine+3]]=Variablen[Code[CodeBlock][CodeLine+1]]/Variablen[Code[CodeBlock][CodeLine+2]];
CodeLine+=4;
return;
  } 
             if(Code[CodeBlock][CodeLine]==B01000101){
Variablen[Code[CodeBlock][CodeLine+3]]=Variablen[Code[CodeBlock][CodeLine+1]]*Variablen[Code[CodeBlock][CodeLine+2]];
CodeLine+=4;
return;
  } 
  }
}
if(Code[CodeBlock][CodeLine]>=B10000000){
if(Code[CodeBlock][CodeLine]>=B11000000){

}
else{
  
}
}
}
void loop() {
  ExecuteCommand();
}
