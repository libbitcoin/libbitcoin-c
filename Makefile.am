###############################################################################
#  Copyright (c) 2014-2015 libbitcoin-network developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Automake settings.
#==============================================================================
# Look for macros in the m4 subdirectory.
#------------------------------------------------------------------------------
ACLOCAL_AMFLAGS = -I m4


# Distribute, make and install products.
#==============================================================================
# files => ${pkgconfigdir}
#------------------------------------------------------------------------------
pkgconfig_DATA = \
    libbitcoin-c.pc

# files => ${docdir}
#------------------------------------------------------------------------------
doc_DATA = \
    AUTHORS \
    COPYING \
    ChangeLog \
    INSTALL \
    NEWS \
    README

# src/libbitcoin-c.la => ${libdir}
#------------------------------------------------------------------------------
lib_LTLIBRARIES = src/libbitcoin-c.la
src_libbitcoin_c_la_CPPFLAGS = -I${srcdir}/include ${bitcoin_CPPFLAGS}
src_libbitcoin_c_la_LIBADD = ${bitcoin_LIBS}
src_libbitcoin_c_la_SOURCES = \
    src/utility/data.cpp \
    src/utility/string.cpp \
    src/formats/base_16.cpp \
    src/math/hash.cpp \
    src/math/elliptic_curve.cpp \
    src/wallet/hd_public.cpp \
    src/wallet/hd_private.cpp

# local: test/libbitcoin_network_test
#------------------------------------------------------------------------------
if WITH_TESTS

TESTS = libbitcoin_c_test_runner.sh

check_PROGRAMS = test/libbitcoin_c_test
test_libbitcoin_c_test_CPPFLAGS = -I${srcdir}/include ${bitcoin_CPPFLAGS}
test_libbitcoin_c_test_LDADD = src/libbitcoin-c.la ${boost_unit_test_framework_LIBS} ${bitcoin_LIBS}
test_libbitcoin_c_test_SOURCES = \
    test/main.cpp \
    test/utility/data.cpp \
    test/formats/base_16.cpp \
    test/math/hash.cpp \
    test/wallet/hd_public.cpp

endif WITH_TESTS

# files => ${includedir}/bitcoin
#------------------------------------------------------------------------------
include_bitcoindir = ${includedir}/bitcoin
include_bitcoin_HEADERS = \
    include/bitcoin/bitcoin.h

include_bitcoin_bitcoin_c_mathdir = ${includedir}/bitcoin/bitcoin/c/math
include_bitcoin_bitcoin_c_math_HEADERS = \
    include/bitcoin/bitcoin/c/math/hash.h

include_bitcoin_bitcoin_c_utilitydir = ${includedir}/bitcoin/bitcoin/c/utility
include_bitcoin_bitcoin_c_utility_HEADERS = \
    include/bitcoin/bitcoin/c/utility/data.h \
    include/bitcoin/bitcoin/c/utility/string.h

include_bitcoin_bitcoin_c_formatsdir = ${includedir}/bitcoin/bitcoin/c/formats
include_bitcoin_bitcoin_c_formats_HEADERS = \
    include/bitcoin/bitcoin/c/formats/base_16.h

include_bitcoin_bitcoin_c_walletdir = ${includedir}/bitcoin/bitcoin/c/wallet
include_bitcoin_bitcoin_c_wallet_HEADERS = \
    include/bitcoin/bitcoin/c/wallet/hd_public.h \
    include/bitcoin/bitcoin/c/wallet/hd_private.h

include_bitcoin_bitcoin_c_internal_mathdir = ${includedir}/bitcoin/bitcoin/c/internal/math
include_bitcoin_bitcoin_c_internal_math_HEADERS = \
    include/bitcoin/bitcoin/c/internal/math/hash.hpp \
    include/bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp

include_bitcoin_bitcoin_c_internal_utilitydir = ${includedir}/bitcoin/bitcoin/c/internal/utility
include_bitcoin_bitcoin_c_internal_utility_HEADERS = \
    include/bitcoin/bitcoin/c/internal/utility/data.hpp

include_bitcoin_bitcoin_c_internal_walletdir = ${includedir}/bitcoin/bitcoin/c/internal/wallet
include_bitcoin_bitcoin_c_internal_wallet_HEADERS = \
    include/bitcoin/bitcoin/c/internal/wallet/hd_public.hpp

