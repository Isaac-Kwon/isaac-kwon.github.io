#include "TROOT.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLine.h"
#include "TBox.h"

#define MTIME 10

void data_production(){

    Double_t xmin = 0.;
    Double_t xmax = 0.7;
    Double_t yerr = 0.01;
    Double_t myperiod = 0.2;

    TCanvas * c1 = new TCanvas("c1", "Canvas 1", 1200, 800);
    TF1     * f1 = new TF1("f1", "0.5*9.81*pow(x,2)", 0., 0.7);
    f1->GetXaxis()->SetTitle("Falling Time (sec.)");
    f1->GetYaxis()->SetTitle("Falling Height (meter)");
    f1->SetTitle("Falling Height Curve");
    f1->Draw();

    Int_t i;
    TLine * mline[MTIME];
    for(i=0; i<MTIME; i++){ // 데이터 측정선. 낙하거리에 대한 지정선임.
        mline[i] = new TLine(xmin, 0.2*(i+1), xmax, 0.2*(i+1) );
        mline[i]->Draw();
    }

    TBox * mxbox[MTIME];
    for(i=0; i<MTIME; i++){ // 데이터 측정선. 낙하거리에 오차가 있다고 할 떄의 범위.

        mxbox[i] = new TBox(0., myperiod*(i+1)-yerr, 0.7, myperiod*(i+1)+yerr );
        mxbox[i]->SetFillColorAlpha(kBlue,0.3);
        mxbox[i]->Draw();
        
    }

    TBox * mybox[MTIME];
    for(i=0; i<MTIME; i++){ // 데이터 측정선(Y평행선). 낙하거리에 오차가 있다고 할 떄의 범위.
        Double_t left = f1->GetX(myperiod*(i+1)-yerr);
        Double_t right = f1->GetX(myperiod*(i+1)+yerr);

        mybox[i] = new TBox(left, 0, right, f1->GetMaximum() );
        mybox[i]->SetFillColorAlpha(kGreen,0.3);
        mybox[i]->Draw();
    }

    TLine * mtline[MTIME];
    TBox  * mtbox[MTIME];
    for(i=0; i<MTIME; i++){ // 데이터 측정선(Y평행선). 낙하거리에 오차가 있다고 할 떄의 범위.
        Double_t left = f1->GetX(myperiod*(i+1)-yerr);
        Double_t right = f1->GetX(myperiod*(i+1)+yerr);

        mybox[i] = new TBox(left, 0, right, f1->GetMaximum() );
        mybox[i]->SetFillColorAlpha(kGreen,0.3);
        mybox[i]->Draw();
    }
}