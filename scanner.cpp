#include "scanner.h"

// putback() puts its argument back into the Token_stream's buffer
void Token_stream::putback(Token t)
{
    if (full) error("putback into a full buffer");
    buffer = t;             // copy t to buffer
    full = true;            // buffer is now full
}

Token Token_stream::get()
{
    if (full) {             // do we already have a Token ready?
        full = false;       // remove token from buffer
        return buffer;
    }
    char ch;
    cin.get(ch);            // cin.get() does NOT skip whitespace
    while (isspace(ch)) {
        if (ch == '\n') return Token(print);
        cin.get(ch);
    }
    switch (ch) {
    case '(': case ')': case '+': case '-': case '*': case '/': case '=': case 'q':
        return Token(ch);   // let each character represent itself
    default:
        if (isdigit(ch)) {
            string s;
            s += ch;
            while (cin.get(ch) && (isdigit(ch) || ch == '.')) s += ch;
            cin.unget();
            if(regex_match(s,std::regex("[0-9]+(\\.[0-9][0-9])?"))){ 
                return Token(number, stod(s));
            }else{
                error("Illegal number");
            }
        }
        if (isalpha(ch) || ch == '_'){
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
            cin.unget();
                if (s == "var") return Token(variable);	    
                if (s == "const") return Token(constant);	    
                if (regex_match(s,(std::regex("[a-zA-Z][a-zA-Z0-9]*"))) || regex_match(s,std::regex("__[a-zA-Z0-9]+__"))){
                    return Token(name, s);
                }else{
                    error("Illegal name");
                }
        }
        error("Bad token");
    }
    error("Illegal character");
}
