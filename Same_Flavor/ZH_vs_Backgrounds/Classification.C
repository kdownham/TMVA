//=====================================================================
//
// Macro used for the training of various BDTs for the WWZ to 
// 4 lepton analysis (CMS).
//
// This macro in particular trains BDTs targeting the opposite-flavor
// channel
//
//=====================================================================
//
// Author:
//      Keegan Downham, UC Santa Barbara
//
//=====================================================================

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

int Classification(TString weightName){

    // Load the TMVA library
    TMVA::Tools::Instance();

    // MVA methods to be trained + tested
    std::map<std::string,int> Use;

    // Boosted decision trees
    Use["BDT"]              = 0;
    Use["BDT_T200"]         = 0;
    Use["BDT_T400"]         = 0;
    Use["BDTG_D2"]          = 1;
    Use["BDTG_T400"]        = 1;
    Use["BDTG_T400_LR0p5"]  = 1;
    Use["BDTG_LR0p1"]       = 1;
    Use["BDTG_T200"]        = 1;
    Use["BDTG"]             = 1;
    Use["BDTG_LR0p1_D2"]    = 1;
    Use["BDTG_D1"]          = 1;
    Use["BDTG_LR0p1_D1"]    = 1;
    Use["BDTG_T400_LR0p1_D2"] = 1;
    Use["BDTG_T400_LR0p1_D1"] = 1;
    Use["BDTG_LR0p1_D2_NS10"]    = 1;
    Use["BDTG_LR0p1_D2_NS1"]    = 1;
    // TODO: create other BDT options with different hyperparameter options
    //=====================================================================
    // 
    // All options for BDTs are listed in table 25 of the TMVA user's guide:
    // 	    root.cern.ch/download/doc/tmva/TMVAUsersGuide.pdf
    //
    // Ideas:
    // 	    - Vary the number of trees 
    // 	    - Vary the tree depth
    // 	    - Vary min node size
    // 	    - Vary nCuts
    // 	    - Keep boost type limited to Gradient Boost and AdaBoost
    // 	    - Vary Beta away from 0.5 (only for AdaBoost)
    //
    //
    //=====================================================================

    std::cout << "===> Start TMVA 4-lepton classification" << std::endl;

    //=====================================================================
    // Preparing the input data
    //=====================================================================
    
    // Read the training and test data
    
    TString dir = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_020724_BDTUpdate/Run2/";

    TFile *input_signal(0);
    TString fname_signal = dir+"ZHWWZ.root";
    TFile *input_bkgd(0);
    TString fname_bkgd = dir+"BDT_Backgrounds_OF.root";

    // Open the files for signal and background
    input_signal = TFile::Open(fname_signal);
    input_bkgd = TFile::Open(fname_bkgd);

    std::cout << "--- WWZ -> 4 lepton classification using the following input files: " << std::endl;
    std::cout << "--- Signal: " << input_signal->GetName() << std::endl;
    std::cout << "--- Background: " << input_bkgd->GetName() << std::endl;

    // Specify the trees for training
    TTree *signalTrain = (TTree*)input_signal->Get("t_BDT_SF_train");
    TTree *signalTest  = (TTree*)input_signal->Get("t_BDT_SF_test");
    TTree *bkgdTrain   = (TTree*)input_bkgd->Get("t_BDT_SF_train");
    TTree *bkgdTest    = (TTree*)input_bkgd->Get("t_BDT_SF_test");

    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outfileName = weightName+".root";
    TFile* outputFile = TFile::Open("classification/"+outfileName,"RECREATE");

    // Create the TMVA factory object
    // Arguments:
    // 1). Base name of the weight files in the directory weight/
    // 2). Output file for the training results
    // 3). Options string (options can be suppressed by using !)
    
    TMVA::Factory *factory = new TMVA::Factory( weightName, outputFile,
						"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );   

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

    // Specify the input variables that will be used for the MVA training

    dataloader->AddVariable("m_ll", "m_{ll}", "GeV", 'F');
    dataloader->AddVariable("m_4l", "m_{4l}", "GeV", 'F');
    dataloader->AddVariable("dPhi_4Lep_MET", "#Delta#phi(4Lep,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_Zcand_MET", "#Delta#phi(Zcands,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_WW_MET", "#Delta#phi(Wcands,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_W1_MET", "#Delta#phi(l^{W1},p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_W2_MET", "#Delta#phi(l^{W2},p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dR_Wcands", "#Delta R(l^{W1},l^{W2})", "", 'F');
    dataloader->AddVariable("dR_Zcands", "#Delta R(l^{Z1},l^{Z2})", "", 'F');
    dataloader->AddVariable("dR_WW_Z", "#Delta R(Wcands,Zcands)", "", 'F');
    dataloader->AddVariable("MET", "p_{T}^{miss}", "GeV", 'F');
    dataloader->AddVariable("MT2", "M_{T2}", "GeV", 'F');
    dataloader->AddVariable("Pt4l", "p_{T}^{4l}", "GeV", 'F');
    dataloader->AddVariable("HT", "H_{T}", "GeV", 'F');
    dataloader->AddVariable("STLep", "#Sigma_{lep,MET} p_{T}", "GeV", 'F');
    dataloader->AddVariable("leading_Zcand_pt", "p_{T}^{Z1}", "GeV", 'F');
    dataloader->AddVariable("subleading_Zcand_pt", "p_{T}^{Z2}", "GeV", 'F');
    dataloader->AddVariable("leading_Wcand_pt", "p_{T}^{W1}", "GeV", 'F');
    dataloader->AddVariable("subleading_Wcand_pt", "p_{T}^{W2}", "GeV", 'F');
    dataloader->AddVariable("njets", "N_{jets}", "", 'F');
    dataloader->AddVariable("cos_helicity_X", "cos(#theta_{X})", "", 'F');
    dataloader->AddVariable("MT_leading_Wcand", "M_{T}^{W1}", "GeV", 'F');
    dataloader->AddVariable("MT_subleading_Wcand", "M_{T}^{W2}", "GeV", 'F');
    dataloader->AddVariable("MT_Wcands", "M_{T}^{Wcands}", "GeV", 'F');
    dataloader->AddVariable("MT_4Lep", "M_{T}^{4Lep}", "GeV", 'F');
    //dataloader->AddVariable("leading_jet_DeepFlav", "Leading Jet DeepFlav Score", "", 'F');
    dataloader->AddVariable("min_dR_W1_jet", "min(#Delta R(l^{W1},j))", "", 'F');
    dataloader->AddVariable("min_dR_W2_jet", "min(#Delta R(l^{W2},j))", "", 'F');

    // Specify the spectator variables that will not be included in the training
    dataloader->AddSpectator("leading_jet_pt", "leading jet p_{T}", "GeV", 'F');
    dataloader->AddSpectator("subleading_jet_pt", "subleading jet p_{T}", "GeV", 'F');
    dataloader->AddSpectator("leading_jet_DeepFlav", "Leading Jet DeepFlav Score", "", 'F');

    Double_t signalWeight = 1.0;
    Double_t bkgdWeight = 1.0;
 
    //=========================================================================
    //	Here is where we can add more background trees into our dataloader
    //  i.e.
    //  dataloader->AddBackgroundTree(bgtree1, weight1);
    //  dataloader->AddBackgroundTree(bgtree2, weight2);
    //  dataloader->AddBackgroundTree(bgtree3, weight3);
    //
    //  Note: the weights can be specified to reflect the relative fraction
    //  of background events from each process
    //
    //=========================================================================
    dataloader->AddSignalTree(signalTrain, signalWeight, TMVA::Types::kTraining);
    dataloader->AddSignalTree(signalTest,  signalWeight, TMVA::Types::kTesting );
    dataloader->AddBackgroundTree(bkgdTrain, bkgdWeight, TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(bkgdTest , bkgdWeight, TMVA::Types::kTesting );

    // Set individual event weights (point to the branch within the tree)
    // Signal
    dataloader->SetSignalWeightExpression("weight");
    // Background
    dataloader->SetBackgroundWeightExpression("weight");

    // Apply additional cuts on the signal and background samples (can be different)
    //TCut cut_all = "m_ll > -999 && dPhi_4Lep_MET > -999 && dPhi_Zcand_MET > -999 && dR_Wcands > -999 && dR_Zcands > -999 && MET > -999 && MT2 > -999 && Pt4l > -999 && STLepHad > -999 && leading_Zcand_pt > -999 && subleading_Zcand_pt > -999 && leading_Wcand_pt > -999 && subleading_Wcand_pt > -999";
    
    // Book MVA methods
    //================================================================================
    // Note about NormMode option:
    //      NormMode=NumEvents - N events in first class is equal to sum of all others
    //	    NormMode=EqualNumEvents - All classes have same # of effective events
    //================================================================================
    //dataloader->PrepareTrainingAndTestTree( cut_all, cut_all,
    //					  "nTrain_Signal=0:nTest_Signal=0:nTrain_Background=0:nTest_Background=0:SplitMode=Random:!V" );

    // Boosted Decision Trees (BDTs)
    if (Use["BDT"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=800:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=SDivSqrtSPlusB:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDT_T200"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT_T200",
                           "!H:!V:NTrees=200:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=SDivSqrtSPlusB:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDT_T400"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT_T400",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=SDivSqrtSPlusB:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );


    if (Use["BDTG"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:nCuts=20:MaxDepth=3:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_D2"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_D2",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:nCuts=20:MaxDepth=2:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_T400"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_T400",
                           "!H:!V:NTrees=400:MinNodeSize=5%:BoostType=Grad:nCuts=20:MaxDepth=3:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_T400_LR0p5"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_T400_LR0p5",
                           "!H:!V:NTrees=400:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.5:nCuts=20:MaxDepth=3:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_LR0p1"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_LR0p1",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=3:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_T200"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_T200",
                           "!H:!V:NTrees=200:MinNodeSize=5%:BoostType=Grad:nCuts=20:MaxDepth=3:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_LR0p1_D2"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_LR0p1_D2",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=2:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_D1"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_D1",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:nCuts=20:MaxDepth=1:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_LR0p1_D1"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_LR0p1_D1",
                           "!H:!V:NTrees=800:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=1:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_T400_LR0p1_D2"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_T400_LR0p1_D2",
                           "!H:!V:NTrees=400:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=2:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_T400_LR0p1_D1"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_T400_LR0p1_D1",
                           "!H:!V:NTrees=400:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=1:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_LR0p1_D2_NS10"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_LR0p1_D2_NS10",
                           "!H:!V:NTrees=800:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=2:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    if (Use["BDTG_LR0p1_D2_NS1"])
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG_LR0p1_D2_NS1",
                           "!H:!V:NTrees=800:MinNodeSize=1%:BoostType=Grad:Shrinkage=0.1:nCuts=20:MaxDepth=2:SeparationType=SDivSqrtSPlusB:NegWeightTreatment=IgnoreNegWeightsInTraining" );

    // Now I can tell the factory to train, test, and evaluate all MVA methods
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    // Save the output
    outputFile->Close();

    std::cout << "===> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "===> Classification_4Lep is done!" << std::endl;

    delete factory;
    delete dataloader;

    // Launch the GUI for the root macros
    if (!gROOT->IsBatch()) TMVA::TMVAGui( "classification/"+outfileName );

    return 0;

}
