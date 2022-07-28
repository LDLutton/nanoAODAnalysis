#include<TVector2.h>
#include<Math/Vector4D.h>
#include <Math/GenVector/LorentzVector.h>
#include <math.h>
#include<vector>

float ZMass = 91.1876;

//For calculating DeltaR for two particles from their respective etas and phis
float calcDeltaR(float phi1,float eta1,float phi2,float eta2){
    float deta = eta1-eta2;
    float dphi = abs(phi1-phi2);
    if (dphi > M_PI) dphi -= (2*M_PI);
    return sqrt((deta*deta)+(dphi*dphi));
}

//Int_t getInitialMother(TTreeReader *myEventsReader,Int_t genPartInd):
Int_t getInitialMother(TTreeReaderArray<Int_t> &GenPart_genPartIdxMother,TTreeReaderArray<Int_t> &GenPart_pdgId,Int_t genPartInd,bool debug){
    bool momFound = false;
    std::vector<Int_t> motherAr;
    Int_t tmpMomInd = GenPart_genPartIdxMother[genPartInd];
    if (debug) std::cout << "tmpMomInd " << tmpMomInd << "\n";
    while (!momFound){
        motherAr.push_back(GenPart_pdgId[tmpMomInd]);
        tmpMomInd = GenPart_genPartIdxMother[tmpMomInd];
        if (debug) std::cout << "tmpMomInd " << tmpMomInd <<" motherAr " << motherAr.back() << "\n";
        if (tmpMomInd == -1 || tmpMomInd == 0) momFound = true;
    }
    return motherAr.back();
}



void dolCandCutWithID(TTreeReaderArray<Bool_t> &Lep_IdL,TTreeReaderArray<Float_t> &Lep_eta,TTreeReaderArray<Float_t> &Lep_mass,TTreeReaderArray<Int_t> &Lep_charge,TTreeReaderArray<Float_t> &Lep_phi,TTreeReaderArray<Float_t> &Lep_pt,TTreeReaderArray<Float_t> &Lep_Dxy,TTreeReaderArray<Float_t> &Lep_Dz,TTreeReaderArray<Float_t> &Lep_sip3d,TTreeReaderArray<Float_t> &Lep_MiniPFRelIso,TTreeReaderArray<Float_t> &Electron_sieie,TTreeReaderArray<Float_t> &Electron_hoe,TTreeReaderArray<Float_t> &Electron_eInvMinusPInv,TTreeReaderArray<Bool_t> &Electron_convVeto,TTreeReaderArray<UChar_t> &Electron_lostHits,TTreeReaderArray<Int_t> &Lep_jetIdx,TTreeReaderArray<Float_t> &Jet_btagDeepFlavB,TTreeReaderArray<Float_t> &Lep_mvaTTH,UInt_t nlLep,std::vector<UInt_t> &lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &lepCandVecAr,std::vector<Int_t> &lepCandChargeAr,float lPtCut,float lEtaCut,float lDxyCut,float lDzCut,float lMiniPFRelIsoCut,float eSieieBarrelCut,float eSieieEndcapCut,float eHoeCut,float eInvMinusPInvCut,UInt_t eLostHitsCut,float lepJetDeepTagLooseCut,float lepJetDeepTagMediumCut,float lPromptMVACut,float lSIP3DCut,bool isMuon,bool debug){
    for (UInt_t lItr=0; lItr < nlLep; lItr++){
        if (debug) std::cout << "lItr " << lItr<< "Lep_IdL[lItr]" << Lep_IdL[lItr] << "\n";
        bool lepPass = false;
        if (!Lep_IdL[lItr]){
            continue;
        }
        float tmpPt = Lep_pt[lItr];
        if (debug) std::cout << "lItr " << lItr << " tmpPt " << tmpPt << "\n";
        if (tmpPt > lPtCut){
            if (debug) std::cout << "passed pt cut\n";
            float tmpEta = Lep_eta[lItr];
            if (debug) std::cout << "tmpEta " <<tmpEta << "\n";
            if (abs(tmpEta) < lEtaCut){
                if (debug) std::cout << "passed eta cut\n";
                float tmpDxy = Lep_Dxy[lItr];
                if (abs(tmpDxy) < lDxyCut) {
                    if (debug) std::cout << "passed Dxy cut\n";
                    float tmpDz = Lep_Dz[lItr];
                    if (abs(tmpDz) < lDzCut) {
                        if (debug) std::cout << "passed Dz cut\n";
                        float tmpLepSIP3D = Lep_sip3d[lItr];
                        if (tmpLepSIP3D < lSIP3DCut) {
                            if (debug) std::cout << "passed LepSIP3D cut\n";
                            float tmpLep_MiniPFRelIso = Lep_MiniPFRelIso[lItr];
                            if (tmpLep_MiniPFRelIso < lMiniPFRelIsoCut*tmpPt) {
                                if (debug) std::cout << "passed Lep Iso cut\n";
                                Int_t tmpJetId = Lep_jetIdx[lItr];
                                if (debug) std::cout << "tmpJetId " << tmpJetId << "\n";
                                float tmpJetbTag;
                                if (tmpJetId <0) {
                                    tmpJetbTag = 0;
                                }
                                else {
                                    tmpJetbTag = Jet_btagDeepFlavB[tmpJetId];
                                }
                                float tmpJetbTagCut = lepJetDeepTagLooseCut;
                                if (tmpPt < 20){
                                    tmpJetbTagCut = lepJetDeepTagMediumCut;
                                }
                                else if (tmpPt <45){
                                    tmpJetbTagCut = lepJetDeepTagLooseCut+(((tmpPt-20)/25)*(lepJetDeepTagMediumCut-lepJetDeepTagLooseCut));
                                }
                                if (tmpJetbTag < tmpJetbTagCut){
                                    if (debug) std::cout << "passed Lep nearest jet btag cut\n";
                                    float tmpLepMVA = Lep_mvaTTH[lItr];
                                    if (tmpLepMVA > lPromptMVACut) {
                                        if (debug) std::cout << "passed Lep ttH MVA cut\n";
                                        if (!isMuon){
                                            float tmpSieieCut = eSieieBarrelCut;
                                            if (tmpEta > 1.5){
                                                tmpSieieCut = eSieieEndcapCut;
                                            }
                                            float tmpSieie = Electron_sieie[lItr];
                                            if (tmpSieie < eSieieBarrelCut) {
                                                if (debug) std::cout << "passed Lep Sieie cut\n";
                                                float tmpHoe = Electron_hoe[lItr];
                                                if (tmpHoe < eHoeCut) {
                                                    if (debug) std::cout << "passed Lep Hoe cut\n";
                                                    float tmpInvEInvP = Electron_eInvMinusPInv[lItr];
                                                    if (tmpInvEInvP > eInvMinusPInvCut) {
                                                        if (debug) std::cout << "passed Lep eInvMinusPInv cut\n";
                                                        if (Electron_convVeto[lItr]) {
                                                            if (debug) std::cout << "passed Elec Conv cut\n";
                                                            UChar_t tmpLostHits =  Electron_lostHits[lItr];
                                                            if (tmpLostHits <= eLostHitsCut) {
                                                                if (debug) std::cout << "passed elec misshits cut\n";
                                                                lepPass = true;
                                                            }
                                                        }
                                                    }

                                                }
                                            }
                                        }
                                        else lepPass = true;
                                    }
                                }
                            }

                        }
                    }
                }
                
                
            }
        }
        if (lepPass){
            lepCandIndAr.push_back(lItr);
            float tmpPhi = Lep_phi[lItr];
            float tmpMass = Lep_mass[lItr];
            float tmpEta = Lep_eta[lItr];
            ROOT::Math::PtEtaPhiMVector tmpVec = ROOT::Math::PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass);
            lepCandVecAr.push_back(tmpVec);
            Int_t tmpCharge = Lep_charge[lItr];
            lepCandChargeAr.push_back(tmpCharge);
        }
    }
}

void dolZ1Cut(TTreeReaderArray<Float_t> &Lep_pt,std::vector<UInt_t> lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,std::vector<Int_t> lepCandChargeAr,std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsAr,bool &Z1IsMuon,bool forMuon,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,float &tmpTopZ1LeadPt,float &tmpTopZ1TrailingPt,Int_t &tmpTopLeadItr,Int_t &tmpTopTrailingItr,ROOT::Math::PtEtaPhiMVector &tmpTopLeadVec,ROOT::Math::PtEtaPhiMVector &tmpTopTrailingVec,Int_t &tmpTopLeadCharge,Int_t &tmpTopTrailingCharge,float &difFromZMassOne, bool debug){
    if (debug) std::cout << "in dolZ1Cut fcn\n";
    for (UInt_t lItrOne=0; lItrOne<lepCandIndAr.size()-1; lItrOne++) { //LEP LOOP ONE
        Int_t tmpChargeOne = lepCandChargeAr[lItrOne];
        if (debug) std::cout << "lItrOne " << lItrOne << " lepCandIndAr[lItrOne] " << lepCandIndAr[lItrOne] << " tmpChargeOne " << tmpChargeOne << "\n";
        for (UInt_t lItrTwo=lItrOne+1; lItrTwo<lepCandIndAr.size(); lItrTwo++){ //LEP LOOP TWO
            Int_t tmpChargeTwo = lepCandChargeAr[lItrTwo];
            if (debug) std::cout << "lItrTwo " << lItrTwo << " lepCandIndAr[lItrTwo] " << lepCandIndAr[lItrTwo] << " tmpChargeOne " << tmpChargeTwo << "\n";
            if (tmpChargeOne != tmpChargeTwo){ //CHECK IF OPPOSITE CHARGE
                ROOT::Math::PtEtaPhiMVector tmpZ1VecOne = lepCandVecAr[lItrOne];
                ROOT::Math::PtEtaPhiMVector tmpZ1VecTwo = lepCandVecAr[lItrTwo];
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo;
                float tmpZ1Mass = tmpZ1Vec.M();
                if (debug){
                    std::cout << "not the same charge. yay\n";
                    std::cout << "tmpZ1VecOne " << tmpZ1VecOne << "tmpZ1VecTwo " << tmpZ1VecTwo << "tmpZ1Vec " << tmpZ1Vec << "\n";
                }
                if (tmpZ1Mass > invMassCutLow && tmpZ1Mass < invMassCutHigh){ //CHECK IF INV MASS PASSES CUTS
                    if (debug) std::cout << "Passed inv mass cut\n";
                    float tmpZDif = abs(tmpZ1Mass - ZMass);
                    float tmpPtOne = Lep_pt[lepCandIndAr[lItrOne]];
                    float tmpPtTwo = Lep_pt[lepCandIndAr[lItrTwo]];
                    if (debug) std::cout << "tmpZDif " << tmpZDif << "tmpPtOne " << tmpPtOne << "tmpPtTwo " << tmpPtTwo << "\n";
                    float tmpPtLead;
                    float tmpPtTrailing;
                    UInt_t tmpLeadItr;
                    UInt_t tmpTrailingItr;
                    ROOT::Math::PtEtaPhiMVector tmpLeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpTrailingVec;
                    Int_t tmpLeadCharge;
                    Int_t tmpTrailingCharge;
                    if (tmpPtOne >= tmpPtTwo){ //SORT PTS
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrOne],lepCandIndAr[lItrTwo]])
                        tmpPtLead = tmpPtOne;
                        tmpPtTrailing = tmpPtTwo;
                        tmpLeadItr = lItrOne;
                        tmpTrailingItr = lItrTwo;
                        tmpLeadVec = tmpZ1VecOne;
                        tmpTrailingVec = tmpZ1VecTwo;
                        tmpLeadCharge = tmpChargeOne;
                        tmpTrailingCharge = tmpChargeTwo;
                    }
                    else{
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrTwo],lepCandIndAr[lItrOne]])
                        tmpPtLead = tmpPtTwo;
                        tmpPtTrailing = tmpPtOne;
                        tmpLeadItr = lItrTwo;
                        tmpTrailingItr = lItrOne;
                        tmpLeadVec = tmpZ1VecTwo;
                        tmpTrailingVec = tmpZ1VecOne;
                        tmpLeadCharge = tmpChargeTwo;
                        tmpTrailingCharge = tmpChargeOne;
                    }


                    if (tmpZDif < difFromZMassOne){ //CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                        if (debug) std::cout << "current smallest zdif yay\n";
                        
                        if (tmpPtLead > ptLeadCut && tmpPtTrailing > ptTrailingCut){ //CHECK IF PASSES PT CUT
                            if (debug) std::cout << "wow it passed the pt cut also yay\n";
                            tmpTopZ1LeadPt = tmpPtLead;
                            tmpTopZ1TrailingPt = tmpPtTrailing;
                            difFromZMassOne = tmpZDif;
                            tmpTopLeadItr = tmpLeadItr;
                            tmpTopTrailingItr = tmpTrailingItr;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            if (!forMuon) Z1IsMuon = false;
                            else Z1IsMuon = true;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            tmpTopLeadVec = tmpLeadVec;
                            tmpTopTrailingVec = tmpTrailingVec;
                            tmpTopLeadCharge = tmpLeadCharge;
                            tmpTopTrailingCharge = tmpTrailingCharge;
                        }
                    }
                    std::array<UInt_t,2> tmpItrList = {tmpLeadItr,tmpTrailingItr};
                    lepPassesZ2CutsAr.push_back(tmpItrList);
                    
                }
                
            }
        }
    }
}


