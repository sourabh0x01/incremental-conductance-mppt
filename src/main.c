#include "ti_msp_dl_config.h"
#include "mpptIncrementalConductance.h"
mpptParameters_t mpptParameters;
volatile uint32_t pwmUpdateCounter = 0;
void initializeMPPT(void);
void readPVInputs(void);
void updatePWM(float refVoltage);
int main(void)
{
   SYSCFG_DL_init();                  // Init peripherals
   initializeMPPT();                 // Set up MPPT params
   NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
   DL_TimerG_startCounter(TIMER_0_INST);  // Start 100μs timer
   while (1)
   {
       __WFI();  // Enter low-power mode until next interrupt
   }
}

void TIMER_0_INST_IRQHandler(void)
{
   DL_TimerG_clearInterruptStatus(TIMER_0_INST);
   // 1. Read ADC
   readPVInputs();
   // 2. Run MPPT Algorithm
   mpptIncCondutanceFunction(&mpptParameters);
   // 3. Throttle PWM update to 1 Hz (10,000 samples)
   pwmUpdateCounter++;
   if (pwmUpdateCounter >= 10000)
   {
       updatePWM(mpptParameters.VmmpOut);
       pwmUpdateCounter = 0;
   }
}

void readPVInputs(void)
{
   float rawVoltage = DL_ADC12_readConversionResult(ADC_INST_VOLT);
   float rawCurrent = DL_ADC12_readConversionResult(ADC_INST_CURR);
   mpptParameters.pvVoltage = rawVoltage * VOLTAGE_SCALING_FACTOR;
   mpptParameters.pvCurrent = rawCurrent * CURRENT_SCALING_FACTOR;
}

void updatePWM(float refVoltage)
{
   float panelVoltage = mpptParameters.pvVoltage;
   float error = refVoltage - panelVoltage;
   float dutyAdjust = error * 0.05f;
   static float currentDuty = 0.5f;
   currentDuty += dutyAdjust;
   if (currentDuty > 0.95f) currentDuty = 0.95f;
   if (currentDuty < 0.05f) currentDuty = 0.05f;
   DL_TimerG_setCaptureCompareValue(PWM_INSTANCE, DL_TIMER_CC_1_INDEX, (uint32_t)(currentDuty * PWM_PERIOD_TICKS));
}
