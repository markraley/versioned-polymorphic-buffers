#pragma once
namespace vp_scram {

	bool version_check(long ver)
	{
		return (ver < 1 || ver > 3) ? false : true;
	}
	long get_high_version() {
		return 3;
	}
	long get_low_version() {
		return 1;
	}

	vector<tuple<int, int>> vlist_Phrase = {
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 3, 0 }
	};

	vector<tuple<int, int, string>> rlist_Phrase = {
		{ 3, 0, "HashBrowns"}
	};

	ReorderCog *rcog_factory_Phrase(string &n, vector<int> v, uint seed) {
		if (n == "HashBrowns")
			return new HashBrowns(v, seed);
		return(NULL);
	}

	vector<int> get_vlist_Phrase(int ver) {
		vector<int> v; int i = 0;
		for (auto tt = vlist_Phrase.begin(); tt != vlist_Phrase.end(); tt++, i++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				v.push_back(i);
			}
		};

		return v;
	}

	ReorderCog *get_rcog_Phrase(int ver, uint seed) {
		for (auto tt = rlist_Phrase.begin(); tt != rlist_Phrase.end(); tt++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				return rcog_factory_Phrase(get<2>(*tt), get_vlist_Phrase(ver), seed);
			}
		};

		return(new IdentityReorderCog(get_vlist_Phrase(ver)));
	}

	void write_Header(write_context &ctx, Header &payload)
	{
		write_int(ctx, payload.version);
		write_string(ctx, payload.test_name);
	}

	void write_Phrase(write_context &ctx, Phrase &payload)
	{
		vector<int> v((*ctx.reorder_map["Phrase"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_string(ctx, payload.word1);
				break;
				case 1:
				write_string(ctx, payload.word2);
				break;
				case 2:
				write_string(ctx, payload.word3);
				break;
				case 3:
				write_string(ctx, (*ctx.salt_map["PepperShaker"])());
				break;
			}
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.test_name);
	}

	void read_Phrase(read_context &ctx, Phrase &payload)
	{
		vector<int> v((*ctx.reorder_map["Phrase"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_string(ctx, payload.word1);
					break;
				case 1:
					read_string(ctx, payload.word2);
					break;
				case 2:
					read_string(ctx, payload.word3);
					break;
				case 3:
					read_string(ctx);
					break;
			}
	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver, uint seed) {
		rmap["Phrase"] = get_rcog_Phrase(ver, seed);
	}

}