void dolZ1CutWithInvMass(TTreeReaderArray<Float_t> &Lep_pt,std::vector<UInt_t> lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,std::vector<Int_t> lepCandChargeAr,std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsAr,bool &Z1IsMuon,bool forMuon,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,float &tmpTopZ1LeadPt,float &tmpTopZ1TrailingPt,Int_t &tmpTopLeadItr,Int_t &tmpTopTrailingItr,ROOT::Math::PtEtaPhiMVector &tmpTopLeadVec,ROOT::Math::PtEtaPhiMVector &tmpTopTrailingVec,Int_t &tmpTopLeadCharge,Int_t &tmpTopTrailingCharge,float &difFromZMassOne,
ROOT::Math::PtEtaPhiMVector HFJPlusZFJVec,float fatJetZPlusHInvMassCut, bool debug){
    if (debug) std::cout << "in dolZ1Cut fcn\n";
    for (UInt_t lItrOne=0; lItrOne<lepCandIndAr.size()-1; lItrOne++) { //LEP LOOP ONE
        Int_t tmpChargeOne = lepCandChargeAr[lItrOne];
        if (debug) std::cout << "lItrOne " << lItrOne << " lepCandIndAr[lItrOne] " << lepCandIndAr[lItrOne] << " tmpChargeOne " << tmpChargeOne << "\n";
        for (UInt_t lItrTwo=lItrOne+1; lItrTwo<lepCandIndAr.size(); lItrTwo++){ //LEP LOOP TWO
            Int_t tmpChargeTwo = lepCandChargeAr[lItrTwo];
            if (debug) std::cout << "lItrTwo " << lItrTwo << " lepCandIndAr[lItrTwo] " << lepCandIndAr[lItrTwo] << " tmpChargeOne " << tmpChargeTwo << "\n";
            if (tmpChargeOne != tmpChargeTwo){ //CHECK IF OPPOSITE CHARGE
                ROOT::Math::PtEtaPhiMVector tmpZ1VecOne = lepCandVecAr[lItrOne];
                ROOT::Math::PtEtaPhiMVector tmpZ1VecTwo = lepCandVecAr[lItrTwo];
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo;
                ROOT::Math::PtEtaPhiMVector HFJPlusZPairVec = HFJPlusZFJVec+tmpZ1Vec;
                float tmpHFJPlusZPairMass = HFJPlusZPairVec.M();
                if (tmpHFJPlusZPairMass > fatJetZPlusHInvMassCut){
                    float tmpZ1Mass = tmpZ1Vec.M();
                    if (debug){
                        std::cout << "not the same charge. yay\n";
                        std::cout << "tmpZ1VecOne " << tmpZ1VecOne << "tmpZ1VecTwo " << tmpZ1VecTwo << "tmpZ1Vec " << tmpZ1Vec << "\n";
                    }
                    if (tmpZ1Mass > invMassCutLow && tmpZ1Mass < invMassCutHigh){ //CHECK IF INV MASS PASSES CUTS
                        if (debug) std::cout << "Passed inv mass cut\n";
                        float tmpZDif = abs(tmpZ1Mass - ZMass);
                        float tmpPtOne = Lep_pt[lepCandIndAr[lItrOne]];
                        float tmpPtTwo = Lep_pt[lepCandIndAr[lItrTwo]];
                        if (debug) std::cout << "tmpZDif " << tmpZDif << "tmpPtOne " << tmpPtOne << "tmpPtTwo " << tmpPtTwo << "\n";
                        float tmpPtLead;
                        float tmpPtTrailing;
                        UInt_t tmpLeadItr;
                        UInt_t tmpTrailingItr;
                        ROOT::Math::PtEtaPhiMVector tmpLeadVec;
                        ROOT::Math::PtEtaPhiMVector tmpTrailingVec;
                        Int_t tmpLeadCharge;
                        Int_t tmpTrailingCharge;
                        if (tmpPtOne >= tmpPtTwo){ //SORT PTS
                            //lepPassesZ2CutsAr.append([lepCandIndAr[lItrOne],lepCandIndAr[lItrTwo]])
                            tmpPtLead = tmpPtOne;
                            tmpPtTrailing = tmpPtTwo;
                            tmpLeadItr = lItrOne;
                            tmpTrailingItr = lItrTwo;
                            tmpLeadVec = tmpZ1VecOne;
                            tmpTrailingVec = tmpZ1VecTwo;
                            tmpLeadCharge = tmpChargeOne;
                            tmpTrailingCharge = tmpChargeTwo;
                        }
                        else{
                            //lepPassesZ2CutsAr.append([lepCandIndAr[lItrTwo],lepCandIndAr[lItrOne]])
                            tmpPtLead = tmpPtTwo;
                            tmpPtTrailing = tmpPtOne;
                            tmpLeadItr = lItrTwo;
                            tmpTrailingItr = lItrOne;
                            tmpLeadVec = tmpZ1VecTwo;
                            tmpTrailingVec = tmpZ1VecOne;
                            tmpLeadCharge = tmpChargeTwo;
                            tmpTrailingCharge = tmpChargeOne;
                        }


                        if (tmpZDif < difFromZMassOne){ //CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                            if (debug) std::cout << "current smallest zdif yay\n";
                            
                            if (tmpPtLead > ptLeadCut && tmpPtTrailing > ptTrailingCut){ //CHECK IF PASSES PT CUT
                                if (debug) std::cout << "wow it passed the pt cut also yay\n";
                                tmpTopZ1LeadPt = tmpPtLead;
                                tmpTopZ1TrailingPt = tmpPtTrailing;
                                difFromZMassOne = tmpZDif;
                                tmpTopLeadItr = tmpLeadItr;
                                tmpTopTrailingItr = tmpTrailingItr;
                                if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                                if (!forMuon) Z1IsMuon = false;
                                else Z1IsMuon = true;
                                if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                                tmpTopLeadVec = tmpLeadVec;
                                tmpTopTrailingVec = tmpTrailingVec;
                                tmpTopLeadCharge = tmpLeadCharge;
                                tmpTopTrailingCharge = tmpTrailingCharge;
                            }
                        }
                        std::array<UInt_t,2> tmpItrList = {tmpLeadItr,tmpTrailingItr};
                        lepPassesZ2CutsAr.push_back(tmpItrList);
                        
                    }
                }
            }
        }
    }
}
                

void fillZ2Ars(std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsFinalAr,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> &lZ2VecPairAr,std::vector<std::array<double,2>> &lZ2PtPairAr,std::vector<std::array<Int_t,2>> &lZ2ChargePairAr,std::vector<std::array<UInt_t,2>> lepPassesZ2CutsAr,std::vector<Int_t> lepCandChargeAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,bool shouldIgnore,std::array<Int_t,2> indsToIgnore,bool &Z2CandsBool){
    
    if (!shouldIgnore) lepPassesZ2CutsFinalAr = lepPassesZ2CutsAr;
    //std::cout << "lepPassesZ2CutsAr.size() "<< lepPassesZ2CutsAr.size() << "\n";
    for (UInt_t lepPassesZ2CutsInd=0;lepPassesZ2CutsInd<lepPassesZ2CutsAr.size();lepPassesZ2CutsInd++){ //Loop through lep Z2 cand pairs to fill all arrays
        if (shouldIgnore){
            //std::cout << "indsToIgnore[0] " <<indsToIgnore[0] << " indsToIgnore[1] " << indsToIgnore[1] << "\n";
            //std::cout << "lepPassesZ2CutsInd " <<lepPassesZ2CutsInd << "\n";
            //std::cout << "lepPassesZ2CutsAr[lepPassesZ2CutsInd] " <<lepPassesZ2CutsAr[lepPassesZ2CutsInd] << "\n";
            if (!(std::find(std::begin(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), indsToIgnore[0]) != std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd])) && !(std::find(std::begin(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), indsToIgnore[1]) != std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]))){
                lepPassesZ2CutsFinalAr.push_back(lepPassesZ2CutsAr[lepPassesZ2CutsInd]);


                std::array<Int_t,2> tmplZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                lZ2ChargePairAr.push_back(tmplZ2ChargePair);
                ROOT::Math::PtEtaPhiMVector tmpVecOne = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]];
                ROOT::Math::PtEtaPhiMVector tmpVecTwo = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]];
                std::array<double,2> tmplZ2PtPair = {tmpVecOne.Pt(),tmpVecTwo.Pt()};
                std::array<ROOT::Math::PtEtaPhiMVector,2> tmplZ2VecPair = {tmpVecOne,tmpVecTwo};
                std::array<Int_t,2> tmpZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                
                lZ2PtPairAr.push_back(tmplZ2PtPair);
                lZ2VecPairAr.push_back(tmplZ2VecPair);
                Z2CandsBool = true;
            }
        }
        else{
            std::array<Int_t,2> tmplZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
            lZ2ChargePairAr.push_back(tmplZ2ChargePair);
            ROOT::Math::PtEtaPhiMVector tmpVecOne = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]];
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]];
            std::array<double,2> tmplZ2PtPair = {tmpVecOne.Pt(),tmpVecTwo.Pt()};
            std::array<ROOT::Math::PtEtaPhiMVector,2> tmplZ2VecPair = {tmpVecOne,tmpVecTwo};
            std::array<Int_t,2> tmpZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                
            lZ2PtPairAr.push_back(tmplZ2PtPair);
            lZ2VecPairAr.push_back(tmplZ2VecPair);
            Z2CandsBool = true;

        }
    }
}



void dolZ2Cut(ROOT::Math::PtEtaPhiMVector Z1LeadVec,ROOT::Math::PtEtaPhiMVector Z1TrailingVec,ROOT::Math::PtEtaPhiMVector tmpZ1Vec,float tmpZ1M,Int_t Z1LeadCharge,Int_t Z1TrailingCharge,bool Z1IsMuon,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> lZ2VecPairAr,std::vector<std::array<double,2>> lZ2PtPairAr,std::vector<std::array<Int_t,2>> lZ2ChargePairAr,Int_t &tmpZ2Ind,bool &Z2IsMuon,float &tmpTopZ2LeadPt,float &tmpTopZ2TrailingPt,float fourLepInvMassCut,float optLepInvMassCut, bool forElec){
    
    //tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
    //float tmpZ1M = tmpZ1Vec.M();
    for (UInt_t Z2Itr=0;Z2Itr<lZ2VecPairAr.size();Z2Itr++){ //LOOP OVER ALL Z2 CANDIDATE PAIRS
        float tmpZ2LeadPt = lZ2PtPairAr[Z2Itr][0];
        if ((tmpZ2LeadPt > tmpTopZ2LeadPt) || (tmpZ2LeadPt == tmpTopZ2LeadPt  && lZ2PtPairAr[Z2Itr][1] > tmpTopZ2TrailingPt)){ //Check if passes lead Z2 pt cut
            ROOT::Math::PtEtaPhiMVector tmpZ4Vec = tmpZ1Vec+lZ2VecPairAr[Z2Itr][0]+lZ2VecPairAr[Z2Itr][1];
            if (tmpZ4Vec.M() > fourLepInvMassCut){ //Check if passes four lepton inv mass cut
                if ((forElec && !Z1IsMuon) || (!forElec && Z1IsMuon)){ //If Z1 is same lep type, then have to perform second 4e cuts
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec = lZ2VecPairAr[Z2Itr][0] + lZ2VecPairAr[Z2Itr][1];
                    float tmpZ2M = tmpZ2Vec.M();
                    ROOT::Math::PtEtaPhiMVector tmpLepPairVecOne;
                    ROOT::Math::PtEtaPhiMVector tmpLepPairVecTwo;
                    if (Z1LeadCharge != lZ2ChargePairAr[Z2Itr][0]){
                        tmpLepPairVecOne = Z1LeadVec + lZ2VecPairAr[Z2Itr][0];
                        tmpLepPairVecTwo = Z1TrailingVec + lZ2VecPairAr[Z2Itr][1];
                    }
                    else{
                        tmpLepPairVecOne = Z1LeadVec + lZ2VecPairAr[Z2Itr][1];
                        tmpLepPairVecTwo = Z1TrailingVec + lZ2VecPairAr[Z2Itr][0];
                    }

                    UInt_t tmpPassCtr = 0;
                    if (tmpLepPairVecOne.M() > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpZ1M > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpZ2M > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpPassCtr >= 3){
                        tmpZ2Ind = Z2Itr;
                        tmpTopZ2LeadPt = tmpZ2LeadPt;
                        tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                        Z2IsMuon = !forElec;
                    }
                    else if (tmpPassCtr == 2){
                        if (tmpLepPairVecTwo.M() > optLepInvMassCut){
                            tmpZ2Ind = Z2Itr;
                            tmpTopZ2LeadPt = tmpZ2LeadPt;
                            tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                            Z2IsMuon = !forElec;
                        }
                    }
                }
                else{
                    tmpZ2Ind = Z2Itr;
                    tmpTopZ2LeadPt = tmpZ2LeadPt;
                    tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                    Z2IsMuon = !forElec;
                }
            }
        }
    }   
}

bool doISOCut(float Z1LeadIso,float Z1TrailingIso,float Z2LeadIso,float Z2TrailingIso,float lepIsoCut){
    if (Z1LeadIso + Z1TrailingIso >= lepIsoCut) return false;
    else if (Z1LeadIso + Z2LeadIso >= lepIsoCut) return false;
    else if (Z1LeadIso + Z2TrailingIso >= lepIsoCut) return false;
    else if (Z1TrailingIso + Z2LeadIso >= lepIsoCut) return false;
    else if (Z1TrailingIso + Z2TrailingIso >= lepIsoCut) return false;
    else if (Z2LeadIso + Z2TrailingIso >= lepIsoCut) return false;
    else return true;
}


bool doSemiLepISOCut(float leadIso,float trailingIso,float lepIsoCut){
    if (leadIso + trailingIso >= lepIsoCut) return false;
    else return true;
}


