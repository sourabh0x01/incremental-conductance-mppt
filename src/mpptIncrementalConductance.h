typedef struct
{
   float pvCurrent;
   float pvVoltage;
   float pvCurrentHigh;
   float pvCurrentLow;
   float pvVoltageHigh;
   float pvVoltageLow;
   float MaxVoltage;
   float MinVoltage;
   float stepSize;
   float VmmpOut;
   float conductance;
   float incrementalConductance;
   float deltaV;
   float deltaI;
   float pvVoltageOld;
   float pvCurrentOld;
   float stepFirst;
   float voc;
   float baseStepSize;
   uint8_t mpptEnable;
   uint8_t mpptFirst;
} mpptParameters_t;
void mpptIncCondutanceFunction(mpptParameters_t *mppt);
