import datetime
from ROOT import TLegend, TPad,TCanvas


today = datetime.datetime.today()


forCondor = False
if forCondor:
    forCondorStr = "/scratch365/dlutton/HistosAndPNGs/"
    savePathBool = False
else:
    forCondorStr = ""
    savePathBool = True


#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

testRun = False
MGOHW = True

MGOSix = False
MGOSixEtaDifCut = False
MGOHBox = False
MGOHBoxEtaDifCut = False
MGOHDD = False
MGOHDDEtaDifCut = False

normalizeDataTogether = True
makeUnstacked = False

comparisonPlotsOnly = True

useTightdRCut = False
tightCutStr = ""
if useTightdRCut:
  tightCutStr = "WithTighterdRCut"
onlyDoSomeHists = False
histsToDo = 2

breakEvEarly = False
breakEvAt = 2500

onlyLHETree = False
useLHETree = False
onlyTaggedTrees = False
useTaggedTrees = False

makeRaw = False
makeGenRaw = False
makeHFJ = False
makeZHFJ = False
makeZHJ = False
makeZFJ = False
makeZJ = False

scaleSignalToBackground = False

useLogY = True
useLogYForRatioPlot = True


drawXSPlots = False
drawEvPlots = False
#ignoreHist = True
#ignoreHistInd = 13

FJCandidateHistIndRangeAr = [[9,14],[14,19]]
#FJMatchedHistIndRangeAr = [[19,24],[24,29],[29,34]]
FJMatchedHistIndRangeAr = [[19,24]]
FJCandidateSaveNameAr = ["","UsingDTHForCand"]
FJMatchedSaveNameAr = ["","UsingDTHForMatch","UsingdRForMatch"]


XSxTitleAr = ["Cross Section"]
XShTitleAr = ["Cross Section"]
XSBinsAndRangeAr = [[50,-1,1]]

evNxTitleAr = ["Events","Weighted Events/Bin (pb)"]
evNhTitleAr = ["Total Events","Events Passing Higgs Jet Cuts"]
evNBinsAndRangeAr = [[4,132877,132881],[4,55628,55632]]

histAr = []
canAr = []


histGenRawAr = []
canGenRawAr = []

histRawAr = []
canRawAr = []

histSelectedAr = []
canSelectedAr = []

histHFJGenAr = []
canHFJGenAr = []

histZFJGenAr = []
canZFJGenAr = []

histZHFJGenAr = []
canZHFJGenAr = []

histZHJGenAr = []
canZHJGenAr = []

histZJGenAr = []
canZJGenAr = []

#Arrays for tagged trees

histGenRawTaggedAr = []
canGenRawTaggedAr = []

histRawTaggedAr = []
canRawTaggedAr = []

histHFJGenTaggedAr = []
canHFJGenTaggedAr = []

histZFJGenTaggedAr = []
canZFJGenTaggedAr = []

histZHFJGenTaggedAr = []
canZHFJGenTaggedAr = []

histZHJGenTaggedAr = []
canZHJGenTaggedAr = []

histZJGenTaggedAr = []
canZJGenTaggedAr = []


#Higgs gen matching with FatJets tree

HFJGenSaveNameAr = ["HPtFromHFJGen","HEtaFromHFJGen","HPhiFromHFJGen","HMassFromHFJGen","HdRFromFJFromHFJGen",
"HnDecayFromHFJGen","HDecaypdgIdFromHFJGen"]

HFJGenSaveNameAr = [genSaveName+tightCutStr for genSaveName in HFJGenSaveNameAr]
HFJGenTitleAr = ["H Pt","H Eta","H Phi","H Mass","Gen Higgs dR from Matched Fat Jet",
"Number of Decay Products from Higgs","Higgs Decay Particle PDG Id"]

HFJGenXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId"]

HFJGenBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[5,0,5],[12,-6,6]]

#Z gen matching with FatJets tree

ZFJGenSaveNameAr = ["ZLeadPtFromZFJGen","ZLeadEtaFromZFJGen","ZLeadPhiFromZFJGen","ZLeadMassFromZFJGen","ZLeaddRFromFJFromZFJGen",
"ZLeadnDecayFromZFJGen","ZLeadDecaypdgIdFromZFJGen",
"ZTrailingPtFromZFJGen","ZTrailingEtaFromZFJGen","ZTrailingPhiFromZFJGen","ZTrailingMassFromZFJGen","ZTrailingdRFromFJFromZFJGen",
"ZTrailingnDecayFromZFJGen","ZTrailingDecaypdgIdFromZFJGen",
"ZPairInvMassFromZFJGen","ZPairEtaSepFromZFJGen"]

ZFJGenSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZFJGenSaveNameAr]

ZFJGenTitleAr = ["Lead Z Pt","Lead Z Eta","Lead Z Phi","Lead Z Mass","Gen Lead Z dR from Matched Fat Jet",
"Number of Decay Products from Lead Z","Lead Z Decay Particle PDG Id",
"Trailing Z Pt","Trailing Z Eta","Trailing Z Phi","Trailing Z Mass","Gen Trailing Z dR from Matched Fat Jet",
"Number of Decay Products from Trailing Z","Trailing Z Decay Particle PDG Id",
"Z Pair Invariant Mass","Z Pair Eta Separation"]

ZFJGenXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Invariant Mass (GeV)","Eta Separation"]

ZFJGenBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8]]

#Higgs and Z gen matching with FatJets tree

ZHFJGenSaveNameAr = ["ZPairPlusHInvMassFromZHFJGen"]
ZHFJGenSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZHFJGenSaveNameAr]
ZHFJGenTitleAr = ["Invariant Mass of Z Pair With Higgs"]
ZHFJGenXTitleAr = ["Invariant Mass (GeV)"]
ZHFJGenBinsAndRangeAr = [[100,0,6000]]

#Higgs and Z gen matching with jets tree

ZHJGenSaveNameAr = ["ZPairPlusHInvMassFromZHJGen"]
ZHJGenSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZHJGenSaveNameAr]
ZHJGenTitleAr = ["Invariant Mass of Z Pair With Higgs"]
ZHJGenXTitleAr = ["Invariant Mass (GeV)"]
ZHJGenBinsAndRangeAr = [[100,0,6000]]

#Z gen matching with jets tree

ZJGenSaveNameAr = ["ZLeadPtFromZJGen","ZLeadEtaFromZJGen","ZLeadPhiFromZJGen","ZLeadMassFromZJGen","ZLeaddRFromJFromZJGen",
"ZLeadnDecayFromZJGen","ZLeadDecaypdgIdFromZJGen",
"ZTrailingPtFromZJGen","ZTrailingEtaFromZJGen","ZTrailingPhiFromZJGen","ZTrailingMassFromZJGen","ZTrailingdRFromJFromZJGen",
"ZTrailingnDecayFromZJGen","ZTrailingDecaypdgIdFromZJGen",
"ZPairInvMassFromZJGen","ZPairEtaSepFromZJGen"]

ZJGenSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZJGenSaveNameAr]

ZJGenTitleAr = ["Lead Z Pt","Lead Z Eta","Lead Z Phi","Lead Z Mass","Gen Lead Z dR from Matched Jet",
"Number of Decay Products from Lead Z","Lead Z Decay Particle PDG Id",
"Trailing Z Pt","Trailing Z Eta","Trailing Z Phi","Trailing Z Mass","Gen Trailing Z dR from Matched Jet",
"Number of Decay Products from Trailing Z","Trailing Z Decay Particle PDG Id",
"Z Pair Invariant Mass","Z Pair Eta Separation"]

ZJGenXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Invariant Mass (GeV)","Eta Separation"]

ZJGenBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8]]


GenRawSaveNameAr = ["Z1PtFromGenRaw","Z1EtaFromGenRaw","Z1PhiFromGenRaw","Z1MassFromGenRaw","Z1pdgIdFromGenRaw","Z1genPartIdxMotherFromGenRaw",
"Z1nDecayFromGenRaw","Z1DecaypdgIdFromGenRaw",
"Z2PtFromGenRaw","Z2EtaFromGenRaw","Z2PhiFromGenRaw","Z2MassFromGenRaw","Z2pdgIdFromGenRaw","Z2genPartIdxMotherFromGenRaw",
"Z2nDecayFromGenRaw","Z2DecaypdgIdFromGenRaw",
"ZPairInvMassFromGenRaw","ZPairEtaSepFromGenRaw",
"HPtFromGenRaw","HEtaFromGenRaw","HPhiFromGenRaw","HMassFromGenRaw","HpdgIdFromGenRaw","HgenPartIdxMotherFromGenRaw",
"HnDecayFromGenRaw","HDecaypdgIdFromGenRaw",
"ZPairPlusHInvMassFromGenRaw"]


GenRawTitleAr = ["Lead Z Pt","Lead Z Eta","Lead Z Phi","Lead Z Mass","Lead Z pdgId","Lead Z Gen Part Mother Ind",
"Number of Decay Products from Lead Z","Lead Z Decay Particle PDG Id",
"Trailing Z Pt","Trailing Z Eta","Trailing Z Phi","Trailing Z Mass","Trailing Z pdgId","Trailing Z Gen Part Mother Ind",
"Number of Decay Products from Trailing Z","Trailing Z Decay Particle PDG Id",
"Z Pair Invariant Mass","Z Pair Eta Separation",
"H Pt","H Eta","H Phi","H Mass","H pdgId","H Gen Part Mother Ind",
"Number of Decay Products from Higgs","Higgs Decay Particle PDG Id",
"Z Pair Plus H Invariant Mass"]

GenRawXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","Gen Part Mother Ind",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","Gen Part Mother Ind",
"N","pdgId",
"Mass (GeV)","Eta Separation",
"Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","Gen Part Mother Ind",
"N","pdgId",
"Mass (GeV)"]

GenRawBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[5,0,5],[12,-6,6],
[100,0,6000]]



