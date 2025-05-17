#include "TOLENTINO-WT.h"

// ------------------------------ ADMIN PHASE ------------------------------ // 
        // the functions are not necessarily exclusive to the A.P. //
/*
    displayAdminSelection() simply displays the selection the game master
        can choose from.
*/
void
displayAdminSelection()
{
    printf(" - | - | - | - | - | - | - | - | - | - | -\n");
    printf("[1] Add Word\n");
    printf("[2] Add Trivia\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Word\n");
    printf("[5] Delete Clue\n");
    printf("[6] View Words and Clues\n");
    printf("[7] Export\n");
    printf("[8] Import\n");
    printf("[0] Back to Main Menu\n");
    printf(" - | - | - | - | - | - | - | - | - | - | -\n\n");
}

/* 
    displayWord() displays all the word in the struct array along with its 
        element number.
  
    @param str[]:   struct array where the words are stored
    @param n:   number of non-garbage values in the array

    Pre-condition:  the string must be at least one character in 
                        length and contains at least one letter
*/ 
void 
displayWord(WordDetail str[], int n)
{
    int i;

    printf("|---------------- | WORD LIST | ----------------|\n\n");
    for (i = 0; i < n; i++)
        printf ("[%03d] -- %s\n", i + 1, str[i].Answer);
    printf("\n|---------------- | --------- | ----------------|\n");
}

/* 
    displayContent() displays all the trivia under the word.
  
    @param content[]:   struct array where the words are stored
    @param index:       index of the word to be displayed
    @param trivnum:     the number of trivia under the word

    Pre-condition:      index and trivnum are non-negative integer
                        content[] should not contain garbage value
*/ 
void 
displayContent(WordDetail content[], int index, int trivnum)
{
    int i;

    printf("\n|-------------- | WORD CONTENT | --------------|\n\n");
    
    printf("---- [%03d]\n\n", index + 1);
    printf("OBJECT: %s [%c]\n", content[index].Answer, content[index].firstLetter);
 
    for (i = 0; i < trivnum; i++)
        printf("[%02d] %s: %s\n", i + 1,
                content[index].Trivia[i].Relation, 
                content[index].Trivia[i].RelValue);
    
    printf("\n|-------------- | ------------ | --------------|\n\n");
}

/* 
    displayContent2() displays all the trivia under the word.
    This is just a simple formatting with respect to the specs
        unlike the first one.
  
    @param content[]:   struct array where the words are stored
    @param index:   index of the word to be displayed
    @param trivnum: the number of trivia under the word

    Pre-condition:  index and trivnum are non-negative integer
                        content[] should not contain garbage value
*/ 
void 
displayContent2(WordDetail content[], int index, int trivnum)
{
    int i;

    printf("\n|-------------- | WORD CONTENT | --------------|\n\n");
    
    printf("Object: %s\n", content[index].Answer);
 
    for (i = 0; i < trivnum; i++)
        printf("    %s: %s\n",
                content[index].Trivia[i].Relation, 
                content[index].Trivia[i].RelValue);
    
    printf("\n|-------------- | ------------ | --------------|\n\n");
}

/* 
    SmallestString() gets the "lowest" word in terms of ASCII
        value.
  
    @param str[]:   struct array where the words are stored
                        WORD Answer is specifically accessed
    @param n:   the number of non-garbage elements

    Pre-condition:  n is non-negative integer
                    no duplicates of a word in the array exists
*/ 
int 
SmallestString (WordDetail str[], int n)
{
    int i;
    int small = 0;

    for (i = 0; i < n; i++)
    {
        if (strcmp(str[i].Answer, str[small].Answer) > 0) 
            small = i;
    }
    
    return small;
}

/*
    arrangeAlphabetical() arranges the word list (struct array of words)
        alphabetically using the variable Answer under the struct
        WordContentTag. 
    Calls the function SmallestString().

    @param content[]:   array of struct that contains the details 
                            of the word
    @param n:   number of elements

    Pre-condition:  n is non-negative integer
                    content[] should not be garbage value
*/
void 
arrangeAlphabetical(WordDetail content[], int n)
{
    int i, small;
    WordDetail temp;

    for (i = 0; i < n; i++)
    {
        //modifications in the parameter since the starting point changes
        small = SmallestString(content + i, n - i) + i; 

        temp = content[i];
        content[i] = content[small];
        content[small] = temp;
    }
}

/*
    checkLength() checks if the user input is at least
        1 character in length and does not exceed 
        character limit.

    @param str[]:   character array to be checked
    @param n:   character limit

    Pre-condition:  n should be non-negative integer
                    usually LEN30 and LEN20
*/
int
checkLength(char str[], int n)
{
    int len = strlen(str),
        res = 0;

    if (len >= 1 && len < n)
        res = 1;

    return res;
}

/*
    checkWordValid() checks if the user input contains 
        at least 1 letter (OR 0) and also calls checkLength().

    @param str[]:   character array to be checked
    @param n:   character limit

    @return res:    1 if valid
                    0 if not

    Pre-condition:  str[] is any string
                    n is non-negative integer, usually LEN30 and LEN20
    
    note: if user wants to input a number, using the actual word or 
        adding n at the end of the number can be done
        example: "one hundred" or "100n"
*/
int
checkWordValid(char str[], int n)
{
    int resChar = 0,
        resLength,
        i,
        res = 0,
        len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') || 
            (str[i] >= 'a' && str[i] <= 'z') || 
            str[i] == '0')
            resChar = 1;
    }

    resLength = checkLength(str, n);

    if (resLength == 1 && resChar == 1)
        res = 1;

    return res;   
}

/*
    getInput() allows user string input with spaces.

    @param str[]:   character array where input should be stored
    @param n:       number of maximum characters to input

    Pre-condition:  n > 0, usually 100 (maximum input)
*/
void
getInput(char str[], int n)
{
    int ctr = 0;
    char input;

    do {
        scanf("%c", &input);
        if (input != '\n')
        {
            str[ctr] = input;
            ctr++;
        }
    } while (input != '\n' && ctr < n);

    str[ctr] = '\0';

    fflush(stdin); //clearing input buffer
}

/* 
    findWord() checks a word if it exists in an array.
        Similar to LinearSearch() algorithim discussed.
  
    @param str[]:   struct array; also the
                        list of words
    @param key:     a string that the function is looking for
    @param n:       number of non-garbage values in the array

    @return -1:     if key is not found
    @return  i:     index of where the key is found in the string array

    Pre-condition:  words should already be validated by checkValidWord()
                    words should be sorted alphabetically
                    n is a non-negative integer
*/
int 
findWord(WordDetail str[], WORD key, int n)
{
    int i = 0;
    int found = 0;

    while (found == 0 && i < n) 
    {
        if (!strcmp(str[i].Answer, key))
            found = 1;
        else
            i++;
    }

    if (!found)
        return -1;
    else
        return i;
}

/* 
    findTrivia() checks if the pair of relation and relation value
        exists in an array.
    Similar to LinearSearch() algorithim discussed.
  
    @param rel[]:   struct array; also the
                        list of trivia of a word
    @param relin, 
        relvalin:   a string that the function is looking for
    @param n:       number of non-garbage values in the array

    @return -1:     if key is not found
    @return  i:     index of where the key is found in the string array

    Pre-condition:  should already be validated by checkValidWord()
                    n is a non-negative integer
*/
int
findTrivia(TriviaDetail rel[], char relin[], char relvalin[], int n)
{
    int i = 0;
    int found = 0;

    while (found == 0 && i < n)
    {
        if (!strcmp(rel[i].Relation, relin))
            if (!strcmp(rel[i].RelValue, relvalin))
                found = 1;
            else i++;
        else 
            i++;
    }

    if (!found)
        return -1;
    else
        return i;
}

