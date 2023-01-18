#include <exception>

#ifndef COMPILER_EXCEPTIONS
#define COMPILER_EXCEPTIONS

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

#endif