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

	vector<tuple<int, int>> vlist_Egg = {
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 }
	};

	vector<tuple<int, int, string>> rlist_Egg = {
		{ 1, 0, "h1"}
	};

	ReorderCog *rcog_factory_Egg(string &n, vector<int> v) {
		if (n == "h1")
			return new EggScrambler(v);
		return(NULL);
	}

	vector<int> get_vlist_Egg(int ver) {
		vector<int> v; int i = 0;
		for (auto tt = vlist_Egg.begin(); tt != vlist_Egg.end(); tt++, i++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				v.push_back(i);
			}
		};

		return v;
	}

	ReorderCog *get_rcog_Egg(int ver) {
		for (auto tt = rlist_Egg.begin(); tt != rlist_Egg.end(); tt++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				return rcog_factory_Egg(get<2>(*tt), get_vlist_Egg(ver));
			}
		};

		return(new IdentityReorderCog(get_vlist_Egg(ver)));
	}

	void write_Header(write_context &ctx, Header &payload)
	{
		write_int(ctx, payload.version);
		write_string(ctx, payload.test_name);
	}

	void write_A(write_context &ctx, A &payload)
	{
		write_int(ctx, payload.i1);
		write_string(ctx, payload.s1);
	}

	void write_OuterA(write_context &ctx, OuterA &payload)
	{
		write_int(ctx, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_int(ctx, ii->first);
			write_A(ctx, *(ii->second));
		}
	}

	void write_OuterB(write_context &ctx, OuterB &payload)
	{
		write_int(ctx, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_string(ctx, ii->first);
			write_A(ctx, *(ii->second));
		}
	}

	void write_OuterC(write_context &ctx, OuterC &payload)
	{
		write_int(ctx, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_int(ctx, ii->first);
			write_string(ctx, (ii->second));
		}
	}

	void write_D1(write_context &ctx, D1 &payload)
	{
		write_A(ctx, payload.apod);
		write_int(ctx, payload.i);
		write_string(ctx, payload.s);
		write_A(ctx, *(payload.aref));
	}

	void write_OuterD(write_context &ctx, OuterD &payload)
	{
		write_int(ctx, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_string(ctx, ii->first);
			write_D1(ctx, *(ii->second));
		}
	}

	void write_Egg(write_context &ctx, Egg &payload)
	{
		vector<int> v((*ctx.reorder_map["Egg"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_int(ctx, payload.i1);
				break;
				case 1:
				write_string(ctx, payload.s1);
				break;
				case 2:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
				case 3:
				write_string(ctx, (*ctx.salt_map["PepperShaker"])());
				break;
			}
	}

	void write_Omlette(write_context &ctx, Omlette &payload)
	{
		write_int(ctx, payload.lookup.size());
		for (auto ii = payload.lookup.begin();ii != payload.lookup.end(); ii++) {
			write_int(ctx, ii->first);
			write_Egg(ctx, *(ii->second));
		}
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.test_name);
	}

	void read_A(read_context &ctx, A &payload)
	{
		read_int(ctx, payload.i1);
		read_string(ctx, payload.s1);
	}

	void read_OuterA(read_context &ctx, OuterA &payload)
	{
		int count_lookup;
		read_int(ctx, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			int k;
			read_int(ctx, k);
			auto *v = new A;
			read_A(ctx, *v);
			payload.lookup[k] = v;
		}

	}

	void read_OuterB(read_context &ctx, OuterB &payload)
	{
		int count_lookup;
		read_int(ctx, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			string k;
			read_string(ctx, k);
			auto *v = new A;
			read_A(ctx, *v);
			payload.lookup[k] = v;
		}

	}

	void read_OuterC(read_context &ctx, OuterC &payload)
	{
		int count_lookup;
		read_int(ctx, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			int k;
			read_int(ctx, k);
			string v;
			read_string(ctx, v);
			payload.lookup[k] = v;
		}

	}

	void read_D1(read_context &ctx, D1 &payload)
	{
		read_A(ctx, payload.apod);
		read_int(ctx, payload.i);
		read_string(ctx, payload.s);
		payload.aref = new A;
		read_A(ctx, *(payload.aref));
	}

	void read_OuterD(read_context &ctx, OuterD &payload)
	{
		int count_lookup;
		read_int(ctx, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			string k;
			read_string(ctx, k);
			auto *v = new D1;
			read_D1(ctx, *v);
			payload.lookup[k] = v;
		}

	}

	void read_Egg(read_context &ctx, Egg &payload)
	{
		vector<int> v((*ctx.reorder_map["Egg"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_int(ctx, payload.i1);
					break;
				case 1:
					read_string(ctx, payload.s1);
					break;
				case 2:
					read_string(ctx);
					break;
				case 3:
					read_string(ctx);
					break;
			}
	}

	void read_Omlette(read_context &ctx, Omlette &payload)
	{
		int count_lookup;
		read_int(ctx, count_lookup);
		for (auto i = 0; i < count_lookup; i++) {
			int k;
			read_int(ctx, k);
			auto *v = new Egg;
			read_Egg(ctx, *v);
			payload.lookup[k] = v;
		}

	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver) {
		rmap["Egg"] = get_rcog_Egg(ver);
	}

}
