#include "toyjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch) do{ assert(*c->json == (ch)); c->json++;}while(0)

typedef struct {
	const char *json;
}toyContext;

int toyParse(toyValue *v, const char *json);
static void toyParseWhitespace(toyContext *c);
static int toyParseValue(toyContext *c, toyValue *v);
static int toyParseNull(toyContext *c, toyValue *v);
static int toyParseTrue(toyContext *c, toyValue *v);
static int toyParseFalse(toyContext *c, toyValue *v);


int toyParse(toyValue *v, const char *json) {
	toyContext *c;
	assert(v != NULL);
	c->json = json;
	v->type = TOY_NULL;
	toyParseWhitespace(c);
	return toyParseValue(c, v);
}


static void toyParseWhitespace(toyContext *c) {
	char *p = c;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c->json = p;
}

static int toyParseValue(toyContext *c, toyValue *v) {
	switch (*c->json) {
		case 'n': return toyParseNull(c, v);
		case 't': return toyParseTrue(c, v);
		case 'f': return toyParseFalse(c, v);
		case '\0': return TOY_PARSE_EXPECT_VALUE;
		default: return TOY_PARSE_INVALID_VALUE;
	}
}

static int toyParseNull(toyContext *c, toyValue *v) {
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
		return TOY_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = TOY_NULL;
	return TOY_PARSE_OK;
}

static int toyParseTrue(toyContext *c, toyValue *v) {
	EXPECT(c, 't');
	if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
		return TOY_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = TOY_TRUE;
	return TOY_PARSE_OK;
}


static int toyParseFalse(toyContext *c, toyValue *v) {
	EXPECT(c, 'f');
	if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
		return TOY_PARSE_INVALID_VALUE;
	}
	c->json += 4;
	v->type = TOY_FALSE;
	return TOY_PARSE_OK;
}

