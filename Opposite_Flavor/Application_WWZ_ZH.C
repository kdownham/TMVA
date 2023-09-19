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

     Use_ZH["BDTG_T400_LR0p1_D2"]            = 1;
     Use_WWZ["BDTG_T400_LR0p1_D2"]           = 1;  // Need to use the same method as utilized during the training

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

     TMVA::Reader *reader_wwz = new TMVA::Reader( "!Color:!Silent" );
     TMVA::Reader *reader_zh = new TMVA::Reader( "!Color:!Silent" );

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

     TString dir_1 = "WWZ_vs_Backgrounds/dataset/weights/";
     TString prefix_1 = "Grad_Optimal_v1";
     for (std::map<std::string,int>::iterator it = Use_WWZ.begin(); it != Use_WWZ.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_1 + prefix_1 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_wwz->BookMVA( methodName, weightfile );
         }
     }

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

     TString dir_2 = "ZH_vs_Backgrounds/dataset/weights/";
     TString prefix_2 = "Grad_Optimal_v1";
     for (std::map<std::string,int>::iterator it = Use_ZH.begin(); it != Use_ZH.end(); it++) {
         if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir_2 + prefix_2 + TString("_") + TString(it->first) + TString(".weights.xml");
         reader_zh->BookMVA( methodName, weightfile );
         }
     }

     TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_090123_metFix/Run2/";
     std::vector<TString> files = {"NonResWWZ.root", "ZHWWZ.root", "TTZ.root", "ZZ.root"};

     ofstream mva_scores;
     mva_scores.open("mva_scores_OF.txt");

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

          for (Long64_t ievt=0; ievt<tree->GetEntries(); ievt++){
               if (ievt%1000 == 0){
                   std::cout << "--- ... Processing event: " << ievt << std::endl;
               }

               tree->GetEntry(ievt);

               //std::cout << "WWZ score: " << reader_wwz->EvaluateMVA("BDTG method") << std::endl;
               //std::cout << "ZH score : " << reader_zh->EvaluateMVA("BDTG method") << std::endl;

               float mva_wwz = reader_wwz->EvaluateMVA("BDTG_T400_LR0p1_D2 method");
               float mva_zh = reader_zh->EvaluateMVA("BDTG_T400_LR0p1_D2 method");

               mva_scores << proc << " " << mva_wwz << " " << mva_zh << " " << weight << " \n";               

          } 

          std::cout << "End of event loop!" << std::endl;

     } 

     mva_scores.close();

     std::cout << "Stored mva scores in text file: mva_scores_OF.txt" << std::endl;      

     //TMVA::Reader *r_wwz = Book_WWZ(Use, "test_Grad_v1");
     //TMVA::Reader *r_zh  = Book_ZH(Use, "test_Grad_v1");           

     //calcMVAs(r_wwz, r_zh);

}

