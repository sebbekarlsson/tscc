set(INCLUDE_SRC
    include/AST.h
    include/ASTArray.h
    include/ASTAssignment.h
    include/ASTAttributeAccess.h
    include/ASTBinop.h
    include/ASTClass.h
    include/ASTCompound.h
    include/ASTDatatype.h
    include/ASTFloat.h
    include/ASTFunctionCall.h
    include/ASTFunctionDefinition.h
    include/ASTIf.h
    include/ASTReturn.h
    include/ASTInteger.h
    include/ASTNull.h
    include/ASTObjectInit.h
    include/ASTString.h
    include/ASTUndefined.h
    include/ASTVariable.h
    include/ASTVariableDefinition.h
    include/ASTWhile.h
    include/dynamic_list.h
    include/io.h
    include/lex.h
    include/outputbuffer.h
    include/parse.h
    include/remap.h
    include/scope.h
    include/strutils.h
    include/token.h
    include/visit.h
)

set(AST_SRC
    AST.c
    ASTArray.c
    ASTAssignment.c
    ASTAttributeAccess.c
    ASTBinop.c
    ASTClass.c
    ASTCompound.c
    ASTDatatype.c
    ASTFloat.c
    ASTFunctionCall.c
    ASTFunctionDefinition.c
    ASTIf.c
    ASTReturn.c
    ASTInteger.c
    ASTNull.c
    ASTObjectInit.c
    ASTString.c
    ASTUndefined.c
    ASTVariable.c
    ASTVariableDefinition.c
    ASTWhile.c    
)

set(TSCC_SRC
    dynamic_list.c
    io.c
    lex.c
    outputbuffer.c
    parse.c
    remap.c
    scope.c
    strutils.c
    token.c
    visit.c
)

source_group("include", FILES ${INCLUDE_SRC})
source_group("AST" FILES ${AST_SRC})
source_group("TSCC" FILES ${TSCC_SRC})

#add_library(TSCC SHARED
#            Main.c
#            ${INCLUDE_SRC}
#            ${AST_SRC}
#            ${TSCC_SRC}
#)


add_executable(TSCC
    main.c
    ${INCLUDE_SRC}
    ${AST_SRC}
    ${TSCC_SRC}
)

set(CMAKE_CXX_FLAGS_RELEASE "/MD")
set(CMAKE_CXX_FLAGS_DEBUG "/MD")

target_compile_options(TSCC PUBLIC /GS- /GR-)


include_directories(TSCC ${CMAKE_CURRENT_SOURCE_DIR})
#set_target_properties(TSCC PROPERTIES OUTPUT_NAME tscc)