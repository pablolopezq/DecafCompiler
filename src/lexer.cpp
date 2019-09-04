#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include "ExprLexer.h"

enum class State {
    Start_q0,
    Start_q1,
    BCom_q0,
    BCom_q1,
    BCom_q3,
    LCom_q0,
    ID_q0,
    ID_q1,
    ID_q2,
    Operators_q0,
    Operators_q10,
    Operators_q13,
    Operators_q18,
    Operators_q23,
    Operators_q24,
    Operators_q4,
    Operators_q8,
    Punctuation_q0,
    Numbers_q0,
    Numbers_q1,
    Numbers_q2,
    Numbers_q4,
    Numbers_q5,
    Numbers_q6,
    StringConst_q0,
    StringConst_q2,
    StringConst_q3,
    StringConst_q4,
    CharConst_q0,
    CharConst_q1,
    CharConst_q2,
    CharConst_q4,
};

Symbol ExprLexer::checkKeyword(string text){
    if(text == "break")
        return Symbol::KW_BREAK;
    else if(text == "while")
        return Symbol::KW_WHILE;
    else if(text == "bool")
        return Symbol::KW_BOOL;
    else if(text == "void")
        return Symbol::KW_VOID;
    else if(text == "continue")
        return Symbol::KW_CONTINUE;
    else if(text == "class")
        return Symbol::KW_CLASS;
    else if(text == "else")
        return Symbol::KW_ELSE;
    else if(text == "extends")
        return Symbol::KW_EXTENDS;
    else if(text == "false")
        return Symbol::KW_FALSE;
    else if(text == "for")
        return Symbol::KW_FOR;
    else if(text == "if")
        return Symbol::KW_IF;
    else if(text == "int")
        return Symbol::KW_INT;
    else if(text == "new")
        return Symbol::KW_NEW;
    else if(text == "null")
        return Symbol::KW_NULL;
    else if(text == "return")
        return Symbol::KW_RETURN;
    else if(text == "rot")
        return Symbol::KW_ROT;
    else if(text == "true")
        return Symbol::KW_TRUE;
    else
        return Symbol::ID;
}

