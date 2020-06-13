#include "TROOT.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TH1D.h"

#define NDP 10000

void tutorial_random_gaus_histogram(){
    TRandom * r = new TRandom();
    TH1D * h1 = new TH1D("h1", "h1", 100, -5, 5);

    Int_t i;
    for(i=0; i<NDP; i++){
        h1->Fill(r->Gaus(0,1));
    }
    h1->Draw();
}