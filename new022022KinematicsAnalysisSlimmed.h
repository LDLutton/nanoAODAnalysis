#include<TTree.h>

bool debug = false;
bool debugHadronic = false;
bool debugGenPart = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool useTighterCut = false;

bool testRun = true;
bool MGC2VEtaDifCut = false;
bool MGOSix = false;
bool MGOSixEtaDifCut = false;
bool MGOHBox = false;
bool MGOHBoxEtaDifCut = false;
bool MGOHDD = false;
bool MGOHDDEtaDifCut = false;
bool MGOHW = false;
bool MGSM = false;



//VBF jet pair selection;
//Defining jet matching cuts;

float jetPTCut = 50.;
float jetEtaDifCut = 2.0;
float jetInvMassCut = 400.;

//Defining fat jet matching cuts;
float fatJetPTCut = 200.;
float hFatJetPTCut = 350.;
float hFatJetDeepTagCut = 0.2;
float hFatJetdRCut = 0.4;