Symbol ExprLexer::getNextToken() 
{
    text = "";
    State state = State::Start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // Start
            case State::Start_q0:
                state = State::Start_q1;
                text="";
                break;
            case State::Start_q1:
                if ((ch == '\n') || (ch == ' ') || (ch == '\t')) {
                    state = State::Start_q1;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Symbol::Eof;
                } else {
                    // Trying next automaton 'ID'
                    state = State::ID_q0;
                }
                break;
            // BCom
            case State::BCom_q0:
                if (ch == '*') {
                    state = State::BCom_q1;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    text += ch;
                    state = State::BCom_q3;
                    ch = getNextChar();
                } else {
                    state = State::BCom_q0;
                    ch = getNextChar();
                }
                break;
            case State::BCom_q1:
                if (ch == '/') {
                    state = State::Start_q0;
                    ch = getNextChar();
                } else {
                    state = State::BCom_q0;
                }
                break;
            // LCom
            case State::LCom_q0:
                if (ch == '\n') {
                    state = State::Start_q0;
                    ch = getNextChar();
                } else {
                    state = State::LCom_q0;
                    ch = getNextChar();
                }
                break;
            // ID
            case State::ID_q0:
                if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ID_q1;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'Operators'
                    state = State::Operators_q0;
                }
                break;
            case State::ID_q1:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ID_q1;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return checkKeyword(text);
                }
                break;
            // Operators
            case State::Operators_q0:
                if (ch == '/') {
                    text += ch;
                    state = State::Operators_q4;
                    ch = getNextChar();
                } else if (ch == '=') {
                    text += ch;
                    state = State::Operators_q8;
                    ch = getNextChar();
                } else if (ch == '&') {
                    text += ch;
                    state = State::Operators_q24;
                    ch = getNextChar();
                } else if (ch == '-') {
                    text += ch;
                    return Symbol::SUB;
                } else if (ch == '+') {
                    text += ch;
                    return Symbol::SUM;
                } else if (ch == '>') {
                    text += ch;
                    state = State::Operators_q10;
                    ch = getNextChar();
                } else if (ch == '*') {
                    text += ch;
                    return Symbol::MULT;
                } else if (ch == '!') {
                    text += ch;
                    state = State::Operators_q18;
                    ch = getNextChar();
                } else if (ch == '|') {
                    text += ch;
                    state = State::Operators_q23;
                    ch = getNextChar();
                } else if (ch == '<') {
                    text += ch;
                    state = State::Operators_q13;
                    ch = getNextChar();
                } else if (ch == '%') {
                    text += ch;
                    return Symbol::MOD;
                } else {
                    // Trying next automaton 'Punctuation'
                    state = State::Punctuation_q0;
                }
                break;
            case State::Operators_q10:
                if (ch == '>') {
                    text += ch;
                    return Symbol::SHIFT_RIGHT;
                } else if (ch == '=') {
                    text += ch;
                    return Symbol::GTE;
                } else {
                    ungetChar(ch);
                    return Symbol::GT;
                }
                break;
            case State::Operators_q13:
                if (ch == '=') {
                    text += ch;
                    return Symbol::LT;
                } else if (ch == '<') {
                    text += ch;
                    return Symbol::SHIFT_LEFT;
                } else {
                    ungetChar(ch);
                    return Symbol::LTE;
                }
                break;
            case State::Operators_q18:
                if (ch == '=') {
                    text += ch;
                    return Symbol::NOT_EQUAL;
                } else {
                    ungetChar(ch);
                    return Symbol::NEGATION;
                }
                break;
            case State::Operators_q23:
                if (ch == '|') {
                    text += ch;
                    return Symbol::OR;
                } else {
                    // Trying next automaton 'Punctuation'
                    state = State::Punctuation_q0;
                }
                break;
            case State::Operators_q24:
                if (ch == '&') {
                    text += ch;
                    return Symbol::AND;
                } else {
                    // Trying next automaton 'Punctuation'
                    state = State::Punctuation_q0;
                }
                break;
            case State::Operators_q4:
                if (ch == '/') {
                    state = State::LCom_q0;
                    ch = getNextChar();
                } else if (ch == '*') {
                    state = State::BCom_q0;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::DIV;
                }
                break;
            case State::Operators_q8:
                if (ch == '=') {
                    text += ch;
                    return Symbol::EQUAL;
                } else {
                    ungetChar(ch);
                    return Symbol::ASSIGN;
                }
                break;
            // Punctuation
            case State::Punctuation_q0:
                if (ch == ',') {
                    text += ch;
                    return Symbol::COMMA;
                } else if (ch == ';') {
                    text += ch;
                    return Symbol::SEMICOLON;
                } else if (ch == '[') {
                    text += ch;
                    return Symbol::OPEN_BRACKET;
                } else if (ch == '}') {
                    text += ch;
                    return Symbol::CLOSE_KEY;
                } else if (ch == '.') {
                    text += ch;
                    return Symbol::POINT;
                } else if (ch == ')') {
                    text += ch;
                    return Symbol::CLOSE_PAREN;
                } else if (ch == ']') {
                    text += ch;
                    return Symbol::CLOSE_BRACKET;
                } else if (ch == '{') {
                    text += ch;
                    return Symbol::OPEN_KEY;
                } else if (ch == '(') {
                    text += ch;
                    return Symbol::OPEN_PAREN;
                } else {
                    // Trying next automaton 'Numbers'
                    state = State::Numbers_q0;
                }
                break;
            // Numbers
            case State::Numbers_q0:
                if ((ch >= '1') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else if (ch == '0') {
                    text += ch;
                    state = State::Numbers_q4;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'StringConst'
                    state = State::StringConst_q0;
                }
                break;
            case State::Numbers_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else if (ch == '.') {
                    text += ch;
                    state = State::Numbers_q2;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::Number;
                }
                break;
            case State::Numbers_q2:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q2;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::Number;
                }
                break;
            case State::Numbers_q4:
                if (ch == 'x') {
                    text += ch;
                    state = State::Numbers_q5;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::Number;
                }
                break;
            case State::Numbers_q5:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::Numbers_q6;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'StringConst'
                    state = State::StringConst_q0;
                }
                break;
            case State::Numbers_q6:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::Numbers_q6;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::Number;
                }
                break;
            // StringConst
            case State::StringConst_q0:
                if (ch == '"') {
                    text += ch;
                    state = State::StringConst_q2;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'CharConst'
                    state = State::CharConst_q0;
                }
                break;
            case State::StringConst_q2:
                if (ch == '\\') {
                    text += ch;
                    state = State::StringConst_q4;
                    ch = getNextChar();
                } else if (ch == '"') {
                    text += ch;
                    return Symbol::STRING_CONST;
                } else {
                    text += ch;
                    state = State::StringConst_q2;
                    ch = getNextChar();
                }
                break;
            case State::StringConst_q3:
                if (ch == '"') {
                    text += ch;
                    return Symbol::STRING_CONST;
                } else {
                    // Trying next automaton 'CharConst'
                    state = State::CharConst_q0;
                }
                break;
            case State::StringConst_q4:
                if ((ch == 't') || (ch == 'r') || (ch == 'n') || (ch == '\\')) {
                    text += ch;
                    state = State::StringConst_q3;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'CharConst'
                    state = State::CharConst_q0;
                }
                break;
            // CharConst
            case State::CharConst_q0:
                if (ch == '\'') {
                    text += ch;
                    state = State::CharConst_q1;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::Start_q0;
                }
                break;
            case State::CharConst_q1:
                    text += ch;
                state = State::CharConst_q2;
                ch = getNextChar();
                break;
            case State::CharConst_q2:
                if (ch == '\\') {
                    text += ch;
                    state = State::CharConst_q4;
                    ch = getNextChar();
                } else if (ch == '\'') {
                    text += ch;
                    return Symbol::CHAR_CONST;
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::Start_q0;
                }
                break;
            case State::CharConst_q4:
                if ((ch == 'n') || (ch == '\\') || (ch == 't') || (ch == 'r')) {
                    text += ch;
                    return Symbol::CHAR_CONST;
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::Start_q0;
                }
                break;
        }
    }

}

