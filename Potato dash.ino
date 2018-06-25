#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

//pinos
#define CLK 11 // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

//cores
#define POTATA 51,25,0
#define OLEO 0,5,20
#define PRETO 0,0,0
#define LILAS 194, 48, 220
#define BRANCO 255,255,255
#define VERDINHO 4,7,0
#define VERDAO 0,7,0
#define AZULZINHO 0,4,7
#define ROXINHO 4,0,7
#define AZULZAO 0,0,7
#define MAGENTA 7,0,4
#define VERMELHO 7,0,0

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

//variavel da coordenada para apagar a função
int X;
int Y = 23;

//obstaculos
int P, K, R;

// botao
int bjump = 12;
int estadopulo = 0;

//obstaculos
int obs = 0;
int obs2 = 0;
int temobstaculo = 0;
int obstaculo = 0;


//funçao pulo
int variavel = 0;
int contador = 0;
int pulo = 0;

//morte
int coordbatatax = 0;
int coordobs1   = 0;
int temobs = 1;

//substituir o delay
unsigned long anterior = 0;
unsigned long atual = 0;
int interval = 30;
int tempo1 = 80;
int cont1 = 0;
int flag = 0;

//placar
int gamestart = 0;
int r = 0;
int pontuacao = 0;
int bestatual = 0;
int bestmaior = 0;


void setup() {
  matrix.begin();
  pinMode(bjump, INPUT_PULLUP); // botao
  attachInterrupt(12, jump, FALLING); // interrupção
  intro();
  while (digitalRead(12) == 1);
  delay(200);
  matrix.fillRect(0, 0, 33, 33, matrix.Color333 (PRETO));
  variavel = 18; // posição da ordenada
  batata(2, variavel, 5, 6);
  obs = 0;
  P = 35;
  K = 150;
  R = 160;
  chao();
}

void batata(int posx, int posy, int tam1, int tam2) {
  matrix.fillRect(posx, posy, tam1, tam2, matrix.Color333(POTATA));
  matrix.drawLine(posx + 1, posy - 1, posx + tam1 - 2, posy - 1,  matrix.Color333(POTATA));
  matrix.drawLine(posx + 1, posy + tam2, posx + tam1 - 2, posy + tam2,  matrix.Color333(POTATA));
  matrix.drawPixel(posx + 1, posy + 1, matrix.Color333(OLEO));
  matrix.drawPixel(posx + 3, posy + 1, matrix.Color333(OLEO));
}

void chao() {
  matrix.fillRect(0, 25, 32, 7, matrix.Color333(LILAS));
}