RawSaveNameAr = ["Z1PtFromLHERaw","Z1EtaFromLHERaw","Z1PhiFromLHERaw","Z1MassFromLHERaw",
"Z2PtFromLHERaw","Z2EtaFromLHERaw","Z2PhiFromLHERaw","Z2MassFromLHERaw",
"ZPairInvMassFromLHERaw","ZPairEtaSepFromLHERaw",
"HPtFromLHERaw","HEtaFromLHERaw","HPhiFromLHERaw","HMassFromLHERaw","ZPairPlusHInvMassFromLHERaw",
"JetLeadPtFromLHERaw","JetLeadEtaFromLHERaw","JetLeadPhiFromLHERaw","JetLeadInvMassFromLHERaw","JetLeadpdgIdFromLHERaw",
"JetTrailingPtFromLHERaw","JetTrailingEtaFromLHERaw","JetTrailingPhiFromLHERaw","JetTrailingInvMassFromLHERaw","JetTrailingpdgIdFromLHERaw",
"JPairInvMassFromLHERaw","JPairEtaSepFromLHERaw"]


RawTitleAr = ["Lead Z Pt","Lead Z Eta","Lead Z Phi","Lead Z Mass",
"Trailing Z Pt","Trailing Z Eta","Trailing Z Phi","Trailing Z Mass",
"Z Pair Invariant Mass","Z Pair Eta Separation",
"H Pt","H Eta","H Phi","H Mass","Z Pair Plus H Invariant Mass",
"Jet Lead Pt","Jet Lead Eta","Jet Lead Phi","Jet Lead Invariant Mass","Jet Lead pdgId",
"Jet Trailing Pt","Jet Trailing Eta","Jet Trailing Phi","Jet Trailing Invariant Mass","Jet Trailing pdgId",
"Jet Pair Invariant Mass", "Jet Pair Eta Separation"]

RawXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)",
"Pt (GeV)","Eta","Phi","Mass (GeV)",
"Mass (GeV)","Eta Separation",
"Pt (GeV)","Eta","Phi","Mass (GeV)","Mass (GeV)", 
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Invariant Mass (GeV)", "Eta Separation"]

RawBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[100,0,6000],[40,0,8],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[100,0,6000],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[100,0,6000],[40,0,8]]


################ TAGGING TREES

#Higgs gen matching with FatJets tree

HFJGenTaggedSaveNameAr = ["HPtFromHFJGenTagged","HEtaFromHFJGenTagged","HPhiFromHFJGenTagged","HMassFromHFJGenTagged","HdRFromFJFromHFJGenTagged",
"HnDecayFromHFJGenTagged","HDecaypdgIdFromHFJGenTagged"]
HFJGenTaggedSaveNameAr = [genSaveName+tightCutStr for genSaveName in HFJGenTaggedSaveNameAr]

HFJGenTaggedTitleAr = ["H Pt for Hadronic Events","H Eta for Hadronic Events","H Phi for Hadronic Events","H Mass for Hadronic Events","Gen Higgs dR from Matched Fat Jet for Hadronic Events",
"Number of Decay Products from Higgs for Hadronic Events","Higgs Decay Particle PDG Id for Hadronic Events"]

HFJGenTaggedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId"]

HFJGenTaggedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[5,0,5],[12,-6,6]]

#Z gen matching with FatJets tree

ZFJGenTaggedSaveNameAr = ["ZLeadPtFromZFJGenTagged","ZLeadEtaFromZFJGenTagged","ZLeadPhiFromZFJGenTagged","ZLeadMassFromZFJGenTagged","ZLeaddRFromFJFromZFJGenTagged",
"ZLeadnDecayFromZFJGenTagged","ZLeadDecaypdgIdFromZFJGenTagged",
"ZTrailingPtFromZFJGenTagged","ZTrailingEtaFromZFJGenTagged","ZTrailingPhiFromZFJGenTagged","ZTrailingMassFromZFJGenTagged","ZTrailingdRFromFJFromZFJGenTagged",
"ZTrailingnDecayFromZFJGenTagged","ZTrailingDecaypdgIdFromZFJGenTagged",
"ZPairInvMassFromZFJGenTagged","ZPairEtaSepFromZFJGenTagged"]

ZFJGenTaggedSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZFJGenTaggedSaveNameAr]

ZFJGenTaggedTitleAr = ["Lead Z Pt for Hadronic Events","Lead Z Eta for Hadronic Events","Lead Z Phi for Hadronic Events","Lead Z Mass for Hadronic Events","GenTagged Lead Z dR from Matched Fat Jet for Hadronic Events",
"Number of Decay Products from Lead Z for Hadronic Events","Lead Z Decay Particle PDG Id for Hadronic Events",
"Trailing Z Pt for Hadronic Events","Trailing Z Eta for Hadronic Events","Trailing Z Phi for Hadronic Events","Trailing Z Mass for Hadronic Events","GenTagged Trailing Z dR from Matched Fat Jet for Hadronic Events",
"Number of Decay Products from Trailing Z for Hadronic Events","Trailing Z Decay Particle PDG Id for Hadronic Events",
"Z Pair Invariant Mass for Hadronic Events","Z Pair Eta Separation for Hadronic Events"]

ZFJGenTaggedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Invariant Mass (GeV)","Eta Separation"]

ZFJGenTaggedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8]]

#Higgs and Z gen matching with FatJets tree

ZHFJGenTaggedSaveNameAr = ["ZPairPlusHInvMassFromZHFJGenTagged"]
ZHFJGenTaggedSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZHFJGenTaggedSaveNameAr]

