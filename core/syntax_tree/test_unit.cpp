#define BOOST_TEST_MODULE SYNTAX_TREE
#include <st_node.hpp>
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

	shared_ptr<prog> 	root(new prog(prog::PROG1));
		shared_ptr<stmt> 	stmt1(new stmt(stmt::STMT1));
			shared_ptr<def> 	def1(new def(def::DEF1));
				shared_ptr<def> 	def2(new def(def::DEF2));
					shared_ptr<_def> 	_def1(new _def(_def::_DEF1));
						shared_ptr<type> 	type1(new type(type::TYPE1, "real"));
						shared_ptr<varlist> vlist1(new varlist(varlist::VARLIST1));
							shared_ptr<id> id1(new id(id::ID1, "id1"));
							shared_ptr<varlist> vlist2(new varlist(varlist::VARLIST4));
								shared_ptr<id> id2(new id(id::ID1, "id2"));
								shared_ptr<expr> expr1(new expr(expr::EXPR11));
									shared_ptr<expr> expr2(new expr(expr::EXPR2));
										shared_ptr<expr> expr3(new expr(expr::EXPR3));
											shared_ptr<expr> expr4(new expr(expr::EXPR4));
												shared_ptr<expr> expr5(new expr(expr::EXPR5));
													shared_ptr<expr> expr6(new expr(expr::EXPR6));
														shared_ptr<expr> expr7(new expr(expr::EXPR7));
															shared_ptr<expr> expr8(new expr(expr::EXPR8));
																shared_ptr<expr> expr9(new expr(expr::EXPR9));
																	shared_ptr<expr> expr10(new expr(expr::EXPR10));
																		shared_ptr<expr> expr11(new expr(expr::EXPR1));
																			shared_ptr<obj> obj1(new obj(obj::OBJ2));
																				shared_ptr<literal> literal1(new literal(literal::LITERAL1));
																				obj1->add_child(literal1);
																			expr11->add_child(obj1);
																		expr10->add_child(expr11);
																		expr10->add_child(expr11);
																	expr9->add_child(expr10);
																	expr9->add_child(expr11);
																expr8->add_child(expr9);
																expr8->add_child(expr11);
															expr7->add_child(expr8);
															expr7->add_child(expr11);
														expr6->add_child(expr7);
														expr6->add_child(expr11);
													expr5->add_child(expr6);
													expr5->add_child(expr11);
												expr4->add_child(expr5);
												expr4->add_child(expr11);
											expr3->add_child(expr4);
											expr3->add_child(expr11);
										expr2->add_child(expr3);
										expr2->add_child(expr11);
									expr1->add_child(expr2);
								vlist2->add_child(id2);
								vlist2->add_child(expr1);
							vlist1->add_child(id1);
							vlist1->add_child(vlist2);
						_def1->add_child(type1);
						_def1->add_child(vlist1);
					def2->add_child(_def1);
				shared_ptr<_def> _def2(new _def(_def::_DEF1));
					shared_ptr<varlist> vlist3(new varlist(varlist::VARLIST3));
							shared_ptr<id> id3(new id(id::ID1, "id3"));
						vlist3->add_child(id3);
					_def2->add_child(type1);
					_def2->add_child(vlist3);
				def1->add_child(def2);
				def1->add_child(_def2);
			shared_ptr<stmt> 	stmt2(new stmt(stmt::STMT3));
				shared_ptr<_stmt> _stmt1(new _stmt(_stmt::_STMT4));
					shared_ptr<procedure> proc1(new procedure(procedure::PROCEDURE2));
						proc1->add_child(id3);
					_stmt1->add_child(proc1);
				stmt2->add_child(_stmt1);
			stmt1->add_child(def1);
			stmt1->add_child(stmt2);
		root->add_child(stmt1);

	root->eval_attributes();
	/*previously defined syntax attributed tree should be correct*/
	BOOST_CHECK_MESSAGE(root->get_prog_ok()==true, "incorrect semantic analyse-...");

	/*id's that are in varlist are already deployed in symbol table
	so new evaluation of vlist2 should find previously added to symbol table id
	and yeld error*/
	vlist2->eval_attributes();
	BOOST_CHECK_MESSAGE(vlist2->get_prog_ok()==false, "incorrect semantic analyse...");

	symb_tab.clean_buckets();
	/*after cleanyng symbol table id1 is no more there, so 
		expr12->eval_attributes should yeld semantic error*/
	shared_ptr<expr> expr12( new expr(expr::EXPR1));
		shared_ptr<obj> 	obj2 (new obj(obj::OBJ1));
			obj2->add_child(id1);
		expr12->add_child(obj2);
	expr12->eval_attributes();
	BOOST_CHECK_MESSAGE(expr12->get_prog_ok()==false, "incorrect semantic analyse...");

}
