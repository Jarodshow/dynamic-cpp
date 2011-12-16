/*
    Copyright (C) 2009, 2011 Ferruccio Barletta (ferruccio.barletta@gmail.com)

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#include <sstream>
using namespace std;

#define BOOST_TEST_MODULE dynamic_tests
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "dynamic.h"

using namespace dynamic;

BOOST_AUTO_TEST_CASE (ctor) {
    BOOST_CHECK_NO_THROW(var());

    var v;
    BOOST_TEST_MESSAGE("sizeof(var) = " << sizeof(v));
}

BOOST_AUTO_TEST_CASE (simple_ctor) {
    stringstream ss;

    var v;
    BOOST_CHECK(v.is_null());
    BOOST_CHECK(!v.is_collection());
    BOOST_CHECK_EQUAL(v.type(), "null");
    ss << v;
    BOOST_CHECK_EQUAL(ss.str(), "$");

    var vi(12);
    BOOST_CHECK(vi.is_int());
    BOOST_CHECK(vi.is_numeric());
    BOOST_CHECK(!vi.is_collection());
    BOOST_CHECK_EQUAL(vi.type(), "int");
    BOOST_CHECK_EQUAL(int(vi), 12);
    ss.str(string());
    ss << vi;
    BOOST_CHECK_EQUAL(ss.str(), "12");

    var vd(100.5);
    BOOST_CHECK(vd.is_double());
    BOOST_CHECK(vd.is_numeric());
    BOOST_CHECK(!vd.is_collection());
    BOOST_CHECK_EQUAL(vd.type(), "double");
    BOOST_CHECK_CLOSE(double(vd), 100.5, 1e-6);
    ss.str(string());
    ss << vd;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");

    var vs("hello");
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK(!vs.is_collection());
    BOOST_CHECK_EQUAL(vs.type(), "string");
    BOOST_CHECK_EQUAL(string(vs), "hello");
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "'hello'");

    var vn(vs);
    BOOST_CHECK(vn.is_string());
    BOOST_CHECK(!vn.is_collection());
    BOOST_CHECK_EQUAL(vn.type(), "string");
    BOOST_CHECK_EQUAL(string(vn), "hello");
    ss.str(string());
    ss << vn;
    BOOST_CHECK_EQUAL(ss.str(), "'hello'");
}

BOOST_AUTO_TEST_CASE (simple_assign) {
    stringstream ss;

    var v(10);
    BOOST_CHECK(v.is_int());
    v = $;
    BOOST_CHECK(v.is_null());
    BOOST_CHECK(!v.is_collection());
    BOOST_CHECK_EQUAL(v.type(), "null");
    ss << v;
    BOOST_CHECK_EQUAL(ss.str(), "$");

    var vi;
    vi = 12;
    BOOST_CHECK(vi.is_int());
    BOOST_CHECK(vi.is_numeric());
    BOOST_CHECK(!vi.is_collection());
    BOOST_CHECK_EQUAL(vi.type(), "int");
    BOOST_CHECK_EQUAL(int(vi), 12);
    ss.str(string());
    ss << vi;
    BOOST_CHECK_EQUAL(ss.str(), "12");

    var vd;
    vd = 100.5;
    BOOST_CHECK(vd.is_double());
    BOOST_CHECK(vd.is_numeric());
    BOOST_CHECK(!vd.is_collection());
    BOOST_CHECK_EQUAL(vd.type(), "double");
    BOOST_CHECK_CLOSE(double(vd), 100.5, 1e-6);
    ss.str(string());
    ss << vd;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");

    var vs;
    vs = "hello";
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK_EQUAL(vs.type(), "string");
    BOOST_CHECK_EQUAL(string(vs), "hello");
    BOOST_CHECK(!vs.is_collection());
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "'hello'");

    string world = "world";
    vs = world;
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK(!vs.is_collection());
    BOOST_CHECK_EQUAL(vs.type(), "string");
    BOOST_CHECK_EQUAL(string(vs), "world");
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "'world'");

    var vn;
    vn = vd;
    BOOST_CHECK(vn.is_double());
    BOOST_CHECK(vn.is_numeric());
    BOOST_CHECK(!vn.is_collection());
    BOOST_CHECK_EQUAL(vn.type(), "double");
    BOOST_CHECK_CLOSE(double(vn), 100.5, 1e-6);
    ss.str(string());
    ss << vn;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");
}
