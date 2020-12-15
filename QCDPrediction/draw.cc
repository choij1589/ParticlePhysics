void draw() {
	TCanvas* cvs = new TCanvas("cvs", "");
	TFile* f = new TFile("out.root");
	vector<TString> channels = {
        "ud_to_ud", "uu_to_uu", "uubar_to_ddbar", "uubar_to_uubar", "uubar_to_gg",
        "ug_to_ug", "gg_to_uubar", "gg_to_gg"};
	vector<TH1D*> hists;
	for (const auto &ch: channels) {
		TH1D* this_hist = (TH1D*)f->Get(ch);
	}

	int color = 2;
	cvs->cd();
	
	for (const auto &h: hists) {
		h->SetStats(0);
		h->SetLineColor(color); color++;
		h->Draw("hist&same");
	}
	cvs->SaveAs("out.pdf");
}
