// Class: ReadCuts
// Automatically generated by MethodBase::MakeClass
//

/* configuration options =====================================================

#GEN -*-*-*-*-*-*-*-*-*-*-*- general info -*-*-*-*-*-*-*-*-*-*-*-

Method         : Cuts::Cuts
TMVA Release   : 4.2.1         [262657]
ROOT Release   : 6.20/09       [398345]
Creator        : kdownham
Date           : Tue May 23 16:03:50 2023
Host           : Linux cmsbuild76.cern.ch 3.10.0-1062.4.1.el7.x86_64 #1 SMP Fri Oct 18 17:15:30 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
Dir            : /home/users/kdownham/Triboson/TMVA/macros
Training events: 2000
Analysis type  : [Classification]


#OPT -*-*-*-*-*-*-*-*-*-*-*-*- options -*-*-*-*-*-*-*-*-*-*-*-*-

# Set by User:
V: "False" [Verbose output (short form of "VerbosityLevel" below - overrides the latter one)]
H: "False" [Print method-specific help message]
FitMethod: "MC" [Minimisation Method (GA, SA, and MC are the primary methods to be used; the others have been introduced for testing purposes and are depreciated)]
EffMethod: "EffSel" [Selection Method]
# Default:
VerbosityLevel: "Default" [Verbosity level]
VarTransform: "None" [List of variable transformations performed before training, e.g., "D_Background,P_Signal,G,N_AllClasses" for: "Decorrelation, PCA-transformation, Gaussianisation, Normalisation, each for the given class of events ('AllClasses' denotes all events of all classes, if no class indication is given, 'All' is assumed)"]
CreateMVAPdfs: "False" [Create PDFs for classifier outputs (signal and background)]
IgnoreNegWeightsInTraining: "False" [Events with negative weights are ignored in the training (but are included for testing and performance evaluation)]
CutRangeMin[0]: "-1.000000e+00" [Minimum of allowed cut range (set per variable)]
    CutRangeMin[1]: "-1.000000e+00"
CutRangeMax[0]: "-1.000000e+00" [Maximum of allowed cut range (set per variable)]
    CutRangeMax[1]: "-1.000000e+00"
VarProp[0]: "FSmart" [Categorisation of cuts]
    VarProp[1]: "FSmart"
##


#VAR -*-*-*-*-*-*-*-*-*-*-*-* variables *-*-*-*-*-*-*-*-*-*-*-*-

NVar 2
Var_4LepMET_mt2_PuppiMET      Var_4LepMET_mt2_PuppiMET      Var_4LepMET_mt2_PuppiMET      MT2                           GeV                               'F'    [0.0438518188894,213.741104126]
Var_4LepMET_other_mll         Var_4LepMET_other_mll         Var_4LepMET_other_mll         m_{ll}                        GeV                               'F'    [10.425330162,1380.99389648]
NSpec 0


============================================================================ */

#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

class ReadCuts : public IClassifierReader {

 public:

   // constructor
   ReadCuts( std::vector<std::string>& theInputVars )
      : IClassifierReader(),
        fClassName( "ReadCuts" ),
        fNvars( 2 )
   {
      // the training input variables
      const char* inputVars[] = { "Var_4LepMET_mt2_PuppiMET", "Var_4LepMET_other_mll" };

      // sanity checks
      if (theInputVars.size() <= 0) {
         std::cout << "Problem in class \"" << fClassName << "\": empty input vector" << std::endl;
         fStatusIsClean = false;
      }

      if (theInputVars.size() != fNvars) {
         std::cout << "Problem in class \"" << fClassName << "\": mismatch in number of input values: "
                   << theInputVars.size() << " != " << fNvars << std::endl;
         fStatusIsClean = false;
      }

      // validate input variables
      for (size_t ivar = 0; ivar < theInputVars.size(); ivar++) {
         if (theInputVars[ivar] != inputVars[ivar]) {
            std::cout << "Problem in class \"" << fClassName << "\": mismatch in input variable names" << std::endl
                      << " for variable [" << ivar << "]: " << theInputVars[ivar].c_str() << " != " << inputVars[ivar] << std::endl;
            fStatusIsClean = false;
         }
      }

      // initialize min and max vectors (for normalisation)
      fVmin[0] = 0;
      fVmax[0] = 0;
      fVmin[1] = 0;
      fVmax[1] = 0;

      // initialize input variable types
      fType[0] = 'F';
      fType[1] = 'F';

      // initialize constants
      Initialize();

   }

   // destructor
   virtual ~ReadCuts() {
      Clear(); // method-specific
   }

   // the classifier response
   // "inputValues" is a vector of input values in the same order as the
   // variables given to the constructor
   double GetMvaValue( const std::vector<double>& inputValues ) const override;

 private:

   // method-specific destructor
   void Clear();

   // common member variables
   const char* fClassName;

   const size_t fNvars;
   size_t GetNvar()           const { return fNvars; }
   char   GetType( int ivar ) const { return fType[ivar]; }

   // normalisation of input variables
   double fVmin[2];
   double fVmax[2];
   double NormVariable( double x, double xmin, double xmax ) const {
      // normalise to output range: [-1, 1]
      return 2*(x - xmin)/(xmax - xmin) - 1.0;
   }

   // type of input variable: 'F' or 'I'
   char   fType[2];

   // initialize internal variables
   void Initialize();
   double GetMvaValue__( const std::vector<double>& inputValues ) const;

   // private members (method specific)
   // not implemented for class: "ReadCuts"
};
inline double ReadCuts::GetMvaValue( const std::vector<double>& inputValues ) const
{
   // classifier response value
   double retval = 0;

   // classifier response, sanity check first
   if (!IsStatusClean()) {
      std::cout << "Problem in class \"" << fClassName << "\": cannot return classifier response"
                << " because status is dirty" << std::endl;
   }
   else {
         retval = GetMvaValue__( inputValues );
   }

   return retval;
}
