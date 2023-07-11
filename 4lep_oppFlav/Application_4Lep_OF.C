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

void Application_4Lep_OF(){

    // Load the TMVA library 
    TMVA::Tools::Instance();

    // Create a map for the different MVA methods
    std::map<std::string,int> Use;

    // Make sure to use the same MVA methods as defined in the Classification_4Lep.C macro
    Use["BDT"]            = 1;
    //Use["BDT_T200"]       = 1;
    //Use["BDT_T400"]       = 1;
    //Use["BDT_D2"]         = 1;     
    //Use["BDT_D4"]         = 1;
    //Use["BDT_NS2p5"]      = 1;
    //Use["BDT_NS10"]       = 1;
    //Use["BDT_L3"]         = 1;
    //Use["BDT_L7"]         = 1;

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
    float dPhi_WW_MET; 
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
    float weight;

    reader->AddVariable( "m_ll", &m_ll );  
    reader->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );    
    reader->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
    reader->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
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

    // Add spectator variables to the reader
    // - Those defined in the training must also be added to the reader

    // Tell the reader where to find the weights
    TString dir = "dataset/weights/";
    TString prefix = "Default_OFChannel";

    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   UInt_t nbin = 100;

   // Prepare the input tree for the reader
   // This corresponds to the ROOT file that contains the tree that your variables live in
   //======================================================================================
   // In this case, we have one signal process:
   // WWZ
   // and multiple background processes:
   // ZZ, TTZ, WZ, Higgs, and Other
   //======================================================================================
   std::vector<float> yields_c1;
   std::vector<float> yields_c2;
   std::vector<float> yields_c3;
   std::vector<float> yields_c4;

   int idx = 0;

   TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_070623_masterSync/Run2/";
   std::vector<TString> files = {"WWZ.root", "ZZ.root", "TTZ.root", "WZ.root", "Higgs.root", "Other.root"};
   for (auto f : files ){
        std::cout << "=============================================================" << std::endl;
	std::cout << "Calculating MVA scores for events in file: " << f << std::endl;
	TFile *input = TFile::Open( path+f );
	TTree *tree  = (TTree*)input->Get("t_BDT_OF");
	tree->SetBranchAddress("m_ll", &m_ll);        
	tree->SetBranchAddress("dPhi_4Lep_MET", &dPhi_4Lep_MET);
	tree->SetBranchAddress("dPhi_Zcand_MET", &dPhi_Zcand_MET);
	tree->SetBranchAddress("dPhi_WW_MET", &dPhi_WW_MET);
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
	tree->SetBranchAddress("weight", &weight);

	// Define an output tree
	//TTree *t_MVA = new TTree("t_MVA", "MVA scores for BDT methods");

        // Define the histograms

	TH1F *histBDT(0);
	//TH1F *histBDT_T200(0);
	//TH1F *histBDT_T400(0);
	//TH1F *histBDT_D2(0);
	//TH1F *histBDT_D4(0);
	//TH1F *histBDT_L3(0);
	//TH1F *histBDT_L7(0);
	//TH1F *histBDT_NS2p5(0);
	//TH1F *histBDT_NS10(0);

	if (Use["BDT"]){
	    histBDT = new TH1F( "MVA_BDT", "MVA_BDT", nbin, -1.0, 1.0 );
	}	

	//if (Use["BDT_T200"]){
        //    histBDT_T200 = new TH1F( "MVA_BDT_T200", "MVA_BDT_T200", nbin, -1.0, 1.0 );
        //}

	//if (Use["BDT_T400"]){
        //    histBDT_T400 = new TH1F( "MVA_BDT_T400", "MVA_BDT_T400", nbin, -1.0, 1.0 );
        //}

	//if (Use["BDT_D2"]){
        //    histBDT_D2 = new TH1F( "MVA_BDT_D2", "MVA_BDT_D2", nbin, -1.0, 1.0 );
        //}

        //if (Use["BDT_D4"]){
	//    histBDT_D4 = new TH1F( "MVA_BDT_D4", "MVA_BDT_D4", nbin, -1.0, 1.0 );
	//}

	//if (Use["BDT_L3"]){
        //    histBDT_L3 = new TH1F( "MVA_BDT_L3", "MVA_BDT_L3", nbin, -1.0, 1.0 );
        //}

	//if (Use["BDT_L7"]){
	//    histBDT_L7 = new TH1F( "MVA_BDT_L7", "MVA_BDT_L7", nbin, -1.0, 1.0 );
	//}

	//if (Use["BDT_NS2p5"]){
        //    histBDT_NS2p5 = new TH1F( "MVA_BDT_NS2p5", "MVA_BDT_NS2p5", nbin, -1.0, 1.0 );
        //}

	//if (Use["BDT_NS10"]){
        //    histBDT_NS10 = new TH1F( "MVA_BDT_NS10", "MVA_BDT_NS10", nbin, -1.0, 1.0 );
        //}

	std::cout << "==============================================================" << std::endl;
	std::cout << "--- Processing: " << tree->GetEntries() << " events" << std::endl;

	float c1_yields = 0.;
	float c2_yields = 0.;
	float c3_yields = 0.;
	float c4_yields = 0.;
	
        for (Long64_t ievt=0; ievt<tree->GetEntries();ievt++){
	     if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
	     
	     tree->GetEntry(ievt);
	
	     // Apply selection cuts on the branches here
	     //if (not (CutBVeto == 1)) continue;
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

	     // TODO: add all hists
	     if (Use["BDT"]){  
		 float MVA_BDT = reader->EvaluateMVA("BDT method");    
		 histBDT       -> Fill(MVA_BDT, weight);
		 //t_MVA->Branch("MVA_BDT",&MVA_BDT,"MVA_BDT/F");
		 if ( MVA_BDT > 0.05 ) c1_yields += weight;
		 if ( MVA_BDT > 0.1 ) c2_yields += weight;
		 if ( MVA_BDT > 0.2 ) c3_yields += weight;
		 if ( MVA_BDT > 0.25 ) c4_yields += weight;	
             }

	     
             
	     //if (Use["BDT_T200"]){      
             //    float MVA_BDT_T200 = reader->EvaluateMVA("BDT_T200 method"); 
             //    histBDT_T200  -> Fill(MVA_BDT_T200, weight);
             //    //t_MVA->Branch("MVA_BDT_T200",&MVA_BDT_T200,"MVA_BDT_T200/F");
             //}

	     //if (Use["BDT_T400"]){
             //    float MVA_BDT_T400 = reader->EvaluateMVA("BDT_T400 method");
             //    histBDT_T400  -> Fill(MVA_BDT_T400, weight);
             //    //t_MVA->Branch("MVA_BDT_T400",&MVA_BDT_T400,"MVA_BDT_T400/F");
             //}

	     //if (Use["BDT_D2"]){
             //    float MVA_BDT_D2 = reader->EvaluateMVA("BDT_D2 method");
             //    histBDT_D2    -> Fill(MVA_BDT_D2, weight);
             //    //t_MVA->Branch("MVA_BDT_D2",&MVA_BDT_D2,"MVA_BDT_D2/F");
             //}

	     //if (Use["BDT_D4"]){
             //    float MVA_BDT_D4 = reader->EvaluateMVA("BDT_D4 method");
             //    histBDT_D4    -> Fill(MVA_BDT_D4, weight);
             //    //t_MVA->Branch("MVA_BDT_D4",&MVA_BDT_D4,"MVA_BDT_D4/F");
             //}

	     //if (Use["BDT_L3"]){
             //    float MVA_BDT_L3 = reader->EvaluateMVA("BDT_L3 method");
             //    histBDT_L3    -> Fill(MVA_BDT_L3, weight);
             //    //t_MVA->Branch("MVA_BDT_L3",&MVA_BDT_L3,"MVA_BDT_L3/F");
             //}

	     //if (Use["BDT_L7"]){
             //    float MVA_BDT_L7 = reader->EvaluateMVA("BDT_L7 method");
             //    histBDT_L7    -> Fill(MVA_BDT_L7, weight);
             //    //t_MVA->Branch("MVA_BDT_L7",&MVA_BDT_L7,"MVA_BDT_L7/F");
             //}

	     //if (Use["BDT_NS2p5"]){
             //    float MVA_BDT_NS2p5 = reader->EvaluateMVA("BDT_NS2p5 method");
             //    histBDT_NS2p5    -> Fill(MVA_BDT_NS2p5, weight);
             //    //t_MVA->Branch("MVA_BDT_NS2p5",&MVA_BDT_NS2p5,"MVA_BDT_NS2p5/F");
             //}

	     //if (Use["BDT_NS10"]){
             //    float MVA_BDT_NS10 = reader->EvaluateMVA("BDT_NS10 method");
             //    histBDT_NS10    -> Fill(MVA_BDT_NS10, weight);
             //    //t_MVA->Branch("MVA_BDT_NS10",&MVA_BDT_NS10,"MVA_BDT_NS10/F");
             //}

	     //t_MVA->Fill();

	}   

	yields_c1.push_back(c1_yields);
	yields_c2.push_back(c2_yields);
	yields_c3.push_back(c3_yields);
	yields_c4.push_back(c4_yields);

	std::cout << "--- End of event loop ---" << std::endl;
	// Write histograms
	TFile *target = new TFile( "outputs/MVA_"+f, "RECREATE" );
	if (Use["BDT"])      histBDT->Write();
	//if (Use["BDT_T200"]) histBDT_T200->Write();
	//if (Use["BDT_T400"]) histBDT_T400->Write();
	//if (Use["BDT_D2"])   histBDT_D2->Write();
	//if (Use["BDT_D4"])   histBDT_D4->Write();
	//if (Use["BDT_L3"])   histBDT_L3->Write();
	//if (Use["BDT_L7"])   histBDT_L7->Write();
	//if (Use["BDT_NS2p5"])histBDT_NS2p5->Write();
	//if (Use["BDT_NS10"]) histBDT_NS10->Write();

	//t_MVA->Write();

	target->Close();

	std::cout << "--- Created root file: " << target->GetName() << " containing the MVA output histograms" << std::endl;	     

	delete histBDT;
	//delete histBDT_T200;
	//delete histBDT_T400;
	//delete histBDT_D2;
	//delete histBDT_D4;
	//delete histBDT_L3;
	//delete histBDT_L7;
	//delete histBDT_NS2p5;
	//delete histBDT_NS10;
	delete input;
	delete target;

   }

   delete reader;

   std::cout << "===> TMVA 4-lepton Application is done!" << std::endl;

   std::cout << "================================================================================" << std::endl;
   std::cout << "Printing yields for MVA > 0.05" << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "WWZ = " << yields_c1[0] << std::endl;
   std::cout << "ZZ = " << yields_c1[1] << std::endl;
   std::cout << "TTZ = " << yields_c1[2] << std::endl;
   std::cout << "WZ = " << yields_c1[3] << std::endl;
   std::cout << "Higgs = " << yields_c1[4] << std::endl;
   std::cout << "Other = " << yields_c1[5] << std::endl;
   std::cout << "================================================================================" << std::endl;
   std::cout << "Printing yields for MVA > 0.1" << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "WWZ = " << yields_c2[0] << std::endl;
   std::cout << "ZZ = " << yields_c2[1] << std::endl;
   std::cout << "TTZ = " << yields_c2[2] << std::endl;
   std::cout << "WZ = " << yields_c2[3] << std::endl;
   std::cout << "Higgs = " << yields_c2[4] << std::endl;
   std::cout << "Other = " << yields_c2[5] << std::endl;
   std::cout << "================================================================================" << std::endl;
   std::cout << "Printing yields for MVA > 0.2" << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "WWZ = " << yields_c3[0] << std::endl;
   std::cout << "ZZ = " << yields_c3[1] << std::endl;
   std::cout << "TTZ = " << yields_c3[2] << std::endl;
   std::cout << "WZ = " << yields_c3[3] << std::endl;
   std::cout << "Higgs = " << yields_c3[4] << std::endl;
   std::cout << "Other = " << yields_c3[5] << std::endl;
   std::cout << "================================================================================" << std::endl;
   std::cout << "Printing yields for MVA > 0.25" << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "WWZ = " << yields_c4[0] << std::endl;
   std::cout << "ZZ = " << yields_c4[1] << std::endl;
   std::cout << "TTZ = " << yields_c4[2] << std::endl;
   std::cout << "WZ = " << yields_c4[3] << std::endl;
   std::cout << "Higgs = " << yields_c4[4] << std::endl;
   std::cout << "Other = " << yields_c4[5] << std::endl;
   std::cout << "================================================================================" << std::endl;
   std::cout << "Signal Regions" << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "MVA in [0.05,0.1]" << std::endl;
   std::cout << "WWZ = " << -(yields_c2[0] - yields_c1[0]) << std::endl;
   std::cout << "Background = " << (yields_c2[1]+yields_c2[2]+yields_c2[3]+yields_c2[4]+yields_c2[5]) - (yields_c1[1]+yields_c1[2]+yields_c1[3]+yields_c1[4]+yields_c1[5]) << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "MVA in [0.1,0.2]" << std::endl;
   std::cout << "WWZ = " << -(yields_c3[0] - yields_c2[0]) << std::endl;
   std::cout << "Background = " << (yields_c3[1]+yields_c3[2]+yields_c3[3]+yields_c3[4]+yields_c3[5]) - (yields_c2[1]+yields_c2[2]+yields_c2[3]+yields_c2[4]+yields_c2[5]) << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "MVA in [0.2,0.25]" << std::endl;
   std::cout << "WWZ = " << -(yields_c4[0] - yields_c3[0]) << std::endl;
   std::cout << "Background = " << (yields_c4[1]+yields_c4[2]+yields_c4[3]+yields_c4[4]+yields_c4[5]) - (yields_c3[1]+yields_c3[2]+yields_c3[3]+yields_c3[4]+yields_c3[5]) << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;
   std::cout << "MVA > 0.25" << std::endl;
   std::cout << "WWZ = " << yields_c4[0] << std::endl;
   std::cout << "Background = " << (yields_c4[1]+yields_c4[2]+yields_c4[3]+yields_c4[4]+yields_c4[5]) << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;



}
