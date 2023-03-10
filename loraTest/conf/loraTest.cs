//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################



using CgenMin.MacroProcesses;
using System.Collections.Generic;

namespace loraTestProject
{
    
    public class LoraMsgReceived  : AEEventEVT<LoraMsgReceived>
    {
        public LoraMsgReceived() :
            base("LoraMsgReceived",
            "int16_t sendingLoraAddress;", "int8_t payloadsize;", "char payload[200];"
            )
        { }
    }

    public class LoraCommandResponded : AEEventSignal<LoraCommandResponded>
    {
        public LoraCommandResponded() :
            base("LoraCommandResponded",
            ""
            )
        { }
    }

    public class LoopObjectTestlora : AELoopObject
    {
        public LoopObjectTestlora(string instanceName, AEPriorities priority, int freqOfLoop)
            : base("loraTest", instanceName, priority, freqOfLoop, null)
        {

        }
    }


    class RYLR896_U : AEUtilityService
    {
        public RYLR896_U(string instanceNameOfTDU, int serviceBuffersize, AEPriorities priority )
            : base("loraTest", instanceNameOfTDU, priority, serviceBuffersize,
                  new CppFunctionArgs(
                      new CppFunctionArg("RYLR896Driver*", "rYLR896Driver", false) 
                        ),
                  new ActionRequest("SendData", ServiceType.TDU, "bool", "int16_t", "addressOfLoraModToSendTo", "char*", "dataToSend", "int8_t", "payloadSize" )
                  )
        { 
        }

    }

    public class loraTest : AEProject
    {
		[AEEXETest]
        public void defaultTest()
        {
            AEClock aEClock = new AEClock("clock1", 200);
            LoopObjectTestlora loopObjectTestlora = new LoopObjectTestlora("loopObjectTestlora", AEPriorities.MediumPriority, 1);
             
            RYLR896_U rYLR896_U = new RYLR896_U("rYLR896_U", 5, AEPriorities.MediumPriority);

            aEClock.FlowIntoTDU(rYLR896_U, AEClock_PrescalerEnum.PRESCALER1);
        }

        protected override string _GetDirectoryOfLibrary()
        {
            return @"loraTest"; 
        }

        protected override List<AEEvent> _GetEventsInLibrary()
        {
            return new List<AEEvent>() { 
                LoraMsgReceived.Init(3),
                LoraCommandResponded.Init(10)

            };
        }
         
         
        protected override List<AEHal> _GetPeripheralsInLibrary()
        {
		//ADCPERIPHERAL1_CH1.Init(Portenum.PortB, PinEnum.PIN0)
            return new List<AEHal>() {
                UARTPERIPHERAL2.Init(BaudRatesEnum.T_115200,35,Portenum.PortA, PinEnum.PIN2, Portenum.PortA, PinEnum.PIN3)
            };
        }

        protected override List<AEProject> _GetLibrariesIDependOn()
        {
            return new List<AEProject>() { };
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