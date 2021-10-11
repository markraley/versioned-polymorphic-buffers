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

	void write_Header(write_context &ctx, Header &payload)
	{
		write_int(ctx, payload.version);
		write_string(ctx, payload.tag);
	}

	void write_Card(write_context &ctx, Card &payload)
	{
		write_int(ctx, payload.id);
		write_string(ctx, payload.name);
	}

	void write_Deck(write_context &ctx, Deck &payload)
	{
		write_int(ctx, payload.cards.size());
		for (auto ii = payload.cards.begin();ii != payload.cards.end(); ii++)
			write_Card(ctx, *(*ii));
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.tag);
	}

	void read_Card(read_context &ctx, Card &payload)
	{
		read_int(ctx, payload.id);
		read_string(ctx, payload.name);
	}

	void read_Deck(read_context &ctx, Deck &payload)
	{
		int count_cards;
		read_int(ctx, count_cards);
		for (auto i = 0; i < count_cards; i++) {
			auto pod = new Card;
			read_Card(ctx, *pod);
			payload.cards.push_back(pod);
		}
	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver) {
	}

}