void death() {
  matrix.fillRect(0, 0, 33, 33, matrix.Color333(PRETO));

  matrix.drawLine(9, 1, 9, 3, matrix.Color333(LILAS));
  matrix.drawLine(10, 4, 11, 4, matrix.Color333(LILAS));
  matrix.drawLine(10, 6, 11, 6, matrix.Color333(LILAS));        // Y
  matrix.drawLine(12, 1, 12, 5, matrix.Color333(LILAS));

  matrix.drawLine(15, 1, 16, 1, matrix.Color333(LILAS));
  matrix.drawLine(14, 2, 14, 3, matrix.Color333(LILAS));     // O
  matrix.drawLine(17, 2, 17, 3, matrix.Color333(LILAS));
  matrix.drawLine(15, 4, 16, 4, matrix.Color333(LILAS));

  matrix.drawLine(19, 1, 19, 3, matrix.Color333(LILAS));
  matrix.drawLine(22, 1, 22, 3, matrix.Color333(LILAS));   // U
  matrix.drawLine(20, 4, 21, 4, matrix.Color333(LILAS));


  matrix.drawLine(11, 8, 11, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(9, 10, 10, 10, matrix.Color333(MAGENTA));     // D
  matrix.drawLine(9, 14, 10, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(8, 11, 8, 13, matrix.Color333(MAGENTA));

  matrix.drawLine(13, 10, 13, 14, matrix.Color333(MAGENTA));     // I

  matrix.drawLine(16, 10, 17, 10, matrix.Color333(MAGENTA));
  matrix.drawLine(15, 11, 15, 13, matrix.Color333(MAGENTA));     // E
  matrix.drawLine(16, 14, 18, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(16, 12, 18, 12, matrix.Color333(MAGENTA));
  matrix.drawPixel(18, 11, matrix.Color333(MAGENTA));

  matrix.drawLine(23, 8, 23, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(21, 10, 22, 10, matrix.Color333(MAGENTA));     // D
  matrix.drawLine(21, 14, 22, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(20, 11, 20, 13, matrix.Color333(MAGENTA));

  matrix.fillRect(13, Y - 7, 7, 13, matrix.Color333(PRETO));
  matrix.fillRect(13, Y, 7, 7, matrix.Color333(BRANCO));
  matrix.fillRect(15, Y - 3, 3, 3, matrix.Color333(BRANCO));
  matrix.drawPixel(14, Y - 1 , matrix.Color333(BRANCO));
  matrix.drawPixel(18, Y - 1, matrix.Color333(BRANCO));
  matrix.drawPixel(15, Y - 6 , matrix.Color333(BRANCO));
  matrix.drawPixel(17, Y - 6, matrix.Color333(BRANCO));
  matrix.drawLine(16, Y - 7, 16, Y - 4, matrix.Color333(BRANCO));


  delay(1500);
  matrix.fillRect(0, 0, 33, 33, matrix.Color333(PRETO));
  matrix.drawLine(4, 1, 4, 7, matrix.Color333(OLEO));
  matrix.drawLine(5, 1, 7, 1, matrix.Color333(OLEO));     // B
  matrix.drawLine(5, 4, 7, 4, matrix.Color333(OLEO));
  matrix.drawLine(5, 7, 7, 7, matrix.Color333(OLEO));
  matrix.drawLine(8, 2, 8, 3, matrix.Color333(OLEO));
  matrix.drawLine(8, 5, 8, 6, matrix.Color333(OLEO));

  matrix.drawLine(11, 1, 14, 1, matrix.Color333(OLEO));
  matrix.drawLine(11, 4, 13, 4, matrix.Color333(OLEO));     // E
  matrix.drawLine(11, 7, 14, 7, matrix.Color333(OLEO));
  matrix.drawLine(10, 1, 10, 7, matrix.Color333(OLEO));

  matrix.drawLine(17, 1, 19, 1, matrix.Color333(OLEO));
  matrix.drawLine(17, 4, 19, 4, matrix.Color333(OLEO));
  matrix.drawLine(17, 7, 19, 7, matrix.Color333(OLEO));
  matrix.drawLine(16, 2, 16, 3, matrix.Color333(OLEO));       // S
  matrix.drawLine(20, 5, 20, 6, matrix.Color333(OLEO));
  matrix.drawPixel(20, 2, matrix.Color333(OLEO));
  matrix.drawPixel(16, 6, matrix.Color333(OLEO));

  matrix.drawLine(24, 1, 24, 7, matrix.Color333(OLEO));
  matrix.drawLine(22, 1, 26, 1, matrix.Color333(OLEO));        // T

  matrix.setCursor(10, 10);
  matrix.setTextColor(matrix.Color333(BRANCO));
  matrix.print(bestmaior);

  matrix.fillRect(12,19,7,5, matrix.Color333(POTATA));
  matrix.fillRect(14,28,3,2, matrix.Color333(POTATA));
  matrix.drawLine(13,24,17,24, matrix.Color333(POTATA));
  matrix.drawLine(14,25,16,25, matrix.Color333(POTATA));
   matrix.drawLine(15,26,15,27, matrix.Color333(POTATA));
        
          matrix.drawLine(9,19,10,19, matrix.Color333(POTATA));
        matrix.drawLine(20,19,21,19, matrix.Color333(POTATA));
          matrix.drawLine(8,20,8,22, matrix.Color333(POTATA));
        matrix.drawLine(22,20,22,22, matrix.Color333(POTATA));
          matrix.drawLine(11,25,12,25, matrix.Color333(POTATA));
        matrix.drawLine(18,25,19,25, matrix.Color333(POTATA));
         matrix.drawLine(12,19,18,19, matrix.Color333(255,230,0));
        
        matrix.drawPixel(11,20, matrix.Color333(POTATA));
        matrix.drawPixel(9,23, matrix.Color333(POTATA));
        matrix.drawPixel(10,24, matrix.Color333(POTATA));
        matrix.drawPixel(19,20, matrix.Color333(POTATA));
        matrix.drawPixel(21,23, matrix.Color333(POTATA));
        matrix.drawPixel(20,24, matrix.Color333(POTATA));
        matrix.drawPixel(13,29, matrix.Color333(POTATA));
        matrix.drawPixel(17,29, matrix.Color333(POTATA));

  P = 40;
  K = 50;
  R = 60;
}


void intro() {
  matrix.fillRect(0, 0, 33, 33, matrix.Color333 (PRETO)); // limpa a tela
  matrix.fillRect(10, 6 , 16, 17, matrix.Color333(POTATA));
  matrix.fillRect(15, 2, 8, 2, matrix.Color333(POTATA));
  matrix.fillRect(12, 4, 13, 2, matrix.Color333(POTATA));
  matrix.fillRect(26, 9, 2, 10, matrix.Color333(POTATA));
  matrix.fillRect(8, 10, 3, 4, matrix.Color333(POTATA));
  matrix.fillRect(6, 14, 4, 9, matrix.Color333(POTATA));
  matrix.fillRect(4, 17, 3, 9, matrix.Color333(POTATA));
  matrix.fillRect(6, 23, 15, 5, matrix.Color333(POTATA));
  matrix.fillRect(21, 23, 3, 2, matrix.Color333(POTATA));
  matrix.drawPixel(23, 3, matrix.Color333(POTATA));
  matrix.drawPixel(25, 5, matrix.Color333(POTATA));
  matrix.drawPixel(11, 5, matrix.Color333(POTATA));
  matrix.drawPixel(25, 5, matrix.Color333(POTATA));               // corpo da batata
  matrix.drawPixel(24, 23, matrix.Color333(POTATA));
  matrix.drawPixel(21, 26, matrix.Color333(POTATA));
  matrix.drawPixel(5, 26, matrix.Color333(POTATA));
  matrix.drawLine(13, 3, 14, 3, matrix.Color333(POTATA));
  matrix.drawLine(26, 7, 26, 8, matrix.Color333(POTATA));
  matrix.drawLine(9, 8, 9, 9, matrix.Color333(POTATA));
  matrix.drawLine(7, 12, 7, 13, matrix.Color333(POTATA));
  matrix.drawLine(5, 15, 5, 16, matrix.Color333(POTATA));
  matrix.drawLine(26, 19, 26, 20, matrix.Color333(POTATA));
  matrix.drawLine(3, 19, 3, 24, matrix.Color333(POTATA));
  matrix.drawLine(21, 25, 22, 25, matrix.Color333(POTATA));
  matrix.drawLine(8, 28, 18, 28, matrix.Color333(POTATA));

  matrix.drawLine(12, 6, 14, 6, matrix.Color333(PRETO));
  matrix.drawPixel(15, 7, matrix.Color333(PRETO));
  matrix.drawLine(21, 6, 23, 6, matrix.Color333(PRETO));
  matrix.drawPixel(20, 7, matrix.Color333(PRETO));
  matrix.drawLine(21, 9, 23, 9, matrix.Color333(PRETO));
  matrix.drawLine(12, 9, 14, 9, matrix.Color333(PRETO));
  matrix.drawLine(11, 10, 11, 11, matrix.Color333(PRETO));
  matrix.drawLine(15, 10, 15, 11, matrix.Color333(PRETO));
  matrix.drawLine(20, 10, 20, 11, matrix.Color333(PRETO));
  matrix.drawLine(24, 10, 24, 11, matrix.Color333(PRETO));
  matrix.fillRect(12, 10, 2, 3, matrix.Color333(OLEO));               // rosto da batata
  matrix.fillRect(21, 10, 2, 3, matrix.Color333(OLEO));
  matrix.drawPixel(12, 10, matrix.Color333(BRANCO));
  matrix.drawPixel(21, 10, matrix.Color333(BRANCO));
  matrix.drawLine(17, 10, 17, 12, matrix.Color333(PRETO));
  matrix.drawLine(16, 13, 16, 15, matrix.Color333(PRETO));
  matrix.drawLine(17, 15, 18, 15, matrix.Color333(PRETO));
  matrix.drawLine(16, 18, 19, 18, matrix.Color333(PRETO));
  matrix.drawPixel(21, 16, matrix.Color333(PRETO));
  matrix.drawPixel(20, 17, matrix.Color333(PRETO));
  matrix.drawPixel(15, 17, matrix.Color333(PRETO));
  matrix.drawLine(11, 14, 13, 14, matrix.Color333(MAGENTA));
  matrix.drawLine(22, 14, 24, 14, matrix.Color333(MAGENTA));
  delay(800);
  matrix.fillRect(0, 0, 33, 33, matrix.Color333 (PRETO)); // limpa a tela
  matrix.drawLine(2, 1, 2, 6,  matrix.Color333(VERDINHO));
  matrix.drawLine(2, 1, 4, 1,  matrix.Color333(VERDINHO));
  matrix.drawLine(2, 4, 4, 4,  matrix.Color333(VERDINHO)); // P
  matrix.drawLine(5, 2, 5, 3,  matrix.Color333(VERDINHO));

  matrix.drawLine(8, 3, 9, 3,  matrix.Color333(VERDAO));
  matrix.drawLine(7, 4, 7, 5,  matrix.Color333(VERDAO));
  matrix.drawLine(8, 6, 9, 6,  matrix.Color333(VERDAO)); // O
  matrix.drawLine(10, 4, 10, 5,  matrix.Color333(VERDAO));

  matrix.drawLine(13, 1, 13, 6,  matrix.Color333(AZULZINHO));
  matrix.drawLine(12, 2, 14, 2,  matrix.Color333(AZULZINHO)); // T
  matrix.drawPixel(14, 6,  matrix.Color333(AZULZINHO));

  matrix.drawLine(17, 3, 18, 3,  matrix.Color333(AZULZAO));
  matrix.drawLine(16, 4, 16, 5,  matrix.Color333(AZULZAO));
  matrix.drawLine(17, 6, 18, 6,  matrix.Color333(AZULZAO)); // A
  matrix.drawLine(19, 4, 19, 5,  matrix.Color333(AZULZAO));
  matrix.drawPixel(20, 6,  matrix.Color333(AZULZAO));

  matrix.drawLine(22, 1, 22, 6,  matrix.Color333(ROXINHO));
  matrix.drawLine(21, 2, 23, 2,  matrix.Color333(ROXINHO)); // T
  matrix.drawPixel(23, 6,  matrix.Color333(ROXINHO));

  matrix.drawLine(26, 3, 27, 3,  matrix.Color333(MAGENTA));
  matrix.drawLine(25, 4, 25, 5,  matrix.Color333(MAGENTA));
  matrix.drawLine(26, 6, 27, 6,  matrix.Color333(MAGENTA)); // O
  matrix.drawLine(28, 4, 28, 5,  matrix.Color333(MAGENTA));


  matrix.drawLine(4, 10, 4, 16,  matrix.Color333(BRANCO));
  matrix.drawLine(8, 12, 8, 14,  matrix.Color333(BRANCO));  // D
  matrix.drawPixel(7, 11,  matrix.Color333(BRANCO));
  matrix.drawPixel(7, 15,  matrix.Color333(BRANCO));
  matrix.drawLine(5, 10, 6, 10,  matrix.Color333(BRANCO));
  matrix.drawLine(5, 16, 6, 16,  matrix.Color333(BRANCO));

  matrix.drawLine(10, 11, 10, 16,  matrix.Color333(BRANCO));
  matrix.drawLine(14, 11, 14, 16,  matrix.Color333(BRANCO));  // A
  matrix.drawLine(11, 10, 13, 10,  matrix.Color333(BRANCO));
  matrix.drawLine(11, 13, 13, 13,  matrix.Color333(BRANCO));

  matrix.drawLine(17, 10, 19, 10,  matrix.Color333(BRANCO));
  matrix.drawLine(17, 13, 19, 13,  matrix.Color333(BRANCO));
  matrix.drawLine(17, 16, 19, 16, matrix.Color333(BRANCO)); // S
  matrix.drawLine(16, 11, 16, 12, matrix.Color333(BRANCO));
  matrix.drawLine(20, 14, 20, 15, matrix.Color333(BRANCO));
  matrix.drawPixel(20, 11,  matrix.Color333(BRANCO));
  matrix.drawPixel(16, 15,  matrix.Color333(BRANCO));

  matrix.drawLine(22, 10, 22, 16,  matrix.Color333(BRANCO));
  matrix.drawLine(26, 10, 26, 16,  matrix.Color333(BRANCO));
  matrix.drawLine(23, 13, 25, 13,  matrix.Color333(BRANCO)); // H

  // corações
  delay(400);
  matrix.fillRect(3, 22, 7, 3, matrix.Color333(VERMELHO));
  matrix.drawLine(4, 21, 5, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(7, 21, 8, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(4, 25, 8, 25, matrix.Color333(VERMELHO));
  matrix.drawLine(5, 26, 7, 26, matrix.Color333(VERMELHO));
  matrix.drawPixel(6, 27, matrix.Color333(VERMELHO));

  delay(400);
  matrix.fillRect(12, 22, 7, 3, matrix.Color333(VERMELHO));
  matrix.drawLine(13, 21, 14, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(16, 21, 17, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(13, 25, 17, 25, matrix.Color333(VERMELHO));                    // corações
  matrix.drawLine(14, 26, 16, 26, matrix.Color333(VERMELHO));
  matrix.drawPixel(15, 27, matrix.Color333(VERMELHO));

  delay(400);
  matrix.fillRect(21, 22, 7, 3, matrix.Color333(VERMELHO));
  matrix.drawLine(22, 21, 23, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(25, 21, 26, 21,  matrix.Color333(VERMELHO));
  matrix.drawLine(22, 25, 26, 25, matrix.Color333(VERMELHO));
  matrix.drawLine(23, 26, 25, 26, matrix.Color333(VERMELHO));
  matrix.drawPixel(24, 27, matrix.Color333(VERMELHO));

}

void obstacle1() { // tomate
  matrix.fillCircle(P + 1, 22, 2, matrix.Color333(PRETO));
  matrix.drawLine(P - 1, 19, P + 1, 19, matrix.Color333(PRETO));
  matrix.fillCircle(P, 22, 2, matrix.Color333(7, 0, 0));
  matrix.drawLine(P - 1, 20, P + 1, 20, matrix.Color333(0, 7, 0));
  matrix.drawPixel(P, 19, matrix.Color333(0, 7, 0));
}

void obstacle2() { // cenoura
  matrix.fillRect(K, 17, 4, 8, matrix.Color333(PRETO));
  matrix.fillRect(K, 18, 3, 6, matrix.Color333(255, 137, 0));
  matrix.drawPixel(K + 1, 24, matrix.Color333(255, 137, 0));
  matrix.drawLine(K, 18, K + 2, 18, matrix.Color333(0, 7, 0));
  matrix.drawPixel(K + 1, 17, matrix.Color333(0, 7, 0));
}

void obstacle3 () { // maracuja/ pimentão
  matrix.fillRect(R, 18, 6, 7, matrix.Color333(PRETO));
  matrix.fillCircle(R, 22, 2, matrix.Color333(255, 230, 0));
  matrix.drawPixel(R, 20, matrix.Color333(PRETO));
  matrix.drawPixel(R + 4, 20, matrix.Color333(PRETO));
  matrix.drawPixel(R, 20, matrix.Color333(0, 7, 0));
  matrix.drawPixel(R, 19, matrix.Color333(0, 7, 0));
  matrix.drawPixel(R + 1, 18, matrix.Color333(0, 7, 0));
}

void placar() {
  matrix.fillRect(9, 1, 21, 8, matrix.Color333(PRETO));
  matrix.setCursor(10, 1);
  matrix.setTextColor(matrix.Color333(BRANCO));
  matrix.print(pontuacao);
}


void loop() {
  randomSeed (analogRead(A0));
  unsigned long atual = millis();
  unsigned long ant = millis();
  estadopulo = !digitalRead(12);
  gamestart = 1;

  if (obs == 0) obstacle1();
  if (obs == 1) obstacle2();
  if (obs == 2) obstacle3();

  if (obs2 == 0) obstacle1();
  if (obs2 == 1) obstacle2();
  if (obs2 == 2) obstacle3();

  bestatual = pontuacao;

  if(bestatual>bestmaior) bestmaior = bestatual;
  

  if (gamestart == 1) {
    r++;
    cont1++;
    placar();
  }

  if (r % 25 == 0) pontuacao++;
  if (cont1 % 17 == 0) {
    tempo1--;
    flag = 1;
  }
  if (tempo1 == 10) flag = 0;

  if (atual >= anterior + interval) {
    coordbatatax = 2;
    if (estadopulo == 1) { //subir
      pulo = 1;
    }

    else  pulo = 0;

    if (estadopulo == 1 && variavel <= 9)
      contador++;
    if (contador > 30) pulo = 0;
    if (estadopulo == 0 && variavel == 18) contador = 0;

    if (pulo == 1) { // sobe uhu
      if (variavel > 8) {
        variavel--;
        matrix.fillRect(2, variavel, 6, 8, matrix.Color333(PRETO));
        batata(coordbatatax, variavel, 5, 6);
      }
    }
    if (pulo == 0) {
      if (variavel < 18) { //desce
        variavel++;
        matrix.fillRect(2, variavel, 6, -8, matrix.Color333(PRETO));
        batata(coordbatatax, variavel, 5, 6);
      }
    }
    anterior = atual;
  } // fim do botao (pulo)

  if (ant >= atual + tempo1) {
    switch (obs) {
      case 0: // morte com o tomate
        P--;
        obstacle1();
        if (P == 10) {
          obs2 = random(3);
          K = 35; 
          R = 35;
          if (obs2 == 0) obs2 = 1;
        }

        if ((((((2 <= P - 2 && P - 2 <= 7) && (variavel + 7 >= 22) || (2 <= P + 2 && P + 2 <= 7)) && (variavel + 8 >= 20))))) {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;

      case 1: // morte com a cenoura
        K--;
        obstacle2();
        if (K == 10) {
          obs2 = random(3);
          P = 35;
          R = 35;
          if (obs2 == 1) obs2 = 2;
        }


        if ((((2 <= K  && K <= 7)) && (variavel + 8 >= 20) || (2 <= K + 2 && K + 2 <= 7)) && (variavel + 8 >= 18))  {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;

      case 2: // morte com o maracujá ou pimentão
        R--;
        obstacle3();
        if (R == 10) {
          obs2 = random(3);
          P = 35;
          K = 35;
          if (obs2 == 2) obs2 = 0;
        }


        if ((((((2 <= R - 2 && R - 2 <= 7) && (variavel + 7 >= 22) || (2 <= R + 2 && R + 2 <= 7)) && (variavel + 8 >= 19))))) {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;
    }

    switch (obs2) {
      case 0: // morte com o tomate
        P--;
        obstacle1();
        if (P == 10) {
          obs = random(3);
          R = 35;
          K = 35;
          if (obs == 0) obs = 1;
        }

        if ((((((2 <= P - 2 && P - 2 <= 7) && (variavel + 7 >= 22) || (2 <= P + 2 && P + 2 <= 7)) && (variavel + 8 >= 20))))) {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;

      case 1: // morte com a cenoura
        K--;
        obstacle2();
        if (K == 10) {
          obs = random(3);
          R = 35;
          P = 35;
          if (obs == 1) obs = 2;
        }

        if ((((2 <= K  && K <= 7)) && (variavel + 8 >= 20) || (2 <= K + 2 && K + 2 <= 7)) && (variavel + 8 >= 18))  {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;

      case 2: // morte com o maracujá ou pimentão
        R--;
        obstacle3();
        if (R == 10) {
          obs = random(3);
          K = 35;
          P = 35;
          if (obs == 2) obs = 0;
        }

        if ((((((2 <= R - 2 && R - 2 <= 7) && (variavel + 7 >= 22) || (2 <= R + 2 && R + 2 <= 7)) && (variavel + 8 >= 19))))) {
          death();
          r = 0;
          tempo1 = 80;
          pontuacao = 0;
          delay(2000);
          setup();
        }
        break;
    }
    atual = ant;
  }

} // fim do loop

void jump() {
  estadopulo = 1;
}

