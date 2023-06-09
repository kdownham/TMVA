//=====================================================================
//
// Macro used for the training of various BDTs for the WWZ to 
// 4 lepton analysis (CMS).
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

int Classification_4Lep(){

    // Load the TMVA library
    TMVA::Tools::Instance();

    // MVA methods to be trained + tested
    std::map<std::string,int> Use;

    // Boosted decision trees
    Use["BDT"]             = 1; // uses Adaptive Boost
    Use["BDTG"]		   = 1; // uses Gradient Boost
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
    
    TString dir = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_BDT_tree/Run2/";

    TFile *input_signal(0);
    TString fname_signal = dir+"WWZ.root";
    TFile *input_ZZ(0);
    TString fname_ZZ = dir+"ZZ.root";
    TFile *input_TTZ(0);
    TString fname_TTZ = dir+"TTZ.root";
    TFile *input_WZ(0);
    TString fname_WZ = dir+"WZ.root";
    TFile *input_Higgs(0);
    TString fname_Higgs = dir+"Higgs.root";
    TFile *input_Other(0);
    TString fname_Other = dir+"Other.root";

    // Open the files for signal and background
    input_signal = TFile::Open(fname_signal);
    input_ZZ = TFile::Open(fname_ZZ);
    input_TTZ = TFile::Open(fname_TTZ);
    input_WZ = TFile::Open(fname_WZ);     
    input_Higgs = TFile::Open(fname_Higgs);
    input_Other = TFile::Open(fname_Other);

    std::cout << "--- WWZ -> 4 lepton classification using the following input files: " << std::endl;
    std::cout << "--- Signal: " << input_signal->GetName() << std::endl;
    std::cout << "--- ZZ: " << input_ZZ->GetName() << std::endl;
    std::cout << "--- TTZ: " << input_TTZ->GetName() << std::endl;
    std::cout << "--- WZ: " << input_WZ->GetName() << std::endl;
    std::cout << "--- Higgs: " << input_Higgs->GetName() << std::endl;
    std::cout << "--- Other: " << input_Other->GetName() << std::endl;

    // Specify the trees for training
    TTree *signalTree = (TTree*)input_signal->Get("t_BDT");
    TTree *ZZTree = (TTree*)input_ZZ->Get("t_BDT");
    TTree *TTZTree = (TTree*)input_TTZ->Get("t_BDT");
    TTree *WZTree = (TTree*)input_WZ->Get("t_BDT");
    TTree *HiggsTree = (TTree*)input_Higgs->Get("t_BDT");
    TTree *OtherTree = (TTree*)input_Other->Get("t_BDT");

    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outputName("WWZ_Backgrounds_4Lep.root");
    TFile* outputFile = TFile::Open(outputName,"RECREATE");

    // Create the TMVA factory object
    // Arguments:
    // 1). Base name of the weight files in the directory weight/
    // 2). Output file for the training results
    // 3). Options string (options can be suppressed by using !)
    
    TMVA::Factory *factory = new TMVA::Factory( "TMVA_Classification_4Lep", outputFile,
						"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );   

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

    // Specify the input variables that will be used for the MVA training

    dataloader->AddVariable("m_ll", "m_{ll}", "GeV", 'F');
    dataloader->AddVariable("dPhi_4Lep_MET", "#Delta#phi(4Lep,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_Zcand_MET", "#Delta#phi(Zcands,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dR_Wcands", "#Delta R(l^{W1},l^{W2})", "", 'F');
    dataloader->AddVariable("dR_Zcands", "#Delta R(l^{Z1},l^{Z2})", "", 'F');
    dataloader->AddVariable("MET", "p_{T}^{miss}", "GeV", 'F');
    dataloader->AddVariable("MT2", "M_{T2}", "GeV", 'F');
    dataloader->AddVariable("Pt4l", "p_{T}^{4l}", "GeV", 'F');
    dataloader->AddVariable("STLepHad", "#Sigma_{lep,had} p_{T}", "GeV", 'F');
    dataloader->AddVariable("leading_Zcand_pt", "p_{T}^{Z1}", "GeV", 'F');
    dataloader->AddVariable("subleading_Zcand_pt", "p_{T}^{Z2}", "GeV", 'F');
    dataloader->AddVariable("leading_Wcand_pt", "p_{T}^{W1}", "GeV", 'F');
    dataloader->AddVariable("subleading_Wcand_pt", "p_{T}^{W2}", "GeV", 'F');
    dataloader->AddVariable("SFChannel", "Same Flavor Channel" , "", 'B');
    dataloader->AddVariable("OFChannel", "Opposite Flavor Channel", "", 'B');

    Double_t signalWeight = 1.0;
    Double_t ZZWeight = 1.0;
    Double_t TTZWeight = 1.0;
    Double_t WZWeight = 1.0;
    Double_t HiggsWeight = 1.0;
    Double_t OtherWeight = 1.0;
 
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
    dataloader->AddSignalTree(signalTree, signalWeight);
    dataloader->AddBackgroundTree(ZZTree, ZZWeight);
    dataloader->AddBackgroundTree(TTZTree, TTZWeight);
    dataloader->AddBackgroundTree(WZTree, WZWeight);
    dataloader->AddBackgroundTree(HiggsTree, HiggsWeight);
    dataloader->AddBackgroundTree(OtherTree, OtherWeight);

    // Set individual event weights (point to the branch within the tree)
    // Signal
    dataloader->SetSignalWeightExpression("scaleLumi*intLumi");
    // Background
    dataloader->SetBackgroundWeightExpression("scaleLumi*intLumi");

    // Apply additional cuts on the signal and background samples (can be different)
    TCut cut_all = "m_ll > -999 && dPhi_4Lep_MET > -999 && dPhi_Zcand_MET > -999 && dR_Wcands > -999 && dR_Zcands > -999 && MET > -999 && MT2 > -999 && Pt4l > -999 && STLepHad > -999 && leading_Zcand_pt > -999 && subleading_Zcand_pt > -999 && leading_Wcand_pt > -999 && subleading_Wcand_pt > -999";
    
    // Book MVA methods
    //================================================================================
    // Note about NormMode option:
    //      NormMode=NumEvents - N events in first class is equal to sum of all others
    //	    NormMode=EqualNumEvents - All classes have same # of effective events
    //================================================================================
    dataloader->PrepareTrainingAndTestTree( cut_all, cut_all,
					  "nTrain_Signal=900000:nTrain_Background=3100000:SplitMode=Random:NormMode=NumEvents:!V" );

    // Boosted Decision Trees (BDTs)
    if (Use["BDT"]) // Adaptive Boost
	factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

    if (Use["BDTG"]) // Gradient Boost
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=200:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3" );

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
    if (!gROOT->IsBatch()) TMVA::TMVAGui( outputName );

    return 0;

}
