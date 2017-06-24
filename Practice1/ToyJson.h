#ifndef TOYJSON_H__
#define TOYJSON_H__

typedef enum { TOY_NULL, TOY_FALSE, TOY_TRUE, TOY_NUMBER, TOY_STRING, TOY_ARRAY, TOY_OBJECT } toyType;

typedef struct {
	toyType type;
}toyValue;

enum {
    TOY_PARSE_OK = 0,
    TOY_PARSE_EXPECT_VALUE,
    TOY_PARSE_INVALID_VALUE,
    TOY_PARSE_ROOT_NOT_SINGULAR
};

int toyParse(toyValue* v, const char* json);

toyType toyGetType(const toyValue* v);

#endif /* TOYJSON_H__ */
