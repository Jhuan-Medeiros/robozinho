#include <Ps3Controller.h>

// Define as portas das rodas

int rele1 = 23;
int rele2 = 33;
int roda1 = 18;
int roda2 = 19;

// Define o canal para as rodas

int canalRoda1 = 0;
int canalRoda2 = 1;

int frequencia = 5000;

int bits = 8;

void setup()
{
    Serial.begin(115200);

    // Define o controle

    Ps3.begin("01:02:03:04:05:06");

    pinMode(rele1, OUTPUT);
    pinMode(rele2, OUTPUT);

    // Começa o processo de leitura por ledc

    ledcSetup(canalRoda1, frequencia, bits);
    ledcSetup(canalRoda2, frequencia, bits);

    ledcAttachPin(roda1, canalRoda1);
    ledcAttachPin(roda2, canalRoda2);
}

void movimento(){
    int gatilhoR2 = Ps3.data.analog.button.r2;
        int gatilhoL2 = Ps3.data.analog.button.l2;

        int analogicoEsquerdo = Ps3.data.analog.stick.lx;

        if (gatilhoR2 > 5
        )
        {
            ledcWrite(canalRoda1, gatilhoR2);
            ledcWrite(canalRoda2, gatilhoR2);
            digitalWrite(rele1, LOW);
            digitalWrite(rele2, LOW);
        }
        else if (gatilhoL2 > 5)
        {
            ledcWrite(canalRoda1, gatilhoL2);
            ledcWrite(canalRoda2, gatilhoL2);
            digitalWrite(rele1, HIGH);
            digitalWrite(rele2, HIGH);
        }
        else if (abs(analogicoEsquerdo) > 20)
        {
            int velocidadeVirar = map(abs(analogicoEsquerdo), 20, 127, 100, 255);

            if (analogicoEsquerdo > 20)
            {
                digitalWrite(rele1, HIGH);
                digitalWrite(rele2, LOW);
            }
            else
            {
                digitalWrite(rele1, LOW);
                digitalWrite(rele2, HIGH);
            }
            ledcWrite(canalRoda1, velocidadeVirar);
            ledcWrite(canalRoda2, velocidadeVirar);
        }
        else
        {
            ledcWrite(canalRoda1, 0);
            ledcWrite(canalRoda2, 0);
            digitalWrite(rele1, LOW);
            digitalWrite(rele2, LOW);
        }
}

void loop()
{
    if (Ps3.isConnected())
    {
        movimento();
    }
}
