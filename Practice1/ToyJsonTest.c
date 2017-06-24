#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toyjson.h"

static int mainRet = 0;
static int testCount = 0;
static int testPass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do {\
		testCount++;\
		if (equality) {\
			testPass++;\
		} else {\
			fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
			mainRet = 1;\
		}\
	} while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void testParse();
static void testParseNull();
static void testParseTrue();
static void testParseFalse();
static void testParseInvalidValue();

int main(void) {
	testParse();
	printf("%d/%d (%3.2f%%) passed\n", testPass, testCount, testPass * 100.0 / testCount);
    return mainRet;
}

static void testParse() {
	testParseNull();
	testParseTrue();
	testParseFalse();
	testParseInvalidValue();
}

static void testParseNull() {
	toyValue v;
	v.type = TOY_FALSE;
	EXPECT_EQ_INT(TOY_PARSE_OK, toyParse(&v, "null"));
}

static void testParseTrue() {
	toyValue v;
	v.type = TOY_FALSE;
	EXPECT_EQ_INT(TOY_PARSE_OK, toyParse(&v, "true"));
}

static void testParseFalse() {
	toyValue v;
	v.type = TOY_FALSE;
	EXPECT_EQ_INT(TOY_PARSE_OK, toyParse(&v, "false"));
}

static void testParseInvalidValue() {
	toyValue v;
	v.type = TOY_FALSE;
	EXPECT_EQ_INT(TOY_PARSE_INVALID_VALUE, toyParse(&v, "summer"));

	v.type = TOY_FALSE;
	EXPECT_EQ_INT(TOY_PARSE_INVALID_VALUE, toyParse(&v, "nul"));
}











