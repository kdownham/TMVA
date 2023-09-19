#include <stdio.h>

TFile *convert_txt_to_root(TString input, TString output, int nlines){

     Int_t process;
     Float_t wwz_score;
     Float_t zh_score;
     Float_t weight;

     TString filename = output+".root";
     FILE *fp = fopen(input,"r");

     TFile *hfile = TFile::Open(filename,"RECREATE");
     TTree *tree = new TTree("T","MVA scores");
     tree->Branch("process",&process,"process/I");
     tree->Branch("wwz_score",&wwz_score,"wwz_score/F");
     tree->Branch("zh_score",&zh_score,"zh_score/F");
     tree->Branch("weight",&weight,"weight/F");

     char line[nlines];

     int i = 0;

     while (fgets(line,nlines,fp)){
	 i++;
         sscanf(line,"%i %f %f %f",&process,&wwz_score,&zh_score,&weight);
	 tree->Fill();
     } 

     tree->Print();
     tree->Write();

     fclose(fp);
     return hfile;

}
