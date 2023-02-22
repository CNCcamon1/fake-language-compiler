#include <exception>
#include <string>
#include <vector>

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


class Error{
   public:
      Error(const char* messageInput, int lineInput){
         message = messageInput;
         line = lineInput;
      }
      const char* message;
      int line;
};

class ErrorReporter{
    public:
        ErrorReporter(){
            errorStatus = false;
        }
        bool errorStatus;

        void reportError(const char* message, int line){
         Error* error = new Error(message, line);
         errors.push_back(error);
         errorStatus = true;
        };
        void reportWarning(const char* message){
            
        };

        void print_errors(){
         for(int i=0; i<errors.size(); i++){
            std::cout<<errors[i]->message<<" at line "<<errors[i]->line<<std::endl;
         }
        }
   private:
      std::vector<Error*> errors;
      std::vector<const char*> warnings;
};

#endif