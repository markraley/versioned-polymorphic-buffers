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

	void write_Header(long nVersion, write_context &wc, Header &payload)
	{
		write_int(wc, payload.version);
		write_string(wc, payload.tag);
	}

	void write_Value(long, write_context &wc, Value &);
	void write_Reverse(long, write_context &wc, Reverse &);
	void write_Skip(long, write_context &wc, Skip &);
	void write_DrawTwo(long, write_context &wc, DrawTwo &);

	void write_Card(long nVersion, write_context &wc, Card &payload)
	{
		const std::type_info& tid = typeid(payload);
		if (std::type_index(tid) == std::type_index(typeid(Value))) {
			write_int(wc,0);
			write_Value(nVersion, wc, dynamic_cast<Value &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Reverse))) {
			write_int(wc,1);
			write_int(wc,0);
			write_Reverse(nVersion, wc, dynamic_cast<Reverse &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Skip))) {
			write_int(wc,1);
			write_int(wc,1);
			write_Skip(nVersion, wc, dynamic_cast<Skip &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(DrawTwo))) {
			write_int(wc,1);
			write_int(wc,2);
			write_DrawTwo(nVersion, wc, dynamic_cast<DrawTwo &> (payload));
		}
		write_int(wc, payload.id);
	}

	void write_Value(long nVersion, write_context &wc, Value &payload)
	{
		write_int(wc, payload.value);
		write_string(wc, payload.color);
	}

	void write_Action(long nVersion, write_context &wc, Action &payload)
	{
		write_string(wc, payload.color);
	}

	void write_Reverse(long nVersion, write_context &wc, Reverse &payload)
	{
	}

	void write_Skip(long nVersion, write_context &wc, Skip &payload)
	{
	}

	void write_DrawTwo(long nVersion, write_context &wc, DrawTwo &payload)
	{
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

	Value* read_Value(long, read_context &rc);
	Action* read_Action(long, read_context &rc);

	Card* read_Card(long nVersion, read_context &rc)
	{
		Card* payload_ptr; int t; read_int(rc, t);
		if (t == 0)
			payload_ptr = read_Value(nVersion, rc);
		if (t == 1)
			payload_ptr = read_Action(nVersion, rc);
		auto &payload = *payload_ptr;
		read_int(rc, payload.id);
		return payload_ptr;
	}

	Value *read_Value(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new Value;
		auto &payload = *payload_ptr;
		read_int(rc, payload.value);
		read_string(rc, payload.color);
		return payload_ptr;
	}

	void read_Value(long nVersion, read_context &rc, Value &payload)
	{
		read_int(rc, payload.value);
		read_string(rc, payload.color);
	}

	Reverse* read_Reverse(long, read_context &rc);
	Skip* read_Skip(long, read_context &rc);
	DrawTwo* read_DrawTwo(long, read_context &rc);

	Action* read_Action(long nVersion, read_context &rc)
	{
		Action* payload_ptr; int t; read_int(rc, t);
		if (t == 0)
			payload_ptr = read_Reverse(nVersion, rc);
		if (t == 1)
			payload_ptr = read_Skip(nVersion, rc);
		if (t == 2)
			payload_ptr = read_DrawTwo(nVersion, rc);
		auto &payload = *payload_ptr;
		read_string(rc, payload.color);
		return payload_ptr;
	}

	Reverse *read_Reverse(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new Reverse;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_Reverse(long nVersion, read_context &rc, Reverse &payload)
	{
	}

	Skip *read_Skip(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new Skip;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_Skip(long nVersion, read_context &rc, Skip &payload)
	{
	}

	DrawTwo *read_DrawTwo(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new DrawTwo;
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	void read_DrawTwo(long nVersion, read_context &rc, DrawTwo &payload)
	{
	}

	void read_Deck(long nVersion, read_context &rc, Deck &payload)
	{
		int count_cards;
		read_int(rc, count_cards);
		for (auto i = 0; i < count_cards; i++) {
			auto *pod = read_Card(nVersion, rc);
			payload.cards.push_back(pod);
		}
	}

}