/*
    AddWord() gets input for words in admin phase.
    Calls checkValidWord() to validate input.
    Calls findWord() to check if a word exists already.

    @param input:       string user input
    @param ans[]:       struct array where the input must be stored
    @param *numElem:    pointer that updates the number of words added

    @return valid:      1 if word added succesfuly
                        0 if terminated or duplicate is found      

    Pre-condition:      input can accept up to 100 characters,
                            but is for validation
                        the lowest *numElem value is 0 and it
                            should be the number of non-garbage values
*/
int
AddWord(SCAN input, WordDetail ans[], int *numElem)
{
    int valid = 1;

    do {
        printf("Enter Word/Phrase: "); 
        getInput(input, LEN100);

        if (!checkWordValid(input, LEN20))
            printf(">> Please enter valid word and length.\n\n");
    } while (!checkWordValid(input, LEN20));

    if (findWord(ans, input, *numElem) == -1 
        && strcmp(input, "0"))
    {
        strcpy(ans[*numElem].Answer, input);
        ans[*numElem].firstLetter = ans[*numElem].Answer[0];
        printf(">> %s [%c] succesfully added!\n\n", ans[*numElem].Answer, 
                                                    ans[*numElem].firstLetter);
        *numElem += 1;
    }
    else if (findWord(ans, input, *numElem) != -1)
    {
        printf(">> %s already exist. Please enter unique word.\n\n", input);
        valid = 0;
    }
    else if (!strcmp(input, "0"))
    {
        printf(">> [WORD] Exiting...\n\n");
        valid = 0;
    }

    return valid;
}

/*
    AddTrivia() gets input for relatiion and relation value in admin phase.
    Calls checkWordValid() to validate input.
    Calls findTrivia() to check if a trivia exists already.

    @param relinput:    string user input of relation
    @param relvalinput: string user input of relation value
    @param rel[]:       struct array where the input must be stored
    @param *trivctr:    a pointer that updates the number of trivia added

    @return valid:      1 if word added succesfuly
                        0 if terminated or duplicate is found 

    Pre-condition:      the lowest *trivctr can be is 0 and
                            it should be the number of non-garbage
                            values
                        inputs can be up to 100 characters, 
                            but is for validation

    note: the only time user can input 0 is during relation input
*/
int
AddTrivia(SCAN relinput, SCAN relvalinput, 
         TriviaDetail rel[], int *trivctr)
{
    int valid, endRelInput;
    int success = 0;

    endRelInput = 0;
    do {
        printf("Enter Relation: ");
        getInput(relinput, LEN100);

        if (!checkWordValid(relinput, LEN30))
            printf(">> Please enter valid word and length.\n\n");
        else if (!(*trivctr) && !strcmp(relinput, "0"))
            printf(">> Please enter at least 1 trivia.\n\n");
        else
            endRelInput = 1;
    } while (!endRelInput);

    strcpy(rel[*trivctr].Relation, relinput);

    if (strcmp(relinput, "0") != 0)
    {
        do {
            printf("Enter %s: ", relinput);
            getInput(relvalinput, LEN30);

            if (!checkWordValid(relvalinput, LEN30) ||
                !strcmp(relvalinput, "0"))
                printf(">> Please enter valid word and length.\n\n");
        } while (!checkWordValid(relvalinput, LEN30) ||
                !strcmp(relvalinput, "0"));

        valid = findTrivia(rel, relinput, relvalinput, *trivctr);

        if (valid != -1)
            printf(">> %s as %s already exists.\n\n", relvalinput, relinput);
        else
        {
            strcpy(rel[*trivctr].RelValue, relvalinput);
            printf(">> %s succesfully added as %s!\n\n", relvalinput, relinput);
            *trivctr += 1;
            success = 1;
        }
    }
    else
        printf(">> [TRIVIA] Exiting...\n\n");

    return success;
}

/*
    modifyWord() allows modification in an existing word.
    Calls checkWordValid() to validate input.
    Calls findWord() to check if a word exists already.

    @param input:       string user input of the word
    @param content[]:   struct array where the input must be stored
    @param index:       index of the content to be modified
    @param numElem:     number of non-grabage values

    @return valid:      1 if word added succesfuly
                        0 if terminated or duplicate is found 

    Pre-condition:      index and numElem should be non-negative integers
                        inputs can be up to 100 characters but is for
                            validation
    
    note: input loop will only end if the input is "0" or a valid one
*/
int
modifyWord(SCAN input, WordDetail content[], int index, int numElem)
{
    int flag = 0;
    int success = 0;

    do {
        do {
            printf("Enter Modified Word: "); 
            getInput(input, LEN100);

            if (!checkWordValid(input, LEN20))
                printf(">> Please enter valid word and length.\n\n");
        } while (!checkWordValid(input, LEN20));

        if (strcmp(input, "0") == 0)
        {
            printf(">> Cancelling...\n");
            printf("\n============ >> EXIT: MODIFY WORD\n\n");
            flag = 1;
        }
        else if (findWord(content, input, numElem) == -1)
        {
            strcpy(content[index].Answer, input);
            content[index].firstLetter = content[index].Answer[0];
            printf(">> %s [%c] succesfully changed!\n", content[index].Answer, 
                                                        content[index].firstLetter);
            flag = 1;
            success = 1;
        }
        else if (findWord(content, input, numElem) != -1)
            printf(">> %s already exist. Please enter unique word.\n\n", input);
    } while (!flag);

    return success;
}

/*
    modifyRelation() allows modification in an existing relation part in clues.
    Calls checkWordValid() to validate input.
    Calls findTrivia() to check if a trivia exists already.

    @param relinput:    string user input of the relation
    @param rel[]:       struct array where the input must be stored
    @param trivIndex:   index of the trivia to be modified
    @param numTriv:     number of non-grabage values
    @param mode:        1 - stand alone modify relation
                        2 - called in modifyTrivia()

    @return valid:      1 if word added succesfuly
                        2 if terminated

    Pre-condition:      index and numElem should be non-negative integers
                        inputs can be up to 100 characters
                            but is for validation
*/
int
modifyRelation(SCAN relinput, TriviaDetail rel[], int trivIndex, 
                int numTriv, int mode)
{
    int valid = 0;
    int success = 0;

    do 
    {
        do 
        {
            printf("Enter Relation: ");
            getInput(relinput, LEN100);

            if (!checkWordValid(relinput, LEN30))
                printf(">> Please enter valid word and length.\n\n");
        } while (!checkWordValid(relinput, LEN30));

        if (strcmp(relinput, "0") != 0) 
        {
            if (mode == 1)
                valid = findTrivia(rel, relinput, rel[trivIndex].RelValue, numTriv);
            else
                valid = -1;
            
            if (valid == -1)
            {
                if (mode == 1)
                    printf(">> %s succesfully changed to %s!\n\n", rel[trivIndex].Relation, relinput);

                strcpy(rel[trivIndex].Relation, relinput);
                success = 1;
            }
            else
                printf(">> %s as %s already exists.\n\n", rel[trivIndex].RelValue, relinput);
        }
        else
        {
            printf(">> Exiting...\n\n");
            success = 2;
        }
    } while (!success);

    return success;
}

