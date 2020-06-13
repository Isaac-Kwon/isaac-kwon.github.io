#include "TROOT.h"

#include "TRandom3.h"

#include "TFile.h"
#include "TTree.h"

#include "TGraph.h"
#include "TF1.h"
#include "TMath.h"

#include "TFitResultPtr.h"

#define NDP 40

#define hstart 0.0000  // 0.0    m
#define hgap   0.05     // 5.0   cm
#define herror 0.001   // 0.1    cm (1.0 mm)
#define terror 0.0001  // 0.0001 s

/*
본 파일은 싱글 데이터 프로덕션 파일입니다.
트리 브랜치에 {도달 시간, 도달 거리(정의값, 실제값)} 를 기재합니다.
*/

Double_t Round(const Double_t x, const Double_t digit = 0.1){
    Double_t div = x/digit;
    Double_t jud = div-TMath::Floor(div);
    Double_t result = x;
    
    if(jud<0.5){
        result -= jud*digit;
    }else{
        result += (1-jud)*digit;
    }

    return result;

}

Double_t MeasureT(Double_t h, Double_t g=9.806){
    return TMath::Sqrt(2*h/g);
}

void mftn2(){
    TTree * tree_ = new TTree("T","Tree for Tutorial");
    TFile * file_ = new TFile("./example_tree2.root", "RECREATE");
    TRandom3 * r  = new TRandom3();

    Double_t h_define;
    Double_t h_real;
    Double_t t;
    Double_t p0, p1, p2;

    TF1 * f1 = new TF1("fitftn", "[0]+[1]*x+0.5*[2]*x*x", hstart, hstart+hgap*(NDP+0.5));
    Int_t i;

    tree_->Branch("row", &i, "row/I");
    tree_->Branch("hdef",&h_define,"hdef/D");
    tree_->Branch("hreal",&h_real,"hreal/D");
    tree_->Branch("t", &t, "t/D");

    Double_t h_now = hstart;
    Double_t h_define0 = 0;

    for(i=0; i<NDP; i++){
        h_define0 += hgap;
        h_define = h_define0;
        h_now += hgap + (r->Gaus(0,herror)); // 측정오차 고려 (이전지점부터 다음지점까지의 오차)
        h_real = h_now;
        t = Round( // 최소단위 반올림
            MeasureT(h_now) // 실제 시간
                + (r->Uniform(-1*terror/2,terror/2)), // 시간측정오차 이전 (0.5 * 눈금) 에서 이후 (0.5 * 눈금) 까지
            terror);
        tree_->Fill();
    }
    
    file_->Add(tree_);
    file_->Write();
    file_->Close();
}

void tree_example2(){
    mftn2();
}