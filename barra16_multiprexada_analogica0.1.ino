/*
 * valor calibracion muestras = (valor blanco + valor negro)/2
 * valores blanco 208  393  973  972  259  197  280  160  203  156  256  279  292  412  264  327
 * valores negro  972  980  1007  1007  975  974  982  973  982  971  979  976  977  982  968  974
 * valor muestras 590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650
 */
const int LedsIr = 11;    //Pin para encender los leds ir
const int S0 = 14;        //Pin A0 de modo digital 
const int S1 = 15;        //Pin A1 de modo digital
const int S2 = 16;        //Pin A2 de modo digital
const int S3 = 17;        //Pin A3 de modo digital
const int ANALOG_IN = A4;

int Muestras[16]={590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650}; 
int sensorValores[16];
int Valor_Digital[16];

void setup()
{
  Serial.begin(9600);
  pinMode(LedsIr, OUTPUT);  //
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(LedsIr,HIGH); // Enciendo los leds ir
}

void loop()
{
Leer_Sensores_ir();
  delay(250);               
}


void Leer_Sensores_ir(void) {
 for(int i=0; i<=15;i++)  {       //Leo los 16 canales               
    digitalWrite(S0, i&0x01);
    digitalWrite(S1, i&0x02);
    digitalWrite(S2, i&0x04);
    digitalWrite(S3, i&0x08);
    sensorValores[i] = analogRead(ANALOG_IN); //Guardo los valores de los 16 sensores
 //  Serial.print(sensorValores[i]);  //aqui monitoreamos cada una de las 16 lecturas analogicas
 //  Serial.print("  ");
    if(sensorValores[i] < Muestras[i] ){Valor_Digital[i] = 1 ;}  //Convierto los valores de analogicos a digitales
    else {Valor_Digital[i] = 0 ;}
   Serial.print(Valor_Digital[i]);  //aqui monitoreamos cada una de las lecturas digitales
   Serial.print("  ");
  }
   Serial.println(" ");
}




