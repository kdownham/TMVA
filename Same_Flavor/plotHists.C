std::vector<TH1F*> WWZ_hists(int nbin);
std::vector<TH1F*> ZH_hists(int nbin);

void plotHists(bool draw2Donly=false, bool makeSRs=true){

     int nbin = 50;
     int LW = 5;

     TString file = "mva_scores.root";
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

     THStack *hs_wwz = new THStack("hs_wwz","WWZ MVA score (Same Flavor Channel);MVA score;Events");
     THStack *hs_zh = new THStack("hs_zh","ZH MVA score (Same Flavor Channel);MVA score;Events");

     TH2F *histBDT_WWZ = new TH2F("MVA_BDT_WWZ","MVA_BDT_WWZ", nbin, -1.0, 1.0, nbin, -1.0, 1.0 );
     TH2F *histBDT_ZH  = new TH2F("MVA_BDT_ZH" ,"MVA_BDT_ZH" , nbin, -1.0, 1.0, nbin, -1.0, 1.0 );
     TH2F *histBDT_TTZ = new TH2F("MVA_BDT_TTZ","MVA_BDT_TTZ", nbin, -1.0, 1.0, nbin, -1.0, 1.0 );
     TH2F *histBDT_ZZ  = new TH2F("MVA_BDT_ZZ" ,"MVA_BDT_ZZ" , nbin, -1.0, 1.0, nbin, -1.0, 1.0 );

     std::vector<TH1F*> vec_WWZ = WWZ_hists(nbin);
     std::vector<TH1F*> vec_ZH  = ZH_hists(nbin);

     float c1_wwz = 0.;
     float c2_wwz = 0.;
     float c3_wwz = 0.;
     float c4_wwz = 0.;

     float c1_zh = 0.;
     float c2_zh = 0.;
     float c3_zh = 0.;
     float c4_zh = 0.;

     float c1_bkg = 0.;
     float c2_bkg = 0.;
     float c3_bkg = 0.;
     float c4_bkg = 0.;
     
     // Loop over events
     for (int i=0; i<t->GetEntries(); i++){
	  t->GetEntry(i);

          bool wwz_SR1 = ( wwz_score > 0.9 && zh_score > 0.8 );
          bool wwz_SR2 = ( wwz_score > 0.9  && zh_score > -0.6 && zh_score < 0.8 );
          bool zh_SR1  = ( wwz_score < 0.9 && wwz_score > 0.7 && zh_score > 0.85 );
          bool zh_SR2  = ( wwz_score < 0.7 && wwz_score > 0.6 && zh_score > 0.85 );

	  // Fill histograms
	  if ( process == 0 ){
               histBDT_WWZ->Fill(wwz_score,zh_score,weight);
	       vec_WWZ[0]->Fill(wwz_score,weight);
	       vec_ZH[0]->Fill(zh_score,weight);
               if ( wwz_SR1 ) c1_wwz += weight;
               if ( wwz_SR2 ) c2_wwz += weight;
               if ( zh_SR1 )  c3_wwz += weight;
               if ( zh_SR2 )  c4_wwz += weight;
          }
	  if ( process == 1 ){
               histBDT_ZH->Fill(wwz_score,zh_score,weight);
	       vec_WWZ[1]->Fill(wwz_score,weight);
               vec_ZH[1]->Fill(zh_score,weight);
	       if ( wwz_SR1 ) c1_zh += weight;
               if ( wwz_SR2 ) c2_zh += weight;
               if ( zh_SR1 )  c3_zh += weight;
               if ( zh_SR2 )  c4_zh += weight;
          }
          if ( process == 2 ){
	       histBDT_TTZ->Fill(wwz_score,zh_score,weight);
               vec_WWZ[2]->Fill(wwz_score,weight);
               vec_ZH[2]->Fill(zh_score,weight);
	       if ( wwz_SR1 ) c1_bkg += weight;
               if ( wwz_SR2 ) c2_bkg += weight;
               if ( zh_SR1 )  c3_bkg += weight;
               if ( zh_SR2 )  c4_bkg += weight;
          }
          if ( process == 3 ){
	       histBDT_ZZ->Fill(wwz_score,zh_score,weight);
               vec_WWZ[3]->Fill(wwz_score,weight);
               vec_ZH[3]->Fill(zh_score,weight);
	       if ( wwz_SR1 ) c1_bkg += weight;
               if ( wwz_SR2 ) c2_bkg += weight;
               if ( zh_SR1 )  c3_bkg += weight;
               if ( zh_SR2 )  c4_bkg += weight;
          }

     }

     histBDT_WWZ->SetLineColor(kRed);
     histBDT_WWZ->SetFillColor(kRed);
     vec_WWZ[0]->SetLineColor(kRed);
     vec_ZH[0]->SetLineColor(kRed);
     vec_WWZ[0]->SetLineWidth(LW);
     vec_ZH[0]->SetLineWidth(LW);
     vec_WWZ[0]->Scale(50.);     
     vec_ZH[0]->Scale(50.);
     histBDT_ZH->SetLineColor(kBlue);
     histBDT_ZH->SetFillColor(kBlue);
     vec_WWZ[1]->SetLineColor(kBlue);
     vec_ZH[1]->SetLineColor(kBlue);
     vec_WWZ[1]->SetLineWidth(LW);
     vec_ZH[1]->SetLineWidth(LW);
     vec_WWZ[1]->Scale(50.);
     vec_ZH[1]->Scale(50.);
     histBDT_TTZ->SetLineColor(kGreen);
     histBDT_TTZ->SetFillColor(kGreen);
     vec_WWZ[2]->SetLineColor(kGreen);
     vec_ZH[2]->SetLineColor(kGreen);
     vec_WWZ[2]->SetLineWidth(LW);
     vec_ZH[2]->SetLineWidth(LW);
     vec_WWZ[2]->Scale(50.);
     vec_ZH[2]->Scale(50.);
     histBDT_ZZ->SetLineColor(kViolet);
     histBDT_ZZ->SetFillColor(kViolet);
     vec_WWZ[3]->SetLineWidth(LW);
     vec_ZH[3]->SetLineWidth(LW);
     vec_WWZ[3]->SetLineColor(kViolet);
     vec_ZH[3]->SetLineColor(kViolet);

     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     legend->AddEntry(histBDT_WWZ,"NonResonant WWZ (x50)","f");
     legend->AddEntry(histBDT_ZH, "ZH #rightarrow WWZ (x50)","f");
     legend->AddEntry(histBDT_TTZ,"t#bar{t}Z (x50)","f");
     legend->AddEntry(histBDT_ZZ, "ZZ","f");

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
         cs3->Divide(2,2);
         cs3->cd(1);
         histBDT_WWZ->SetStats(0);
         histBDT_WWZ->Draw("COLZ");
         histBDT_WWZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         histBDT_WWZ->GetYaxis()->SetTitle("ZH MVA score");
         cs3->cd(2);
         histBDT_ZH->SetStats(0);
         histBDT_ZH->Draw("COLZ");
         histBDT_ZH->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         histBDT_ZH->GetYaxis()->SetTitle("ZH MVA score");
         cs3->cd(3);
         histBDT_TTZ->SetStats(0);
         histBDT_TTZ->Draw("COLZ");
         histBDT_TTZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         histBDT_TTZ->GetYaxis()->SetTitle("ZH MVA score");
         cs3->cd(4);
         histBDT_ZZ->SetStats(0);
         histBDT_ZZ->Draw("COLZ");
         histBDT_ZZ->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
         histBDT_ZZ->GetYaxis()->SetTitle("ZH MVA score");
            
         cs3->Print("MVAPlots/WWZ_ZH_2D_scores.png");
     }

     if (makeSRs){
         std::cout << "Printing yields in Signal Regions" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "WWZ SR1" << std::endl;
         std::cout << "WWZ: " << c1_wwz << " events" << std::endl;
         std::cout << "ZH:  " << c1_zh  << " events" << std::endl;
         std::cout << "Bkg: " << c1_bkg << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "WWZ SR2" << std::endl;
         std::cout << "WWZ: " << c2_wwz << " events" << std::endl;
         std::cout << "ZH:  " << c2_zh  << " events" << std::endl;
         std::cout << "Bkg: " << c2_bkg << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR1" << std::endl;
         std::cout << "WWZ: " << c3_wwz << " events" << std::endl;
         std::cout << "ZH:  " << c3_zh  << " events" << std::endl;
         std::cout << "Bkg: " << c3_bkg << " events" << std::endl;
         std::cout << "=============================================" << std::endl;
         std::cout << "ZH  SR2" << std::endl;
         std::cout << "WWZ: " << c4_wwz << " events" << std::endl;
         std::cout << "ZH:  " << c4_zh  << " events" << std::endl;
         std::cout << "Bkg: " << c4_bkg << " events" << std::endl;
     }

}

