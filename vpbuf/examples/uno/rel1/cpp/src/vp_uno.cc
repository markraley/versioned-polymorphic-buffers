#pragma once
namespace vp_uno {

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

	void write_Value(write_context &ctx, Value &);
	void write_Reverse(write_context &ctx, Reverse &);
	void write_Skip(write_context &ctx, Skip &);
	void write_DrawTwo(write_context &ctx, DrawTwo &);

	void write_Card(write_context &ctx, Card &payload)
	{
		const std::type_info& tid = typeid(payload);
		if (std::type_index(tid) == std::type_index(typeid(Value))) {
			write_int(ctx,0);
			write_Value(ctx, dynamic_cast<Value &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Reverse))) {
			write_int(ctx,1);
			write_int(ctx,0);
			write_Reverse(ctx, dynamic_cast<Reverse &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Skip))) {
			write_int(ctx,1);
			write_int(ctx,1);
			write_Skip(ctx, dynamic_cast<Skip &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(DrawTwo))) {
			write_int(ctx,1);
			write_int(ctx,2);
			write_DrawTwo(ctx, dynamic_cast<DrawTwo &> (payload));
		}
		write_int(ctx, payload.id);
	}

	void write_Value(write_context &ctx, Value &payload)
	{
		write_int(ctx, payload.value);
		write_string(ctx, payload.color);
	}

	void write_Action(write_context &ctx, Action &payload)
	{
		write_string(ctx, payload.color);
	}

	void write_Reverse(write_context &ctx, Reverse &payload)
	{
		write_Action(ctx, payload);
	}

	void write_Skip(write_context &ctx, Skip &payload)
	{
		write_Action(ctx, payload);
	}

	void write_DrawTwo(write_context &ctx, DrawTwo &payload)
	{
		write_Action(ctx, payload);
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

	Value* read_Value(read_context &ctx);
	Action* read_Action(read_context &ctx);

	Card* read_Card(read_context &ctx)
	{
		Card* payload_ptr; int t; read_int(ctx, t);
		if (t == 0)
			payload_ptr = read_Value(ctx);
		if (t == 1)
			payload_ptr = read_Action(ctx);
		auto &payload = *payload_ptr;
		read_int(ctx, payload.id);
		return payload_ptr;
	}

	Value *read_Value(read_context &ctx)
	{
		auto *payload_ptr = new Value;
		auto &payload = *payload_ptr;
		read_int(ctx, payload.value);
		read_string(ctx, payload.color);
		return payload_ptr;
	}

	void read_Value(read_context &ctx, Value &payload)
	{
		read_int(ctx, payload.value);
		read_string(ctx, payload.color);
	}

	Reverse* read_Reverse(read_context &ctx);
	Skip* read_Skip(read_context &ctx);
	DrawTwo* read_DrawTwo(read_context &ctx);

	Action* read_Action(read_context &ctx)
	{
		Action* payload_ptr; int t; read_int(ctx, t);
		if (t == 0)
			payload_ptr = read_Reverse(ctx);
		if (t == 1)
			payload_ptr = read_Skip(ctx);
		if (t == 2)
			payload_ptr = read_DrawTwo(ctx);
		auto &payload = *payload_ptr;
		read_string(ctx, payload.color);
		return payload_ptr;
	}

	Reverse *read_Reverse(read_context &ctx)
	{
		auto *payload_ptr = new Reverse;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_Reverse(read_context &ctx, Reverse &payload)
	{
	}

	Skip *read_Skip(read_context &ctx)
	{
		auto *payload_ptr = new Skip;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_Skip(read_context &ctx, Skip &payload)
	{
	}

	DrawTwo *read_DrawTwo(read_context &ctx)
	{
		auto *payload_ptr = new DrawTwo;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_DrawTwo(read_context &ctx, DrawTwo &payload)
	{
	}

	void read_Deck(read_context &ctx, Deck &payload)
	{
		int count_cards;
		read_int(ctx, count_cards);
		for (auto i = 0; i < count_cards; i++) {
			auto *pod = read_Card(ctx);
			payload.cards.push_back(pod);
		}
	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver) {
	}

}
