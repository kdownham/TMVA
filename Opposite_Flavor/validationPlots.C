

void validationPlots(){

     int nbin = 50;
     TString file_train = "mva_scores_train.root";
     TFile *f_train = TFile::Open(file_train);

     Int_t process;
     Float_t wwz_score;
     Float_t zh_score;
     Float_t weight;

     TTree *t_train = (TTree*)f_train->Get("T");

     t_train->SetBranchAddress("process",&process);
     t_train->SetBranchAddress("wwz_score",&wwz_score);
     t_train->SetBranchAddress("zh_score",&zh_score);
     t_train->SetBranchAddress("weight",&weight);


     // Define 6 histograms for testing
     TH1F* h1_wwz_train = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h1_zh_train  = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h1_bkg_train = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h2_wwz_train = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);
     TH1F* h2_zh_train  = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);
     TH1F* h2_bkg_train = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);

     // Loop over events and fill histograms
     for (int i=0; i<t_train->GetEntries(); i++){
	  t_train->GetEntry(i);
	  if ( process == 0 ){
	       h1_wwz_train->Fill(wwz_score,weight);
	       h2_wwz_train->Fill(zh_score,weight);
	  }
          if ( process == 1 ){
               h1_zh_train->Fill(wwz_score,weight);
               h2_zh_train->Fill(zh_score,weight);
          }
	  if ( process == 2 || process == 3 ){
               h1_bkg_train->Fill(wwz_score,weight);
               h2_bkg_train->Fill(zh_score,weight);
          }
     }

     // Scale to unity
     h1_wwz_train->Scale(1./h1_wwz_train->Integral());     
     h1_zh_train->Scale(1./h1_zh_train->Integral());
     h1_bkg_train->Scale(1./h1_bkg_train->Integral());
     h2_wwz_train->Scale(1./h2_wwz_train->Integral());
     h2_zh_train->Scale(1./h2_zh_train->Integral());
     h2_bkg_train->Scale(1./h2_bkg_train->Integral());

     
     // Now do the same for the testing dataset
     TString file_test = "mva_scores_test.root";
     TFile *f_test = TFile::Open(file_test);

     TTree *t_test = (TTree*)f_test->Get("T");

     t_test->SetBranchAddress("process",&process);
     t_test->SetBranchAddress("wwz_score",&wwz_score);
     t_test->SetBranchAddress("zh_score",&zh_score);
     t_test->SetBranchAddress("weight",&weight);

     TH1F* h1_wwz_test = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h1_zh_test  = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h1_bkg_test = new TH1F("WWZ MVA Score","WWZ MVA Score",nbin,-1.0,1.0);
     TH1F* h2_wwz_test = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);
     TH1F* h2_zh_test  = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);
     TH1F* h2_bkg_test = new TH1F("ZH MVA Score","ZH MVA Score",nbin,-1.0,1.0);

     for (int i=0; i<t_test->GetEntries(); i++){
          t_test->GetEntry(i);
          if ( process == 0 ){
               h1_wwz_test->Fill(wwz_score,weight);
               h2_wwz_test->Fill(zh_score,weight);
          }
          if ( process == 1 ){
               h1_zh_test->Fill(wwz_score,weight);
               h2_zh_test->Fill(zh_score,weight);
          }
          if ( process == 2 || process == 3 ){
               h1_bkg_test->Fill(wwz_score,weight);
               h2_bkg_test->Fill(zh_score,weight);
          }
     }

     h1_wwz_test->Scale(1./h1_wwz_test->Integral());
     h1_zh_test->Scale(1./h1_zh_test->Integral());
     h1_bkg_test->Scale(1./h1_bkg_test->Integral());
     h2_wwz_test->Scale(1./h2_wwz_test->Integral());
     h2_zh_test->Scale(1./h2_zh_test->Integral());
     h2_bkg_test->Scale(1./h2_bkg_test->Integral());

     // create legend
     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     h1_wwz_train ->SetLineColor(kRed);   
     h1_zh_train  ->SetLineColor(kBlue);
     h1_bkg_train ->SetLineColor(kBlack);
     h2_wwz_train ->SetLineColor(kRed);
     h2_zh_train  ->SetLineColor(kBlue);
     h2_bkg_train ->SetLineColor(kBlack);

     h1_wwz_test ->SetLineColor(kRed);
     h1_zh_test  ->SetLineColor(kBlue);
     h1_bkg_test ->SetLineColor(kBlack);
     h2_wwz_test ->SetLineColor(kRed);
     h2_zh_test  ->SetLineColor(kBlue);
     h2_bkg_test ->SetLineColor(kBlack);

     h1_wwz_test ->SetLineStyle(2); 
     h1_zh_test  ->SetLineStyle(2);
     h1_bkg_test ->SetLineStyle(2);
     h2_wwz_test ->SetLineStyle(2);
     h2_zh_test  ->SetLineStyle(2);
     h2_bkg_test ->SetLineStyle(2);

     legend->AddEntry(h1_wwz_train, "WWZ training", "f");
     legend->AddEntry(h1_wwz_test, "WWZ testing", "f");
     legend->AddEntry(h1_zh_train, "ZH training", "f");
     legend->AddEntry(h1_zh_test, "ZH testing", "f");
     legend->AddEntry(h1_bkg_train, "Background training", "f");
     legend->AddEntry(h1_bkg_test, "Background testing", "f");

     TCanvas *c1 = new TCanvas("c1","c1",10,10,1400,900);
     c1->cd();    

     h1_wwz_train->SetStats(0);
     h1_wwz_train->GetYaxis()->SetRangeUser(0.,0.15); 
     h1_wwz_train->GetXaxis()->SetTitle("WWZ MVA Score");
     h1_wwz_train->GetYaxis()->SetTitle("Fraction of Events");
     h1_wwz_train->Draw("hist");
     h1_wwz_test ->Draw("hist same");             
     h1_zh_train ->Draw("hist same");
     h1_zh_test  ->Draw("hist same");
     h1_bkg_train->Draw("hist same");
     h1_bkg_test ->Draw("hist same");
     legend->Draw();

     c1->Print("MVAPlots/WWZ_score_validation.png");

     TCanvas *c2 = new TCanvas("c2","c2",10,10,1400,900);
     c2->cd();

     h2_wwz_train->SetStats(0);
     h2_wwz_train->GetYaxis()->SetRangeUser(0.,0.15);
     h2_wwz_train->GetXaxis()->SetTitle("ZH MVA Score");
     h2_wwz_train->GetYaxis()->SetTitle("Fraction of Events");
     h2_wwz_train->Draw("hist");
     h2_wwz_test ->Draw("hist same");
     h2_zh_train ->Draw("hist same");
     h2_zh_test  ->Draw("hist same");
     h2_bkg_train->Draw("hist same");
     h2_bkg_test ->Draw("hist same");
     legend->Draw();

     c2->Print("MVAPlots/ZH_score_validation.png");

}
