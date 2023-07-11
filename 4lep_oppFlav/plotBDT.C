void plotBDT(TString BDT_hist){

     TString dir = "outputs/";
     std::vector<TString> files = {"WWZ", "ZZ", "TTZ", "WZ", "Higgs", "Other"};
     std::vector<int> colors = {4, 3, 5, 800, 1};

     TH1F *h_signal(0);
     THStack *hs_backgrounds = new THStack("hs_backgrounds","MVA score for backgrounds;MVA score;Events");

     TLegend* legend = new TLegend(0.60,0.60,0.90,0.90,"","NDC");
     legend->SetBorderSize(0);
     legend->SetTextFont(43);
     legend->SetTextAlign(12);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillColor(0);
     legend->SetFillStyle(0);

     int i = 0;

     //for (auto f: files){
     //    std::cout << "Process = " << f << std::endl;
     //    TFile* file = TFile::Open(dir+"MVA_"+f+".root","READ");
     //    if ( f == "WWZ" ){
     //         h_signal = (TH1F*)file->Get("MVA_"+BDT_hist);
     //         h_signal->SetLineColor(kRed);
     //         legend->AddEntry(h_signal,f,"f");
     //    }
     //    if ( f != "WWZ" ){
     //         TH1F *h_bkgd = (TH1F*)file->Get("MVA_"+BDT_hist);
     //         std::cout << "Number of entries in histogram for process " << f << " = " << h_bkgd->GetEntries() << std::endl;
     //         h_bkgd->SetFillColor(colors[i]);
     //         //h_bkgd->Draw("hist");
     //         std::cout << "Fill color = " << colors[i] << std::endl;
     //         hs_backgrounds->Add(h_bkgd);
     //         legend->AddEntry(h_bkgd,f,"f");
     //         i++;
     //         delete h_bkgd;
     //    }
     //}
     
     TFile* file = TFile::Open(dir+"MVA_WWZ.root","READ");
     TH1F *h_WWZ = (TH1F*)file->Get("MVA_"+BDT_hist);
     h_WWZ->SetLineColor(kRed);
     legend->AddEntry(h_WWZ,"WWZ","f");

     TFile* file1 = TFile::Open(dir+"MVA_ZZ.root","READ");
     TH1F *h_ZZ = (TH1F*)file1->Get("MVA_"+BDT_hist);
     h_ZZ->SetFillColor(kBlue);
     hs_backgrounds->Add(h_ZZ);
     legend->AddEntry(h_ZZ,"ZZ","f");

     TFile* file2 = TFile::Open(dir+"MVA_TTZ.root","READ");
     TH1F *h_TTZ = (TH1F*)file2->Get("MVA_"+BDT_hist);
     h_TTZ->SetFillColor(kGreen);
     hs_backgrounds->Add(h_TTZ);
     legend->AddEntry(h_TTZ,"TTZ","f");

     TFile* file3 = TFile::Open(dir+"MVA_WZ.root","READ");
     TH1F *h_WZ = (TH1F*)file3->Get("MVA_"+BDT_hist);
     h_WZ->SetFillColor(kYellow);
     hs_backgrounds->Add(h_WZ);
     legend->AddEntry(h_WZ,"WZ","f");
 
     TFile* file4 = TFile::Open(dir+"MVA_Higgs.root","READ");
     TH1F *h_Higgs = (TH1F*)file4->Get("MVA_"+BDT_hist);
     h_Higgs->SetFillColor(kOrange);
     hs_backgrounds->Add(h_Higgs);
     legend->AddEntry(h_Higgs,"Higgs","f");

     TFile* file5 = TFile::Open(dir+"MVA_Other.root","READ");
     TH1F *h_Other = (TH1F*)file5->Get("MVA_"+BDT_hist);
     h_Other->SetFillColor(kViolet);
     hs_backgrounds->Add(h_Other);
     legend->AddEntry(h_Other,"Other","f");

     TCanvas *cs = new TCanvas("cs","cs",10,10,1400,900);
     cs->cd();
     hs_backgrounds->Draw("hist");
     h_WWZ->Draw("hist same");
     legend->Draw();

     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of signal events = " << h_WWZ->Integral() << std::endl;
     std::cout << "Number of signal entries = " << h_WWZ->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of ZZ events = " << h_ZZ->Integral() << std::endl;
     std::cout << "Number of ZZ entries = " << h_ZZ->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of TTZ events = " << h_TTZ->Integral() << std::endl;
     std::cout << "Number of TTZ entries = " << h_TTZ->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of WZ events = " << h_WZ->Integral() << std::endl;
     std::cout << "Number of WZ entries = " << h_WZ->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of Higgs events = " << h_Higgs->Integral() << std::endl;
     std::cout << "Number of Higgs entries = " << h_Higgs->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;
     std::cout << "Number of Other events = " << h_Other->Integral() << std::endl;
     std::cout << "Number of Other entries = " << h_Other->GetEntries() << std::endl;
     std::cout << "====================================================================================" << std::endl;





     //cs->Print("mva_scores/MVA_score_"+BDT_hist+".png");

}
