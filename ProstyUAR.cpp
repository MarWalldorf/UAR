#include "ProstyUAR.h"
#include "RegulatorPID.h" // Tutaj potrzebujemy pełnej definicji PID

ProstyUAR::ProstyUAR(ModelARX& arx, RegulatorPID& pid)
    : model(arx), regulator(pid), poprzednie_y(0.0)
{
}

double ProstyUAR::symuluj(double w) {
    // 1. Oblicz uchyb (wartość zadana - wyjście z poprzedniego kroku)
    double e = w - poprzednie_y;

    // 2. Oblicz sterowanie z regulatora (zakładamy dt = 1.0 dla symulacji dyskretnej)
    // Używamy przeciążonej metody symuluj(e) z dodanego adaptera w RegulatorPID
    double u = regulator.symuluj(e);

    // 3. Symuluj obiekt
    double y = model.symuluj(u);

    // 4. Zapamiętaj wyjście dla następnego kroku
    poprzednie_y = y;

    return y;
}
