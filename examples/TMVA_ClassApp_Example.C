//////////////////////////////////////////////////
//
// Example script for the application of a 
// Classification BDT using a single signal (WWZ)
// and a single background (ZZ)
//
//////////////////////////////////////////////////
//
// Author:
// 	Keegan Downham, UC Santa Barbara
//
//////////////////////////////////////////////////

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void TMVA_ClassApp_Example(){

    // Load the library
    TMVA::Tools::Instance();

    // Create a map for the different MVA methods
    std::map<std::string,int> Use;
    
    // Cut optimization methods
    //Use["Cuts"]		= 0;
    //Use["CutsD"]	= 0;
    //Use["CutsPCA"]	= 0;
   
    // Boosted Decision Trees (BDTs)
    Use["BDT"]		= 1; // uses Adaptive Boost
    Use["BDTG"]		= 0; // uses Gradient Boost
    Use["BDTB"]		= 0; // uses Bagging
    Use["BDTD"]		= 0; // decorrelation + Adaptive Boost
    Use["BDTF"]		= 0; // allow usage of fisher discriminant for node splitting
    // In principle we can define more options if we want to perform a more thorough study, 
    // but for now we will keep things simple.
    
    std::cout << std::endl;
    std::cout << "===> Start TMVA_ClassApp_Example" << std::endl;

    // -------------------------------------------------------------
    // Create the reader object (analagous to the factory)
    
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    // Define a set of variables, and then feed them to the reader
    // - variable names MUST exactly match the name and type from the weight files
    float Var_4LepMET_mt2_PuppiMET;
    float Var_4LepMET_other_mll; 
    reader->AddVariable( "Var_4LepMET_mt2_PuppiMET", &Var_4LepMET_mt2_PuppiMET );
    reader->AddVariable( "Var_4LepMET_other_mll", &Var_4LepMET_other_mll );

    // Add spectator variables to the reader
    // - Those defined in the training must also be added to the reader
    // (For this example, we don't include any spectator variables)

    // Now we can book the MVA methods we wish to use
    TString dir = "dataset/weights/";
    TString prefix = "TMVA_Classification_Example";   

    // Book the method(s) that we want to use
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   UInt_t nbin = 100;
   // In this example, we only care about the BDT output histograms
   TH1F *histBDT(0);
   TH1F *histBDTG(0);
   TH1F *histBDTB(0);
   TH1F *histBDTD(0);
   TH1F *histBDTF(0);

   if (Use["BDT"])   histBDT		= new TH1F( "MVA_BDT" ,	 "MVA_BDT" ,  nbin, -1.0, 1.0 );
   if (Use["BDTG"])  histBDTG           = new TH1F( "MVA_BDTG",  "MVA_BDTG",  nbin, -1.0, 1.0 );
   if (Use["BDTB"])  histBDTB           = new TH1F( "MVA_BDTB",  "MVA_BDTB",  nbin, -1.0, 1.0 );
   if (Use["BDTD"])  histBDTD           = new TH1F( "MVA_BDTD",  "MVA_BDTD",  nbin, -1.0, 1.0 );
   if (Use["BDTF"])  histBDTF           = new TH1F( "MVA_BDTF",  "MVA_BDTF",  nbin, -1.0, 1.0 );  

   // Prepare the input tree for the reader
   // This corresponds to the ROOT file that contains the tree that your variables reside within
   // In our case, we point towards the signal (WWZ) and background (ZZ) root files
   TFile *input_sig(0);
   TString fname_sig = "/ceph/cms/store/user/kdownham/VVVAnalysis/051723/WWZJetsTo4L2Nu_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2_NANOAODSIM_3LepTau_4Lep_051723/output_1.root";
   input_sig = TFile::Open( fname_sig );

   //TFile *input_bkg(0);
   //TString fname_bkg = "";
   //input_bkg = TFile::Open( fname_bkg );

   std::cout << "--- Select signal sample" << std::endl;
   TTree* sigTree = (TTree*)input_sig->Get("t");
   sigTree->SetBranchAddress( "Var_4LepMET_mt2_PuppiMET", &Var_4LepMET_mt2_PuppiMET );
   sigTree->SetBranchAddress( "Var_4LepMET_other_mll", &Var_4LepMET_other_mll );

   //std::cout << "--- Select background sample" << std::endl;
   //TTree* bkgTree = (TTree*)input_bkg->Get("t");
   //bkgTree->SetBranchAddress( "Var_4LepMET_mt2_PuppiMET", &Var_4LepMET_mt2_PuppiMET );
   //bkgTree->SetBranchAddress( "Var_4LepMET_other_mll", &Var_4LepMET_other_mll ); 

   // Signal Event Loop
   std::cout << "--- Processing: " << sigTree->GetEntries() << " signal events" << std::endl;
   TStopwatch sw;
   sw.Start(); 

   for (Long64_t ievt=0; ievt<sigTree->GetEntries();ievt++){

	if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

	sigTree->GetEntry(ievt);

        if (Var_4LepMET_mt2_PuppiMET == -999) continue;
        if (Var_4LepMET_other_mll == -999) continue;

	if (Use["BDT"          ])   histBDT    ->Fill( reader->EvaluateMVA( "BDT method"           ) );
        if (Use["BDTG"         ])   histBDTG   ->Fill( reader->EvaluateMVA( "BDTG method"          ) );
        if (Use["BDTB"         ])   histBDTB   ->Fill( reader->EvaluateMVA( "BDTB method"          ) );
        if (Use["BDTD"         ])   histBDTD   ->Fill( reader->EvaluateMVA( "BDTD method"          ) );
        if (Use["BDTF"         ])   histBDTF   ->Fill( reader->EvaluateMVA( "BDTF method"          ) );

   } 

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print(); 

   // Write histograms
   TFile *target = new TFile( "WWZ_Application_Example.root", "RECREATE" );
   if (Use["BDT"])	histBDT   ->Write();
   if (Use["BDTG"])     histBDTG  ->Write();
   if (Use["BDTB"])     histBDTB  ->Write();
   if (Use["BDTD"])     histBDTD  ->Write();
   if (Use["BDTF"])     histBDTF  ->Write();  

   target->Close();

   std::cout << "--- Created root file: \"WWZ_Application_Example.root\" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVA Application Examples is done!" << std::endl << std::endl;

}
