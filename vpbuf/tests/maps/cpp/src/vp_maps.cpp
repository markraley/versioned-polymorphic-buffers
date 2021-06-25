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
	}

	void write_OuterB(long nVersion, write_context &wc, OuterB &payload)
	{
	}

	void write_OuterC(long nVersion, write_context &wc, OuterC &payload)
	{
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
	}

	void read_OuterB(long nVersion, read_context &rc, OuterB &payload)
	{
	}

	void read_OuterC(long nVersion, read_context &rc, OuterC &payload)
	{
	}

}