void doVBFJetCut(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Int_t> &Jet_jetId,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_mass,float jetPTCut,float jetEtaDifCut,float jetInvMassCut,float &jetPairInvMass,float &jetLeadPt,float &jetLeadEta,float &jetLeadPhi,float &jetTrailingPt,float &jetTrailingEta,float &jetTrailingPhi,UInt_t &leadJet_1,UInt_t &leadJet_2,std::vector<ROOT::Math::PtEtaPhiMVector> dRCheckVecAr,float dRCut,bool debug){
    //debug = true;
    //std::cout << "++++++++ "<< VBFJetdRCut << "\n";
    for (UInt_t jetIndOne=0; jetIndOne<nJetLen-1;jetIndOne++){
        float jetPtOne = Jet_pt[jetIndOne];
        Int_t jetIdOne = Jet_jetId[jetIndOne];
        if (debug) std::cout << "jetIndOne: " << jetIndOne << " Jet_pt[jetIndOne]: " << Jet_pt[jetIndOne] << " Jet_jetId[jetIndOne]: " << Jet_jetId[jetIndOne] << "\n";
        if (jetPtOne < jetPTCut || !(jetIdOne == 6)) continue;
        float jetEtaOne = Jet_eta[jetIndOne];
        float jetPhiOne = Jet_phi[jetIndOne];
        bool FJdRPass = true;
        for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
            float tmpDeltaR = calcDeltaR(jetPhiOne,jetEtaOne,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

            

            if (tmpDeltaR < dRCut){
                FJdRPass = false;
                break;
            }

        }
        if (!FJdRPass) continue;
        float jetMassOne = Jet_mass[jetIndOne];
        ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne);

        for (UInt_t jetIndTwo=jetIndOne+1; jetIndTwo<nJetLen; jetIndTwo++){
            float jetPtTwo = Jet_pt[jetIndTwo];
            Int_t jetIdTwo = Jet_jetId[jetIndTwo];
            if (debug) std::cout << "jetIndTwo: " << jetIndTwo << " Jet_pt[jetIndTwo]: " << Jet_pt[jetIndTwo] << " Jet_jetId[jetIndTwo]: " << Jet_jetId[jetIndTwo] << "\n";
            if (jetPtTwo < jetPTCut || !(jetIdTwo == 6)) continue;
            
            
            float jetEtaTwo = Jet_eta[jetIndTwo];
            if (debug) std::cout << "jetEtaOne: " << jetEtaOne << " jetEtaTwo: " << jetEtaTwo << " jetEtaDifCut: " << jetEtaDifCut << "\n";
            if (abs(jetEtaOne - jetEtaTwo) < jetEtaDifCut) continue;
            
            
            float jetPhiTwo = Jet_phi[jetIndTwo];
            FJdRPass = true;
            for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                float tmpDeltaR = calcDeltaR(jetPhiTwo,jetEtaTwo,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                

                if (tmpDeltaR < dRCut){
                    FJdRPass = false;
                    break;
                }

            }
            if (!FJdRPass) continue;
            
            float jetMassTwo = Jet_mass[jetIndTwo];
            
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo);
            ROOT::Math::PtEtaPhiMVector tmpVecSum = tmpVecOne+tmpVecTwo;
            float tmpJetPairInvMass = tmpVecSum.M();

            if (debug) std::cout << "tmpJetPairInvMass: " << tmpJetPairInvMass << " jetInvMassCut: " << jetInvMassCut << "\n";


            if (tmpJetPairInvMass < jetInvMassCut) continue;
            if (tmpJetPairInvMass > jetPairInvMass){
                //Check dR to Higgs and Z FJs
                //bool FJdRPass = true;
                //std::cout << "------------ "<< VBFJetdRCut << "\n";
                /*
                for (UInt_t tmpFJItr=0;tmpFJItr<selectedFJ_phi.size();tmpFJItr++){
  
                    if (calcDeltaR(selectedFJ_phi[tmpFJItr],selectedFJ_eta[tmpFJItr],jetPhiOne,jetEtaOne) <= VBFJetdRCut) {
                        FJdRPass = false;
                        break;
                    }
                    if (calcDeltaR(selectedFJ_phi[tmpFJItr],selectedFJ_eta[tmpFJItr],jetPhiTwo,jetEtaTwo) <= VBFJetdRCut) {
                        FJdRPass = false;
                        break;
                    }
                }
                */
                /*
                //bool FJdRPass = true;
                ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJet_pt,tmpFatJet_eta,tmpFatJet_phi,tmpFatJet_mass);
                
                for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                    float tmpDeltaR = calcDeltaR(jetPhiOne,jetEtaOne,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                    

                    if (tmpDeltaR < dRCut){
                        FJdRPass = false;
                        break;
                    }
                    tmpDeltaR = calcDeltaR(jetPhiTwo,jetEtaTwo,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                    

                    if (tmpDeltaR < dRCut){
                        FJdRPass = false;
                        break;
                    }


                }
                */




                if (debug) std::cout << "FJdRPass: " << FJdRPass << " FJdRPass: " << FJdRPass << "\n";
                
                jetPairInvMass = tmpJetPairInvMass;
                if (jetPtOne >= jetPtTwo) {
                    jetLeadPt = jetPtOne;
                    jetLeadEta = jetEtaOne;
                    jetLeadPhi = jetPhiOne;
                    jetTrailingPt = jetPtTwo;
                    jetTrailingEta = jetEtaTwo;
                    jetTrailingPhi = jetPhiTwo;
                    leadJet_1 = jetIndOne;
                    leadJet_2 = jetIndTwo;
                }
                else {
                    jetLeadPt = jetPtTwo;
                    jetLeadEta = jetEtaTwo;
                    jetLeadPhi = jetPhiTwo;
                    jetTrailingPt = jetPtOne;
                    jetTrailingEta = jetEtaOne;
                    jetTrailingPhi = jetPhiOne;
                    leadJet_1 = jetIndTwo;
                    leadJet_2 = jetIndOne;
                }
                
            }
        }
    }
    //debug = false;
}

void doBJetVeto(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_btagDeepFlavB,float &hFatJet_phi_fromHParticleNet,float &hFatJet_eta_fromHParticleNet,float dRCut,float bTagCut,bool &passesCut,bool debug){
    //debug = true;
    //std::cout << "++++++++ "<< VBFJetdRCut << "\n";
    passesCut = true;
    for (UInt_t jetInd=0; jetInd<nJetLen-1;jetInd++){
        float jetPt = Jet_pt[jetInd];
        if (jetPt >= 30){
            float jetEta = Jet_eta[jetInd];
            if (abs(jetEta) <= 2.5){
                float jetPhi = Jet_phi[jetInd];
                float tmpDeltaR = calcDeltaR(jetPhi,jetEta,hFatJet_phi_fromHParticleNet,hFatJet_eta_fromHParticleNet);
                if (tmpDeltaR > 0.8) {
                    float tmpJetBTag = Jet_btagDeepFlavB[jetInd];
                    if (tmpJetBTag > bTagCut) {
                        passesCut = false;
                        break;
                    }
                }
            }
        }   
    }
}

void doBJetVeto_WithBDTVariables(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_btagDeepFlavB,float &hFatJet_phi_fromHParticleNet,float &hFatJet_eta_fromHParticleNet,float dRCut,float bTagCut,bool &passesCut,float &maxPassingBTag,bool debug){
    //debug = true;
    //std::cout << "++++++++ "<< VBFJetdRCut << "\n";
    passesCut = true;
    for (UInt_t jetInd=0; jetInd<nJetLen-1;jetInd++){
        float jetPt = Jet_pt[jetInd];
        if (jetPt >= 30){
            float jetEta = Jet_eta[jetInd];
            if (abs(jetEta) <= 2.5){
                float jetPhi = Jet_phi[jetInd];
                float tmpDeltaR = calcDeltaR(jetPhi,jetEta,hFatJet_phi_fromHParticleNet,hFatJet_eta_fromHParticleNet);
                if (tmpDeltaR > 0.8) {
                    float tmpJetBTag = Jet_btagDeepFlavB[jetInd];
                    if (tmpJetBTag > maxPassingBTag) maxPassingBTag = tmpJetBTag;
                    if (tmpJetBTag > bTagCut) {
                        passesCut = false;
                        break;
                    }
                }
            }
        }   
    }
}


void doVBFJetCutEtaDifSelection(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Int_t> &Jet_jetId,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_mass,float jetPTCut,float jetEtaDifCut,float jetInvMassCut,float &jetPairInvMass,float &jetLeadPt,float &jetLeadEta,float &jetLeadPhi,float &jetTrailingPt,float &jetTrailingEta,float &jetTrailingPhi,UInt_t &leadJet_1,UInt_t &leadJet_2,std::vector<ROOT::Math::PtEtaPhiMVector> dRCheckVecAr,float dRCut,bool debug){
    //debug = true;
    //std::cout << "++++++++ "<< VBFJetdRCut << "\n";
    float jetEtaDif = 0;
    for (UInt_t jetIndOne=0; jetIndOne<nJetLen-1;jetIndOne++){
        float jetPtOne = Jet_pt[jetIndOne];
        Int_t jetIdOne = Jet_jetId[jetIndOne];
        if (debug) std::cout << "jetIndOne: " << jetIndOne << " Jet_pt[jetIndOne]: " << Jet_pt[jetIndOne] << " Jet_jetId[jetIndOne]: " << Jet_jetId[jetIndOne] << "\n";
        //Checking Jetid
        if (jetPtOne < jetPTCut || !(jetIdOne == 6)) continue;
        float jetEtaOne = Jet_eta[jetIndOne];
        float jetPhiOne = Jet_phi[jetIndOne];
        bool FJdRPass = true;
        //Checking dR
        for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
            float tmpDeltaR = calcDeltaR(jetPhiOne,jetEtaOne,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

            

            if (tmpDeltaR < dRCut){
                FJdRPass = false;
                break;
            }

        }
        if (!FJdRPass) continue;
        float jetMassOne = Jet_mass[jetIndOne];
        ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne);
        //second jet loop
        for (UInt_t jetIndTwo=jetIndOne+1; jetIndTwo<nJetLen; jetIndTwo++){
            float jetPtTwo = Jet_pt[jetIndTwo];
            Int_t jetIdTwo = Jet_jetId[jetIndTwo];
            if (debug) std::cout << "jetIndTwo: " << jetIndTwo << " Jet_pt[jetIndTwo]: " << Jet_pt[jetIndTwo] << " Jet_jetId[jetIndTwo]: " << Jet_jetId[jetIndTwo] << "\n";
            //Checking second JetID
            if (jetPtTwo < jetPTCut || !(jetIdTwo == 6)) continue;
            
            
            float jetEtaTwo = Jet_eta[jetIndTwo];
            if (debug) std::cout << "jetEtaOne: " << jetEtaOne << " jetEtaTwo: " << jetEtaTwo << " jetEtaDifCut: " << jetEtaDifCut << "\n";
            //Checking jet eta dif
            float tmpJetEtaDif = abs(jetEtaOne - jetEtaTwo);
            if (tmpJetEtaDif < jetEtaDifCut || tmpJetEtaDif < jetEtaDif) continue;
            
            
            float jetPhiTwo = Jet_phi[jetIndTwo];
            FJdRPass = true;
            //Checking second jet dR
            for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                float tmpDeltaR = calcDeltaR(jetPhiTwo,jetEtaTwo,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                

                if (tmpDeltaR < dRCut){
                    FJdRPass = false;
                    break;
                }

            }
            if (!FJdRPass) continue;
            
            float jetMassTwo = Jet_mass[jetIndTwo];
            
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo);
            ROOT::Math::PtEtaPhiMVector tmpVecSum = tmpVecOne+tmpVecTwo;
            float tmpJetPairInvMass = tmpVecSum.M();

            if (debug) std::cout << "tmpJetPairInvMass: " << tmpJetPairInvMass << " jetInvMassCut: " << jetInvMassCut << "\n";

            //Checking jet pair inv mass
            if (tmpJetPairInvMass < jetInvMassCut) continue;




            if (debug) std::cout << "FJdRPass: " << FJdRPass << " FJdRPass: " << FJdRPass << "\n";
            
            jetEtaDif = tmpJetEtaDif;
            jetPairInvMass = tmpJetPairInvMass;
            if (jetPtOne >= jetPtTwo) {
                jetLeadPt = jetPtOne;
                jetLeadEta = jetEtaOne;
                jetLeadPhi = jetPhiOne;
                jetTrailingPt = jetPtTwo;
                jetTrailingEta = jetEtaTwo;
                jetTrailingPhi = jetPhiTwo;
                leadJet_1 = jetIndOne;
                leadJet_2 = jetIndTwo;
            }
            else {
                jetLeadPt = jetPtTwo;
                jetLeadEta = jetEtaTwo;
                jetLeadPhi = jetPhiTwo;
                jetTrailingPt = jetPtOne;
                jetTrailingEta = jetEtaOne;
                jetTrailingPhi = jetPhiOne;
                leadJet_1 = jetIndTwo;
                leadJet_2 = jetIndOne;
            }
                
            
        }
    }
    //debug = false;
}

void doVBFJetCutPtSelection(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Int_t> &Jet_jetId,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_mass,float jetPTCut,float jetEtaDifCut,float jetInvMassCut,float &jetPairInvMass,float &jetLeadPt,float &jetLeadEta,float &jetLeadPhi,float &jetTrailingPt,float &jetTrailingEta,float &jetTrailingPhi,UInt_t &leadJet_1,UInt_t &leadJet_2,std::vector<ROOT::Math::PtEtaPhiMVector> dRCheckVecAr,float dRCut,bool debug){
    //debug = true;
    //std::cout << "++++++++ "<< VBFJetdRCut << "\n";
    for (UInt_t jetIndOne=0; jetIndOne<nJetLen-1;jetIndOne++){
        float jetPtOne = Jet_pt[jetIndOne];
        Int_t jetIdOne = Jet_jetId[jetIndOne];
        if (debug) std::cout << "jetIndOne: " << jetIndOne << " Jet_pt[jetIndOne]: " << Jet_pt[jetIndOne] << " Jet_jetId[jetIndOne]: " << Jet_jetId[jetIndOne] << "\n";
        //Checking Jetid
        if (jetPtOne < jetPTCut || !(jetIdOne == 6)) continue;
        float jetEtaOne = Jet_eta[jetIndOne];
        float jetPhiOne = Jet_phi[jetIndOne];
        bool FJdRPass = true;
        //Checking dR
        for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
            float tmpDeltaR = calcDeltaR(jetPhiOne,jetEtaOne,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

            

            if (tmpDeltaR < dRCut){
                FJdRPass = false;
                break;
            }

        }
        if (!FJdRPass) continue;
        float jetMassOne = Jet_mass[jetIndOne];
        ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne);
        //second jet loop
        for (UInt_t jetIndTwo=jetIndOne+1; jetIndTwo<nJetLen; jetIndTwo++){
            float jetPtTwo = Jet_pt[jetIndTwo];
            Int_t jetIdTwo = Jet_jetId[jetIndTwo];
            if (debug) std::cout << "jetIndTwo: " << jetIndTwo << " Jet_pt[jetIndTwo]: " << Jet_pt[jetIndTwo] << " Jet_jetId[jetIndTwo]: " << Jet_jetId[jetIndTwo] << "\n";
            //Checking second JetID
            if (jetPtTwo < jetPTCut || !(jetIdTwo == 6)) continue;
            
            
            float jetEtaTwo = Jet_eta[jetIndTwo];
            if (debug) std::cout << "jetEtaOne: " << jetEtaOne << " jetEtaTwo: " << jetEtaTwo << " jetEtaDifCut: " << jetEtaDifCut << "\n";
            //Checking jet eta dif
            float tmpJetEtaDif = abs(jetEtaOne - jetEtaTwo);
            if (tmpJetEtaDif < jetEtaDifCut) continue;
            
            
            float jetPhiTwo = Jet_phi[jetIndTwo];
            FJdRPass = true;
            //Checking second jet dR
            for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                float tmpDeltaR = calcDeltaR(jetPhiTwo,jetEtaTwo,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                

                if (tmpDeltaR < dRCut){
                    FJdRPass = false;
                    break;
                }

            }
            if (!FJdRPass) continue;
            
            float jetMassTwo = Jet_mass[jetIndTwo];
            
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo);
            ROOT::Math::PtEtaPhiMVector tmpVecSum = tmpVecOne+tmpVecTwo;
            float tmpJetPairInvMass = tmpVecSum.M();

            if (debug) std::cout << "tmpJetPairInvMass: " << tmpJetPairInvMass << " jetInvMassCut: " << jetInvMassCut << "\n";

            //Checking jet pair inv mass
            if (tmpJetPairInvMass < jetInvMassCut) continue;




            if (debug) std::cout << "FJdRPass: " << FJdRPass << " FJdRPass: " << FJdRPass << "\n";

            //Checking Pt for jet selection
            bool passPt = false;
            if (jetPtOne >= jetPtTwo) {
                if (jetPtOne > jetLeadPt) {
                    passPt = true;
                }
                else if (jetPtOne == jetLeadPt && jetPtTwo > jetTrailingPt) passPt = true;

            }
            if (passPt){
                jetPairInvMass = tmpJetPairInvMass;
                if (jetPtOne >= jetPtTwo) {
                    jetLeadPt = jetPtOne;
                    jetLeadEta = jetEtaOne;
                    jetLeadPhi = jetPhiOne;
                    jetTrailingPt = jetPtTwo;
                    jetTrailingEta = jetEtaTwo;
                    jetTrailingPhi = jetPhiTwo;
                    leadJet_1 = jetIndOne;
                    leadJet_2 = jetIndTwo;
                }
                else {
                    jetLeadPt = jetPtTwo;
                    jetLeadEta = jetEtaTwo;
                    jetLeadPhi = jetPhiTwo;
                    jetTrailingPt = jetPtOne;
                    jetTrailingEta = jetEtaOne;
                    jetTrailingPhi = jetPhiOne;
                    leadJet_1 = jetIndTwo;
                    leadJet_2 = jetIndOne;
                }
            }
                
            
        }
    }
    //debug = false;
}

