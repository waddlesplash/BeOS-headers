//******************************************************************************
//
//	File:		parse.h
//
//	Description:	Expression Parser
//	
//
//	Copyright 1993, Be Incorporated
//
//	Change History:
//
//			bgs	jun 3 93	new today
//
//******************************************************************************/

#ifndef	_PARSE_H
#define	_PARSE_H

#ifndef	_DATABASE_H
#include "Database.h"
#endif

#ifndef QUERY_H
#include "Query.h"
#endif

//----------------------------------------------------------------------

class	BParser {
private:
		char	*exp;
		char	*exp0;
		char	*tmp_copy;
		long	pt;
		long	error;
		BQuery	*the_query;
public:
		void	BParser(bool live_query, char *exp);
		void	~BParser();

		long	is_op(long *op_size);
		char	is_name(long *name_size);
		BQuery	*parse();
		void	get_table_name(char *buf);
private:
		char	*find_query_start();
		void	pre_process();
		long	factor();
		void	term();
		void	expression();
		void	tail_space();
		void	push_name(long name_size);
		void	reformulate();
		void	fill_query();
};

//------------------------------------------------------------------------------

extern	"C" void test();

#endif