/*
    modifyRelValue() allows modification in an existing relation value part in clues
    Calls checkWordValid() to validate input
    Calls findTrivia() to check if a trivia exists already

    @param relvalinput: string user input of the relation value
    @param rel[]:       struct array where the input must be stored
    @param trivIndex:   index of the trivia to be modified
    @param numTriv:     number of non-grabage values
    @param mode:        1 - stand alone modify relation value
                        2 - called in modifyTrivia()

    @return valid:      1 if word added succesfuly
                        2 if terminated

    Pre-condition:      index and numElem should be non-negative integers
                        inputs can be up to 100 characters
                            but is for validation
*/
int 
modifyRelValue(SCAN relvalinput, TriviaDetail rel[], int trivIndex, int numTriv, int mode)
{
    int valid = 0,
        success = 0;

    do {
        do {
            printf("Enter %s: ", rel[trivIndex].Relation);
            getInput(relvalinput, LEN30);

            if (!checkWordValid(relvalinput, LEN30))
                printf(">> Please enter valid word and length.\n\n");
        } while (!checkWordValid(relvalinput, LEN30));

        if (mode == 1)
            valid = findTrivia(rel, rel[trivIndex].Relation, relvalinput, numTriv);
        else
            valid = -1;

        if (valid != -1)
            printf(">> %s as %s already exists.\n\n", relvalinput, rel[trivIndex].Relation);
        else if (strcmp(relvalinput, "0") == 0)
        {
            printf(">> Exiting...\n\n");
            success = 2;
        }
        else
        {
            strcpy(rel[trivIndex].RelValue, relvalinput);

            if (mode == 1)
                printf(">> %s succesfully added as %s!\n\n", relvalinput, rel[trivIndex].Relation);

            success = 1;
        }
    } while (!success);

    return success;
}

/*
    modifyTrivia() allows modification in both relation and relation value.
    Calls modifyRelation() and modifyRelValue().

    @param relinput:    string user input of the relation
    @param relvalinput: string user input of the relation value
    @param rel[]:       struct array where the input must be stored
    @param trivIndex:   index of the trivia to be modified
    @param numTriv:     number of non-grabage values

    Pre-condition:      index and numElem should be non-negative integers
                        inputs can be up to 100 characters 
                            but is for validation
*/
int
modifyTrivia(SCAN relinput, SCAN relvalinput, 
            TriviaDetail rel[], int trivIndex, int numTriv)
{
    int relSuccess = 0, 
        relvalSuccess = 0,
        valid = 0,
        success;
    int i;
    TriviaDetail tempContainer[MAX10];

    success = 0;
    for (i = 0; i < numTriv; i++)
        tempContainer[i] = rel[i];

    relSuccess = modifyRelation(relinput, tempContainer, trivIndex, numTriv, 2);

    if (relSuccess == 1)
    {
        relvalSuccess = modifyRelValue(relvalinput, tempContainer, trivIndex, numTriv, 2);
        valid = findTrivia(rel, relinput, relvalinput, numTriv);
    }

    if (valid == -1 && relvalSuccess != 2)
    {
        printf(">> %s as %s successfully added!\n\n", relvalinput, relinput);

        for (i = 0; i < numTriv; i++)
            rel[i] = tempContainer[i];

        success = 1;
    }
    
    if (relvalSuccess == 2 || valid > -1)
    {
        if (valid > -1)
            printf("\n>> Duplicate found.");

        printf("\n>> No changes made.\n\n");
        printf("====================\n");
    }

    return success;
}

/*
    deleteWord() deletes an existing word. 

    @param content[]:   struct array where words are stored
    @param del:         index of the word to be deleted
    @param *elem:       a pointer to the number of elements

    Pre-condition:      *elem should be the number of non-garbage elements
                        del is non-negative integer
                            maximum del is *elem - 1
                            minimum is 0
                        content[] should already be in alphabetical order based on
                            WORD Answer under WordDetail unless used in removeDuplicate()
*/
void
deleteWord(WordDetail content[], int del, int *elem)
{
    int i;

    for (i = del + 1; i < *elem; i++)
        content[i - 1] = content[i];

    *elem -= 1;
}

/*
    deleteTrivia() deletes an existing trivia. 

    @param trivia[]:    struct array where trivia are stored
    @param del:         index of the trivia to be deleted
    @param *elem:       a pointer to the number of elements

    Pre-condition:      *elem should be the number of non-garbage elements
                        del is non-negative integer
                            maximum del is *elem - 1
                            minimum is 0
*/
void 
deleteTrivia(TriviaDetail trivia[], int del, int *elem)
{
    int i;

    for (i = del + 1; i < *elem; i++)
        trivia[i - 1] = trivia[i];
        
    *elem -= 1;
}

/*
    exportContents() exports the existing contents of the 
        program in the desired output.

        Object: Table
        Kind of: Furniture
        Color: Commonly Brown

    @param *export:    file pointer to the destination file
    @param content[]:  struct array of words and its details
    @param elem:       number of elements/words

    Pre-condition:      elem should be the number of non-garbage elements
                        *export can be null or existing
                        content[] should already be in alphabetical order based on
                            WORD Answer under WordDetail
*/
void
exportContent(FILE *export, WordDetail content[], int elem)
{
    int wordInd, trivInd;

    for (wordInd = 0; wordInd < elem; wordInd++)
    {
        fprintf(export, "Object: %s\n", content[wordInd].Answer);

        for (trivInd = 0; trivInd < content[wordInd].RelCtr; trivInd++)
        {
            fprintf(export, "%s: %s\n", content[wordInd].Trivia[trivInd].Relation,
                                        content[wordInd].Trivia[trivInd].RelValue);
        } 

        if (wordInd + 1 != elem)
            fprintf(export, "\n");
    }

    fprintf(export, "\n");
}

/*
    findColon() finds the colon in a string
    Used in importing
    Also stores the relation in TRIVIA dest

    @param str:     string for the imported text
    @param dest:    destination where the relation is stored

    @returns i:     index of the start of relation value
                    example -- Part: Inch 
                        returns 6 since "Inch" starts 
                        at index 6

                    at the same time, "Part" is being stored
                        in TRIVIA dest

    Pre-condition:  str can be up to 100 characters 
                    str contains ":"   
                    there are characters next to ":"
*/  
int
findColon(SCAN str, TRIVIA dest)
{
    int i = 0;
    int found = 0;
    int len = strlen(str);

    while (i < len && !found)
    {
        if (str[i] == ':')
            found = 1;
        else
        {
            dest[i] = str[i];
            i++;
        }  
    }

    dest[i] = '\0';
    i += 2;

    return i;
}

/*
    findDuplicate() finds the first 2 pairs of duplicates in an array
    Used in importing

    @param content:     struct array where words are stored
    @param elem:        number of non-garbage elements
    @param *dupe1:      where the first duplicate is stored
    @parazm *dupe2:     where the second duplicate is stored

    Pre-condition:      content[] can be in any order; usually original 
                            comes first then the imported words
*/
void
findDuplicate(WordDetail content[], int elem, int *dupe1, int *dupe2)
{
    int i = 0, j;
    int found = 0;

    while (i < elem && found == 0)
    {
        for (j = i + 1; j < elem && !found; j++)
            if (strcmp(content[i].Answer, content[j].Answer) == 0)
                found = 1;

        if (!found)
            i++;
    }

    if (found)
    {
        *dupe1 = i;
        *dupe2 = j - 1;
    }
    else
    {
        *dupe1 = -1;
        *dupe2 = -1;
    }
}

