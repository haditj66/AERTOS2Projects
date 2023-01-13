//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################



using CgenMin.MacroProcesses;
using commonAOsProject;
using commonHalAOsProject;
using System.Collections.Generic;

namespace blinkyProject
{

    public class blinky : AEProject
    {
		[AEEXETest]
        public void defaultTest()
        {
            AEClock clock1 = new AEClock("clock1", 1000);

            AESensor sineSensor = new AESensor("sineSensor", SensorResolution.Resolution16Bit,SensorDataType.int16_T);
            AESensor gpioSensor = new AESensor("sengpioSensorsor2", SensorResolution.Resolution16Bit,SensorDataType.int16_T);

            AverageSPB averageSPB = new AverageSPB("averageSPB", StyleOfSPB.EachSPBTask,  false, new SPBChannelUserDefinedCountBuffer(4));
            IfRightOnSPB ifRightOnSPB = new IfRightOnSPB("ifRightOnSPB", StyleOfSPB.EachSPBTask,  false);
             
            PWMDriverU pWMDriverU = new PWMDriverU("pWMDriverU",10,AEPriorities.MediumPriority, ifRightOnSPB);

            //linking ----------
            clock1.
                FlowIntoSensor(sineSensor, AEClock_PrescalerEnum.PRESCALER1)
               .FlowIntoSPB(averageSPB,SPBChannelNum.CH0,LinkTypeEnum.Copy);
            averageSPB.FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy);

            clock1.
                FlowIntoSensor(gpioSensor, AEClock_PrescalerEnum.PRESCALER4)
               .FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy);


             

        }

        protected override string _GetDirectoryOfLibrary()
        {
            return @"blinky"; 
        }

        protected override List<AEEvent> _GetEventsInLibrary()
        {
            return new List<AEEvent>() {
                
            };
        }

		protected override List<AEHal> _GetPeripheralsInLibrary()
        { 
            return new List<AEHal>() {
                PWMPERIPHERAL1.Init(Portenum.PortD, PinEnum.PIN12),
                GPIOPERIPHERAL1.Init(Portenum.PortA, PinEnum.PIN1)
            };
        }

        protected override List<AEProject> _GetLibrariesIDependOn()
        {
            return new List<AEProject>() {
            new commonAOs(),
            new commonHalAOs()
            };
        }
		
		protected override List<string> _GetAnyAdditionalIncludeDirs()
        {
            return new List<string>() { };
        }
		
		protected override List<string> _GetAnyAdditionalSRCDirs()
        {
            return new List<string>() {  };
        }
		
 
    }
	
	
	
}