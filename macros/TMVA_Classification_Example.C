///////////////////////////////////////////////////
//
// Example code to run the TMVA Training phase
// using a BDT using basic CMS data
//
///////////////////////////////////////////////////
//
// Author:
//	Keegan Downham, UC Santa Barbara
//
///////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVA_Classification_Example(bool debug = true){

    // Need to add lines here for the loading of the shared libTMVA
    // 
    
    if (debug) std::cout << "Debug 1" << std::endl;    

    // Load the library
    TMVA::Tools::Instance();

    if (debug) std::cout << "Debug 2" << std::endl;

    // Default MVA methods to be trained + tested
    std::map<std::string,int> Use;

    // Cut optimization
    Use["Cuts"]		   = 0;
    Use["CutsD"]	   = 0;
    Use["CutsPCA"]	   = 0;
    Use["CutsGA"]	   = 0;
    Use["CutsSA"]	   = 0;
    //
    // Boosted Decision Trees
    Use["BDT"]		   = 1; // uses Adaptive Boost
    Use["BDTG"]		   = 0; // uses Gradient Boost
    //Use["BDTB"]		   = 0; // uses Bagging
    //Use["BDTD"]		   = 0; // decorrelation + Adaptive Boost
    //Use["BDTF"]		   = 0; // allow usage of fisher discriminant for node splitting
    // -----------------------------------------------------------------

    std::cout << "==> Start TMVA Classification Example" << std::endl;


    // Here is where I start to prepare the input data

    // Read training and test data
    TFile *input_Sig(0);
    TString fname_Sig = "/ceph/cms/store/user/kdownham/VVVAnalysis/051723/WWZJetsTo4L2Nu_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_3LepTau_4Lep_051723/output_1.root";
    TFile *input_Bkgd(0);
    TString fname_Bkgd = "/ceph/cms/store/user/kdownham/VVVAnalysis/051723/ZZTo4L_TuneCP5_13TeV_powheg_pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_3LepTau_4Lep_051723/output_101.root";
    
    input_Sig = TFile::Open( fname_Sig );
    input_Bkgd = TFile::Open( fname_Bkgd );

    std::cout << "--- Example TMVA classification using the following input files: " << std::endl;
    std::cout << "--- Signal: " << input_Sig->GetName() << std::endl;
    std::cout << "--- Background: " << input_Bkgd->GetName() << std::endl;

    if (debug) std::cout << "Debug 3" << std::endl;

    // Specify the trees for training
    TTree *signalTree    = (TTree*)input_Sig->Get("t");   
    TTree *background    = (TTree*)input_Bkgd->Get("t");      

    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outputName( "WWZ_ZZ_Example.root" ); 
    TFile* outputFile = TFile::Open( outputName, "RECREATE" ); 
 
    if (debug) std::cout << "Debug 4" << std::endl;

    // Create the TMVA factory object
    // Arguments:
    // 1). Base name of the weight files in the directory weight/
    // 2). Output file for the training results
    // 3). Options string (options can be suppressed by using !)

    TMVA::Factory *factory = new TMVA::Factory( "TMVA_Classification_Example", outputFile, 
						"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

    if (debug) std::cout << "Debug 5" << std::endl;

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

    // Specify the input variables that will be used for the MVA training
    // Variable expressions are allowed (i.e. var3 = 0.5*(var1+var2))

    dataloader->AddVariable( "Var_4LepMET_mt2_PuppiMET", "MT2", "GeV", 'F' );
    dataloader->AddVariable( "Var_4LepMET_other_mll", "m_{ll}", "GeV", 'F' );

    Double_t signalWeight = 1.0;
    Double_t bkgdWeight = 1.0;

    dataloader->AddSignalTree(signalTree, signalWeight);
    dataloader->AddBackgroundTree(background, bkgdWeight);
    
    // Set individual event weights ( point to the branch within the tree )
    // For signal
    dataloader->SetSignalWeightExpression("Var_4LepMET_scaleLumi*Var_4LepMET_intLumi");
    // For background
    dataloader->SetBackgroundWeightExpression("Var_4LepMET_scaleLumi*Var_4LepMET_intLumi");
   
    // Apply additional cuts on the signal and background samples (can be different)
    TCut mycut_sig = "Var_4LepMET_mt2_PuppiMET > -999 && Var_4LepMET_other_mll > -999"; // For example: TCut mycut_sig = "Var_4LepMET_emuChannel = true";
    TCut mycut_bkgd = ""; 

    if (debug) std::cout << "Debug 6" << std::endl;

    // Book MVA methods
    dataloader->PrepareTrainingAndTestTree( mycut_sig, mycut_sig,
					  "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   
    // Cut optimization
    if (Use["Cuts"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=2000:VarProp=FSmart" );

   if (debug) std::cout << "Debug 7" << std::endl;

   if (Use["CutsD"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=2000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (debug) std::cout << "Debug 8" << std::endl;

   if (Use["CutsPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=2000:VarProp=FSmart:VarTransform=PCA" );

   if (debug) std::cout << "Debug 9" << std::endl;

   if (Use["CutsGA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (debug) std::cout << "Debug 10" << std::endl;

   if (Use["CutsSA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=1500:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );   

   if (debug) std::cout << "Debug 11" << std::endl;

   // Boosted Decision Trees (BDTs)
   if (Use["BDT"]) // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=400:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (debug) std::cout << "Debug 12" << std::endl;

   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=10:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

   // Now I can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events   
   if (debug) std::cout << "Debug 13" << std::endl;
   factory->TrainAllMethods();

   // Evaluate all MVAs using the set of test events
   if (debug) std::cout << "Debug 14" << std::endl;
   factory->TestAllMethods();

   // Evaluate and compare performance of all configured MVAs
   if (debug) std::cout << "Debug 15" << std::endl;
   factory->EvaluateAllMethods();

   // --------------------------------------------
   //
   // Save the output
   outputFile->Close();  

   std::cout << "===> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "===> TMVA_Classification_Example is done!" << std::endl;

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outputName );

   return 0;
}