ZHFJGenTaggedTitleAr = ["Invariant Mass of Z Pair With Higgs for Hadronic Events"]
ZHFJGenTaggedXTitleAr = ["Invariant Mass (GeV)"]
ZHFJGenTaggedBinsAndRangeAr = [[100,0,6000]]

#Higgs and Z gen matching with jets tree

ZHJGenTaggedSaveNameAr = ["ZPairPlusHInvMassFromZHJGenTagged"]
ZHJGenTaggedSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZHJGenTaggedSaveNameAr]
ZHJGenTaggedTitleAr = ["Invariant Mass of Z Pair With Higgs for Hadronic Events"]
ZHJGenTaggedXTitleAr = ["Invariant Mass (GeV)"]
ZHJGenTaggedBinsAndRangeAr = [[100,0,6000]]

#Z gen matching with jets tree

ZJGenTaggedSaveNameAr = ["ZLeadPtFromZJGenTagged","ZLeadEtaFromZJGenTagged","ZLeadPhiFromZJGenTagged","ZLeadMassFromZJGenTagged","ZLeaddRFromJFromZJGenTagged",
"ZLeadnDecayFromZJGenTagged","ZLeadDecaypdgIdFromZJGenTagged",
"ZTrailingPtFromZJGenTagged","ZTrailingEtaFromZJGenTagged","ZTrailingPhiFromZJGenTagged","ZTrailingMassFromZJGenTagged","ZTrailingdRFromJFromZJGenTagged",
"ZTrailingnDecayFromZJGenTagged","ZTrailingDecaypdgIdFromZJGenTagged",
"ZPairInvMassFromZJGenTagged","ZPairEtaSepFromZJGenTagged"]

ZJGenTaggedSaveNameAr = [genSaveName+tightCutStr for genSaveName in ZJGenTaggedSaveNameAr]

ZJGenTaggedTitleAr = ["Lead Z Pt for Hadronic Events","Lead Z Eta for Hadronic Events","Lead Z Phi for Hadronic Events","Lead Z Mass for Hadronic Events","GenTagged Lead Z dR from Matched Jet for Hadronic Events",
"Number of Decay Products from Lead Z for Hadronic Events","Lead Z Decay Particle PDG Id for Hadronic Events",
"Trailing Z Pt for Hadronic Events","Trailing Z Eta for Hadronic Events","Trailing Z Phi for Hadronic Events","Trailing Z Mass for Hadronic Events","GenTagged Trailing Z dR from Matched Jet for Hadronic Events",
"Number of Decay Products from Trailing Z for Hadronic Events","Trailing Z Decay Particle PDG Id for Hadronic Events",
"Z Pair Invariant Mass for Hadronic Events","Z Pair Eta Separation for Hadronic Events"]

ZJGenTaggedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","dR",
"N","pdgId",
"Invariant Mass (GeV)","Eta Separation"]

ZJGenTaggedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,400],[50,0,0.4],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8]]


GenRawTaggedSaveNameAr = ["Z1PtFromGenRawTagged","Z1EtaFromGenRawTagged","Z1PhiFromGenRawTagged","Z1MassFromGenRawTagged","Z1pdgIdFromGenRawTagged","Z1genPartIdxMotherFromGenRawTagged",
"Z1nDecayFromGenRawTagged","Z1DecaypdgIdFromGenRawTagged",
"Z2PtFromGenRawTagged","Z2EtaFromGenRawTagged","Z2PhiFromGenRawTagged","Z2MassFromGenRawTagged","Z2pdgIdFromGenRawTagged","Z2genPartIdxMotherFromGenRawTagged",
"Z2nDecayFromGenRawTagged","Z2DecaypdgIdFromGenRawTagged",
"ZPairInvMassFromGenRawTagged","ZPairEtaSepFromGenRawTagged",
"HPtFromGenRawTagged","HEtaFromGenRawTagged","HPhiFromGenRawTagged","HMassFromGenRawTagged","HpdgIdFromGenRawTagged","HgenPartIdxMotherFromGenRawTagged",
"HnDecayFromGenRawTagged","HDecaypdgIdFromGenRawTagged",
"ZPairPlusHInvMassFromGenRawTagged"]


GenRawTaggedTitleAr = ["Lead Z Pt for Hadronic Events","Lead Z Eta for Hadronic Events","Lead Z Phi for Hadronic Events","Lead Z Mass for Hadronic Events","Lead Z pdgId for Hadronic Events","Lead Z GenTagged Part Mother Ind for Hadronic Events",
"Number of Decay Products from Lead Z for Hadronic Events","Lead Z Decay Particle PDG Id for Hadronic Events",
"Trailing Z Pt for Hadronic Events","Trailing Z Eta for Hadronic Events","Trailing Z Phi for Hadronic Events","Trailing Z Mass for Hadronic Events","Trailing Z pdgId for Hadronic Events","Trailing Z GenTagged Part Mother Ind for Hadronic Events",
"Number of Decay Products from Trailing Z for Hadronic Events","Trailing Z Decay Particle PDG Id for Hadronic Events",
"Z Pair Invariant Mass for Hadronic Events","Z Pair Eta Separation for Hadronic Events",
"H Pt for Hadronic Events","H Eta for Hadronic Events","H Phi for Hadronic Events","H Mass for Hadronic Events","H pdgId for Hadronic Events","H GenTagged Part Mother Ind for Hadronic Events",
"Number of Decay Products from Higgs for Hadronic Events","Higgs Decay Particle PDG Id for Hadronic Events",
"Z Pair Plus H Invariant Mass for Hadronic Events"]

GenRawTaggedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","GenTagged Part Mother Ind",
"N","pdgId",
"Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","GenTagged Part Mother Ind",
"N","pdgId",
"Mass (GeV)","Eta Separation",
"Pt (GeV)","Eta","Phi","Mass (GeV)","pdgId","GenTagged Part Mother Ind",
"N","pdgId",
"Mass (GeV)"]

GenRawTaggedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[4,0,4],[36,-18,18],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[4,0,4],[36,-18,18],
[100,0,6000],[40,0,8],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[60,-30,30],[110,0,110],
[5,0,5],[12,-6,6],
[100,0,6000]]



RawTaggedSaveNameAr = ["Z1PtFromLHERawTagged","Z1EtaFromLHERawTagged","Z1PhiFromLHERawTagged","Z1MassFromLHERawTagged",
"Z2PtFromLHERawTagged","Z2EtaFromLHERawTagged","Z2PhiFromLHERawTagged","Z2MassFromLHERawTagged",
"ZPairInvMassFromLHERawTagged","ZPairEtaSepFromLHERawTagged",
"HPtFromLHERawTagged","HEtaFromLHERawTagged","HPhiFromLHERawTagged","HMassFromLHERawTagged","ZPairPlusHInvMassFromLHERawTagged",
"JetLeadPtFromLHERawTagged","JetLeadEtaFromLHERawTagged","JetLeadPhiFromLHERawTagged","JetLeadInvMassFromLHERawTagged","JetLeadpdgIdFromLHERawTagged",
"JetTrailingPtFromLHERawTagged","JetTrailingEtaFromLHERawTagged","JetTrailingPhiFromLHERawTagged","JetTrailingInvMassFromLHERawTagged","JetTrailingpdgIdFromLHERawTagged",
"JPairInvMassFromLHERawTagged","JPairEtaSepFromLHERawTagged"]


RawTaggedTitleAr = ["Lead Z Pt for Hadronic Events","Lead Z Eta for Hadronic Events","Lead Z Phi for Hadronic Events","Lead Z Mass for Hadronic Events",
"Trailing Z Pt for Hadronic Events","Trailing Z Eta for Hadronic Events","Trailing Z Phi for Hadronic Events","Trailing Z Mass for Hadronic Events",
"Z Pair Invariant Mass for Hadronic Events","Z Pair Eta Separation for Hadronic Events",
"H Pt for Hadronic Events","H Eta for Hadronic Events","H Phi for Hadronic Events","H Mass for Hadronic Events","Z Pair Plus H Invariant Mass for Hadronic Events",
"Jet Lead Pt for Hadronic Events","Jet Lead Eta for Hadronic Events","Jet Lead Phi for Hadronic Events","Jet Lead Invariant Mass for Hadronic Events","Jet Lead pdgId for Hadronic Events",
"Jet Trailing Pt for Hadronic Events","Jet Trailing Eta for Hadronic Events","Jet Trailing Phi for Hadronic Events","Jet Trailing Invariant Mass for Hadronic Events","Jet Trailing pdgId for Hadronic Events",
"Jet Pair Invariant Mass for Hadronic Events", "Jet Pair Eta Separation for Hadronic Events"]

RawTaggedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)",
"Pt (GeV)","Eta","Phi","Mass (GeV)",
"Mass (GeV)","Eta Separation",
"Pt (GeV)","Eta","Phi","Mass (GeV)","Mass (GeV)", 
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Invariant Mass (GeV)", "Eta Separation"]

RawTaggedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[100,0,6000],[40,0,8],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[100,0,6000],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[100,0,6000],[40,0,8]]


############

SelectedSaveNameAr = ["Z1PtFromLHESelected","Z1EtaFromLHESelected","Z1PhiFromLHESelected","Z1MassFromLHESelected",
"Z2PtFromLHESelected","Z2EtaFromLHESelected","Z2PhiFromLHESelected","Z2MassFromLHESelected",
"ZPairInvMassFromLHESelected","ZPairEtaSepFromLHESelected",
"HPtFromLHESelected","HEtaFromLHESelected","HPhiFromLHESelected","HMassFromLHESelected","ZPairPlusHInvMassFromLHESelected",
"JetLeadPtFromLHESelected","JetLeadEtaFromLHESelected","JetLeadPhiFromLHESelected","JetLeadInvMassFromLHESelected","JetLeadpdgIdFromLHESelected",
"JetTrailingPtFromLHESelected","JetTrailingEtaFromLHESelected","JetTrailingPhiFromLHESelected","JetTrailingInvMassFromLHESelected","JetTrailingpdgIdFromLHESelected",
"JPairInvMassFromLHESelected","JPairEtaSepFromLHESelected"
]


