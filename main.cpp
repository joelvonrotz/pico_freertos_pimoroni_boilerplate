#include "FreeRTOS.h"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/stellar_unicorn/stellar_unicorn.hpp"
#include "pico/stdlib.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

using namespace pimoroni;

PicoGraphics_PenRGB888 graphics(16, 16, nullptr);
StellarUnicorn stellar_unicorn;

BaseType_t res;
TaskHandle_t taskBorderBlinkyHandler;
TimerHandle_t timerHandle;

/* [TASKS] ------------------------------------ */
static void taskBorderBlinky(void *params) {
  (void)params;
  xTimerStart(timerHandle, pdMS_TO_TICKS(10));
  TickType_t xLastWakeTime = xTaskGetTickCount();
  graphics.set_clip(Rect(1,1,14,14));

  for (;;) {
    graphics.set_pen(60,60,60);
    graphics.rectangle(Rect(0,0,16,16));
    vTaskDelayUntil (&xLastWakeTime , pdMS_TO_TICKS(1000));
    graphics.set_pen(0,0,0);
    graphics.rectangle(Rect(0,0,16,16));
    vTaskDelayUntil (&xLastWakeTime , pdMS_TO_TICKS(1000));
  }
}

static void timerCallbackRefreshScreen(TimerHandle_t xTimer) {
  stellar_unicorn.update(&graphics);
}

int main() {
  stdio_init_all();

  stellar_unicorn.init();
  graphics.clear();

  timerHandle = xTimerCreate(
    NULL,
    pdMS_TO_TICKS(30),
    pdTRUE,
    NULL,
    timerCallbackRefreshScreen
  );

  res = xTaskCreate (taskBorderBlinky , /*function*/
    "Blinky",                     /* Kernel awareness name */
    500/ sizeof( StackType_t ),   /* stack size */
    (void *)NULL,                 /* task parameter */
    tskIDLE_PRIORITY +1,          /* priority */
    &taskBorderBlinkyHandler      /* handle */
  );

  if (res != pdPASS) {
    panic("task couldn't be created");  /* error handling here */
  }

  vTaskStartScheduler();
  while (true) {
  }
}