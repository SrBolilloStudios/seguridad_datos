#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.delay(2000); // Espera de reconocimiento
  
  // Mantenemos presionada la tecla ALT izquierda sin soltarla
  // 0 indica que no enviamos una tecla normal, solo el modificador
  DigiKeyboard.sendKeyPress(0, MOD_ALT_LEFT);

  // El Digispark ya tiene un retraso inicial de ~5 segundos por el bootloader .
  // Si quieres 5 segundos adicionales de espera tras ese arranque:
  DigiKeyboard.delay(5000); 

  // Inicializar el teclado
  DigiKeyboard.sendKeyStroke(0);

  // 1. Abrir el cuadro "Ejecutar" (Win + R)
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);

  // 2. Escribir el comando de reinicio inmediato
  // /r = restart, /t 0 = tiempo de espera cero
  DigiKeyboard.print(F("shutdown /r /t 0"));

  // 3. Presionar Enter
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
}

void loop() {
  // El bucle vacío mantiene al procesador ocupado, pero la tecla 
  // seguirá enviándose como "presionada" por el bus USB.
}