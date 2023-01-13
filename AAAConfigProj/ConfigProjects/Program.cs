//#define TEST_AESELECT
#define TEST_AEGENERATE
//#define TEST_AEINIT

using CgenMin.MacroProcesses;
using CodeGenerator.MacroProcesses.AESetups;
using CodeGenerator.ProblemHandler;
using System;
using System.Collections.Generic;


using System.IO;
using System.Linq;
using System.Text.RegularExpressions;


namespace testaertosproj
{
    class Program
    {

        static void Main(string[] args)
        {

             


            //=====================================================
            //AEGENERATE
            //=====================================================  
#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            if (args[0] == "aegenerate")
            {
#endif

#if (TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT) || (!TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT)
                string ProjectName = CodeGenerator.Program.GetAEProjectName();
                string ProjectTest = CodeGenerator.Program.GetAEProjectTestName();


                //generate the project.
                AEInitializing aEInitializing = new AEInitializing();
                var projectSelected = AEInitializing.GetProjectIfNameExists(ProjectName);
                CodeGenerator.Program.aeinitOptions aeinitOptions = new CodeGenerator.Program.aeinitOptions() { nameOfTheProject = ProjectName };
                //CodeGenerator.Program._aeinitProjectFileStructure(aeinitOptions, aEInitializing, projectSelected, projectSelected.DirectoryOfLibrary);

                aEInitializing.GenerateProject(ProjectName, ProjectTest);
#endif


#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            }
#endif



#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            else if (args[0] == "aeselect")
            {




                string projectNameSelection = "";
                string projectEXETestSelection = "";

                try
                {
                    projectNameSelection = args[1] == null ? "" : args[1];
                    projectEXETestSelection = args[2] == null ? "" : args[2];
                }
                catch (Exception)
                {

                }
#endif














            //=====================================================
            //AEselect
            //===================================================== 

#if (TEST_AESELECT && !TEST_AEGENERATE && !TEST_AEINIT)

            string projectNameSelection = "testprojectname";
            string projectEXETestSelection = "testname";
#endif

#if (TEST_AESELECT && !TEST_AEGENERATE && !TEST_AEINIT) || (!TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT)


                ProblemHandle prob = new ProblemHandle();

                //if projectName is null, return back a list of possible projects you can select
                if (projectNameSelection == null)
                {
                    string disp = "You did not provide projectNameSelection"; disp += "\n";
                    disp += "Here is a list of projects to choose from"; disp += "\n";
                    disp += GetProjectsDisplay();

                    Console.WriteLine(disp);
                    return;
                }


                //projectNameSelection and is valid project provided but not projectSelected
                var projectSelected = AEInitializing.GetProjectIfNameExists(projectNameSelection);
                if (projectNameSelection == null && projectSelected != null)
                {
                    string disp = $"{projectNameSelection} is valid but no tests selected "; disp += "\n";
                    disp += $"Here is a list of test from chosen project {projectNameSelection}"; disp += "\n";
                    disp += GetProjectTestsDisplay(projectSelected);
                    Console.WriteLine(disp);
                    return;
                }

                //projectNameSelection provided but is NOT valid
                if (projectSelected == null)
                {
                    string disp = $"No such project of name {projectNameSelection} exists."; disp += "\n";
                    disp += "Here is a list of projects to choose from"; disp += "\n";
                    disp += GetProjectsDisplay();
                    Console.WriteLine(disp);
                    return;
                }

                //projectNameSelection provided  and is valid but projectEXETestSelection is NOT valid
                string TestSelected = projectSelected.ListOfTests.FirstOrDefault(s => s == projectEXETestSelection);

                string dispp = projectEXETestSelection == null ? "You did not provide projectEXETestSelection" : ""; dispp += "\n";
                if (projectSelected != null && (TestSelected == null || string.IsNullOrWhiteSpace(TestSelected)))
                {
                    dispp += $"No such test of name {projectEXETestSelection} exists for project named {projectNameSelection} ."; dispp += "\n";
                    dispp += $"Here is a list of test from chosen project {projectNameSelection}"; dispp += "\n";
                    dispp += GetProjectTestsDisplay(projectSelected);
                    Console.WriteLine(dispp);
                    return;
                }
                projectEXETestSelection = TestSelected;



                //everything is valid from here, start the process of changing the project chosen
                //step1: set the AETarget.cmake file
                //step2: set the IntegTestPipeline.h file 
                //step3: init the project just in case
                //step4: generate AEConfig TODO

                AEInitializing aEInitializing = new AEInitializing();

                //step1: set the AETarget.cmake file
                aEInitializing.WriteFileContents_FromCGENMMFile_ToFullPath(
                    "AERTOS\\AETarget",
                    Path.Combine(@"C:/AERTOS/AERTOS", $"AETarget.cmake"),//
                    true, false,
                     new MacroVar() { MacroName = "ProjectName", VariableValue = projectSelected.Name },
                     new MacroVar() { MacroName = "ProjectDir", VariableValue = projectSelected.DirectoryOfLibrary },
                     new MacroVar() { MacroName = "TestChosen", VariableValue = TestSelected }
                     );

                //step2: set the IntegTestPipeline.h file
                aEInitializing.WriteFileContents_FromCGENMMFile_ToFullPath(
                    "AERTOS\\IntegTestPipeline",
                    Path.Combine(projectSelected.DirectoryOfLibrary, $"IntegTestPipeline.h"),
                    true, false,
                     new MacroVar() { MacroName = "ProjectName", VariableValue = projectSelected.Name }
                     );



                //step3: init the project just in case
                CodeGenerator.Program.aeinitOptions aeinitOptions = new CodeGenerator.Program.aeinitOptions() { nameOfTheProject = projectSelected.Name };
                CodeGenerator.Program._aeinitProjectFileStructure(aeinitOptions, aEInitializing, projectSelected, projectSelected.DirectoryOfLibrary);

#endif

#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            }
#endif









            //=====================================================
            //AEINIT
            //===================================================== 

#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            else if (args[0] == "aeinit")
            {

                string nameOfTheProject = "";
                string envIronDirectory = "";

                try
                {
                    nameOfTheProject = args[1] == null ? "" : args[1];
                    envIronDirectory = args[2] == null ? "" : args[2]; 
                }
                catch (Exception)
                {

                }
#endif

#if (TEST_AEINIT && !TEST_AEGENERATE && !TEST_AESELECT)

            string nameOfTheProject = "commonHalAOs";
            string envIronDirectory = @"C:/Users/hadi/Documents/AERTOSProjects/commonHalAOs";
#endif


#if (TEST_AEINIT && !TEST_AEGENERATE && !TEST_AESELECT) || (!TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT)

            ProblemHandle prob = new ProblemHandle();

                //check if a project already exists here.
                AEProject projAlreadyExists = AEInitializing.GetProjectIfDirExists(envIronDirectory);
                if (nameOfTheProject == null)
                {

                    if (projAlreadyExists == null)
                    {
                        prob.ThereisAProblem("You didnt provide a AEProject name and no project exists here yet. do that with \"aeinit <projectName>\"");
                    }

                    nameOfTheProject = projAlreadyExists.Name;


                }
                else if (nameOfTheProject != null)
                {
                    if (projAlreadyExists != null)
                    {
                        if (projAlreadyExists.Name != nameOfTheProject)
                        {
                            prob.ThereisAProblem($"There already exists a project here of different name {projAlreadyExists.Name}");
                        }

                    }


                }
            //check that the current name is not already in use by another project at a different directory
            if (AEInitializing.GetProjectIfNameExists(nameOfTheProject) != null)
            {
                var bla = AEInitializing.GetProjectIfNameExists(nameOfTheProject);
                prob.ThereisAProblem($"There already exists a project of name {bla.Name}, at directory, {bla.DirectoryOfLibrary}. choose another name.");
            }

            AEInitializing aEInitializing = new AEInitializing();


                if (projAlreadyExists == null)
                {

                    //just use the relative directory if in base directory
                    string basdir_ = AEProject.BaseAEDir.Replace("\\", "/");
                    string envIronDirectory_ = envIronDirectory.Replace("\\", "/");
                    //Console.WriteLine($"basdir_: {basdir_}");
                    //Console.WriteLine($"envIronDirectory_: {envIronDirectory_}");
                    //Console.WriteLine($"isSubDirOfPath(basdir_, envIronDirectory_): {isSubDirOfPath(basdir_, envIronDirectory_)}");
                    string DirOfProject = CodeGenerator.Program.isSubDirOfPath(basdir_, envIronDirectory_) ?
                        envIronDirectory_.Replace(basdir_ + "/", "") :
                        envIronDirectory_;



                    string PathToconfcs = Path.Combine(envIronDirectory, "conf");

                    Console.WriteLine($"creating { nameOfTheProject}.cs at directory  {DirOfProject}");
                    //create a .cs class file that will start the project type 
                    aEInitializing.WriteFileContents_FromCGENMMFile_ToFullPath(
                        "AERTOS\\AEProjectCS",
                        Path.Combine(PathToconfcs, $"{nameOfTheProject}.cs"),
                        false, false,
                         new MacroVar() { MacroName = "NameOfProject", VariableValue = nameOfTheProject },
                         new MacroVar() { MacroName = "DirOfProject", VariableValue = DirOfProject }
                         );


                }

                Console.WriteLine($"initing { nameOfTheProject}");
                CodeGenerator.Program.aeinitOptions opts = new CodeGenerator.Program.aeinitOptions() { nameOfTheProject = nameOfTheProject };
                CodeGenerator.Program._aeinitProjectFileStructure(opts, aEInitializing, projAlreadyExists, envIronDirectory);
                Console.WriteLine($"done initing { nameOfTheProject}");
#endif



#if !TEST_AEGENERATE && !TEST_AESELECT && !TEST_AEINIT
            }
#endif


            //Console.WriteLine("Hello World!");
        }





        static string GetProjectsDisplay()
        {
            string disp = "";
            foreach (var proj in AEInitializing.GetAllCurrentAEProjects())
            {
                disp += "=============================================================="; disp += "\n";
                disp += $"ProjectName: {proj.Name}"; disp += "\n";
                disp += $"ProjectDirectory: {proj.DirectoryOfLibrary}"; disp += "\n";
                disp += $"ProjectTestsToChoose: "; disp += "\n";
                foreach (var test in proj.ListOfTests)
                {
                    disp += $"  {test}"; disp += "\n";
                }
            }

            return disp;
        }

        static string GetProjectTestsDisplay(AEProject proj)
        {
            string disp = "";
            disp += "=============================================================="; disp += "\n";
            disp += $"ProjectName: {proj.Name}"; disp += "\n";
            disp += $"ProjectDirectory: {proj.DirectoryOfLibrary}"; disp += "\n";
            disp += $"ProjectTestsToChoose: "; disp += "\n";
            foreach (var test in proj.ListOfTests)
            {
                disp += $"  {test}"; disp += "\n";
            }

            return disp;
        }
    }




}
