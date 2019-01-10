
int sensorValues[16];
int umbral=500; //por debajo de este valor la lectura del sensor sera cero, para un mejor calculo de la suma ponderada

/*Definimos valores constantes para las lineas selectoras del multiplexor (S0,S1,S2 y S3) asi como el output del mux (ANALOG_IN), 
 *
 *
 */
const int LEd_ir = 11;                  // Pin de encendido de los leds ir
const int S0 = 14;                      // Pin A0 en modo digital
const int S1 = 15;                      // Pin A1 en modo digital
const int S2 = 16;                      // Pin A2 en modo digital
const int S3 = 17;                      // Pin A3 en modo digital
const int ANALOG_IN = A4;               // Pin de lectura analogica

void setup()
{
  Serial.begin(9600);
  pinMode(S0, OUTPUT);                //Pines para el multiplexado del circuito
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(LEd_ir, OUTPUT);
  digitalWrite(LEd_ir, HIGH);
}

void loop()
{
int posicion=0;
  posicion=readSensor(); //Funcion para leer sensores que devuelve la posicion en un rango de 0 a 1200
  Serial.println(posicion); //Desplegamos continuamente la posicion en pantalla, quitar este envio de datos al momento
  delay(500);               //de integrar el codigo con un codigo completo ya que alentaria el procesamiento.
}

///////Funcion para leer sensores y devuelve el error//////////////
int readSensor(void) {
long int valor=0,sumap=0,suma=0,pos=0;
  
 for(int i=0; i<15;i++)  {                  //Leo los 16 canales
    digitalWrite(S0, i&0x01);
    digitalWrite(S1, i&0x02);
    digitalWrite(S2, i&0x04);
    digitalWrite(S3, i&0x08);
    sensorValues[i] = analogRead(ANALOG_IN); //Guardo las lecturas de los sensores
    if(sensorValues[i]<=umbral)
    {
      sensorValues[i]=0;
    }
    valor=sensorValues[i]*i;                 //Pondero las lecturas
    sumap=sumap+valor;
    suma=suma+sensorValues[i];
    //Serial.println(sensorValues[i]);  //aqui monitoreamos cada una de las lecturas
    delayMicroseconds(5);
  }
  pos=(sumap*100)/suma;
  suma=0;
  valor=0;
  return pos;                           //retorna el valor de la posicion
}




