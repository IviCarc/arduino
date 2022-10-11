
 float intensidad= 0;//=corriente(); //Corriente eficaz (A)
 float sensor;
 float potencia;

unsigned long previousMillis=0;

long retardo2=millis();

void CORRIENTE (){
  float ondac=0;
  long retardo=millis();

int s=0;

while(millis()-retardo<1000)//Duración de un segundo
  { 
//-------Ecuaciones para el calculo de la intencidad y potencia 
    sensor = analogRead(A0) * (1.115 / 1023.0);////voltaje del sensor(se puede cambiar el valor para lograr mayor presisción)
    intensidad=sensor*30.0; //corriente=sensor*(30A/1V)
    ondac=ondac+sq(intensidad);//Sumatoria de Cuadrados/ sq-->cuadrado de un número
    s=s+1;
    delay(1);
  }
ondac=ondac*2;//Para compensar los cuadrados de los semiciclos negativos.
intensidad=sqrt((ondac)/s); //ecuación del RMS sqrt-->raiz cuadrada

 Serial.print("Corriente: ");  
 Serial.print(intensidad,4);

}




void setup() {

  Serial.begin(9600);
  analogReference(INTERNAL);
  
}

void loop(){
  CORRIENTE();
}