SelectedTitleAr = ["Z1 Lead Pt After Cuts","Z1 Lead Eta After Cuts","Lead Z Phi","Lead Z Mass",
"Trailing Z Pt","Trailing Z Eta","Trailing Z Phi","Trailing Z Mass",
"Z Pair Invariant Mass","Z Pair Eta Separation",
"H Pt","H Eta","H Phi","H Mass","Z Pair Plus H Invariant Mass",
"Jet Lead Pt After Cuts","Jet Lead Eta After Cuts","Jet Lead Phi After Cuts","Jet Lead Invariant Mass After Cuts","Jet Lead pdgId",
"Jet Trailing Pt After Cuts","Jet Trailing Eta After Cuts","Jet Trailing Phi After Cuts","Jet Trailing Invariant Mass After Cuts","Jet Trailing pdgId",
"Jet Pair Invariant Mass After Cuts", "Jet Pair Eta Separation After Cuts"]

SelectedXTitleAr = ["Pt (GeV)","Eta","Phi","Mass (GeV)",
"Pt (GeV)","Eta","Phi","Mass (GeV)",
"Mass (GeV)","Eta Separation",
"Pt (GeV)","Eta","Phi","Mass (GeV)","Mass (GeV)", 
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Pt (GeV)","Eta","Phi","Invariant Mass (GeV)","pdg Id",
"Invariant Mass (GeV)", "Eta Separation"]

SelectedBinsAndRangeAr = [[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],
[100,0,6000],[40,0,8],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[100,0,200],[100,0,6000],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[34,0.,2500.],[50,-4.5,4.5],[50,-3.5,3.5],[50,-0.03,0.03],[10,-5,5],
[100,0,6000],[40,0,8]]



FASaveNameAr = ["nJets","JetLeadPt","JetTrailingPt","JetLeadPhi","JetTrailingPhi","JetPairIM","JetLeadEta","JetTrailingEta",
"nFJ","FJPt","FJPhi","FJEta","FJMass","FJDeepTagH",
"FJPt_UsingDTH","FJPhi_UsingDTH","FJEta_UsingDTH","FJMass_UsingDTH","FJDeepTagH_UsingDTH",

"nGP","dR","Ind","pdg","pdgMom",
"dR_UsingDTH","Ind_UsingDTH","pdg_UsingDTH","pdgMom_UsingDTH",
"hbbTag","DEHLT","DMHLT","MEGHLT","SEHLT","SMHLT","HHLT",
"LepChannel","SemiLepChannel","HadChannel",
"passedLep","passedSemiLep","passedHad"
]


FATitleAr = ["Number of Jets","Jet Lead Pt","Jet Trailing Pt","Jet Lead Phi","Jet Trailing Phi","Jet Pair Inv Mass","Jet Lead Eta","Jet Trailing Eta",
"Number of Fat Jets","Pt of Higgs Candidate Fat Jets","Phi of Higgs Candidate Fat Jets","Eta of Higgs Candidate Fat Jets","Mass of Higgs Candidate Fat Jets","DeepTag_H of Higgs Candidate Fat Jets",
"Pt of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Phi of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Eta of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Mass of Higgs Candidate Fat Jets Chosen Using DeepTag_H","DeepTag_H of Higgs Candidate Fat Jets Chosen Using DeepTag_H",

"Number of Gen Particles","dR of Higgs Candidate Fat Jet to Closest Gen Particle","Index of Closest Gen Particle to Higgs Candidate Fat Jet","pdg Id of Closest Gen Particle to Higgs Candidate Fat Jet","pdg Id of Initial Particle Leading to Closest Gen Particle to Higgs Candidate Fat Jet",
"dR of Higgs Candidate Fat Jet to Closest Gen Particle Chosen Using DeepTag_H","Index of Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H","pdg Id of Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H","pdg Id of Initial Particle Leading to Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H",
"Hbb Tag for Events that Pass (always true)","Double Elec HLT","Double Muon HLT","Muon EG HLT","Single Electron HLT","Single Muon HLT","Hadronic HLT",
"Leptonic Channel","Semi-Leptonic Channel","Hadronic Channel",
"passedLep","passedSemiLep","passedHad"]

FAXTitleAr = ["nJet","Pt (GeV)","Pt (GeV)","Phi","Phi","Inv Mass (GeV)","Eta","Eta",
"nFatJet","Pt (GeV)","Phi","Eta","Mass (GeV)","DeepTag_H",
"Pt (GeV)","Phi","Eta","Mass (GeV)","DeepTag_H",

"nGenParts","dR","Index","pdg Id","pdg Id",
"dR","Index","pdg Id","pdg Id",
"","","","","","","",
"","","",
"","",""]

FABinsAndRangeAr = [[20,0,20],[50,0,2500],[50,0,2500],[50,-3.5,3.5],[50,-3.5,3.5],[100,0,6000],[50,-4.5,4.5],[50,-4.5,4.5],
[8,0,8],[50,0,2500],[50,-3.5,3.5],[50,-4.5,4.5],[60,0,600],[100,0,1],
[50,0,2500],[50,-3.5,3.5],[50,-4.5,4.5],[60,0,600],[100,0,1],

[160,0,160],[30,0,0.3],[120,0,120],[35,-5,30],[35,-5,30],
[30,0,0.3],[120,0,120],[35,-5,30],[35,-5,30],
[3,0,3],[2,0,2],[2,0,2],[2,0,2],[2,0,2],[2,0,2],[2,0,2],
[2,0,2],[2,0,2],[2,0,2],
[2,0,2],[2,0,2],[2,0,2]]


