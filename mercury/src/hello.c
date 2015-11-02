/*
 *  Very simple example program
 */

#include "duktape.h"

int adder(duk_context *ctx) {
	int i;
	int n = duk_get_top(ctx);  /* #args */
	double res = 0.0;

	for (i = 0; i < n; i++) {
		res += duk_to_number(ctx, i);
	}

	duk_push_number(ctx, res);
	return 1;  /* one return value */
}

int main(int argc, char *argv[]) {
	duk_context *ctx = duk_create_heap_default();

	(void) argc; (void) argv;  /* suppress warning */

	duk_eval_string(ctx, "print('Hello world!');");

	duk_push_global_object(ctx);
	duk_push_c_function(ctx, adder, DUK_VARARGS);
	duk_put_prop_string(ctx, -2, "adder");
	duk_push_c_function(ctx, [](duk_context *ctx) -> int {
		duk_push_number(ctx, (double) 745);
		return 1;
	}, DUK_VARARGS);
	duk_put_prop_string(ctx, -2, "adder_two");
	duk_pop(ctx);  /* pop global */

	duk_eval_string(ctx, "print('2+3+4=' + adder(2, 3, 4));");
	duk_eval_string(ctx, "print('2+3+4=' + adder_two(2, 3, 4));");
	duk_pop(ctx);  /* pop eval result */

	duk_destroy_heap(ctx);

	return 0;
}
