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

void MultiApplication(TString weightname, bool makeHists = false){

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
    int   eventID;

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

    reader->AddSpectator( "eventID", &eventID );

    // Add spectator variables to the reader
    // - Those defined in the training must also be added to the reader

    // Tell the reader where to find the weights
    TString dir = "dataset/weights/";
    TString prefix = weightname;

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
   // and one background process:
   // ZZ
   //======================================================================================

   // Open files
   // Create histograms
   // Loop over events
   // Compute MVA scores
   // Fill histograms

   TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_080323_trgUpdate/Run2/";
   std::vector<TString> files = {"NonResWWZ.root","ZHWWZ.root", "TTZ.root", "ZZ.root"};
   std::vector<TH2F*> hist_2D_signals;
   std::vector<TH2F*> hist_2D_bkgds;
   std::vector<TH1F*> hist_WWZ;
   std::vector<TH1F*> hist_ZH;
   std::vector<TH1F*> hist_ZZ;
   std::vector<TH1F*> hist_TTZ;
   std::vector<float> cut1_yields;
   std::vector<float> cut1_errors;
   std::vector<float> cut2_yields;
   std::vector<float> cut2_errors;
   std::vector<float> cut3_yields;
   std::vector<float> cut3_errors;
   std::vector<float> cut4_yields;
   std::vector<float> cut4_errors;

   for (auto f : files){
	std::cout << "=======================================================" << std::endl;
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
	tree->SetBranchAddress("eventID", &eventID);

        TH2F *histBDT_signals(0);
	TH2F *histBDT_bkgds(0);
	TH1F *histWWZ_score(0);
	TH1F *histZH_score(0);
	TH1F *histTTZ_score(0);
	TH1F *histZZ_score(0);

        TString proc = "";

	if ( f == "NonResWWZ.root" ) proc += "NonResWWZ";
	if ( f == "ZHWWZ.root" ) proc += "ZHWWZ";
	if ( f == "TTZ.root" ) proc += "TTZ";
	if ( f == "ZZ.root" ) proc += "ZZ";

        if (Use["BDT"] && makeHists){
	    histBDT_signals = new TH2F( "MVA_BDT_signals_"+proc, "MVA_BDT_signals_"+proc, nbin, 0., 1.0, nbin, 0., 1.0 );
	    histBDT_bkgds = new TH2F( "MVA_BDT_bkgds_"+proc, "MVA_BDT_bkgds_"+proc, nbin, 0., 1.0, nbin, 0., 1.0 );
	    histWWZ_score = new TH1F( "MVA_1_"+proc, "MVA_1_"+proc, nbin, 0., 1.0 );
	    histZH_score = new TH1F( "MVA_2_"+proc, "MVA_2_"+proc, nbin, 0., 1.0 );
	    histTTZ_score = new TH1F( "MVA_3_"+proc, "MVA_3_"+proc, nbin, 0., 1.0 );
	    histZZ_score = new TH1F( "MVA_4_"+proc, "MVA_4_"+proc, nbin, 0., 1.0 );
	}  

        float cut1_temp = 0.;
	float cut2_temp = 0.;
	float cut3_temp = 0.;
	float cut4_temp = 0.;
        float cut1_tempSQw = 0.;
	float cut2_tempSQw = 0.;
	float cut3_tempSQw = 0.;
	float cut4_tempSQw = 0.;

        for (Long64_t ievt=0; ievt<tree->GetEntries(); ievt++){
	     if (ievt%1000 == 0){
		 std::cout << "--- ... Processing event: " << ievt << std::endl;
	     }
	     tree->GetEntry(ievt);

	     if (Use["BDT"]){
		 if ( makeHists ){
		        std::cout << "--------------------------------------------------------------------------" << std::endl;
		        histBDT_signals->Fill((reader->EvaluateMulticlass( "BDT method" )[0]),(reader->EvaluateMulticlass( "BDT method" )[1]), weight);
		        histBDT_bkgds->Fill((reader->EvaluateMulticlass( "BDT method" )[2]),(reader->EvaluateMulticlass( "BDT method" )[3]), weight);
		        histWWZ_score->Fill((reader->EvaluateMulticlass( "BDT method" )[0]), weight);
		        histZH_score->Fill((reader->EvaluateMulticlass( "BDT method" )[1]), weight);
		        histTTZ_score->Fill((reader->EvaluateMulticlass( "BDT method" )[2]), weight);
		        histZZ_score->Fill((reader->EvaluateMulticlass( "BDT method" )[3]), weight);
	         }
		 
		 float WWZ_score = reader->EvaluateMulticlass( "BDT method" )[0];
		 float ZH_score = reader->EvaluateMulticlass( "BDT method" )[1];

		 bool WWZ_SR_1 = ( WWZ_score > 0.94 && ZH_score < 0.06 );
		 bool WWZ_SR_2 = ( WWZ_score > 0.85 && WWZ_score < 0.94 );
		 bool ZH_SR_1  = ( WWZ_score < 0.06 && ZH_score > 0.94 );
		 bool ZH_SR_2  = ( WWZ_score < 0.20 && WWZ_score > 0.06 && ZH_score > 0.80 && ZH_score < 0.94);

		 if ( WWZ_SR_1 ){
		      cut1_temp += weight;
		      cut1_tempSQw += std::pow(weight,2.0);
		 }
		
		 if ( WWZ_SR_2 ){
                      cut3_temp += weight;
                      cut3_tempSQw += std::pow(weight,2.0);
                 }

		 if ( ZH_SR_1 ){
		      cut2_temp += weight;
		      cut2_tempSQw += std::pow(weight,2.0);
		 }

		 if ( ZH_SR_2 ){
                      cut4_temp += weight;
                      cut4_tempSQw += std::pow(weight,2.0);
                 }

	     }

	}

	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "Process: " << proc << std::endl;
	std::cout << "Number of events in WWZ SR 1: " << cut1_temp << " +/- " << std::sqrt(cut1_tempSQw) << std::endl;
	std::cout << "Number of events in WWZ SR 2: " << cut3_temp << " +/- " << std::sqrt(cut3_tempSQw) << std::endl;
	std::cout << "Number of events in ZH SR 1: " << cut2_temp << " +/- " << std::sqrt(cut2_tempSQw) << std::endl;
	std::cout << "Number of events in ZH SR 2: " << cut4_temp << " +/- " << std::sqrt(cut4_tempSQw) << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

        cut1_yields.push_back(cut1_temp);
	cut1_errors.push_back(std::sqrt(cut1_tempSQw));
	cut2_yields.push_back(cut2_temp);
	cut2_errors.push_back(std::sqrt(cut2_tempSQw));	
	cut3_yields.push_back(cut3_temp);
        cut3_errors.push_back(std::sqrt(cut3_tempSQw));
        cut4_yields.push_back(cut4_temp);
        cut4_errors.push_back(std::sqrt(cut4_tempSQw));

	//std::cout << "----- End of event loop for file: " << f << " -----" << std::endl;

        if (Use["BDT"] && makeHists){
	    hist_2D_signals.push_back(histBDT_signals);
	    hist_2D_bkgds.push_back(histBDT_bkgds);
	    hist_WWZ.push_back(histWWZ_score);
	    hist_ZH.push_back(histZH_score);
	    hist_TTZ.push_back(histTTZ_score);
	    hist_ZZ.push_back(histZZ_score);
	}   

   }

   
   if ( makeHists ){ 

        TFile *target = new TFile( "MulticlassApplication.root", "RECREATE" );
        if (Use["BDT"]){
            for ( int i = 0; i < hist_WWZ.size(); i++ ){
            	     hist_WWZ[i]->Write();
            	     hist_ZH[i]->Write();
                  hist_TTZ[i]->Write();
                  hist_ZZ[i]->Write();
                  hist_2D_signals[i]->Write();
                  hist_2D_bkgds[i]->Write();
            }
        }

        target->Close();

   }

   //std::cout << "===> Created root file: \"MulticlassApplication.root\" containing the MVA output histograms" << std::endl;   

   std::cout << "TMVA Multiclass Application is done!" << std::endl;     

   std::cout << "===========================================================================================" << std::endl;
   std::cout << "-------------------------------Printing SR Summary-----------------------------------------" << std::endl;
   std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
   std::cout << "-------------------------------------WWZ SR 1----------------------------------------------" << std::endl;
   std::cout << "NonResonant WWZ: " << cut1_yields[0] << " +/- " << cut1_errors[0] << " events" << std::endl;
   std::cout << "ZHWWZ          : " << cut1_yields[1] << " +/- " << cut1_errors[1] << " events" << std::endl;
   std::cout << "TTZ            : " << cut1_yields[2] << " +/- " << cut1_errors[2] << " events" << std::endl;
   std::cout << "ZZ             : " << cut1_yields[3] << " +/- " << cut1_errors[3] << " events" << std::endl;   
   std::cout << "-------------------------------------WWZ SR 2----------------------------------------------" << std::endl;
   std::cout << "NonResonant WWZ: " << cut3_yields[0] << " +/- " << cut3_errors[0] << " events" << std::endl;
   std::cout << "ZHWWZ          : " << cut3_yields[1] << " +/- " << cut3_errors[1] << " events" << std::endl;
   std::cout << "TTZ            : " << cut3_yields[2] << " +/- " << cut3_errors[2] << " events" << std::endl;
   std::cout << "ZZ             : " << cut3_yields[3] << " +/- " << cut3_errors[3] << " events" << std::endl;
   std::cout << "--------------------------------------ZH SR 1-----------------------------------------------" << std::endl;
   std::cout << "NonResonant WWZ: " << cut2_yields[0] << " +/- " << cut2_errors[0] << " events" << std::endl;
   std::cout << "ZHWWZ          : " << cut2_yields[1] << " +/- " << cut2_errors[1] << " events" << std::endl;
   std::cout << "TTZ            : " << cut2_yields[2] << " +/- " << cut2_errors[2] << " events" << std::endl;
   std::cout << "ZZ             : " << cut2_yields[3] << " +/- " << cut2_errors[3] << " events" << std::endl;
   std::cout << "--------------------------------------ZH SR 2-----------------------------------------------" << std::endl;
   std::cout << "NonResonant WWZ: " << cut4_yields[0] << " +/- " << cut4_errors[0] << " events" << std::endl;
   std::cout << "ZHWWZ          : " << cut4_yields[1] << " +/- " << cut4_errors[1] << " events" << std::endl;
   std::cout << "TTZ            : " << cut4_yields[2] << " +/- " << cut4_errors[2] << " events" << std::endl;
   std::cout << "ZZ             : " << cut4_yields[3] << " +/- " << cut4_errors[3] << " events" << std::endl;
   std::cout << "===========================================================================================" << std::endl;

   delete reader;

}