std::vector<TH1F*> WWZ_hists(int nbin){ 

     TH1F* h1_wwz = new TH1F("WWZ MVA score (WWZ)","WWZ MVA score (WWZ)",nbin,-1.0,1.0); 
     TH1F* h1_zh  = new TH1F("WWZ MVA score (ZH)","WWZ MVA score (ZH)",nbin,-1.0,1.0); 
     TH1F* h1_ttz = new TH1F("WWZ MVA score (TTZ)","WWZ MVA score (TTZ)",nbin,-1.0,1.0); 
     TH1F* h1_zz  = new TH1F("WWZ MVA score (ZZ)","WWZ MVA score (ZZ)",nbin,-1.0,1.0); 

     std::vector<TH1F*> hists = {h1_wwz,h1_zh,h1_ttz,h1_zz};

     return hists;

}

std::vector<TH1F*> ZH_hists(int nbin){

     TH1F* h2_wwz = new TH1F("ZH MVA score (WWZ)","ZH MVA score (WWZ)",nbin,-1.0,1.0);
     TH1F* h2_zh  = new TH1F("ZH MVA score (ZH)","ZH MVA score (ZH)",nbin,-1.0,1.0);
     TH1F* h2_ttz = new TH1F("ZH MVA score (TTZ)","ZH MVA score (TTZ)",nbin,-1.0,1.0);
     TH1F* h2_zz  = new TH1F("ZH MVA score (ZZ)","ZH MVA score (ZZ)",nbin,-1.0,1.0);

     std::vector<TH1F*> hists = {h2_wwz,h2_zh,h2_ttz,h2_zz};

     return hists;

}
