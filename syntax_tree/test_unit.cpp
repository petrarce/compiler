#define BOOST_TEST_MODULE SYNTAX_TREE
#include "node.hpp"
#include <stbl.hpp>
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(NFA_check_links)
{
	//PROG->STMT
		//STMT-> DEF STMT
			//DEF -> DEF _DEF
				//DEF ->_DEF
					//_DEF->TYPE VARLIST
						//TYPE->Type
						//VARLIST->ID, VARLIST
							//ID->Id
							//VARLIST->ID = EXPR, VARLIST
								//ID->Id
								//EXPR-> EXPR+EXPR
									//EXPR->EXPR-EXPR
										//EXPR->EXPR%EXPR
											//EXPR '/' EXPR
												//EXPR '%' EXPR
													//EXPR '<' EXPR
														//EXPR '>' EXPR
															//EXPR Eq EXPR
																//EXPR Neq EXPR
																	//('EXPR')
																		//EXPR->OBJ
																			//OBJ->LITERAL
																				//LITERAL->Literal
																	//EXPR->OBJ
																		//OBJ->ID
																			//ID->Id
																//EXPR->OBJ
																	//OBJ->LITERAL
																		//LITERAL->Literal
															//EXPR->OBJ
																//OBJ->LITERAL
																	//LITERAL->Literal
														//EXPR->OBJ
															//OBJ->LITERAL
																//LITERAL->Literal
													//EXPR->OBJ
														//OBJ->LITERAL
															//LITERAL->Literal

												//EXPR->OBJ
													//OBJ->LITERAL
														//LITERAL->Literal
											//EXPR->OBJ
												//OBJ->LITERAL
													//LITERAL->Literal
										//EXPR->OBJ
											//OBJ->LITERAL
												//LITERAL->Literal
									//EXPR->OBJ
										//OBJ->LITERAL
											//LITERAL->Literal
								//EXPR->OBJ
									//OBJ->LITERAL
										//LITERAL->Literal
							//VARLIST->ID
								//ID->Id
				//_DEF->TYPE VARLIST
					//TYPE->Type
					//VARLIST->ID
						//ID->Id

			//STMT-> _STMT STMT
				//_STMT-> WHILE
					//WHILE->While(EXPR){STMT}
						//EXPR->OBJ
							//OBJ->LITERAL
								//LITERAL->Literal
						//STMT-> _STMT
							//_STMT->IF
								//If(EXPR){STMT}Else{STMT}
									//EXPR->OBJ
										//OBJ->LITERAL
											//LITERAL->Literal
									//STMT->_STMT
										//_STMT-> ASSIGN
											//ASSIGN->ID = EXPR
												//ID->Id
												//EXPR->OBJ
													//OBJ->LITERAL
														//LITERAL->Literal
									//STMT->_STMT
										//_STMT->PROCEDURE
											//PROCEDURE->ID(ARGS)
												//ID->Id
												//ARGS->ARG, ARGS
													//ARG->EXPR
														//EXPR->OBJ
															//OBJ->LITERAL
																//LITERAL->Literal
													//ARGS->ARG
														//ARG->EXPR
															//EXPR->OBJ
	stbl& symb_tab = *stbl::get_instance();

	prog 	root(prog::PROG1);
		stmt 	stmt1(stmt::STMT1);
			def 	def1(def::DEF1);
				def 	def2(def::DEF2);
					_def 	_def1(_def::_DEF1);
						type 	type1(type::TYPE1, "real");
						varlist vlist1(varlist::VARLIST1);
							id id1(id::ID1, "id1");
							varlist vlist2(varlist::VARLIST4);
								id id2(id::ID1, "id2");
								expr expr1(expr::EXPR11);
									expr expr2(expr::EXPR2);
										expr expr3(expr::EXPR3);
											expr expr4(expr::EXPR4);
												expr expr5(expr::EXPR5);
													expr expr6(expr::EXPR6);
														expr expr7(expr::EXPR7);
															expr expr8(expr::EXPR8);
																expr expr9(expr::EXPR9);
																	expr expr10(expr::EXPR10);
																		expr expr11(expr::EXPR1);
																			obj obj1(obj::OBJ2);
																				literal literal1(literal::LITERAL1);
																				obj1.add_child(&literal1);
																			expr11.add_child(&obj1);
																		expr10.add_child(&expr11);
																		expr10.add_child(&expr11);
																	expr9.add_child(&expr10);
																	expr9.add_child(&expr11);
																expr8.add_child(&expr9);
																expr8.add_child(&expr11);
															expr7.add_child(&expr8);
															expr7.add_child(&expr11);
														expr6.add_child(&expr7);
														expr6.add_child(&expr11);
													expr5.add_child(&expr6);
													expr5.add_child(&expr11);
												expr4.add_child(&expr5);
												expr4.add_child(&expr11);
											expr3.add_child(&expr4);
											expr3.add_child(&expr11);
										expr2.add_child(&expr3);
										expr2.add_child(&expr11);
									expr1.add_child(&expr2);
								vlist2.add_child(&id2);
								vlist2.add_child(&expr1);
							vlist1.add_child(&id1);
							vlist1.add_child(&vlist2);
						_def1.add_child(&type1);
						_def1.add_child(&vlist1);
					def2.add_child(&_def1);
				_def _def2(_def::_DEF1);
					varlist vlist3(varlist::VARLIST3);
							id id3(id::ID1, "id3");
						vlist3.add_child(&id3);
					_def2.add_child(&type1);
					_def2.add_child(&vlist3);
				def1.add_child(&def2);
				def1.add_child(&_def2);
			stmt 	stmt2(stmt::STMT3);
				_stmt _stmt1(_stmt::_STMT4);
					procedure proc1(procedure::PROCEDURE2);
						proc1.add_child(&id3);
					_stmt1.add_child(&proc1);
				stmt2.add_child(&_stmt1);
			stmt1.add_child(&def1);
			stmt1.add_child(&stmt2);
		root.add_child(&stmt1);

	root.eval_attributes();
	/*previously defined syntax attributed tree should be correct*/
	BOOST_CHECK_MESSAGE(root.get_prog_ok()==true, "incorrect semantic analyse...");

	/*id's that are in varlist are already deployed in symbol table
	so new evaluation of vlist2 should find previously added to symbol table id
	and yeld error*/
	vlist2.eval_attributes();
	BOOST_CHECK_MESSAGE(vlist2.get_prog_ok()==false, "incorrect semantic analyse...");

	symb_tab.clean_buckets();
	/*after cleanyng symbol table id1 is no more there, so 
		expr12.eval_attributes should yeld semantic error*/
	expr expr12(expr::EXPR1);
		obj 	obj2(obj::OBJ1);
			obj2.add_child(&id1);
		expr12.add_child(&obj2);
	expr12.eval_attributes();
	BOOST_CHECK_MESSAGE(expr12.get_prog_ok()==false, "incorrect semantic analyse...");
}
