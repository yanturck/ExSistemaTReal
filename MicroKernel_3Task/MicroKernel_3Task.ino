#include "avr/wdt.h"
#include "TimerOne.h" // Se for simular no TinkerCad, remover e usar registradores

#define NUMBER_OF_TASKS  3
#define TEMPO_MAXIMO_EXECUCAO 100   // 100ms
#define SUCCESS 1
#define FAIL    0
#define SIM 1
#define NAO 0

#define H HIGH
#define L LOW

#define A 11
#define B 10
#define C 9
#define D 8
#define E 7
#define F 6
#define G 5

typedef void(*ptrFunc)();  // Definição ponteiro de função

// Definição da estrutura que contem as informações das tarefas
typedef struct{
  ptrFunc Function;
  uint32_t period;
  bool enableTask; 
} TaskHandle;

// Definição do buffer para armazenar as tarefas
TaskHandle* buffer[NUMBER_OF_TASKS]; 

// Variáveis globais do kernel
volatile uint32_t taskCounter[NUMBER_OF_TASKS];
volatile int16_t TempoEmExecucao;
volatile uint32_t sysTickCounter = 0;
volatile bool TemporizadorEstourou;
volatile bool TarefaSendoExecutada;

int count = 0;
char segs[8];

// Inicializa as variaveis utilizadas pelo kernel
char KernelInit() {
  memset(buffer, NULL, sizeof(buffer));    // Inicializa o buffer para funções
  memset(taskCounter, 0, sizeof(taskCounter)); 

  TemporizadorEstourou = NAO;
  TarefaSendoExecutada = NAO;

  // Base de tempo para o escalonador
  Timer1.initialize(10000);             // 10ms
  Timer1.attachInterrupt(IsrTimer);    // chama vIsrTimer() quando o timer estoura

  return SUCCESS;
}

// Adiciona uma nova tarefa ao pool
char KernelAdd(TaskHandle* task) {
  int i;
 
  // Verifica se já existe a tarefa no buffer
  for(i = 0; i < NUMBER_OF_TASKS; i++) {
    if((buffer[i]!=NULL) && (buffer[i] == task)) return SUCCESS;
  }

  // Adiciona a tarefa em um slot vazio
  for(i = 0; i < NUMBER_OF_TASKS; i++) {
    if(!buffer[i]) {
      buffer[i] = task;
      return SUCCESS;
    }
  }
  return FAIL;
}

// Remove a tarefa do pool
char KernelRemoveTask(TaskHandle* task) {
  int i;
  
  for(i=0; i<NUMBER_OF_TASKS; i++) {
     if(buffer[i] == task) {
        buffer[i] = NULL;
        return SUCCESS; 
     }
  }
  return FAIL;
}

// Escalona as terefas
void KernelLoop() {
  int i;

  for (;;) {
    if (TemporizadorEstourou == SIM) {
      for (i = 0; i < NUMBER_OF_TASKS; i++) {
        if (buffer[i] != 0) {
          if (((sysTickCounter - taskCounter[i])>buffer[i]->period) && (buffer[i]->enableTask == SIM)) {
            TarefaSendoExecutada = SIM;
            TempoEmExecucao = TEMPO_MAXIMO_EXECUCAO;
            buffer[i]->Function();
            TarefaSendoExecutada = NAO;
            taskCounter[i] = sysTickCounter;
          }
        }
      }
    }
  }
}

void IsrTimer() {
  int i;
  TemporizadorEstourou = SIM;

  sysTickCounter++;
  
  // Conta o tempo em que uma tarefa está em execução
  if (TarefaSendoExecutada == SIM) {
    TempoEmExecucao--;
    if (!TempoEmExecucao) {
      // possivelmente a tarefa travou, então, ativa o WDT para reiniciar o micro
      wdt_enable(WDTO_15MS);
      while (1);
    }
  }
}

// =================================== Tarefas =============================================
void LED1() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  Serial.println("LED1 Ligado!");
}

void LED2() {
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  Serial.println("LED2 Ligado!");
}

// Task Contador
void Contador() {
  Serial.println(count);
  switch(count) {
    case 0: *segs = "HHHHHHL";
      count++;
    break;
    case 1: *segs = "HHLLLLL";
      count++;
    break;
    case 2: *segs = "HHLHHLH";
      count++;
    break;
    case 3: *segs = "HHHHLLH";
      count++;
    break;
    case 4: *segs = "LHHLLHH";
      count++;
    break;
    case 5: *segs = "HLHHLHH";
      count++;
    break;
    case 6: *segs = "HLHHHHH";
      count++;
    break;
    case 7: *segs = "HHHLLLL";
      count++;
    break;
    case 8: *segs = "HHHHHHH";
      count++;
    break;
    case 9: *segs = "HHHHLHH";
      count = 0;
    break;
  }

  digitalWrite(A, segs[0]);
  digitalWrite(B, segs[1]);
  digitalWrite(C, segs[2]);
  digitalWrite(D, segs[3]);
  digitalWrite(E, segs[4]);
  digitalWrite(F, segs[5]);
  digitalWrite(G, segs[6]);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); // LED1
  pinMode(12, OUTPUT); // LED2
  
  pinMode(A, OUTPUT); // Segmento1
  pinMode(B, OUTPUT); // Segmento2
  pinMode(C, OUTPUT); // Segmento3
  pinMode(D, OUTPUT); // Segmento4
  pinMode(E, OUTPUT); // Segmento5
  pinMode(F, OUTPUT); // Segmento6
  pinMode(G, OUTPUT); // Segmento7
  
  TaskHandle task1 = {LED1, 500, SIM}; 
  TaskHandle task2 = {LED2, 230, SIM};
  TaskHandle task3 = {Contador, 750, SIM};
  KernelInit();
  KernelAdd(&task1);
  KernelAdd(&task2);
  KernelAdd(&task3);
  KernelLoop();
}

void loop() {}