/*
    removeDuplicate() prints 1 pairs of duplicate and asks the user
        which to remove
    Used in importing

    @param content:     struct array where words are stored
    @param *elem:       where the number of non-garbage elements
                            is stored

    Pre-condition:      content[] can be in any order; usually original 
                            comes first then the imported words
                        will only run if findDuplicate() returns value > -1
*/
void
removeDuplicate(WordDetail content[], int *elem)
{
    int dupInd1, dupInd2, dupSelect;
    int flag;

    flag = 0;
    do {
        findDuplicate(content, *elem, &dupInd1, &dupInd2);

        if (dupInd1 != -1 && dupInd2 != -1)
        {
            flag = 1;
            printf("_________________________________________________\n");
            printf("_________________________________________________\n\n");

            printf("               [ORIGINAL ENTRY (1)]\n");
            displayContent(content, dupInd1, content[dupInd1].RelCtr);
            printf("\n                 [NEW ENTRY (2)]\n");
            displayContent(content, dupInd2, content[dupInd2].RelCtr);

            printf(">> Duplicate found.\n\n");

            do {
                printf("Keep Entry #: ");
                scanf("%d", &dupSelect);

                if (dupSelect != 1 && dupSelect != 2)
                    printf(">> Invalid input.\n\n");
            } while (dupSelect != 1 && dupSelect != 2);
            
            if (dupSelect == 1)
                deleteWord(content, dupInd2, elem);
            else
                deleteWord(content, dupInd1, elem);
        }
    } while (dupInd1 != -1 && dupInd2 != -1);

    if (flag)
    {
        printf("_________________________________________________\n");
        printf("_________________________________________________\n\n\n");
    }
}

/*
    importContent() imports data from a .txt file
    The .txt file must follow the format:

        Object: Table
        Kind of: Furniture
        Color: Commonly Brown

        Object: Apple
        Category: Fruit

    @param *import:     file pointer to the file
    @param content[]:   temporary struct array of words and its details
    @param orig[]:      original struct array of words and its details
    @param *elem:       number of elements/words

    Pre-condition:      elem should be the number of non-garbage elements
                            it can start from 0 to any positive integer
                        *import should be existing
                        assumed that the string values follow the maximum length
                            20 characters for WORD Answer
                            30 characters for TRIVIA Relation and TRIVIA RelValue

    note: this function can accept up to 500 entries in a text file; however, it is to be
        checked for duplicates AND anything exceeds the 150 maximum count is disregarded
*/
void
importContent(FILE *import, WordDetail content[], WordDetail orig[], int *elem)
{
    int i, wordInd, trivInd, trivStart, 
        len, valid;
    WORD worTemp;
    TRIVIA relvalTemp, relTemp;
    SCAN scanTemp;

    // copy all the current words to the temporary container //
    for (i = 0; i < *elem; i++)
        content[i] = orig[i];

    wordInd = *elem;

    fgets(scanTemp, LEN100, import);
    while (!feof(import)) 
    {
        if (*elem < MAX500)
        {
            if (strncmp(scanTemp, "Object: ", 8) == 0)
            {
                strcpy(worTemp, &scanTemp[8]);
                len = strlen(worTemp);
                worTemp[len - 1] = '\0';

                strcpy(content[wordInd].Answer, worTemp);
                content[wordInd].firstLetter = content[wordInd].Answer[0];
                content[wordInd].RelCtr = 0;
                *elem += 1;
                
                wordInd += 1;
                trivInd = 0; 
            }
            else if (strcmp(scanTemp, "\n") != 0 && content[wordInd - 1].RelCtr < 10)
            {                             //any trivia that exceeds 10 is disregarded
                trivStart = findColon(scanTemp, relTemp);

                strcpy(relvalTemp, &scanTemp[trivStart]);
                len = strlen(relvalTemp);
                relvalTemp[len - 1] = '\0';

                valid = findTrivia(content[wordInd - 1].Trivia, relTemp, 
                                relvalTemp, content[wordInd - 1].RelCtr);

                if (valid == -1)
                {
                    strcpy(content[wordInd - 1].Trivia[trivInd].Relation, relTemp);
                    strcpy(content[wordInd - 1].Trivia[trivInd].RelValue, relvalTemp);
                    content[wordInd - 1].RelCtr += 1;

                    trivInd += 1;
                }
            }
        }

        fgets(scanTemp, LEN100, import);
    }

    // -------- cleaning up ---------- //
    removeDuplicate(content, elem); //removing duplicates
    //disregard any word that exceeds the maxmium count
    if (*elem > MAX)
    {
        for (i = *elem; i >= MAX; i--)
            deleteWord(content, i, elem);

        *elem = MAX;
    }
    arrangeAlphabetical(content, *elem);
    //copy all that values in content[] to orig[]
    for (i = 0; i < MAX; i++)
        orig[i] = content[i];
    // -------- cleaning up ---------- //
}

/*
    catTxt() concatenates the string ".txt" when it is missing
    Used in importing/exporting

    @param str[]:   string to be concatenated
*/
void
catTxt(char str[])
{
    int len = strlen(str);

    if (strcmp(&str[len - 4], ".txt") != 0 && strcmp(&str[len - 4], ".TXT") != 0)
        strcat(str, ".txt");
}
// ------------------------------ ADMIN PHASE ------------------------------ //

// ------------------------------- SHUFFLER ------------------------------- //
       // the functions are not necessarily exclusive to the SHUFFLER //  
/*
    initializeIndex() initializes an array of indices 
        with the number of elements as well as 
        prepares it for flagging

    @param index[][MAX]:    1st row = indices (0 to elem - 1)
                            2nd row = flagging (0 or 1)
    @param elem:    number of non-garbage elements

    Pre-condition:  elem is non-negative integer
                    index[][MAX] can accept up to 150 numbers
*/
void
initializeIndex(int index[][MAX], int elem)
{
    int row, col;
    int ctr;

    ctr = 0;
    for (row = 0; row < 2; row++)
    {
        for (col = 0; col < elem; col++)
        {
            if (row == 0)
            {
                index[row][col] = ctr;
                ctr++;
            }
            else
            {
                index[row][col] = 0;
            }
        }
    }
}

/*
    shuffleIndex() uses Fisher-Yates algorithm to shuffle 
        the indices initiliazed by initializeIndex()

    @param index[]: array of indices
    @param elem:    number of non-garbage elements

    Pre-condition:  elem is non-negative integer
                    index[] and elem can accept up to 150 numbers
*/
void
shuffleIndex(int index[], int elem)
{
    int i;
    int temp;
    int ind;

    srand(time(NULL));
    for (i = elem - 1; i >= 0; i--)
    {
        ind = rand () % (i + 1);
        
        temp = index[i];
        index[i] = index[ind];
        index[ind] = temp;
    } 
}

/*
    shuffleWords() assign the words from orig[#].Answer
        to the shuffle array on the shuffled index

    @param orig[]:  struct array of words
    @param shuffle[]:   array where the shuffled words are stored
    @param index[][MAX]:    2D array of indices, specifically 
                                accessed the 1st row
    @param elem:    number of non-garbage elements

    Pre-condition:  elem is non-negative integer
                    accessing orig[] should be until the 
                        non-garbage value only
*/
void
shuffleWords(WordDetail orig[], WORD shuffle[], int index[][MAX], int elem)
{
    int i;

    for (i = 0; i < elem; i++)
        strcpy(shuffle[index[0][i]], orig[i].Answer);
}