//TMVA::Reader *Book_WWZ(std::map<std::string,int> method_WWZ, TString weightname_WWZ){
//
//     TMVA::Reader *reader_wwz = new TMVA::Reader( "!Color:!Silent" );
//
//     float m_ll;
//     float dPhi_4Lep_MET;
//     float dPhi_Zcand_MET;
//     float dPhi_WW_MET;
//     float dR_Wcands;
//     float dR_Zcands;
//     float dR_WW_Z;
//     float MET;
//     float MT2;
//     float Pt4l;
//     float STLepHad;
//     float STLep;
//     float leading_Zcand_pt;
//     float subleading_Zcand_pt;
//     float leading_Wcand_pt;
//     float subleading_Wcand_pt;
//     float weight;
//
//     reader_wwz->AddVariable( "m_ll", &m_ll );
//     reader_wwz->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
//     reader_wwz->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
//     reader_wwz->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
//     reader_wwz->AddVariable( "dR_Wcands", &dR_Wcands );
//     reader_wwz->AddVariable( "dR_Zcands", &dR_Zcands );
//     reader_wwz->AddVariable( "dR_WW_Z", &dR_WW_Z );
//     reader_wwz->AddVariable( "MET", &MET );
//     reader_wwz->AddVariable( "MT2", &MT2 );
//     reader_wwz->AddVariable( "Pt4l", &Pt4l );
//     reader_wwz->AddVariable( "STLepHad", &STLepHad );
//     reader_wwz->AddVariable( "STLep", &STLep );
//     reader_wwz->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
//     reader_wwz->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
//     reader_wwz->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
//     reader_wwz->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );
//
//     TString dir = "WWZ_vs_Backgrounds/dataset/weights/";
//     TString prefix = weightname_WWZ;
//     for (std::map<std::string,int>::iterator it = method_WWZ.begin(); it != method_WWZ.end(); it++) {
//         if (it->second) {
//         TString methodName = TString(it->first) + TString(" method");
//         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
//         reader_wwz->BookMVA( methodName, weightfile );
//         }
//     }
//
//     return reader_wwz;        
//
//}
//
//TMVA::Reader *Book_ZH(std::map<std::string,int> method_ZH, TString weightname_ZH){
//
//     TMVA::Reader *reader_zh = new TMVA::Reader( "!Color:!Silent" );
//
//     float m_ll;
//     float dPhi_4Lep_MET;
//     float dPhi_Zcand_MET;
//     float dPhi_WW_MET;
//     float dR_Wcands;
//     float dR_Zcands;
//     float dR_WW_Z;
//     float MET;
//     float MT2;
//     float Pt4l;
//     float STLepHad;
//     float STLep;
//     float leading_Zcand_pt;
//     float subleading_Zcand_pt;
//     float leading_Wcand_pt;
//     float subleading_Wcand_pt;
//     float weight;
//
//     reader_zh->AddVariable( "m_ll", &m_ll );
//     reader_zh->AddVariable( "dPhi_4Lep_MET", &dPhi_4Lep_MET );
//     reader_zh->AddVariable( "dPhi_Zcand_MET", &dPhi_Zcand_MET );
//     reader_zh->AddVariable( "dPhi_WW_MET", &dPhi_WW_MET );
//     reader_zh->AddVariable( "dR_Wcands", &dR_Wcands );
//     reader_zh->AddVariable( "dR_Zcands", &dR_Zcands );
//     reader_zh->AddVariable( "dR_WW_Z", &dR_WW_Z );
//     reader_zh->AddVariable( "MET", &MET );
//     reader_zh->AddVariable( "MT2", &MT2 );
//     reader_zh->AddVariable( "Pt4l", &Pt4l );
//     reader_zh->AddVariable( "STLepHad", &STLepHad );
//     reader_zh->AddVariable( "STLep", &STLep );
//     reader_zh->AddVariable( "leading_Zcand_pt", &leading_Zcand_pt );
//     reader_zh->AddVariable( "subleading_Zcand_pt", &subleading_Zcand_pt );
//     reader_zh->AddVariable( "leading_Wcand_pt", &leading_Wcand_pt );
//     reader_zh->AddVariable( "subleading_Wcand_pt", &subleading_Wcand_pt );
//
//     TString dir = "ZH_vs_Backgrounds/dataset/weights/";
//     TString prefix = weightname_ZH;
//     for (std::map<std::string,int>::iterator it = method_ZH.begin(); it != method_ZH.end(); it++) {
//         if (it->second) {
//         TString methodName = TString(it->first) + TString(" method");
//         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
//         reader_zh->BookMVA( methodName, weightfile );
//         }
//     }
//
//     return reader_zh;     
//
//}
//
//void calcMVAs(TMVA::Reader *r1, TMVA::Reader *r2){
//
//     TString path = "/home/users/kdownham/Triboson/VVVNanoLooper/analysis/output_081723_metUpdate/Run2/";
//     std::vector<TString> files = {"NonResWWZ.root", "ZHWWZ.root", "TTZ.root", "ZZ.root"};
//
//     ofstream mva_scores;
//     mva_scores.open("mva_scores_SF.txt");
//
//     float m_ll;
//     float dPhi_4Lep_MET;
//     float dPhi_Zcand_MET;
//     float dPhi_WW_MET;
//     float dR_Wcands;
//     float dR_Zcands;
//     float dR_WW_Z;
//     float MET;
//     float MT2;
//     float Pt4l;
//     float STLepHad;
//     float STLep;
//     float leading_Zcand_pt;
//     float subleading_Zcand_pt;
//     float leading_Wcand_pt;
//     float subleading_Wcand_pt;
//     float weight;
//
//     // Loop over files
//
//     for (auto f: files){
//	  std::cout << "=============================================================" << std::endl;
//	  std::cout << "Calculating MVA scores for events in file: " << f << std::endl;
//          TFile *input = TFile::Open( path+f );
//          TTree *tree  = (TTree*)input->Get("t_BDT_SF");
//          tree->SetBranchAddress("m_ll", &m_ll);
//          tree->SetBranchAddress("dPhi_4Lep_MET", &dPhi_4Lep_MET);
//          tree->SetBranchAddress("dPhi_Zcand_MET", &dPhi_Zcand_MET);
//          tree->SetBranchAddress("dPhi_WW_MET", &dPhi_WW_MET);
//          tree->SetBranchAddress("dR_Wcands", &dR_Wcands);
//          tree->SetBranchAddress("dR_Zcands", &dR_Zcands);
//	  tree->SetBranchAddress("dR_WW_Z", &dR_WW_Z);
//          tree->SetBranchAddress("MET", &MET);
//          tree->SetBranchAddress("MT2", &MT2);
//          tree->SetBranchAddress("Pt4l", &Pt4l);
//          tree->SetBranchAddress("STLepHad", &STLepHad);
//	  tree->SetBranchAddress("STLep", &STLep);
//          tree->SetBranchAddress("leading_Zcand_pt", &leading_Zcand_pt);
//          tree->SetBranchAddress("subleading_Zcand_pt", &subleading_Zcand_pt);
//          tree->SetBranchAddress("leading_Wcand_pt", &leading_Wcand_pt);
//          tree->SetBranchAddress("subleading_Wcand_pt", &subleading_Wcand_pt);
//          tree->SetBranchAddress("weight", &weight);
//
//          TString proc = "";
//
//	  if ( f == "NonResWWZ.root" ) proc += "NonResWWZ";
//	  if ( f == "ZHWWZ.root" ) proc += "ZHWWZ";
//	  if ( f == "TTZ.root" ) proc += "TTZ";
//	  if ( f == "ZZ.root"  ) proc += "ZZ";
//
//          for (Long64_t ievt=0; ievt<tree->GetEntries(); ievt++){
//	       if (ievt%1000 == 0){
//		   std::cout << "--- ... Processing event: " << ievt << std::endl;
//	       }
//	
//	       tree->GetEntry(ievt);
//
//	       std::cout << "WWZ score: " << r1->EvaluateMVA("BDTG method") << std::endl;
//	       std::cout << "ZH score : " << r2->EvaluateMVA("BDTG method") << std::endl;
//
//               float mva_wwz = r1->EvaluateMVA("BDTG method");
//	       float mva_zh = r2->EvaluateMVA("BDTG method");
//
//               mva_scores << proc << " " << mva_wwz << " " << mva_zh << " " << weight << " \n";              
//
//	  }
//
//	  std::cout << "End of event loop!" << std::endl;
//
//     }
//
//     mva_scores.close();
//
//     std::cout << "Stored mva scores in text file: mva_scores_SF.txt" << std::endl;
//
//}
