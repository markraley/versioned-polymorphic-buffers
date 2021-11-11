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

	vector<tuple<int, int>> vlist_Word = {
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 3, 0 },
		{ 3, 0 },
		{ 4, 0 },
		{ 4, 0 }
	};

	vector<tuple<int, int, string>> rlist_Word = {
		{ 2, 0, "h1"}
	};

	ReorderCog *rcog_factory_Word(string &n, vector<int> v, uint seed) {
		if (n == "h1")
			return new EggScrambler(v, seed);
		return(NULL);
	}

	vector<int> get_vlist_Word(int ver) {
		vector<int> v; int i = 0;
		for (auto tt = vlist_Word.begin(); tt != vlist_Word.end(); tt++, i++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				v.push_back(i);
			}
		};

		return v;
	}

	ReorderCog *get_rcog_Word(int ver, uint seed) {
		for (auto tt = rlist_Word.begin(); tt != rlist_Word.end(); tt++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				return rcog_factory_Word(get<2>(*tt), get_vlist_Word(ver), seed);
			}
		};

		return(new IdentityReorderCog(get_vlist_Word(ver)));
	}

	vector<tuple<int, int>> vlist_Phrase = {
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 }
	};

	vector<tuple<int, int, string>> rlist_Phrase = {
		{ 4, 0, "h2"}
	};

	ReorderCog *rcog_factory_Phrase(string &n, vector<int> v, uint seed) {
		if (n == "h2")
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

	void write_Word(write_context &ctx, Word &payload)
	{
		vector<int> v((*ctx.reorder_map["Word"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_string(ctx, payload.fragment1);
				break;
				case 1:
				write_string(ctx, payload.fragment2);
				break;
				case 2:
				write_string(ctx, payload.fragment3);
				break;
				case 3:
				write_string(ctx, payload.fragment4);
				break;
				case 4:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
				case 5:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
				case 6:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
				case 7:
				write_string(ctx, (*ctx.salt_map["SaltShaker"])());
				break;
			}
	}

	void write_Phrase(write_context &ctx, Phrase &payload)
	{
		vector<int> v((*ctx.reorder_map["Phrase"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_Word(ctx, payload.word1);
				break;
				case 1:
				write_Word(ctx, payload.word2);
				break;
				case 2:
				write_Word(ctx, payload.word3);
				break;
			}
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.test_name);
	}

	void read_Word(read_context &ctx, Word &payload)
	{
		vector<int> v((*ctx.reorder_map["Word"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_string(ctx, payload.fragment1);
					break;
				case 1:
					read_string(ctx, payload.fragment2);
					break;
				case 2:
					read_string(ctx, payload.fragment3);
					break;
				case 3:
					read_string(ctx, payload.fragment4);
					break;
				case 4:
					assert(read_string(ctx) == (*ctx.salt_map["SaltShaker"])());
					break;
				case 5:
					assert(read_string(ctx) == (*ctx.salt_map["SaltShaker"])());
					break;
				case 6:
					assert(read_string(ctx) == (*ctx.salt_map["SaltShaker"])());
					break;
				case 7:
					assert(read_string(ctx) == (*ctx.salt_map["SaltShaker"])());
					break;
			}
	}

	void read_Phrase(read_context &ctx, Phrase &payload)
	{
		vector<int> v((*ctx.reorder_map["Phrase"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_Word(ctx, payload.word1);
					break;
				case 1:
					read_Word(ctx, payload.word2);
					break;
				case 2:
					read_Word(ctx, payload.word3);
					break;
			}
	}

	void init_reorder_map(map<string, ReorderCog *> &rmap, int ver, uint seed) {
		rmap["Word"] = get_rcog_Word(ver, seed);
		rmap["Phrase"] = get_rcog_Phrase(ver, seed);
	}

}