/*
    countEntries() counts the words that start with the letter;
        this is used for preparing the formula for shuffling

    for example: {Apple, Admire, Balloon, Pan}
            letters[0].letter = A
            letters[0].count = 2
            *nLetters = 3 --> (A, B, P)

    @param orig[]:  struct array of words
    @param letters[]:   struct array where the details of the 
                            letter is stored
    @param elem:    number of non-garbage elements
    @param *nLetters:   a pointer that updates the count existing letters

    Pre-condition:  elem is non-negative integer
                    lowest *nLetters value is 0 (= no words exists in orig[])
*/
void
countEntries(WordDetail orig[], letterDetail letters[], int elem, int *nLetters)
{
    char letter = 'A';
    int j, k, ctr;

    k = 0;
    for (letter = 'A'; letter <= 'z'; letter++)
    {
        ctr = 0;
        for (j = 0; j < elem; j++)
        {
            if (letter == orig[j].Answer[0])
                ctr++;
        }

        if (ctr > 0)
        {
            letters[k].letter = letter;
            letters[k].count = ctr;
            (*nLetters) += 1;

            k++;
        }

        if (letter == 'Z')
            letter = 'a' - 1;
    }
}

/*
    validEntryCount() checks if the entry count is valid for the table
        considering the restrictions where no similar letters in every row

    @param letters[]:   struct array where the details of the 
                            letter is stored
    @param nletter: number of non-garbage elements
    @param nrows:   number of rows
    @param nsize:   table size (row * column)

    @return 1:  if valid, meaning entries are sufficient for the size
    @return 0:  if insufficient

    Pre-condition:  nletter, nrows, and nsize are non-negative integer          
*/
int
validEntryCount(letterDetail letters[], int nletter, 
            int nrows, int ncols, int nsize, int nelem)
{
    int checkpoint1 = 0, checkpoint2 = 1;
    int i, max;
    int diff, sum;

    // checkpoint 1 = size compatibility check //
    if (nrows == nelem)
        checkpoint1 = 1;

    if (nletter >= nrows)
        checkpoint1 = 1;

    if (ncols >= nrows)
        checkpoint1 = 1;
    // checkpoint 1 = size compatibility check //

    // find maximum letter count //
    max = 0;
    for (i = 1; i < nletter; i++)
    {
        if (letters[i].count > letters[max].count)
            max = i;
    }
    // find maximum letter count //

    // checkpoint 2 = letter count check //
    diff = letters[max].count - nrows; //
    sum = nletter + diff; 
    
    if (letters[max].count > nrows && sum < nsize && ncols > nrows)
        if (nletter < ncols)
            checkpoint2 = 0;
    // checkpoint 2 = letter count check //

    if (nletter < ncols)
        checkpoint2 = 0;

    if (checkpoint1 && checkpoint2)
        return 1;
    else
        return 0;
}

/*
    word2D() transfers the 1D array of words from shuffle[] to 
        the table[row][col]

    @param shuffle[]:   array of the shuffled words
    @param table[][MAXTABLE]:   2D array of strings; also the table
    @param rowsize:     number of rows
    @param colsize:     number of columns

    Pre-condition:  rowsize and colsize are non-negative
                    the entry count must already be validated by
                        validEntryCount()
                    the elements in shuffle and table should
                        correspond with table size          
*/
void
word2D(WORD shuffle[], WORD table[][MAXTABLE],
    int rowsize, int colsize)
{
    int row, col;
    int wordCtr;

    wordCtr = 0;
    for (row = 0; row < rowsize; row++)
    {
        for (col = 0; col < colsize; col++)
        {
            strcpy(table[row][col], shuffle[wordCtr]);
            wordCtr++;
        }
    }
}

/*
    findLetter() is used to find the first word that starts with the 
        letter

    @param shuffle[]:   string array that consists of the shuffled words
    @param letter:  char that is to find
    @param n:   number of non-garbage elements in shuffle[]

    @return -1: not found
    @return i: index of the word

    Pre-condition:  n is non-negative integer
                    letter already exists in the array
                        meaning, if the shuffle[] array does not have a word
                        that starts with Z, then @param letter can not be 'Z'
*/
int 
findLetter(WORD shuffle[], char letter, int n)
{
    int i;
    int found = 0;

    for (i = 0; i < n && !found; i++)
    {
        if (shuffle[i][0] == letter)
            found = 1;
    }

    if (found)
        return i -= 1;
    else
        return -1;
}

/*
    validTable() checks if the table is valid; meaning
        no repitition of letters in the row

    @param table[][MAXTABLE]:   2D array of strings; also the table
    @param letters[]:   struct array of existing letters in the enry
                            specifically accessing .letters
    @param rowsize:     number of rows
    @param colsize:     number of columns
    @param nletters:    number of non garbage elements in letters[]

    @return success:    1 if no repitition
                        0 if there is

    Pre-condition:  rowsize and colsize are non-negative
                    the entry count must already be validated by
                        validEntryCount()
                    the elements in shuffle and table should
                        correspond with table size          
*/
int
validTable(WORD table[][MAXTABLE], letterDetail letters[],
            int rowsize, int colsize, int nletters)
{
    int row, col, lettInd;
    int flag, success, stop;

    success = 1;
    stop = 0;
    for (row = 0; row < rowsize; row++)
    {
        for (lettInd = 0; lettInd < nletters && !stop; lettInd++)
        {
            flag = 0;
            for (col = 0; col < colsize && !stop; col++)
            {
                if (table[row][col][0] == letters[lettInd].letter)
                    flag++;
                if (table[row][col][0] == '\0')
                    stop = 1;
            }

            if (flag > 1 || stop)
                success = 0;
        }
    }
    return success;
}

/*
    shuffler1() shuffles all the words, put it into 2D array, and
        checks if the table is valid (no repitition of letters 
        per row)
    This also calls all the functions under "SHUFFLER"
    Used for small-scale shuffling
    Lets the computer generate combinations that satisfies the 
        restrictions

    @param original[]:   2D array of strings; also the table
    @param shuffled[]:   struct array of existing letters in the enry
                            specifically accessing .letters
    @param table[][MAXTABLE]:     2D array of strings
    @param nrows:    number of rows
    @param ncols:    number of columns
    @param nsize:    table size -- row * col
    @param nelem:    number of non garbage elements in original[]

    @return success:    1 if shuffling is success
                        0 if not

    Pre-condition:  rowsize and colsize are non-negative
                    the entry count must already be validated by
                        validEntryCount()
                    the elements in shuffle and table should
                        correspond with table size          
*/
int
shuffler1(WordDetail original[], WORD shuffled[], WORD table[][MAXTABLE], letterDetail fletter[], 
        int nrows, int ncols, int nsize, int nelem, int nletters)
{
    int shuffleFlag, success2D, successShuffle;
    int randIndex[2][MAX];
    time_t currTime, loopTime;

    shuffleFlag = 1;
    successShuffle = 0;

    initializeIndex(randIndex, nelem);
    currTime = time(NULL);

    do {
        shuffleIndex(randIndex[0], nelem);
        shuffleWords(original, shuffled, randIndex, nelem);

        word2D(shuffled, table, nrows, ncols);
        success2D = validTable(table, fletter, nrows, ncols, nletters);

        if (success2D)
            shuffleFlag = 0;

        loopTime = time(NULL);

        if (loopTime - currTime > 15)
            shuffleFlag = 0;
    } while (shuffleFlag);

    if (success2D)
        successShuffle = 1;
    
    return successShuffle;
}

