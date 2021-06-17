#pragma once
namespace vp_poker {

	bool version_check(long ver)
	{
		return (ver < 1 || ver > 1) ? false : true;
	}
	long get_high_version() {
		return 1;
	}
	long get_low_version() {
		return 1;
	}

	void write_Header(long nVersion, write_context &wc, Header &payload)
	{
		write_int(wc, payload.version);
		write_string(wc, payload.tag);
	}

	void write_Card(long nVersion, write_context &wc, Card &payload)
	{
		write_int(wc, payload.id);
		write_string(wc, payload.name);
	}

	void write_Deck(long nVersion, write_context &wc, Deck &payload)
	{
		write_int(wc, payload.cards.size());
		for (auto ii = payload.cards.begin();ii != payload.cards.end(); ii++)
			write_Card(nVersion, wc, *(*ii));
	}

	void read_Header(long nVersion, read_context &rc, Header &payload)
	{
		read_int(rc, payload.version);
		read_string(rc, payload.tag);
	}

	void read_Card(long nVersion, read_context &rc, Card &payload)
	{
		read_int(rc, payload.id);
		read_string(rc, payload.name);
	}

	void read_Deck(long nVersion, read_context &rc, Deck &payload)
	{
		int count_cards;
		read_int(rc, count_cards);
		for (auto i = 0; i < count_cards; i++) {
			auto pod = new Card;
			read_Card(nVersion, rc, *pod);
			payload.cards.push_back(pod);
		}
	}

}
