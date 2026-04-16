#include <stdio.h>
#include <stdlib.h>

#define NUM_DATA 100

int BinaryData();
float Transmitter(int txData);
float Channel(float txSignal);
int Receiver(float rxSignal);

int main()
{
    int i, txData, rxData, count = 0;
    float txSignal, rxSignal, errorRate;

    for (i = 0; i < NUM_DATA; i++) {
        txData = BinaryData();
        txSignal = Transmitter(txData);
        rxSignal = Channel(txSignal);
        rxData = Receiver(rxSignal);

        count += (txData != rxData);
    }

    errorRate = (float) count / NUM_DATA;
    printf("Error rate = %.1f\n", errorRate);
    return 0;
}

int BinaryData()
{
    return rand() % 2;
}

float Transmitter(int txData)
{
    return ((txData == 1)? 1.0 : -1.0);
}

float Channel(float txSignal)
{
    return txSignal;
}

int Receiver(float rxSignal)
{
    return ((rxSignal > 0.0) ? 1 : 0);
}