void debugOutputForVBFJetCut(UInt_t evCount,UInt_t leadJet_1,UInt_t leadJet_2,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_eta,bool debug){
    if (debug){
        std::cout << " found jet pairs\n";
        std::cout << evCount+1 << " selected jet pair\n";
        std::cout << "Lead jet ind    " << leadJet_1 << "\n";
        std::cout << "Trailing jet ind    " << leadJet_2 << "\n";
        std::cout << "Lead jet phi    " << Jet_phi[leadJet_1] << "\n";
        std::cout << "Trailing jet phi    " << Jet_phi[leadJet_2] << "\n";
        std::cout << "Lead jet eta    " << Jet_eta[leadJet_1] << "\n";
        std::cout << "Trailing jet eta    " << Jet_eta[leadJet_2] << "\n";
    }
}

void doHiggsFatJetCut(UInt_t nFatJetLen,float &hFatJet_pt_fromHParticleNet,float &hFatJet_phi_fromHParticleNet,float &hFatJet_eta_fromHParticleNet,float &hFatJet_mass_fromHParticleNet,float &hFatJet_HParticleNet_fromHParticleNet,UInt_t &hFatJet_ind_fromHParticleNet,TTreeReaderArray<Float_t> &FatJet_deepTag_H,float hFatJetDeepTagCut,TTreeReaderArray<Float_t> &FatJet_pt,float hFatJetPTCut,TTreeReaderArray<Int_t> &FatJet_jetId,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,float dRCut,std::vector<Int_t> &FJIndAr,float ZPairPlusHInvMassCut,float ZPairPlusHPtCut){
    float tmpFJHParticleNetMax = hFatJetDeepTagCut;
    ROOT::Math::PtEtaPhiMVector HFJVec;
    for (UInt_t fatJetInd=0;fatJetInd<nFatJetLen;fatJetInd++){
        bool sameFJ = false;
        for (UInt_t FJInd=0;FJInd<FJIndAr.size();FJInd++){
            if (fatJetInd == FJIndAr[FJInd]) {
                sameFJ = true;
                break;
            }
        }
        if (sameFJ) continue;
        
        float tmpFatJet_deepTag_H = FatJet_deepTag_H[fatJetInd];

        if (debug) {
            std::cout << fatJetInd << " +++++++++++++++\n";
            std::cout << "Fat jet DeepTag_H    " <<  tmpFatJet_deepTag_H << "\n";
        }
        
        if (tmpFatJet_deepTag_H > tmpFJHParticleNetMax){
            float tmpFatJet_pt = FatJet_pt[fatJetInd];

            if (debug){
                std::cout << "Fat jet pt    " <<  tmpFatJet_pt << "\n";
            }
            
            if (tmpFatJet_pt > hFatJetPTCut){
                Int_t tmpFatJet_jetId = FatJet_jetId[fatJetInd];

                if (debug){
                    std::cout << "Fat jet jetId    " <<  tmpFatJet_jetId << "\n";
                }

                if (tmpFatJet_jetId == 6){
                    
                    

                    if (debug) std::cout << "Passed fatjet cuts\n";

                    if (tmpFatJet_deepTag_H > hFatJet_HParticleNet_fromHParticleNet){
                        if (debug) std::cout << "HParticleNet greater than previous FJ HParticleNet\n";
                        float tmpFatJet_phi = FatJet_phi[fatJetInd];
                        float tmpFatJet_eta = FatJet_eta[fatJetInd];
                        //ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJet_pt,tmpFatJet_eta,tmpFatJet_phi,FatJet_mass[fatJetInd]);
                        bool tmpPassdR = true;
                        float tmpZPairPlusHPt = tmpFatJet_pt;
                        float tmpFatJet_mass = FatJet_mass[fatJetInd];
                        ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJet_pt,tmpFatJet_eta,tmpFatJet_phi,tmpFatJet_mass);
                        for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                            float tmpDeltaR = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                            

                            if (tmpDeltaR < dRCut){
                                tmpPassdR = false;
                                break;
                            }
                            tmpZPairPlusHPt += dRCheckVecAr[dRCheckVecInd].Pt();
                            tmpFJVec += dRCheckVecAr[dRCheckVecInd];

                        }
                        //std::cout << "tmpPassdR " << tmpPassdR << " tmpFJVec.M() " << tmpFJVec.M() << " ZPairPlusHInvMassCut " << ZPairPlusHInvMassCut<< "\n";
                        if (tmpPassdR && (tmpFJVec.M() > ZPairPlusHInvMassCut)) {
                            if (tmpZPairPlusHPt > ZPairPlusHPtCut){
                            

                                
                                if (debug){
                                    std::cout << "Fat jet phi    " <<  tmpFatJet_phi << "\n";
                                    std::cout << "Fat jet eta    " <<  tmpFatJet_eta << "\n";
                                }
                                




                                hFatJet_HParticleNet_fromHParticleNet = tmpFatJet_deepTag_H;
                                hFatJet_pt_fromHParticleNet = tmpFatJet_pt;
                                hFatJet_eta_fromHParticleNet = tmpFatJet_eta;
                                hFatJet_phi_fromHParticleNet = tmpFatJet_phi;
                                hFatJet_mass_fromHParticleNet = tmpFatJet_mass;
                                hFatJet_ind_fromHParticleNet = fatJetInd;
                                tmpFJHParticleNetMax = tmpFatJet_deepTag_H;
                                HFJVec = tmpFJVec;
                            }
                        }
                    }
                    
                }
            }
        }
    }
    if (hFatJet_pt_fromHParticleNet != 0) {
        FJIndAr.push_back(hFatJet_ind_fromHParticleNet);
        dRCheckVecAr.push_back(HFJVec);
    }
}

void doHiggsFatJetCutEarlySelection(UInt_t nFatJetLen,float &hFatJet_pt_fromHParticleNet,float &hFatJet_phi_fromHParticleNet,float &hFatJet_eta_fromHParticleNet,float &hFatJet_mass_fromHParticleNet,float &hFatJet_HParticleNet_fromHParticleNet,UInt_t &hFatJet_ind_fromHParticleNet,TTreeReaderArray<Float_t> &FatJet_deepTag_H,float hFatJetDeepTagCut,TTreeReaderArray<Float_t> &FatJet_pt,float hFatJetPTCut,TTreeReaderArray<Int_t> &FatJet_jetId,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,float dRCut,std::vector<Int_t> &FJIndAr){
    float tmpFJHParticleNetMax = hFatJetDeepTagCut;
    ROOT::Math::PtEtaPhiMVector HFJVec;
    for (UInt_t fatJetInd=0;fatJetInd<nFatJetLen;fatJetInd++){
        bool sameFJ = false;
        for (UInt_t FJInd=0;FJInd<FJIndAr.size();FJInd++){
            if (fatJetInd == FJIndAr[FJInd]) {
                sameFJ = true;
                break;
            }
        }
        if (sameFJ) continue;
        
        float tmpFatJet_deepTag_H = FatJet_deepTag_H[fatJetInd];

        if (debug) {
            std::cout << fatJetInd << " +++++++++++++++\n";
            std::cout << "Fat jet DeepTag_H    " <<  tmpFatJet_deepTag_H << "\n";
        }
        
        if (tmpFatJet_deepTag_H > tmpFJHParticleNetMax){
            float tmpFatJet_pt = FatJet_pt[fatJetInd];

            if (debug){
                std::cout << "Fat jet pt    " <<  tmpFatJet_pt << "\n";
            }
            
            if (tmpFatJet_pt > hFatJetPTCut){
                Int_t tmpFatJet_jetId = FatJet_jetId[fatJetInd];

                if (debug){
                    std::cout << "Fat jet jetId    " <<  tmpFatJet_jetId << "\n";
                }

                if (tmpFatJet_jetId == 6){
                    
                    

                    if (debug) std::cout << "Passed fatjet cuts\n";

                    if (tmpFatJet_deepTag_H > hFatJet_HParticleNet_fromHParticleNet){
                        if (debug) std::cout << "HParticleNet greater than previous FJ HParticleNet\n";
                        float tmpFatJet_phi = FatJet_phi[fatJetInd];
                        float tmpFatJet_eta = FatJet_eta[fatJetInd];
                        //ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJet_pt,tmpFatJet_eta,tmpFatJet_phi,FatJet_mass[fatJetInd]);
                        bool tmpPassdR = true;
                        float tmpZPairPlusHPt = tmpFatJet_pt;
                        float tmpFatJet_mass = FatJet_mass[fatJetInd];
                        ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJet_pt,tmpFatJet_eta,tmpFatJet_phi,tmpFatJet_mass);
                        for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                            float tmpDeltaR = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                            

                            if (tmpDeltaR < dRCut){
                                tmpPassdR = false;
                                break;
                            }
                            tmpZPairPlusHPt += dRCheckVecAr[dRCheckVecInd].Pt();
                            tmpFJVec += dRCheckVecAr[dRCheckVecInd];

                        }
                        //std::cout << "tmpPassdR " << tmpPassdR << " tmpFJVec.M() " << tmpFJVec.M() << " ZPairPlusHInvMassCut " << ZPairPlusHInvMassCut<< "\n";
                        if (tmpPassdR) {
                                
                            if (debug){
                                std::cout << "Fat jet phi    " <<  tmpFatJet_phi << "\n";
                                std::cout << "Fat jet eta    " <<  tmpFatJet_eta << "\n";
                            }
                            




                            hFatJet_HParticleNet_fromHParticleNet = tmpFatJet_deepTag_H;
                            hFatJet_pt_fromHParticleNet = tmpFatJet_pt;
                            hFatJet_eta_fromHParticleNet = tmpFatJet_eta;
                            hFatJet_phi_fromHParticleNet = tmpFatJet_phi;
                            hFatJet_mass_fromHParticleNet = tmpFatJet_mass;
                            hFatJet_ind_fromHParticleNet = fatJetInd;
                            tmpFJHParticleNetMax = tmpFatJet_deepTag_H;
                            HFJVec = tmpFJVec;
                        
                        }
                    }
                    
                }
            }
        }
    }
    if (hFatJet_pt_fromHParticleNet != 0) {
        FJIndAr.push_back(hFatJet_ind_fromHParticleNet);
        dRCheckVecAr.push_back(HFJVec);
    }
}

void doHiggsFatJetCutST(std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,float ZPairPlusHInvMassCut,float ZPairPlusHPtCut,bool &passesSTCutBool){

    float tmpZPairPlusHPt = 0.;
    ROOT::Math::PtEtaPhiMVector tmpFJVec;
    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {

        if (dRCheckVecInd == 0){
            tmpFJVec = dRCheckVecAr[dRCheckVecInd];
        }
        else {
            tmpFJVec += dRCheckVecAr[dRCheckVecInd];
        }
        tmpZPairPlusHPt += dRCheckVecAr[dRCheckVecInd].Pt();
        

    }
    //std::cout << "tmpPassdR " << tmpPassdR << " tmpFJVec.M() " << tmpFJVec.M() << " ZPairPlusHInvMassCut " << ZPairPlusHInvMassCut<< "\n";
    if (tmpFJVec.M() > ZPairPlusHInvMassCut) {
        if (tmpZPairPlusHPt > ZPairPlusHPtCut){
            passesSTCutBool = true;
        }
    }
}

void doHiggsFatJetCutSTWithBDTVars(std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,float ZPairPlusHInvMassCut,float ZPairPlusHPtCut,float &ZPairPlusHInvMass,float &ZPairPlusHPt,bool &passesSTCutBool){

    float tmpZPairPlusHPt = 0.;
    ROOT::Math::PtEtaPhiMVector tmpFJVec;
    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {

        if (dRCheckVecInd == 0){
            tmpFJVec = dRCheckVecAr[dRCheckVecInd];
        }
        else {
            tmpFJVec += dRCheckVecAr[dRCheckVecInd];
        }
        tmpZPairPlusHPt += dRCheckVecAr[dRCheckVecInd].Pt();
        

    }
    //std::cout << "tmpPassdR " << tmpPassdR << " tmpFJVec.M() " << tmpFJVec.M() << " ZPairPlusHInvMassCut " << ZPairPlusHInvMassCut<< "\n";
    if (tmpFJVec.M() > ZPairPlusHInvMassCut) {
        if (tmpZPairPlusHPt > ZPairPlusHPtCut){
            passesSTCutBool = true;
            ZPairPlusHInvMass = tmpFJVec.M();
            ZPairPlusHPt = tmpZPairPlusHPt;

        }
    }
}

