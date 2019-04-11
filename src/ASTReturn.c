#include "include/ASTReturn.h"
#include <stdlib.h>


AST_return* init_ast_return(token* t, AST* statement) {
	AST_return* returnStatement = calloc(1, sizeof(struct AST_RETURN_STRUCT));
	AST_constructor((AST*)returnStatement, t, AST_RETURN);

	returnStatement->statement = statement;
	return returnStatement;
}