#pragma once
namespace vp_maps {

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
		write_string(wc, payload.test_name);
	}

	void write_A(long nVersion, write_context &wc, A &payload)
	{
		write_int(wc, payload.i1);
		write_string(wc, payload.s1);
	}

	void write_OuterA(long nVersion, write_context &wc, OuterA &payload)
	{
		write_int(wc, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_int(nVersion, wc, ii->first);
			write_A(nVersion, wc, *(ii->second));
		}
	}

	void write_OuterB(long nVersion, write_context &wc, OuterB &payload)
	{
		write_int(wc, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_string(nVersion, wc, ii->first);
			write_A(nVersion, wc, *(ii->second));
		}
	}

	void write_OuterC(long nVersion, write_context &wc, OuterC &payload)
	{
		write_int(wc, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_int(nVersion, wc, ii->first);
			write_string(nVersion, wc, (ii->second));
		}
	}

	void write_D1(long nVersion, write_context &wc, D1 &payload)
	{
		write_A(nVersion, wc, payload.apod);
		write_int(wc, payload.i);
		write_string(wc, payload.s);
		write_A(nVersion, wc, *(payload.aref));
	}

	void write_OuterD(long nVersion, write_context &wc, OuterD &payload)
	{
		write_int(wc, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_string(nVersion, wc, ii->first);
			write_D1(nVersion, wc, *(ii->second));
		}
	}

	void read_Header(long nVersion, read_context &rc, Header &payload)
	{
		read_int(rc, payload.version);
		read_string(rc, payload.test_name);
	}

	void read_A(long nVersion, read_context &rc, A &payload)
	{
		read_int(rc, payload.i1);
		read_string(rc, payload.s1);
	}

	void read_OuterA(long nVersion, read_context &rc, OuterA &payload)
	{
		int count_lookup;
		read_int(rc, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			int k;
			read_int(rc, k);
			auto *v = new A;
			read_A(nVersion, rc, *v);
			payload.lookup[k] = v;
		}

	}

	void read_OuterB(long nVersion, read_context &rc, OuterB &payload)
	{
		int count_lookup;
		read_int(rc, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			string k;
			read_string(rc, k);
			auto *v = new A;
			read_A(nVersion, rc, *v);
			payload.lookup[k] = v;
		}

	}

	void read_OuterC(long nVersion, read_context &rc, OuterC &payload)
	{
		int count_lookup;
		read_int(rc, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			int k;
			read_int(rc, k);
			string v;
			read_string(rc, v);
			payload.lookup[k] = v;
		}

	}

	void read_D1(long nVersion, read_context &rc, D1 &payload)
	{
		read_A(nVersion, rc, payload.apod);
		read_int(rc, payload.i);
		read_string(rc, payload.s);
		payload.aref = new A;
		read_A(nVersion, rc, *(payload.aref));
	}

	void read_OuterD(long nVersion, read_context &rc, OuterD &payload)
	{
		int count_lookup;
		read_int(rc, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			string k;
			read_string(rc, k);
			auto *v = new D1;
			read_D1(nVersion, rc, *v);
			payload.lookup[k] = v;
		}

	}

}
