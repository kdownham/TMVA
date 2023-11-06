# Opposite Flavor BDT Training

This directory is the home of macros for the training of the Opposite-Flavor BDTs for the 4-lepton analysis. There are 2 signal processes: WWZ (code for training in the `WWZ_vs_Backgrounds`
directory), and ZH (code for training in `ZH_vs_Backgrounds` directory). The macros for the training are called `Classification.C`, and they take one argument: the name of the weights file 
that you would like to produce. Give the weights file a descriptive title so you can remember the options that you used for it. To perform the BDT training, one must first set the path to the
corresponding `Classification.C` macro in your `.rootrc` by adding the following line

```
Unix.*.Root.MacroPath: /path/to/directory/containing/macro

```
After this, make a directory called `classification` within the `WWZ_vs_Backgrounds` and `ZH_vs_Backgrounds` directories. This is where the output root file will go (produced from the training)

Then once you have added this, you can begin the training by executing the training macro with the command:

```
root -l 'Classification.C("desired_name_of_weights_file")'

```
Once the training has completed, a TMVA macro will automatically execute and a GUI will pop up. This GUI has different buttons that allow you to make plots of input variable distributions,
ROC curves, KS tests between training and testing datasets, and much more. I would recommend playing around with this for a bit to get a feel for what you can do.
