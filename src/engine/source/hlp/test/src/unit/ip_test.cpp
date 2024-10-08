#include <gtest/gtest.h>

#include "hlp_test.hpp"

auto constexpr NAME = "ipParser";
static const std::string TARGET = "/TargetField";

INSTANTIATE_TEST_SUITE_P(IPBuild,
                         HlpBuildTest,
                         ::testing::Values(BuildT(SUCCESS, getIPParser, {NAME, TARGET, {}, {}}),
                                           BuildT(FAILURE, getIPParser, {NAME, TARGET, {}, {"unexpected"}})));

INSTANTIATE_TEST_SUITE_P(
    IPParse,
    HlpParseTest,
    ::testing::Values(ParseT(SUCCESS,
                             "0.0.0.0",
                             j(fmt::format(R"({{"{}":"0.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.1",
                             j(fmt::format(R"({{"{}":"0.0.0.1"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.10",
                             j(fmt::format(R"({{"{}":"0.0.0.10"}})", TARGET.substr(1))),
                             8,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.100",
                             j(fmt::format(R"({{"{}":"0.0.0.100"}})", TARGET.substr(1))),
                             9,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.1.0",
                             j(fmt::format(R"({{"{}":"0.0.1.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.10.0",
                             j(fmt::format(R"({{"{}":"0.0.10.0"}})", TARGET.substr(1))),
                             8,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.0.100.0",
                             j(fmt::format(R"({{"{}":"0.0.100.0"}})", TARGET.substr(1))),
                             9,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.1.0.0",
                             j(fmt::format(R"({{"{}":"0.1.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.10.0.0",
                             j(fmt::format(R"({{"{}":"0.10.0.0"}})", TARGET.substr(1))),
                             8,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0.100.0.0",
                             j(fmt::format(R"({{"{}":"0.100.0.0"}})", TARGET.substr(1))),
                             9,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "1.0.0.0",
                             j(fmt::format(R"({{"{}":"1.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "10.0.0.0",
                             j(fmt::format(R"({{"{}":"10.0.0.0"}})", TARGET.substr(1))),
                             8,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "100.0.0.0",
                             j(fmt::format(R"({{"{}":"100.0.0.0"}})", TARGET.substr(1))),
                             9,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "100.20.0.55",
                             j(fmt::format(R"({{"{}":"100.20.0.55"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "192.168.0.1",
                             j(fmt::format(R"({{"{}":"192.168.0.1"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "255.255.255.255",
                             j(fmt::format(R"({{"{}":"255.255.255.255"}})", TARGET.substr(1))),
                             15,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "256.168.0.1", {}, 11, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "100.500.0.1", {}, 11, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "20.200.1000.1", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "20.200.0.950", {}, 12, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "20.200.0.a", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "10.20.30.40.50",
                             j(fmt::format(R"({{"{}":"10.20.30.40"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "192.168.0.1left over",
                             j(fmt::format(R"({{"{}":"192.168.0.1"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, ".20.30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10..30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20..40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20.30.", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10 .20.30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20.30. 40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.-20.30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20.-30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20.30.-40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10x.20.30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20x.30.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "10.20.30x.40", {}, 0, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "10.20.30.40x",
                             j(fmt::format(R"({{"{}":"10.20.30.40"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "10.20.30.40end",
                             j(fmt::format(R"({{"{}":"10.20.30.40"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {"end"}, {}}),
                      ParseT(SUCCESS,
                             "10.20.30.40",
                             j(fmt::format(R"({{"{}":"10.20.30.40"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {"end"}, {}}),
                      ParseT(FAILURE, "some text end", {}, 0, getIPParser, {NAME, TARGET, {"end"}, {}}),
                      ParseT(SUCCESS,
                             "192.168.11.32",
                             j(fmt::format(R"({{"{}":"192.168.11.32"}})", TARGET.substr(1))),
                             13,
                             getIPParser,
                             {NAME, TARGET, {""}, {}}),
                      ParseT(FAILURE, "some text", {}, 0, getIPParser, {NAME, TARGET, {""}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.0.1",
                             j(fmt::format(R"({{"{}":"0.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.0.2",
                             j(fmt::format(R"({{"{}":"0.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.0.3",
                             j(fmt::format(R"({{"{}":"0.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.0.0.0",
                             j(fmt::format(R"({{"{}":"0.0.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.1.0.0",
                             j(fmt::format(R"({{"{}":"0.1.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.2.0.0",
                             j(fmt::format(R"({{"{}":"0.2.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),
                      ParseT(SUCCESS,
                             "0.3.0.0",
                             j(fmt::format(R"({{"{}":"0.3.0.0"}})", TARGET.substr(1))),
                             7,
                             getIPParser,
                             {NAME, TARGET, {".1", ".2", ".3"}, {}}),

                      // IPv6
                      ParseT(SUCCESS,
                             "2345:425:2CA1:0000:0000:567:5673:23b5",
                             j(fmt::format(R"({{"{}":"2345:425:2CA1:0000:0000:567:5673:23b5"}})", TARGET.substr(1))),
                             37,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2345:0425:2CA1:0:0:0567:5673:23b5",
                             j(fmt::format(R"({{"{}":"2345:0425:2CA1:0:0:0567:5673:23b5"}})", TARGET.substr(1))),
                             33,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2345:0425:2CA1::0567:5673:23b5",
                             j(fmt::format(R"({{"{}":"2345:0425:2CA1::0567:5673:23b5"}})", TARGET.substr(1))),
                             30,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "::1",
                             j(fmt::format(R"({{"{}":"::1"}})", TARGET.substr(1))),
                             3,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0:0:0:0:0:0:0:1",
                             j(fmt::format(R"({{"{}":"0:0:0:0:0:0:0:1"}})", TARGET.substr(1))),
                             15,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "::",
                             j(fmt::format(R"({{"{}":"::"}})", TARGET.substr(1))),
                             2,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "0:0:0:0:0:0:0:0",
                             j(fmt::format(R"({{"{}":"0:0:0:0:0:0:0:0"}})", TARGET.substr(1))),
                             15,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, ":::1", {}, 4, getIPParser, {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2001:db8::1",
                             j(fmt::format(R"({{"{}":"2001:db8::1"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2001:DB8::1",
                             j(fmt::format(R"({{"{}":"2001:DB8::1"}})", TARGET.substr(1))),
                             11,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2001:db8::2:1",
                             j(fmt::format(R"({{"{}":"2001:db8::2:1"}})", TARGET.substr(1))),
                             13,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
                             j(fmt::format(R"({{"{}":"ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"}})", TARGET.substr(1))),
                             39,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "ff00::",
                             j(fmt::format(R"({{"{}":"ff00::"}})", TARGET.substr(1))),
                             6,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "::ffff:0:", {}, 9, getIPParser, {NAME, TARGET, {}, {}}),

                      // IPv4 mapped IPv6
                      ParseT(SUCCESS,
                             "::ffff:0:0.0.0.0",
                             j(fmt::format(R"({{"{}":"::ffff:0:0.0.0.0"}})", TARGET.substr(1))),
                             16,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "::ffff:192.168.0.24",
                             j(fmt::format(R"({{"{}":"::ffff:192.168.0.24"}})", TARGET.substr(1))),
                             19,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2345:0425:2CA1:0:0:0567:192.168.0.24",
                             j(fmt::format(R"({{"{}":"2345:0425:2CA1:0:0:0567:192.168.0.24"}})", TARGET.substr(1))),
                             36,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(SUCCESS,
                             "2345:0425:2CA1::0567:192.168.0.24",
                             j(fmt::format(R"({{"{}":"2345:0425:2CA1::0567:192.168.0.24"}})", TARGET.substr(1))),
                             33,
                             getIPParser,
                             {NAME, TARGET, {}, {}}),
                      ParseT(FAILURE, "2345:0425:2CA1:0:0:192.168.0.24", {}, 31, getIPParser, {NAME, TARGET, {}, {}})));
