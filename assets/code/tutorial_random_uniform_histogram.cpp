#include "TROOT.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TH1D.h"

#define NDP 100

void tutorial_random_uniform_histogram(){
    TRandom * r = new TRandom();
    TH1D * h1 = new TH1D("h1", "h1", 100, -5, 5);

    Int_t i;
    for(i=0; i<NDP; i++){
        h1->Fill(r->Uniform(-2,2));
    }
    h1->Draw();
}