void doSemiLepChanFatJetCut(Int_t &FJInd,Int_t numFatJet,float fatJetPTCut,float fatJetZTagCut,TTreeReaderArray<Float_t> &FatJet_pt,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,TTreeReaderArray<Float_t> &FatJet_deepTag_ZvsQCD,TTreeReaderArray<Int_t> &FatJet_jetId,
std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,float dRCut,
UInt_t &passSemiLepCut,bool &passesCutsBool,bool &passedAsSemiLepBool){

    float semiLepFatJetPT = 0;
    float semiLepFatJetTag = 0;
    float semiLepFatJet_phi = 0;
    float semiLepFatJet_eta = 0;
    ROOT::Math::PtEtaPhiMVector semiLepFatJetVec;
    if (dRCheckVecAr.size()){
        for (UInt_t i=0; i<numFatJet;i++){

            //Skip selected higgs fatjet
            //No longer do this, since this cut comes before Higgs FJ
            //if (i == hFatJet_ind_fromHParticleNet) continue;

            float tmpFatJetPT = FatJet_pt[i];
            float tmpFatJetTag = FatJet_deepTag_ZvsQCD[i];
            Int_t tmpFatJet_jetId = FatJet_jetId[i];
                    
            //Trying out tagging instead of pt for choosing final H FJ
            //if (tmpFatJetTag > fatJetZTagCut && tmpFatJetPT > fatJetPTCut && tmpFatJetPT > semiLepFatJetPT){
            //std::cout << "tmpFatJetPT " << tmpFatJetPT << " fatJetPTCut " << fatJetPTCut <<"\n";
            if (tmpFatJetTag > fatJetZTagCut && tmpFatJetPT > fatJetPTCut && tmpFatJetTag > semiLepFatJetTag && tmpFatJet_jetId == 6){
                //std::cout << "Wow it passed!\n";
                ROOT::Math::PtEtaPhiMVector tmpFJVec = ROOT::Math::PtEtaPhiMVector(tmpFatJetPT,FatJet_eta[i],FatJet_phi[i],FatJet_mass[i]);
                bool tmpPassdR = true;
                for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                    float tmpDeltaR = calcDeltaR(FatJet_phi[i],FatJet_eta[i],dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());
                    if (tmpDeltaR < dRCut){
                        tmpPassdR = false;
                        break;
                    }

                }
                if (tmpPassdR){

                    FJInd = i;
                    semiLepFatJetPT = tmpFatJetPT;
                    semiLepFatJetTag = tmpFatJetTag;
                    semiLepFatJet_phi = FatJet_phi[i];
                    semiLepFatJet_eta = FatJet_eta[i];
                    semiLepFatJetVec = tmpFJVec;
                }
                
            }
        }
        if (FJInd >= 0) {
            dRCheckVecAr.push_back(semiLepFatJetVec);
            passSemiLepCut += 1;
            passesCutsBool = true;
            passedAsSemiLepBool = true;

        }
    }
    

}

void doHadChanFatJetCut(Int_t &LFJOneInd,Int_t &LFJTwoInd,Int_t numFatJet,float fatJetPTCut,float fatJetZPairInvMassCut,TTreeReaderArray<Float_t> &FatJet_pt,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,TTreeReaderArray<Float_t> &FatJet_deepTag_ZvsQCD){

    float leadFatJetMaxTag = 0;
    float secondFatJetMaxTag = 0;
    float leadFatJet_phi = 0;
    float leadFatJet_eta = 0;
    float secondFatJet_phi = 0;
    float secondFatJet_eta = 0;
    //ROOT::Math::PtEtaPhiMVector leadFatJetVec;
    //ROOT::Math::PtEtaPhiMVector secondFatJetVec;

    for (UInt_t i=0;i<numFatJet-1;i++){
        if (debug) std::cout << "First FatJet " << i << "\n";

        //Skip selected higgs fatjet
        //if (i == hFatJet_ind_fromHParticleNet) continue;

        float tmpFatJet_phi_One = FatJet_phi[i];
        float tmpFatJet_eta_One = FatJet_eta[i];
        float tmpFatJet_Tag_One = FatJet_deepTag_ZvsQCD[i];


        float tmpFatJetPT = FatJet_pt[i];
        if (debug) std::cout << "tmpFatJetPT " << tmpFatJetPT << "\n";

        if (tmpFatJet_Tag_One > fatJetZTagCut && tmpFatJetPT > fatJetPTCut){
            //Looping through all jets past the current one
            for (UInt_t j=i+1;j<numFatJet;j++){
                if (debug) std::cout << "Second FatJet " << j << "\n";

                //Skip selected higgs fatjet
                //if (j == hFatJet_ind_fromHParticleNet) continue;

                float tmpFatJet_phi_Two = FatJet_phi[j];
                float tmpFatJet_eta_Two = FatJet_eta[j];
                float tmpFatJet_Tag_Two = FatJet_deepTag_ZvsQCD[j];

                //Getting PT of the second jet
                float tmpFatJetPTTwo = FatJet_pt[j];

                if (debug) std::cout << "tmpFatJetPTTwo " << tmpFatJetPTTwo << "\n";

                //Checking if it passes the pt cut and tag cut
                if (tmpFatJet_Tag_Two > fatJetZTagCut && tmpFatJetPTTwo > fatJetPTCut){
                    //float tmpZPairPlusH_pt = HFJ_pt + tmpFatJetPT + tmpFatJetPTTwo;
                    //if (tmpZPairPlusH_pt > fatJetZPlusHPTCut){
                    if (true){
                        if (debug) std::cout << "Passed all cuts!!!!!!!!!!!!!!\n";
                        
                        //Selecting on top jet pt first
                        float tmpMaxPtLead = 0;
                        float tmpMaxPtSecond = 0;
                        float tmpMaxTagLead = 0;
                        float tmpMaxTagSecond = 0;
                        UInt_t tmpFJLeadInd=0;
                        UInt_t tmpFJTrailingInd=0;
                        //Sorting which jet has the larger pt
                        if (tmpFatJetPT > tmpFatJetPTTwo){
                            tmpMaxPtLead = tmpFatJetPT;
                            tmpMaxPtSecond = tmpFatJetPTTwo;
                            tmpMaxTagLead = tmpFatJet_Tag_One;
                            tmpMaxTagSecond = tmpFatJet_Tag_Two;
                            tmpFJLeadInd = i;
                            tmpFJTrailingInd = j;

                        }
                        else{
                            tmpMaxPtLead = tmpFatJetPTTwo;
                            tmpMaxPtSecond = tmpFatJetPT;
                            tmpMaxTagLead = tmpFatJet_Tag_Two;
                            tmpMaxTagSecond = tmpFatJet_Tag_One;
                            tmpFJLeadInd = j;
                            tmpFJTrailingInd = i;
                        }

                        //Selecting based on that jet's tag value
                        if (tmpMaxTagLead > leadFatJetMaxTag){
                            leadFatJetMaxTag = tmpMaxTagLead;
                            secondFatJetMaxTag = tmpMaxTagSecond;

                            leadFatJet_phi = FatJet_phi[tmpFJLeadInd];
                            leadFatJet_eta = FatJet_eta[tmpFJLeadInd];
                            secondFatJet_phi = FatJet_phi[tmpFJTrailingInd];
                            secondFatJet_eta = FatJet_eta[tmpFJTrailingInd];

                            LFJOneInd = tmpFJLeadInd;
                            LFJTwoInd = tmpFJTrailingInd;
                        }
                        //If that jet is already part of the current selected pair,
                        //select based on the respective lower pt jets in the pairs
                        else if (tmpMaxTagLead == leadFatJetMaxTag){
                            if (tmpMaxTagSecond > secondFatJetMaxTag){
                                secondFatJetMaxTag = tmpMaxTagSecond;

                                leadFatJet_phi = FatJet_phi[tmpFJLeadInd];
                                leadFatJet_eta = FatJet_eta[tmpFJLeadInd];
                                secondFatJet_phi = FatJet_phi[tmpFJTrailingInd];
                                secondFatJet_eta = FatJet_eta[tmpFJTrailingInd];


                                LFJOneInd = tmpFJLeadInd;
                                LFJTwoInd = tmpFJTrailingInd;
                                
                            }
                        }
                    }
                }
            }
        }
    }
}



