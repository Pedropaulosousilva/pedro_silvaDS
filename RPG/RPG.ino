#define pinHeroiLED 5
#define pinVilaoLED 6
#define ledvermelho 3
#define ledverde 4
#define ledamarelo 2
#define buzzer 10
#define pinoHeroi 8
#define pinoVillian 7

// Pino para o botão que será pressionado para rolar o dado
int pinBotao = 9;
bool estadoBotao = false;           // Estado atual do botão
bool estadoBotao_anterior = false;  // Estado anterior do botão


// Variavel para definição de turno
bool turnoHeroi = false;
bool turnoVilao = false;

// Variável para armazenar o resultado do dado
int resultadoDado;

//variaveis de vida
int vidaVilao = 100;
int vidaHeroi = 100;

//variavel de decisão de turnos
bool turnosOn = false;
bool gamestatus = false;
bool comeco = true;

void setup() {
  // Inicialização dos pinos
  pinMode(pinHeroiLED, OUTPUT);
  pinMode(pinVilaoLED, OUTPUT);
  pinMode(pinBotao, INPUT);
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(ledamarelo, OUTPUT);
  // Inicialização da comunicação serial para debug
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  if (comeco == true){
  inicio();
  }
  //_______________________________________________________________________________________________
  fim ();
  //aaaaaaaaaaaaaaaaaaaaaaaa
  if (turnosOn) {  //dividir quais são os botoes
    estadoBotao = digitalRead(pinBotao);
    if (estadoBotao == HIGH && estadoBotao_anterior == LOW) {
      while (digitalRead(pinBotao) == HIGH) {
        resultadoDado = random(1, 21);  // Gera um número aleatório entre 1 e 20
        Serial.print("Resultado do dado: ");
        delay(800);
        Serial.println(resultadoDado);
        delay(1000);
        if (resultadoDado % 2 == 0) {
          // É par, é o turno do herói
          digitalWrite(pinHeroiLED, HIGH);
          digitalWrite(pinVilaoLED, LOW);
          Serial.println("");
          Serial.println("Turno do heroi!");
          turnoHeroi = true;
          delay(2000);
          digitalWrite(pinHeroiLED, LOW);
          Serial.println("Gire o dado novamente para atacar o VILAO!! \n");
        } else {
          // É ímpar, é o turno do vilão
          digitalWrite(pinHeroiLED, LOW);
          digitalWrite(pinVilaoLED, HIGH);
          Serial.println("");
          Serial.println("Turno do vilao!");
          turnoVilao = true;
          delay(2000);
          digitalWrite(pinVilaoLED, LOW);
          Serial.println("Gire o dado novamente para atacar o HEROI!! \n");
        }
        // Aguarda um tempo para evitar leituras rápidas  do botão
        delay(1000);
        turnosOn = false;
      }
    }
  }  // fim dos turnos_______________________________________________________________________________
  if (estadoBotao == HIGH && estadoBotao_anterior == LOW) {
    while (digitalRead(pinBotao) == HIGH) {
      if (turnoHeroi) {
        ataques();
      }
    }
    while (digitalRead(pinBotao) == HIGH) {
      if (turnoVilao) {
        ataqueVilao();
      }
    }
  }
}

//condições de ataque heroi_____________________________________________________
void ataques() {
  resultadoDado = random(1, 21);  // Gera um número aleatório entre 1 e 20
  Serial.print("Resultado do dado: ");
  delay(800);
  Serial.println(resultadoDado);
  delay(1000);
  if (resultadoDado <= 10) {
    digitalWrite(ledvermelho, HIGH);
    tone(buzzer, 495); //AGUDO________________
    Serial.println("ERROU O ATAQUE");
    Serial.println("");
    turnoHeroi = false;
    delay(1500);
    digitalWrite(ledvermelho, LOW);
    noTone(buzzer);
    resultadoDado = 0;
  }
  if (resultadoDado > 10) {
    if (resultadoDado < 17) {
      digitalWrite(ledverde, HIGH);
      tone(buzzer, 392); //POUCO GRAVE_____________
      Serial.println("Acertou!!");
      delay(1500);
      digitalWrite(ledverde, LOW);
      noTone(buzzer);
      vidaVilao -= resultadoDado;
      Serial.print("Dano causado: ");
      Serial.println(resultadoDado);
      delay(1500);
      Serial.print("VIDA ATUAL DO Vilao: ");
      Serial.println(vidaVilao);
      Serial.println("");
      delay(1000);
      turnoHeroi = false;
    }
    if (resultadoDado >= 17) {
      digitalWrite(ledamarelo, HIGH);
      tone(buzzer, 261); //MUITO GRAVE___________________
      Serial.println("ACERTO CRITICO!!");
      delay(1500);
      digitalWrite(ledamarelo, LOW);
      noTone(buzzer);
      resultadoDado = resultadoDado * 2;
      vidaVilao -= resultadoDado;
      Serial.print("Dano causado : ");
      Serial.println(resultadoDado);
      delay(1500);
      Serial.print("VIDA ATUAL DO Vilao: ");
      Serial.println(vidaVilao);
      Serial.println("");
      delay(1000);
      turnoHeroi = false;
    }
  }
  //TROCA DE TURNO
  Serial.println("Turno Vilao");
  Serial.println("Aperte o botao para rolar o DADO!");
  resultadoDado = 0;
  turnoVilao = true;
  if (estadoBotao == HIGH && estadoBotao_anterior == LOW) {
    while (digitalRead(pinBotao) == HIGH) {
    }
  }
}


