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

     Use_WWZ["BDTG_LR0p1"]       = 1;  // Need to use the same method as utilized during the training
     Use_ZH["BDTG_LR0p1"]        = 1;

     float m_ll;
     float m_4l;
     float dPhi_4Lep_MET;
     float dPhi_Zcand_MET;
     float dPhi_WW_MET;
     float dPhi_W1_MET;
     float dPhi_W2_MET;
     float dR_Wcands;
     float dR_Zcands;
     float dR_WW_Z;
     float MET;
     float MT2;
     float Pt4l;
     float HT;
     float STLep;
     float leading_Zcand_pt;
     float subleading_Zcand_pt;
     float leading_Wcand_pt;
     float subleading_Wcand_pt;
     float njets;
     float cos_helicity_X;
     float MT_leading_Wcand;
     float MT_subleading_Wcand;
     float MT_Wcands;
     float MT_4Lep;
     float leading_jet_DeepFlav;
     float leading_jet_pt;
     float subleading_jet_pt;
     float min_dR_W1_jet;
     float min_dR_W2_jet;
     float weight;

     TMVA::Reader *reader_wwz = new TMVA::Reader( "!Color:!Silent" );
     TMVA::Reader *reader_zh = new TMVA::Reader( "!Color:!Silent" );

     reader_wwz->AddVariable( "m_ll", &m_ll );
     reader_wwz->AddVariable( "m_4l", &m_4l );
     reader_wwz->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
     reader_wwz->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
     reader_wwz->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
     reader_wwz->AddVariable( "dPhi_W1_MET", &dPhi_W1_MET );
     reader_wwz->AddVariable( "dPhi_W2_MET", &dPhi_W2_MET );
     reader_wwz->AddVariable( "dR_Wcands", &dR_Wcands );
     reader_wwz->AddVariable( "dR_Zcands", &dR_Zcands );
     reader_wwz->AddVariable( "dR_WW_Z", &dR_WW_Z );
     reader_wwz->AddVariable( "MET", &MET );
     reader_wwz->AddVariable( "MT2", &MT2 );
     reader_wwz->AddVariable( "Pt4l", &Pt4l );
     reader_wwz->AddVariable( "HT", &HT );
     reader_wwz->AddVariable( "STLep", &STLep );
     reader_wwz->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
     reader_wwz->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
     reader_wwz->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
     reader_wwz->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );
     reader_wwz->AddVariable( "njets", &njets );
     reader_wwz->AddVariable( "cos_helicity_X", &cos_helicity_X );
     reader_wwz->AddVariable( "MT_leading_Wcand", &MT_leading_Wcand );
     reader_wwz->AddVariable( "MT_subleading_Wcand", &MT_subleading_Wcand );
     reader_wwz->AddVariable( "MT_Wcands", &MT_Wcands );
     reader_wwz->AddVariable( "MT_4Lep", &MT_4Lep );
     //reader_wwz->AddVariable( "leading_jet_DeepFlav", &leading_jet_DeepFlav );
     reader_wwz->AddVariable( "min_dR_W1_jet", &min_dR_W1_jet );
     reader_wwz->AddVariable( "min_dR_W2_jet", &min_dR_W2_jet );

     //reader_wwz->AddSpectator( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
     reader_wwz->AddSpectator( "leading_jet_pt", &leading_jet_pt );
     reader_wwz->AddSpectator( "subleading_jet_pt", &subleading_jet_pt );
     reader_wwz->AddSpectator( "leading_jet_DeepFlav", &leading_jet_DeepFlav );

     TString dir_1 = "WWZ_vs_Backgrounds/dataset/weights/";
     TString prefix_1 = "020824_newBkgd";
     for (std::map<std::string,int>::iterator it = Use_WWZ.begin(); it != Use_WWZ.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_1 + prefix_1 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_wwz->BookMVA( methodName, weightfile );
         }
     }

     reader_zh->AddVariable( "m_ll", &m_ll );
     reader_zh->AddVariable( "m_4l", &m_4l );
     reader_zh->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
     reader_zh->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
     reader_zh->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
     reader_zh->AddVariable( "dPhi_W1_MET", &dPhi_W1_MET );
     reader_zh->AddVariable( "dPhi_W2_MET", &dPhi_W2_MET );
     reader_zh->AddVariable( "dR_Wcands", &dR_Wcands );
     reader_zh->AddVariable( "dR_Zcands", &dR_Zcands );
     reader_zh->AddVariable( "dR_WW_Z", &dR_WW_Z );
     reader_zh->AddVariable( "MET", &MET );
     reader_zh->AddVariable( "MT2", &MT2 );
     reader_zh->AddVariable( "Pt4l", &Pt4l );
     reader_zh->AddVariable( "HT", &HT );
     reader_zh->AddVariable( "STLep", &STLep );
     reader_zh->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
     reader_zh->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
     reader_zh->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
     reader_zh->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );
     reader_zh->AddVariable( "njets", &njets );
     reader_zh->AddVariable( "cos_helicity_X", &cos_helicity_X );
     reader_zh->AddVariable( "MT_leading_Wcand", &MT_leading_Wcand );
     reader_zh->AddVariable( "MT_subleading_Wcand", &MT_subleading_Wcand );
     reader_zh->AddVariable( "MT_Wcands", &MT_Wcands );
     reader_zh->AddVariable( "MT_4Lep", &MT_4Lep );
     //reader_zh->AddVariable( "leading_jet_DeepFlav", &leading_jet_DeepFlav );
     reader_zh->AddVariable( "min_dR_W1_jet", &min_dR_W1_jet );
     reader_zh->AddVariable( "min_dR_W2_jet", &min_dR_W2_jet );

     reader_zh->AddSpectator( "leading_jet_pt", &leading_jet_pt );
     reader_zh->AddSpectator( "subleading_jet_pt", &subleading_jet_pt );
     reader_zh->AddSpectator( "leading_jet_DeepFlav", &leading_jet_DeepFlav );

     TString dir_2 = "ZH_vs_Backgrounds/dataset/weights/";
     TString prefix_2 = "020824_newBkgd";
     for (std::map<std::string,int>::iterator it = Use_ZH.begin(); it != Use_ZH.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_2 + prefix_2 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_zh->BookMVA( methodName, weightfile );
         }
     }

     TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_020724_BDTUpdate/Run2/";
     std::vector<TString> files = {"NonResWWZ.root", "ZHWWZ.root", "TTZ.root", "ZZ.root", "tWZ.root", "WZ.root", "VVV.root", "Other.root"};
     //TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/";
     //std::vector<TString> files = {"test_WWZJets_17_testBDT.root"};

     ofstream mva_scores;
     mva_scores.open("mva_scores_SF.txt");

     for (auto f: files){
          std::cout << "=============================================================" << std::endl;
          std::cout << "Calculating MVA scores for events in file: " << f << std::endl;
          TFile *input = TFile::Open( path+f );
          TTree *tree  = (TTree*)input->Get("t_BDT_SF_train");
          tree->SetBranchAddress( "m_ll", &m_ll );
          tree->SetBranchAddress( "m_4l", &m_4l );
          tree->SetBranchAddress( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
          tree->SetBranchAddress( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
          tree->SetBranchAddress( "dPhi_WW_MET", &dPhi_WW_MET );
          tree->SetBranchAddress( "dPhi_W1_MET", &dPhi_W1_MET );
          tree->SetBranchAddress( "dPhi_W2_MET", &dPhi_W2_MET );
          tree->SetBranchAddress( "dR_Wcands", &dR_Wcands );
          tree->SetBranchAddress( "dR_Zcands", &dR_Zcands );
          tree->SetBranchAddress( "dR_WW_Z", &dR_WW_Z );
          tree->SetBranchAddress( "MET", &MET );
          tree->SetBranchAddress( "MT2", &MT2 );
          tree->SetBranchAddress( "Pt4l", &Pt4l );
          tree->SetBranchAddress( "HT", &HT );
          tree->SetBranchAddress( "STLep", &STLep );
          tree->SetBranchAddress( "leading_Zcand_pt", &leading_Zcand_pt );
          tree->SetBranchAddress( "subleading_Zcand_pt", &subleading_Zcand_pt );
          tree->SetBranchAddress( "leading_Wcand_pt", &leading_Wcand_pt );
          tree->SetBranchAddress( "subleading_Wcand_pt", &subleading_Wcand_pt );
          tree->SetBranchAddress( "njets", &njets );
          tree->SetBranchAddress( "cos_helicity_X", &cos_helicity_X );
          tree->SetBranchAddress( "MT_leading_Wcand", &MT_leading_Wcand );
          tree->SetBranchAddress( "MT_subleading_Wcand", &MT_subleading_Wcand );
          tree->SetBranchAddress( "MT_Wcands", &MT_Wcands );
          tree->SetBranchAddress( "MT_4Lep", &MT_4Lep );
          //tree->SetBranchAddress( "leading_jet_DeepFlav", &leading_jet_DeepFlav );
          tree->SetBranchAddress( "leading_jet_pt", &leading_jet_pt );
          tree->SetBranchAddress( "min_dR_W1_jet", &min_dR_W1_jet );
          tree->SetBranchAddress( "min_dR_W2_jet", &min_dR_W2_jet );
          tree->SetBranchAddress( "weight", &weight);          

          TTree *tree1  = (TTree*)input->Get("t_BDT_SF_test");
          tree1->SetBranchAddress( "m_ll", &m_ll );
          tree1->SetBranchAddress( "m_4l", &m_4l );
          tree1->SetBranchAddress( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
          tree1->SetBranchAddress( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
          tree1->SetBranchAddress( "dPhi_WW_MET", &dPhi_WW_MET );
          tree1->SetBranchAddress( "dPhi_W1_MET", &dPhi_W1_MET );
          tree1->SetBranchAddress( "dPhi_W2_MET", &dPhi_W2_MET );
          tree1->SetBranchAddress( "dR_Wcands", &dR_Wcands );
          tree1->SetBranchAddress( "dR_Zcands", &dR_Zcands );
          tree1->SetBranchAddress( "dR_WW_Z", &dR_WW_Z );
          tree1->SetBranchAddress( "MET", &MET );
          tree1->SetBranchAddress( "MT2", &MT2 );
          tree1->SetBranchAddress( "Pt4l", &Pt4l );
          tree1->SetBranchAddress( "HT", &HT );
          tree1->SetBranchAddress( "STLep", &STLep );
          tree1->SetBranchAddress( "leading_Zcand_pt", &leading_Zcand_pt );
          tree1->SetBranchAddress( "subleading_Zcand_pt", &subleading_Zcand_pt );
          tree1->SetBranchAddress( "leading_Wcand_pt", &leading_Wcand_pt );
          tree1->SetBranchAddress( "subleading_Wcand_pt", &subleading_Wcand_pt );
          tree1->SetBranchAddress( "njets", &njets );
          tree1->SetBranchAddress( "cos_helicity_X", &cos_helicity_X );
          tree1->SetBranchAddress( "MT_leading_Wcand", &MT_leading_Wcand );
          tree1->SetBranchAddress( "MT_subleading_Wcand", &MT_subleading_Wcand );
          tree1->SetBranchAddress( "MT_Wcands", &MT_Wcands );
          tree1->SetBranchAddress( "MT_4Lep", &MT_4Lep );
          //tree1->SetBranchAddress( "leading_jet_DeepFlav", &leading_jet_DeepFlav );
          tree1->SetBranchAddress( "min_dR_W1_jet", &min_dR_W1_jet );
          tree1->SetBranchAddress( "min_dR_W2_jet", &min_dR_W2_jet );
          tree1->SetBranchAddress( "weight", &weight);

          int proc = 0;

          if ( f == "NonResWWZ.root" ) proc += 0;
          if ( f == "ZHWWZ.root" ) proc += 1;
          if ( f == "TTZ.root" ) proc += 2;
          if ( f == "ZZ.root"  ) proc += 3;
	  if ( f == "tWZ.root") proc += 4;
	  if ( f == "WZ.root" ) proc += 5;
	  if ( f == "Other.root" ) proc += 6;
	  if ( f == "VVV.root" ) proc += 7;

          for (Long64_t ievt=0; ievt<tree->GetEntries(); ievt++){
               if (ievt%1000 == 0){
                   std::cout << "--- ... Processing event: " << ievt << std::endl;
               }

               tree->GetEntry(ievt);

               //std::cout << "WWZ score: " << reader_wwz->EvaluateMVA("BDTG method") << std::endl;
               //std::cout << "ZH score : " << reader_zh->EvaluateMVA("BDTG method") << std::endl;

               float mva_wwz = reader_wwz->EvaluateMVA("BDTG_LR0p1 method");
               float mva_zh = reader_zh->EvaluateMVA("BDTG_LR0p1 method");

               mva_scores << proc << " " << mva_wwz << " " << mva_zh << " " << weight << " \n";               

          } 

          for (Long64_t ievt=0; ievt<tree1->GetEntries(); ievt++){
               if (ievt%1000 == 0){
                   std::cout << "--- ... Processing event: " << ievt << std::endl;
               }

               tree1->GetEntry(ievt);

               float mva_wwz = reader_wwz->EvaluateMVA("BDTG_LR0p1 method");
               float mva_zh = reader_zh->EvaluateMVA("BDTG_LR0p1 method");

               mva_scores << proc << " " << mva_wwz << " " << mva_zh << " " << weight << " \n";

          }

          std::cout << "End of event loop!" << std::endl;

     } 

     mva_scores.close();

     std::cout << "Stored mva scores in text file: mva_scores_SF.txt" << std::endl;      

}

