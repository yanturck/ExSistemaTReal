/*
 * Elabore um programa para a placa Arduino UNO
 * (use uma placa ou o simulador TinkerCad) que efetue o
 * cálculo da soma dos números primos entre 1 e 9999 e
 * determine em quanto tempo o cálculo foi efetuado.
 * Dica: use a função millis.
 */
unsigned long temp;

void primos(int num) {
  int i, j, count;

  for (i = 1; i <= num; i++) {
    count = 0;
    for (j = 1; j <= i; j++) {
      if (i%j == 0){
        ++count;
      }
    }
    if (count == 2) {
      Serial.println(i);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Os números primos entre 1 e 9999");
  primos(9999);
  temp = millis();
  Serial.println("Tempo gasto");
  Serial.println(temp);
}

void loop() {
    
}
