void mpptIncCondutanceFunction(mpptParameters_t *mppt)
{
   if(mppt->mpptEnable == 1)
   {
       if(mppt->mpptFirst == 1)
       {
           mppt->VmmpOut      = mppt->pvVoltage - mppt->stepFirst;
           mppt->pvVoltageOld = mppt->pvVoltage;
           mppt->pvCurrentOld = mppt->pvCurrent;
           mppt->mpptFirst    = 0;
       }
       else
       {
           mppt->deltaV = mppt->pvVoltage - mppt->pvVoltageOld;
           mppt->deltaI = mppt->pvCurrent - mppt->pvCurrentOld;
           if(mppt->deltaV == 0)
           {
               if(mppt->deltaI != 0)
               {
                   mppt->VmmpOut = mppt->pvVoltage + ((mppt->deltaI > 0) ? mppt->stepSize : -mppt->stepSize);
               }
           }
           else
           {
               mppt->conductance = mppt->pvCurrent / mppt->pvVoltage;
               mppt->incrementalConductance = mppt->deltaI / mppt->deltaV;
               if(mppt->incrementalConductance != mppt->conductance)
               {
                   if(mppt->incrementalConductance > (-mppt->conductance))
                       mppt->VmmpOut = mppt->pvVoltage + mppt->stepSize;
                   else
                       mppt->VmmpOut = mppt->pvVoltage - mppt->stepSize;
               }
           }
           mppt->pvVoltageOld = mppt->pvVoltage;
           mppt->pvCurrentOld = mppt->pvCurrent;
       }
   }
}