void ataqueVilao() {
  resultadoDado = random(1, 21);  // Gera um número aleatório entre 1 e 20
  Serial.print("Resultado do dado: ");
  delay(800);
  Serial.println(resultadoDado);
  delay(1000);
  if (resultadoDado <= 10) {
     digitalWrite(ledvermelho, HIGH);
    tone(buzzer, 495);
    Serial.println("ERROU O ATAQUE");
    Serial.println("");
    turnoVilao = false;
    delay(1500);
    digitalWrite(ledvermelho, LOW);
    noTone(buzzer);
    resultadoDado = 0;
  }
  if (resultadoDado > 10) {
    if (resultadoDado < 17) {
      digitalWrite(ledverde, HIGH);
      tone(buzzer, 392);
      Serial.println("Acertou!!");
      delay(1500);
      digitalWrite(ledverde, LOW);
      noTone(buzzer);
      vidaHeroi -= resultadoDado;
      Serial.print("Dano causado: ");
      Serial.println(resultadoDado);
      delay(1500);
      Serial.print("VIDA ATUAL DO Heroi: ");
      Serial.println(vidaHeroi);
      Serial.println("");
      delay(1000);
      turnoVilao = false;
    }
    if (resultadoDado >= 17) {
      digitalWrite(ledamarelo, HIGH);
      tone(buzzer, 261);
      Serial.println("ACERTO CRITICO!!");
      delay(1500);
      digitalWrite(ledamarelo, LOW);
      noTone(buzzer);
      resultadoDado = resultadoDado * 2;
      vidaHeroi -= resultadoDado;
      Serial.print("Dano causado : ");
      Serial.println(resultadoDado);
      delay(1500);
      Serial.print("VIDA ATUAL DO Heroi: ");
      Serial.println(vidaHeroi);
      Serial.println("");
      delay(1000);
      turnoVilao = false;
    }
  }
  //TROCA DE TURNO
  Serial.println("Turno Heroi");
  Serial.println("Aperte o botao para rolar o DADO!");
  resultadoDado = 0;
  turnoHeroi = true;
  if (estadoBotao == HIGH && estadoBotao_anterior == LOW) {
      while (digitalRead(pinBotao) == HIGH) {
      }
    }
  }

void fim(){
 if (vidaHeroi <= 0){
  Serial.println("Fim de jogo!!!");
  Serial.println("O vilao GANHOUU");
   while (true) {
    // Nada será executado além deste loop infinito
  }
 }
  if (vidaVilao <= 0){
  Serial.println("Fim de jogo!!!");
  Serial.println("O heroi GANHOUU");
   while (true) {
    // Nada será executado além deste loop infinito
  }
 }
}

void inicio() {
  if (digitalRead(pinBotao) == 1 && comeco == true) {
    digitalWrite(ledamarelo, HIGH);
    Serial.println("Bem vindo ao RPG DUEL!!!");
    delay(600);
    Serial.println("Escolhe o seu personagem!");
    delay(300);
    Serial.println("1 Para heroi, 2 para Vilao");
    delay(2000);
    digitalWrite(ledamarelo, LOW);
    gamestatus = true;
  }
  while (gamestatus == true) {

    if (digitalRead(pinoHeroi) == 1) {
      digitalWrite(pinHeroiLED, HIGH);
      Serial.println("HEROIIII!!!");
      Serial.println("Se o numero do dado for PAR o HEROI começa atacando!! \n");
      Serial.println("Se o numero do dado for Impar o VILAO começa atacando!!");
      Serial.println("Aperte o botao para iniciar \n");
      delay(2000);
      digitalWrite(pinHeroiLED, LOW);
      gamestatus = false;
      turnosOn = true;
      comeco = false;
    }
    
    if (digitalRead(pinoVillian) == 1) {
      digitalWrite(pinVilaoLED, HIGH);
      Serial.println("VILAAOOOO!!! \n");
      Serial.println("Se o numero do dado for PAR o HEROI começa atacando!!");
      Serial.println("Se o numero do dado for Impar o VILAO começa atacando!!\n");
      delay(1500);
      Serial.println("Aperte o botao para iniciar");
      delay(2000);
      digitalWrite(pinVilaoLED, LOW);
      gamestatus = false;
      turnosOn = true;
      comeco = false;
    }
  }
}

