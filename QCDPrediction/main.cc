#include "Channel.h"
#include "Channel.cc"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
	double E_cm = 13000.;
	const double etaCut = 5.;
	vector<string> channels = {
		"ud_to_ud", "uu_to_uu", "uubar_to_ddbar", "uubar_to_uubar", "uubar_to_gg",
		"ug_to_ug", "gg_to_uubar", "gg_to_gg"};

	Channel* ch = new Channel(326300);
	cout << "==== start calculation ====" << endl;
	for (const auto &channel: channels) {
		ch->set_channel(channel);
		cout << ch->xsec(E_cm, etaCut) << endl;
	}
	cout << "==== end calculation ====" << endl;
	
	// Let's see E_cm dependence
	TFile* f = new TFile("out.root", "recreate");
	vector<TH1D*> hists;
	for (auto &channel: channels) {
		ch->set_channel(channel);
		char hist_name[channel.size() + 1];
		strcpy(hist_name, channel.c_str());
		TH1D* this_hist = new TH1D(hist_name, "", 1000, 1000., 50000.);
		for (int i = 0; i < 1000; i++) {
			double this_E_cm = 1000. + i * ((50000. - 1000.)/1000);
			this_hist->Fill(this_E_cm, ch->xsec(this_E_cm, etaCut));
		}
		hists.emplace_back(this_hist);
	}
	f->cd();
	for (const auto &h : hists) {
		h->Write();
	}
	f->Close();
	delete ch;
	
	return 0;
}
