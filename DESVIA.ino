#include <SoftwareSerial.h>    //inclui a biblioteca para fazer a comunicacao serial

#define echopin  7 // echo pin
#define trigpin 8 // Trigger pin
#define echopin_d 9
#define trigpin_d 12

//------------------------------------------------------------------------------


SoftwareSerial BT(10, 11); //TX, RX respectivamente
String readvoice;     //string onde o comando de voz sera armazenado
long duration, distance, distance_d, duration_d;   // variaveis auxiliares para o calculo da distancia pelo HC-SR04 


//--------------------------------------------------------------------------

void delay_milisec(unsigned char seconds)    // funcao delay criada em decimos de sgundo
{
    unsigned char i,j;
 
    for(i=0;i<seconds;i++)
        for(j=0;j<100;j++)
            delay(1);
}



//---------------------------------------------------------------

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode (trigpin_d, OUTPUT);
  pinMode (echopin_d, INPUT );  
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

//------------------------------------------------------------------



void frente(){ 
      digitalWrite (3, HIGH);
      digitalWrite (4, HIGH);
      digitalWrite (5,LOW);
      digitalWrite (6,LOW);
      delay(200);      
}


void volta(){
    digitalWrite (3, LOW);
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    digitalWrite (6, HIGH);
    delay(2000);  
}


void esquerda(){
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1000);
   digitalWrite (3, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(450);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1500);
   digitalWrite (3, HIGH);
   digitalWrite (4, HIGH);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
}



void direita(){
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1000);
   digitalWrite (3, HIGH);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(450);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1500);
   digitalWrite (3, HIGH);
   digitalWrite (4, HIGH);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
}

 
 
void para(){
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(500);
}

void gira_direita(){
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1000);
   digitalWrite (3, HIGH);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(450);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(500);
  
}


void gira_esquerda(){
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(1000);
   digitalWrite (3, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(450);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   delay(500);
  
}


void verifica(){
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    
    duration=pulseIn (echopin,HIGH);
    
    distance= duration/58.2;
    delay(50);
    Serial.println(distance);  
}

void verifica_d(){
    digitalWrite(trigpin_d,LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigpin_d,HIGH);
    delayMicroseconds(10);
    
    duration_d = pulseIn (echopin_d,HIGH);
    
    distance_d= duration_d/58.2;
    delay(50);
    Serial.println(distance_d);  
}


//---------------------------------------------------------------

void rotina_obstaculo(){
      verifica();
      if (distance < 15){
        para();
        gira_direita();
        verifica_d();
        while(distance_d < 15){
          verifica_d();
          frente();
        }
        
        delay(500);
        verifica_d();
        if(distance_d > 15){
          para();
          gira_esquerda();
          frente();
        }
        
        
        readvoice = "interrup";
      }
        
        
      }  
      


//-------------------------------------------------------------------
void loop() {
  
//--------------------------------------------------------------------------------
  
  
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }
  
//---------------------------------------------------------------------------------
  rotina_obstaculo(); 
  
  if (readvoice.length() >= 0) {
    Serial.println(readvoice);

      if(readvoice == "frente"){
        frente();}    
        
      else if(readvoice == "volta"){
        volta();}

      else if (readvoice == "direita"){
        direita();}

      else if ( readvoice == "esquerda"){
        esquerda();}

      else if (readvoice == "para"){
        para();}

      readvoice=""; //Reset the variable
  }
}