/*
    shuffler2() shuffles all the words first, then chooses random letter
        from the firstLetter[] array, then finds a word that starts with
        that letter
    This also calls all the functions under "SHUFFLER"
    Used for large-scale shuffling
    
    Generate random index for the struct array of firstLetters, then
        finds a word that starts with that letter; this resets every
        row

    @param original[]:   2D array of strings; also the table
    @param shuffled[]:   struct array of existing letters in the enry
                            specifically accessing .letters
    @param table[][MAXTABLE]:   2D array of strings
    @param nrows:    number of rows
    @param ncols:    number of columns
    @param nsize:    table size -- row * col
    @param nelem:    number of non garbage elements in original[]

    @return success:    1 if shuffling is success
                        0 if not

    Pre-condition:  rowsize and colsize are non-negative
                    the entry count must already be validated by
                        validEntryCount()
                    the elements in shuffle and table should
                        correspond with table size 
*/
int
shuffler2(WordDetail original[], WORD shuffled[], WORD table[][MAXTABLE], letterDetail fletter[],
        int nrows, int ncols, int nsize, int nelem, int nletters)
{
    int successShuffle, success2D;
    int i, row, col, wordInd, lettInd;
    int randIndex[2][MAX], endFlag;
    int lett[2][26];

    WORD bin[MAX];
    time_t currTime, loopTime;

    successShuffle = 0;
    row = 0;

    for (i = 0; i < nletters; i++)
    {
        lett[0][i] = fletter[i].letter;
        lett[1][i] = 0;
    }

    initializeIndex(randIndex, nelem);
    do {
        shuffleIndex(randIndex[0], nelem);
        shuffleWords(original, shuffled, randIndex, nelem);

        for (i = 0; i < nelem; i++)
            strcpy(bin[i], shuffled[i]);

        endFlag = 0;
        for (row = 0; row < nrows; row++)
        {
            currTime = time(NULL);
            for (col = 0; col < ncols; col++)
            {
                do {
                    do {
                        lettInd = rand () % nletters;
                    } while (lett[1][lettInd] == 1);

                    wordInd = findLetter(bin, lett[0][lettInd], nelem);
                    loopTime = time(NULL);

                    if (loopTime - currTime > 12)
                        endFlag = 1;
                } while (wordInd == -1 && !endFlag);

                if (!endFlag)
                {
                    strcpy(table[row][col], bin[wordInd]);
                    lett[1][lettInd] = 1;

                    for (i = wordInd; i < nelem; i++)
                        strcpy(bin[i], bin[i + 1]);
                    nelem -= 1;
                }
                else
                {
                    col = ncols;
                    row = nrows;
                }
            }
            for (i = 0; i < nletters; i++)
                lett[1][i] = 0;
        }
        for (i = 0; i < nletters; i++)
                lett[1][i] = 0;
        
        success2D = validTable(table, fletter, nrows, ncols, nletters);
    } while (!endFlag && !success2D);

    if (row == nrows)
        successShuffle = 1;

    return successShuffle;
}
// ------------------------------- SHUFFLER ------------------------------- //

// ------------------------------ GAME PHASE ------------------------------ //
/*
    getCurrPlayer() returns the number of currnt player (1 or 2)

    @param currPlayer:  integer that sets who the curent player is
                            even number: player 2
                            odd number: player 1

    @return 1:  the current player is 1
    @return 2:  the current player is 2

    Pre-condition: currplayer is >= 0
*/
int
getCurrPlayer(int currPlayer)
{
    int curr; 

    if (currPlayer % 2 == 1)
        curr = 1;
    if (currPlayer % 2 == 0)
        curr = 2;

    return curr;
}

/*
    filterWords() removes the words without trivia

    @param content[]:   struct array of the words
    @param *nelem:  pointer to the number of elements

    Pre-condition:  content[] should be filled and alphabetically arranged
*/
void
filterWords(WordDetail content[], int *nelem)
{
    int i;

    for (i = 0; i < *nelem; i++)
    {
        if (!(content[i].RelCtr >= 1))
        {
            deleteWord(content, i, nelem);
            i -= 1;
        }
    }
}

/*
    printTable() prints the table for game phase

    @param letter:  2D array of a single letter
    @param numrow:  number of rows
    @param numcol:  number of columns

    Pre-condition:  numrow and numcol should be greater
                        than 0
                    currow is non-negative integer
                    letter should have the desired non-garbage
                        elements based on numrow and numcol
*/
void
printTable(char letter[][MAXTABLE], int numrow, int numcol, int currow)
{
    int irow, icol;
    int tabrow = numrow * 5, tabcol = numcol * 7;
    int rowletter, colletter;

    rowletter = 0;
    for (irow = 1; irow <= tabrow; irow++)
    {
        if (irow % 5 == 3)
        {
            if (currow == rowletter)
                printf("     >> ");
            else 
                printf("\t");
        }
        else
            printf("\t");

        colletter = 0;
        for (icol = 1; icol <= tabcol; icol++)
        {
            if (irow % 5 == 1 || irow % 5 == 0)
                printf("-");
            else if (icol % 7 == 1 || icol % 7 == 0)
                printf("|");
            else if (icol % 7 == 4 && irow % 5 == 3)
            {
                printf("%c", letter[rowletter][colletter]); 
                colletter++;
            }
            else
                printf(" ");
        }

        if (irow % 5 == 3)
            rowletter++;

        printf("\n");
    }
}

/*
    getFirstLetter() gets the first letter of the word to be 
        displayed on the table

    @param full[][MAXTABLE]:    2D array of a string
    @param first[][MAXTAB:E]:   2D array of letters
    @param rowsize:     number of rows of the table
    @param colsize:     number of columns of the table

    Pre-condition:  full[][MAXTABLE] should already be 
                        the shuffled version
*/
void
getFirstLetter(WORD full[][MAXTABLE], char first[][MAXTABLE], int rowsize, int colsize)
{
    int row, col;

    for (row = 0; row < rowsize; row++)
        for (col = 0; col < colsize; col++)
            strncpy(&first[row][col], full[row][col], 1);
}

/*
    findChar() finds the letter in a 1D array

    @param str[]:   1D array of characters
    @param key:     letter to find
    @param colsize: number of columns of the table

    @return -1: if not found
    @return i:  index where the letter is

    Pre-condition:  colsize is non-negative integer
                    usually a row fofromrm a 2D array is
                        passed on the str[]
*/
int 
findChar(char str[], char key, int colsize)
{
    int found = 0, i;

    i = 0;
    while (found == 0 && i < colsize)
    {
        if (str[i] == key)
            found = 1;
        else
            i++;
    }
    
    if (!found)
        return -1;
    else
        return i;
}

/*
    flagWord() checks if the word is similar to key
    
    @param *str:    string basis, word from the table
    @param *key:    string to be compared, user input

    @return found:  1 similar, 0 not

    Pre-condition:  *str should be the same spot on the table
                        as its first letter; usually an address
                        from a 2D array of strings

    Sample call: foundWord = flagWord(WordTable[curRow][foundLetter],
                                WordInput);  
*/
int
flagWord(char *str, char *key)
{
    int found = 0;

    if (!strcmp(str, key))
        found = 1;
    
    return found;
}