yTitle = "Weighted Events"


def setUpLegend(legAr):
  legAr.append(TLegend(.9,.6,.99,.92))
  legAr[-1].SetTextSize(0.036)
  legAr[-1].SetTextFont(42)


def setUpPadsAr(padAr,padName):
  padAr.append([])
  padAr[-1].append(TPad(padName, padName,0.,0.40,1,1))
  padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.45))
  #padAr[-1].append(TPad(padName, padName,0.,0.70,1,1))
  #padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.60))

def setUpBottomPadsAr(padAr,logYForRatioPlot):
  padAr[1].SetTopMargin(0)
  padAr[1].SetBottomMargin(0.15)
  if logYForRatioPlot:
    padAr[1].SetLogy()
  padAr[1].Draw()
  padAr[1].cd()

def makeNiceHistos(histo,xTitle,yTitle,noX=True):
  if noX:
    #histo.GetXaxis().SetLabelOffset(999)
    histo.GetXaxis().SetLabelSize(0)
  else:
    histo.GetXaxis().SetTitle(xTitle)
    histo.GetXaxis().SetTitleSize(0.068)
    histo.GetXaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetXaxis().SetLabelSize(0.055)
  histo.GetYaxis().SetTitle(yTitle)
  histo.GetYaxis().CenterTitle()
  histo.GetYaxis().SetTitleOffset(0.55)
  histo.GetYaxis().SetTitleSize(0.068)
  histo.GetYaxis().SetTitleFont(42)
  histo.GetYaxis().SetLabelFont(42)
  histo.GetYaxis().SetLabelSize(0.055)
  histo.SetTitle("")
  histo.SetStats(0)

  
def setHistoElementsForLHETrees(colorAr,histAr,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo,useLHEAr):
    for k,colorA in zip(range(len(colorAr)),colorAr):
      if useLHEAr[k]:
        intAr.append([])
        for histTypeItr, histTitleName in enumerate(histTitleNameAr):
          if onlyDoSomeHists and histTypeItr >= histsToDo:
            break
          
          histAr[k][histTypeItr].SetLineColor(colorA)
          histAr[k][histTypeItr].SetLineWidth(4)
          histAr[k][histTypeItr].SetFillColorAlpha(colorA,0.2)

def normalizeHistsForLHETrees(histAr,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr):
    histMaxAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      histMaxAr.append(0)
    for k in range(len(histAr)):
      if useLHEAr[k]:
        for histTypeItr in range(len(histTypeSaveNameAr)):
          if onlyDoSomeHists and histTypeItr >= histsToDo:
            break
          histAr[k][histTypeItr].Sumw2()
          histAr[k][histTypeItr].Scale(weightsAr[k])
          tmpMax = histAr[k][histTypeItr].GetMaximum()
          if tmpMax > histMaxAr[histTypeItr]:
              histMaxAr[histTypeItr] = tmpMax
          legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr

