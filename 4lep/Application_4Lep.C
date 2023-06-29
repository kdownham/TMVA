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
    float m_ll, dPhi_4Lep_MET, dPhi_Zcand_MET, dR_Wcands, dR_Zcands, MET, MT2, Pt4l, STLepHad, leading_Zcand_pt, subleading_Zcand_pt, leading_Wcand_pt;
    bool SFChannel, OFChannel, CutBVeto;

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



}
