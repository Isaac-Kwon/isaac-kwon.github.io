void scatter_example(){
  TRandom3 * r1 = new TRandom3();
  TCanvas * c1 = new TCanvas();
  c1->SetName("c1");
  TGraphErrors * g1 = new TGraphErrors();
  g1->SetName("g1");
  Int_t i;
  Int_t npoint = 10;
  Double_t x,y;
  // r1->SetSeed(500);
  for(i=0; i<npoint; i++){
    x = 1*(i+1);
    // x = r1->Uniform(0,10);
    y = 2.*x+0.5+(r1->Uniform(-2,2));
    g1->SetPoint(i, x, y);
  }
  // g1->SetLineWidth(1);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(0.8);
  g1->GetXaxis()->SetName("x");
  g1->GetYaxis()->SetName("y");

  g1->GetXaxis()->SetTitle("");//SetTitle("x (arb. unit)");
  g1->GetYaxis()->SetTitle("y (arb. unit)");

  // g1->Fit("pol1");
  g1->Draw("AP");

  TCanvas * c2 = new TCanvas();
  TGraphErrors * g2 = new TGraphErrors(*g1);
  c2->SetName("c2");
  c2->cd();
  g2->Fit("pol1");
  g2->Draw("AP");

  TCanvas * c3 = new TCanvas();
  TGraphErrors * g3 = new TGraphErrors(*g2);
  c3->SetName("c3");
  c3->cd();
  TFitResultPtr ft = g3->Fit("pol1", "S");
  g3->Draw("AP");

  c3->cd();
  
  Double_t a,b;
  TLine * l_;

  a = ft->Parameter(0);
  cout<<a<<endl;
  b = ft->Parameter(1);
  cout<<b<<endl;

  // TH1D * h1 = new TH1D("h1", "Residuals");
  TH1D * h1 = new TH1D("h1", "Residuals", 20, -5, 5 );
  Double_t ymin=0; 
  Double_t ymax=0; 

  TGraphErrors * g3_r = new TGraphErrors(g3->GetN());
  for(i=0;i<g3->GetN();i++){
    g3->GetPoint(i, x, y);

    l_ = new TLine(x,y,x,a+b*x);
    l_->SetLineWidth(2);
    l_->SetLineColor(kBlue);
    l_->Draw();
    
    g3_r->SetPoint(i, x, a+b*x-y);

    h1->Fill(a+b*x-y);
    
    ymin = ymin < a+b*x-y ? ymin : a+b*x-y;
    ymax = ymax > a+b*x-y ? ymax : a+b*x-y;
  }

  TCanvas * c4 = new TCanvas("c4", "Canvas Compare", 800, 800);
  c4->SetName("c4");
  c4->Draw();
  c4->cd();
  TPad * pplot = new TPad("pplot","pad for mother plot", 0., 0.3, 1.0, 1.0);
  TPad * pres = new TPad("pres","pad for mother plot", 0., 0.0, 1.0, 0.3);
  pplot->Draw();
  pres->Draw();

  pplot->cd();
  g3->Draw("AP");
  
  Double_t yplt = TMath::Abs(ymax) > TMath::Abs(ymin)? TMath::Abs(ymax) : TMath::Abs(ymin);
  cout<<ymin<<" - "<<ymax<<endl;
  cout<<yplt<<endl;

  pres->cd();
  pres->SetGridy();
  g3_r->SetMarkerStyle(20);
  g3_r->SetMarkerSize(0.8);
  // gStyle->SetOptTitle(0);
  g3_r->Draw("AP");
  g3_r->GetYaxis()->SetRangeUser(-1*yplt*1.6, yplt*1.6);
  g3_r->SetTitle("");
  g3_r->GetXaxis()->SetTitle("x (arb. unit)");
  g3_r->GetYaxis()->SetTitle("residual (arb. unit)");

  g3_r->GetXaxis()->SetTitleSize(0.035/3.*7.);
  g3_r->GetXaxis()->SetLabelSize(0.035/3.*7.);

  g3_r->GetYaxis()->SetTitleSize(0.035/3.*7.);
  g3_r->GetYaxis()->SetLabelSize(0.035/3.*7.);

  g3->GetYaxis()->SetTitleOffset(1.);
  g3_r->GetYaxis()->SetTitleOffset(1.*3./7.);


  c4->Update();
  
  TCanvas * c5 = new TCanvas();
  c5->SetName("c5");
  c5->Draw();
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetXaxis()->SetTitle("Residual");
  h1->SetTitle("");
  h1->Draw();




  TFile * file = new TFile("SimpleFitting.root", "RECREATE");
  file->Add(c1);
  file->Add(c2);
  file->Add(c3);
  file->Add(c4);
  file->Add(c5);
  file->Write();

  // c1->Close();
  // c2->Close();
  // c3->Close();

}


// 0, 2.49897
// 1, 1.15164
// 2, 3.63047
// 3, 8.2888
// 4, 7.42663
// 5, 10.4399
// 6, 14.3299
// 7, 15.4772
// 8, 16.6602
// 9, 19.4598
