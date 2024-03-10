void make2Dhists(TString tag){

     int nbin = 50;

     TString fname = "mva_scores_"+tag+".root";
     TFile *f = TFile::Open(fname);
  
     Int_t process;
     Float_t wwz_score;
     Float_t zh_score;
     Float_t weight;

     TTree *t = (TTree*)f->Get("T");

     t->SetBranchAddress("process",&process);
     t->SetBranchAddress("wwz_score",&wwz_score);
     t->SetBranchAddress("zh_score",&zh_score);
     t->SetBranchAddress("weight",&weight);

     //std::cout << "Debug 1" << std::endl;

     TH2F *histBDT_WWZ = new TH2F("MVA_BDT_WWZ","MVA_BDT_WWZ", nbin, -1.0, 1.0, nbin, -1.0, 1.0 );
     TH2F *histBDT_ZH  = new TH2F("MVA_BDT_ZH" ,"MVA_BDT_ZH" , nbin, -1.0, 1.0, nbin, -1.0, 1.0 );
     TH2F *histBDT_BKG = new TH2F("MVA_BDT_BKG","MVA_BDT_BKG", nbin, -1.0, 1.0, nbin, -1.0, 1.0 );

     //std::cout << "Debug 2" << std::endl;

     //Loop over events in tree
     for ( int i=0; i<t->GetEntries(); i++ ){
	   t->GetEntry(i);

           if ( process == 0 ){
		histBDT_WWZ->Fill(wwz_score,zh_score,weight);
           }
	   if ( process == 1 ){
		histBDT_ZH->Fill(wwz_score,zh_score,weight);
	   }
	   if ( process > 1 ){
		histBDT_BKG->Fill(wwz_score,zh_score,weight);
	   }

     } // Loop over events in tree

     //std::cout << "Debug 3" << std::endl;

     //f->Close();

     //std::cout << "Debug 4" << std::endl;

     TFile *output = new TFile("mva_hists_2D_"+tag+".root","RECREATE");
     //std::cout << "Debug 5" << std::endl;
     output->cd();
     std::cout << "Integral of h_WWZ = " << histBDT_WWZ->Integral() << std::endl;
     std::cout << "Integral of h_ZH = " << histBDT_ZH->Integral() << std::endl;
     std::cout << "Integral of h_BKG = " << histBDT_BKG->Integral() << std::endl;
     histBDT_WWZ->Write();
     histBDT_ZH->Write();
     histBDT_BKG->Write();

     //std::cout << "Debug 6" << std::endl;

     output->Write();
     output->Close();

     //std::cout << "Debug 7" << std::endl;      

}