const char *ExprLexer::tokenToString(Symbol tk)
{
    switch (tk) {
        case Symbol::CHAR_CONST: return "CHAR_CONST";
        case Symbol::STRING_CONST: return "STRING_CONST";
        case Symbol::Number: return "Number";
        case Symbol::OPEN_KEY: return "OPEN_KEY";
        case Symbol::CLOSE_PAREN: return "CLOSE_PAREN";
        case Symbol::CLOSE_KEY: return "CLOSE_KEY";
        case Symbol::SEMICOLON: return "SEMICOLON";
        case Symbol::KW_ROT: return "KW_ROT";
        case Symbol::CLOSE_BRACKET: return "CLOSE_BRACKET";
        case Symbol::KW_IF: return "KW_IF";
        case Symbol::KW_FALSE: return "KW_FALSE";
        case Symbol::KW_FOR: return "KW_FOR";
        case Symbol::KW_EXTENDS: return "KW_EXTENDS";
        case Symbol::OPEN_PAREN: return "OPEN_PAREN";
        case Symbol::KW_ELSE: return "KW_ELSE";
        case Symbol::Eof: return "Eof";
        case Symbol::KW_RETURN: return "KW_RETURN";
        case Symbol::KW_NULL: return "KW_NULL";
        case Symbol::GTE: return "GTE";
        case Symbol::KW_WHILE: return "KW_WHILE";
        case Symbol::COMMA: return "COMMA";
        case Symbol::KW_INT: return "KW_INT";
        case Symbol::GT: return "GT";
        case Symbol::LT: return "LT";
        case Symbol::KW_BOOL: return "KW_BOOL";
        case Symbol::KW_BREAK: return "KW_BREAK";
        case Symbol::KW_CONTINUE: return "KW_CONTINUE";
        case Symbol::MULT: return "MULT";
        case Symbol::KW_NEW: return "KW_NEW";
        case Symbol::POINT: return "POINT";
        case Symbol::OR: return "OR";
        case Symbol::DIV: return "DIV";
        case Symbol::OPEN_BRACKET: return "OPEN_BRACKET";
        case Symbol::KW_CLASS: return "KW_CLASS";
        case Symbol::NEGATION: return "NEGATION";
        case Symbol::KW_TRUE: return "KW_TRUE";
        case Symbol::ID: return "ID";
        case Symbol::SUB: return "SUB";
        case Symbol::SUM: return "SUM";
        case Symbol::MOD: return "MOD";
        case Symbol::SHIFT_RIGHT: return "SHIFT_RIGHT";
        case Symbol::EQUAL: return "EQUAL";
        case Symbol::KW_VOID: return "KW_VOID";
        case Symbol::LTE: return "LTE";
        case Symbol::NOT_EQUAL: return "NOT_EQUAL";
        case Symbol::SHIFT_LEFT: return "SHIFT_LEFT";
        case Symbol::AND: return "AND";
        case Symbol::ASSIGN: return "ASSIGN";
        default: return "Unknown";
    }

}