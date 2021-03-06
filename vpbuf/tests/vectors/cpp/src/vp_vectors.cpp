#pragma once
namespace vp_vectors {

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

	vector<tuple<int, int>> vlist_A = {
		{ 1, 0 },
		{ 1, 0 }
	};

	vector<tuple<int, int, string>> rlist_A = {
	};

	ReorderCog *rcog_factory_A(string &n, uint seed) {
		return(NULL);
	}

	vector<int> get_vlist_A(int ver) {
		vector<int> v; int i = 0;
		for (auto tt = vlist_A.begin(); tt != vlist_A.end(); tt++, i++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				v.push_back(i);
			}
		};

		return v;
	}

	void init_rcog_A(map<string, CogStack> &rmap, int ver, uint seed) {
		rmap.emplace("A", CogStack(get_vlist_A(ver)));
		auto &cs = rmap["A"];
		for (auto tt = rlist_A.begin(); tt != rlist_A.end(); tt++) {
			if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) || (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {
				cs.cogs.push_back(rcog_factory_A(get<2>(*tt), seed));
			}
		};

	}

	void write_Header(write_context &ctx, Header &payload)
	{
		write_int(ctx, payload.version);
		write_string(ctx, payload.test_name);
	}

	void write_A(write_context &ctx, A &payload)
	{
		vector<int> v((ctx.reorder_map["A"])());

		for (auto i : v) 
			switch(i) {
				case 0:
				write_int(ctx, payload.i1);
				break;
				case 1:
				write_string(ctx, payload.s1);
				break;
			}
	}

	void write_OuterA(write_context &ctx, OuterA &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_A(ctx, *(*ii));
	}

	void write_OuterB(write_context &ctx, OuterB &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_A(ctx, (*ii));
	}

	void write_OuterC(write_context &ctx, OuterC &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_string(ctx, (*ii));
	}

	void write_OuterD(write_context &ctx, OuterD &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_string(ctx, *(*ii));
	}

	void write_OuterE(write_context &ctx, OuterE &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_int(ctx, (*ii));
	}

	void write_OuterF(write_context &ctx, OuterF &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_int(ctx, *(*ii));
	}

	void write_Derived1(write_context &ctx, Derived1 &);
	void write_Derived2(write_context &ctx, Derived2 &);

	void write_Base(write_context &ctx, Base &payload)
	{
		const std::type_info& tid = typeid(payload);
		if (std::type_index(tid) == std::type_index(typeid(Derived1))) {
			write_int(ctx,0);
			write_Derived1(ctx, dynamic_cast<Derived1 &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Derived2))) {
			write_int(ctx,1);
			write_Derived2(ctx, dynamic_cast<Derived2 &> (payload));
		}
	}

	void write_Derived1(write_context &ctx, Derived1 &payload)
	{
		write_int(ctx, payload.i1);
		write_string(ctx, payload.s1);
	}

	void write_Derived2(write_context &ctx, Derived2 &payload)
	{
		write_int(ctx, payload.i1);
		write_string(ctx, payload.s1);
	}

	void write_OuterG(write_context &ctx, OuterG &payload)
	{
		write_int(ctx, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_Base(ctx, *(*ii));
	}

	void read_Header(read_context &ctx, Header &payload)
	{
		read_int(ctx, payload.version);
		read_string(ctx, payload.test_name);
	}

	void read_A(read_context &ctx, A &payload)
	{
		vector<int> v((ctx.reorder_map["A"])());

		for (auto i : v) 
			switch(i) {
				case 0:
					read_int(ctx, payload.i1);
					break;
				case 1:
					read_string(ctx, payload.s1);
					break;
			}
	}

	void read_OuterA(read_context &ctx, OuterA &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new A;
			read_A(ctx, *pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterB(read_context &ctx, OuterB &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			A pod;
			read_A(ctx, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterC(read_context &ctx, OuterC &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			string pod;
			read_string(ctx, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterD(read_context &ctx, OuterD &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new string;
			read_string(ctx, *pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterE(read_context &ctx, OuterE &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			int pod;
			read_int(ctx, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterF(read_context &ctx, OuterF &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new int;
			read_int(ctx, *pod);
			payload.v.push_back(pod);
		}
	}

	Derived1* read_Derived1(read_context &ctx);
	Derived2* read_Derived2(read_context &ctx);

	Base* read_Base(read_context &ctx)
	{
		Base* payload_ptr; int t; read_int(ctx, t);
		if (t == 0)
			payload_ptr = read_Derived1(ctx);
		if (t == 1)
			payload_ptr = read_Derived2(ctx);
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	Derived1 *read_Derived1(read_context &ctx)
	{
		auto *payload_ptr = new Derived1;
		auto &payload = *payload_ptr;
		read_int(ctx, payload.i1);
		read_string(ctx, payload.s1);
		return payload_ptr;
	}

	void read_Derived1(read_context &ctx, Derived1 &payload)
	{
		read_int(ctx, payload.i1);
		read_string(ctx, payload.s1);
	}

	Derived2 *read_Derived2(read_context &ctx)
	{
		auto *payload_ptr = new Derived2;
		auto &payload = *payload_ptr;
		read_int(ctx, payload.i1);
		read_string(ctx, payload.s1);
		return payload_ptr;
	}

	void read_Derived2(read_context &ctx, Derived2 &payload)
	{
		read_int(ctx, payload.i1);
		read_string(ctx, payload.s1);
	}

	void read_OuterG(read_context &ctx, OuterG &payload)
	{
		int count_v;
		read_int(ctx, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto *pod = read_Base(ctx);
			payload.v.push_back(pod);
		}
	}

	void init_reorder_map(map<string, CogStack> &rmap, int ver, uint seed) {
		init_rcog_A(rmap, ver, seed);
	}

}
