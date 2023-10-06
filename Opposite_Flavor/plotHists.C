std::vector<TH1F*> WWZ_hists(int nbin);
std::vector<TH1F*> ZH_hists(int nbin);

void plotHists(bool draw2Donly=true, bool makeSRs=false, bool drawSRs=true){

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

     float c1_wwz_error = 0.;
     float c2_wwz_error = 0.;
     float c3_wwz_error = 0.;
     float c4_wwz_error = 0.;

     float c1_zh = 0.;
     float c2_zh = 0.;
     float c3_zh = 0.;
     float c4_zh = 0.;

     float c1_zh_error = 0.;
     float c2_zh_error = 0.;
     float c3_zh_error = 0.;
     float c4_zh_error = 0.;

     float c1_bkg = 0.;
     float c2_bkg = 0.;
     float c3_bkg = 0.;
     float c4_bkg = 0.;

     float c1_bkg_error = 0.;
     float c2_bkg_error = 0.;
     float c3_bkg_error = 0.;
     float c4_bkg_error = 0.;

     float c1_zz = 0.;
     float c2_zz = 0.;
     float c3_zz = 0.;
     float c4_zz = 0.;

     float c1_zz_error = 0.;
     float c2_zz_error = 0.;
     float c3_zz_error = 0.;
     float c4_zz_error = 0.;

     float c1_ttz = 0.;
     float c2_ttz = 0.;
     float c3_ttz = 0.;
     float c4_ttz = 0.;

     float c1_ttz_error = 0.;
     float c2_ttz_error = 0.;
     float c3_ttz_error = 0.;
     float c4_ttz_error = 0.;

     float c1_higgs = 0.;
     float c2_higgs = 0.;
     float c3_higgs = 0.;
     float c4_higgs = 0.;

     float c1_higgs_error = 0.;
     float c2_higgs_error = 0.;
     float c3_higgs_error = 0.;
     float c4_higgs_error = 0.;

     float c1_wz = 0.;
     float c2_wz = 0.;
     float c3_wz = 0.;
     float c4_wz = 0.;

     float c1_wz_error = 0.;
     float c2_wz_error = 0.;
     float c3_wz_error = 0.;
     float c4_wz_error = 0.;
  
     float c1_other = 0.;
     float c2_other = 0.;
     float c3_other = 0.;
     float c4_other = 0.;

     float c1_other_error = 0.;
     float c2_other_error = 0.;
     float c3_other_error = 0.;
     float c4_other_error = 0.;
     
     // Loop over events
     for (int i=0; i<t->GetEntries(); i++){
	  t->GetEntry(i);

          bool wwz_SR1 = ( wwz_score > 0.7 && zh_score < -0.3 );
          bool wwz_SR2 = ( wwz_score < 0.7 && wwz_score > 0.4 && zh_score < -0.6 );
          bool zh_SR1  = ( wwz_score > 0.5 && zh_score > 0.7 );
          bool zh_SR2  = ( wwz_score < 0.5 && wwz_score > -0.2 && zh_score > 0.7 );


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
          }
          if ( process == 2 || process == 3 || process == 4 || process == 5 || process == 6 ){
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
          }
	  if ( process == 4 ){
	       if ( wwz_SR1 ){
                    c1_higgs += weight;
                    c1_higgs_error += std::pow(weight,2.);
               }
               if ( wwz_SR2 ){
                    c2_higgs += weight;
                    c2_higgs_error += std::pow(weight,2.);
               }
               if ( zh_SR1 ){
                    c3_higgs += weight;
                    c3_higgs_error += std::pow(weight,2.);
               }
               if ( zh_SR2 ){
                    c4_higgs += weight;
                    c4_higgs_error += std::pow(weight,2.);
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
	 std::cout << "Higgs: " << c1_higgs   << "+/-" << std::sqrt(c1_higgs_error) << " events" << std::endl;
	 std::cout << "WZ: "    << c1_wz      << "+/-" << std::sqrt(c1_wz_error) << " events" << std::endl;
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
         std::cout << "Higgs: " << c2_higgs   << "+/-" << std::sqrt(c2_higgs_error) << " events" << std::endl;
         std::cout << "WZ: "    << c2_wz      << "+/-" << std::sqrt(c2_wz_error) << " events" << std::endl;
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
         std::cout << "Higgs: " << c3_higgs   << "+/-" << std::sqrt(c3_higgs_error) << " events" << std::endl;
         std::cout << "WZ: "    << c3_wz      << "+/-" << std::sqrt(c3_wz_error) << " events" << std::endl;
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
         std::cout << "Higgs: " << c4_higgs   << "+/-" << std::sqrt(c4_higgs_error) << " events" << std::endl;
         std::cout << "WZ: "    << c4_wz      << "+/-" << std::sqrt(c4_wz_error) << " events" << std::endl;
         std::cout << "Other: " << c4_other   << "+/-" << std::sqrt(c4_other_error) << " events" << std::endl;

         TH1F* h_SR_wwz   = new TH1F("MVA SR Bins (WWZ)","MVA SR Bins (WWZ)",4,0,4);
	 TH1F* h_SR_zh    = new TH1F("MVA SR Bins (ZH)","MVA SR Bins (ZH)",4,0,4);
	 TH1F* h_SR_zz    = new TH1F("MVA SR Bins (ZZ)","MVA SR Bins (ZZ)",4,0,4);
	 TH1F* h_SR_ttz   = new TH1F("MVA SR Bins (ttZ)","MVA SR Bins (ttZ)",4,0,4);
	 TH1F* h_SR_higgs = new TH1F("MVA SR Bins (Higgs)","MVA SR Bins (Higgs)",4,0,4);
	 TH1F* h_SR_wz    = new TH1F("MVA SR Bins (WZ)","MVA SR Bins (WZ)",4,0,4);
	 TH1F* h_SR_other = new TH1F("MVA SR Bins (Other)","MVA SR Bins (Other)",4,0,4);

	 h_SR_wwz->SetBinContent(1,c1_wwz);
	 h_SR_wwz->SetBinContent(2,c2_wwz);
	 h_SR_wwz->SetBinContent(3,c3_wwz);
	 h_SR_wwz->SetBinContent(4,c4_wwz);
	 h_SR_wwz->SetLineColor(kRed);
	 
	 h_SR_zh->SetBinContent(1,c1_zh);
         h_SR_zh->SetBinContent(2,c2_zh);
         h_SR_zh->SetBinContent(3,c3_zh);
         h_SR_zh->SetBinContent(4,c4_zh);
	 h_SR_zh->SetLineColor(kBlue);

         h_SR_zz->SetBinContent(1,c1_zz);
         h_SR_zz->SetBinContent(2,c2_zz);
         h_SR_zz->SetBinContent(3,c3_zz);
         h_SR_zz->SetBinContent(4,c4_zz);
	 h_SR_zz->SetLineColor(kGreen);
         h_SR_zz->SetFillColorAlpha(kGreen,0.1);

	 h_SR_ttz->SetBinContent(1,c1_ttz);
         h_SR_ttz->SetBinContent(2,c2_ttz);
         h_SR_ttz->SetBinContent(3,c3_ttz);
         h_SR_ttz->SetBinContent(4,c4_ttz);
	 h_SR_ttz->SetLineColor(kOrange);
         h_SR_ttz->SetFillColorAlpha(kOrange,0.1);

	 h_SR_higgs->SetBinContent(1,c1_higgs);
         h_SR_higgs->SetBinContent(2,c2_higgs);
         h_SR_higgs->SetBinContent(3,c3_higgs);
         h_SR_higgs->SetBinContent(4,c4_higgs);
	 h_SR_higgs->SetLineColor(kViolet);
         h_SR_higgs->SetFillColorAlpha(kViolet,0.1);

	 h_SR_wz->SetBinContent(1,c1_wz);
         h_SR_wz->SetBinContent(2,c2_wz);
         h_SR_wz->SetBinContent(3,c3_wz);
         h_SR_wz->SetBinContent(4,c4_wz);
	 h_SR_wz->SetLineColor(kBlack);
         h_SR_wz->SetFillColorAlpha(kBlack,0.1);

	 h_SR_other->SetBinContent(1,c1_other);
         h_SR_other->SetBinContent(2,c2_other);
         h_SR_other->SetBinContent(3,c3_other);
         h_SR_other->SetBinContent(4,c4_other);
	 h_SR_other->SetLineColor(7);
	 h_SR_other->SetFillColorAlpha(7,0.1);

         THStack *hs_SR_bkg = new THStack("hs_SR_bkg","Signal Regions (Opposite Flavor Channel);SR Bin;Events");  

         //hs_SR_bkg->GetYaxis()->SetRangeUser(0.,3.);      

         hs_SR_bkg->Add(h_SR_zz);
	 hs_SR_bkg->Add(h_SR_ttz);
         hs_SR_bkg->Add(h_SR_higgs);
	 hs_SR_bkg->Add(h_SR_wz);
	 hs_SR_bkg->Add(h_SR_other);

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
	 legendSR->AddEntry(h_SR_higgs,"Higgs","f");
	 legendSR->AddEntry(h_SR_wz,"WZ","f");
	 legendSR->AddEntry(h_SR_other,"Other","f");

         TCanvas *cSR = new TCanvas("cSR","cSR",10,10,1400,900);
         cSR->cd();
 	 hs_SR_bkg->SetMaximum(3.);
	 hs_SR_bkg->SetMinimum(0.);
	 hs_SR_bkg->Draw();
	 //h_SR_wwz->GetYaxis()->SetRangeUser(0.,3.);
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
	 delete h_SR_higgs;
	 delete h_SR_wz;
	 delete h_SR_other;
	 delete hs_SR_bkg;

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
