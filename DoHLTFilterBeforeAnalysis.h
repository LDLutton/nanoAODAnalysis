#include<TTree.h>

bool debug = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool debugGenPart = false;

bool scratchDown = true;

bool testRun = true;
bool SDC2V3MCWZHV2 = false;
bool SDC2Vm2p5MCWZHV2 = false;
bool SDC2Vm3MCWZHV2 = false;
bool SDC2Vm1MCWZHV2 = false;
bool SDC2V0MCWZHV2 = false;
bool SDC2V1MCWZHV2 = false;
bool SDC2V4MCWZHV2 = false;
bool SDC2V5MCWZHV2 = false;
bool SDC2V3MC = false;
bool SDC2Vm2p5MC = false;
bool SDC2Vm2MC = false;
bool SDC2Vm1MC = false;
bool SDC2V0MC = false;
bool SDC2V1MC = false;
bool SDC2V4MC = false;
bool SDC2V4p5MC = false;
bool SDC2V3MCV2 = false;
bool SDC2Vm2p5MCV2 = false;
bool SDC2Vm2MCV2 = false;
bool SDC2Vm1MCV2 = false;
bool SDC2V0MCV2 = false;
bool SDC2V1MCV2 = false;
bool SDC2V4MCV2 = false;
bool SDC2V4p5MCV2 = false;

bool SDC2V3MCWZH2017V2 = false;
bool SDC2Vm2p5MCWZH2017V2 = false;
bool SDC2Vm3MCWZH2017V2 = false;
bool SDC2Vm1MCWZH2017V2 = false;
bool SDC2V0MCWZH2017V2 = false;
bool SDC2V1MCWZH2017V2 = false;
bool SDC2V4MCWZH2017V2 = false;
bool SDC2V5MCWZH2017V2 = false;
bool SDC2V3MC2017V2 = false;
bool SDC2Vm2p5MC2017V2 = false;
bool SDC2Vm2MC2017V2 = false;
bool SDC2Vm1MC2017V2 = false;
bool SDC2V0MC2017V2 = false;
bool SDC2V1MC2017V2 = false;
bool SDC2V4MC2017V2 = false;
bool SDC2V4p5MC2017V2 = false;

bool SDC2V3MCWZH2016V2 = false;
bool SDC2Vm2p5MCWZH2016V2 = false;
bool SDC2Vm3MCWZH2016V2 = false;
bool SDC2Vm1MCWZH2016V2 = false;
bool SDC2V0MCWZH2016V2 = false;
bool SDC2V1MCWZH2016V2 = false;
bool SDC2V4MCWZH2016V2 = false;
bool SDC2V5MCWZH2016V2 = false;
bool SDC2V3MC2016V2 = false;
bool SDC2Vm2p5MC2016V2 = false;
bool SDC2Vm2MC2016V2 = false;
bool SDC2Vm1MC2016V2 = false;
bool SDC2V0MC2016V2 = false;
bool SDC2V1MC2016V2 = false;
bool SDC2V4MC2016V2 = false;
bool SDC2V4p5MC2016V2 = false;

bool SDC2V3MCWZH2016APVV2 = false;
bool SDC2Vm2p5MCWZH2016APVV2 = false;
bool SDC2Vm3MCWZH2016APVV2 = false;
bool SDC2Vm1MCWZH2016APVV2 = false;
bool SDC2V0MCWZH2016APVV2 = false;
bool SDC2V1MCWZH2016APVV2 = false;
bool SDC2V4MCWZH2016APVV2 = false;
bool SDC2V5MCWZH2016APVV2 = false;
bool SDC2V3MC2016APVV2 = false;
bool SDC2Vm2p5MC2016APVV2 = false;
bool SDC2Vm2MC2016APVV2 = false;
bool SDC2Vm1MC2016APVV2 = false;
bool SDC2V0MC2016APVV2 = false;
bool SDC2V1MC2016APVV2 = false;
bool SDC2V4MC2016APVV2 = false;
bool SDC2V4p5MC2016APVV2 = false;

bool SDC2V2MCZZHReweight = false;
bool SDC2V2MCZZH17Reweight = false;
bool SDC2V2MCZZH16Reweight = false;
bool SDC2V2MCZZH16APVReweight = false;

bool SDC2V2MCWZHReweight = false;
bool SDC2V2MCWZH17Reweight = false;
bool SDC2V2MCWZH16Reweight = false;
bool SDC2V2MCWZH16APVReweight = false;


bool MGC2VEtaDifCut = false;
bool MGOSix = false;
bool MGOSixEtaDifCut = false;
bool MGOHBox = false;
bool MGOHBoxEtaDifCut = false;
bool MGOHDD = false;
bool MGOHDDEtaDifCut = false;
bool MGOHW = false;
bool MGSM = false;
bool ttHToBBBackground = false;
bool ttZJetsBackground = false;
bool DYBackground = false;
bool QCDPT170to300Background = false;
bool QCDPT300to470Background = false;
bool QCDPT470to600Background = false;
bool QCDPT600to800Background = false;
bool QCDPT800to1000Background = false;
bool QCDPT1000to1400Background = false;
bool QCDPT1400to1800Background = false;
bool QCDPT1800to2400Background = false;
bool QCDPT2400to3200Background = false;
bool QCDPT3200toInfBackground = false;

bool TTJetsBackground = false;
bool TTToHadronicBackground = false;
bool TTTo2L2NuBackground = false;
bool TTToSemiLeptonicBackground = false;
bool ST_s_ChannelBackground = false;
bool ST_t_ChannelAntiTopBackground = false;
bool ST_t_ChannelTopBackground = false;
bool ZZTo2Q2NuBackground = false;
bool WWTo2L2NuBackground = false;
bool WZTo3LNuBackground = false;

bool ZZBackground = false;
bool WWBackground = false;
bool WZBackground = false;

bool TTbb_TTToHadronicBackground = false;
bool TTbb_TTTo2L2NuBackground = false;
bool TTbb_TTToSemiLeptonicBackground = false;

bool LaraTest = false;

float hTobbBR = 0.5772683;
float maxdRCut = 0.8;

//For calculating DeltaR for two particles from their respective etas and phis
float calcDeltaR(float phi1,float eta1,float phi2,float eta2){
    float deta = eta1-eta2;
    float dphi = abs(phi1-phi2);
    if (dphi > M_PI) dphi -= (2*M_PI);
    return sqrt((deta*deta)+(dphi*dphi));
}