def setUpNonStackedHistAndFoMPlotForLHETrees(compCan,cloneHistAr,padAr,histMax,histAr,legAr,dataName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr):
  for k in range(len(histAr)):
      if useLHEAr[k]:
        cloneHistAr.append([])
        for histTypeItr in range(len(histTypeSaveNameAr)):
            if onlyDoSomeHists and histTypeItr >= histsToDo:
              break
            cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())


  
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
    histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
    histAr[0][histTypeItr].Draw("hist E1")

    for j in range(1,len(histAr)):
      if useLHEAr[j]:
        histAr[j][histTypeItr].DrawCopy("same hist E1")
  
    legAr[histTypeItr].Draw()
    compCan[histTypeItr].cd()

    setUpBottomPadsAr(padAr[histTypeItr],useLogYForRatioPlot) 

    histAr[0][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        cloneHistAr[k][histTypeItr].Sumw2()
        cloneHistAr[k][histTypeItr].Divide(histAr[0][histTypeItr])
        makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to cHW",False)
        cloneHistAr[k][histTypeItr].SetLineWidth(2)
        if k == 0 and not useLogYForRatioPlot:
          cloneHistAr[k][histTypeItr].GetYaxis().SetRangeUser(0.,2.0)
        elif useLogYForRatioPlot:
          cloneHistAr[k][histTypeItr].GetYaxis().SetRangeUser(0.01,1000000.0)
        cloneHistAr[k][histTypeItr].Draw("et same")


    compCan[histTypeItr].Update()
    compCan[histTypeItr].Draw()


    if normalizeDataTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_NBT_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_NBT_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    


def setHistoElements(colorAr,histAr,normalizeDataTogether,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo):
    dataIntSumAr = []
    for histTypeItr, histTitleName in enumerate(histTitleNameAr):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      dataIntSumAr.append(0)
    for k,colorA in zip(range(len(colorAr)),colorAr):
      intAr.append([])
      for histTypeItr, histTitleName in enumerate(histTitleNameAr):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        histAr[k][histTypeItr].SetLineColor(colorA)
        histAr[k][histTypeItr].SetLineWidth(4)

        histAr[k][histTypeItr].SetFillColorAlpha(colorA,0.2)
        makeNiceHistos(histAr[k][histTypeItr],"","Weighted Events/Bin (pb)",True)
        histAr[k][histTypeItr].SetTitle(histTitleName)
        tmpHistInt = histAr[k][histTypeItr].Integral()
        if normalizeDataTogether:
                dataIntSumAr[histTypeItr] += tmpHistInt*weightsAr[k]
        intAr[-1].append(tmpHistInt)
    return dataIntSumAr




def normalizeHists(histAr,normalizeDataTogether,dataIntSum,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    histMaxAr = []
    histMinAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      histMaxAr.append(0)
      histMinAr.append(9999)
    for k in range(len(histAr)):
      for histTypeItr in range(len(histTypeSaveNameAr)):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        histAr[k][histTypeItr].Sumw2()
        #print(k,histTypeItr)
        #print(dataIntSum)
        #print(isSignalAr)
        if normalizeDataTogether and dataIntSum[histTypeItr]:
            
            #histAr[k][histTypeItr].Scale(weightsAr[k] / dataIntSum[histTypeItr])
            histAr[k][histTypeItr].Scale(weightsAr[k])
            tmpMax = histAr[k][histTypeItr].GetMaximum()
            if tmpMax > histMaxAr[histTypeItr]:
                histMaxAr[histTypeItr] = tmpMax
            if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                histMinAr[histTypeItr] = tmpMax

            legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
        elif intAr[k][histTypeItr]:
            #print(k,histTypeItr)
            #print(intAr[k][histTypeItr])
            if scaleSignalToBackground:
              histAr[k][histTypeItr].Scale(1.0 / intAr[k][histTypeItr])
            print("-----------------")

            tmpMax = histAr[k][histTypeItr].GetMaximum()
            if not normalizeDataTogether:
              if tmpMax > histMaxAr[histTypeItr]:
                histMaxAr[histTypeItr] = tmpMax
              if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                histMinAr[histTypeItr] = tmpMax
            legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr,histMinAr


def setUpInvHists(histAr,cloneHistAr,invHistsAr,nameAr,intAr,drawInvAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    for k in range(len(histAr)):
      
      cloneHistAr.append([])
      invHistsAr.append([])
      drawInvAr.append([])
      for histTypeItr in range(len(histTypeSaveNameAr)):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())
        invHistsAr[-1].append(histAr[k][histTypeItr].Clone("{0}Inv".format(nameAr[k])))
        if intAr[k][histTypeItr]:
            drawInvAr[-1].append(True)

            tmpNBins = histAr[k][histTypeItr].GetNbinsX()
            tmpBinErrorAr = []
            for i in range(tmpNBins):
                tmpBinErrorAr.append(histAr[k][histTypeItr].GetBinError(i))
            for j in range(k):
                invHistsAr[-1][histTypeItr].Add(histAr[j][histTypeItr])
            for i in range(tmpNBins):
                invHistsAr[-1][histTypeItr].SetBinError(i,tmpBinErrorAr[i])
        else:
            drawInvAr[-1].append(False)


def setUpNonStackedHistAndFoMPlot(compCan,cloneHistAr,padAr,histMax,histMin,normalizeDataTogether,histAr,legAr,dataName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,onlyDoSomeHists,histsToDo):
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    if useLogY:
      padAr[histTypeItr][0].SetLogy()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    tmpMax = histAr[0][histTypeItr].GetMaximum()
    if tmpMax > histMax[histTypeItr]:
        histMax[histTypeItr] = tmpMax
    if tmpMax > 0 and tmpMax < histMin[histTypeItr]:
        histMin[histTypeItr] = tmpMax
    if not useLogY:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
    else:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(histMin[histTypeItr]*0.01,histMax[histTypeItr]*1.1)
    histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
    histAr[0][histTypeItr].Draw("hist E1")

    for j in range(1,len(histAr)):
        histAr[j][histTypeItr].DrawCopy("same hist E1")
    
  
    legAr[histTypeItr].Draw()
    compCan[histTypeItr].cd()

    setUpBottomPadsAr(padAr[histTypeItr],useLogYForRatioPlot) 

    histAr[0][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        #cloneHistAr[k][histTypeItr].Sumw2()
        #cloneHistAr[k][histTypeItr].Divide(histAr[signalPos][histTypeItr])
        #makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to Signal",False)
        #cloneHistAr[k][histTypeItr].SetLineWidth(2)
        cloneHistAr[k][histTypeItr].Draw("et same")

    if useLogY:
      compCan[histTypeItr].SetLogy()

    compCan[histTypeItr].Update()
    compCan[histTypeItr].Draw()


    #REPLACE WITH RATIO PAD
    """
    FoMGraph.Draw("APL same")
    #compCan.Update()
    #tmpFoMMin = FoMGraph.GetMinimum()
    tmpFoMMin = 0
    tmpFoMMax = FoMGraph.GetMaximum()
    defaultCutLine = TLine(defaultCutPos,tmpFoMMin,defaultCutPos,histMax)
    defaultCutLine.SetLineColor(2)
    defaultCutLine.SetLineWidth(4)
    defaultCutLine.SetLineStyle(9)
    defaultCutLine.Draw()
    compCan.Update()
    #"FP" stands for "Full Pass"
    """
    if normalizeDataTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_NBT_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_NBT_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{3}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    
