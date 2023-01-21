#include <exception>
#include <string>

#ifndef ERROR_REPORTER_TYPE
#define ERROR_REPORTER_TYPE

struct EndOfFileException : public std::exception {
   const char * what () const throw () {
      return "End of file reached.";
   }
};

struct ErroneousCommentException : public std::exception {
   const char * what () const throw () {
      return "A comment was entered while the buffer was not empty. There probably wasn't a space between the last token and the start of the comment";
   }
};

struct TerminalMismatchException : public std::exception {
   const char * what () const throw () {
      return "Derivation did not match token";
   }
};

struct NoValidDerivationsException : public std::exception {
   const char * what () const throw () {
      return "No more valid derivation options";
   }
};

class ErrorReporter{
    public:
        ErrorReporter(){
            errorStatus = false;
        }
        bool errorStatus;
        void reportError(std::string* message){

        };
        void reportWarning(std::string* message){
            
        };
};

#endif