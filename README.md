# TMVA
Toolkit for Multivariate Analysis with ROOT

This is currently based on the TMVA user's guide (https://root.cern.ch/download/doc/tmva/TMVAUsersGuide.pdf), and involves the training and application of a simple Boosted Decision Tree (BDT).

Refer to the user's guide (Section 2) for setup instructions before running the example macros (located in the "macros" directory).

In the simple example, a BDT is used to separate a rare Standard Model signal process (WWZ production) from a large Standard Model background process (ZZ production).
Two discriminating kinematic variables are trained on to separate the signal from the background, and the MVA score is computed for the signal process.
