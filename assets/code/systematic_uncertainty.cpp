#include "iostream"

#include "TROOT.h"
#include "TMath.h"

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TRandom3.h"

using namespace std;

Double_t g = 9.809;

Double_t measuretime(Double_t length, Double_t sigma=0.1, TRandom3 * rand = new TRandom3(0)){ //random variable is for time variation.
// s = 0.5 * g * t^2
// -> t = sqrt(2*s/g) \pm dt
    return TMath::Sqrt(2.*length/g)+(rand->Uniform(-1.*sigma, sigma));
}

TGraphErrors * GenerateData(Int_t    n         = 6, //number of data-points / DEF 6 , ==> 20cm * 6 = 1.2m
                            Double_t sigma_l   = 0.001,  //  Length Measurement Sigma      / DEF 0.1cm
                            Bool_t   overlap_l = kFALSE, //  Length Measurement Overlapped / DEF FALSE
                            Double_t hOffset   = 0.01,    //  Height Offset                 / DEF 1 cm
                            Double_t hPeriod   = 0.2,    //  Height Masurement Period (Differeces between heights) / DEF 20cm
                            Double_t sigma_t   = 0.001,   //  Time Measurement Sigma       / DEF 0.001s
                            TRandom3 * r1      = new TRandom3(0)){     // Random operator
    TGraphErrors * g1 = new TGraphErrors(n);

    Int_t i;
    Double_t height = hOffset;
    Double_t height_r = 0.;
    for(i=0; i<n; i++){
        if(!overlap_l){height = hOffset + hPeriod*i + (r1->Gaus(0, sigma_l));}
        else{height += hPeriod + (r1->Gaus(0, sigma_l));}
        height_r = hOffset+hPeriod*i;
        g1->SetPoint(i,  measuretime(height, sigma_t, r1), height_r);
        std::cout<<"SETPOINT "<<measuretime(height, sigma_t, r1)<<":"<<height_r<<endl;
        // if(overlap_l){g1->SetPointError(i,0.1, 0.01);} // If length measurement was overlapped-method, different error applied.
        // else{g1->SetPointError(i,sigma_t, sigma_l);}
        
    }

    g1->GetXaxis()->SetTitle("Measured Time (sec.)");
    g1->GetYaxis()->SetTitle("Height (m)");

    return g1;

}

void SetErrors(TGraphErrors * g1  , //number of data-points / DEF 6 , ==> 20cm * 6 = 1.2m
               Double_t sigma_l   = 0.001,  //  Length Measurement Sigma      / DEF 0.1cm
               Bool_t   overlap_l = kFALSE, //  Length Measurement Overlapped / DEF FALSE
               Double_t sigma_t   = 0.001){   //  Time Measurement Sigma       / DEF 0.001s
    Int_t i;
    for(i=0; i<g1->GetN(); i++){
        Double_t terr, lerr;
        terr = sigma_t;
        lerr = overlap_l ? TMath::Sqrt(i+1)*sigma_l:sigma_l;
        g1->SetPointError(i, terr, lerr);
    }
return;
}

void systematic_uncertainty(){
    TGraphErrors * g1 = GenerateData(20, 0.01, kTRUE);
    SetErrors(g1, 0.01, kTRUE);
    g1->Draw("APE");
    g1->SetMarkerSize(0.3);
    g1->SetMarkerStyle(20);

    return;

}