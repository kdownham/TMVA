void get_yields(){

     TString file = "mva_scores_test.root";
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

     float wwz_tot = 0.;
     float wwz_err = 0.;
     int wwz_counts = 0;
     float zh_tot = 0.;
     float zh_err = 0.;
     int zh_counts = 0;
     float bkg_tot = 0.;
     float bkg_err = 0.;
     int bkg_counts = 0;

     // Now break it down by background
     float zz_tot = 0.;
     float zz_err = 0.;
     int   zz_counts = 0;
     float ttz_tot = 0.;
     float ttz_err = 0.;
     int   ttz_counts = 0;
     float twz_tot = 0.;
     float twz_err = 0.;
     int   twz_counts = 0;
     float wz_tot = 0.;
     float wz_err = 0.;
     int   wz_counts = 0;
     float vvv_tot = 0.;
     float vvv_err = 0.;
     int   vvv_counts = 0;
     float other_tot = 0.;
     float other_err = 0.;
     int   other_counts = 0;

     for (int i=0; i<t->GetEntries(); i++){
          t->GetEntry(i);

          if ( process == 0 ){
	       wwz_tot += weight;
	       wwz_err += std::pow(weight,2.);
	       wwz_counts++;
	  }
	  if ( process == 1 ){
	       zh_tot += weight;
	       zh_err += std::pow(weight,2.); 
               zh_counts++;
	  }
          if ( process > 1 ){
	       bkg_tot += weight;
 	       bkg_err += std::pow(weight,2.);
	       bkg_counts++;
	  }
          if ( process == 3 ){
               zz_tot += weight;
               zz_err += std::pow(weight,2.);
	       zz_counts++;
          }
          if ( process == 2 ){
               ttz_tot += weight;
               ttz_err += std::pow(weight,2.);
	       ttz_counts++;
          }
          if ( process == 4 ){
               twz_tot += weight;
               twz_err += std::pow(weight,2.);
               twz_counts++;
          }
          if ( process == 5 ){
               wz_tot += weight;
               wz_err += std::pow(weight,2.);
	       wz_counts++;
          }
          if ( process == 6 ){
               vvv_tot += weight;
               vvv_err += std::pow(weight,2.);
               vvv_counts++;
          }
          if ( process == 7 ){
               other_tot += weight;
               other_err += std::pow(weight,2.);
	       other_counts++;
          }

     } 

     float bkg_sum = (zz_tot + ttz_tot + twz_tot + wz_tot + vvv_tot + other_tot);
     float bkg_sum_err = ( std::pow(zz_err,2.) + std::pow(ttz_err,2.) + std::pow(twz_err,2.) + std::pow(wz_err,2.) + std::pow(vvv_err,2.) + std::pow(other_err,2.) );
     float bkg_sum_counts = (zz_counts + ttz_counts + twz_counts + wz_counts + vvv_counts + other_counts);

     std::cout << "============================================" << std::endl;
     std::cout << "PRINTING TOTAL YIELDS (SF TR)" << std::endl;
     std::cout << "--------------------------------------------" << std::endl;
     std::cout << "WWZ: " << wwz_tot << " +/- " << std::sqrt(wwz_err) << " (" << wwz_counts << " entries)" << std::endl;
     std::cout << "ZH:  " << zh_tot  << " +/- " << std::sqrt(zh_err)  << " (" << zh_counts << " entries)" << std::endl;
     std::cout << "Bkg: " << bkg_tot << " +/- " << std::sqrt(bkg_err) << " (" << bkg_counts << " entries)" << std::endl;
     std::cout << "--------------------------------------------" << std::endl;
     std::cout << "Breakdown of Background" << std::endl;
     std::cout << "ZZ: " << zz_tot << " +/- " << std::sqrt(zz_err) << " (" << zz_counts << " entries)" << std::endl;
     std::cout << "ttZ: " << ttz_tot << " +/- " << std::sqrt(ttz_err) << " (" << ttz_counts << " entries)" << std::endl;
     std::cout << "tWZ: " << twz_tot << " +/- " << std::sqrt(twz_err) << " (" << twz_counts << " entries)" << std::endl;
     std::cout << "WZ: " << wz_tot << " +/- " << std::sqrt(wz_err) << " (" << wz_counts << " entries)" << std::endl;
     std::cout << "VVV: " << vvv_tot << " +/- " << std::sqrt(vvv_err) << " (" << vvv_counts << " entries)" << std::endl;
     std::cout << "Other: " << other_tot << " +/- " << std::sqrt(other_err) << " (" << other_counts << " entries)" << std::endl;
     std::cout << "><><><><><><><><><><><><><><><><><><><><><><" << std::endl;
     std::cout << "Sanity Check" << std::endl;
     std::cout << "Sum Bkgds: " << bkg_sum << " +/- " << std::sqrt(bkg_sum_err) << " (" << bkg_sum_counts << " entries)" << std::endl; 

}
