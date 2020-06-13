#include "TROOT.h"

#include "TRandom3.h"

#include "TFile.h"
#include "TTree.h"

#include "TGraph.h"
#include "TF1.h"
#include "TMath.h"

#include "TFitResultPtr.h"

#define NENTRIES 3000
#define NDP 10

#define hstart 0.0     // 0.0    m
#define hgap   0.2     // 0.2    m
#define herror 0.005   // 0.5    cm
#define terror 0.0001  // 0.0001 s

/*
본 파일은 멀티플 데이터 프로덕션 파일입니다.
트리 브랜치에 {도달 시간, 도달 거리(정의값, 실제값)} : NDP개 , 2차 피팅 결과 (p0, p1, p2) 를 동시에 기재합니다.
*/

Double_t Round(const Double_t x, const Double_t digit = 0.1){
    Double_t div = x/digit;
    Double_t jud = div-TMath::Floor(div);
    Double_t result = x;
    
    if(jud<0.5){
        result -= jud*digit; // 버림
    }else{
        result += (1-jud)*digit; // 올림
    }

    return result;

}

Double_t MeasureT(Double_t h, Double_t g=9.806){
    return TMath::Sqrt(2*h/g);
}

void gravity_MC(){
    TTree * tree_ = new TTree("T","Monte-Carlo for Gravitational Force in GPLAB");
    TFile * file_ = new TFile("./gravity_MC.root", "RECREATE");
    TRandom3 * r  = new TRandom3();

    Double_t h_define[NDP];
    Double_t h_real[NDP];
    Double_t t[NDP];
    Double_t p0, p1, p2;
    Int_t    NPoint=NDP;

    Int_t i;

    TF1 * f1 = new TF1("fitftn", "[0]+[1]*x+0.5*[2]*x*x", hstart, hstart+hgap*(NDP+0.5));

    tree_->Branch("row", &i, "row/I");
    tree_->Branch("NPoint", &NPoint, "NPoint/I");

    tree_->Branch("hdef",h_define,"hdef[NPoint]/D");
    tree_->Branch("hreal",h_real,"hreal[NPoint]/D");
    tree_->Branch("t", t, "t[NPoint]/D");

    tree_->Branch("p0", &p0, "p0/D");
    tree_->Branch("p1", &p1, "p1/D");
    tree_->Branch("p2", &p2, "p2/D");

    for(i=0; i<NENTRIES; i++){

        Double_t h_now = hstart;
        Double_t h_define0 = 0;

        Int_t j;

        for(j=0; j<NDP; j++){
            h_define0 += hgap;
            h_define[j] = h_define0;
            h_now += hgap + (r->Gaus(0,herror)); // 측정오차 고려 (이전지점부터 다음지점까지의 오차)
            h_real[j] = h_now;
            t[j] = Round( // 최소단위 반올림
                MeasureT(h_now) // 실제 시간
                 + (r->Uniform(-1*terror/2,terror/2)), // 시간측정오차 이전 (0.5 * 눈금) 에서 이후 (0.5 * 눈금) 까지
                terror);
        }

        TGraph * g = new TGraph(NDP, t, h_define);
        TFitResultPtr rp = g->Fit(f1,"SQ");
        p0 = rp.Get()->GetParams()[0];
        p1 = rp.Get()->GetParams()[1];
        p2 = rp.Get()->GetParams()[2];
        tree_->Fill();
        
        g->Delete();

    }   

    file_->Add(tree_);
    file_->Write();
    file_->Close();

}