void makeMVAPlots(TString tag){

     TString file = "MulticlassApplication.root";
     std::vector<TString> procs = {"NonResWWZ", "ZHWWZ", "TTZ", "ZZ"};
     std::vector<int> colors = {4,3,1,800};
     
     THStack *hs_MVA_1_scores = new THStack("hs_MVA_1_scores", "NonResonant WWZ MVA score;MVA score;Events");
     THStack *hs_MVA_2_scores = new THStack("hs_MVA_2_scores", "ZH MVA score;MVA score;Events");

     //std::vector<TH1F*> MVA_1;
     //std::vector<TH1F*> MVA_2;
     std::vector<TH2F*> MVA_12;

     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     TLegend* legend1 = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend1->SetBorderSize(0);
     legend1->SetTextFont(43);
     legend1->SetTextAlign(12);
     legend1->SetLineColor(1);
     legend1->SetLineStyle(1);
     legend1->SetLineWidth(1);
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);

     TLegend* legend2 = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend2->SetBorderSize(0);
     legend2->SetTextFont(43);
     legend2->SetTextAlign(12);
     legend2->SetLineColor(1);
     legend2->SetLineStyle(1);
     legend2->SetLineWidth(1);
     legend2->SetFillColor(0);
     legend2->SetFillStyle(0);

     TFile* f = TFile::Open(file,"READ");
     for (int i = 0; i < procs.size(); i++ ){
	  TH1F* h_1 = (TH1F*)f->Get("MVA_1_"+procs[i]);
	  h_1->SetLineColor(colors[i]);
	  TH1F* h_2 = (TH1F*)f->Get("MVA_2_"+procs[i]);
	  h_2->SetLineColor(colors[i]);
	  TH2F* h_12 = (TH2F*)f->Get("MVA_BDT_signals_"+procs[i]);
	  h_12->SetFillColor(colors[i]);
	  h_12->SetLineColor(colors[i]);

	  TString scale = "";

          if ( procs[i] == "NonResWWZ" || procs[i] == "ZHWWZ" || procs[i] == "TTZ" ){
               h_1->Scale(50.);
               h_2->Scale(50.);
               //h_12->Scale(50.);
               scale += " (50x)";
          }

	
	  hs_MVA_1_scores->Add(h_1);
	  legend->AddEntry(h_1,procs[i]+scale,"f");
	  hs_MVA_2_scores->Add(h_2);
	  legend1->AddEntry(h_2,procs[i]+scale,"f");
	  MVA_12.push_back(h_12);
	  legend2->AddEntry(h_12,procs[i],"f");

     }

     TCanvas *cs = new TCanvas("cs","cs",10,10,1400,900);
     cs->cd();
     hs_MVA_1_scores->Draw("nostack hist");
     legend->Draw();
     cs->Print("MVAPlots/"+tag+"_WWZ_score.png");
     TCanvas *cs2 = new TCanvas("cs2","cs2",10,10,1400,900);
     cs2->cd();
     hs_MVA_2_scores->Draw("nostack hist");
     legend1->Draw();
     cs2->Print("MVAPlots/"+tag+"_ZH_score.png");
     TCanvas *cs3 = new TCanvas("cs3","cs3",10,10,1400,900);
     cs3->Divide(2,2);
     cs3->cd(1);
     MVA_12[0]->Draw("colz");
     MVA_12[0]->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
     MVA_12[0]->GetYaxis()->SetTitle("ZH MVA score");
     cs3->cd(2);
     MVA_12[1]->Draw("colz");
     MVA_12[1]->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
     MVA_12[1]->GetYaxis()->SetTitle("ZH MVA score");
     cs3->cd(3);
     MVA_12[2]->Draw("colz");
     MVA_12[2]->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
     MVA_12[2]->GetYaxis()->SetTitle("ZH MVA score");
     cs3->cd(4);
     MVA_12[3]->Draw("colz");
     MVA_12[3]->GetXaxis()->SetTitle("NonResonant WWZ MVA score");
     MVA_12[3]->GetYaxis()->SetTitle("ZH MVA score");
     //legend2->Draw();
     cs3->Print("MVAPlots/"+tag+"_mva_2D_plot.png");

     TCanvas *cs4 = new TCanvas("cs4","cs4",10,10,1400,900);
     cs4->Divide(2,2);

     TH2F *h1 = (TH2F*)MVA_12[0]->Clone("h1");
     TH2F *h2 = (TH2F*)MVA_12[1]->Clone("h2");
     TH2F *h3 = (TH2F*)MVA_12[2]->Clone("h3");
     TH2F *h4 = (TH2F*)MVA_12[3]->Clone("h4");
     
     h1->GetXaxis()->SetRangeUser(0.8,1.0);      
     h2->GetXaxis()->SetRangeUser(0.8,1.0);     
     h3->GetXaxis()->SetRangeUser(0.8,1.0);     
     h4->GetXaxis()->SetRangeUser(0.8,1.0);

     h1->GetYaxis()->SetRangeUser(0.0,0.2);     
     h2->GetYaxis()->SetRangeUser(0.0,0.2);
     h3->GetYaxis()->SetRangeUser(0.0,0.2);
     h4->GetYaxis()->SetRangeUser(0.0,0.2);

     cs4->cd(1);
     h1->Draw("colz");
     cs4->cd(2);
     h2->Draw("colz");
     cs4->cd(3);
     h3->Draw("colz");
     cs4->cd(4);
     h4->Draw("colz");

     cs4->Print("MVAPlots/"+tag+"_mva_2D_WWZ_SR.png");

     TCanvas *cs5 = new TCanvas("cs5","cs5",10,10,1400,900);
     cs5->Divide(2,2);

     TH2F *h5 = (TH2F*)MVA_12[0]->Clone("h5");
     TH2F *h6 = (TH2F*)MVA_12[1]->Clone("h6");
     TH2F *h7 = (TH2F*)MVA_12[2]->Clone("h7");
     TH2F *h8 = (TH2F*)MVA_12[3]->Clone("h8");  

     h5->GetXaxis()->SetRangeUser(0.0,0.3);
     h6->GetXaxis()->SetRangeUser(0.0,0.3);
     h7->GetXaxis()->SetRangeUser(0.0,0.3);
     h8->GetXaxis()->SetRangeUser(0.0,0.3);

     h5->GetYaxis()->SetRangeUser(0.7,1.0);
     h6->GetYaxis()->SetRangeUser(0.7,1.0);
     h7->GetYaxis()->SetRangeUser(0.7,1.0);
     h8->GetYaxis()->SetRangeUser(0.7,1.0);

     cs5->cd(1);
     h5->Draw("colz");
     cs5->cd(2);
     h6->Draw("colz");
     cs5->cd(3);
     h7->Draw("colz");
     cs5->cd(4);
     h8->Draw("colz");

     cs5->Print("MVAPlots/"+tag+"_mva_2D_ZH_SR.png");
     
}
