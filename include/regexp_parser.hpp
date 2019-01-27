#pragma once
#include <string>
#include <types.hpp>
#include <nfa.hpp>

int regex2nfa(string& regex, const enum SATOKENS token, nfa& new_nfa);