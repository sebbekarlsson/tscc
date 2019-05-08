#include "include/ASTReturn.h"
#include <stdlib.h>


AST_return* init_ast_return(token* t, AST* statement) {
	AST_return* return_statement = calloc(1, sizeof(struct AST_RETURN_STRUCT));
	AST_constructor((AST*)return_statement, t, AST_RETURN);

	return_statement->statement = statement;
	return return_statement;
}