/*
    MODE 1: checkTable() checks if it is a win or not; the number of '*'
        should be equal to the row
    MODE 2: checkTable counts the number of '1's and '2's; gets the
        greatest among the two
    
    @param table[][MAXTABLE]:   2D array of characters
    @param rowsize: number of rows
    @param colsize: number of colsize
    @param mode:    1 - 1 player mode
                    2 - 2 player mode

    @return 1:  if it is a win OR player 1 wins
    @return 2:  if player 2 wins
    @return 0:  lose OR tie

    Pre-condition:  this will only run at the end of the game;
                    hence the table must have '*' already
*/
int 
checkTable(char table[][MAXTABLE], int rowsize, int colsize, int mode)
{
    int i, row, col, flag;
    int p1flag, p2flag;

    if (mode == 1)
    {
        flag = 0;
        for (i = 0; i < rowsize; i++)
            if (findChar(table[i], '*', colsize) != -1)
                flag += 1;
    }
    else if (mode == 2)
    {
        p1flag = 0;
        p2flag = 0;
        for (row = 0; row < rowsize; row++)
            for (col = 0; col < colsize; col++)
                if (table[row][col] == '1')
                    p1flag += 1;
        for (row = 0; row < rowsize; row++)
            for (col = 0; col < colsize; col++)
                if (table[row][col] == '2')
                    p2flag += 1;
    }

    if (mode == 1 && flag == rowsize)
        return 1;
    else if (mode == 2 && p1flag > p2flag)
        return 1;
    else if (mode == 2 && p2flag > p1flag)
        return 2;
    else //no one won
        return 0;
}

/*
    showClue() shows random generated clues

    @param clues[]: struct array of clues in a word
    @param nclues:  number of clues in a word

    Pre-condition:  nclues > 0, no word without trivia shall be used
                        in the game
*/
void
showClue(TriviaDetail clues[], int nclues)
{
    int ind;
    
    if (nclues > 0)
    {
    	ind = rand() % nclues;
	    printf("\n----- [CLUE] --------------------------\n");
	    printf(">> %s\n", clues[ind].Relation);
	    printf(">> %s\n", clues[ind].RelValue);
	    printf("---------------------------------------\n\n");
	}
	else
		printf("\nNo clues available.\n\n");
}
// ----------------------------- GAME PHASE ----------------------------- //

// --------------------------- BONUS / ADDTL ---------------------------- //
/*
    clearContent() clears everything in the struct array of words

    @param orig[]:  struct array of words
    @param *elem:   pointer to the number of elements in the orig[] array
                    must restart to 0

    Pre-condition:  no pre-conditions necessary
*/
void
clearContent(WordDetail orig[], int *nelem)
{
    int i;

    for (i = *nelem - 1; i >= 0; i--)
        deleteWord(orig, i, nelem);
}

/*
    importAdmin() imports admin account details from a file

    @param import:      file pointer to the file containing 
                            admin account details
    @param admins[]:    array of accountDetail structure 
                            representing admin accounts
    @param *nadmin:     pointer to the variable storing 
                            the number of admin accounts

    Pre-condition:  import points to a valid file containing 
                        admin account details
                    admins[] is an array with enough space to 
                        store the imported admin account details
                    nadmin points to a variable storing a 
                        non-negative integer representing 
                        the number of admin accounts
*/
void
importAdmin(FILE *import, accountDetail admins[], int *nadmin)
{
    SCAN scanTemp;
    String30 inputTemp;
    int ctr;
    int len;

    ctr = 0;
    fgets(scanTemp, LEN100, import);
    while (!feof(import))
    {
        if (strncmp("Username: ", scanTemp, 10) == 0)
        {
            strcpy(inputTemp, &scanTemp[10]);
            len = strlen(inputTemp);
            inputTemp[len - 1] = '\0';

            strcpy(admins[ctr].username, inputTemp);
        }
        else if (strncmp("Password: ", scanTemp, 10) == 0)
        {
            strcpy(inputTemp, &scanTemp[10]);
            len = strlen(inputTemp);
            inputTemp[len - 1] = '\0';

            strcpy(admins[ctr].password, inputTemp);
            
            ctr += 1;
        }
        fgets(scanTemp, LEN100, import);
    }

    *nadmin = ctr;
}

/*
    passInput() prompts the user to input password for admin authentication

    @param admins[]:   array of accountDetail structure representing admin accounts
    @param index:      index of the admin account to authenticate

    @return 1:  if the password is correct
    @return 0:  if the password is incorrect after three attempts

    Pre-condition:  index is a valid index of the admins[] array
                    admins[index] holds the username and password for authentication
*/
int
passInput(accountDetail admins[], int index)
{
    String30 input;
    int passFlag = 1, passCor = 0;

    while (passFlag < 4 && !passCor)
    {
        printf("Admin: %s\n", admins[index].username);
        printf("Password: ");
        scanf("%s", input);

        if (strcmp(input, admins[index].password) == 0)
            passCor = 1;
        else
        {
            printf(">> Wrong password. Try Again. [%d/3]\n\n", passFlag);
            passFlag += 1;
        }
    }

    return passCor;
}

/*
    printAdmins() prints the usernames of admin accounts

    @param admins[]:    array of accountDetail structure 
                            representing admin accounts
    @param nadmins:     number of admin accounts in the array

    Pre-condition:      nadmins is a non-negative integer 
                            representing the number of admin accounts
                        admins[] contains valid admin account details
*/
void
printAdmins(accountDetail admins[], int nadmins)
{
    int i;

    printf("\n");
    for (i = 0; i < nadmins; i++)
        printf("Admin [%d]: %s\n", i + 1, admins[i].username);
    printf("\n");
}

/*
    deleteAdmin() deletes an admin account from the array

    @param admins[]:    array of accountDetail structure representing 
                            admin accounts
    @param nadmins:     pointer to the variable storing the number 
                            of admin accounts
    @param del:         index of the admin account to be deleted

    Pre-condition:      del is a valid index of the admins[] array
                        nadmins points to a variable storing a 
                            non-negative integer representing the 
                            number of admin accounts
*/
void
deleteAdmin(accountDetail admins[], int *nadmins, int del)
{
    int i;

    for (i = del + 1; i < *nadmins; i++)
        admins[i - 1] = admins[i];

    *nadmins -= 1;
}

/*
    findAdmin() finds the index of an admin account based on the username

    @param admins[]:   array of accountDetail structure representing admin accounts
    @param input:      username to search for
    @param nadmins:    number of admin accounts in the array

    @return i:         index of the admin account if found
    @return -1:        if the username is not found

    Pre-condition:  nadmins is a non-negative integer representing the number of admin accounts
                    admins[] contains valid admin account details
*/
int
findAdmin(accountDetail admins[], String30 input, int nadmins)
{
    int i, found;

    found = 0;
    for (i = 0; i < nadmins && !found; i++)
    {
        if (strcmp(input, admins[i].username) == 0)
            found = 1;
    }

    if (found)
        return i - 1;
    else
        return -1;
}

