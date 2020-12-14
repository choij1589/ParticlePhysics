#include "Channel.h"
#include "Channel.cc"


int main() {
	double E_cm = 13000.;
	double etaCut = 5.;
	vector<string> channels = {
		"ud_to_ud", "uu_to_uu", "uubar_to_ddbar", "uubar_to_uubar", "uubar_to_gg",
		"ug_to_ug", "gg_to_uubar", "gg_to_gg"};

	Channel* ch = new Channel(326300);
	cout << "==== start calculation ====" << endl;
	for (const auto &channel: channels) {
		ch->set_channel(channel);
		ch->xsec(E_cm, etaCut);
	}
	cout << "==== end calculation ====" << endl;
	delete ch;
	
	return 0;
}
