#pragma once
namespace vp_scram {

	bool version_check(long ver)
	{
		return (ver < 1 || ver > 4) ? false : true;
	}
	long get_high_version() {
		return 4;
	}
	long get_low_version() {
		return 1;
	}

	vector<tuple<int, int>> vlist_Egg = {
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 3, 0 },
		{ 4, 0 },
		{ 4, 0 }
	};

	vector<tuple<int, int, string>> rlist_Egg = {
		{ 2, 3, "h1"},
		{ 4, 0, "h2"}
	};

	ReorderCog *rcog_factory_Egg(string &n, vector<int> v, uint seed) {
		if (n == "h1")
			return new EggScrambler(v, seed);
		if (n == "h2")
			return new HashBrowns(v, seed);
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

	ReorderCog *get_rcog_Egg(int ver, uint seed) {
		for (auto tt = rlist_Egg.begin(); tt != rlist_Egg.end(); tt++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				return rcog_factory_Egg(get<2>(*tt), get_vlist_Egg(ver), seed);
			}
		};

		return(new IdentityReorderCog(get_vlist_Egg(ver)));
	}

	void write_Header(write_context &ctx, Header &payload)
	{
		write_int(ctx, payload.version);
		write_string(ctx, payload.test_name);
	}

	void write_Egg(write_context &ctx, Egg &payload)
	{
		vector<int> v((*ctx.reorder_map["Egg"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_string(ctx, payload.c1);
				break;
				case 1:
				write_string(ctx, payload.c2);
				break;
				case 2:
				write_string(ctx, payload.c3);
				break;
				case 3:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
				case 4:
				write_string(ctx, (*ctx.salt_map["PepperShaker"])());
				break;
				case 5:
				write_string(ctx, (*ctx.salt_map["PepperShaker"])());
				break;
			}
	}

	void write_Omelette(write_context &ctx, Omelette &payload)
	{
		write_int(ctx, payload.eggs.size());
		for (auto ii = payload.eggs.begin();ii != payload.eggs.end(); ii++)
			write_Egg(ctx, (*ii));
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.test_name);
	}

	void read_Egg(read_context &ctx, Egg &payload)
	{
		vector<int> v((*ctx.reorder_map["Egg"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_string(ctx, payload.c1);
					break;
				case 1:
					read_string(ctx, payload.c2);
					break;
				case 2:
					read_string(ctx, payload.c3);
					break;
				case 3:
					assert(read_string(ctx) == (*ctx.salt_map["SaltShaker"])());
					break;
				case 4:
					assert(read_string(ctx) == (*ctx.salt_map["PepperShaker"])());
					break;
				case 5:
					assert(read_string(ctx) == (*ctx.salt_map["PepperShaker"])());
					break;
			}
	}

	void read_Omelette(read_context &ctx, Omelette &payload)
	{
		int count_eggs;
		read_int(ctx, count_eggs);
		for (auto i = 0; i < count_eggs; i++) {
			Egg pod;
			read_Egg(ctx, pod);
			payload.eggs.push_back(pod);
		}
	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver, uint seed) {
		rmap["Egg"] = get_rcog_Egg(ver, seed);
	}

}
