
#include <errno.h>
#include <stdio.h>
#include <wchar.h>
#include <bits/ensure.h>

#include <mlibc/charcode.hpp>
#include <mlibc/debug.hpp>

namespace {
	// All conversion functions mbrlen(), mbrtowc(), wcrtomb(),
	// mbsrtowcs() and wcsrtombs() have an internal state.
	__mlibc_mbstate mbrlen_state = __MLIBC_MBSTATE_INITIALIZER;
	__mlibc_mbstate mbrtowc_state = __MLIBC_MBSTATE_INITIALIZER;
}

wint_t btowc(int c) {
	if(c == EOF)
		return WEOF;

	char nc = c;
	auto cc = mlibc::current_charcode();
	wchar_t wc;
	if(auto e = cc->promote_wtranscode(nc, wc); e != mlibc::charcode_error::null)
		return WEOF;
	return wc;
}

int wctob(wint_t wc) {
	// TODO: Revisit this once we have character encoding functions.
	return wc;
}

int mbsinit(const mbstate_t *stp) {
	if(!stp)
		return -1;
	return !stp->__progress && !stp->__shift;
}

size_t mbrlen(const char *mbs, size_t mb_limit, mbstate_t *stp) {
	auto cc = mlibc::current_charcode();
	wchar_t wc;

	if(!stp)
		stp = &mbrlen_state;
	if(!mbs) {
		*stp = __MLIBC_MBSTATE_INITIALIZER;
		return 0;
	}

	mlibc::code_seq<const char> nseq{mbs, mbs + mb_limit};
	mlibc::code_seq<wchar_t> wseq{&wc, &wc + 1};
	if(auto e = cc->decode_wtranscode(nseq, wseq, *stp); e != mlibc::charcode_error::null)
		__ensure(!"decode_wtranscode() errors are not handled");
	return nseq.it - mbs;
}

size_t mbrtowc(wchar_t *wcp, const char *mbs, size_t mb_limit, mbstate_t *stp) {
	auto cc = mlibc::current_charcode();

	if(!stp)
		stp = &mbrtowc_state;
	if(!mbs) {
		*stp = __MLIBC_MBSTATE_INITIALIZER;
		return 0;
	}

	// TODO: Decode to a local wchar_t.
	__ensure(wcp);

	mlibc::code_seq<const char> nseq{mbs, mbs + mb_limit};
	mlibc::code_seq<wchar_t> wseq{wcp, wcp + 1};
	if(auto e = cc->decode_wtranscode(nseq, wseq, *stp); e != mlibc::charcode_error::null) {
		__ensure(!"decode_wtranscode() errors are not handled");
		__builtin_unreachable();
	}else{
		size_t n = wseq.it - wcp;
		if(!n) // Null-terminate resulting wide string.
			*wcp = 0;
		return n;
	}
}

size_t wcrtomb(char *__restrict, wchar_t, mbstate_t *__restrict)
	MLIBC_STUB_BODY

size_t mbsrtowcs(wchar_t *__restrict wcs, const char **__restrict mbs,
		size_t max_wcs, mbstate_t *__restrict)
	MLIBC_STUB_BODY

size_t wcsrtombs(char *mbs, const wchar_t **wcsp, size_t mb_limit, mbstate_t *stp) {
	__ensure(wcsp && "wcsrtombs() with null input");
	auto cc = mlibc::current_charcode();
	mlibc::code_seq<char> nseq{mbs, mbs + mb_limit};
	mlibc::code_seq<const wchar_t> wseq{*wcsp, nullptr};

	__ensure(mbs && "Handle !mbs case as in mbstowcs()");

	if(auto e = cc->encode_wtranscode(nseq, wseq, *stp); e != mlibc::charcode_error::null) {
		__ensure(!"encode_wtranscode() errors are not handled");
		__builtin_unreachable();
	}else{
		*wcsp = wseq.it;
		size_t n = nseq.it - mbs;
		if(n < mb_limit) // Null-terminate resulting narrow string.
			mbs[n] = 0;
		return n;
	}
}

int wcwidth(wchar_t) {
	static bool warned = false;
	if(!warned)
		mlibc::infoLogger() << "\e[35mmlibc: wcwidth() always returns 1\e[39m" << frg::endlog;
	warned = true;
	return 1;
}

