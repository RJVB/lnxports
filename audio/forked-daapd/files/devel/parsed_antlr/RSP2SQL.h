/** \file
 *  This C header file was generated by $ANTLR version 3.2 debian-7ubuntu3
 *
 *     -  From the grammar source file : RSP2SQL.g
 *     -                            On : 2020-05-27 14:53:21
 *     -           for the tree parser : RSP2SQLTreeParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The tree parser RSP2SQL has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pRSP2SQL, which is returned from a call to RSP2SQLNew().
 *
 * The methods in pRSP2SQL are  as follows:
 *
 *  - pANTLR3_STRING      pRSP2SQL->query(pRSP2SQL)
 *  - RSP2SQL_expr_return      pRSP2SQL->expr(pRSP2SQL)
 *  - RSP2SQL_strcrit_return      pRSP2SQL->strcrit(pRSP2SQL)
 *  - pANTLR3_COMMON_TOKEN      pRSP2SQL->strop(pRSP2SQL)
 *  - RSP2SQL_intcrit_return      pRSP2SQL->intcrit(pRSP2SQL)
 *  - pANTLR3_COMMON_TOKEN      pRSP2SQL->intop(pRSP2SQL)
 *  - RSP2SQL_datecrit_return      pRSP2SQL->datecrit(pRSP2SQL)
 *  - pANTLR3_COMMON_TOKEN      pRSP2SQL->dateop(pRSP2SQL)
 *  - RSP2SQL_datespec_return      pRSP2SQL->datespec(pRSP2SQL)
 *  - RSP2SQL_dateref_return      pRSP2SQL->dateref(pRSP2SQL)
 *  - RSP2SQL_dateintval_return      pRSP2SQL->dateintval(pRSP2SQL)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_RSP2SQL_H
#define _RSP2SQL_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct RSP2SQL_Ctx_struct RSP2SQL, * pRSP2SQL;



	/* Needs #define _GNU_SOURCE for strptime() */

	#include <stdio.h>
	#include <string.h>
	#include <time.h>
	#include <stdint.h>

	#include "logger.h"
	#include "db.h"
	#include "misc.h"
	#include "rsp_query.h"


#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
typedef struct RSP2SQL_expr_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    pANTLR3_STRING result;
    int valid;
}
    RSP2SQL_expr_return;

typedef struct RSP2SQL_strcrit_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    pANTLR3_STRING result;
    int valid;
}
    RSP2SQL_strcrit_return;

typedef struct RSP2SQL_intcrit_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    pANTLR3_STRING result;
    int valid;
}
    RSP2SQL_intcrit_return;

typedef struct RSP2SQL_datecrit_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    pANTLR3_STRING result;
    int valid;
}
    RSP2SQL_datecrit_return;

typedef struct RSP2SQL_datespec_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    time_t date;
    int valid;
}
    RSP2SQL_datespec_return;

typedef struct RSP2SQL_dateref_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    time_t date;
    int valid;
}
    RSP2SQL_dateref_return;

typedef struct RSP2SQL_dateintval_return_struct
{
    pANTLR3_BASE_TREE       start;
    pANTLR3_BASE_TREE       stop;   
    time_t period;
    int valid;
}
    RSP2SQL_dateintval_return;



/** Context tracking structure for RSP2SQL
 */
struct RSP2SQL_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_TREE_PARSER	    pTreeParser;


     pANTLR3_STRING (*query)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_expr_return (*expr)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_strcrit_return (*strcrit)	(struct RSP2SQL_Ctx_struct * ctx);
     pANTLR3_COMMON_TOKEN (*strop)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_intcrit_return (*intcrit)	(struct RSP2SQL_Ctx_struct * ctx);
     pANTLR3_COMMON_TOKEN (*intop)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_datecrit_return (*datecrit)	(struct RSP2SQL_Ctx_struct * ctx);
     pANTLR3_COMMON_TOKEN (*dateop)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_datespec_return (*datespec)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_dateref_return (*dateref)	(struct RSP2SQL_Ctx_struct * ctx);
     RSP2SQL_dateintval_return (*dateintval)	(struct RSP2SQL_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct RSP2SQL_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pRSP2SQL RSP2SQLNew         (pANTLR3_COMMON_TREE_NODE_STREAM instream);
ANTLR3_API pRSP2SQL RSP2SQLNewSSD      (pANTLR3_COMMON_TREE_NODE_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the tree parser will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define STARTSW      14
#define WEEK      26
#define TODAY      24
#define YEAR      28
#define ENDSW      15
#define GTE      20
#define BEFORE      21
#define DAY      25
#define INT      16
#define NOT      11
#define AFTER      22
#define AND      6
#define EOF      -1
#define LTE      19
#define MONTH      27
#define DIGIT19      31
#define INCLUDES      13
#define STR      10
#define QUOTE      29
#define GREATER      18
#define WS      30
#define LPAR      7
#define NEWLINE      4
#define EQUAL      12
#define OR      5
#define LESS      17
#define FIELD      9
#define RPAR      8
#define ESCAPED      33
#define DATE      23
#define DIGIT09      32
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for RSP2SQL
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