/*
    exportAdmin() exports admin account details to a file

    @param *export:     file pointer to the file to export admin account details
    @param admins[]:    array of accountDetail structure representing admin accounts
    @param nadmin:      number of admin accounts to export

    Pre-condition:  *export points to a valid file where admin account 
                        details will be exported
                    nadmin is a non-negative integer representing 
                        the number of admin accounts to export
                    admins[] contains valid admin account details
*/
void
exportAdmin(FILE *export, accountDetail admins[], int nadmin)
{
    int i, j;

    for (i = 0; i < nadmin; i++)
    {
        if (i != 0)
            fprintf(export, "\n");
        for (j = 1; j <= 2; j++)
        {
            if (j == 1)
                fprintf(export, "Username: %s\n", admins[i].username);
            else
                fprintf(export, "Password: %s\n", admins[i].password);
        }
    }
}

/*
    getInput_int() prompts the user to input an integer within a specified range

    @param dest:    pointer to the variable where the input integer will be stored
    @param start:   lower bound of the range
    @param end:     upper bound of the range

    Pre-condition:  start and end are integers representing the inclusive range
                    dest points to a variable where the input integer will be stored
*/
void
getInput_int(int *dest, int start, int end)
{
    do {
        printf("Select #: ");
        scanf("%d", dest);

        if (*dest > end || *dest < start)
            printf(">> Enter value within range.\n\n");
    } while (*dest > end || *dest < start);
}

/*
    findCategory() finds the index of a category based on the category name

    @param str[]:   array of categoryDetail structure representing categories
    @param key:     category name to search for
    @param n:       number of categories in the array

    @return i:      index of the category if found
    @return -1:     if the category name is not found

    Pre-condition:  n is a non-negative integer representing the number of categories
                    str[] contains valid category details
                    String30 catName under categoryDetail is assumed all caps;
                        hence key is converted to all caps
*/
int 
findCategory(categoryDetail str[], String30 key, int n)
{
    int i = 0;
    int found = 0;

    while (found == 0 && i < n) 
    {
        if (!strcmp(str[i].catName, key))
            found = 1;
        else
            i++;
    }

    if (!found)
        return -1;
    else
        return i;
}

/*
    convertCase() converts the case of characters in a string

    @param *str:    pointer to the string to be converted
    @param len:     length of the string
    @param *mode:   mode indicating the conversion to perform
                    1: convert uppercase to lowercase
                    2: convert lowercase to uppercase

    Pre-condition:  str points to a valid string
                    len is the length of the string pointed to by str
                    mode is either 1 or 2
*/
void
convertCase(char *str, int len, int mode)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (mode == 1)
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] += 32;
        if (mode == 2)
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] -= 32;
    }
}

/*
    generateFileName() generates a filename based on the input string

    @param *str:     pointer to the input string
    @param *dest:    pointer to the destination string where the 
                        generated filename will be stored

    Pre-condition:  str points to a valid string
*/
void
generateFileName(char *str, char *dest)
{
    int i, lett1, lett2, found, flagEx;
    int len = strlen(str);
    char incr;
    String30 temp1, temp2;
    FILE *checkDupe;

    found = 0;
    lett1 = 0;
    lett2 = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == ' ' || str[i] == '/')
            found = 1;
        else if (found)
        {
            temp2[lett2] = str[i];
            lett2++;
        }
        else
        {
            temp1[lett1] = str[i];
            lett1++;
        }
    }   

    temp1[strlen(temp1)] = '\0';
    if (temp1[0] >= 'A' && temp1[0] <= 'Z')
        temp1[0] += 32;
    strcpy(dest, "DB-");
    strncat(dest, temp1, 3);

    if (found)
    {
        temp2[strlen(temp2)] = '\0';
        if (temp2[0] >= 'A' && temp2[0] <= 'Z')
            temp2[0] += 32;
        strcat(dest, "_");
        strncat(dest, temp2, 3);
    }

    strcat(dest, ".txt");

    incr = '1';
    flagEx = 0;
    len = strlen(dest);
    do {
        checkDupe = fopen(dest, "r");

        if (checkDupe == NULL)
            flagEx = 1;
        else
        {
            dest[len - 4] = incr;
            dest[strlen(dest) - 3] = '\0';
            strcat(dest, ".txt");
        }

        incr += 1;
        fclose(checkDupe);
    } while (!flagEx && incr < 6);


}

/*
    importCategory() imports category details from a file

    @param *import:     file pointer to the file containing category details
    @param cats[]:      array of categoryDetail structure representing categories
    @param *ncat:       pointer to the variable storing the number of categories

    Pre-condition:      import points to a valid file
                        cats[] is an array with enough space
                        ncat points to a variable storing a non-negative integer
*/
void
importCategory(FILE *import, categoryDetail cats[], int *ncat)
{
    SCAN scanTemp;
    String30 inputTemp;
    int ctr;
    int len;

    ctr = 0;
    fgets(scanTemp, LEN100, import);
    while (!feof(import))
    {
        if (strncmp("Category: ", scanTemp, 10) == 0)
        {
            strcpy(inputTemp, &scanTemp[10]);
            len = strlen(inputTemp);
            inputTemp[len - 1] = '\0';

            strcpy(cats[ctr].catName, inputTemp);
        }
        else if (strncmp("Filename: ", scanTemp, 10) == 0)
        {
            strcpy(inputTemp, &scanTemp[10]);
            len = strlen(inputTemp);
            inputTemp[len - 1] = '\0';

            strcpy(cats[ctr].catFile, inputTemp);
            
            ctr += 1;
        }
        fgets(scanTemp, LEN100, import);
    }

    *ncat = ctr;
}

/*
    exportCategory() exports category details to a file

    @param *export:     file pointer to the file to export category details
    @param aCat[]:      array of categoryDetail structure representing categories
    @param ncat:        number of categories to export

    Pre-condition:      export points to a valid file
                        ncat is a non-negative integer
                        aCat[] contains valid category details
*/
void
exportCategory(FILE *export, categoryDetail aCat[], int ncat)
{
    int i, j;

    for (i = 0; i < ncat; i++)
    {
        if (i != 0)
            fprintf(export, "\n");
        for (j = 1; j <= 2; j++)
        {
            if (j == 1)
                fprintf(export, "Category: %s\n", aCat[i].catName);
            else
                fprintf(export, "Filename: %s\n", aCat[i].catFile);
        }
    }
}

/*
    printCategories() prints category details to the console

    @param aCat[]:      array of categoryDetail structure representing categories
    @param ncat:        number of categories to print
    @param mode:        mode indicating the information to print
                        1: print only category names
                        2: print category names along with filenames

    Pre-condition:      ncat is a non-negative integer
                        aCat[] contains valid category details
*/
void
printCategories(categoryDetail aCat[], int ncat, int mode)
{
    int i;

    printf("\n");
    printf("-------------- >> CATEGORIES ---------\n\n");
    for (i = 0; i < ncat; i++)
    {
        printf("Category [%d]: %s\n", i + 1, aCat[i].catName);
        if (mode == 2)
            printf("\tFilename: %s\n", aCat[i].catFile);
    }
    printf("\n--------------------------------------\n");
}

/*
    deleteCategory() deletes a category from the array of categoryDetail structures

    @param aCat[]:   array of categoryDetail structure representing categories
    @param *ncat:    pointer to the variable storing the number of categories
    @param del:      index of the category to delete

    Pre-condition:  del is a valid index of the category to delete
                    ncat points to a variable storing a non-negative integer
                    aCat[] contains valid category details
*/
void
deleteCategory(categoryDetail aCat[], int *ncat, int del)
{
    int i;

    for (i = del + 1; i < *ncat; i++)
        aCat[i - 1] = aCat[i];

    *ncat -= 1;
}
