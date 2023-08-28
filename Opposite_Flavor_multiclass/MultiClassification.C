//=====================================================================
//
// Macro used for the training of various BDTs for the WWZ to 
// 4 lepton analysis (CMS).
//
// This macro in particular trains BDTs targeting the opposite-flavor
// channel by constructing multiclassifiers for the signal processes
// (WWZ and ZH) vs the background processes (ttZ and ZZ).
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

int MultiClassification(TString weightName){

    // Load the TMVA library
    TMVA::Tools::Instance();

    // MVA methods to be trained + tested
    std::map<std::string,int> Use;

    // Boosted decision trees
    Use["BDT"]             = 1; // uses Gradient Boost (default values for all parameters)
    //=====================================================================
    // 
    // All options for BDTs are listed in table 25 of the TMVA user's guide:
    // 	    root.cern.ch/download/doc/tmva/TMVAUsersGuide.pdf
    //
    //=====================================================================

    std::cout << "===> Start TMVA WWZ vs ZZ Opposite-Flavor classification" << std::endl;

    //=====================================================================
    // Preparing the input data
    //=====================================================================
    
    // Read the training and test data
    
    TString dir = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_080323_trgUpdate/Run2/";

    TFile *input_WWZ(0);
    TString fname_WWZ = dir+"NonResWWZ.root";
    TFile *input_ZH(0);
    TString fname_ZH = dir+"ZHWWZ.root";
    TFile *input_ZZ(0);
    TString fname_ZZ = dir+"ZZ.root";
    TFile *input_TTZ(0);
    TString fname_TTZ = dir+"TTZ.root";

    // Open the files for signal and background
    input_WWZ = TFile::Open(fname_WWZ);
    input_ZH = TFile::Open(fname_ZH);
    input_ZZ = TFile::Open(fname_ZZ);
    input_TTZ = TFile::Open(fname_TTZ);

    std::cout << "--- WWZ -> 4 lepton classification using the following input files: " << std::endl;
    std::cout << "--- WWZ: " << input_WWZ->GetName() << std::endl;
    std::cout << "--- ZH: " << input_ZH->GetName() << std::endl;
    std::cout << "--- ZZ: " << input_ZZ->GetName() << std::endl;
    std::cout << "--- TTZ: " << input_TTZ->GetName() << std::endl;

    // Specify the trees for training
    TString treeName = "t_BDT_OF";
    TTree *WWZTree = (TTree*)input_WWZ->Get(treeName);
    TTree *ZHTree  = (TTree*)input_ZH->Get(treeName);
    TTree *TTZTree = (TTree*)input_TTZ->Get(treeName);
    TTree *ZZTree = (TTree*)input_ZZ->Get(treeName);

    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outfileName = weightName+".root";
    TFile* outputFile = TFile::Open("classification/"+outfileName,"RECREATE");

    // Create the TMVA factory object
    // Arguments:
    // 1). Base name of the weight files in the directory weight/
    // 2). Output file for the training results
    // 3). Options string (options can be suppressed by using !)
    
    TMVA::Factory *factory = new TMVA::Factory( weightName, outputFile,
						"!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Multiclass" );   

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

    // Specify the input variables that will be used for the MVA training

    dataloader->AddVariable("m_ll", "m_{ll}", "GeV", 'F');
    dataloader->AddVariable("dPhi_4Lep_MET", "#Delta#phi(4Lep,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_Zcand_MET", "#Delta#phi(Zcands,p_{T}^{miss})", "", 'F');
    dataloader->AddVariable("dPhi_WW_MET", "#Delta#phi(Wcands,p_{T}^{miss})", "", 'F');
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

    // Spectator variable used for the splitting
    dataloader->AddSpectator("eventID", 'I');

    Double_t WWZWeight = 1.0;
    Double_t ZHWeight = 1.0;
    Double_t TTZWeight = 1.0;
    Double_t ZZWeight = 1.0;
 
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
    dataloader->AddTree(WWZTree, "WWZ", WWZWeight);
    dataloader->AddTree(ZHTree ,  "ZH", ZHWeight);
    dataloader->AddTree(TTZTree, "TTZ", TTZWeight);
    dataloader->AddTree(ZZTree,   "ZZ", ZZWeight);

    // Set individual event weights (point to the branch within the tree)
    // Signal
    dataloader->SetWeightExpression("weight","WWZ");
    dataloader->SetWeightExpression("weight","ZH");
    // Background
    dataloader->SetWeightExpression("weight","TTZ");
    dataloader->SetWeightExpression("weight","ZZ");

    // Apply additional cuts on the signal and background samples (can be different)
    TCut cut_all = "m_ll > -999 && dPhi_4Lep_MET > -999 && dPhi_Zcand_MET > -999 && dR_Wcands > -999 && dR_Zcands > -999 && MET > -999 && MT2 > -999 && Pt4l > -999 && STLepHad > -999 && leading_Zcand_pt > -999 && subleading_Zcand_pt > -999 && leading_Wcand_pt > -999 && subleading_Wcand_pt > -999";
    
    // Book MVA methods
    //================================================================================
    // Note about NormMode option:
    //      NormMode=NumEvents - N events in first class is equal to sum of all others
    //	    NormMode=EqualNumEvents - All classes have same # of effective events
    //================================================================================
    dataloader->PrepareTrainingAndTestTree( cut_all,
    					  "SplitMode=Random:NormMode=NumEvents:!V" );
    //dataloader->PrepareTrainingAndTestTree( cut_all,
    //					  "SplitMode=Random:NormMode=NumEvents:!V" );
   

    // Boosted Decision Trees (BDTs)
    if (Use["BDT"]) // Gradient Boost
        factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=400:MinNodeSize=10%:MaxDepth=1:BoostType=Grad:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=SDivSqrtSPlusB:nCuts=20:IgnoreNegWeightsInTraining=True" );

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    
    // Save the output
    outputFile->Close();

    std::cout << "===> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "===> MultiClassification is done!" << std::endl;

    delete factory;
    delete dataloader;

    // Launch the GUI for the root macros
    if (!gROOT->IsBatch()) TMVA::TMVAMultiClassGui( "classification/"+outfileName );

    return 0;

}
