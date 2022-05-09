import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import THStack, TH1D, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log
from new032022FunctionsForFoMPlots import *
from new032022ResultsForFoMPlots import *
import time as time

startt = time.time()
cutNameAr = ['SemiLepInvMassCutLowCut','SemiLepInvMassCutHighCut''InvMassCutLowCut','InvMassCutHighCut']
debug = False
debugMin = 1000
debugMax = 1004
forCondor = False
if forCondor:
    forCondorStr = "/scratch365/dlutton/new042022AnalysisFiles/"
else:
    forCondorStr = ""
skipEvPassGraphs = False
variableRebin = False
variableRebinVar = 0.3
normalizeBackgroundsTogether = True
sumQCD = True
isQCDAr = []
altNameAr = []

MGSM = True
MGEFT = False
MGC2VEtaDifCut = True
ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = True
QCDPT600to800Background = True
QCDPT800to1000Background = True
QCDPT1000to1400Background = True
QCDPT1400to1800Background = True
QCDPT1800to2400Background = True
QCDPT2400to3200Background = True
QCDPT3200toInfBackground = True
"""
MGSM = True
MGEFT = False
MGC2VEtaDifCut = True

ttHToBBBackground = False
ttZJetsBackground = False
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = False
QCDPT600to800Background = False
QCDPT800to1000Background = False
QCDPT1000to1400Background = False
QCDPT1400to1800Background = False
QCDPT1800to2400Background = False
QCDPT2400to3200Background = False
QCDPT3200toInfBackground = False
"""
TTJetsBackground = True
TTToHadronicBackground = False
TTTo2L2NuBackground = False
TTToSemiLeptonicBackground = False
ST_s_ChannelBackground = True
ST_t_ChannelAntiTopBackground = True
ST_t_ChannelTopBackground = True
ZZTo2Q2NuBackground = True
WWTo2L2NuBackground = True
WZTo3LNuBackground = True

"""

ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = True
QCDPT600to800Background = True
QCDPT800to1000Background = True
QCDPT1000to1400Background = True
QCDPT1400to1800Background = True
QCDPT1800to2400Background = True
QCDPT2400to3200Background = True
QCDPT3200toInfBackground = True

TTJetsBackground = True
TTToHadronicBackground = True
TTTo2L2NuBackground = True
TTToSemiLeptonicBackground = True
ST_s_ChannelBackground = True
ST_t_ChannelAntiTopBackground = True
ST_t_ChannelTopBackground = True
ZZTo2Q2NuBackground = True
WWTo2L2NuBackground = True
WZTo3LNuBackground = True
"""

#All True

"""
MGSM = True
MGEFT = True
ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = True
QCDPT600to800Background = True
QCDPT800to1000Background = True
QCDPT1000to1400Background = True
QCDPT1400to1800Background = True
QCDPT1800to2400Background = True
QCDPT2400to3200Background = True
QCDPT3200toInfBackground = True
"""

XSBackgroundAr = []
totalBackgroundEvents = []
XSSignalAr = []
totalSignalEvents = []
fileAr = []
nameAr = []
isSignalAr = []
colorAr = []

saveNameAr = []

cutAmnt = 200
"""
ptCutBackgroundPassAr = []
ptCutSignalPassAr = []

deepTagCutBackgroundPassAr = []
deepTagCutSignalPassAr = []

VBFdRCutBackgroundPassAr = []
VBFdRCutSignalPassAr = []

VBFPtCutBackgroundPassAr = []
VBFPtCutSignalPassAr = []

VBFEtaCutBackgroundPassAr = []
VBFEtaCutSignalPassAr = []

VBFInvMassCutBackgroundPassAr = []
VBFInvMassCutSignalPassAr = []

evPassptCutAr = []
evPassDeepTagCutAr = []
evPassVBFdRCutAr = []
evPassVBFPtCutAr = []
evPassVBFEtaCutAr = []
evPassVBFInvMassCutAr = []
"""
doLep = False
doSL = True
if doLep:
    saveName = "Lep"
if doSL:
    saveName = "SL"
