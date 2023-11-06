#include <iostream>
#include <fstream>

std::vector<TH1F*> WWZ_hists(int nbin);
std::vector<TH1F*> ZH_hists(int nbin);

void plotHists(bool draw2Donly=true, bool makeSRs=true, bool drawSRs=false, bool makeDatacard=true, bool makeLatex=false){

     int nbin = 50;
     int LW = 5;

     TString tag = "Sync_110623";
     TString file = "mva_scores_Sync_110623.root";
     TFile *f = TFile::Open(file);

     Int_t process;
     Float_t wwz_score;
     Float_t zh_score;
     Float_t weight;

     TTree *t = (TTree*)f->Get("T");

     t->SetBranchAddress("process",&process);
     t->SetBranchAddress("wwz_score",&wwz_score);
     t->SetBranchAddress("zh_score",&zh_score);
     t->SetBranchAddress("weight",&weight);

     THStack *hs_wwz = new THStack("hs_wwz","WWZ MVA score (Opposite Flavor Channel);MVA score;Events");
     THStack *hs_zh = new THStack("hs_zh","ZH MVA score (Opposite Flavor Channel);MVA score;Events");

     TH2F *histBDT_WWZ = new TH2F("MVA_BDT_WWZ","MVA_BDT_WWZ", nbin, -1.3, 1.3, nbin, -1.3, 1.3 );
     TH2F *histBDT_ZH  = new TH2F("MVA_BDT_ZH" ,"MVA_BDT_ZH" , nbin, -1.3, 1.3, nbin, -1.3, 1.3 );
     TH2F *histBDT_BKG = new TH2F("MVA_BDT_BKG","MVA_BDT_BKG", nbin, -1.3, 1.3, nbin, -1.3, 1.3 );
     //TH2F *histBDT_ZZ  = new TH2F("MVA_BDT_ZZ" ,"MVA_BDT_ZZ" , nbin, -1.0, 1.0, nbin, -1.0, 1.0 );

     std::vector<TH1F*> vec_WWZ = WWZ_hists(nbin);
     std::vector<TH1F*> vec_ZH  = ZH_hists(nbin);


     float c1_wwz = 0.;         
     float c2_wwz = 0.;  
     float c3_wwz = 0.;    
     float c4_wwz = 0.;
     float c5_wwz = 0.;
     float c6_wwz = 0.;
     float c7_wwz = 0.;
     float c8_wwz = 0.;

     float c1_wwz_error = 0.;
     float c2_wwz_error = 0.;
     float c3_wwz_error = 0.;
     float c4_wwz_error = 0.;
     float c5_wwz_error = 0.;
     float c6_wwz_error = 0.;
     float c7_wwz_error = 0.;
     float c8_wwz_error = 0.;

     float c1_zh = 0.;
     float c2_zh = 0.;
     float c3_zh = 0.;
     float c4_zh = 0.;
     float c5_zh = 0.;
     float c6_zh = 0.;
     float c7_zh = 0.;
     float c8_zh = 0.;

     float c1_zh_error = 0.;
     float c2_zh_error = 0.;
     float c3_zh_error = 0.;
     float c4_zh_error = 0.;
     float c5_zh_error = 0.;
     float c6_zh_error = 0.;
     float c7_zh_error = 0.;
     float c8_zh_error = 0.;

     float c1_zz = 0.;
     float c2_zz = 0.;
     float c3_zz = 0.;
     float c4_zz = 0.;
     float c5_zz = 0.;
     float c6_zz = 0.;
     float c7_zz = 0.;
     float c8_zz = 0.;

     float c1_zz_error = 0.;
     float c2_zz_error = 0.;
     float c3_zz_error = 0.;
     float c4_zz_error = 0.;
     float c5_zz_error = 0.;
     float c6_zz_error = 0.;
     float c7_zz_error = 0.;
     float c8_zz_error = 0.;

     float c1_ttz = 0.;
     float c2_ttz = 0.;
     float c3_ttz = 0.;
     float c4_ttz = 0.;
     float c5_ttz = 0.;
     float c6_ttz = 0.;
     float c7_ttz = 0.;
     float c8_ttz = 0.;

     float c1_ttz_error = 0.;
     float c2_ttz_error = 0.;
     float c3_ttz_error = 0.;
     float c4_ttz_error = 0.;
     float c5_ttz_error = 0.;
     float c6_ttz_error = 0.;
     float c7_ttz_error = 0.;
     float c8_ttz_error = 0.;

     float c1_twz = 0.;
     float c2_twz = 0.;
     float c3_twz = 0.;
     float c4_twz = 0.;
     float c5_twz = 0.;
     float c6_twz = 0.;
     float c7_twz = 0.;
     float c8_twz = 0.;

     float c1_twz_error = 0.;
     float c2_twz_error = 0.;
     float c3_twz_error = 0.;
     float c4_twz_error = 0.;
     float c5_twz_error = 0.;
     float c6_twz_error = 0.;
     float c7_twz_error = 0.;
     float c8_twz_error = 0.;
  
     float c1_wz = 0.;
     float c2_wz = 0.;
     float c3_wz = 0.;
     float c4_wz = 0.;
     float c5_wz = 0.;
     float c6_wz = 0.;
     float c7_wz = 0.;
     float c8_wz = 0.;

     float c1_wz_error = 0.;
     float c2_wz_error = 0.;
     float c3_wz_error = 0.;
     float c4_wz_error = 0.;
     float c5_wz_error = 0.;
     float c6_wz_error = 0.;
     float c7_wz_error = 0.;
     float c8_wz_error = 0.;

     float c1_vvv = 0.;
     float c2_vvv = 0.;
     float c3_vvv = 0.;
     float c4_vvv = 0.;
     float c5_vvv = 0.;
     float c6_vvv = 0.;
     float c7_vvv = 0.;
     float c8_vvv = 0.;

     float c1_vvv_error = 0.;
     float c2_vvv_error = 0.;
     float c3_vvv_error = 0.;
     float c4_vvv_error = 0.;
     float c5_vvv_error = 0.;
     float c6_vvv_error = 0.;
     float c7_vvv_error = 0.;
     float c8_vvv_error = 0.;

     float c1_other = 0.;
     float c2_other = 0.;
     float c3_other = 0.;
     float c4_other = 0.;
     float c5_other = 0.;
     float c6_other = 0.;
     float c7_other = 0.;
     float c8_other = 0.;

     float c1_other_error = 0.;
     float c2_other_error = 0.;
     float c3_other_error = 0.;
     float c4_other_error = 0.;
     float c5_other_error = 0.;
     float c6_other_error = 0.;
     float c7_other_error = 0.;
     float c8_other_error = 0.;

     float c1_bkg = 0.;
     float c2_bkg = 0.;
     float c3_bkg = 0.;
     float c4_bkg = 0.;
     float c5_bkg = 0.;
     float c6_bkg = 0.;
     float c7_bkg = 0.;
     float c8_bkg = 0.;

     float c1_bkg_error = 0.;
     float c2_bkg_error = 0.;
     float c3_bkg_error = 0.;
     float c4_bkg_error = 0.;
     float c5_bkg_error = 0.;
     float c6_bkg_error = 0.;
     float c7_bkg_error = 0.;
     float c8_bkg_error = 0.;
 
     // Loop over events
     for (int i=0; i<t->GetEntries(); i++){
	  t->GetEntry(i);

          bool wwz_SR1 = ( wwz_score > 0.7 && zh_score < -0.3 );
          bool wwz_SR2 = ( wwz_score < 0.7 && wwz_score > 0.4 && zh_score < -0.6 );
          bool zh_SR1  = ( wwz_score > 0.5 && zh_score > 0.7 );
          bool zh_SR2  = ( wwz_score < 0.5 && wwz_score > -0.2 && zh_score > 0.7 );
          bool original_SRs = ( wwz_SR1 && wwz_SR2 && zh_SR1 && zh_SR2 );
          bool wwz_SR3 = ( !original_SRs && wwz_score > 0.0 && zh_score < (0.8*(wwz_score-1.)) );
          bool wwz_SR4 = ( (!original_SRs && !wwz_SR3) && wwz_score > 0.0 );
          bool zh_SR3  = ( (!original_SRs && !wwz_SR3 && !wwz_SR4) && zh_score > 0.5 );
          bool zh_SR4  = ( (!original_SRs && !wwz_SR3 && !wwz_SR4 && !zh_SR3) && zh_score > 0.0 && wwz_score > -0.5 );


	  // Fill histograms
	  if ( process == 0 ){
               if (weight > 0.0) histBDT_WWZ->Fill(wwz_score,zh_score,weight);
	       vec_WWZ[0]->Fill(wwz_score,weight);
	       vec_ZH[0]->Fill(zh_score,weight);
	       vec_WWZ[3]->Fill(wwz_score,weight);
               vec_ZH[3]->Fill(zh_score,weight);
               if ( wwz_SR1 ){ 
		    c1_wwz += weight;
		    c1_wwz_error += std::pow(weight,2.);
	       }
	       if ( wwz_SR2 ){ 
		    c2_wwz += weight;
		    c2_wwz_error += std::pow(weight,2.);
	       }
	       if ( zh_SR1 ){  
		    c3_wwz += weight;
		    c3_wwz_error += std::pow(weight,2.);
	       }
	       if ( zh_SR2 ){  
		    c4_wwz += weight;
		    c4_wwz_error += std::pow(weight,2.);
	       }
	       if ( wwz_SR3 ){
                    c5_wwz += weight;
                    c5_wwz_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_wwz += weight;
                    c6_wwz_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_wwz += weight;
                    c7_wwz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_wwz += weight;
                    c8_wwz_error += std::pow(weight,2.);
               }
               
          }
	  if ( process == 1 ){
               if (weight > 0.0) histBDT_ZH->Fill(wwz_score,zh_score,weight);
	       vec_WWZ[1]->Fill(wwz_score,weight);
               vec_ZH[1]->Fill(zh_score,weight);
	       vec_WWZ[3]->Fill(wwz_score,weight);
               vec_ZH[3]->Fill(zh_score,weight);
	       if ( wwz_SR1 ){ 
                    c1_zh += weight;
                    c1_zh_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){ 
                    c2_zh += weight;
                    c2_zh_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){  
                    c3_zh += weight;
                    c3_zh_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){  
                    c4_zh += weight;
                    c4_zh_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_zh += weight;
                    c5_zh_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_zh += weight;
                    c6_zh_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_zh += weight;
                    c7_zh_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_zh += weight;
                    c8_zh_error += std::pow(weight,2.);
               }
          }
          if ( process == 2 || process == 3 || process == 4 || process == 5 || process == 6 || process == 7){
	       if (weight > 0.0) histBDT_BKG->Fill(wwz_score,zh_score,weight);
               vec_WWZ[2]->Fill(wwz_score,weight);
               vec_ZH[2]->Fill(zh_score,weight);
	       if ( wwz_SR1 ){
                    c1_bkg += weight;
                    c1_bkg_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_bkg += weight;
                    c2_bkg_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_bkg += weight;
                    c3_bkg_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_bkg += weight;
                    c4_bkg_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_bkg += weight;
                    c5_bkg_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_bkg += weight;
                    c6_bkg_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_bkg += weight;
                    c7_bkg_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_bkg += weight;
                    c8_bkg_error += std::pow(weight,2.);
               }
          }
	  if ( process == 2 ){
	       if ( wwz_SR1 ){
                    c1_ttz += weight;
                    c1_ttz_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_ttz += weight;
                    c2_ttz_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_ttz += weight;
                    c3_ttz_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_ttz += weight;
                    c4_ttz_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_ttz += weight;
                    c5_ttz_error += std::pow(weight,2.);
               }
               if ( wwz_SR3 ){
                    c6_ttz += weight;
                    c6_ttz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c7_ttz += weight;
                    c7_ttz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_ttz += weight;
                    c8_ttz_error += std::pow(weight,2.);
               }
          }
          if ( process == 3 ){
	       if ( wwz_SR1 ){
                    c1_zz += weight;
                    c1_zz_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_zz += weight;
                    c2_zz_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_zz += weight;
                    c3_zz_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_zz += weight;
                    c4_zz_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_zz += weight;
                    c5_zz_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_zz += weight;
                    c6_zz_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_zz += weight;
                    c7_zz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_zz += weight;
                    c8_zz_error += std::pow(weight,2.);
               }
          }
	  if ( process == 4 ){
	       if ( wwz_SR1 ){
                    c1_twz += weight;
                    c1_twz_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_twz += weight;
                    c2_twz_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_twz += weight;
                    c3_twz_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_twz += weight;
                    c4_twz_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_twz += weight;
                    c5_twz_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_twz += weight;
                    c6_twz_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_twz += weight;
                    c7_twz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_twz += weight;
                    c8_twz_error += std::pow(weight,2.);
               }
          }
	  if ( process == 5 ){
	       if ( wwz_SR1 ){
                    c1_wz += weight;
                    c1_wz_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_wz += weight;
                    c2_wz_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_wz += weight;
                    c3_wz_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_wz += weight;
                    c4_wz_error += std::pow(weight,2.);
               }
               if ( wwz_SR3 ){
                    c5_wz += weight;
                    c5_wz_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_wz += weight;
                    c6_wz_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_wz += weight;
                    c7_wz_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_wz += weight;
                    c8_wz_error += std::pow(weight,2.);
               }
          }
	  if ( process == 6 ){
	       if ( wwz_SR1 ){
                    c1_other += weight;
                    c1_other_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_other += weight;
                    c2_other_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_other += weight;
                    c3_other_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_other += weight;
                    c4_other_error += std::pow(weight,2.);
               }
	       if ( wwz_SR3 ){
                    c5_other += weight;
                    c5_other_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_other += weight;
                    c6_other_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_other += weight;
                    c7_other_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_other += weight;
                    c8_other_error += std::pow(weight,2.);
               }
          }
          if ( process == 7 ){
               if ( wwz_SR1 ){
                    c1_vvv += weight;
                    c1_vvv_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_vvv += weight;
                    c2_vvv_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_vvv += weight;
                    c3_vvv_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_vvv += weight;
                    c4_vvv_error += std::pow(weight,2.);
               }
               if ( wwz_SR3 ){
                    c5_vvv += weight;
                    c5_vvv_error += std::pow(weight,2.);
               }
               if ( wwz_SR4 ){
                    c6_vvv += weight;
                    c6_vvv_error += std::pow(weight,2.);
               }
               if ( zh_SR3 ){
                    c7_vvv += weight;
                    c7_vvv_error += std::pow(weight,2.);
               }
               if ( zh_SR4 ){
                    c8_vvv += weight;
                    c8_vvv_error += std::pow(weight,2.);
               }
          }

     }


     histBDT_WWZ->SetLineColor(kRed);
     histBDT_WWZ->SetMarkerColorAlpha(kRed,0.05);
     histBDT_WWZ->SetMarkerStyle(42);
     histBDT_WWZ->SetMarkerSize(0.1);
     vec_WWZ[0]->SetLineColor(kRed);
     vec_ZH[0]->SetLineColor(kRed);
     vec_WWZ[0]->SetLineWidth(LW);
     vec_ZH[0]->SetLineWidth(LW);
     histBDT_ZH->SetLineColor(kBlue);
     histBDT_ZH->SetMarkerColorAlpha(kBlue,0.05);
     histBDT_ZH->SetMarkerStyle(25);
     histBDT_ZH->SetMarkerSize(0.1);
     vec_WWZ[1]->SetLineColor(kBlue);
     vec_ZH[1]->SetLineColor(kBlue);
     vec_WWZ[1]->SetLineWidth(LW);
     vec_ZH[1]->SetLineWidth(LW);
     histBDT_BKG->SetLineColor(kGreen);
     histBDT_BKG->SetMarkerColorAlpha(kGreen,0.05);
     histBDT_BKG->SetMarkerStyle(24);
     histBDT_BKG->SetMarkerSize(0.1);
     vec_WWZ[2]->SetLineColor(kOrange);
     vec_ZH[2]->SetLineColor(kOrange);
     vec_WWZ[2]->SetLineWidth(LW);
     vec_ZH[2]->SetLineWidth(LW);
     vec_WWZ[3]->SetLineColor(kBlack);
     vec_ZH[3]->SetLineColor(kBlack);
     vec_WWZ[3]->SetLineWidth(LW);
     vec_ZH[3]->SetLineWidth(LW);

     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     legend->AddEntry(histBDT_WWZ,"NonResonant WWZ","f");
     legend->AddEntry(histBDT_ZH, "ZH #rightarrow WWZ","f");
     legend->AddEntry(histBDT_BKG,"#Sigma Backgrounds","f");
     legend->AddEntry(vec_WWZ[3], "#Sigma Signals","f");

     TLegend* legend1 = new TLegend(0.80,0.80,0.9,0.9,"","NDC");
     legend1->SetBorderSize(0);
     legend1->SetTextFont(43);
     legend1->SetTextAlign(12);
     legend1->SetLineColor(1);
     legend1->SetLineStyle(1);
     legend1->SetLineWidth(1);
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);

     legend1->AddEntry(histBDT_WWZ,"NonResonant WWZ","f");
     legend1->AddEntry(histBDT_ZH, "ZH #rightarrow WWZ","f");
     legend1->AddEntry(histBDT_BKG,"#Sigma Backgrounds","f");

     for (int k=0; k<vec_WWZ.size(); k++){
	  hs_wwz->Add(vec_WWZ[k]);
     }

     for (int j=0; j<vec_ZH.size(); j++){
          hs_zh->Add(vec_ZH[j]);
     }

     if (!draw2Donly && !makeSRs){
 
     	TCanvas *cs = new TCanvas("cs","cs",10,10,1400,900);
     	cs->cd();
     	hs_wwz->Draw("nostack hist");
     	legend->Draw();
     	cs->Print("MVAPlots/WWZ_scores.png");

     	TCanvas *cs1 = new TCanvas("cs1","cs1",10,10,1400,900);
     	cs1->cd();
     	hs_zh->Draw("nostack hist");
     	legend->Draw();
     	cs1->Print("MVAPlots/ZH_scores.png");

     }

     if (!makeSRs){
         TCanvas *cs3 = new TCanvas("cs3","cs3",10,10,1400,900);
         //cs3->Divide(2,2);
         //cs3->cd(1);
         //histBDT_WWZ->SetStats(0);
         //histBDT_WWZ->Draw("SCAT");
         //histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         //histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_WWZ->SetStats(0);
         ////histBDT_WWZ->Draw("SCAT");
         ////histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         ////histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_ZH->Draw("cont4 same");
         ////histBDT_BKG->Draw("cont4 same");
         //cs3->cd(2);
         //histBDT_ZH->SetStats(0);
         //histBDT_ZH->Draw("SCAT");
         //histBDT_ZH->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         //histBDT_ZH->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_WWZ->SetStats(0);
         ////histBDT_WWZ->Draw("cont2");
         ////histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         ////histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_ZH->Draw("cont2 same");
         ////histBDT_BKG->Draw("cont2 same");
         //cs3->cd(3);
         //histBDT_BKG->SetStats(0);
         //histBDT_BKG->Draw("SCAT");
         //histBDT_BKG->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         //histBDT_BKG->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_WWZ->SetStats(0);
         ////histBDT_WWZ->Draw("cont5");
         ////histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         ////histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
         ////histBDT_ZH->Draw("cont5 same");
         ////histBDT_BKG->Draw("cont5 same");
         cs3->cd();
         TLine* SR1_L1 = new TLine(0.7,-0.3,0.7,-1.0);
         TLine* SR1_L2 = new TLine(0.7,-0.3,1.0,-0.3);
         TLine* SR2_L1 = new TLine(0.4,-0.6,0.7,-0.6);
	 TLine* SR2_L2 = new TLine(0.4,-0.6,0.4,-1.0);
         TLine* SR3_L1 = new TLine(0.5,0.7,1.0,0.7);
	 TLine* SR3_L2 = new TLine(0.5,0.7,0.5,1.0);
         TLine* SR4_L1 = new TLine(-0.2,0.7,-0.2,1.0);
         TLine* SR4_L2 = new TLine(-0.2,0.7,0.5,0.7);
         histBDT_WWZ->SetStats(0);
         histBDT_WWZ->Draw("SCAT");
         histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
	 histBDT_ZH->Draw("SCAT same");
	 histBDT_BKG->Draw("SCAT same");
	 legend1->Draw();
         TString h = "";

         if ( drawSRs ){
	      SR1_L1->SetLineWidth(3);
              SR1_L2->SetLineWidth(3);
              SR2_L1->SetLineWidth(3);
              SR2_L2->SetLineWidth(3);
              SR3_L1->SetLineWidth(3);
              SR3_L2->SetLineWidth(3);
              SR4_L1->SetLineWidth(3);
              SR4_L2->SetLineWidth(3);
	      SR1_L1->Draw();
	      SR1_L2->Draw();
	      SR2_L1->Draw();
	      SR2_L2->Draw();
	      SR3_L1->Draw();
              SR3_L2->Draw();
              SR4_L1->Draw();
              SR4_L2->Draw();
	      h += "_SRs";
	 }
         cs3->Print("MVAPlots/WWZ_ZH_2D_scores"+h+".png");
     }   

     if (makeSRs){
	 std::cout << "Printing yields in Signal Regions" << std::endl;
	 std::cout << "=============================================" << std::endl;
	 std::cout << "WWZ SR1" << std::endl;
	 std::cout << "WWZ: " << c1_wwz << "+/-" << std::sqrt(c1_wwz_error) << " events" << std::endl;
	 std::cout << "ZH:  " << c1_zh  << "+/-" << std::sqrt(c1_zh_error)  << " events" << std::endl;
         std::cout << "Bkg: " << c1_bkg << "+/-" << std::sqrt(c1_bkg_error) << " events" << std::endl;
	 std::cout << "SENSITIVITY = " << (c1_wwz+c1_zh)/std::sqrt(c1_bkg) << std::endl;
	 std::cout << "---------Background Composition--------------" << std::endl;
	 std::cout << "ZZ: "    << c1_zz      << "+/-" << std::sqrt(c1_zz_error) << " events" << std::endl;
	 std::cout << "ttZ: "   << c1_ttz     << "+/-" << std::sqrt(c1_ttz_error) << " events" << std::endl;
	 std::cout << "tWZ: "   << c1_twz   << "+/-" << std::sqrt(c1_twz_error) << " events" << std::endl;
	 std::cout << "WZ: "    << c1_wz      << "+/-" << std::sqrt(c1_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c1_vvv     << "+/-" << std::sqrt(c1_vvv_error) << " events" << std::endl;
	 std::cout << "Other: " << c1_other   << "+/-" << std::sqrt(c1_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "WWZ SR2" << std::endl;
         std::cout << "WWZ: " << c2_wwz << "+/-" << std::sqrt(c2_wwz_error) << " events" << std::endl; 
         std::cout << "ZH:  " << c2_zh  << "+/-" << std::sqrt(c2_zh_error)  << " events" << std::endl;
         std::cout << "Bkg: " << c2_bkg << "+/-" << std::sqrt(c2_bkg_error) << " events" << std::endl;
	 std::cout << "SENSITIVITY = " << (c2_wwz+c2_zh)/std::sqrt(c2_bkg) << std::endl;
	 std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c2_zz      << "+/-" << std::sqrt(c2_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c2_ttz     << "+/-" << std::sqrt(c2_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c2_twz   << "+/-" << std::sqrt(c2_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c2_wz      << "+/-" << std::sqrt(c2_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c2_vvv     << "+/-" << std::sqrt(c2_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c2_other   << "+/-" << std::sqrt(c2_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR1" << std::endl;
         std::cout << "WWZ: " << c3_wwz << "+/-" << std::sqrt(c3_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c3_zh  << "+/-" << std::sqrt(c3_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c3_bkg << "+/-" << std::sqrt(c3_bkg_error) << " events" << std::endl;
	 std::cout << "SENSITIVITY = " << (c3_wwz+c3_zh)/std::sqrt(c3_bkg) << std::endl;
         std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c3_zz      << "+/-" << std::sqrt(c3_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c3_ttz     << "+/-" << std::sqrt(c3_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c3_twz   << "+/-" << std::sqrt(c3_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c3_wz      << "+/-" << std::sqrt(c3_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c3_vvv     << "+/-" << std::sqrt(c3_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c3_other   << "+/-" << std::sqrt(c3_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR2" << std::endl;
         std::cout << "WWZ: " << c4_wwz << "+/-" << std::sqrt(c4_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c4_zh  << "+/-" << std::sqrt(c4_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c4_bkg << "+/-" << std::sqrt(c4_bkg_error) << " events" << std::endl;
	 std::cout << "SENSITIVITY = " << (c4_wwz+c4_zh)/std::sqrt(c4_bkg) << std::endl;
	 std::cout << "---------Background Composition--------------" << std::endl;
	 std::cout << "ZZ: "    << c4_zz      << "+/-" << std::sqrt(c4_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c4_ttz     << "+/-" << std::sqrt(c4_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c4_twz   << "+/-" << std::sqrt(c4_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c4_wz      << "+/-" << std::sqrt(c4_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c4_vvv     << "+/-" << std::sqrt(c4_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c4_other   << "+/-" << std::sqrt(c4_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "WWZ  SR3" << std::endl;
         std::cout << "WWZ: " << c5_wwz << "+/-" << std::sqrt(c5_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c5_zh  << "+/-" << std::sqrt(c5_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c5_bkg << "+/-" << std::sqrt(c5_bkg_error) << " events" << std::endl;
         std::cout << "SENSITIVITY = " << (c5_wwz+c5_zh)/std::sqrt(c5_bkg) << std::endl;
         std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c5_zz      << "+/-" << std::sqrt(c5_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c5_ttz     << "+/-" << std::sqrt(c5_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c5_twz   << "+/-" << std::sqrt(c5_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c5_wz      << "+/-" << std::sqrt(c5_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c5_vvv     << "+/-" << std::sqrt(c5_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c5_other   << "+/-" << std::sqrt(c5_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "WWZ  SR4" << std::endl;
         std::cout << "WWZ: " << c6_wwz << "+/-" << std::sqrt(c6_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c6_zh  << "+/-" << std::sqrt(c6_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c6_bkg << "+/-" << std::sqrt(c6_bkg_error) << " events" << std::endl;
         std::cout << "SENSITIVITY = " << (c6_wwz+c6_zh)/std::sqrt(c6_bkg) << std::endl;
         std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c6_zz      << "+/-" << std::sqrt(c6_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c6_ttz     << "+/-" << std::sqrt(c6_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c6_twz   << "+/-" << std::sqrt(c6_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c6_wz      << "+/-" << std::sqrt(c6_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c6_vvv     << "+/-" << std::sqrt(c6_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c6_other   << "+/-" << std::sqrt(c6_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR3" << std::endl;
         std::cout << "WWZ: " << c7_wwz << "+/-" << std::sqrt(c7_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c7_zh  << "+/-" << std::sqrt(c7_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c7_bkg << "+/-" << std::sqrt(c7_bkg_error) << " events" << std::endl;
         std::cout << "SENSITIVITY = " << (c7_wwz+c7_zh)/std::sqrt(c7_bkg) << std::endl;
         std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c7_zz      << "+/-" << std::sqrt(c7_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c7_ttz     << "+/-" << std::sqrt(c7_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c7_twz   << "+/-" << std::sqrt(c7_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c7_wz      << "+/-" << std::sqrt(c7_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c7_vvv     << "+/-" << std::sqrt(c7_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c7_other   << "+/-" << std::sqrt(c7_other_error) << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR4" << std::endl;
         std::cout << "WWZ: " << c8_wwz << "+/-" << std::sqrt(c8_wwz_error) << " events" << std::endl;
         std::cout << "ZH:  " << c8_zh  << "+/-" << std::sqrt(c8_zh_error) << " events" << std::endl;
         std::cout << "Bkg: " << c8_bkg << "+/-" << std::sqrt(c8_bkg_error) << " events" << std::endl;
         std::cout << "SENSITIVITY = " << (c8_wwz+c8_zh)/std::sqrt(c8_bkg) << std::endl;
         std::cout << "---------Background Composition--------------" << std::endl;
         std::cout << "ZZ: "    << c8_zz      << "+/-" << std::sqrt(c8_zz_error) << " events" << std::endl;
         std::cout << "ttZ: "   << c8_ttz     << "+/-" << std::sqrt(c8_ttz_error) << " events" << std::endl;
         std::cout << "tWZ: "   << c8_twz   << "+/-" << std::sqrt(c8_twz_error) << " events" << std::endl;
         std::cout << "WZ: "    << c8_wz      << "+/-" << std::sqrt(c8_wz_error) << " events" << std::endl;
         std::cout << "VVV: "   << c8_vvv     << "+/-" << std::sqrt(c8_vvv_error) << " events" << std::endl;
         std::cout << "Other: " << c8_other   << "+/-" << std::sqrt(c8_other_error) << " events" << std::endl;

         TH1F* h_SR_wwz   = new TH1F("MVA SR Bins (WWZ)","MVA SR Bins (WWZ)",8,0,8);
	 TH1F* h_SR_zh    = new TH1F("MVA SR Bins (ZH)","MVA SR Bins (ZH)",8,0,8);
	 TH1F* h_SR_zz    = new TH1F("MVA SR Bins (ZZ)","MVA SR Bins (ZZ)",8,0,8);
	 TH1F* h_SR_ttz   = new TH1F("MVA SR Bins (ttZ)","MVA SR Bins (ttZ)",8,0,8);
	 TH1F* h_SR_twz   = new TH1F("MVA SR Bins (tWZ)","MVA SR Bins (Higgs)",8,0,8);
	 TH1F* h_SR_wz    = new TH1F("MVA SR Bins (WZ)","MVA SR Bins (WZ)",8,0,8);
	 TH1F* h_SR_other = new TH1F("MVA SR Bins (Other)","MVA SR Bins (Other)",8,0,8);
         TH1F* h_SR_vvv   = new TH1F("MVA SR Bins (VVV)","MVA SR Bins (VVV)",8,0,8);

	 h_SR_wwz->SetBinContent(1,c1_wwz);
	 h_SR_wwz->SetBinContent(2,c2_wwz);
	 h_SR_wwz->SetBinContent(3,c3_wwz);
	 h_SR_wwz->SetBinContent(4,c4_wwz);
         h_SR_wwz->SetBinContent(5,c5_wwz);
         h_SR_wwz->SetBinContent(6,c6_wwz);
         h_SR_wwz->SetBinContent(7,c7_wwz);
         h_SR_wwz->SetBinContent(8,c8_wwz);
	 h_SR_wwz->SetLineColor(kRed);
	 
	 h_SR_zh->SetBinContent(1,c1_zh);
         h_SR_zh->SetBinContent(2,c2_zh);
         h_SR_zh->SetBinContent(3,c3_zh);
         h_SR_zh->SetBinContent(4,c4_zh);
         h_SR_zh->SetBinContent(5,c5_zh);
         h_SR_zh->SetBinContent(6,c6_zh);
         h_SR_zh->SetBinContent(7,c7_zh);
         h_SR_zh->SetBinContent(8,c8_zh);
	 h_SR_zh->SetLineColor(kBlue);

         h_SR_zz->SetBinContent(1,c1_zz);
         h_SR_zz->SetBinContent(2,c2_zz);
         h_SR_zz->SetBinContent(3,c3_zz);
         h_SR_zz->SetBinContent(4,c4_zz);
         h_SR_zz->SetBinContent(5,c5_zz);
         h_SR_zz->SetBinContent(6,c6_zz);
         h_SR_zz->SetBinContent(7,c7_zz);
         h_SR_zz->SetBinContent(8,c8_zz);
	 h_SR_zz->SetLineColor(kGreen);
         h_SR_zz->SetFillColorAlpha(kGreen,0.1);

	 h_SR_ttz->SetBinContent(1,c1_ttz);
         h_SR_ttz->SetBinContent(2,c2_ttz);
         h_SR_ttz->SetBinContent(3,c3_ttz);
         h_SR_ttz->SetBinContent(4,c4_ttz);
         h_SR_ttz->SetBinContent(5,c5_ttz);
         h_SR_ttz->SetBinContent(6,c6_ttz);
         h_SR_ttz->SetBinContent(7,c7_ttz);
         h_SR_ttz->SetBinContent(8,c8_ttz);
	 h_SR_ttz->SetLineColor(kOrange);
         h_SR_ttz->SetFillColorAlpha(kOrange,0.1);

	 h_SR_twz->SetBinContent(1,c1_twz);
         h_SR_twz->SetBinContent(2,c2_twz);
         h_SR_twz->SetBinContent(3,c3_twz);
         h_SR_twz->SetBinContent(4,c4_twz);
         h_SR_twz->SetBinContent(5,c5_twz);
         h_SR_twz->SetBinContent(6,c6_twz);
         h_SR_twz->SetBinContent(7,c7_twz);
         h_SR_twz->SetBinContent(8,c8_twz);
	 h_SR_twz->SetLineColor(kViolet);
         h_SR_twz->SetFillColorAlpha(kViolet,0.1);

	 h_SR_wz->SetBinContent(1,c1_wz);
         h_SR_wz->SetBinContent(2,c2_wz);
         h_SR_wz->SetBinContent(3,c3_wz);
         h_SR_wz->SetBinContent(4,c4_wz);
         h_SR_wz->SetBinContent(5,c5_wz);
         h_SR_wz->SetBinContent(6,c6_wz);
         h_SR_wz->SetBinContent(7,c7_wz);
         h_SR_wz->SetBinContent(8,c8_wz);
	 h_SR_wz->SetLineColor(kBlack);
         h_SR_wz->SetFillColorAlpha(kBlack,0.1);

	 h_SR_other->SetBinContent(1,c1_other);
         h_SR_other->SetBinContent(2,c2_other);
         h_SR_other->SetBinContent(3,c3_other);
         h_SR_other->SetBinContent(4,c4_other);
         h_SR_other->SetBinContent(5,c5_other);
         h_SR_other->SetBinContent(6,c6_other);
         h_SR_other->SetBinContent(7,c7_other);
         h_SR_other->SetBinContent(8,c8_other);
	 h_SR_other->SetLineColor(7);
	 h_SR_other->SetFillColorAlpha(7,0.1);

         h_SR_vvv->SetBinContent(1,c1_vvv);
         h_SR_vvv->SetBinContent(2,c2_vvv);
         h_SR_vvv->SetBinContent(3,c3_vvv);
         h_SR_vvv->SetBinContent(4,c4_vvv);
         h_SR_vvv->SetBinContent(5,c5_vvv);
         h_SR_vvv->SetBinContent(6,c6_vvv);
         h_SR_vvv->SetBinContent(7,c7_vvv);
         h_SR_vvv->SetBinContent(8,c8_vvv);
         h_SR_vvv->SetLineColor(9);
         h_SR_vvv->SetFillColorAlpha(9,0.1);

         THStack *hs_SR_bkg = new THStack("hs_SR_bkg","Signal Regions (Opposite Flavor Channel);SR Bin;Events");  

         //hs_SR_bkg->GetYaxis()->SetRangeUser(0.,3.);      

         hs_SR_bkg->Add(h_SR_zz);
	 hs_SR_bkg->Add(h_SR_ttz);
         hs_SR_bkg->Add(h_SR_twz);
	 hs_SR_bkg->Add(h_SR_wz);
	 hs_SR_bkg->Add(h_SR_other);
         hs_SR_bkg->Add(h_SR_vvv);

         TLegend* legendSR = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
         legendSR->SetBorderSize(0);
         legendSR->SetTextFont(43);
         legendSR->SetTextAlign(12);
         legendSR->SetLineColor(1);
         legendSR->SetLineStyle(1);
         legendSR->SetLineWidth(1);
         legendSR->SetFillColor(0);
         legendSR->SetFillStyle(0);

	 legendSR->AddEntry(h_SR_wwz,"WWZ","f");
	 legendSR->AddEntry(h_SR_zh, "ZH #rightarrow WWZ","f");
	 legendSR->AddEntry(h_SR_zz, "ZZ","f");
	 legendSR->AddEntry(h_SR_ttz,"t#bar{t}Z","f");
	 legendSR->AddEntry(h_SR_twz,"tWZ","f");
	 legendSR->AddEntry(h_SR_wz,"WZ","f");
	 legendSR->AddEntry(h_SR_other,"Other","f");
         legendSR->AddEntry(h_SR_vvv,"VVV","f");

         TCanvas *cSR = new TCanvas("cSR","cSR",10,10,1400,900);
         cSR->cd();
 	 hs_SR_bkg->SetMaximum(7.);
	 hs_SR_bkg->SetMinimum(0.);
	 hs_SR_bkg->Draw();
	 h_SR_wwz->GetYaxis()->SetRangeUser(0.,8.);
	 h_SR_wwz->SetStats(0);
         h_SR_wwz->SetLineWidth(3);
	 h_SR_zh->SetLineWidth(3);
	 h_SR_wwz->Draw("hist same");
         h_SR_zh->Draw("hist same");
	 //hs_SR_bkg->Draw("same");
	 legendSR->Draw();
	 cSR->Print("MVAPlots/SRBin_Yields_OF.png");

         delete h_SR_wwz;
	 delete h_SR_zh;
	 delete h_SR_zz;
	 delete h_SR_ttz;
	 delete h_SR_twz;
	 delete h_SR_wz;
	 delete h_SR_other;
         delete h_SR_vvv;
	 delete hs_SR_bkg;

     }

     if (makeDatacard){

         ofstream datacard;
	 datacard.open("datacard_mva_OF_"+tag+".txt");	 

         datacard << "imax    " << 8 << " number of bins" << "\n";
         datacard << "jmax    " << 2 << " number of processes minus 1" << "\n";
         datacard << "kmax    " << "*" << " number of nuisance parameters" << "\n";
         datacard << "------------------------------------------------------------------------------" << "\n";
         datacard << "------------------------------------------------------------------------------" << "\n";
         datacard << "bin          " << "SR1     SR2     SR3     SR4     SR5     SR6     SR7     SR8" << "\n";
         datacard << "observation  " << c1_wwz+c1_zh+c1_bkg << " " << c2_wwz+c2_zh+c2_bkg << " " << c3_wwz+c3_zh+c3_bkg << " " << c4_wwz+c4_zh+c4_bkg << " " << c5_wwz+c5_zh+c5_bkg << " " << c6_wwz+c6_zh+c6_bkg << " " << c7_wwz+c7_zh+c7_bkg << " " << c8_wwz+c8_zh+c8_bkg << "\n";
         datacard << "------------------------------------------------------------------------------" << "\n";
         datacard << "bin          SR1     SR1     SR1     SR2     SR2     SR2     SR3     SR3     SR3     SR4     SR4     SR4     SR5     SR5     SR5     SR6     SR6     SR6     SR7     SR7     SR7    SR8   SR8    SR8" << "\n";
         datacard << "process      ZH      WWZ     Bkg     ZH      WWZ     Bkg     ZH      WWZ     Bkg     ZH      WWZ     Bkg     ZH      WWZ     Bkg     ZH      WWZ     Bkg     ZH      WWZ     Bkg    ZH    WWZ    Bkg" << "\n";
         datacard << "process      -1      0       1       -1      0       1       -1      0       1       -1      0       1       -1      0       1       -1      0       1       -1      0       1      -1    0      1" << "\n";
         datacard << "rate         " << c1_zh << " " << c1_wwz << " " << c1_bkg << " " << c2_zh << " " << c2_wwz << " " << c2_bkg << " " << c3_zh << " " << c3_wwz << " " << c3_bkg << " " << c4_zh << " " << c4_wwz << " " << c4_bkg << " " << c5_zh << " " << c5_wwz << " " << c5_bkg << " " << c6_zh << " " << c6_wwz << " " << c6_bkg << " " << c7_zh << " " << c7_wwz << " " << c7_bkg << " " << c8_zh << " " << c8_wwz << " " << c8_bkg << " " << "\n";
         datacard << "------------------------------------------------------------------------------" << "\n";

         datacard.close();
         //std::cout << "Wrote Combine datacard to file: datacard_mva_OF_"+tag+".txt" << std::cout;

     }

     if (makeLatex){

     }

}

std::vector<TH1F*> WWZ_hists(int nbin){ 

     TH1F* h1_wwz = new TH1F("WWZ MVA score (WWZ)","WWZ MVA score (WWZ)",nbin,-1.0,1.0); 
     TH1F* h1_zh  = new TH1F("WWZ MVA score (ZH)","WWZ MVA score (ZH)",nbin,-1.0,1.0); 
     TH1F* h1_bkg = new TH1F("WWZ MVA score (BKG)","WWZ MVA score (BKG)",nbin,-1.0,1.0); 
     TH1F* h1_sig = new TH1F("WWZ MVA score (SIG)","WWZ MVA score (SIG)",nbin,-1.0,1.0); 

     std::vector<TH1F*> hists = {h1_wwz,h1_zh,h1_bkg,h1_sig};

     return hists;

}

std::vector<TH1F*> ZH_hists(int nbin){

     TH1F* h2_wwz = new TH1F("ZH MVA score (WWZ)","ZH MVA score (WWZ)",nbin,-1.0,1.0);
     TH1F* h2_zh  = new TH1F("ZH MVA score (ZH)","ZH MVA score (ZH)",nbin,-1.0,1.0);
     TH1F* h2_bkg = new TH1F("ZH MVA score (BKG)","ZH MVA score (BKG)",nbin,-1.0,1.0);
     TH1F* h2_sig  = new TH1F("ZH MVA score (SIG)","ZH MVA score (SIG)",nbin,-1.0,1.0);

     std::vector<TH1F*> hists = {h2_wwz,h2_zh,h2_bkg,h2_sig};

     return hists;

}
