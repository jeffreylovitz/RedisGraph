#include <stdlib.h>
#include <pthread.h>
#include "../deps/GraphBLAS/Include/GraphBLAS.h"
#include "../deps/libcypher-parser/lib/src/cypher-parser.h"
#include "../src/query_ctx.h"
#include "../src/ast/ast.h"
#include "../src/execution_plan/execution_plan.h"
#include "../src/commands/cmd_dispatcher.h"
#include "../src/commands/cmd_query.h"

void *RACETEST_THREAD(void *ctx) {
	Graph_Query(ctx);
	return NULL;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Provide Cypher query as sole binary argument.\n");
		return 1;
	}

	CommandCtx *ctx = rm_calloc(1, sizeof(CommandCtx));
	ctx->query = argv[1];
	ctx->graph_ctx = GraphContext_Retrieve(NULL, NULL, true, true);

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, RACETEST_THREAD, ctx);
	pthread_create(&thread2, NULL, RACETEST_THREAD, ctx);

	return 0;
}