void getIsoVars(bool Z1IsMuon,float Z1LeadPt,TTreeReaderArray<Float_t> &Electron_etaL,std::vector<UInt_t> elecCandIndAr,Int_t Z1LeadItr,TTreeReaderArray<Float_t> &Electron_dr03EcalRecHitSumEtL,TTreeReaderArray<Float_t> &Electron_dr03TkSumPtL,TTreeReaderArray<Float_t> &Electron_dr03HcalDepth1TowerSumEtL,TTreeReaderArray<Float_t> &Electron_ptL,TTreeReaderArray<Float_t> &Electron_pfRelIso03_allL,
Int_t Z1TrailingItr,float &Z1LeadIso,float Z1TrailingPt,TTreeReaderArray<Float_t> &Muon_pfRelIso03_allL,std::vector<UInt_t> muonCandIndAr,float &Z1TrailingIso,bool Z2IsMuon,std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr,Int_t tmpZ2Ind,float &Z2LeadIso,float &Z2TrailingIso,float tmpTopZ2LeadPt,float tmpTopZ2TrailingPt,std::vector<std::array<UInt_t,2>> muonPassesZ2CutsFinalAr,bool debug) {
    float tmpIso = 0;
    
    float tmpPt;
    float tmpAdd;
    

    if (!Z1IsMuon){
        if (debug) std::cout << "In first if\n";
        tmpPt = Z1LeadPt;
        if (tmpPt > 35){
            if (debug) std::cout << "lead pt > 35\n";
            if (abs(Electron_etaL[elecCandIndAr[Z1LeadItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1LeadItr]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1LeadItr]];
            tmpIso = ( Electron_dr03TkSumPtL[elecCandIndAr[Z1LeadItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecCandIndAr[Z1LeadItr]] ) / Electron_ptL[elecCandIndAr[Z1LeadItr]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecCandIndAr[Z1LeadItr]];
        
        Z1LeadIso = tmpIso;
        if (debug) std::cout << "Got Z1 Lead Iso\n";
        
        tmpPt = Z1TrailingPt;
        if (tmpPt > 35){
            if (debug) std::cout << "trailing pt > 35\n";
            if (abs(Electron_etaL[elecCandIndAr[Z1TrailingItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1TrailingItr]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1TrailingItr]];
            tmpIso = ( Electron_dr03TkSumPtL[elecCandIndAr[Z1TrailingItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecCandIndAr[Z1LeadItr]] ) / Electron_ptL[elecCandIndAr[Z1LeadItr]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecCandIndAr[Z1TrailingItr]];
        Z1TrailingIso = tmpIso;
    }
    else{
        if (debug) std::cout << "getting Z1 muon Isos\n";
        Z1LeadIso = Muon_pfRelIso03_allL[muonCandIndAr[Z1LeadItr]];
        Z1TrailingIso = Muon_pfRelIso03_allL[muonCandIndAr[Z1TrailingItr]];
        //Z1LeadIso = mIso[muonCandIndAr[Z1LeadItr]]
        //Z1TrailingIso = mIso[muonCandIndAr[Z1TrailingItr]]
    }
    if (debug) std::cout << "Now Z2\n";
    if (!Z2IsMuon){
        if (debug) std::cout << "In first Z2 if\n";
        //Z2LeadIso = eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
        //Z2TrailingIso = eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]

        tmpPt = tmpTopZ2LeadPt;
        if (tmpPt > 35){
            if (debug) std::cout << "Z2 lead pt > 35\n";
            /*
            if (debug) std::cout << "tmpZ2Ind " << tmpZ2Ind << "\n";
            if (debug) std::cout << "elecPassesZ2CutsAr[tmpZ2Ind][0] " << elecPassesZ2CutsAr[tmpZ2Ind][0] << "\n";
            if (debug) std::cout << "Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
            if (debug) std::cout << "abs(Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][0]]) " << abs(Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][0]]) << "\n";
            if (debug) std::cout << "Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
            if (debug) std::cout << "Electron_dr03TkSumPtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03TkSumPtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
            if (debug) std::cout << "Electron_dr03HcalDepth1TowerSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03HcalDepth1TowerSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
            if (debug) std::cout << "Electron_ptL[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_ptL[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
            */



            if (abs(Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][0]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]];
            tmpIso = ( Electron_dr03TkSumPtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][0]] ) / Electron_ptL[elecPassesZ2CutsAr[tmpZ2Ind][0]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecPassesZ2CutsAr[tmpZ2Ind][0]];
        if (debug) std::cout << "Got Z2 Lead Iso\n";
        Z2LeadIso = tmpIso;
        if (debug) std::cout << "Got Z2 Lead Iso\n";

        
        tmpPt = tmpTopZ2TrailingPt;
        if (tmpPt > 35){
            if (debug) std::cout << "Z2 trailing pt > 35\n";
            if (abs(Electron_etaL[elecPassesZ2CutsAr[tmpZ2Ind][1]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][1]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][1]];
            tmpIso = ( Electron_dr03TkSumPtL[elecPassesZ2CutsAr[tmpZ2Ind][1]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecPassesZ2CutsAr[tmpZ2Ind][1]] ) / Electron_ptL[elecPassesZ2CutsAr[tmpZ2Ind][1]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecPassesZ2CutsAr[tmpZ2Ind][1]];
        Z2TrailingIso = tmpIso;
        if (debug) std::cout << "Got Z2 trailing Iso\n";
    }

    else{
        if (debug) std::cout << "getting Z2 muon Isos\n";
        Z2LeadIso = Muon_pfRelIso03_allL[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]];
        Z2TrailingIso = Muon_pfRelIso03_allL[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]];
    }

}

void getSemiLepIsoVars(bool Z1IsMuon,float Z1LeadPt,TTreeReaderArray<Float_t> &Electron_etaL,std::vector<UInt_t> elecCandIndAr,Int_t Z1LeadItr,TTreeReaderArray<Float_t> &Electron_dr03EcalRecHitSumEtL,TTreeReaderArray<Float_t> &Electron_dr03TkSumPtL,TTreeReaderArray<Float_t> &Electron_dr03HcalDepth1TowerSumEtL,TTreeReaderArray<Float_t> &Electron_ptL,TTreeReaderArray<Float_t> &Electron_pfRelIso03_allL,
Int_t Z1TrailingItr,float &Z1LeadIso,float Z1TrailingPt,TTreeReaderArray<Float_t> &Muon_pfRelIso03_allL,std::vector<UInt_t> muonCandIndAr,float &Z1TrailingIso,bool debug) {
    float tmpAdd;
    float tmpIso = 0;
    
    if (!Z1IsMuon){
        if (debug) std::cout << "D01 \n";
        if (Z1LeadPt > 35){
            if (debug) std::cout << "D02 \n";
            if (abs(Electron_etaL[elecCandIndAr[Z1LeadItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1LeadItr]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1LeadItr]];
            tmpIso = ( Electron_dr03TkSumPtL[elecCandIndAr[Z1LeadItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecCandIndAr[Z1LeadItr]] ) / Electron_ptL[elecCandIndAr[Z1LeadItr]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecCandIndAr[Z1LeadItr]];
        Z1LeadIso = tmpIso;
    
        if (Z1TrailingPt > 35){
            if (debug) std::cout << "D03 \n";
            if (abs(Electron_etaL[elecCandIndAr[Z1TrailingItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1TrailingItr]] - 1.);
            else tmpAdd = Electron_dr03EcalRecHitSumEtL[elecCandIndAr[Z1TrailingItr]];
            tmpIso = ( Electron_dr03TkSumPtL[elecCandIndAr[Z1TrailingItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEtL[elecCandIndAr[Z1LeadItr]] ) / Electron_ptL[elecCandIndAr[Z1LeadItr]];
        }
        else tmpIso = Electron_pfRelIso03_allL[elecCandIndAr[Z1TrailingItr]];
        Z1TrailingIso = tmpIso;
    }
    else{
        if (debug) std::cout << "D04 \n";
        if (debug) std::cout << "Z1LeadItr " << Z1LeadItr << "\n";
        if (debug) std::cout << "muonCandIndAr[Z1LeadItr]" << muonCandIndAr[Z1LeadItr] << "\n";
        Z1LeadIso = Muon_pfRelIso03_allL[muonCandIndAr[Z1LeadItr]];
        Z1TrailingIso = Muon_pfRelIso03_allL[muonCandIndAr[Z1TrailingItr]];
    }
}



void postZ2DebugOut(std::vector<UInt_t> elecCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> elecCandVecAr,std::vector<Int_t> elecCandChargeAr,
std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr,std::vector<std::array<UInt_t,2>> elecPassesZ2CutsFinalAr,
std::vector<UInt_t> muonCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> muonCandVecAr,std::vector<Int_t> muonCandChargeAr,
std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr,std::vector<std::array<UInt_t,2>> muonPassesZ2CutsFinalAr) {
    std::vector<float> tmpPtAr;
    std::vector<ROOT::Math::PtEtaPhiMVector> tmpVecAr;
    //for elecCandInd in elecCandIndAr:
    std::cout << "elecCandIndAr loop\n";
    for (UInt_t elecCandIndInd=0; elecCandIndInd<elecCandIndAr.size();elecCandIndInd++){
        cout << "elecCandIndInd " << elecCandIndInd << "elecCandIndAr[elecCandIndInd]" << elecCandIndAr[elecCandIndInd] << "\n";

    }
    std::cout << "elecCandChargeAr loop\n";
    for (UInt_t elecCandChargeInd=0; elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
        cout << "elecCandChargeInd " << elecCandChargeInd << "elecCandChargeAr[elecCandChargeInd]" << elecCandChargeAr[elecCandChargeInd] << "\n";
    }
    std::cout << "elecCandVecAr loop\n";
    if (elecCandVecAr.size()){
        for (UInt_t elecCandVecItrOne=0; elecCandVecItrOne<elecCandVecAr.size()-1; elecCandVecItrOne++){
            std::cout << "elecCandVecItrOne " << elecCandVecItrOne << " elecCandVecOne " << elecCandVecAr[elecCandVecItrOne] << "\n";
            for (UInt_t elecCandVecItrTwo=elecCandVecItrOne+1; elecCandVecItrTwo<elecCandVecAr.size(); elecCandVecItrTwo++){
                std::cout << "elecCandVecItrTwo " << elecCandVecItrTwo << " elecCandVecTwo " << elecCandVecAr[elecCandVecItrTwo] << "\n";
                ROOT::Math::PtEtaPhiMVector tmpVecSum = elecCandVecAr[elecCandVecItrOne]+elecCandVecAr[elecCandVecItrTwo];
                std::cout << tmpVecSum << "\n";
                std::cout << tmpVecSum.M() << "\n";
            }
        }
    }
    
    std::cout << "elecPassesZ2CutsAr loop\n";
    for (UInt_t elecPassesZ2CutsInd=0; elecPassesZ2CutsInd<elecPassesZ2CutsAr.size(); elecPassesZ2CutsInd++){
        std::cout << "elecPassesZ2CutsInd " << elecPassesZ2CutsInd << "elecPassesZ2CutsAr[elecPassesZ2CutsInd][0] " << elecPassesZ2CutsAr[elecPassesZ2CutsInd][0] << "\n";
        std::cout << "elecPassesZ2CutsInd " << elecPassesZ2CutsInd << "elecPassesZ2CutsAr[elecPassesZ2CutsInd][1] " << elecPassesZ2CutsAr[elecPassesZ2CutsInd][1] << "\n";

    }

    std::cout << "elecPassesZ2CutsFinalAr loop\n";
    for (UInt_t elecPassesZ2CutsFinalInd=0; elecPassesZ2CutsFinalInd<elecPassesZ2CutsFinalAr.size();elecPassesZ2CutsFinalInd++){
        std::cout << "elecPassesZ2CutsFinalInd " << elecPassesZ2CutsFinalInd << "elecPassesZ2CutsFinalAr[elecPassesZ2CutsFinalInd][0]" << elecPassesZ2CutsFinalAr[elecPassesZ2CutsFinalInd][0] << "\n";

    }


    std::cout << "muonCandIndAr loop\n";
    for (UInt_t muonCandIndInd=0; muonCandIndInd<muonCandIndAr.size();muonCandIndInd++){
        std::cout << "muonCandIndInd " << muonCandIndInd << "muonCandIndAr[muonCandIndInd]" << muonCandIndAr[muonCandIndInd] << "\n";

    }
    std::cout << "muonCandChargeAr loop\n";
    for (UInt_t muonCandChargeInd=0; muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
        std::cout << "muonCandChargeInd " << muonCandChargeInd << "muonCandChargeAr[muonCandChargeInd]" << muonCandChargeAr[muonCandChargeInd] << "\n";
    }
    std::cout <<"muonCandVecAr loop\n";
    if (muonCandVecAr.size()) {
        for (UInt_t muonCandVecItrOne=0; muonCandVecItrOne<muonCandVecAr.size()-1; muonCandVecItrOne++){
            std::cout <<"muonCandVecItrOne " << muonCandVecItrOne << " muonCandVecOne " << muonCandVecAr[muonCandVecItrOne] << "\n";
            for (UInt_t muonCandVecItrTwo=muonCandVecItrOne+1; muonCandVecItrTwo<muonCandVecAr.size(); muonCandVecItrTwo++){
                std::cout <<"muonCandVecItrTwo " << muonCandVecItrTwo << " muonCandVecTwo " << muonCandVecAr[muonCandVecItrTwo] << "\n";
                ROOT::Math::PtEtaPhiMVector tmpVecSum = muonCandVecAr[muonCandVecItrOne]+muonCandVecAr[muonCandVecItrTwo];
                std::cout <<tmpVecSum << "\n";
                std::cout <<tmpVecSum.M() << "\n";
            }
        }
    }
    //std::cout <<"muonPassesZ2CutsAr " << muonPassesZ2CutsAr << "\n";
    std::cout << "muonPassesZ2CutsAr loop\n";
    for (UInt_t muonPassesZ2CutsInd=0; muonPassesZ2CutsInd<muonPassesZ2CutsAr.size();muonPassesZ2CutsInd++){
        std::cout << "muonPassesZ2CutsInd " << muonPassesZ2CutsInd << "muonPassesZ2CutsAr[muonPassesZ2CutsInd][0]" << muonPassesZ2CutsAr[muonPassesZ2CutsInd][0] << "\n";

    }

    //std::cout <<"muonPassesZ2CutsFinalAr " << muonPassesZ2CutsFinalAr << "\n";
    std::cout << "muonPassesZ2CutsFinalAr loop\n";
    for (UInt_t muonPassesZ2CutsFinalInd=0; muonPassesZ2CutsFinalInd<muonPassesZ2CutsFinalAr.size();muonPassesZ2CutsFinalInd++){
        std::cout << "muonPassesZ2CutsFinalInd " << muonPassesZ2CutsFinalInd << "muonPassesZ2CutsFinalAr[muonPassesZ2CutsFinalInd][0]" << muonPassesZ2CutsFinalAr[muonPassesZ2CutsFinalInd][0] << "\n";

    }
}

void dolZ1CutWithTree(TTreeReaderArray<Float_t> &Lep_pt,std::vector<UInt_t> lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,std::vector<Int_t> lepCandChargeAr,std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsAr,bool &Z1IsMuon,bool forMuon,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,float &tmpTopZ1LeadPt,float &tmpTopZ1TrailingPt,Int_t &tmpTopLeadItr,Int_t &tmpTopTrailingItr,ROOT::Math::PtEtaPhiMVector &tmpTopLeadVec,ROOT::Math::PtEtaPhiMVector &tmpTopTrailingVec,Int_t &tmpTopLeadCharge,Int_t &tmpTopTrailingCharge,float &difFromZMassOne,std::vector<Float_t> &SemiLepOrLepInvMass,bool debug){
    if (debug) std::cout << "in dolZ1Cut fcn\n";
    for (UInt_t lItrOne=0; lItrOne<lepCandIndAr.size()-1; lItrOne++) { //LEP LOOP ONE
        Int_t tmpChargeOne = lepCandChargeAr[lItrOne];
        if (debug) std::cout << "lItrOne " << lItrOne << " lepCandIndAr[lItrOne] " << lepCandIndAr[lItrOne] << " tmpChargeOne " << tmpChargeOne << "\n";
        for (UInt_t lItrTwo=lItrOne+1; lItrTwo<lepCandIndAr.size(); lItrTwo++){ //LEP LOOP TWO
            Int_t tmpChargeTwo = lepCandChargeAr[lItrTwo];
            if (debug) std::cout << "lItrTwo " << lItrTwo << " lepCandIndAr[lItrTwo] " << lepCandIndAr[lItrTwo] << " tmpChargeOne " << tmpChargeTwo << "\n";
            if (tmpChargeOne != tmpChargeTwo){ //CHECK IF OPPOSITE CHARGE
                ROOT::Math::PtEtaPhiMVector tmpZ1VecOne = lepCandVecAr[lItrOne];
                ROOT::Math::PtEtaPhiMVector tmpZ1VecTwo = lepCandVecAr[lItrTwo];
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo;
                float tmpZ1Mass = tmpZ1Vec.M();
                if (debug){
                    std::cout << "not the same charge. yay\n";
                    std::cout << "tmpZ1VecOne " << tmpZ1VecOne << "tmpZ1VecTwo " << tmpZ1VecTwo << "tmpZ1Vec " << tmpZ1Vec << "\n";
                }
                SemiLepOrLepInvMass.push_back(tmpZ1Mass);
                if (tmpZ1Mass > invMassCutLow && tmpZ1Mass < invMassCutHigh){ //CHECK IF INV MASS PASSES CUTS
                    if (debug) std::cout << "Passed inv mass cut\n";
                    float tmpZDif = abs(tmpZ1Mass - ZMass);
                    float tmpPtOne = Lep_pt[lepCandIndAr[lItrOne]];
                    float tmpPtTwo = Lep_pt[lepCandIndAr[lItrTwo]];
                    if (debug) std::cout << "tmpZDif " << tmpZDif << "tmpPtOne " << tmpPtOne << "tmpPtTwo " << tmpPtTwo << "\n";
                    float tmpPtLead;
                    float tmpPtTrailing;
                    UInt_t tmpLeadItr;
                    UInt_t tmpTrailingItr;
                    ROOT::Math::PtEtaPhiMVector tmpLeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpTrailingVec;
                    Int_t tmpLeadCharge;
                    Int_t tmpTrailingCharge;
                    if (tmpPtOne >= tmpPtTwo){ //SORT PTS
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrOne],lepCandIndAr[lItrTwo]])
                        tmpPtLead = tmpPtOne;
                        tmpPtTrailing = tmpPtTwo;
                        tmpLeadItr = lItrOne;
                        tmpTrailingItr = lItrTwo;
                        tmpLeadVec = tmpZ1VecOne;
                        tmpTrailingVec = tmpZ1VecTwo;
                        tmpLeadCharge = tmpChargeOne;
                        tmpTrailingCharge = tmpChargeTwo;
                    }
                    else{
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrTwo],lepCandIndAr[lItrOne]])
                        tmpPtLead = tmpPtTwo;
                        tmpPtTrailing = tmpPtOne;
                        tmpLeadItr = lItrTwo;
                        tmpTrailingItr = lItrOne;
                        tmpLeadVec = tmpZ1VecTwo;
                        tmpTrailingVec = tmpZ1VecOne;
                        tmpLeadCharge = tmpChargeTwo;
                        tmpTrailingCharge = tmpChargeOne;
                    }


                    if (tmpZDif < difFromZMassOne){ //CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                        if (debug) std::cout << "current smallest zdif yay\n";
                        
                        if (tmpPtLead > ptLeadCut && tmpPtTrailing > ptTrailingCut){ //CHECK IF PASSES PT CUT
                            if (debug) std::cout << "wow it passed the pt cut also yay\n";
                            tmpTopZ1LeadPt = tmpPtLead;
                            tmpTopZ1TrailingPt = tmpPtTrailing;
                            difFromZMassOne = tmpZDif;
                            tmpTopLeadItr = tmpLeadItr;
                            tmpTopTrailingItr = tmpTrailingItr;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            if (!forMuon) Z1IsMuon = false;
                            else Z1IsMuon = true;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            tmpTopLeadVec = tmpLeadVec;
                            tmpTopTrailingVec = tmpTrailingVec;
                            tmpTopLeadCharge = tmpLeadCharge;
                            tmpTopTrailingCharge = tmpTrailingCharge;
                        }
                    }
                    std::array<UInt_t,2> tmpItrList = {tmpLeadItr,tmpTrailingItr};
                    lepPassesZ2CutsAr.push_back(tmpItrList);
                    
                }
            }
        }
    }
}

void doLeptonicCutsWithTree(TTreeReaderArray<Float_t> &Electron_etaL,TTreeReaderArray<Float_t> &Electron_massL,TTreeReaderArray<Int_t> &Electron_chargeL,TTreeReaderArray<Float_t> &Electron_phiL,TTreeReaderArray<Float_t> &Electron_ptL,UInt_t neLep,std::vector<UInt_t> &elecCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &elecCandVecAr,std::vector<Int_t> &elecCandChargeAr,UInt_t &negElecCands,UInt_t &posElecCands,UInt_t &totElecCands,bool &enoughElecCands,UInt_t &negMuonCands,UInt_t &posMuonCands,UInt_t &totMuonCands,bool &enoughMuonCands,bool &enoughLepCands,float ePtCut,float eEtaCut,
TTreeReaderArray<Float_t> &Muon_etaL,TTreeReaderArray<Float_t> &Muon_massL,TTreeReaderArray<Int_t> &Muon_chargeL,TTreeReaderArray<Float_t> &Muon_phiL,TTreeReaderArray<Float_t> &Muon_ptL,UInt_t nmLep,std::vector<UInt_t> &muonCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &muonCandVecAr,std::vector<Int_t> &muonCandChargeAr,


TTreeReaderArray<Float_t> &Electron_DxyL,TTreeReaderArray<Float_t> &Electron_DzL,TTreeReaderArray<Float_t> &Electron_MiniPFRelIsoL,TTreeReaderArray<Float_t> &Electron_sieieL,TTreeReaderArray<Float_t> &Electron_hoeL,TTreeReaderArray<Float_t> &Electron_eInvMinusPInvL,TTreeReaderArray<Bool_t> &Electron_convVetoL,TTreeReaderArray<UChar_t> &Electron_lostHitsL,TTreeReaderArray<Int_t> &Electron_jetIdxL,TTreeReaderArray<Float_t> &Jet_btagDeepFlavBL,TTreeReaderArray<Float_t> &Electron_mvaTTHL,

TTreeReaderArray<Float_t> &Muon_DxyL,TTreeReaderArray<Float_t> &Muon_DzL,TTreeReaderArray<Float_t> &Muon_MiniPFRelIsoL,TTreeReaderArray<Float_t> &Muon_mvaTTHL,TTreeReaderArray<Int_t> &Muon_jetIdxL,

float lDxyCut,float lDzCut,float lMiniPFRelIsoCut,float eSieieBarrelCut,float eSieieEndcapCut,float eHoeCut,float eInvMinusPInvCut,UInt_t eLostHitsCut,float lepJetDeepTagLooseCut,float lepJetDeepTagMediumCut,float ePromptMVACut,float mPromptMVACut,
float mPtCut,float mEtaCut,
bool &Z1IsMuon,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,
float &Z1LeadPt,float &Z1TrailingPt,Int_t &Z1LeadItr,Int_t &Z1TrailingItr,ROOT::Math::PtEtaPhiMVector &Z1LeadVec,ROOT::Math::PtEtaPhiMVector &Z1TrailingVec,Int_t &Z1LeadCharge,Int_t &Z1TrailingCharge,float &difFromZMassOne,
std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> eZ2VecPairAr,Int_t &tmpZ2Ind,bool &Z2IsMuon,float &tmpTopZ2LeadPt,float &tmpTopZ2TrailingPt,float fourLepInvMassCut,float optLepInvMassCut,
std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> mZ2VecPairAr,
ROOT::Math::PtEtaPhiMVector &tmpZ1Vec,float &tmpZ1M,
TTreeReaderArray<Float_t> &Electron_dr03EcalRecHitSumEtL,TTreeReaderArray<Float_t> &Electron_dr03TkSumPtL,TTreeReaderArray<Float_t> &Electron_dr03HcalDepth1TowerSumEtL,TTreeReaderArray<Float_t> &Electron_pfRelIso03_allL,
float &Z1LeadIso,TTreeReaderArray<Float_t> &Muon_pfRelIso03_allL,float &Z1TrailingIso,float &Z2LeadIso,float &Z2TrailingIso,float lepIsoCut,
float &Z1LeadSIP,TTreeReaderArray<Float_t> &Electron_sip3dL,float &Z1TrailingSIP,float &Z2LeadSIP,TTreeReaderArray<Float_t> &Muon_sip3dL,float &Z2TrailingSIP,float SIPCut,UInt_t &passLepCut,bool &passesCutsBool, bool &passedAsLepBool,
std::vector<Float_t> &LepInvMass,
TTreeReaderArray<Bool_t> &Elec_IdL,TTreeReaderArray<Bool_t> &Muon_IdL,
std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,
bool debug
) {
    if (neLep){
        if (debug) std::cout << "Doing elec cand cut\n";
        dolCandCutWithID(Elec_IdL,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,Electron_DxyL,Electron_DzL,Electron_sip3dL,Electron_MiniPFRelIsoL,Electron_sieieL,Electron_hoeL,Electron_eInvMinusPInvL,Electron_convVetoL,Electron_lostHitsL,Electron_jetIdxL,Jet_btagDeepFlavBL,Electron_mvaTTHL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,lDxyCut,lDzCut,lMiniPFRelIsoCut,eSieieBarrelCut,eSieieEndcapCut,eHoeCut,eInvMinusPInvCut,eLostHitsCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,ePromptMVACut,SIPCut,false,debug);
        //doeCandCut(Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut);
        for (UInt_t elecCandChargeInd=0;elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
            if (elecCandChargeAr[elecCandChargeInd] == -1) negElecCands += 1;
            else posElecCands += 1;
        }
        totElecCands = std::min(negElecCands,posElecCands);
        if (totElecCands >= 1) enoughElecCands = true;
    }


    
    
    if (debug){
        std::cout << "--------------------------------------------\n";
        std::cout << "neLep " << neLep << "\n";
        for (UInt_t tmpItr=0; tmpItr < neLep; tmpItr++){
            std::cout <<"tmpItr " << tmpItr << " Electron_ptL[tmpItr] " << Electron_ptL[tmpItr] << " Electron_etaL[tmpItr] " << Electron_etaL[tmpItr] << " Electron_chargeL[tmpItr] " << Electron_chargeL[tmpItr] << "\n";
        }
    }
    if (nmLep){
        if (debug) std::cout << "Doing muon cand cut\n";

        dolCandCutWithID(Muon_IdL,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,Muon_DxyL,Muon_DzL,Muon_sip3dL,Muon_MiniPFRelIsoL,Electron_sieieL,Electron_hoeL,Electron_eInvMinusPInvL,Electron_convVetoL,Electron_lostHitsL,Muon_jetIdxL,Jet_btagDeepFlavBL,Muon_mvaTTHL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,lDxyCut,lDzCut,lMiniPFRelIsoCut,eSieieBarrelCut,eSieieEndcapCut,eHoeCut,eInvMinusPInvCut,eLostHitsCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,mPromptMVACut,SIPCut,true,debug);

        //domCandCut(Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,neLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut);
        for (UInt_t muonCandChargeInd=0;muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
            if (muonCandChargeAr[muonCandChargeInd] == -1) negMuonCands += 1;
            else posMuonCands += 1;
        }
        totMuonCands = std::min(negMuonCands,posMuonCands);
        if (totMuonCands >= 1) enoughMuonCands = true;
    }

    enoughLepCands = false;
    if (totElecCands+totMuonCands >= 2) enoughLepCands = true;
    if (debug){
        std::cout << "negElecCands " << negElecCands << " posElecCands " << posElecCands << " totElecCands " << totElecCands << "\n";
        std::cout << "nmLep " << nmLep << " negMuonCands " << negMuonCands << " posMuonCands " << posMuonCands << " totMuonCands " << totMuonCands << "\n";
        std::cout << "enoughLepCands " << enoughLepCands << "\n";
    }
    
    

    

    if (enoughLepCands){ //Check there are enough lep cands after candidate cuts
        //passesCandCutsCtr += 1
        std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr;
        if (enoughElecCands){ //If enough elec cands, run Z1 cuts
            dolZ1CutWithTree(Electron_ptL,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,false,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,LepInvMass,debug);
        }
        std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr;
        if (enoughMuonCands){ //If enough muon cands, run Z1 cuts
            dolZ1CutWithTree(Muon_ptL,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,true,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,LepInvMass,debug);
        }
        if (debug) std::cout <<"Z1LeadItr " << Z1LeadItr << " Z1TrailingItr " << Z1TrailingItr << " Z1LeadPt " << Z1LeadPt << " Z1TrailingPt " << Z1TrailingPt << " Z1LeadVec " << Z1LeadVec << " Z1TrailingVec " << Z1TrailingVec << " Z1LeadCharge " << Z1LeadCharge << " Z1TrailingCharge " << Z1TrailingCharge << " Z1IsMuon " << Z1IsMuon << " difFromZMassOne " << difFromZMassOne << "\n";
        if (Z1LeadItr >= 0) { //If Z1 found
            //passesZ1CutsCtr += 1
            if (debug) std::cout <<"passed Z1 cut. checking for enough Z2 now\n";

            std::vector<std::array<UInt_t,2>> elecPassesZ2CutsFinalAr;
                
            
            std::vector<std::array<double,2>> eZ2PtPairAr;
            std::vector<std::array<Int_t,2>> eZ2ChargePairAr;
            bool tmpIgnore;
            if (!Z1IsMuon) tmpIgnore = true;
            else tmpIgnore = false;
            std::array<Int_t,2> indsToIgnore = {Z1LeadItr,Z1TrailingItr};
            bool eZ2CandsBool = false;
            bool mZ2CandsBool = false;
                

            fillZ2Ars(elecPassesZ2CutsFinalAr,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,elecPassesZ2CutsAr,elecCandChargeAr,elecCandVecAr,tmpIgnore,indsToIgnore,eZ2CandsBool);

            std::vector<std::array<UInt_t,2>> muonPassesZ2CutsFinalAr;
                
            
            std::vector<std::array<double,2>> mZ2PtPairAr;
            std::vector<std::array<Int_t,2>> mZ2ChargePairAr;
            fillZ2Ars(muonPassesZ2CutsFinalAr,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,muonPassesZ2CutsAr,muonCandChargeAr,muonCandVecAr,!tmpIgnore,indsToIgnore,mZ2CandsBool);


            if (debug){
                postZ2DebugOut(elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,elecPassesZ2CutsFinalAr,
                muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,muonPassesZ2CutsFinalAr);

            }


            //if (elecPassesZ2CutsFinalAr || muonPassesZ2CutsFinalAr){
            if (eZ2CandsBool || mZ2CandsBool) {
                if (debug) std::cout << "passed to Z2 Cut\n";
                tmpZ2Ind = -1;
                Z2IsMuon = false;
                tmpTopZ2LeadPt = 0;
                tmpTopZ2TrailingPt = 0;
                tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
                tmpZ1M = tmpZ1Vec.M();

                
                if (eZ2CandsBool) dolZ2Cut(Z1LeadVec,Z1TrailingVec,tmpZ1Vec,tmpZ1M,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,true);
                if (mZ2CandsBool) dolZ2Cut(Z1LeadVec,Z1TrailingVec,tmpZ1Vec,tmpZ1M,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,false);
                if (debug) std::cout << "tmpZ2Ind " << tmpZ2Ind << " Z2IsMuon " << Z2IsMuon << " tmpTopZ2LeadPt " << tmpTopZ2LeadPt << " tmpTopZ2TrailingPt " << tmpTopZ2TrailingPt << "\n";
                if (tmpZ2Ind >= 0){ //Passed Z2 Cut
                    if (debug) std::cout << "passed Z2 cut\n";
                    //passesZ2CutsCtr += 1
                    getIsoVars(Z1IsMuon,Z1LeadPt,Electron_etaL,elecCandIndAr,Z1LeadItr,Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_ptL,Electron_pfRelIso03_allL,
                    Z1TrailingItr,Z1LeadIso,Z1TrailingPt,Muon_pfRelIso03_allL,muonCandIndAr,Z1TrailingIso,Z2IsMuon,elecPassesZ2CutsAr,tmpZ2Ind,Z2LeadIso,Z2TrailingIso,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,muonPassesZ2CutsFinalAr,debug);
                    if (debug) std::cout << "Z1LeadIso " << Z1LeadIso << " Z1TrailingIso " << Z1TrailingIso << " Z2LeadIso " << Z2LeadIso << " Z2TrailingIso " << Z2TrailingIso << "\n";

                    
                    bool passIsoCut = doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut);

                    if (passIsoCut){
                        
                        if (debug) std::cout << "passed iso cut yay\n";
                        //passesIsoCutCtr += 1
                    
                        passLepCut += 1;
                        passesCutsBool = true;
                        passedAsLepBool = true;
                        dRCheckVecAr.push_back(Z1LeadVec);
                        dRCheckVecAr.push_back(Z1TrailingVec);
                        ROOT::Math::PtEtaPhiMVector tmpZ2LeadVec;
                        ROOT::Math::PtEtaPhiMVector tmpZ2TrailingVec;
                        if (Z2IsMuon){
                            dRCheckVecAr.push_back(mZ2VecPairAr[tmpZ2Ind][0]);
                            dRCheckVecAr.push_back(mZ2VecPairAr[tmpZ2Ind][1]);

                        }
                        else {
                            dRCheckVecAr.push_back(eZ2VecPairAr[tmpZ2Ind][0]);
                            dRCheckVecAr.push_back(eZ2VecPairAr[tmpZ2Ind][1]);
                        }
                    
                    }

                }

            }
                                
                            
        }
    }

}

void doSemiLepCutWithTree(bool &enoughElecCands,UInt_t &negElecCands,UInt_t &posElecCands,UInt_t &totElecCands,TTreeReaderArray<Float_t> &Electron_etaL,TTreeReaderArray<Float_t> &Electron_massL,TTreeReaderArray<Int_t> &Electron_chargeL,TTreeReaderArray<Float_t> &Electron_phiL,TTreeReaderArray<Float_t> &Electron_ptL,UInt_t neLep,std::vector<UInt_t> &elecCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &elecCandVecAr,std::vector<Int_t> &elecCandChargeAr,float ePtCut,float eEtaCut,
bool &enoughMuonCands,UInt_t &negMuonCands,UInt_t &posMuonCands,UInt_t &totMuonCands,TTreeReaderArray<Float_t> &Muon_etaL,TTreeReaderArray<Float_t> &Muon_massL,TTreeReaderArray<Int_t> &Muon_chargeL,TTreeReaderArray<Float_t> &Muon_phiL,TTreeReaderArray<Float_t> &Muon_ptL,UInt_t nmLep,std::vector<UInt_t> &muonCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &muonCandVecAr,std::vector<Int_t> &muonCandChargeAr,

float mPtCut,float mEtaCut,
bool &enoughLepCands,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,bool &Z1Cand,float &difFromZMassOne,Int_t &Z1LeadItr,Int_t &Z1TrailingItr,float &Z1LeadPt,float &Z1TrailingPt,bool &Z1IsMuon,ROOT::Math::PtEtaPhiMVector &Z1LeadVec,ROOT::Math::PtEtaPhiMVector &Z1TrailingVec,Int_t &Z1LeadCharge,Int_t &Z1TrailingCharge,
TTreeReaderArray<Float_t> &Electron_dr03EcalRecHitSumEtL,TTreeReaderArray<Float_t> &Electron_dr03TkSumPtL,TTreeReaderArray<Float_t> &Electron_dr03HcalDepth1TowerSumEtL,TTreeReaderArray<Float_t> &Electron_pfRelIso03_allL,
float &Z1LeadIso,TTreeReaderArray<Float_t> &Muon_pfRelIso03_allL,float &Z1TrailingIso,float lepIsoCut,
std::vector<Float_t> &SemiLepInvMass,
TTreeReaderArray<Bool_t> &Elec_IdL,TTreeReaderArray<Bool_t> &Muon_IdL,
std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,
bool &passedAsSemiLepLepCutBool,
bool debug){
    /*
    enoughElecCands = false;
    negElecCands = 0;
    posElecCands = 0;
    totElecCands = 0;
    elecCandIndAr.clear();
    elecCandVecAr.clear();
    elecCandChargeAr.clear();

    if (neLep){
        if (debug) std::cout << "Doing elec cand cut\n";
        dolCandCutWithID(Elec_IdL,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,debug);
        
        for (UInt_t elecCandChargeInd=0;elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
            if (debug) std::cout << "elecCandChargeInd " << elecCandChargeInd << " elecCandChargeAr[elecCandChargeInd] " << elecCandChargeAr[elecCandChargeInd] << "\n";
            if (elecCandChargeAr[elecCandChargeInd] == -1) negElecCands += 1;
            else posElecCands += 1;
        }
        totElecCands = std::min(negElecCands,posElecCands);
        if (totElecCands >= 1) enoughElecCands = true;
    }


    enoughMuonCands = false;
    negMuonCands = 0;
    posMuonCands = 0;
    totMuonCands = 0;
    muonCandIndAr.clear();
    muonCandVecAr.clear();
    muonCandChargeAr.clear();

    if (debug){
        std::cout << "--------------------------------------------\n";
        std::cout << "neLep " << neLep << "\n";
        for (UInt_t tmpItr=0; tmpItr < neLep; tmpItr++){
            std::cout <<"tmpItr " << tmpItr << " Electron_ptL[tmpItr] " << Electron_ptL[tmpItr] << " Electron_etaL[tmpItr] " << Electron_etaL[tmpItr] << " Electron_chargeL[tmpItr] " << Electron_chargeL[tmpItr] << "\n";
        }
    }
    if (nmLep){
        if (debug) std::cout << "Doing muon cand cut\n";

        dolCandCutWithID(Muon_IdL,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,debug);

        //domCandCut(Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,neLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut);
        for (UInt_t muonCandChargeInd=0;muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
            if (muonCandChargeAr[muonCandChargeInd] == -1) negMuonCands += 1;
            else posMuonCands += 1;
        }
        totMuonCands = std::min(negMuonCands,posMuonCands);
        if (totMuonCands >= 1) enoughMuonCands = true;
    }

    */
    enoughLepCands = false;
    
    if (totElecCands || totMuonCands) enoughLepCands = true;
    if (debug){
        std::cout << "negElecCands " << negElecCands << " posElecCands " << posElecCands << " totElecCands " << totElecCands << "\n";
        std::cout << "nmLep " << nmLep << " negMuonCands " << negMuonCands << " posMuonCands " << posMuonCands << " totMuonCands " << totMuonCands << "\n";
        std::cout << "enoughLepCands " << enoughLepCands << "\n";
    }
    
    
    if (enoughLepCands){ //Check there are enough lep cands after candidate cuts
        //passesCandCutsCtr += 1
        Z1Cand = false;
        difFromZMassOne = 1000.;
        Z1LeadItr = -1;
        Z1TrailingItr = -1;
        Z1LeadPt = 0.;
        Z1TrailingPt = 0.;
        Z1IsMuon = false;
        Z1LeadCharge = 0;
        Z1TrailingCharge = 0;
        Z1LeadIso = 0;
        Z1TrailingIso = 0;
        std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr;
        if (enoughElecCands){ //If enough elec cands, run Z1 cuts
        
            dolZ1CutWithTree(Electron_ptL,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,false,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,SemiLepInvMass,debug);
        }
        std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr;
        if (enoughMuonCands){ //If enough muon cands, run Z1 cuts
            dolZ1CutWithTree(Muon_ptL,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,true,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,SemiLepInvMass,debug);
        }
        if (debug) std::cout <<"Z1LeadItr " << Z1LeadItr << " Z1TrailingItr " << Z1TrailingItr << " Z1LeadPt " << Z1LeadPt << " Z1TrailingPt " << Z1TrailingPt << " Z1LeadVec " << Z1LeadVec << " Z1TrailingVec " << Z1TrailingVec << " Z1LeadCharge " << Z1LeadCharge << " Z1TrailingCharge " << Z1TrailingCharge << " Z1IsMuon " << Z1IsMuon << " difFromZMassOne " << difFromZMassOne << "\n";
        //if (Z1LeadItr<0) {
        //    std::cout << "ddntpass Z1LeadItr" << Z1LeadItr << "\n";
        //}
        if (Z1LeadItr >= 0) { //If Z1 found
            bool semiLepPassIso = false;
            getSemiLepIsoVars(Z1IsMuon,Z1LeadPt,Electron_etaL,elecCandIndAr,Z1LeadItr,Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_ptL,Electron_pfRelIso03_allL,
            Z1TrailingItr,Z1LeadIso,Z1TrailingPt, Muon_pfRelIso03_allL,muonCandIndAr,Z1TrailingIso,debug);
            semiLepPassIso = doSemiLepISOCut(Z1LeadIso,Z1TrailingIso,lepIsoCut);
            //if (!semiLepPassIso) {
            //    std::cout << "ddntpass semiLepPassIso" << semiLepPassIso << "\n";
            //}
            if (semiLepPassIso) {
                if (debug) std::cout << "Passed SemiLep lep cuts\n";
                dRCheckVecAr.push_back(Z1LeadVec);
                dRCheckVecAr.push_back(Z1TrailingVec);
                passedAsSemiLepLepCutBool = true;
                //std::cout << "PASSED ALL THE WAY!!!!\n";
                if (debug) {
                    std::cout << "Z1IsMuon " <<Z1IsMuon<< "\n";
                    std::cout << "elecCandIndAr size " << elecCandIndAr.size() << "\n";

                    std::cout << "muonCandIndAr loop " << muonCandIndAr.size() << "\n";
                    
                    for (UInt_t muonCandIndInd=0; muonCandIndInd<muonCandIndAr.size();muonCandIndInd++){
                        std::cout << "muonCandIndInd " << muonCandIndInd << "muonCandIndAr[muonCandIndInd]" << muonCandIndAr[muonCandIndInd] << "\n";

                    }
                }
            }

        }
    }
}

void doSemiLepCutWithTreeWithBDTVars(bool &enoughElecCands,UInt_t &negElecCands,UInt_t &posElecCands,UInt_t &totElecCands,TTreeReaderArray<Float_t> &Electron_etaL,TTreeReaderArray<Float_t> &Electron_massL,TTreeReaderArray<Int_t> &Electron_chargeL,TTreeReaderArray<Float_t> &Electron_phiL,TTreeReaderArray<Float_t> &Electron_ptL,UInt_t neLep,std::vector<UInt_t> &elecCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &elecCandVecAr,std::vector<Int_t> &elecCandChargeAr,float ePtCut,float eEtaCut,
bool &enoughMuonCands,UInt_t &negMuonCands,UInt_t &posMuonCands,UInt_t &totMuonCands,TTreeReaderArray<Float_t> &Muon_etaL,TTreeReaderArray<Float_t> &Muon_massL,TTreeReaderArray<Int_t> &Muon_chargeL,TTreeReaderArray<Float_t> &Muon_phiL,TTreeReaderArray<Float_t> &Muon_ptL,UInt_t nmLep,std::vector<UInt_t> &muonCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &muonCandVecAr,std::vector<Int_t> &muonCandChargeAr,

float mPtCut,float mEtaCut,
bool &enoughLepCands,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,bool &Z1Cand,float &difFromZMassOne,Int_t &Z1LeadItr,Int_t &Z1TrailingItr,float &Z1LeadPt,float &Z1TrailingPt,bool &Z1IsMuon,ROOT::Math::PtEtaPhiMVector &Z1LeadVec,ROOT::Math::PtEtaPhiMVector &Z1TrailingVec,Int_t &Z1LeadCharge,Int_t &Z1TrailingCharge,
TTreeReaderArray<Float_t> &Electron_dr03EcalRecHitSumEtL,TTreeReaderArray<Float_t> &Electron_dr03TkSumPtL,TTreeReaderArray<Float_t> &Electron_dr03HcalDepth1TowerSumEtL,TTreeReaderArray<Float_t> &Electron_pfRelIso03_allL,
float &Z1LeadIso,TTreeReaderArray<Float_t> &Muon_pfRelIso03_allL,float &Z1TrailingIso,float lepIsoCut,
std::vector<Float_t> &SemiLepInvMass,
TTreeReaderArray<Bool_t> &Elec_IdL,TTreeReaderArray<Bool_t> &Muon_IdL,
TTreeReaderArray<Float_t> &Electron_sip3dL,TTreeReaderArray<Float_t> &Muon_sip3dL,float &Z1LeadSIP,float &Z1TrailingSIP,
std::vector<ROOT::Math::PtEtaPhiMVector> &dRCheckVecAr,
bool &passedAsSemiLepLepCutBool,
float &selectedLeptons_InvMass,
bool debug){
    enoughLepCands = false;
    
    if (totElecCands || totMuonCands) enoughLepCands = true;
    if (debug){
        std::cout << "negElecCands " << negElecCands << " posElecCands " << posElecCands << " totElecCands " << totElecCands << "\n";
        std::cout << "nmLep " << nmLep << " negMuonCands " << negMuonCands << " posMuonCands " << posMuonCands << " totMuonCands " << totMuonCands << "\n";
        std::cout << "enoughLepCands " << enoughLepCands << "\n";
    }
    
    
    if (enoughLepCands){ //Check there are enough lep cands after candidate cuts
        //passesCandCutsCtr += 1
        Z1Cand = false;
        difFromZMassOne = 1000.;
        Z1LeadItr = -1;
        Z1TrailingItr = -1;
        Z1LeadPt = 0.;
        Z1TrailingPt = 0.;
        Z1IsMuon = false;
        Z1LeadCharge = 0;
        Z1TrailingCharge = 0;
        Z1LeadIso = 0;
        Z1TrailingIso = 0;
        std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr;
        if (enoughElecCands){ //If enough elec cands, run Z1 cuts
        
            dolZ1CutWithTree(Electron_ptL,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,false,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,SemiLepInvMass,debug);
        }
        std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr;
        if (enoughMuonCands){ //If enough muon cands, run Z1 cuts
            dolZ1CutWithTree(Muon_ptL,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,true,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,SemiLepInvMass,debug);
        }
        if (debug) std::cout <<"Z1LeadItr " << Z1LeadItr << " Z1TrailingItr " << Z1TrailingItr << " Z1LeadPt " << Z1LeadPt << " Z1TrailingPt " << Z1TrailingPt << " Z1LeadVec " << Z1LeadVec << " Z1TrailingVec " << Z1TrailingVec << " Z1LeadCharge " << Z1LeadCharge << " Z1TrailingCharge " << Z1TrailingCharge << " Z1IsMuon " << Z1IsMuon << " difFromZMassOne " << difFromZMassOne << "\n";
        //if (Z1LeadItr<0) {
        //    std::cout << "ddntpass Z1LeadItr" << Z1LeadItr << "\n";
        //}
        if (Z1LeadItr >= 0) { //If Z1 found
            bool semiLepPassIso = false;
            getSemiLepIsoVars(Z1IsMuon,Z1LeadPt,Electron_etaL,elecCandIndAr,Z1LeadItr,Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_ptL,Electron_pfRelIso03_allL,
            Z1TrailingItr,Z1LeadIso,Z1TrailingPt, Muon_pfRelIso03_allL,muonCandIndAr,Z1TrailingIso,debug);
            semiLepPassIso = doSemiLepISOCut(Z1LeadIso,Z1TrailingIso,lepIsoCut);
            //if (!semiLepPassIso) {
            //    std::cout << "ddntpass semiLepPassIso" << semiLepPassIso << "\n";
            //}
            if (semiLepPassIso) {
                if (debug) std::cout << "Passed SemiLep lep cuts\n";
                dRCheckVecAr.push_back(Z1LeadVec);
                dRCheckVecAr.push_back(Z1TrailingVec);
                ROOT::Math::PtEtaPhiMVector tmpZVec = Z1LeadVec+Z1TrailingVec;
                if (!Z1IsMuon){
                    Z1LeadSIP = Electron_sip3dL[elecCandIndAr[Z1LeadItr]];
                    Z1TrailingSIP = Electron_sip3dL[elecCandIndAr[Z1TrailingItr]];
                }
                else {
                    Z1LeadSIP = Muon_sip3dL[muonCandIndAr[Z1LeadItr]];
                    Z1TrailingSIP = Muon_sip3dL[muonCandIndAr[Z1TrailingItr]];
                }
                selectedLeptons_InvMass = tmpZVec.M();
                passedAsSemiLepLepCutBool = true;
                //std::cout << "PASSED ALL THE WAY!!!!\n";
                if (debug) {
                    std::cout << "Z1IsMuon " <<Z1IsMuon<< "\n";
                    std::cout << "elecCandIndAr size " << elecCandIndAr.size() << "\n";

                    std::cout << "muonCandIndAr loop " << muonCandIndAr.size() << "\n";
                    
                    for (UInt_t muonCandIndInd=0; muonCandIndInd<muonCandIndAr.size();muonCandIndInd++){
                        std::cout << "muonCandIndInd " << muonCandIndInd << "muonCandIndAr[muonCandIndInd]" << muonCandIndAr[muonCandIndInd] << "\n";

                    }
                }
            }

        }
    }
}
