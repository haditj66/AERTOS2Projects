//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################



using CgenMin.MacroProcesses;
using commonAOsProject;
using commonHalAOsProject;
using System;
using System.Collections.Generic;

namespace MotorDriverEncoderProject
{



    class EncoderPosition_SPB : AESPBBase
    {
        public EncoderPosition_SPB(string nameOfSPB, StyleOfSPB styleOfSPB, bool isSubscribable)
            : base("MotorDriverEncoder", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false),
                  new SPBChannelLockedInCountBuffer(1),
                  new SPBChannelLockedInCountBuffer(1)
                  )
        {
        }

        protected override CppFunctionArgs SetcppConstructorArgs()
        {
            CppFunctionArgs ret = new CppFunctionArgs(
                new CppFunctionArg(CppTypeEnum.int16_t, "currentPosition", false),
                new CppFunctionArg(CppTypeEnum.bool_t, "reverseCount", false, "false")
                );

            return ret;
        }
    }



    class LoopTest : AELoopObject
    {
        public LoopTest( string instanceNameOfloopObject   ) 
            : base("MotorDriverEncoder", instanceNameOfloopObject, AEPriorities.MediumPriority, 100, null)
        {
        }
    }




    class MotorDriverSpeedControllerTDU : AEUtilityService
    {
        public MotorDriverSpeedControllerTDU(string instanceNameOfTDU, int serviceBuffersize, AEPriorities priority , IADC adcForOpticalSensor1, IADC adcForOpticalSensor2, IPWM pwmForMotorControl, IGPIO gpioToChangeDirections ,  int countsPerRevolution = 20, int MinimumAngularVelocitytobeConsideredZero = 10, float MaxDeltaPWMPerSec = 20)
            : base("MotorDriverEncoder", instanceNameOfTDU, priority, serviceBuffersize,
                  new CppFunctionArgs(
                      new CppFunctionArg("AEPWM*", "pwmPeripheral", false),
                      new CppFunctionArg("AEGPIOOutput*", "gpiotoChangeDirections", false),
                      new CppFunctionArg(CppTypeEnum.int32_t, "DesiredPosition"),
                      new CppFunctionArg(CppTypeEnum.float_t, "MaxDeltaPWMPerSec", false, "20")
                      
                        ),
                  new ActionRequest("MoveToAngularPositionWithSpeed", ServiceType.TDU, "bool", "int16_t","StepCountToTurnTo", "float", "speedToTurnAt", "bool", "withRamping"),
                   new ActionRequest("MoveAtSpeed", ServiceType.TDU, "bool", "float", "speedToTurnAt", "bool", "withRamping")
                  )
        {

            AEClock aEClock = new AEClock("clock1", 1000);

            //two optical sensors from an adc
            AESensor opticalsensor1 = new AESensor("opticalsensor1", adcForOpticalSensor1, 0, 100);
            AESensor opticalsensor2 = new AESensor("opticalsensor2", adcForOpticalSensor2, 0, 100);

            EncoderPosition_SPB encoderPosition_SPB = new EncoderPosition_SPB("encoderPosition_SPB",StyleOfSPB.ChainOfSPBsFromInterrupt, true);

            //two pids. one for angular position, the other is for angular velocity
            PID_SPB angularPositionPID = new PID_SPB("angularPositionPID", StyleOfSPB.ChainOfSPBsFromInterrupt, true, new SPBChannelUserDefinedChannelConsumptionSize(1));
            PID_WithDesiredInputAsChannel_SPB angularVelocityPID = new PID_WithDesiredInputAsChannel_SPB("angularVelocityPID", StyleOfSPB.ChainOfSPBsFromInterrupt, true);

            aEClock.FlowIntoSensor(opticalsensor1, AEClock_PrescalerEnum.PRESCALER1)
                .FlowIntoFilter(new HighOrLowFilter())
                .FlowIntoSPB(encoderPosition_SPB,SPBChannelNum.CH0, LinkTypeEnum.Copy);
            aEClock.FlowIntoSensor(opticalsensor2, AEClock_PrescalerEnum.PRESCALER1)
                .FlowIntoFilter(new HighOrLowFilter())
                .FlowIntoSPB(encoderPosition_SPB, SPBChannelNum.CH1, LinkTypeEnum.Copy);

            var discreteFilter =
            encoderPosition_SPB.FlowIntoFilter(new AngularDerivativeDiscreteFilter(countsPerRevolution, MinimumAngularVelocitytobeConsideredZero));
            discreteFilter.FlowIntoSPB(angularVelocityPID, SPBChannelNum.CH0, LinkTypeEnum.Copy);

            encoderPosition_SPB.FlowIntoSPB(angularPositionPID, SPBChannelNum.CH0, LinkTypeEnum.Copy);
                angularPositionPID.FlowIntoSPB(angularVelocityPID, SPBChannelNum.CH1, LinkTypeEnum.Copy); ;

            angularVelocityPID.FlowIntoTDU(this);
            //subscribe to current position
            this.SubscribeToSPB(encoderPosition_SPB, "CurrentPosition", 0);

        }

    }


    public class MotorDriverEncoder : AEProject
    { 

        
        
        [AEEXETest]
        public void defaultTest()
        {

            MotorDriverSpeedControllerTDU motorDriverSpeedControllerTDU = new MotorDriverSpeedControllerTDU
                ("motorDriverSpeedControllerTDU",10, AEPriorities.MediumPriority, ADCPERIPHERAL1_CH1.Instance, ADCPERIPHERAL1_CH2.Instance, PWMPERIPHERAL1.Instance, GPIOPERIPHERAL1.Instance);


            LoopTest loopTest = new LoopTest("looptest");

            //AEClock aEClock = new AEClock("clock1",100);
            //AESensor aESensor = new AESensor("sens1", SensorResolution.Resolution16Bit);

            //EncoderPosition_SPB encoderPosition_SPB = new EncoderPosition_SPB("encoderPosition_SPB", StyleOfSPB.EachSPBTask,false);

            //aEClock.FlowIntoSensor(aESensor, AEClock_PrescalerEnum.PRESCALER1)
            //    .FlowIntoSPB(encoderPosition_SPB,SPBChannelNum.CH0, LinkTypeEnum.Copy)
            //    .FlowIntoSPB(encoderPosition_SPB,SPBChannelNum.CH1, LinkTypeEnum.Copy);
        }

        protected override string _GetDirectoryOfLibrary()
        {
            return @"MotorDriverEncoder"; 
        }

        protected override List<AEEvent> _GetEventsInLibrary()
        {
            return new List<AEEvent>() { };
        }

		protected override List<AEHal> _GetPeripheralsInLibrary()
        {
            //ADCPERIPHERAL1_CH1.Init(Portenum.PortB, PinEnum.PIN0)
            return new List<AEHal>() {
                ADCPERIPHERAL1_CH1.Init(Portenum.PortB, PinEnum.PIN0),
                ADCPERIPHERAL1_CH2.Init(Portenum.PortA, PinEnum.PIN2),
                PWMPERIPHERAL1.Init(Portenum.PortD, PinEnum.PIN12),
                GPIOPERIPHERAL1.Init(Portenum.PortB, PinEnum.PIN7)
            };
        }

        protected override List<AEProject> _GetLibrariesIDependOn()
        {
            return new List<AEProject>() { new commonAOs(),
            new commonHalAOs()};
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