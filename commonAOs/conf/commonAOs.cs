//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################



using CgenMin.MacroProcesses; 
using System;
using System.Collections.Generic;
using System.Linq;

namespace commonAOsProject
{





    public class GainFilter : AEFilter_ConstructorArg<float>
    {
        public GainFilter(float arg1Value)
            : base("gain", arg1Value, "commonAOs", 1)
        {
        }
    }

    public class AddOrSubFilter : AEFilter_ConstructorArg<float>
    {
        public AddOrSubFilter(float arg1Value)
            : base("valuetoSum", arg1Value, "commonAOs", 1)
        {
        }
    }


    public class AngularDerivativeDiscreteFilter : AEFilter_ConstructorArg<int, int>
    {
        public AngularDerivativeDiscreteFilter(int CountsPerRevolution, int MinimumAngularVelocitytobeConsideredZero)
            : base("CountsPerRevolution",CountsPerRevolution, "MinimumAngularVelocitytobeConsideredZero", MinimumAngularVelocitytobeConsideredZero, "commonAOs", 2)
        {

        }
    }

    public class DerivativeFilter : AEFilter
    {
        public DerivativeFilter()
            : base("commonAOs", 2)
        {

        }
    }   
    public class HighOrLowFilter :  AEFilter_ConstructorArg<int, int>
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="ThresholdOfAHigh">value threshold of high or low. </param>
        /// <param name="countsToHighOrLow">how many times does it have to be high or low consecutively to count as a high or low</param>
        public HighOrLowFilter(int ThresholdOfAHigh = 700, int countsToHighOrLow = 5)
            : base("ThresholdOfAHigh", ThresholdOfAHigh, "countsToHighOrLow", countsToHighOrLow, "commonAOs", 1)
        {

        }
    }

    public class MovingAverageFilter : AEFilter
    {
        public MovingAverageFilter(int numOfSamples)
            : base("commonAOs", numOfSamples)//, true)
        {

        }
    }
    public class AverageSPB : AESPBBase
    {
        public AverageSPB(string nameOfSPB, StyleOfSPB styleOfSPB,  bool isSubscribable, SPBChannelUserDefinedCountBuffer ch1)
            : base("commonAOs", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), ch1)
        {

        }
    }

    public class IfRightOnSPB : AESPBBase
    {
        public IfRightOnSPB(string nameOfSPB, StyleOfSPB styleOfSPB,  bool isSubscribable )
            : base("commonAOs", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), 
                  new SPBChannelLockedInCountBuffer(1),
                  new SPBChannelLockedInCountBuffer(1))
        {

        }
    }

    public class PID_SPB : AESPBBase
    {
        public PID_SPB(string nameOfSPB, StyleOfSPB styleOfSPB,   bool isSubscribable, SPBChannelUserDefinedChannelConsumptionSize ch1)
            : base("commonAOs", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), ch1)
        {

        }

        //uint8_t kpfrom0to100, uint8_t  kifrom0to100, uint8_t kdfrom0to100, 
        //float maxPossibleError, float maxpossibleRateOfChangeOfControlVariable, float desiredInput,
        //        float mapOutputTOMin = -100000, float mapOutputTOMax = 100000, float offsetFromZero = 0)
        protected override CppFunctionArgs SetcppConstructorArgs() 
        {
            CppFunctionArgs ret = new CppFunctionArgs(
                new CppFunctionArg(CppTypeEnum.uint8_t, "kpfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kifrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kdfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxPossibleError", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxpossibleRateOfChangeOfControlVariable", false),
                new CppFunctionArg(CppTypeEnum.float_t, "desiredInput", false),
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMin", false, "-100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMax", false, "100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "offsetFromZero", false, "0")
                );
            return ret;
        }
    }


    
    public class PID_WithDesiredInputAsChannel_SPB : AESPBBase
    {
        /// <summary>
        /// first channel is the input. Second channel is the desired input
        /// </summary>
        /// <param name="nameOfSPB"></param>
        /// <param name="styleOfSPB"></param>
        /// <param name="isSubscribable"></param>
        public PID_WithDesiredInputAsChannel_SPB(string nameOfSPB, StyleOfSPB styleOfSPB, bool isSubscribable )
            : base("commonAOs", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), 
                  new SPBChannelLockedInCountBuffer(1),
                  new SPBChannelLockedInCountBuffer(1))
        {

        }

 

        //uint8_t kpfrom0to100, uint8_t  kifrom0to100, uint8_t kdfrom0to100, 
        //float maxPossibleError, float maxpossibleRateOfChangeOfControlVariable, float desiredInput,
        //        float mapOutputTOMin = -100000, float mapOutputTOMax = 100000, float offsetFromZero = 0)
        protected override CppFunctionArgs SetcppConstructorArgs()
        {
            CppFunctionArgs ret = new CppFunctionArgs(
                new CppFunctionArg(CppTypeEnum.uint8_t, "kpfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kifrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kdfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxPossibleError", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxpossibleRateOfChangeOfControlVariable", false), 
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMin", false, "-100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMax", false, "100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "offsetFromZero", false, "0")
                );
            return ret;
        }
    }

    public class ThreeDimensionalVectorSPB : AESPBBase
    {
        public ThreeDimensionalVectorSPB(string instanceName, StyleOfSPB styleOfSPB, bool isSubscribable )
            : base("commonAOs", instanceName, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(4, false), 
                  new SPBChannelLockedInCountBuffer(1),
                  new SPBChannelLockedInCountBuffer(1),
                  new SPBChannelLockedInCountBuffer(1))
        {

        }   
    }

    public class IfAllTrueSPB : AESPBBase_VariableNumOfChannels_AllSameCountBufferSizes
    {
        public IfAllTrueSPB( string instanceName, StyleOfSPB styleOfSPB,  bool isSubscribable,   int numOfChannels) 
            : base("commonAOs", instanceName, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), numOfChannels, 1)
        {
        }
         
    }







    public class commonAOs : AEProject
    {
		[AEEXETest]//====================================================================================================================================================================================
        public void defaultTest()
        {
            AddOrSubFilter addOrSubFilter = new AddOrSubFilter(3);
            AEClock aEClock = new AEClock("clock1", 1000 );
            AESensor sensor1 = new AESensor("sensor1", SensorResolution.Resolution12Bit, 0, 100);
            aEClock.FlowIntoSensor(sensor1, AEClock_PrescalerEnum.PRESCALER1)
                .FlowIntoFilter(new AngularDerivativeDiscreteFilter(20, 10))
                .FlowIntoFilter(new MovingAverageFilter(5));
            //AngularDerivativeDiscreteFilter angularDerivativeDiscreteFilter = new AngularDerivativeDiscreteFilter(20);
            DerivativeFilter derivativeFilter = new DerivativeFilter();
            HighOrLowFilter highorlow = new HighOrLowFilter();

            IfRightOnSPB ifRightOnSPB = new IfRightOnSPB("ifRightOnSPB", StyleOfSPB.EachSPBTask, false);

            AverageSPB averageSPB = new AverageSPB("averageSPB", StyleOfSPB.EachSPBTask,   false, new SPBChannelUserDefinedCountBuffer(10));
            PID_SPB pidSPB = new PID_SPB("pidSPB", StyleOfSPB.EachSPBTask,   false, new SPBChannelUserDefinedChannelConsumptionSize(1));
            //PID_WithDesiredInputAsChannel_SPB pidSPB = new PID_WithDesiredInputAsChannel_SPB("pidSPB", StyleOfSPB.EachSPBTask,   false   );
            ThreeDimensionalVectorSPB threeDimensionalVectorSPB = new ThreeDimensionalVectorSPB("threeDimensionalVectorSPB", StyleOfSPB.EachSPBTask, false);
            IfAllTrueSPB ifAllTrueSPB = new IfAllTrueSPB("ifAllTrueSPB",StyleOfSPB.EachSPBTask,false, 3);


            sensor1.FlowIntoSPB(averageSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy)
                .FlowIntoSPB(pidSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy)
                //.FlowIntoSPB(pidSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy)
                .FlowIntoSPB(threeDimensionalVectorSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy)
                .FlowIntoSPB(threeDimensionalVectorSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy)
                .FlowIntoSPB(threeDimensionalVectorSPB, SPBChannelNum.CH2, LinkTypeEnum.Copy)

                .FlowIntoSPB(ifAllTrueSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy)
                .FlowIntoSPB(ifAllTrueSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy)
                .FlowIntoSPB(ifAllTrueSPB, SPBChannelNum.CH2, LinkTypeEnum.Copy);

            //sensor1.FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy)
            //    .FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy);

            //MovingAverageFilter movingAverageFilter = new MovingAverageFilter(5);
        }

        protected override string _GetDirectoryOfLibrary()
        {
            return @"commonAOs"; //C:\Users\hadi\Documents\AERTOSProjects\
        }

        protected override List<AEEvent> _GetEventsInLibrary()
        {
            return new List<AEEvent>() { };
        }

		protected override List<AEHal> _GetPeripheralsInLibrary()
        {
		//ADCPERIPHERAL1_CH1.Init(Portenum.PortB, PinEnum.PIN0)
            return new List<AEHal>() {
                
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
            return new List<string>() { };
        }

    }
	
	
	
}