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
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_A(nVersion, wc, *(*ii));
	}

	void write_OuterB(long nVersion, write_context &wc, OuterB &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_A(nVersion, wc, (*ii));
	}

	void write_OuterC(long nVersion, write_context &wc, OuterC &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_string(nVersion, wc, (*ii));
	}

	void write_OuterD(long nVersion, write_context &wc, OuterD &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_string(nVersion, wc, *(*ii));
	}

	void write_OuterE(long nVersion, write_context &wc, OuterE &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_int(nVersion, wc, (*ii));
	}

	void write_OuterF(long nVersion, write_context &wc, OuterF &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_int(nVersion, wc, *(*ii));
	}

	void write_Derived1(long, write_context &wc, Derived1 &);
	void write_Derived2(long, write_context &wc, Derived2 &);

	void write_Base(long nVersion, write_context &wc, Base &payload)
	{
		const std::type_info& tid = typeid(payload);
		if (std::type_index(tid) == std::type_index(typeid(Derived1))) {
			write_int(wc,0);
			write_Derived1(nVersion, wc, dynamic_cast<Derived1 &> (payload));
		}
		if (std::type_index(tid) == std::type_index(typeid(Derived2))) {
			write_int(wc,1);
			write_Derived2(nVersion, wc, dynamic_cast<Derived2 &> (payload));
		}
	}

	void write_Derived1(long nVersion, write_context &wc, Derived1 &payload)
	{
		write_int(wc, payload.i1);
		write_string(wc, payload.s1);
	}

	void write_Derived2(long nVersion, write_context &wc, Derived2 &payload)
	{
		write_int(wc, payload.i1);
		write_string(wc, payload.s1);
	}

	void write_OuterG(long nVersion, write_context &wc, OuterG &payload)
	{
		write_int(wc, payload.v.size());
		for (auto ii = payload.v.begin();ii != payload.v.end(); ii++)
			write_Base(nVersion, wc, *(*ii));
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
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new A;
			read_A(nVersion, rc, *pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterB(long nVersion, read_context &rc, OuterB &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			A pod;
			read_A(nVersion, rc, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterC(long nVersion, read_context &rc, OuterC &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			string pod;
			read_string(nVersion, rc, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterD(long nVersion, read_context &rc, OuterD &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new string;
			read_string(nVersion, rc, *pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterE(long nVersion, read_context &rc, OuterE &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			int pod;
			read_int(nVersion, rc, pod);
			payload.v.push_back(pod);
		}
	}

	void read_OuterF(long nVersion, read_context &rc, OuterF &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto pod = new int;
			read_int(nVersion, rc, *pod);
			payload.v.push_back(pod);
		}
	}

	Derived1* read_Derived1(long, read_context &rc);
	Derived2* read_Derived2(long, read_context &rc);

	Base* read_Base(long nVersion, read_context &rc)
	{
		Base* payload_ptr; int t; read_int(rc, t);
		if (t == 0)
			payload_ptr = read_Derived1(nVersion, rc);
		if (t == 1)
			payload_ptr = read_Derived2(nVersion, rc);
		auto &payload = *payload_ptr;
		return payload_ptr;
	}

	Derived1 *read_Derived1(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new Derived1;
		auto &payload = *payload_ptr;
		read_int(rc, payload.i1);
		read_string(rc, payload.s1);
		return payload_ptr;
	}

	void read_Derived1(long nVersion, read_context &rc, Derived1 &payload)
	{
		read_int(rc, payload.i1);
		read_string(rc, payload.s1);
	}

	Derived2 *read_Derived2(long nVersion, read_context &rc)
	{
		auto *payload_ptr = new Derived2;
		auto &payload = *payload_ptr;
		read_int(rc, payload.i1);
		read_string(rc, payload.s1);
		return payload_ptr;
	}

	void read_Derived2(long nVersion, read_context &rc, Derived2 &payload)
	{
		read_int(rc, payload.i1);
		read_string(rc, payload.s1);
	}

	void read_OuterG(long nVersion, read_context &rc, OuterG &payload)
	{
		int count_v;
		read_int(rc, count_v);
		for (auto i = 0; i < count_v; i++) {
			auto *pod = read_Base(nVersion, rc);
			payload.v.push_back(pod);
		}
	}

}
