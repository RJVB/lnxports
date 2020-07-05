/** \file
 *  This C header file was generated by $ANTLR version 3.2 debian-7ubuntu3
 *
 *     -  From the grammar source file : RSP.g
 *     -                            On : 2020-05-28 00:12:29
 *     -                 for the lexer : RSPLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer RSPLexer has the callable functions (rules) shown below,
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
 * a parser context typedef pRSPLexer, which is returned from a call to RSPLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pRSPLexer are  as follows:
 *
 *  -  void      pRSPLexer->QUOTE(pRSPLexer)
 *  -  void      pRSPLexer->LPAR(pRSPLexer)
 *  -  void      pRSPLexer->RPAR(pRSPLexer)
 *  -  void      pRSPLexer->AND(pRSPLexer)
 *  -  void      pRSPLexer->OR(pRSPLexer)
 *  -  void      pRSPLexer->NOT(pRSPLexer)
 *  -  void      pRSPLexer->EQUAL(pRSPLexer)
 *  -  void      pRSPLexer->INCLUDES(pRSPLexer)
 *  -  void      pRSPLexer->STARTSW(pRSPLexer)
 *  -  void      pRSPLexer->ENDSW(pRSPLexer)
 *  -  void      pRSPLexer->GREATER(pRSPLexer)
 *  -  void      pRSPLexer->LESS(pRSPLexer)
 *  -  void      pRSPLexer->GTE(pRSPLexer)
 *  -  void      pRSPLexer->LTE(pRSPLexer)
 *  -  void      pRSPLexer->BEFORE(pRSPLexer)
 *  -  void      pRSPLexer->AFTER(pRSPLexer)
 *  -  void      pRSPLexer->DAY(pRSPLexer)
 *  -  void      pRSPLexer->WEEK(pRSPLexer)
 *  -  void      pRSPLexer->MONTH(pRSPLexer)
 *  -  void      pRSPLexer->YEAR(pRSPLexer)
 *  -  void      pRSPLexer->TODAY(pRSPLexer)
 *  -  void      pRSPLexer->NEWLINE(pRSPLexer)
 *  -  void      pRSPLexer->WS(pRSPLexer)
 *  -  void      pRSPLexer->FIELD(pRSPLexer)
 *  -  void      pRSPLexer->INT(pRSPLexer)
 *  -  void      pRSPLexer->DATE(pRSPLexer)
 *  -  void      pRSPLexer->STR(pRSPLexer)
 *  -  void      pRSPLexer->ESCAPED(pRSPLexer)
 *  -  void      pRSPLexer->DIGIT09(pRSPLexer)
 *  -  void      pRSPLexer->DIGIT19(pRSPLexer)
 *  -  void      pRSPLexer->Tokens(pRSPLexer)
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

#ifndef	_RSPLexer_H
#define _RSPLexer_H
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
typedef struct RSPLexer_Ctx_struct RSPLexer, * pRSPLexer;



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

/** Context tracking structure for RSPLexer
 */
struct RSPLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mQUOTE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mLPAR)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mRPAR)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mAND)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mOR)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mNOT)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mEQUAL)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mINCLUDES)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mSTARTSW)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mENDSW)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mGREATER)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mLESS)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mGTE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mLTE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mBEFORE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mAFTER)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mDAY)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mWEEK)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mMONTH)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mYEAR)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mTODAY)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mNEWLINE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mWS)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mFIELD)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mINT)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mDATE)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mSTR)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mESCAPED)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mDIGIT09)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mDIGIT19)	(struct RSPLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct RSPLexer_Ctx_struct * ctx);    const char * (*getGrammarFileName)();
    void	    (*free)   (struct RSPLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pRSPLexer RSPLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pRSPLexer RSPLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
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

/* End of token definitions for RSPLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */