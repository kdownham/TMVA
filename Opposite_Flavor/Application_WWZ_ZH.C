#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <iostream>
#include <fstream>

using namespace std;

using namespace TMVA;

//TMVA::Reader *Book_WWZ(std::map<std::string,int> method_WWZ, TString weightname_WWZ);
//TMVA::Reader *Book_ZH(std::map<std::string,int> method_ZH, TString weightname_ZH);
//void calcMVAs(TMVA::Reader *r1, TMVA::Reader *r2);

void Application_WWZ_ZH(){

     TMVA::Tools::Instance();
     std::map<std::string,int> Use_WWZ;
     std::map<std::string,int> Use_ZH;

     

     Use_ZH["BDTG_T400_LR0p1_D2"]            = 1;  // Need to use the same method(s) as utilized during the training
     Use_WWZ["BDTG_T400_LR0p1_D2"]           = 1;  // Need to use the same method(s) as utilized during the training

     // Define the input variables
     float m_ll;
     float dPhi_4Lep_MET;
     float dPhi_Zcand_MET;
     float dPhi_WW_MET;
     float dR_Wcands;
     float dR_Zcands;
     float dR_WW_Z;
     float MET;
     float MT2;
     float Pt4l;
     float STLepHad;
     float STLep;
     float leading_Zcand_pt;
     float subleading_Zcand_pt;
     float leading_Wcand_pt;
     float subleading_Wcand_pt;
     float weight;

     // Create 2 TMVA reader objects (1 per signal)
     TMVA::Reader *reader_wwz = new TMVA::Reader( "!Color:!Silent" );
     TMVA::Reader *reader_zh = new TMVA::Reader( "!Color:!Silent" );

     // Add the variables to the WWZ reader
     reader_wwz->AddVariable( "m_ll", &m_ll );
     reader_wwz->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
     reader_wwz->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
     reader_wwz->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
     reader_wwz->AddVariable( "dR_Wcands", &dR_Wcands );
     reader_wwz->AddVariable( "dR_Zcands", &dR_Zcands );
     reader_wwz->AddVariable( "dR_WW_Z", &dR_WW_Z );
     reader_wwz->AddVariable( "MET", &MET );
     reader_wwz->AddVariable( "MT2", &MT2 );
     reader_wwz->AddVariable( "Pt4l", &Pt4l );
     reader_wwz->AddVariable( "STLepHad", &STLepHad );
     reader_wwz->AddVariable( "STLep", &STLep );
     reader_wwz->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
     reader_wwz->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
     reader_wwz->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
     reader_wwz->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );

     TString dir_1 = "WWZ_vs_Backgrounds/dataset/weights/"; // Path to your WWZ "weights" directory
     TString prefix_1 = "Grad_Optimal_v1";                  // Name of the "weight" file you want to evaluate for the WWZ signal (without the .weights.xml)
     for (std::map<std::string,int>::iterator it = Use_WWZ.begin(); it != Use_WWZ.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_1 + prefix_1 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_wwz->BookMVA( methodName, weightfile );
         }
     }

     // Add the variables to the ZH reader
     reader_zh->AddVariable( "m_ll", &m_ll );
     reader_zh->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
     reader_zh->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
     reader_zh->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
     reader_zh->AddVariable( "dR_Wcands", &dR_Wcands );
     reader_zh->AddVariable( "dR_Zcands", &dR_Zcands );
     reader_zh->AddVariable( "dR_WW_Z", &dR_WW_Z );
     reader_zh->AddVariable( "MET", &MET );
     reader_zh->AddVariable( "MT2", &MT2 );
     reader_zh->AddVariable( "Pt4l", &Pt4l );
     reader_zh->AddVariable( "STLepHad", &STLepHad );
     reader_zh->AddVariable( "STLep", &STLep );
     reader_zh->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
     reader_zh->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
     reader_zh->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
     reader_zh->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );

     TString dir_2 = "ZH_vs_Backgrounds/dataset/weights/"; // Path to your ZH "weights" directory
     TString prefix_2 = "Grad_Optimal_v1";		   // Name of the "weight" file you want to evaluate for the ZH signal (without the .weights.xml)
     for (std::map<std::string,int>::iterator it = Use_ZH.begin(); it != Use_ZH.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_2 + prefix_2 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_zh->BookMVA( methodName, weightfile );
         }
     }

     TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_090123_metFix/Run2/";  // Path pointing towards your MC file directory
     std::vector<TString> files = {"NonResWWZ.root", "ZHWWZ.root", "TTZ.root", "ZZ.root", "Higgs.root", "WZ.root", "Other.root"};  // Name of MC files that we want to evaluate

     ofstream mva_scores;
     mva_scores.open("mva_scores_OF.txt");  // This is the output text file containing the mva scores for each event

     // Loop over MC files
     for (auto f: files){
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
          tree->SetBranchAddress("dR_WW_Z", &dR_WW_Z);
          tree->SetBranchAddress("MET", &MET);
          tree->SetBranchAddress("MT2", &MT2);
          tree->SetBranchAddress("Pt4l", &Pt4l);
          tree->SetBranchAddress("STLepHad", &STLepHad);
          tree->SetBranchAddress("STLep", &STLep );
          tree->SetBranchAddress("leading_Zcand_pt", &leading_Zcand_pt);
          tree->SetBranchAddress("subleading_Zcand_pt", &subleading_Zcand_pt);
          tree->SetBranchAddress("leading_Wcand_pt", &leading_Wcand_pt);
          tree->SetBranchAddress("subleading_Wcand_pt", &subleading_Wcand_pt);
          tree->SetBranchAddress("weight", &weight);

          int proc = 0;

          if ( f == "NonResWWZ.root" ) proc += 0;
          if ( f == "ZHWWZ.root" ) proc += 1;
          if ( f == "TTZ.root" ) proc += 2;
          if ( f == "ZZ.root"  ) proc += 3;
	  if ( f == "Higgs.root" ) proc += 4;
	  if ( f == "WZ.root" ) proc += 5;
	  if ( f == "Other.root" ) proc += 6;

          for (Long64_t ievt=0; ievt<tree->GetEntries(); ievt++){
               if (ievt%1000 == 0){
                   std::cout << "--- ... Processing event: " << ievt << std::endl;
               }

               tree->GetEntry(ievt);

               float mva_wwz = reader_wwz->EvaluateMVA("BDTG_T400_LR0p1_D2 method");
               float mva_zh = reader_zh->EvaluateMVA("BDTG_T400_LR0p1_D2 method");

               mva_scores << proc << " " << mva_wwz << " " << mva_zh << " " << weight << " \n"; // This is what writes the process, mva_scores, and weights into the text file              

          } 

          std::cout << "End of event loop!" << std::endl;

     } 

     mva_scores.close();

     std::cout << "Stored mva scores in text file: mva_scores_OF.txt" << std::endl;      

     //TMVA::Reader *r_wwz = Book_WWZ(Use, "test_Grad_v1");
     //TMVA::Reader *r_zh  = Book_ZH(Use, "test_Grad_v1");           

     //calcMVAs(r_wwz, r_zh);

}
