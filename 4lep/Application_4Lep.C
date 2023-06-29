////////////////////////////////////////////////
//
// Script used to compute the MVA scores for 
// signal and background processes in the 
// WWZ -> 4 lepton analysis and write out the 
// results to histograms for each file.
//
////////////////////////////////////////////////
//
// Author:
//      Keegan Downham, UC Santa Barbara
//
////////////////////////////////////////////////

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void Application_4Lep(){

    // Load the TMVA library 
    TMVA::Tools::Instance();

    // Create a map for the different MVA methods
    std::map<std::string,int> Use;

    // Make sure to use the same MVA methods as defined in the Classification_4Lep.C macro
    Use["BDT"]            = 1;
    Use["BDT_T200"]       = 1;
    Use["BDT_T400"]       = 1;
    Use["BDT_D2"]         = 1;     
    Use["BDT_D4"]         = 1;
    Use["BDT_NS2p5"]      = 1;
    Use["BDT_NS10"]       = 1;
    Use["BDT_L3"]         = 1;
    Use["BDT_L7"]         = 1;

    std::cout << std::endl;
    std::cout << "===> Start 4Lepton MVA Application" << std::endl;

    //------------------------------------
    // Create the TMVA reader object

    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  
    // Define a set of variables, and feed them to the reader
    // - variable names MUST exactly match the name and type from the weight files
    float m_ll; 
    float dPhi_4Lep_MET; 
    float dPhi_Zcand_MET; 
    float dR_Wcands; 
    float dR_Zcands; 
    float MET; 
    float MT2; 
    float Pt4l; 
    float STLepHad; 
    float leading_Zcand_pt; 
    float subleading_Zcand_pt; 
    float leading_Wcand_pt; 
    float subleading_Wcand_pt;
    int SFChannel; 
    int OFChannel; 
    int CutBVeto;

    reader->AddVariable( "m_ll", &m_ll );  
    reader->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );    
    reader->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
    reader->AddVariable( "dR_Wcands", &dR_Wcands );
    reader->AddVariable( "dR_Zcands", &dR_Zcands );
    reader->AddVariable( "MET", &MET );
    reader->AddVariable( "MT2", &MT2 );
    reader->AddVariable( "Pt4l", &Pt4l );
    reader->AddVariable( "STLepHad", &STLepHad );
    reader->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
    reader->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
    reader->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
    reader->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );
    reader->AddVariable( "SFChannel", &SFChannel );
    reader->AddVariable( "OFChannel", &OFChannel );

    // Add spectator variables to the reader
    // - Those defined in the training must also be added to the reader
    reader->AddSpectator( "CutBVeto", &CutBVeto );

    // Tell the reader where to find the weights
    TString dir = "dataset/weights/";
    TString prefix = "TMVA_Classification_4Lep";

    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   UInt_t nbin = 100;
   // Define BDT output histograms for every method and process that we care about
   //TH1F *histBDT_D4_signal(0);
   //TH1F *histBDT_D4_ZZ(0); 
   //TH1F *histBDT_D4_TTZ(0); 
   //TH1F *histBDT_D4_WZ(0);
   //TH1F *histBDT_D4_Higgs(0);
   //TH1F *histBDT_D4_Other(0);
   //TH1F *histBDT_L7_signal(0);
   //TH1F *histBDT_L7_ZZ(0);
   //TH1F *histBDT_L7_TTZ(0);
   //TH1F *histBDT_L7_WZ(0);
   //TH1F *histBDT_L7_Higgs(0);
   //TH1F *histBDT_L7_Other(0);

   // Let's just do this for the D4 and L7 options since they perform the best....
   //if (Use["BDT_D4"]){
   //     histBDT_D4_signal = new TH1F( "MVA_BDT_D4_signal", "MVA_BDT_D4_signal", nbin, -1.0, 1.0 );
   //     histBDT_D4_ZZ     = new TH1F( "MVA_BDT_D4_ZZ", "MVA_BDT_D4_ZZ", nbin, -1.0, 1.0 );
   //     histBDT_D4_TTZ    = new TH1F( "MVA_BDT_D4_TTZ", "MVA_BDT_D4_TTZ", nbin, -1.0, 1.0 );
   //     histBDT_D4_WZ     = new TH1F( "MVA_BDT_D4_WZ", "MVA_BDT_D4_WZ", nbin, -1.0, 1.0 );
   //     histBDT_D4_Higgs  = new TH1F( "MVA_BDT_D4_Higgs", "MVA_BDT_D4_Higgs", nbin, -1.0, 1.0 );
   //     histBDT_D4_Other  = new TH1F( "MVA_BDT_D4_Other", "MVA_BDT_D4_Other", nbin, -1.0, 1.0 );      
   //}     
   //if (Use["BDT_L7"]){
   //     histBDT_L7_signal = new TH1F( "MVA_BDT_L7_signal", "MVA_BDT_L7_signal", nbin, -1.0, 1.0 );
   //     histBDT_L7_ZZ     = new TH1F( "MVA_BDT_L7_ZZ", "MVA_BDT_L7_ZZ", nbin, -1.0, 1.0 );
   //     histBDT_L7_TTZ    = new TH1F( "MVA_BDT_L7_TTZ", "MVA_BDT_L7_TTZ", nbin, -1.0, 1.0 );
   //     histBDT_L7_WZ     = new TH1F( "MVA_BDT_L7_WZ", "MVA_BDT_L7_WZ", nbin, -1.0, 1.0 );
   //     histBDT_L7_Higgs  = new TH1F( "MVA_BDT_L7_Higgs", "MVA_BDT_L7_Higgs", nbin, -1.0, 1.0 );
   //     histBDT_L7_Other  = new TH1F( "MVA_BDT_L7_Other", "MVA_BDT_L7_Other", nbin, -1.0, 1.0 );  
   //}

   // Prepare the input tree for the reader
   // This corresponds to the ROOT file that contains the tree that your variables live in
   //======================================================================================
   // In this case, we have one signal process:
   // WWZ
   // and multiple background processes:
   // ZZ, TTZ, WZ, Higgs, and Other
   //======================================================================================

   TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_BDT_tree/Run2/";
   std::vector<TString> files = {"WWZ.root", "ZZ.root", "TTZ.root", "WZ.root", "Higgs.root", "Other.root"};
   for (auto f : files ){
        std::cout << "=============================================================" << std::endl;
	std::cout << "Calculating MVA scores for events in file: " << f << std::endl;
	TFile *input = TFile::Open( path+f );
	TTree *tree  = (TTree*)input->Get("t_BDT");
	tree->SetBranchAddress("m_ll", &m_ll);        
	tree->SetBranchAddress("dPhi_4Lep_MET", &dPhi_4Lep_MET);
	tree->SetBranchAddress("dPhi_Zcand_MET", &dPhi_Zcand_MET);
	tree->SetBranchAddress("dR_Wcands", &dR_Wcands);
	tree->SetBranchAddress("dR_Zcands", &dR_Zcands);
	tree->SetBranchAddress("MET", &MET);
	tree->SetBranchAddress("MT2", &MT2);
	tree->SetBranchAddress("Pt4l", &Pt4l);
	tree->SetBranchAddress("STLepHad", &STLepHad);
	tree->SetBranchAddress("leading_Zcand_pt", &leading_Zcand_pt);
	tree->SetBranchAddress("subleading_Zcand_pt", &subleading_Zcand_pt);
  	tree->SetBranchAddress("leading_Wcand_pt", &leading_Wcand_pt);
 	tree->SetBranchAddress("subleading_Wcand_pt", &subleading_Wcand_pt);
	tree->SetBranchAddress("SFChannel", &SFChannel);
	tree->SetBranchAddress("OFChannel", &OFChannel);
	tree->SetBranchAddress("CutBVeto", &CutBVeto);

        // Define the histograms

	TH1F *histBDT_D4(0);
	TH1F *histBDT_L7(0);	

        if (Use["BDT_D4"]){
	    histBDT_D4 = new TH1F( "MVA_BDT_D4", "MVA_BDT_D4", nbin, -1.0, 1.0 ); 
	}
	if (Use["BDT_L7"]){
	    histBDT_L7 = new TH1F( "MVA_BDT_L7", "MVA_BDT_L7", nbin, -1.0, 1.0 );
	}

	std::cout << "==============================================================" << std::endl;
	std::cout << "--- Processing: " << tree->GetEntries() << " events" << std::endl;
	
        for (Long64_t ievt=0; ievt<tree->GetEntries();ievt++){
	     if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
	     
	     tree->GetEntry(ievt);
	
	     // Apply selection cuts on the branches here
	     if (not (CutBVeto == 1)) continue;
	     if (not (m_ll > -999)) continue;	     	    
	     if (not (dPhi_4Lep_MET > -999)) continue;  
	     if (not (dPhi_Zcand_MET > -999)) continue;
	     if (not (dR_Wcands > -999)) continue;
	     if (not (dR_Zcands > -999)) continue;
	     if (not (MET > -999)) continue;
	     if (not (MT2 > -999)) continue;
	     if (not (Pt4l > -999)) continue;
	     if (not (STLepHad > -999)) continue;
	     if (not (leading_Zcand_pt > -999)) continue;
	     if (not (subleading_Zcand_pt > -999)) continue;
	     if (not (leading_Wcand_pt > -999)) continue; 
	     if (not (subleading_Wcand_pt > -999)) continue;

             if (Use["BDT_D4"]) histBDT_D4  -> Fill( reader->EvaluateMVA( "BDT_D4 method" ));
	     if (Use["BDT_L7"]) histBDT_L7  -> Fill( reader->EvaluateMVA( "BDT_L7 method" ));       

	}   

	std::cout << "--- End of event loop ---" << std::endl;
	// Write histograms
	TFile *target = new TFile( "outputs/MVA_"+f, "RECREATE" );
	if (Use["BDT_D4"]) histBDT_D4->Write();
	if (Use["BDT_L7"]) histBDT_L7->Write();

	target->Close();

	std::cout << "--- Created root file: " << target->GetName() << " containing the MVA output histograms" << std::endl;	     

	delete tree;
	delete histBDT_D4;
	delete histBDT_L7;
	delete input;
	delete target;

   }

   delete reader;

   std::cout << "===> TMVA 4-lepton Application is done!" << std::endl;

}
