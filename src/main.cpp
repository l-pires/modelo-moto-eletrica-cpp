#include <stdio.h>

#include "Battery.hpp"
#include "ETB.hpp"
#include "Motorcycle.hpp"

void printMotorcycle(Motorcycle moto) {
  printf(
    "Motorcycle plate: %s\n"
    "Speed: %.2f\n",
    moto.getPlate(), moto.getSpeed()
  );
  if(moto.getBattery() == NULL) {
    printf(
      "Attached battery UID: NONE\n"
      "Motorcycle battery SoC: %.2f\n",
      0.0 
    );
  } else {
    printf(
      "Attached battery UID: %lld\n"
      "Motorcycle battery SoC: %.2f\n",
      moto.getBattery()->getUid(),
      moto.getBattery()->getSoc()
    );
  }
}

void printETB(ETB etb) {
  printf("ETB ID: %ld\n", etb.getUid());
  for(int i = 0; i < STORAGE_CAPACITY; i++) {
    printf("CP %d [ ", i + 1);
    if(etb.isEmpty(i)) {
      printf(
        "battery UID NONE | "
        "battery SoC NONE | "
        "charging: NO ]\n"
      );
    } else {
      Battery b = *etb.getBattery(i);
      printf(
        "battery UID %lld | "
        "battery SoC %.2f | ",
        b.getUid(), b.getSoc()
      );
      if(etb.isCharging(i))
        printf("charging: YES ]\n");
      else
        printf("charging: NO ]\n");
    }
  }
}

void printReport(int time, Motorcycle moto, ETB etb) {
  printf(
    "< Tempo: %dmin %ds >\n\n",
    time / 60, time % 60
  );
  printMotorcycle(moto);
  printf("\n");
  printETB(etb);
  printf("______________________________________________________________\n\n");
}

void cycle(int *time, int acceleration_time, 
            int brake_time, Motorcycle *moto, ETB *etb) {
  /* Realiza um ciclo de simulação da forma:
   * Aceleração por 'acceleration_time' segundos;
   * Frenagem de 'brake_time' segundos;
   */
  moto->accelerate();
  for(int t = 0; t < acceleration_time; t++, (*time)++) {
    moto->update();
    etb->update();
    if((*time) % 10 == 0) {
      printReport(*time, *moto, *etb);
    }
  }
  moto->startBrake();
  for(int t = 0; t < brake_time; t++, (*time)++) {
    moto->update();
    etb->update();
    if((*time) % 10 == 0) {
      printReport(*time, *moto, *etb);
    }
  }
  moto->stopBrake();
}

int main() {
  // Setup
  Motorcycle moto("XXX0000");
  Battery b0(0, 85.0, &moto);
  moto.attach(&b0);

  ETB etb(0xFF);
  Battery b[6];
  for(int i = 0; i < 6; i++) {
    b[i].setUid(i + 1);
    b[i].attach(&etb);
    etb.attach(i, b + i);
    etb.startCharging(i);
  }
  etb.getBattery(0)->charge(100.0);
  etb.getBattery(1)->charge(100.0);
  etb.getBattery(2)->charge(100.0);
  etb.getBattery(3)->charge(70.0);
  etb.getBattery(4)->charge(60.0);
  etb.getBattery(5)->charge(50.0);

  // Simulação
  int time = 0;
  printReport(time, moto, etb);

  moto.turnOn();
  time++;

  /** 6 ciclos de:
   *    - Acelera por 3 minutos;
   *    - Freia por 10 segundos;
   */
  for(int i = 0; i < 6; i++) {
    cycle(&time, 3 * 60, 10, &moto, &etb);
  }

  /** 4 ciclos de:
   *    - Acelera por 2 minutos;
   *    - Freia por 12 segundos;
   */
  for(int i = 0; i < 4; i++) {
    cycle(&time, 2 * 60, 12, &moto, &etb);
  }

  /** 1 ciclo de:
   *    - Acelera por 1 minuto e 40 segundos;
   *    - Freia por 32 segundos;
   */
  cycle(&time, 100, 31, &moto, &etb);

  // Simulando o minuto 30
  moto.turnOff();
  moto.update();
  etb.update();
  // Bateria adicionada ao ETB imediatamente
  Battery * tmp = moto.detach();
  etb.attach(6, tmp);
  etb.startCharging(6);
  // Report do minuto 30
  printReport(time, moto, etb);
  time++;

  // 10 segundos para a troca de bateria
  for(int t = 0; t < 10; t++, time++) {
    moto.update();
    etb.update();
    if(time % 10 == 0) {
      // Tempo 30 minutos e 10 segundos
      // Bateria adicionada a moto imediatamente
      Battery * tmp = etb.detach(0);
      moto.attach(tmp);

      printReport(time, moto, etb);
    }
  }

  // Mais 50 segundos de simulação
  for(int t = 0; t < 50; t++, time++) {
    moto.update();
    etb.update();
    if(time % 10 == 0) {
      printReport(time, moto, etb);
    }
  }

  return 0;
}
