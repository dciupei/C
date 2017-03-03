//
//  getWord.h
//  Hashtables
//
//  Created by David Ciupei on 1/28/16.
//  Copyright © 2016 David Ciupei. All rights reserved.
//

#ifndef getWord_h
#define getWord_h

#include <stdio.h>

#define DICT_MAX_WORD_LEN 256/* maximum length of a word (+1) */

/* Reads characters from fd until a single word is assembled */
/* and returns a copy of the word allocated from the heap.   */
/* NULL is returned at EOF.                                  */

/* Words are defined to be separated by whitespace and start */
/* with an alphabetic character.  All alphabetic characters  */
/* translated to lower case and punctuation is removed.      */

char* getNextWord(FILE* fd);


#endif /* getWord_h */
