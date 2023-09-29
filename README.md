# TMVA
Toolkit for Multivariate Analysis with ROOT

This is currently based on the TMVA user's guide (https://root.cern.ch/download/doc/tmva/TMVAUsersGuide.pdf), and involves the training and application of a simple Boosted Decision Tree (BDT).

Refer to the user's guide (Section 2) for setup instructions before running the example macros (located in the "macros" directory).

In the simple example, a BDT is used to separate a rare Standard Model signal process (WWZ production) from a large Standard Model background process (ZZ production).
Two discriminating kinematic variables are trained on to separate the signal from the background, and the MVA score is computed for the signal process.

# Application to a 4-lepton analysis

The main part of this analysis focuses on the WWZ --> 4 lepton analysis. In this case, we have 2 signal processes (WWZ & ZH->ZWW*) that we would like to separate from background processes (namely ZZ and ttZ). 
There are also 2 channels that are defined for the 4-lepton analysis depending on the flavor of the leptons coming from the W bosons. If the leptons from the W's in the event are of the same flavor (ee/mumu), they
are considered to be part of the same flavor channel (see `Same_Flavor` directory), while if the leptons have different flavor (e mu) they belong to the opposite flavor channel (see `Opposite_Flavor` directory).

Inside those directories you will find instructions for running the various scripts for the training/testing/application of the different BDTs used in this analysis. There are 4 different BDTs that are currently employed:

(1). Opposite Flavor Channel, WWZ vs Backgrounds
(2). Opposite Flavor Channel, ZH vs Backgrounds
(3). Same Flavor Channel, WWZ vs Backgrounds
(4). Same Flavor Channel, ZH vs Backgrounds