colorAr = []
fileAr = []
if MGSM:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(SMSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(SMSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(SMSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(SMSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(SMSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(SMSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(SMSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(SMSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(SMSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(SMSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(SMSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(SMSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(SMSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(SMSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(SMSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(SMSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(SMSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(SMSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(SMSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(SMSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(SMSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(SMSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(SMSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(SMSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(SMSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(SMSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(SMSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(SMSLSIPCutPassAr)

        evPasshFatJetPtAr.append(SMSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(SMSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(SMSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(SMSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(SMSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(SMSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(SMSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(SMSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(SMSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(SMSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(SMSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(SMSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(SMSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(SMSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(SMSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(SMSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(SMSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(SMSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(SMSLLepeEtaCutPassAr)
        evPassLepePtAr.append(SMSLLepePtCutPassAr)
        evPassPtLeadAr.append(SMSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(SMSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(SMSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(SMSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(SMSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(SMSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(SMSLLepIsoCutPassAr)
        evPassSIPAr.append(SMSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(SMLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(SMLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(SMLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(SMLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(SMLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(SMLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(SMLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(SMLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(SMLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(SMLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(SMLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(SMLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(SMLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(SMLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(SMLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(SMLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(SMLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(SMLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(SMLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(SMLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(SMLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(SMLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(SMLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(SMLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(SMLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(SMLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(SMLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(SMLepSIPCutPassAr)

        evPasshFatJetPtAr.append(SMLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(SMLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(SMLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(SMLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(SMLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(SMLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(SMLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(SMLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(SMLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(SMLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(SMLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(SMLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(SMLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(SMLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(SMLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(SMLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(SMLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(SMLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(SMLepLepeEtaCutPassAr)
        evPassLepePtAr.append(SMLepLepePtCutPassAr)
        evPassPtLeadAr.append(SMLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(SMLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(SMLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(SMLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(SMLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(SMLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(SMLepLepIsoCutPassAr)
        evPassSIPAr.append(SMLepSIPCutPassAr)

    nameAr.append("SM")
    saveNameAr.append("SM")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(2)
    isSignalAr.append(False)

    XSBackgroundAr.append(SMXS)
    totalBackgroundEvents.append(SMWeightSum)
    
    isQCDAr.append(False)
if MGC2VEtaDifCut:
    if doSL:
        hFatJetPtCutSignalPassAr.append(C2VEtaDifCutSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutSignalPassAr.append(C2VEtaDifCutSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutSignalPassAr.append(C2VEtaDifCutSLVBFJetPtCutPassAr)
        VBFJetdRCutSignalPassAr.append(C2VEtaDifCutSLVBFJetdRCutPassAr)
        VBFJetEtaCutSignalPassAr.append(C2VEtaDifCutSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutSignalPassAr.append(C2VEtaDifCutSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutSignalPassAr.append(C2VEtaDifCutSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutSignalPassAr.append(C2VEtaDifCutSLSemiLepmEtaCutPassAr)
        SemiLepePtCutSignalPassAr.append(C2VEtaDifCutSLSemiLepePtCutPassAr)
        SemiLepeEtaCutSignalPassAr.append(C2VEtaDifCutSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutSignalPassAr.append(C2VEtaDifCutSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutSignalPassAr.append(C2VEtaDifCutSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutSignalPassAr.append(C2VEtaDifCutSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutSignalPassAr.append(C2VEtaDifCutSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutSignalPassAr.append(C2VEtaDifCutSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutSignalPassAr.append(C2VEtaDifCutSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutSignalPassAr.append(C2VEtaDifCutSLLepmPtCutPassAr)
        LepmEtaCutSignalPassAr.append(C2VEtaDifCutSLLepmEtaCutPassAr)
        LepeEtaCutSignalPassAr.append(C2VEtaDifCutSLLepeEtaCutPassAr)
        LepePtCutSignalPassAr.append(C2VEtaDifCutSLLepePtCutPassAr)
        PtLeadCutSignalPassAr.append(C2VEtaDifCutSLPtLeadCutPassAr)
        PtTrailingCutSignalPassAr.append(C2VEtaDifCutSLPtTrailingCutPassAr)
        InvMassCutLowCutSignalPassAr.append(C2VEtaDifCutSLInvMassCutLowCutPassAr)
        InvMassCutHighCutSignalPassAr.append(C2VEtaDifCutSLInvMassCutHighCutPassAr)
        FourLepInvMassCutSignalPassAr.append(C2VEtaDifCutSLFourLepInvMassCutPassAr)
        OptLepInvMassCutSignalPassAr.append(C2VEtaDifCutSLOptLepInvMassCutPassAr)
        LepIsoCutSignalPassAr.append(C2VEtaDifCutSLLepIsoCutPassAr)
        SIPCutSignalPassAr.append(C2VEtaDifCutSLSIPCutPassAr)
        evPasshFatJetPtAr.append(C2VEtaDifCutSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(C2VEtaDifCutSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(C2VEtaDifCutSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(C2VEtaDifCutSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(C2VEtaDifCutSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(C2VEtaDifCutSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(C2VEtaDifCutSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(C2VEtaDifCutSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(C2VEtaDifCutSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(C2VEtaDifCutSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(C2VEtaDifCutSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(C2VEtaDifCutSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(C2VEtaDifCutSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(C2VEtaDifCutSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(C2VEtaDifCutSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(C2VEtaDifCutSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(C2VEtaDifCutSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(C2VEtaDifCutSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(C2VEtaDifCutSLLepeEtaCutPassAr)
        evPassLepePtAr.append(C2VEtaDifCutSLLepePtCutPassAr)
        evPassPtLeadAr.append(C2VEtaDifCutSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(C2VEtaDifCutSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(C2VEtaDifCutSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(C2VEtaDifCutSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(C2VEtaDifCutSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(C2VEtaDifCutSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(C2VEtaDifCutSLLepIsoCutPassAr)
        evPassSIPAr.append(C2VEtaDifCutSLSIPCutPassAr)

    if doLep:
        hFatJetPtCutSignalPassAr.append(C2VEtaDifCutLephFatJetPtCutPassAr)
        hFatJetDeepTagCutSignalPassAr.append(C2VEtaDifCutLephFatJetDeepTagCutPassAr)
        VBFJetPtCutSignalPassAr.append(C2VEtaDifCutLepVBFJetPtCutPassAr)
        VBFJetdRCutSignalPassAr.append(C2VEtaDifCutLepVBFJetdRCutPassAr)
        VBFJetEtaCutSignalPassAr.append(C2VEtaDifCutLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutSignalPassAr.append(C2VEtaDifCutLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutSignalPassAr.append(C2VEtaDifCutLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutSignalPassAr.append(C2VEtaDifCutLepSemiLepmEtaCutPassAr)
        SemiLepePtCutSignalPassAr.append(C2VEtaDifCutLepSemiLepePtCutPassAr)
        SemiLepeEtaCutSignalPassAr.append(C2VEtaDifCutLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutSignalPassAr.append(C2VEtaDifCutLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutSignalPassAr.append(C2VEtaDifCutLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutSignalPassAr.append(C2VEtaDifCutLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutSignalPassAr.append(C2VEtaDifCutLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutSignalPassAr.append(C2VEtaDifCutLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutSignalPassAr.append(C2VEtaDifCutLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutSignalPassAr.append(C2VEtaDifCutLepLepmPtCutPassAr)
        LepmEtaCutSignalPassAr.append(C2VEtaDifCutLepLepmEtaCutPassAr)
        LepeEtaCutSignalPassAr.append(C2VEtaDifCutLepLepeEtaCutPassAr)
        LepePtCutSignalPassAr.append(C2VEtaDifCutLepLepePtCutPassAr)
        PtLeadCutSignalPassAr.append(C2VEtaDifCutLepPtLeadCutPassAr)
        PtTrailingCutSignalPassAr.append(C2VEtaDifCutLepPtTrailingCutPassAr)
        InvMassCutLowCutSignalPassAr.append(C2VEtaDifCutLepInvMassCutLowCutPassAr)
        InvMassCutHighCutSignalPassAr.append(C2VEtaDifCutLepInvMassCutHighCutPassAr)
        FourLepInvMassCutSignalPassAr.append(C2VEtaDifCutLepFourLepInvMassCutPassAr)
        OptLepInvMassCutSignalPassAr.append(C2VEtaDifCutLepOptLepInvMassCutPassAr)
        LepIsoCutSignalPassAr.append(C2VEtaDifCutLepLepIsoCutPassAr)
        SIPCutSignalPassAr.append(C2VEtaDifCutLepSIPCutPassAr)
        evPasshFatJetPtAr.append(C2VEtaDifCutLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(C2VEtaDifCutLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(C2VEtaDifCutLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(C2VEtaDifCutLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(C2VEtaDifCutLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(C2VEtaDifCutLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(C2VEtaDifCutLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(C2VEtaDifCutLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(C2VEtaDifCutLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(C2VEtaDifCutLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(C2VEtaDifCutLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(C2VEtaDifCutLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(C2VEtaDifCutLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(C2VEtaDifCutLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(C2VEtaDifCutLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(C2VEtaDifCutLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(C2VEtaDifCutLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(C2VEtaDifCutLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(C2VEtaDifCutLepLepeEtaCutPassAr)
        evPassLepePtAr.append(C2VEtaDifCutLepLepePtCutPassAr)
        evPassPtLeadAr.append(C2VEtaDifCutLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(C2VEtaDifCutLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(C2VEtaDifCutLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(C2VEtaDifCutLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(C2VEtaDifCutLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(C2VEtaDifCutLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(C2VEtaDifCutLepLepIsoCutPassAr)
        evPassSIPAr.append(C2VEtaDifCutLepSIPCutPassAr)
    nameAr.append("C2VEtaDifCut")
    saveNameAr.append("C2VEtaDifCut")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(6)
    isSignalAr.append(True)
    XSSignalAr.append(C2VEtaDifCutXS)
    #C2VEtaDifCutCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(C2VEtaDifCutLepOrSemiLepCZTree.GetEntries())
    totalSignalEvents.append(C2VEtaDifCutWeightSum)
    
    isQCDAr.append(False)
"""
if MGEFT:
    
    ptCutBackgroundPassAr.append(MGEFTPtCutPassAr)
    deepTagCutBackgroundPassAr.append(MGEFTDeepTagCutPassAr)
    VBFdRCutBackgroundPassAr.append(MGEFTVBFdRCutPassAr)
    VBFPtCutBackgroundPassAr.append(MGEFTVBFPtCutPassAr)
    VBFEtaCutBackgroundPassAr.append(MGEFTVBFEtaCutPassAr)
    VBFInvMassCutBackgroundPassAr.append(MGEFTVBFInvMassCutPassAr)
    nameAr.append("EFT")
    saveNameAr.append("EFT")
    colorAr.append(6)
    #nameAr.append("EFTC0p1")
    isSignalAr.append(True)
    EFTXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for EFTXS in EFTXSTree:
        tmpXSAvg += EFTXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    #tmpXSAvg = tmpXSAvg*0.1 / tmpXSCnt
    XSAr.append(tmpXSAvg)
    #EFTCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(EFTCZTree.GetEntries())
    
    totalEvents.append(evNum)
    isQCDAr.append(False)
"""
if ttHToBBBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ttHToBBSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ttHToBBSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ttHToBBSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ttHToBBSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ttHToBBSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ttHToBBSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ttHToBBSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ttHToBBSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ttHToBBSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ttHToBBSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ttHToBBSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ttHToBBSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ttHToBBSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ttHToBBSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ttHToBBSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ttHToBBSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ttHToBBSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ttHToBBSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ttHToBBSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ttHToBBSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ttHToBBSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ttHToBBSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ttHToBBSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ttHToBBSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ttHToBBSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ttHToBBSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ttHToBBSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ttHToBBSLSIPCutPassAr)

        evPasshFatJetPtAr.append(ttHToBBSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ttHToBBSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ttHToBBSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ttHToBBSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ttHToBBSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ttHToBBSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ttHToBBSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ttHToBBSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ttHToBBSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ttHToBBSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ttHToBBSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ttHToBBSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ttHToBBSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ttHToBBSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ttHToBBSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ttHToBBSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ttHToBBSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ttHToBBSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ttHToBBSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ttHToBBSLLepePtCutPassAr)
        evPassPtLeadAr.append(ttHToBBSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ttHToBBSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ttHToBBSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ttHToBBSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ttHToBBSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ttHToBBSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ttHToBBSLLepIsoCutPassAr)
        evPassSIPAr.append(ttHToBBSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ttHToBBLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ttHToBBLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ttHToBBLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ttHToBBLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ttHToBBLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ttHToBBLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ttHToBBLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ttHToBBLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ttHToBBLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ttHToBBLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ttHToBBLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ttHToBBLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ttHToBBLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ttHToBBLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ttHToBBLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ttHToBBLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ttHToBBLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ttHToBBLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ttHToBBLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ttHToBBLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ttHToBBLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ttHToBBLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ttHToBBLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ttHToBBLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ttHToBBLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ttHToBBLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ttHToBBLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ttHToBBLepSIPCutPassAr)

        evPasshFatJetPtAr.append(ttHToBBLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ttHToBBLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ttHToBBLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ttHToBBLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ttHToBBLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ttHToBBLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ttHToBBLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ttHToBBLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ttHToBBLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ttHToBBLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ttHToBBLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ttHToBBLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ttHToBBLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ttHToBBLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ttHToBBLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ttHToBBLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ttHToBBLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ttHToBBLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ttHToBBLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ttHToBBLepLepePtCutPassAr)
        evPassPtLeadAr.append(ttHToBBLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ttHToBBLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ttHToBBLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ttHToBBLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ttHToBBLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ttHToBBLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ttHToBBLepLepIsoCutPassAr)
        evPassSIPAr.append(ttHToBBLepSIPCutPassAr)
    
    nameAr.append("ttHToBBBackground")
    saveNameAr.append("ttHToBB")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(7)
    isSignalAr.append(False)
    tmpXSAvg = 0.5071*0.582
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ttHToBBWeightSum)
    
    isQCDAr.append(False)
if ttZJetsBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ttZJetsSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ttZJetsSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ttZJetsSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ttZJetsSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ttZJetsSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ttZJetsSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ttZJetsSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ttZJetsSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ttZJetsSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ttZJetsSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ttZJetsSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ttZJetsSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ttZJetsSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ttZJetsSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ttZJetsSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ttZJetsSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ttZJetsSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ttZJetsSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ttZJetsSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ttZJetsSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ttZJetsSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ttZJetsSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ttZJetsSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ttZJetsSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ttZJetsSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ttZJetsSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ttZJetsSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ttZJetsSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ttZJetsSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ttZJetsSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ttZJetsSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ttZJetsSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ttZJetsSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ttZJetsSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ttZJetsSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ttZJetsSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ttZJetsSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ttZJetsSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ttZJetsSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ttZJetsSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ttZJetsSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ttZJetsSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ttZJetsSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ttZJetsSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ttZJetsSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ttZJetsSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ttZJetsSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ttZJetsSLLepePtCutPassAr)
        evPassPtLeadAr.append(ttZJetsSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ttZJetsSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ttZJetsSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ttZJetsSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ttZJetsSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ttZJetsSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ttZJetsSLLepIsoCutPassAr)
        evPassSIPAr.append(ttZJetsSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ttZJetsLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ttZJetsLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ttZJetsLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ttZJetsLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ttZJetsLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ttZJetsLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ttZJetsLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ttZJetsLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ttZJetsLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ttZJetsLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ttZJetsLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ttZJetsLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ttZJetsLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ttZJetsLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ttZJetsLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ttZJetsLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ttZJetsLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ttZJetsLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ttZJetsLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ttZJetsLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ttZJetsLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ttZJetsLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ttZJetsLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ttZJetsLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ttZJetsLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ttZJetsLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ttZJetsLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ttZJetsLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ttZJetsLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ttZJetsLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ttZJetsLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ttZJetsLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ttZJetsLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ttZJetsLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ttZJetsLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ttZJetsLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ttZJetsLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ttZJetsLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ttZJetsLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ttZJetsLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ttZJetsLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ttZJetsLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ttZJetsLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ttZJetsLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ttZJetsLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ttZJetsLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ttZJetsLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ttZJetsLepLepePtCutPassAr)
        evPassPtLeadAr.append(ttZJetsLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ttZJetsLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ttZJetsLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ttZJetsLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ttZJetsLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ttZJetsLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ttZJetsLepLepIsoCutPassAr)
        evPassSIPAr.append(ttZJetsLepSIPCutPassAr)


    nameAr.append("ttZJetsBackground")
    saveNameAr.append("ttZJets")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 0.5407
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ttZJetsWeightSum)
    
    isQCDAr.append(False)


if DYBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(DYSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(DYSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(DYSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(DYSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(DYSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(DYSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(DYSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(DYSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(DYSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(DYSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(DYSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(DYSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(DYSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(DYSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(DYSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(DYSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(DYSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(DYSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(DYSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(DYSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(DYSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(DYSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(DYSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(DYSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(DYSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(DYSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(DYSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(DYSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(DYSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(DYSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(DYSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(DYSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(DYSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(DYSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(DYSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(DYSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(DYSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(DYSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(DYSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(DYSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(DYSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(DYSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(DYSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(DYSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(DYSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(DYSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(DYSLLepeEtaCutPassAr)
        evPassLepePtAr.append(DYSLLepePtCutPassAr)
        evPassPtLeadAr.append(DYSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(DYSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(DYSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(DYSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(DYSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(DYSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(DYSLLepIsoCutPassAr)
        evPassSIPAr.append(DYSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(DYLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(DYLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(DYLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(DYLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(DYLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(DYLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(DYLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(DYLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(DYLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(DYLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(DYLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(DYLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(DYLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(DYLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(DYLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(DYLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(DYLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(DYLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(DYLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(DYLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(DYLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(DYLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(DYLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(DYLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(DYLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(DYLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(DYLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(DYLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(DYLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(DYLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(DYLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(DYLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(DYLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(DYLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(DYLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(DYLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(DYLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(DYLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(DYLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(DYLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(DYLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(DYLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(DYLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(DYLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(DYLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(DYLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(DYLepLepeEtaCutPassAr)
        evPassLepePtAr.append(DYLepLepePtCutPassAr)
        evPassPtLeadAr.append(DYLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(DYLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(DYLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(DYLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(DYLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(DYLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(DYLepLepIsoCutPassAr)
        evPassSIPAr.append(DYLepSIPCutPassAr)


    nameAr.append("DYBackground")
    saveNameAr.append("DY")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(8)
    isSignalAr.append(False)
    tmpXSAvg = 5364
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(DYWeightSum)
    
    isQCDAr.append(False)


if QCDPT170to300Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT170to300SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT170to300SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT170to300SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT170to300SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT170to300SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT170to300SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT170to300SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT170to300SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT170to300SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT170to300SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT170to300SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT170to300SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT170to300SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT170to300SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT170to300SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT170to300SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT170to300SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT170to300SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT170to300SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT170to300SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT170to300SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT170to300SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT170to300SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT170to300SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT170to300SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT170to300SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT170to300SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT170to300SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT170to300SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT170to300SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT170to300SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT170to300SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT170to300SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT170to300SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT170to300SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT170to300SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT170to300SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT170to300SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT170to300SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT170to300SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT170to300SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT170to300SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT170to300SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT170to300SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT170to300SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT170to300SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT170to300SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT170to300SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT170to300SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT170to300SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT170to300SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT170to300SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT170to300SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT170to300SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT170to300SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT170to300SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT170to300LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT170to300LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT170to300LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT170to300LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT170to300LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT170to300LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT170to300LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT170to300LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT170to300LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT170to300LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT170to300LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT170to300LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT170to300LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT170to300LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT170to300LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT170to300LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT170to300LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT170to300LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT170to300LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT170to300LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT170to300LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT170to300LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT170to300LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT170to300LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT170to300LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT170to300LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT170to300LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT170to300LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT170to300LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT170to300LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT170to300LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT170to300LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT170to300LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT170to300LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT170to300LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT170to300LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT170to300LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT170to300LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT170to300LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT170to300LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT170to300LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT170to300LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT170to300LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT170to300LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT170to300LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT170to300LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT170to300LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT170to300LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT170to300LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT170to300LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT170to300LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT170to300LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT170to300LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT170to300LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT170to300LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT170to300LepSIPCutPassAr)


    nameAr.append("QCDPT170to300Background")
    altNameAr.append("QCDPT170to300")
    saveNameAr.append("QCD0")
    isSignalAr.append(False)
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    colorAr.append(1)
    tmpXSAvg = 103300.0
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT170to300WeightSum)
    
    isQCDAr.append(True)
if QCDPT300to470Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT300to470SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT300to470SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT300to470SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT300to470SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT300to470SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT300to470SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT300to470SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT300to470SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT300to470SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT300to470SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT300to470SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT300to470SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT300to470SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT300to470SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT300to470SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT300to470SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT300to470SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT300to470SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT300to470SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT300to470SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT300to470SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT300to470SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT300to470SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT300to470SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT300to470SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT300to470SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT300to470SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT300to470SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT300to470SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT300to470SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT300to470SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT300to470SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT300to470SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT300to470SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT300to470SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT300to470SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT300to470SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT300to470SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT300to470SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT300to470SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT300to470SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT300to470SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT300to470SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT300to470SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT300to470SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT300to470SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT300to470SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT300to470SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT300to470SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT300to470SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT300to470SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT300to470SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT300to470SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT300to470SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT300to470SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT300to470SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT300to470LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT300to470LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT300to470LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT300to470LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT300to470LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT300to470LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT300to470LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT300to470LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT300to470LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT300to470LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT300to470LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT300to470LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT300to470LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT300to470LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT300to470LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT300to470LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT300to470LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT300to470LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT300to470LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT300to470LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT300to470LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT300to470LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT300to470LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT300to470LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT300to470LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT300to470LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT300to470LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT300to470LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT300to470LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT300to470LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT300to470LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT300to470LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT300to470LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT300to470LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT300to470LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT300to470LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT300to470LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT300to470LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT300to470LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT300to470LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT300to470LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT300to470LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT300to470LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT300to470LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT300to470LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT300to470LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT300to470LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT300to470LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT300to470LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT300to470LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT300to470LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT300to470LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT300to470LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT300to470LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT300to470LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT300to470LepSIPCutPassAr)


    nameAr.append("QCDPT300to470Background")
    altNameAr.append("QCDPT300to470")
    saveNameAr.append("QCD1")
    isSignalAr.append(False)
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    colorAr.append(8)
    tmpXSAvg = 6826.0
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT300to470WeightSum)
    
    isQCDAr.append(True)
if QCDPT470to600Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT470to600SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT470to600SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT470to600SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT470to600SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT470to600SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT470to600SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT470to600SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT470to600SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT470to600SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT470to600SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT470to600SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT470to600SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT470to600SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT470to600SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT470to600SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT470to600SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT470to600SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT470to600SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT470to600SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT470to600SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT470to600SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT470to600SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT470to600SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT470to600SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT470to600SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT470to600SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT470to600SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT470to600SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT470to600SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT470to600SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT470to600SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT470to600SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT470to600SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT470to600SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT470to600SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT470to600SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT470to600SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT470to600SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT470to600SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT470to600SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT470to600SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT470to600SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT470to600SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT470to600SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT470to600SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT470to600SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT470to600SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT470to600SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT470to600SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT470to600SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT470to600SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT470to600SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT470to600SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT470to600SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT470to600SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT470to600SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT470to600LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT470to600LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT470to600LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT470to600LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT470to600LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT470to600LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT470to600LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT470to600LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT470to600LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT470to600LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT470to600LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT470to600LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT470to600LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT470to600LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT470to600LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT470to600LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT470to600LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT470to600LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT470to600LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT470to600LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT470to600LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT470to600LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT470to600LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT470to600LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT470to600LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT470to600LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT470to600LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT470to600LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT470to600LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT470to600LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT470to600LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT470to600LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT470to600LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT470to600LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT470to600LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT470to600LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT470to600LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT470to600LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT470to600LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT470to600LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT470to600LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT470to600LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT470to600LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT470to600LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT470to600LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT470to600LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT470to600LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT470to600LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT470to600LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT470to600LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT470to600LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT470to600LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT470to600LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT470to600LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT470to600LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT470to600LepSIPCutPassAr)


    nameAr.append("QCDPT470to600Background")
    altNameAr.append("QCDPT470to600")
    saveNameAr.append("QCD2")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    colorAr.append(9)
    isSignalAr.append(False)
    
    tmpXSAvg = 552.6
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT470to600WeightSum)
    
    isQCDAr.append(True)
if QCDPT600to800Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT600to800SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT600to800SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT600to800SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT600to800SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT600to800SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT600to800SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT600to800SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT600to800SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT600to800SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT600to800SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT600to800SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT600to800SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT600to800SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT600to800SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT600to800SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT600to800SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT600to800SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT600to800SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT600to800SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT600to800SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT600to800SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT600to800SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT600to800SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT600to800SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT600to800SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT600to800SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT600to800SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT600to800SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT600to800SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT600to800SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT600to800SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT600to800SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT600to800SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT600to800SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT600to800SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT600to800SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT600to800SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT600to800SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT600to800SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT600to800SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT600to800SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT600to800SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT600to800SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT600to800SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT600to800SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT600to800SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT600to800SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT600to800SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT600to800SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT600to800SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT600to800SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT600to800SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT600to800SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT600to800SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT600to800SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT600to800SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT600to800LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT600to800LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT600to800LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT600to800LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT600to800LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT600to800LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT600to800LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT600to800LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT600to800LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT600to800LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT600to800LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT600to800LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT600to800LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT600to800LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT600to800LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT600to800LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT600to800LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT600to800LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT600to800LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT600to800LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT600to800LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT600to800LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT600to800LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT600to800LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT600to800LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT600to800LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT600to800LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT600to800LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT600to800LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT600to800LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT600to800LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT600to800LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT600to800LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT600to800LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT600to800LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT600to800LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT600to800LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT600to800LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT600to800LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT600to800LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT600to800LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT600to800LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT600to800LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT600to800LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT600to800LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT600to800LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT600to800LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT600to800LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT600to800LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT600to800LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT600to800LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT600to800LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT600to800LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT600to800LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT600to800LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT600to800LepSIPCutPassAr)


    nameAr.append("QCDPT600to800Background")
    altNameAr.append("QCDPT600to800")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD3")
    
    colorAr.append(10)
    isSignalAr.append(False)
    tmpXSAvg = 156.6
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT600to800WeightSum)
    
    isQCDAr.append(True)
if QCDPT800to1000Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT800to1000SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT800to1000SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT800to1000SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT800to1000SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT800to1000SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT800to1000SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT800to1000SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT800to1000SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT800to1000SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT800to1000SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT800to1000SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT800to1000SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT800to1000SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT800to1000SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT800to1000SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT800to1000SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT800to1000SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT800to1000SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT800to1000SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT800to1000SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT800to1000SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT800to1000SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT800to1000SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT800to1000SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT800to1000SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT800to1000SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT800to1000SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT800to1000SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT800to1000SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT800to1000SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT800to1000SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT800to1000SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT800to1000SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT800to1000SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT800to1000SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT800to1000SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT800to1000SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT800to1000SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT800to1000SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT800to1000SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT800to1000SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT800to1000SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT800to1000SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT800to1000SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT800to1000SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT800to1000SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT800to1000SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT800to1000LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT800to1000LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT800to1000LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT800to1000LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT800to1000LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT800to1000LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT800to1000LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT800to1000LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT800to1000LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT800to1000LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT800to1000LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT800to1000LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT800to1000LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT800to1000LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT800to1000LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT800to1000LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT800to1000LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT800to1000LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT800to1000LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT800to1000LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT800to1000LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT800to1000LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT800to1000LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT800to1000LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT800to1000LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT800to1000LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT800to1000LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT800to1000LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT800to1000LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT800to1000LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT800to1000LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT800to1000LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT800to1000LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT800to1000LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT800to1000LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT800to1000LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT800to1000LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT800to1000LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT800to1000LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT800to1000LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT800to1000LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT800to1000LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT800to1000LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT800to1000LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT800to1000LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT800to1000LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT800to1000LepSIPCutPassAr)


    nameAr.append("QCDPT800to1000Background")
    altNameAr.append("QCDPT800to1000")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD4")
    colorAr.append(11)
    isSignalAr.append(False)
    tmpXSAvg = 26.32
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT800to1000WeightSum)
    
    isQCDAr.append(True)
if QCDPT1000to1400Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1000to1400SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1000to1400SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1000to1400SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1000to1400SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1000to1400SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1000to1400SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1000to1400SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1000to1400SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1000to1400SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1000to1400SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1000to1400SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1000to1400SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1000to1400SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1000to1400SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1000to1400SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1000to1400SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1000to1400SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1000to1400SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1000to1400SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1000to1400SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1000to1400SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1000to1400SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1000to1400SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1000to1400SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1000to1400SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1000to1400SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1000to1400SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1000to1400SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1000to1400SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1000to1400SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1000to1400SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1000to1400SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1000to1400SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1000to1400SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1000to1400SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1000to1400SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1000to1400SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1000to1400SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1000to1400SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1000to1400SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1000to1400SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1000to1400SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1000to1400SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1000to1400SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1000to1400SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1000to1400SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1000to1400SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1000to1400LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1000to1400LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1000to1400LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1000to1400LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1000to1400LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1000to1400LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1000to1400LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1000to1400LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1000to1400LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1000to1400LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1000to1400LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1000to1400LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1000to1400LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1000to1400LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1000to1400LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1000to1400LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1000to1400LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1000to1400LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1000to1400LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1000to1400LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1000to1400LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1000to1400LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1000to1400LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1000to1400LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1000to1400LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1000to1400LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1000to1400LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1000to1400LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1000to1400LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1000to1400LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1000to1400LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1000to1400LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1000to1400LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1000to1400LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1000to1400LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1000to1400LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1000to1400LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1000to1400LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1000to1400LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1000to1400LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1000to1400LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1000to1400LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1000to1400LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1000to1400LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1000to1400LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1000to1400LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1000to1400LepSIPCutPassAr)


    nameAr.append("QCDPT1000to1400Background")
    altNameAr.append("QCDPT1000to1400")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD5")
    colorAr.append(12)
    isSignalAr.append(False)
    tmpXSAvg = 7.5
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT1000to1400WeightSum)
    
    isQCDAr.append(True)
if QCDPT1400to1800Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1400to1800SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1400to1800SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1400to1800SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1400to1800SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1400to1800SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1400to1800SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1400to1800SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1400to1800SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1400to1800SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1400to1800SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1400to1800SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1400to1800SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1400to1800SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1400to1800SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1400to1800SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1400to1800SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1400to1800SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1400to1800SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1400to1800SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1400to1800SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1400to1800SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1400to1800SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1400to1800SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1400to1800SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1400to1800SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1400to1800SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1400to1800SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1400to1800SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1400to1800SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1400to1800SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1400to1800SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1400to1800SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1400to1800SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1400to1800SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1400to1800SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1400to1800SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1400to1800SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1400to1800SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1400to1800SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1400to1800SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1400to1800SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1400to1800SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1400to1800SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1400to1800SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1400to1800SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1400to1800SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1400to1800SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1400to1800LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1400to1800LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1400to1800LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1400to1800LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1400to1800LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1400to1800LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1400to1800LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1400to1800LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1400to1800LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1400to1800LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1400to1800LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1400to1800LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1400to1800LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1400to1800LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1400to1800LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1400to1800LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1400to1800LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1400to1800LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1400to1800LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1400to1800LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1400to1800LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1400to1800LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1400to1800LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1400to1800LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1400to1800LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1400to1800LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1400to1800LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1400to1800LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1400to1800LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1400to1800LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1400to1800LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1400to1800LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1400to1800LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1400to1800LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1400to1800LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1400to1800LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1400to1800LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1400to1800LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1400to1800LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1400to1800LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1400to1800LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1400to1800LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1400to1800LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1400to1800LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1400to1800LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1400to1800LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1400to1800LepSIPCutPassAr)


    nameAr.append("QCDPT1400to1800Background")
    altNameAr.append("QCDPT1400to1800")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD6")
    isSignalAr.append(False)
    colorAr.append(13)
    tmpXSAvg = 0.6479
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT1400to1800WeightSum)
    
    isQCDAr.append(True)
if QCDPT1800to2400Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1800to2400SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1800to2400SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1800to2400SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1800to2400SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1800to2400SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1800to2400SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1800to2400SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1800to2400SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1800to2400SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1800to2400SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1800to2400SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1800to2400SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1800to2400SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1800to2400SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1800to2400SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1800to2400SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1800to2400SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1800to2400SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1800to2400SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1800to2400SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1800to2400SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1800to2400SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1800to2400SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1800to2400SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1800to2400SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1800to2400SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1800to2400SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1800to2400SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1800to2400SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1800to2400SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1800to2400SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1800to2400SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1800to2400SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1800to2400SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1800to2400SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1800to2400SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1800to2400SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1800to2400SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1800to2400SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1800to2400SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1800to2400SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1800to2400SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1800to2400SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1800to2400SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1800to2400SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1800to2400SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1800to2400SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT1800to2400LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT1800to2400LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT1800to2400LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT1800to2400LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT1800to2400LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT1800to2400LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT1800to2400LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT1800to2400LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT1800to2400LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT1800to2400LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT1800to2400LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT1800to2400LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT1800to2400LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT1800to2400LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT1800to2400LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT1800to2400LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT1800to2400LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT1800to2400LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT1800to2400LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT1800to2400LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT1800to2400LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT1800to2400LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT1800to2400LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT1800to2400LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT1800to2400LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT1800to2400LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT1800to2400LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT1800to2400LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT1800to2400LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT1800to2400LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT1800to2400LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT1800to2400LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT1800to2400LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT1800to2400LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT1800to2400LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT1800to2400LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT1800to2400LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT1800to2400LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT1800to2400LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT1800to2400LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT1800to2400LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT1800to2400LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT1800to2400LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT1800to2400LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT1800to2400LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT1800to2400LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT1800to2400LepSIPCutPassAr)


    nameAr.append("QCDPT1800to2400Background")
    altNameAr.append("QCDPT1800to2400")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD7")
    isSignalAr.append(False)
    colorAr.append(14)
    tmpXSAvg = 0.08715
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT1800to2400WeightSum)
    
    isQCDAr.append(True)
if QCDPT2400to3200Background:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT2400to3200SLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT2400to3200SLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT2400to3200SLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT2400to3200SLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT2400to3200SLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT2400to3200SLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT2400to3200SLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT2400to3200SLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT2400to3200SLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT2400to3200SLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT2400to3200SLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT2400to3200SLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT2400to3200SLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT2400to3200SLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT2400to3200SLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT2400to3200SLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT2400to3200SLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT2400to3200SLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT2400to3200SLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT2400to3200SLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT2400to3200SLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT2400to3200SLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT2400to3200SLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT2400to3200SLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT2400to3200SLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT2400to3200SLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT2400to3200SLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT2400to3200SLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT2400to3200SLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT2400to3200SLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT2400to3200SLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT2400to3200SLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT2400to3200SLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT2400to3200SLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT2400to3200SLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT2400to3200SLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT2400to3200SLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT2400to3200SLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT2400to3200SLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT2400to3200SLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT2400to3200SLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT2400to3200SLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT2400to3200SLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT2400to3200SLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT2400to3200SLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT2400to3200SLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT2400to3200SLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT2400to3200LephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT2400to3200LephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT2400to3200LepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT2400to3200LepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT2400to3200LepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT2400to3200LepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT2400to3200LepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT2400to3200LepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT2400to3200LepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT2400to3200LepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT2400to3200LepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT2400to3200LepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT2400to3200LepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT2400to3200LepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT2400to3200LepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT2400to3200LepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT2400to3200LepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT2400to3200LepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT2400to3200LepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT2400to3200LephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT2400to3200LephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT2400to3200LepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT2400to3200LepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT2400to3200LepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT2400to3200LepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT2400to3200LepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT2400to3200LepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT2400to3200LepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT2400to3200LepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT2400to3200LepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT2400to3200LepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT2400to3200LepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT2400to3200LepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT2400to3200LepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT2400to3200LepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT2400to3200LepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT2400to3200LepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT2400to3200LepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT2400to3200LepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT2400to3200LepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT2400to3200LepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT2400to3200LepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT2400to3200LepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT2400to3200LepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT2400to3200LepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT2400to3200LepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT2400to3200LepSIPCutPassAr)


    nameAr.append("QCDPT2400to3200Background")
    altNameAr.append("QCDPT2400to3200")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD8")
    isSignalAr.append(False)
    colorAr.append(15)
    tmpXSAvg = 0.005242
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT2400to3200WeightSum)
    
    isQCDAr.append(True)
if QCDPT3200toInfBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(QCDPT3200toInfSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT3200toInfSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT3200toInfSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT3200toInfSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT3200toInfSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT3200toInfSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT3200toInfSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT3200toInfSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT3200toInfSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT3200toInfSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT3200toInfSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT3200toInfSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT3200toInfSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT3200toInfSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT3200toInfSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT3200toInfSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT3200toInfSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT3200toInfSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT3200toInfSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT3200toInfSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT3200toInfSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT3200toInfSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT3200toInfSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT3200toInfSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT3200toInfSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT3200toInfSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT3200toInfSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT3200toInfSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT3200toInfSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT3200toInfSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT3200toInfSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT3200toInfSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT3200toInfSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT3200toInfSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT3200toInfSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT3200toInfSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT3200toInfSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT3200toInfSLLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT3200toInfSLLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT3200toInfSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT3200toInfSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT3200toInfSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT3200toInfSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT3200toInfSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT3200toInfSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT3200toInfSLLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT3200toInfSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(QCDPT3200toInfLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(QCDPT3200toInfLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(QCDPT3200toInfLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(QCDPT3200toInfLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(QCDPT3200toInfLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(QCDPT3200toInfLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(QCDPT3200toInfLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(QCDPT3200toInfLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(QCDPT3200toInfLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(QCDPT3200toInfLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(QCDPT3200toInfLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(QCDPT3200toInfLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(QCDPT3200toInfLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(QCDPT3200toInfLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(QCDPT3200toInfLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(QCDPT3200toInfLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(QCDPT3200toInfLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(QCDPT3200toInfLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(QCDPT3200toInfLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(QCDPT3200toInfLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(QCDPT3200toInfLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(QCDPT3200toInfLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(QCDPT3200toInfLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(QCDPT3200toInfLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(QCDPT3200toInfLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(QCDPT3200toInfLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(QCDPT3200toInfLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(QCDPT3200toInfLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(QCDPT3200toInfLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(QCDPT3200toInfLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(QCDPT3200toInfLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(QCDPT3200toInfLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(QCDPT3200toInfLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(QCDPT3200toInfLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(QCDPT3200toInfLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(QCDPT3200toInfLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(QCDPT3200toInfLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(QCDPT3200toInfLepLepeEtaCutPassAr)
        evPassLepePtAr.append(QCDPT3200toInfLepLepePtCutPassAr)
        evPassPtLeadAr.append(QCDPT3200toInfLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(QCDPT3200toInfLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(QCDPT3200toInfLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(QCDPT3200toInfLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(QCDPT3200toInfLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(QCDPT3200toInfLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(QCDPT3200toInfLepLepIsoCutPassAr)
        evPassSIPAr.append(QCDPT3200toInfLepSIPCutPassAr)


    nameAr.append("QCDPT3200toInfBackground")
    altNameAr.append("QCDPT3200toInf")
    fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,altNameAr[-1])))
    saveNameAr.append("QCD9")
    isSignalAr.append(False)
    colorAr.append(16)
    tmpXSAvg = 0.0001349
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(QCDPT3200toInfWeightSum)
    
    isQCDAr.append(True)

if TTJetsBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(TTJetsSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(TTJetsSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(TTJetsSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(TTJetsSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(TTJetsSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(TTJetsSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(TTJetsSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(TTJetsSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(TTJetsSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(TTJetsSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(TTJetsSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(TTJetsSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(TTJetsSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(TTJetsSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(TTJetsSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(TTJetsSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(TTJetsSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(TTJetsSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(TTJetsSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(TTJetsSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(TTJetsSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(TTJetsSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(TTJetsSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(TTJetsSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(TTJetsSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(TTJetsSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(TTJetsSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(TTJetsSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(TTJetsSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(TTJetsSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(TTJetsSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(TTJetsSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(TTJetsSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(TTJetsSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(TTJetsSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(TTJetsSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(TTJetsSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(TTJetsSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(TTJetsSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(TTJetsSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(TTJetsSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(TTJetsSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(TTJetsSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(TTJetsSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(TTJetsSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(TTJetsSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(TTJetsSLLepeEtaCutPassAr)
        evPassLepePtAr.append(TTJetsSLLepePtCutPassAr)
        evPassPtLeadAr.append(TTJetsSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(TTJetsSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(TTJetsSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(TTJetsSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(TTJetsSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(TTJetsSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(TTJetsSLLepIsoCutPassAr)
        evPassSIPAr.append(TTJetsSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(TTJetsLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(TTJetsLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(TTJetsLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(TTJetsLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(TTJetsLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(TTJetsLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(TTJetsLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(TTJetsLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(TTJetsLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(TTJetsLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(TTJetsLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(TTJetsLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(TTJetsLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(TTJetsLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(TTJetsLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(TTJetsLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(TTJetsLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(TTJetsLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(TTJetsLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(TTJetsLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(TTJetsLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(TTJetsLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(TTJetsLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(TTJetsLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(TTJetsLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(TTJetsLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(TTJetsLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(TTJetsLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(TTJetsLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(TTJetsLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(TTJetsLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(TTJetsLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(TTJetsLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(TTJetsLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(TTJetsLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(TTJetsLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(TTJetsLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(TTJetsLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(TTJetsLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(TTJetsLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(TTJetsLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(TTJetsLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(TTJetsLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(TTJetsLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(TTJetsLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(TTJetsLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(TTJetsLepLepeEtaCutPassAr)
        evPassLepePtAr.append(TTJetsLepLepePtCutPassAr)
        evPassPtLeadAr.append(TTJetsLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(TTJetsLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(TTJetsLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(TTJetsLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(TTJetsLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(TTJetsLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(TTJetsLepLepIsoCutPassAr)
        evPassSIPAr.append(TTJetsLepSIPCutPassAr)


    nameAr.append("TTJetsBackground")
    
    saveNameAr.append("TTJets")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 722.8
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(TTJetsWeightSum)
    
    isQCDAr.append(False)
if ST_s_ChannelBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ST_s_ChannelSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_s_ChannelSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_s_ChannelSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_s_ChannelSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_s_ChannelSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_s_ChannelSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_s_ChannelSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_s_ChannelSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_s_ChannelSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_s_ChannelSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_s_ChannelSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_s_ChannelSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_s_ChannelSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_s_ChannelSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_s_ChannelSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_s_ChannelSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_s_ChannelSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_s_ChannelSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_s_ChannelSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_s_ChannelSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_s_ChannelSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_s_ChannelSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_s_ChannelSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_s_ChannelSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_s_ChannelSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_s_ChannelSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_s_ChannelSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_s_ChannelSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_s_ChannelSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_s_ChannelSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_s_ChannelSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_s_ChannelSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_s_ChannelSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_s_ChannelSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_s_ChannelSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_s_ChannelSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_s_ChannelSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_s_ChannelSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_s_ChannelSLLepePtCutPassAr)
        evPassPtLeadAr.append(ST_s_ChannelSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_s_ChannelSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_s_ChannelSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_s_ChannelSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_s_ChannelSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_s_ChannelSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_s_ChannelSLLepIsoCutPassAr)
        evPassSIPAr.append(ST_s_ChannelSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ST_s_ChannelLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_s_ChannelLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_s_ChannelLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_s_ChannelLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_s_ChannelLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_s_ChannelLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_s_ChannelLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_s_ChannelLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_s_ChannelLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_s_ChannelLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_s_ChannelLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_s_ChannelLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_s_ChannelLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_s_ChannelLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_s_ChannelLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_s_ChannelLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_s_ChannelLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_s_ChannelLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_s_ChannelLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_s_ChannelLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_s_ChannelLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_s_ChannelLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_s_ChannelLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_s_ChannelLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_s_ChannelLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_s_ChannelLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_s_ChannelLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_s_ChannelLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_s_ChannelLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_s_ChannelLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_s_ChannelLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_s_ChannelLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_s_ChannelLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_s_ChannelLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_s_ChannelLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_s_ChannelLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_s_ChannelLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_s_ChannelLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_s_ChannelLepLepePtCutPassAr)
        evPassPtLeadAr.append(ST_s_ChannelLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_s_ChannelLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_s_ChannelLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_s_ChannelLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_s_ChannelLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_s_ChannelLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_s_ChannelLepLepIsoCutPassAr)
        evPassSIPAr.append(ST_s_ChannelLepSIPCutPassAr)


    nameAr.append("ST_s_ChannelBackground")
    saveNameAr.append("ST_s_Channel")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 3.74
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ST_s_ChannelWeightSum)
    
    isQCDAr.append(False)
if ST_t_ChannelAntiTopBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_t_ChannelAntiTopSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_t_ChannelAntiTopSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_t_ChannelAntiTopSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_t_ChannelAntiTopSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_t_ChannelAntiTopSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_t_ChannelAntiTopSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_t_ChannelAntiTopSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_t_ChannelAntiTopSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_t_ChannelAntiTopSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_t_ChannelAntiTopSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_t_ChannelAntiTopSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_t_ChannelAntiTopSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_t_ChannelAntiTopSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_t_ChannelAntiTopSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_t_ChannelAntiTopSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_t_ChannelAntiTopSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_t_ChannelAntiTopSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_t_ChannelAntiTopSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_t_ChannelAntiTopSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_t_ChannelAntiTopSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_t_ChannelAntiTopSLLepePtCutPassAr)
        evPassPtLeadAr.append(ST_t_ChannelAntiTopSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_t_ChannelAntiTopSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_t_ChannelAntiTopSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_t_ChannelAntiTopSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_t_ChannelAntiTopSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_t_ChannelAntiTopSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_t_ChannelAntiTopSLLepIsoCutPassAr)
        evPassSIPAr.append(ST_t_ChannelAntiTopSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_t_ChannelAntiTopLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_t_ChannelAntiTopLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_t_ChannelAntiTopLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_t_ChannelAntiTopLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_t_ChannelAntiTopLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_t_ChannelAntiTopLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_t_ChannelAntiTopLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_t_ChannelAntiTopLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_t_ChannelAntiTopLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_t_ChannelAntiTopLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_t_ChannelAntiTopLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_t_ChannelAntiTopLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_t_ChannelAntiTopLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_t_ChannelAntiTopLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_t_ChannelAntiTopLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_t_ChannelAntiTopLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_t_ChannelAntiTopLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_t_ChannelAntiTopLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_t_ChannelAntiTopLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_t_ChannelAntiTopLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_t_ChannelAntiTopLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_t_ChannelAntiTopLepLepePtCutPassAr)
        evPassPtLeadAr.append(ST_t_ChannelAntiTopLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_t_ChannelAntiTopLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_t_ChannelAntiTopLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_t_ChannelAntiTopLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_t_ChannelAntiTopLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_t_ChannelAntiTopLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_t_ChannelAntiTopLepLepIsoCutPassAr)
        evPassSIPAr.append(ST_t_ChannelAntiTopLepSIPCutPassAr)


    nameAr.append("ST_t_ChannelAntiTopBackground")
    saveNameAr.append("ST_t_ChannelAntiTop")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 69.09
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ST_t_ChannelAntiTopWeightSum)
    
    isQCDAr.append(False)
if ST_t_ChannelTopBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ST_t_ChannelTopSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_t_ChannelTopSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_t_ChannelTopSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_t_ChannelTopSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_t_ChannelTopSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_t_ChannelTopSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_t_ChannelTopSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_t_ChannelTopSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_t_ChannelTopSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_t_ChannelTopSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_t_ChannelTopSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_t_ChannelTopSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_t_ChannelTopSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelTopSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelTopSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_t_ChannelTopSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_t_ChannelTopSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_t_ChannelTopSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_t_ChannelTopSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_t_ChannelTopSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_t_ChannelTopSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_t_ChannelTopSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_t_ChannelTopSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_t_ChannelTopSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_t_ChannelTopSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_t_ChannelTopSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_t_ChannelTopSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_t_ChannelTopSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_t_ChannelTopSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_t_ChannelTopSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_t_ChannelTopSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_t_ChannelTopSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_t_ChannelTopSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_t_ChannelTopSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_t_ChannelTopSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_t_ChannelTopSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_t_ChannelTopSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_t_ChannelTopSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_t_ChannelTopSLLepePtCutPassAr)
        evPassPtLeadAr.append(ST_t_ChannelTopSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_t_ChannelTopSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_t_ChannelTopSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_t_ChannelTopSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_t_ChannelTopSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_t_ChannelTopSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_t_ChannelTopSLLepIsoCutPassAr)
        evPassSIPAr.append(ST_t_ChannelTopSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ST_t_ChannelTopLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ST_t_ChannelTopLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ST_t_ChannelTopLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ST_t_ChannelTopLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ST_t_ChannelTopLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ST_t_ChannelTopLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ST_t_ChannelTopLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ST_t_ChannelTopLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ST_t_ChannelTopLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ST_t_ChannelTopLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ST_t_ChannelTopLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ST_t_ChannelTopLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ST_t_ChannelTopLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ST_t_ChannelTopLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ST_t_ChannelTopLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ST_t_ChannelTopLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ST_t_ChannelTopLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ST_t_ChannelTopLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ST_t_ChannelTopLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ST_t_ChannelTopLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ST_t_ChannelTopLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ST_t_ChannelTopLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ST_t_ChannelTopLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ST_t_ChannelTopLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ST_t_ChannelTopLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ST_t_ChannelTopLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ST_t_ChannelTopLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ST_t_ChannelTopLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ST_t_ChannelTopLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ST_t_ChannelTopLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ST_t_ChannelTopLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ST_t_ChannelTopLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ST_t_ChannelTopLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ST_t_ChannelTopLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ST_t_ChannelTopLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ST_t_ChannelTopLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ST_t_ChannelTopLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ST_t_ChannelTopLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ST_t_ChannelTopLepLepePtCutPassAr)
        evPassPtLeadAr.append(ST_t_ChannelTopLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ST_t_ChannelTopLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ST_t_ChannelTopLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ST_t_ChannelTopLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ST_t_ChannelTopLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ST_t_ChannelTopLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ST_t_ChannelTopLepLepIsoCutPassAr)
        evPassSIPAr.append(ST_t_ChannelTopLepSIPCutPassAr)


    nameAr.append("ST_t_ChannelTopBackground")
    saveNameAr.append("ST_t_ChannelTop")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 115.3
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ST_t_ChannelTopWeightSum)
    
    isQCDAr.append(False)
if ZZTo2Q2NuBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(ZZTo2Q2NuSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ZZTo2Q2NuSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ZZTo2Q2NuSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ZZTo2Q2NuSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ZZTo2Q2NuSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ZZTo2Q2NuSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ZZTo2Q2NuSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ZZTo2Q2NuSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ZZTo2Q2NuSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ZZTo2Q2NuSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ZZTo2Q2NuSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ZZTo2Q2NuSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ZZTo2Q2NuSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ZZTo2Q2NuSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ZZTo2Q2NuSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ZZTo2Q2NuSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ZZTo2Q2NuSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ZZTo2Q2NuSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ZZTo2Q2NuSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ZZTo2Q2NuSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ZZTo2Q2NuSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ZZTo2Q2NuSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ZZTo2Q2NuSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ZZTo2Q2NuSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ZZTo2Q2NuSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ZZTo2Q2NuSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ZZTo2Q2NuSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ZZTo2Q2NuSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ZZTo2Q2NuSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ZZTo2Q2NuSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ZZTo2Q2NuSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ZZTo2Q2NuSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ZZTo2Q2NuSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ZZTo2Q2NuSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ZZTo2Q2NuSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ZZTo2Q2NuSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(ZZTo2Q2NuSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ZZTo2Q2NuSLLepeEtaCutPassAr)
        evPassLepePtAr.append(ZZTo2Q2NuSLLepePtCutPassAr)
        evPassPtLeadAr.append(ZZTo2Q2NuSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(ZZTo2Q2NuSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ZZTo2Q2NuSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ZZTo2Q2NuSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ZZTo2Q2NuSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ZZTo2Q2NuSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ZZTo2Q2NuSLLepIsoCutPassAr)
        evPassSIPAr.append(ZZTo2Q2NuSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(ZZTo2Q2NuLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(ZZTo2Q2NuLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(ZZTo2Q2NuLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(ZZTo2Q2NuLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(ZZTo2Q2NuLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(ZZTo2Q2NuLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(ZZTo2Q2NuLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(ZZTo2Q2NuLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(ZZTo2Q2NuLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(ZZTo2Q2NuLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(ZZTo2Q2NuLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(ZZTo2Q2NuLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(ZZTo2Q2NuLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(ZZTo2Q2NuLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(ZZTo2Q2NuLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(ZZTo2Q2NuLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(ZZTo2Q2NuLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(ZZTo2Q2NuLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(ZZTo2Q2NuLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(ZZTo2Q2NuLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(ZZTo2Q2NuLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(ZZTo2Q2NuLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(ZZTo2Q2NuLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(ZZTo2Q2NuLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(ZZTo2Q2NuLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(ZZTo2Q2NuLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(ZZTo2Q2NuLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(ZZTo2Q2NuLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(ZZTo2Q2NuLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(ZZTo2Q2NuLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(ZZTo2Q2NuLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(ZZTo2Q2NuLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(ZZTo2Q2NuLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(ZZTo2Q2NuLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(ZZTo2Q2NuLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(ZZTo2Q2NuLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(ZZTo2Q2NuLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(ZZTo2Q2NuLepLepeEtaCutPassAr)
        evPassLepePtAr.append(ZZTo2Q2NuLepLepePtCutPassAr)
        evPassPtLeadAr.append(ZZTo2Q2NuLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(ZZTo2Q2NuLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(ZZTo2Q2NuLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(ZZTo2Q2NuLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(ZZTo2Q2NuLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(ZZTo2Q2NuLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(ZZTo2Q2NuLepLepIsoCutPassAr)
        evPassSIPAr.append(ZZTo2Q2NuLepSIPCutPassAr)


    nameAr.append("ZZTo2Q2NuBackground")
    saveNameAr.append("ZZTo2Q2Nu")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 4.561
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(ZZTo2Q2NuWeightSum)
    
    isQCDAr.append(False)
if WWTo2L2NuBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(WWTo2L2NuSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(WWTo2L2NuSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(WWTo2L2NuSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(WWTo2L2NuSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(WWTo2L2NuSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(WWTo2L2NuSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(WWTo2L2NuSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(WWTo2L2NuSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(WWTo2L2NuSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(WWTo2L2NuSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(WWTo2L2NuSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(WWTo2L2NuSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(WWTo2L2NuSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(WWTo2L2NuSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(WWTo2L2NuSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(WWTo2L2NuSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(WWTo2L2NuSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(WWTo2L2NuSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(WWTo2L2NuSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(WWTo2L2NuSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(WWTo2L2NuSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(WWTo2L2NuSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(WWTo2L2NuSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(WWTo2L2NuSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(WWTo2L2NuSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(WWTo2L2NuSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(WWTo2L2NuSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(WWTo2L2NuSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(WWTo2L2NuSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(WWTo2L2NuSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(WWTo2L2NuSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(WWTo2L2NuSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(WWTo2L2NuSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(WWTo2L2NuSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(WWTo2L2NuSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(WWTo2L2NuSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(WWTo2L2NuSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(WWTo2L2NuSLLepeEtaCutPassAr)
        evPassLepePtAr.append(WWTo2L2NuSLLepePtCutPassAr)
        evPassPtLeadAr.append(WWTo2L2NuSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(WWTo2L2NuSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(WWTo2L2NuSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(WWTo2L2NuSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(WWTo2L2NuSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(WWTo2L2NuSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(WWTo2L2NuSLLepIsoCutPassAr)
        evPassSIPAr.append(WWTo2L2NuSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(WWTo2L2NuLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(WWTo2L2NuLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(WWTo2L2NuLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(WWTo2L2NuLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(WWTo2L2NuLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(WWTo2L2NuLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(WWTo2L2NuLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(WWTo2L2NuLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(WWTo2L2NuLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(WWTo2L2NuLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(WWTo2L2NuLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(WWTo2L2NuLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(WWTo2L2NuLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(WWTo2L2NuLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(WWTo2L2NuLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(WWTo2L2NuLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(WWTo2L2NuLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(WWTo2L2NuLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(WWTo2L2NuLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(WWTo2L2NuLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(WWTo2L2NuLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(WWTo2L2NuLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(WWTo2L2NuLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(WWTo2L2NuLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(WWTo2L2NuLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(WWTo2L2NuLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(WWTo2L2NuLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(WWTo2L2NuLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(WWTo2L2NuLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(WWTo2L2NuLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(WWTo2L2NuLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(WWTo2L2NuLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(WWTo2L2NuLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(WWTo2L2NuLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(WWTo2L2NuLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(WWTo2L2NuLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(WWTo2L2NuLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(WWTo2L2NuLepLepeEtaCutPassAr)
        evPassLepePtAr.append(WWTo2L2NuLepLepePtCutPassAr)
        evPassPtLeadAr.append(WWTo2L2NuLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(WWTo2L2NuLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(WWTo2L2NuLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(WWTo2L2NuLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(WWTo2L2NuLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(WWTo2L2NuLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(WWTo2L2NuLepLepIsoCutPassAr)
        evPassSIPAr.append(WWTo2L2NuLepSIPCutPassAr)


    nameAr.append("WWTo2L2NuBackground")
    saveNameAr.append("WWTo2L2Nu")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 10.48
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(WWTo2L2NuWeightSum)
    
    isQCDAr.append(False)
if WZTo3LNuBackground:
    if doSL:
        hFatJetPtCutBackgroundPassAr.append(WZTo3LNuSLhFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(WZTo3LNuSLhFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(WZTo3LNuSLVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(WZTo3LNuSLVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(WZTo3LNuSLVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(WZTo3LNuSLVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(WZTo3LNuSLSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(WZTo3LNuSLSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(WZTo3LNuSLSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(WZTo3LNuSLSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(WZTo3LNuSLSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(WZTo3LNuSLSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(WZTo3LNuSLSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(WZTo3LNuSLSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(WZTo3LNuSLSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(WZTo3LNuSLSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(WZTo3LNuSLLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(WZTo3LNuSLLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(WZTo3LNuSLLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(WZTo3LNuSLLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(WZTo3LNuSLPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(WZTo3LNuSLPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(WZTo3LNuSLInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(WZTo3LNuSLInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(WZTo3LNuSLFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(WZTo3LNuSLOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(WZTo3LNuSLLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(WZTo3LNuSLSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(WZTo3LNuSLhFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(WZTo3LNuSLhFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(WZTo3LNuSLVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(WZTo3LNuSLVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(WZTo3LNuSLVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(WZTo3LNuSLVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(WZTo3LNuSLSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(WZTo3LNuSLSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(WZTo3LNuSLSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(WZTo3LNuSLSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(WZTo3LNuSLSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(WZTo3LNuSLSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(WZTo3LNuSLSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(WZTo3LNuSLSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(WZTo3LNuSLSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(WZTo3LNuSLSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(WZTo3LNuSLLepmPtCutPassAr)
        evPassLepmEtaAr.append(WZTo3LNuSLLepmEtaCutPassAr)
        evPassLepeEtaAr.append(WZTo3LNuSLLepeEtaCutPassAr)
        evPassLepePtAr.append(WZTo3LNuSLLepePtCutPassAr)
        evPassPtLeadAr.append(WZTo3LNuSLPtLeadCutPassAr)
        evPassPtTrailingAr.append(WZTo3LNuSLPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(WZTo3LNuSLInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(WZTo3LNuSLInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(WZTo3LNuSLFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(WZTo3LNuSLOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(WZTo3LNuSLLepIsoCutPassAr)
        evPassSIPAr.append(WZTo3LNuSLSIPCutPassAr)
    if doLep:
        hFatJetPtCutBackgroundPassAr.append(WZTo3LNuLephFatJetPtCutPassAr)
        hFatJetDeepTagCutBackgroundPassAr.append(WZTo3LNuLephFatJetDeepTagCutPassAr)
        VBFJetPtCutBackgroundPassAr.append(WZTo3LNuLepVBFJetPtCutPassAr)
        VBFJetdRCutBackgroundPassAr.append(WZTo3LNuLepVBFJetdRCutPassAr)
        VBFJetEtaCutBackgroundPassAr.append(WZTo3LNuLepVBFJetEtaCutPassAr)
        VBFJetInvMassCutBackgroundPassAr.append(WZTo3LNuLepVBFJetInvMassCutPassAr)
        SemiLepmPtCutBackgroundPassAr.append(WZTo3LNuLepSemiLepmPtCutPassAr)
        SemiLepmEtaCutBackgroundPassAr.append(WZTo3LNuLepSemiLepmEtaCutPassAr)
        SemiLepePtCutBackgroundPassAr.append(WZTo3LNuLepSemiLepePtCutPassAr)
        SemiLepeEtaCutBackgroundPassAr.append(WZTo3LNuLepSemiLepeEtaCutPassAr)
        SemiLepPtLeadCutBackgroundPassAr.append(WZTo3LNuLepSemiLepPtLeadCutPassAr)
        SemiLepPtTrailingCutBackgroundPassAr.append(WZTo3LNuLepSemiLepPtTrailingCutPassAr)
        SemiLepInvMassCutLowCutBackgroundPassAr.append(WZTo3LNuLepSemiLepInvMassCutLowCutPassAr)
        SemiLepInvMassCutHighCutBackgroundPassAr.append(WZTo3LNuLepSemiLepInvMassCutHighCutPassAr)
        SemiLepFatJetPtCutBackgroundPassAr.append(WZTo3LNuLepSemiLepFatJetPtCutPassAr)
        SemiLepFatJetZTagCutBackgroundPassAr.append(WZTo3LNuLepSemiLepFatJetZTagCutPassAr)
        LepmPtCutBackgroundPassAr.append(WZTo3LNuLepLepmPtCutPassAr)
        LepmEtaCutBackgroundPassAr.append(WZTo3LNuLepLepmEtaCutPassAr)
        LepeEtaCutBackgroundPassAr.append(WZTo3LNuLepLepeEtaCutPassAr)
        LepePtCutBackgroundPassAr.append(WZTo3LNuLepLepePtCutPassAr)
        PtLeadCutBackgroundPassAr.append(WZTo3LNuLepPtLeadCutPassAr)
        PtTrailingCutBackgroundPassAr.append(WZTo3LNuLepPtTrailingCutPassAr)
        InvMassCutLowCutBackgroundPassAr.append(WZTo3LNuLepInvMassCutLowCutPassAr)
        InvMassCutHighCutBackgroundPassAr.append(WZTo3LNuLepInvMassCutHighCutPassAr)
        FourLepInvMassCutBackgroundPassAr.append(WZTo3LNuLepFourLepInvMassCutPassAr)
        OptLepInvMassCutBackgroundPassAr.append(WZTo3LNuLepOptLepInvMassCutPassAr)
        LepIsoCutBackgroundPassAr.append(WZTo3LNuLepLepIsoCutPassAr)
        SIPCutBackgroundPassAr.append(WZTo3LNuLepSIPCutPassAr)
        #ptCutBackgroundPassAr.append(ttHToBBLepOrSemiLepPtCutPassAr)

        evPasshFatJetPtAr.append(WZTo3LNuLephFatJetPtCutPassAr)
        evPasshFatJetDeepTagAr.append(WZTo3LNuLephFatJetDeepTagCutPassAr)
        evPassVBFJetPtAr.append(WZTo3LNuLepVBFJetPtCutPassAr)
        evPassVBFJetdRAr.append(WZTo3LNuLepVBFJetdRCutPassAr)
        evPassVBFJetEtaAr.append(WZTo3LNuLepVBFJetEtaCutPassAr)
        evPassVBFJetInvMassAr.append(WZTo3LNuLepVBFJetInvMassCutPassAr)
        evPassSemiLepmPtAr.append(WZTo3LNuLepSemiLepmPtCutPassAr)
        evPassSemiLepmEtaAr.append(WZTo3LNuLepSemiLepmEtaCutPassAr)
        evPassSemiLepePtAr.append(WZTo3LNuLepSemiLepePtCutPassAr)
        evPassSemiLepeEtaAr.append(WZTo3LNuLepSemiLepeEtaCutPassAr)
        evPassSemiLepPtLeadAr.append(WZTo3LNuLepSemiLepPtLeadCutPassAr)
        evPassSemiLepPtTrailingAr.append(WZTo3LNuLepSemiLepPtTrailingCutPassAr)
        evPassSemiLepInvMassCutLowAr.append(WZTo3LNuLepSemiLepInvMassCutLowCutPassAr)
        evPassSemiLepInvMassCutHighAr.append(WZTo3LNuLepSemiLepInvMassCutHighCutPassAr)
        evPassSemiLepFatJetPtAr.append(WZTo3LNuLepSemiLepFatJetPtCutPassAr)
        evPassSemiLepFatJetZTagAr.append(WZTo3LNuLepSemiLepFatJetZTagCutPassAr)
        evPassLepmPtAr.append(WZTo3LNuLepLepmPtCutPassAr)
        evPassLepmEtaAr.append(WZTo3LNuLepLepmEtaCutPassAr)
        evPassLepeEtaAr.append(WZTo3LNuLepLepeEtaCutPassAr)
        evPassLepePtAr.append(WZTo3LNuLepLepePtCutPassAr)
        evPassPtLeadAr.append(WZTo3LNuLepPtLeadCutPassAr)
        evPassPtTrailingAr.append(WZTo3LNuLepPtTrailingCutPassAr)
        evPassInvMassCutLowAr.append(WZTo3LNuLepInvMassCutLowCutPassAr)
        evPassInvMassCutHighAr.append(WZTo3LNuLepInvMassCutHighCutPassAr)
        evPassFourLepInvMassAr.append(WZTo3LNuLepFourLepInvMassCutPassAr)
        evPassOptLepInvMassAr.append(WZTo3LNuLepOptLepInvMassCutPassAr)
        evPassLepIsoAr.append(WZTo3LNuLepLepIsoCutPassAr)
        evPassSIPAr.append(WZTo3LNuLepSIPCutPassAr)


    nameAr.append("WZTo3LNuBackground")
    saveNameAr.append("WZTo3LNu")
    if weakCuts:
        fileAr.append(TFile.Open("{0}BeforeWeakCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    else:
        fileAr.append(TFile.Open("{0}BeforeCutEvents{1}.root".format(forCondorStr,saveNameAr[-1])))
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 5.052
    XSBackgroundAr.append(tmpXSAvg)
    
    totalBackgroundEvents.append(WZTo3LNuWeightSum)
    
    isQCDAr.append(False)


anyQCD = True in isQCDAr


varLepCutSignalPassAr = [InvMassCutLowCutSignalPassAr,InvMassCutHighCutSignalPassAr]
varLepCutBackgroundPassAr = [InvMassCutLowCutBackgroundPassAr,InvMassCutHighCutBackgroundPassAr]

varSemiLepCutSignalPassAr = [SemiLepInvMassCutLowCutSignalPassAr,SemiLepInvMassCutHighCutSignalPassAr]
varSemiLepCutBackgroundPassAr = [SemiLepInvMassCutLowCutBackgroundPassAr,SemiLepInvMassCutHighCutBackgroundPassAr]
"""
if doSL:
    varCutSignalPassAr = varSemiLepCutSignalPassAr
    varCutBackgroundPassAr = varSemiLepCutBackgroundPassAr
if doLep:
    varCutSignalPassAr = varLepCutSignalPassAr
    varCutBackgroundPassAr = varLepCutBackgroundPassAr
"""

#in DrawFoMPlots these weights are set to 1 because the previous step does the weighting
#However for the histos that is not the case. For them the weighting will be handled during the histo creation process
weightsSignalAr = [1 for tmpXS,tmpEvs in zip(XSSignalAr,totalSignalEvents)]
weightsBackgroundAr = [1 for tmpXS,tmpEvs in zip(XSBackgroundAr,totalBackgroundEvents)]

weightsAr = weightsSignalAr+weightsBackgroundAr
#weightsBackgroundAr = [tmpXS*Run2Lumi/tmpEvs for tmpXS,tmpEvs in zip(XSBackgroundAr,totalBackgroundEvents)]
#weightsSignalAr = [tmpXS*Run2Lumi/tmpEvs for tmpXS,tmpEvs in zip(XSSignalAr,totalSignalEvents)]
print("weightsBackgroundAr",weightsBackgroundAr)
print("weightsSignalAr",weightsSignalAr)
#cutAmnt = 200
binAmnt = 200
logOrNot = True
chanName = "Any"
if saveName == "LepOrSL":
    chanName = "Lep or Semi-Lep"
elif saveName == "SL":
    chanName = "Semi-Lep"
elif saveName == "Lep" or saveName == "Had":
    logOrNot= False
    chanName = saveName

print(logOrNot)
#makeFoMPlots(evPassVarCutAr,varCutSignalPassAr,varCutBackgroundPassAr,weightsSignalAr,weightsBackgroundAr,varCutRangeAr,cutAmnt,cutNameAr,nameAr,skipEvPassGraphs,saveName,isSignalAr,isQCDAr,anyQCD,chanName)
#makeFoMWithEvPassPlots(evPassVarCutAr,varCutSignalPassAr,varCutBackgroundPassAr,weightsSignalAr,weightsBackgroundAr,varCutRangeAr,cutAmnt,cutNameAr,nameAr,skipEvPassGraphs,saveName,isSignalAr,isQCDAr,anyQCD,chanName,defaultCutPosAr,logOrNot,cutsToPlot,badCutIndsForSL)
varLepCutRangeAr = [InvMassCutLowRangeAr,InvMassCutHighRangeAr]
varSemiLepCutRangeAr = [InvMassCutLowRangeAr,InvMassCutHighRangeAr]
defaultLepCutPos = [InvMassCutLowCut,InvMassCutHighCut]
defaultSemiLepCutPos = [InvMassCutLowCut,InvMassCutHighCut]
varLepCutSignalSumAr = []
varLepCutBackgroundSumAr = []
for cutInd, varLepCutRangeA in enumerate(varLepCutRangeAr):
    varCutSignalSumAr = [0 for i in range(cutAmnt+1)]
    varCutBackgroundSumAr = [0 for i in range(cutAmnt+1)]

    for varCutSignalPass in varLepCutSignalPassAr[cutInd]:
        for c in range(cutAmnt+1):
            varCutSignalSumAr[c] += varCutSignalPass[c]
    for varCutBackgroundPass in varLepCutBackgroundPassAr[cutInd]:
        for c in range(cutAmnt+1):
            varCutBackgroundSumAr[c] += varCutBackgroundPass[c]
    varLepCutSignalSumAr.append(varCutSignalSumAr)
    varLepCutBackgroundSumAr.append(varCutBackgroundSumAr)


varSemiLepCutSignalSumAr = []
varSemiLepCutBackgroundSumAr = []
for cutInd, varSemiLepCutRangeA in enumerate(varSemiLepCutRangeAr):
    varCutSignalSumAr = [0 for i in range(cutAmnt+1)]
    varCutBackgroundSumAr = [0 for i in range(cutAmnt+1)]

    for varCutSignalPass in varSemiLepCutSignalPassAr[cutInd]:
        for c in range(cutAmnt+1):
            varCutSignalSumAr[c] += varCutSignalPass[c]
    for varCutBackgroundPass in varSemiLepCutBackgroundPassAr[cutInd]:
        for c in range(cutAmnt+1):
            varCutBackgroundSumAr[c] += varCutBackgroundPass[c]
    varSemiLepCutSignalSumAr.append(varCutSignalSumAr)
    varSemiLepCutBackgroundSumAr.append(varCutBackgroundSumAr)


FoMLepGraphAr = []
varLepCutGraphAr = [array('d'),array('d')]
varLepCutXAr = [array('d'),array('d')]
FoMSemiLepGraphAr = []
varSemiLepCutGraphAr = [array('d'),array('d')]
varSemiLepCutXAr = [array('d'),array('d')]
print('test')
for cutInd, varLepCutRangeA in enumerate(varLepCutRangeAr):
    #print(len(varLepCutSignalPassAr),len(varLepCutSignalPassAr[cutInd]),varLepCutSignalPassAr[cutInd])
    FoMCalc(varLepCutSignalSumAr[cutInd],varLepCutBackgroundSumAr[cutInd],varLepCutGraphAr[cutInd],varLepCutXAr[cutInd],cutAmnt,varLepCutRangeA)
for cutInd, varSemiLepCutRangeA in enumerate(varSemiLepCutRangeAr):
    #print(len(varSemiLepCutSignalPassAr),len(varSemiLepCutSignalPassAr[cutInd]),varSemiLepCutSignalPassAr[cutInd])
    FoMCalc(varSemiLepCutSignalSumAr[cutInd],varSemiLepCutBackgroundSumAr[cutInd],varSemiLepCutGraphAr[cutInd],varSemiLepCutXAr[cutInd],cutAmnt,varSemiLepCutRangeA)
print('test')
BeforeCutLepInvMassSaveNameAr = ["LepInvMassLow","LepInvMassHigh"]
BeforeCutSemiLepInvMassSaveNameAr = ["SemiLepInvMassLow","SemiLepInvMassHigh"]
histLepAr = []
canLepAr = []
histSemiLepAr = []
canSemiLepAr = []
onlyDoSomeHists = False
histsToDo = 0
breakEvEarly = False
breakEvAt = 0

makeUnstacked = False


BeforeCutLepInvMassBinsAndRangeAr = [[120,0,120],[120,60,180]]
BeforeCutSemiLepInvMassBinsAndRangeAr = [[120,0,120],[120,60,180]]

##################MAIN LOOP##################
for k,fileA in enumerate(fileAr):
    evCtr = 0
    
    print("Entering file {0}".format(k))
    BeforeCutLepInvMassTree = fileA.BeforeCutLepInvMassTree
    histLepAr.append([])
    canLepAr.append([])
    
    #Initialize all BeforeCutLepInvMass hists
    print("Initializing InvMass hists")
    for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
            break
        canLepAr[-1].append(TCanvas("{0}Can{1}".format(BeforeCutLepInvMassSaveName,saveNameAr[k]),"{0}Can{1}".format(BeforeCutLepInvMassSaveName,saveNameAr[k]),3600,2400))
        histLepAr[-1].append(TH1D("{0}Hist{1}".format(BeforeCutLepInvMassSaveName,saveNameAr[k]),"{0}Hist{1}".format(BeforeCutLepInvMassSaveName,saveNameAr[k]), BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][0], BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][1], BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][2]))
    print("Looping over events")
    #LOOP OVER EVENTS IN FILE k
    tmpInd = 0
    for j,ev in enumerate(BeforeCutLepInvMassTree):
        if breakEvEarly and evCtr >= breakEvAt:
            break
        if evCtr % 1000 == 0:
            print("ev:",evCtr)
        
        valAr = [ev.LepInvMassL,ev.LepInvMassL]
        evWeight = ev.genLepWeightL

        for valItr,valA in enumerate(valAr):
            #print(valItr)
            if onlyDoSomeHists and valItr >= histsToDo:
                break
            #if evCtr <20 and evCtr > 10 and valItr == 0:
            #    print(valA)
            #print(valA)
            #print(type(valA))
            if "vector" in str(type(valA)):
                for valEl in valA:
                    #print("vec",valItr,valEl)
                    histLepAr[k][valItr].Fill(valEl,evWeight)
            else:
                #print(valItr,valA)
                histLepAr[k][valItr].Fill(valA,evWeight)
            #histLepAr[k][valItr].Fill(valA,evWeight)
        evCtr += 1



    evCtr = 0
    
    print("Entering file {0}".format(k))
    BeforeCutSemiLepInvMassTree = fileA.BeforeCutSemiLepInvMassTree
    histSemiLepAr.append([])
    canSemiLepAr.append([])
    
    #Initialize all BeforeCutSemiLepInvMass hists
    print("Initializing InvMass hists")
    for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
            break
        canSemiLepAr[-1].append(TCanvas("{0}Can{1}".format(BeforeCutSemiLepInvMassSaveName,saveNameAr[k]),"{0}Can{1}".format(BeforeCutSemiLepInvMassSaveName,saveNameAr[k]),3600,2400))
        histSemiLepAr[-1].append(TH1D("{0}Hist{1}".format(BeforeCutSemiLepInvMassSaveName,saveNameAr[k]),"{0}Hist{1}".format(BeforeCutSemiLepInvMassSaveName,saveNameAr[k]), BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][0], BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][1], BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][2]))
    print("Looping over events")
    #LOOP OVER EVENTS IN FILE k
    tmpInd = 0
    for j,ev in enumerate(BeforeCutSemiLepInvMassTree):
        if breakEvEarly and evCtr >= breakEvAt:
            break
        if evCtr % 1000 == 0:
            print("ev:",evCtr)
        
        valAr = [ev.SemiLepInvMassL,ev.SemiLepInvMassL]
        evWeight = ev.genSemiLepWeightL

        for valItr,valA in enumerate(valAr):
            #print(valItr)
            if onlyDoSomeHists and valItr >= histsToDo:
                break
            #if evCtr <20 and evCtr > 10 and valItr == 0:
            #    print(valA)
            #print(valA)
            #print(type(valA))
            if "vector" in str(type(valA)):
                for valEl in valA:
                    #print("vec",valItr,valEl)
                    histSemiLepAr[k][valItr].Fill(valEl,evWeight)
            else:
                #print(valItr,valA)
                histSemiLepAr[k][valItr].Fill(valA,evWeight)
            #histSemiLepAr[k][valItr].Fill(valA,evWeight)
        evCtr += 1


    

BeforeCutLepInvMassTitleAr = ["Inv Mass","Inv Mass"]
BeforeCutSemiLepInvMassTitleAr = ["Inv Mass","Inv Mass"]
BeforeCutLepInvMassXTitleAr = ["Inv Mass (GeV)","Inv Mass (GeV)"]
BeforeCutSemiLepInvMassXTitleAr = ["Inv Mass (GeV)","Inv Mass (GeV)"]
signalPos = 1

###############STARTING LEP GRAPHS###############
padAr = []
legAr = []
QCDSumHistAr = []
signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if not sumQCD or not isQCDAr[k]:
        if isSignalAr[k]:
            signalName += "_"+saveNameAr[k]
        else:
            backgroundName += "_"+saveNameAr[k]

sumQCDCanAr = []
#print(len(weightsAr),len(histLepAr),len(histLepAr[0]),len(BeforeCutLepInvMassSaveNameAr),len(QCDSumHistAr))
if sumQCD:
    backgroundName += "_QCDSum"
    for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
            break
        sumQCDCanAr.append(TCanvas("{0}CanQCDSum".format(BeforeCutLepInvMassSaveName),"{0}CanQCDSum".format(BeforeCutLepInvMassSaveName),3600,2400))
        QCDSumHistAr.append(TH1D("{0}HistQCDSum".format(BeforeCutLepInvMassSaveName),"{0}HistQCDSum".format(BeforeCutLepInvMassSaveName), BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][0], BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][1], BeforeCutLepInvMassBinsAndRangeAr[BeforeCutLepInvMassItr][2]))
    for k in range(len(histLepAr)):
        if isQCDAr[k]:
            for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
                if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
                    break
                #print(k,BeforeCutLepInvMassItr)
                histLepAr[k][BeforeCutLepInvMassItr].Sumw2()
                QCDSumHistAr[BeforeCutLepInvMassItr].Sumw2()
                QCDSumHistAr[BeforeCutLepInvMassItr].Add(histLepAr[k][BeforeCutLepInvMassItr])
"""         
if not comparisonPlotsOnly:
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
                if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
                    break
                canAr[k][BeforeCutLepInvMassItr].cd()
                histLepAr[k][BeforeCutLepInvMassItr].Draw("hist")
                if savePathBool:
                    canAr[k][BeforeCutLepInvMassItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(saveNameAr[k],BeforeCutLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canAr[k][BeforeCutLepInvMassItr].SaveAs("{0}{1}{2}.png".format(saveNameAr[k],BeforeCutLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
            if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
                break
            sumQCDCanAr[BeforeCutLepInvMassItr].cd()
            QCDSumHistAr[BeforeCutLepInvMassItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[BeforeCutLepInvMassItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(BeforeCutLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[BeforeCutLepInvMassItr].SaveAs("QCDSum{0}{1}.png".format(BeforeCutLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
"""
for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
    if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
        break
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}{1}Pad".format(BeforeCutLepInvMassSaveName,BeforeCutLepInvMassItr))
    #padAr[-1][0].Draw()
    #padAr[-1][0].cd()

intComparisonAr = []



backgroundIntSumAr,QCDSumIntAr = setHistoElementsForFoM(colorAr,sumQCD,QCDSumHistAr,isQCDAr,histLepAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,BeforeCutLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


histMaxAr,histMinAr = normalizeHistsForFoM(histLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,saveNameAr,intComparisonAr,BeforeCutLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)



if sumQCD:
    histMaxAr,histMinAr = scaleQCDHistForFoM(QCDSumIntAr,QCDSumHistAr,histMaxAr,histMinAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



comparisonCanAr = []
comparisonHistStackAr = []
for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
    if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
        break
    comparisonCanAr.append(TCanvas("comparisonCan{0}".format(BeforeCutLepInvMassSaveName),"comparisonCan{0}".format(BeforeCutLepInvMassSaveName),3600,2400))
    comparisonHistStackAr.append(THStack("hist{0}Stack".format(BeforeCutLepInvMassSaveName),BeforeCutLepInvMassTitleAr[BeforeCutLepInvMassItr]))


maxIntAr = addHistsToStackForFoM(fileAr,histLepAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistAr,normalizeBackgroundsTogether,backgroundIntSumAr,BeforeCutLepInvMassSaveNameAr,signalPos,onlyDoSomeHists,histsToDo,weightsAr)

#Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

invHistsAr = []
drawInvAr = []
cloneHistAr = []


setUpInvHistsForFoM(histLepAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,saveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistAr,BeforeCutLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo)


defaultCutPosAr = []
cutRangeAr = [[0,120],[60,180]]

setUpStackedHistAndDrawFoMPlotForFoM(histMaxAr,histMinAr,histLepAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,BeforeCutLepInvMassSaveNameAr,BeforeCutLepInvMassXTitleAr,signalPos,onlyDoSomeHists,histsToDo,defaultLepCutPos,cutRangeAr,FoMLepGraphAr,varLepCutGraphAr,varLepCutXAr,chanName)
#setUpStackedHistAndDrawFoMPlot(histMax,histAr,histStack,invHistsAr,drawInvAr,legAr,FoMCan,padAr,FoMGraph,cutRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName,defaultCutPos)

if makeUnstacked:
    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for BeforeCutLepInvMassItr, BeforeCutLepInvMassSaveName in enumerate(BeforeCutLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutLepInvMassItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(BeforeCutLepInvMassSaveName),"comparisonUnstackedCan{0}".format(BeforeCutLepInvMassSaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("BeforeCutLepInvMassUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlotForFoM(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistAr,histMaxAr,histMinAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histLepAr,legAr,signalName,backgroundName,BeforeCutLepInvMassSaveNameAr,BeforeCutLepInvMassTitleAr,BeforeCutLepInvMassXTitleAr,signalPos,onlyDoSomeHists,histsToDo)






###############STARTING SEMI LEP GRAPHS###############
padAr = []
legAr = []
QCDSumHistAr = []
signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if not sumQCD or not isQCDAr[k]:
        if isSignalAr[k]:
            signalName += "_"+saveNameAr[k]
        else:
            backgroundName += "_"+saveNameAr[k]

sumQCDCanAr = []
#print(len(weightsAr),len(histSemiLepAr),len(histSemiLepAr[0]),len(BeforeCutSemiLepInvMassSaveNameAr),len(QCDSumHistAr))
if sumQCD:
    backgroundName += "_QCDSum"
    for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
            break
        sumQCDCanAr.append(TCanvas("{0}CanQCDSum".format(BeforeCutSemiLepInvMassSaveName),"{0}CanQCDSum".format(BeforeCutSemiLepInvMassSaveName),3600,2400))
        QCDSumHistAr.append(TH1D("{0}HistQCDSum".format(BeforeCutSemiLepInvMassSaveName),"{0}HistQCDSum".format(BeforeCutSemiLepInvMassSaveName), BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][0], BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][1], BeforeCutSemiLepInvMassBinsAndRangeAr[BeforeCutSemiLepInvMassItr][2]))
    for k in range(len(histSemiLepAr)):
        if isQCDAr[k]:
            for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
                if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
                    break
                #print(k,BeforeCutSemiLepInvMassItr)
                histSemiLepAr[k][BeforeCutSemiLepInvMassItr].Sumw2()
                QCDSumHistAr[BeforeCutSemiLepInvMassItr].Sumw2()
                QCDSumHistAr[BeforeCutSemiLepInvMassItr].Add(histSemiLepAr[k][BeforeCutSemiLepInvMassItr])
"""         
if not comparisonPlotsOnly:
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
                if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
                    break
                canAr[k][BeforeCutSemiLepInvMassItr].cd()
                histSemiLepAr[k][BeforeCutSemiLepInvMassItr].Draw("hist")
                if savePathBool:
                    canAr[k][BeforeCutSemiLepInvMassItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(saveNameAr[k],BeforeCutSemiLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canAr[k][BeforeCutSemiLepInvMassItr].SaveAs("{0}{1}{2}.png".format(saveNameAr[k],BeforeCutSemiLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
            if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
                break
            sumQCDCanAr[BeforeCutSemiLepInvMassItr].cd()
            QCDSumHistAr[BeforeCutSemiLepInvMassItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[BeforeCutSemiLepInvMassItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(BeforeCutSemiLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[BeforeCutSemiLepInvMassItr].SaveAs("QCDSum{0}{1}.png".format(BeforeCutSemiLepInvMassSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
"""
for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
    if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
        break
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}{1}Pad".format(BeforeCutSemiLepInvMassSaveName,BeforeCutSemiLepInvMassItr))
    #padAr[-1][0].Draw()
    #padAr[-1][0].cd()

intComparisonAr = []



backgroundIntSumAr,QCDSumIntAr = setHistoElementsForFoM(colorAr,sumQCD,QCDSumHistAr,isQCDAr,histSemiLepAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,BeforeCutSemiLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


histMaxAr,histMinAr = normalizeHistsForFoM(histSemiLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,saveNameAr,intComparisonAr,BeforeCutSemiLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)



if sumQCD:
    histMaxAr,histMinAr = scaleQCDHistForFoM(QCDSumIntAr,QCDSumHistAr,histMaxAr,histMinAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



comparisonCanAr = []
comparisonHistStackAr = []
for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
    if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
        break
    comparisonCanAr.append(TCanvas("comparisonCan{0}".format(BeforeCutSemiLepInvMassSaveName),"comparisonCan{0}".format(BeforeCutSemiLepInvMassSaveName),3600,2400))
    comparisonHistStackAr.append(THStack("hist{0}Stack".format(BeforeCutSemiLepInvMassSaveName),BeforeCutSemiLepInvMassTitleAr[BeforeCutSemiLepInvMassItr]))


maxIntAr = addHistsToStackForFoM(fileAr,histSemiLepAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistAr,normalizeBackgroundsTogether,backgroundIntSumAr,BeforeCutSemiLepInvMassSaveNameAr,signalPos,onlyDoSomeHists,histsToDo,weightsAr)

#Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

invHistsAr = []
drawInvAr = []
cloneHistAr = []


setUpInvHistsForFoM(histSemiLepAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,saveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistAr,BeforeCutSemiLepInvMassSaveNameAr,onlyDoSomeHists,histsToDo)


defaultCutPosAr = []
cutRangeAr = [[0,120],[60,180]]

setUpStackedHistAndDrawFoMPlotForFoM(histMaxAr,histMinAr,histSemiLepAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,BeforeCutSemiLepInvMassSaveNameAr,BeforeCutSemiLepInvMassXTitleAr,signalPos,onlyDoSomeHists,histsToDo,defaultSemiLepCutPos,cutRangeAr,FoMSemiLepGraphAr,varSemiLepCutGraphAr,varSemiLepCutXAr,chanName)
#setUpStackedHistAndDrawFoMPlot(histMax,histAr,histStack,invHistsAr,drawInvAr,legAr,FoMCan,padAr,FoMGraph,cutRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName,defaultCutPos)

if makeUnstacked:
    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for BeforeCutSemiLepInvMassItr, BeforeCutSemiLepInvMassSaveName in enumerate(BeforeCutSemiLepInvMassSaveNameAr):
        if onlyDoSomeHists and BeforeCutSemiLepInvMassItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(BeforeCutSemiLepInvMassSaveName),"comparisonUnstackedCan{0}".format(BeforeCutSemiLepInvMassSaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("BeforeCutSemiLepInvMassUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlotForFoM(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistAr,histMaxAr,histMinAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histSemiLepAr,legAr,signalName,backgroundName,BeforeCutSemiLepInvMassSaveNameAr,BeforeCutSemiLepInvMassTitleAr,BeforeCutSemiLepInvMassXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

print("Done.","time:",time.time()-startt)