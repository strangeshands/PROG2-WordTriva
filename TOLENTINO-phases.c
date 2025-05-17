#include "TOLENTINO-func.c"

/*
    adminPhase() is basically the whole admin phase
    In this phase, the user is given 8 choices that 
        can to create, edit, delete, modify, and
        import/export list of words to be used in 
        the game phase
    Calls functions from WordTrivia-func.c

    @param aWordsList[]:    struct array; the list of words to 
                                be modified in this phase
    @param *numElem:    a pointer to the number of words in the list
*/
void
adminPhase(WordDetail aWordsList[], int *numElem)
{
    //user inputs
    SCAN wordInput; 
    SCAN trivName, trivVal;

    //storing
    WordDetail tempContainer[MAX500];

    //selections
    char ViewSelection, fileSelect;
    int wordSelect, AdminSelection, numEditSelect, 
        modifyTrivSelect, modifySelect;
    WORD fileNameInput, modWord;

    //counters/checkers
    int valid, flag, elemInd,
        expFlag, impFlag, displayFlag;

    //file
    FILE *fp_export, *fp_import;

    do {
        // -- ADMIN SELECTION START -- //
        displayAdminSelection();
        getInput_int(&AdminSelection, 0, 8);
        printf("\n");
        fflush(stdin); //clearing input buffer
        // -- ADMIN SELECTION END -- //

        switch (AdminSelection)
        {
            // -- ADD WORD START -- //
            case 1:
            {
                printf("------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-* [ ADD WORD ] *-*-*-*-*-*-*-*-*\n");
                printf("------------------------------------------------\n\n");

                if (*numElem < 150)
                {
                    printf(">> Current word count: %d/%d\n\n", *numElem, MAX);
                    do { 
                        valid = AddWord(wordInput, aWordsList, numElem);
                        fflush(stdin); //clearing input buffer

                        printf("[Word Counter] %d\n\n", *numElem);
                    
                        elemInd = *numElem - 1;
                        if (strcmp(wordInput, "0") && valid)
                        {
                            aWordsList[elemInd].RelCtr = 0;
                            do {
                                AddTrivia(trivName, trivVal, aWordsList[elemInd].Trivia, 
                                        &aWordsList[elemInd].RelCtr);

                                printf("[Trivia Counter for %s] %d\n\n", wordInput, 
                                                                        aWordsList[elemInd].RelCtr);
                            } while (strcmp(trivName, "0") && aWordsList[elemInd].RelCtr < 10);

                            if (aWordsList[elemInd].RelCtr == 10)
                                printf(">> Maximum trivia reached for %s.\n\n", wordInput);
                        }

                        if (*numElem != 0)
                        {
                            arrangeAlphabetical(aWordsList, *numElem);
                            displayWord (aWordsList, *numElem);
                            printf ("\n"); //spacer
                        }
                    } while (strcmp(wordInput, "0")  && *numElem < MAX);
                }
                else
                    printf(">> Maximum word count reached %d/%d.\n\n", *numElem, MAX);

                break;
            }
            // -- ADD WORD END -- //
            // -- ADD TRIVIA START -- //
            case 2:
            {
                printf("--------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-* [ ADD TRIVIA ] *-*-*-*-*-*-*-*-*\n");
                printf("--------------------------------------------------\n\n");

                displayFlag = 0;

                if (*numElem == 0)
                    printf(">> No words to display.\n\n");
                else
                {
                    do {
                        arrangeAlphabetical(aWordsList, *numElem);
                        if (!displayFlag)
                            displayWord(aWordsList, *numElem);
                        printf ("\n"); //spacer

                        displayFlag = 1;

                        printf("Select Word: ");
                        getInput(modWord, LEN20);

                        if (strcmp(modWord, "0") != 0)
                            wordSelect = findWord(aWordsList, modWord, *numElem);

                        if (strcmp(modWord, "0") == 0)
                            printf(">> Exiting...\n\n");
                        else if (wordSelect == -1)
                            printf(">> Word not found.\n");
                        else
                        {
                            displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);

                            if (aWordsList[wordSelect].RelCtr == 10)
                            {
                                printf(">> Maximum trivia reached for %s.\n\n", aWordsList[wordSelect].Answer);
                                displayFlag = 0;
                            }
                            else
                            {
                                strcpy(trivName, "\0"); //to start loop
                                while (strcmp(trivName, "0") && aWordsList[wordSelect].RelCtr < 10)
                                {
                                    flag = AddTrivia(trivName, trivVal, aWordsList[wordSelect].Trivia, 
                                            &aWordsList[wordSelect].RelCtr);

                                    if (flag)
                                    {
                                        printf("[Trivia Counter for %s] %d\n", aWordsList[wordSelect].Answer, 
                                                                            aWordsList[wordSelect].RelCtr);
                                        displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);
                                    }

                                    if (aWordsList[wordSelect].RelCtr == 10)
                                         printf(">> Maximum trivia reached for %s.\n\n", aWordsList[wordSelect].Answer);

                                    displayFlag = 0;
                                }
                            }
                        }
                    } while (strcmp(modWord, "0") != 0);
                }
                break;
            }
            // -- ADD TRIVIA END -- //
            // -- MODIFY ENTRY START -- //
            case 3:
            {
                printf("---------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-* [ MODIFY WORD ] *-*-*-*-*-*-*-*-*\n");
                printf("---------------------------------------------------\n\n");

                displayFlag = 0;
                if (*numElem == 0)
                    printf(">> No words to display.\n\n");
                else
                {
                    do {
                        arrangeAlphabetical(aWordsList, *numElem);
                        if (!displayFlag)
                            displayWord (aWordsList, *numElem);
                        displayFlag = 1;

                        printf ("\n"); //spacer
                        printf("Modify Word: ");
                        getInput(modWord, LEN20);

                        if (strcmp(modWord, "0") != 0)
                            wordSelect = findWord(aWordsList, modWord, *numElem);
                            
                        fflush(stdin); //clearing input buffer
                        //printf("\n"); //spacer

                        if (strcmp(modWord, "0") == 0)
                            printf(">> Exiting...\n\n");
                        else if (wordSelect == -1)
                            printf(">> Word not found.\n");
                        else
                        {
                            flag = 1;
                            do {
                                displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);
                                printf("Modify Word [1]    Modify Trivia [2]    Exit [0]\n\n");
                                getInput_int(&modifySelect, 0, 2);
                                fflush(stdin); //clearing input buffer
                                //printf("\n"); //spacer

                                if (modifySelect == 0)
                                {
                                    printf(">> [%s] Exiting...\n\n", aWordsList[wordSelect].Answer);
                                    printf("=================================================\n");
                                    printf("=================================================\n\n\n");
                                }
                                else if (modifySelect == 1)
                                {
                                    printf("\n============ >> MODIFY WORD\n\n");
                                    flag = modifyWord(wordInput, aWordsList, wordSelect, *numElem);
                                }
                                else if (modifySelect == 2)
                                {
                                    do {
                                        printf("\n============ >> MODIFY TRIVIA\n\n");
                                        printf("[%s] Edit Trivia #: ", aWordsList[wordSelect].Answer);
                                        scanf("%d", &numEditSelect);
                                        fflush(stdin); //clearing input buffer

                                        numEditSelect -= 1;

                                        if (numEditSelect < -1 || numEditSelect >= aWordsList[wordSelect].RelCtr)
                                            printf(">> Please enter value within range.\n");
                                        else if (numEditSelect == -1)
                                        {
                                            printf(">> Exiting...\n");
                                            printf("\n============ >> EXIT: MODIFY TRIVIA\n\n");
                                        }
                                        else
                                        {
                                            do {
                                                printf("\n>> EDITING [%d] -- [%s: %s] <<\n\n", numEditSelect + 1, 
                                                                                        aWordsList[wordSelect].Trivia[numEditSelect].Relation,
                                                                                        aWordsList[wordSelect].Trivia[numEditSelect].RelValue);

                                                printf("Modify Relation [1]    Modify Relation Value [2]\n");
                                                printf("  Modify Both [3]             Exit [0]\n\n");

                                                do {
                                                    printf("Enter Selection #: ");
                                                    scanf("%d", &modifyTrivSelect);
                                                    fflush(stdin); //clearing input buffer

                                                    if (modifyTrivSelect < 0 || modifyTrivSelect > 3)
                                                        printf(">> Enter valid input.\n\n");
                                                } while (modifyTrivSelect < 0 || modifyTrivSelect > 3);

                                                if (modifyTrivSelect != 0)
                                                    printf("\n"); //spacer

                                                if (modifyTrivSelect == 1)
                                                    flag = modifyRelation(trivName, aWordsList[wordSelect].Trivia, numEditSelect,
                                                                            aWordsList[wordSelect].RelCtr, 1);
                                                else if (modifyTrivSelect == 2)
                                                    flag = modifyRelValue(trivVal, aWordsList[wordSelect].Trivia, numEditSelect,
                                                                aWordsList[wordSelect].RelCtr, 1);
                                                else if (modifyTrivSelect == 3)
                                                    flag = modifyTrivia(trivName, trivVal, aWordsList[wordSelect].Trivia, 
                                                                numEditSelect, aWordsList[wordSelect].RelCtr);
                                                else
                                                {
                                                    printf(">> Exiting...\n");
                                                    displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);
                                                }

                                                if (flag == 1 || flag == 2)
                                                    displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);
                                            } while (modifyTrivSelect != 0 && (flag != 1 && flag != 2));
                                        }
                                    } while (numEditSelect != -1);
                                }
                                displayFlag = 0;
                            } while (modifySelect != 0);
                        }
                    } while (strcmp(modWord, "0") != 0);
                }
                break;
            }
            // -- MODIFY ENTRY END -- //
            // -- DELETE WORD START -- //
            case 4:
            {
                displayFlag = 0;
                printf("---------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-* [ DELETE WORD ] *-*-*-*-*-*-*-*-*\n");
                printf("---------------------------------------------------\n\n");

                if (*numElem == 0)
                    printf(">> No words to display.\n\n");
                else
                {
                    do {
                        arrangeAlphabetical(aWordsList, *numElem);
                        if (!displayFlag)
                            displayWord (aWordsList, *numElem);
                        printf ("\n"); //spacer

                        printf("Select Word: ");
                        getInput(modWord, LEN20);
                        fflush(stdin); //clearing input buffer

                        if (strcmp(modWord, "0") != 0)
                            wordSelect = findWord(aWordsList, modWord, *numElem);

                        if (strcmp(modWord, "0") == 0)
                            printf(">> Exiting...\n\n");
                        else if (wordSelect == - 1)  
                        {
                            printf(">> Word not found.\n");
                            displayFlag = 1;
                        }
                        else
                        {
                            printf(">> %s successfuly deleted!\n\n", aWordsList[wordSelect].Answer);
                            deleteWord(aWordsList, wordSelect, numElem);
                            displayFlag = 0;
                        }

                        if (*numElem == 0)
                            printf(">> All words have been deleted.\n\n");
                    } while (strcmp(modWord, "0") != 0 && *numElem != 0);
                }
                break;
            }
            // -- DELETE WORD END -- //
            // -- DELETE TRIVIA START -- //
            case 5:
            {
                displayFlag = 0;

                printf("---------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-* [ DELETE CLUE ] *-*-*-*-*-*-*-*-*\n");
                printf("---------------------------------------------------\n\n");

                if (*numElem == 0)
                    printf(">> No words to display.\n\n");
                else
                {
                    do {
                        arrangeAlphabetical(aWordsList, *numElem);
                        if (!displayFlag)
                            displayWord (aWordsList, *numElem);
                        printf ("\n"); //spacer

                        printf("Select Word: ");
                        getInput(modWord, LEN20);
                        fflush(stdin); //clearing input buffer

                        if (strcmp(modWord, "0") != 0)
                            wordSelect = findWord(aWordsList, modWord, *numElem);

                        if (strcmp(modWord, "0") == 0)
                            printf(">> Exiting...\n\n");
                        else if (wordSelect == -1)
                        {
                            printf(">> Word not found.\n");
                            displayFlag = 1;
                        }       
                        else
                        {
                            displayFlag = 0;

                            if (aWordsList[wordSelect].RelCtr != 0)
                            {
                                do {
                                    if (!displayFlag)
                                        displayContent(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);
                                    
                                    printf("Delete Trivia #: ");
                                    scanf("%d", &numEditSelect);
                                    fflush(stdin); //clearing input buffer
                                    numEditSelect -= 1;

                                    if (numEditSelect >= aWordsList[wordSelect].RelCtr || numEditSelect < -1)
                                    {
                                        printf(">> Please input number within the range.\n\n");
                                        displayFlag = 1;
                                    }
                                    else if (numEditSelect == -1)
                                    {
                                        printf(">> Exiting...\n\n");
                                        displayFlag = 0;
                                    }
                                    else
                                    {
                                        printf(">> %s as %s succesffuly deleted!\n", 
                                                                aWordsList[wordSelect].Trivia[numEditSelect].RelValue,
                                                                aWordsList[wordSelect].Trivia[numEditSelect].Relation);

                                        deleteTrivia(aWordsList[wordSelect].Trivia, numEditSelect, 
                                                    &aWordsList[wordSelect].RelCtr);

                                        displayFlag = 0;
                                    }
                                } while (numEditSelect != -1 && aWordsList[wordSelect].RelCtr != 0);
                            }

                            if (aWordsList[wordSelect].RelCtr == 0)
                                printf(">> All trivia for word [%s] have been deleted.\n\n\n",
                                                                     aWordsList[wordSelect].Answer);
                        }
                    } while (strcmp(modWord, "0") != 0 && *numElem != 0);
                }

                break;
            }
            // -- DELETE TRIVIA END -- //
            // -- VIEW WORD/CLUES START -- //
            case 6:
            {
                printf("----------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-*-*-* [ VIEW ] *-*-*-*-*-*-*-*-*-*-*\n");
                printf("----------------------------------------------------\n\n");

                if (*numElem > 0)
                {
                    do {
                        arrangeAlphabetical(aWordsList, *numElem);
                        displayWord (aWordsList, *numElem);
                        printf ("\n"); //spacer

                        do {
                            printf("Select Word: ");
                            getInput(modWord, LEN20);
                            fflush(stdin); //clearing input buffer

                            if (strcmp(modWord, "0") != 0)
                            {
                                wordSelect = findWord(aWordsList, modWord, *numElem);
                                
                                if (wordSelect == -1)
                                {
                                    printf(">> Word not found.\n\n");
                                    displayFlag = 1;
                                } 
                            }
                        } while (strcmp(modWord, "0") != 0 && wordSelect == -1);

                        if (strcmp(modWord, "0") != 0)
                        {
                            flag = 1; //flag for view word
                            do {
                                if (flag)
                                    displayContent2(aWordsList, wordSelect, aWordsList[wordSelect].RelCtr);   

                                do {

                                    printf("Next/Previous/Exit [N/P/0]: ");
                                    scanf(" %c", &ViewSelection);
                                    convertCase(&ViewSelection, 1, 2);
                                    fflush(stdin); //clearing input buffer

                                    if (ViewSelection != 'N' && ViewSelection != 'P' && ViewSelection != '0')
                                        printf(">> Invalid input.\n\n");

                                } while (ViewSelection != 'N' && ViewSelection != 'P' && ViewSelection != '0');

                                if (ViewSelection == 'P')
                                {
                                    if (wordSelect - 1 < 0)
                                    { 
                                        printf(">> You are viewing the first word.\n\n");
                                        flag = 0;
                                    }
                                    else
                                    {
                                        wordSelect -= 1;
                                        flag = 1;
                                    }
                                }
                                else if (ViewSelection == 'N')
                                {
                                    if (wordSelect + 1 >= *numElem)
                                    { 
                                        printf(">> You are viewing the last word.\n\n");
                                        flag = 0;
                                    }
                                    else
                                    {
                                        wordSelect += 1;
                                        flag = 1;
                                    }
                                }
                                else 
                                    printf (">> Exiting...\n\n");
                            } while (wordSelect < *numElem && ViewSelection != '0');
                        }
                        else
                            printf (">> Exiting..\n\n");
                    } while (strcmp(modWord, "0") != 0);
                }
                else
                    printf(">> No words added yet.\n\n");
                
                break;
            }
            // -- VIEW WORD/CLUES END -- //
            // -- EXPORT START -- //
            case 7:
            {
                printf("------------------------------------------------------\n");
                printf("*-*-*-*-*-*-*-*-*-*-* [ EXPORT ] *-*-*-*-*-*-*-*-*-*-*\n");
                printf("-----------------------------------------------------\n\n");

                if (*numElem > 0)
                {
                    expFlag = 0;
                    do {
                        do {
                            printf("Enter Filename [file.txt]: ");
                            getInput(fileNameInput, LEN100);

                            valid = checkWordValid(fileNameInput, LEN30);
                            if (!valid)
                                printf(">> Please input valid word and length.\n\n");
                        } while (!valid);

                        if ((strcmp(fileNameInput, "0") != 0))
                        {
                            catTxt(fileNameInput);
                            fp_export = fopen(fileNameInput, "r");
                            
                            if (fp_export != NULL)
                            {
                                printf(">> File already exists.\n\n");
                                do {
                                    printf(">> Overwrite [W] Cancel [C]? ");
                                    scanf(" %c", &fileSelect);
                                    convertCase(&fileSelect, 1, 2);

                                    if (fileSelect != 'W' && fileSelect != 'C')
                                        printf(">> Enter valid character.\n\n");
                                } while (fileSelect != 'W' && fileSelect != 'C');
                            }

                            if (fileSelect == 'W' || fp_export == NULL)
                            {
                                fp_export = fopen(fileNameInput, "w");
                                
                                printf(">> Exporting... \n");
                                exportContent(fp_export, aWordsList, *numElem);

                                fclose(fp_export);

                                expFlag = 1;
                            }
                            else
                                printf(">> Please enter unique file name.\n\n");
                        }
                        else
                            printf("\n>> Exiting...\n");
                    } while (strcmp(fileNameInput, "0") != 0 && !expFlag);

                    printf ("\n"); //spacer
                }
                else
                    printf(">> No words added yet.\n\n");

                break;
            }
            // -- EXPORT END -- //
            // -- IMPORT START -- //
            case 8:
            { 
                if (*numElem < 150)  
                {
                    printf("------------------------------------------------------\n");
                    printf("*-*-*-*-*-*-*-*-*-*-* [ IMPORT ] *-*-*-*-*-*-*-*-*-*-*\n");
                    printf("------------------------------------------------------\n\n");

                    impFlag = 0;
                    do {
                        do {
                            printf("Enter Filename [file.txt]: ");
                            getInput(fileNameInput, LEN100);
                            

                            valid = checkWordValid(fileNameInput, LEN30);
                            if (!valid)
                                printf(">> Please input valid word and length.\n\n");
                        } while (!valid);

                        if (strcmp(fileNameInput, "0") != 0)
                        {
                            catTxt(fileNameInput);
                            fp_import = fopen(fileNameInput, "r");

                            if (fp_import == NULL)
                                printf(">> File does not exist.\n\n");
                            else
                            {
                                printf("\n>> Importing... \n");
                                importContent(fp_import, tempContainer, aWordsList, numElem);
                                printf(">> %d words loaded.\n\n", *numElem);
                                impFlag = 1;

                                fclose(fp_import);
                            }
                        }
                        else
                            printf(">> Exiting...\n\n");
                    } while (strcmp(fileNameInput, "0") != 0 && !impFlag);
                }
                else
                    printf(">> Maximum word count reached.\n\n");

                break;
            }
            // -- IMPORT END -- //
            case 0:
            {
                if (*numElem > 0)
                {
                    clearContent(aWordsList, numElem);
                    printf(">> Array content erased.\n");
                }
                printf(">> Exiting...\n\n");
            }
                break;
        }
    } while (AdminSelection != 0);
}

/*
    gamePhase() is basically the Word Trivia game itself
    Calls functions from WordTrivia-func.c

    @param aWordsList[]:    struct array; the list of words to 
                                be used in the game
    @param *numElem:    a pointer to the number of words in the list
    @param gameMode:    0 - default
                        non-zero integer - category game
    @param categories[]:    struct array; the list of categories
                                available
    @param playMode:    1 - 1 player mode
                        2 - 2 player mode
*/
void
gamePhase(WordDetail aWordsList[], int *numElem, int gameMode, 
        categoryDetail categories[], int playMode)
{
    // --------- variables --------- // 
    WordDetail tempContainer[MAX500];
    WORD shuffled[MAX];

    char LetterTable[MAXTABLE][MAXTABLE];
    WORD WordTable[MAXTABLE][MAXTABLE];

    WORD WordInput;
    char letterInput;
    int foundLetter, foundWord, checkWin;

    int rowInput, colInput, curRow, 
        wordInd, size;
    int doneShuffle, importFlag, sizeInputFlag, 
        endTableFlag, rowFlag, countFlag, mainGameFlag,
        answerFlag, P1RowFlag, P2RowFlag;
    int importSelect, gameSelect;
    int currPlayer;

    letterDetail firstLetters[26];
    int numLetters;
    int successCount;

    SCAN filename;
    FILE *import;
    // --------- variables --------- // 

    // initialize //
    mainGameFlag = 0;
    importFlag = 0;
    // initialize //

    printf("\n====================================================================================\n");

    while (!mainGameFlag)
    {
        printf("\n                                 >> %d PLAYER MODE <<\n", playMode);

        currPlayer = 1; 
        sizeInputFlag = 1;    
        size = 0;

        // when the gameMode is a category game, importing comes first //
        if (gameMode != 0 && !importFlag)
        {
            strcpy(filename, categories[gameMode - 1].catFile);
            printf("\n>> Loading database...");

            import = fopen(filename, "r");

            if (import == NULL)
            {
                printf("\n>> ERROR: Database not found.\n\n");

                mainGameFlag = 1;
                doneShuffle = 0;
                countFlag = 0;
                sizeInputFlag = 0;
            }
            else
            {
                printf("\n>> Importing... \n");
                importContent(import, tempContainer, aWordsList, numElem);
                fclose(import);

                filterWords(aWordsList, numElem);

                if (*numElem < 1)
                {
                    printf(">> No words found. Game won't proceed.\n\n");

                    mainGameFlag = 1;
                    doneShuffle = 0;
                    countFlag = 0;
                    sizeInputFlag = 0;
                }
                importFlag = 1; //stopping import portion
            }
        }

        // informing user of the current number of elements //
        if (sizeInputFlag)
            printf("\n>> Current words: %d/%d.\n", *numElem, MAX);
        if (*numElem == 150 && !importFlag)
        {
            importFlag = 1; //stopping import portion
            printf(">> Word database full, can not add more.\n");
        }

        // input validation for board size //
        if (sizeInputFlag)
        {
            do {
                printf("\nEnter number of rows #: ");
                scanf("%d", &rowInput);
                printf("Enter number of columns #: ");
                scanf("%d", &colInput);

                size = rowInput * colInput;

                if (rowInput < 0 || colInput < 0)
                    printf(">> Invalid range.\n");
                else if (size < 0 || size > 150)
                    printf(">> Cell count invalid.\n");
            } while (size < 0 || size > 150 ||
                    rowInput < 0 || colInput < 0);
        }
        // input validation for board size //

        if (size)
            printf("\n>> Board Size: %d\n", size);

        if (size == 0)
        {
            printf(">> Exiting...\n\n");
            clearContent(aWordsList, numElem);

            mainGameFlag = 1;
            doneShuffle = 0;
            countFlag = 0;
        }
        else if (!importFlag)
        {
            // import file portion //
            while (!importFlag)
            {
                printf("\nEnter file to import: ");
                scanf("%s", filename);

                if (strcmp(filename, "0") == 0) //user chose to cancel
                {
                    printf(">> Exiting...\n\n");
                    clearContent(aWordsList, numElem);

                    importFlag = 1;
                    mainGameFlag = 1;
                    doneShuffle = 0;
                    countFlag = 0;
                }
                else
                {
                    import = fopen(filename, "r");

                    if (import == NULL)
                        printf(">> File does not exist.\n");
                    else
                    {
                        printf("\n>> Importing... \n");
                        importContent(import, tempContainer, aWordsList, numElem);
                        fclose(import);

                        filterWords(aWordsList, numElem);
                        printf(">> Current words: %d/%d.\n", *numElem, MAX);

                        importFlag = 1; //ends the import file portion
                    }
                }
            }
            // import file portion //
        }

        // checking the word count //
        if (*numElem < size && strcmp(filename, "0") && size != 0)
        {
            printf(">> Insufficient words. Game won't proceed.\n");
            printf("\n           --------------------------------------------------------------\n");

            importFlag = 0;
            doneShuffle = 0; 
            countFlag = 0;
            clearContent(aWordsList, numElem);
        }
        else if (*numElem >= size && size != 0)
        {
            countEntries(aWordsList, firstLetters, *numElem, &numLetters);
            successCount = validEntryCount(firstLetters, numLetters, rowInput, 
                                        colInput, size, *numElem);

            if (successCount)
            {
                countFlag = 1; //the only time the game will proceed to the next step (shuffling)
                doneShuffle = 0;
            }
            else
            {
                printf(">> Insufficient letter count. Game won't proceed\n\n");
                printf("\n           --------------------------------------------------------------\n");

                clearContent(aWordsList, numElem);

                importFlag = 0;
                doneShuffle = 0;
                countFlag = 0;
            }
        }
        // checking the word count //

        // shuffling //
        if (countFlag)
        {
            doneShuffle = 0;
            printf("\n-----------------------------------------\n");
            printf(">> Preparing table.\n");
            printf(">> This might take a while.\n");
            printf("-----------------------------------------\n");

            printf("\n-");
            doneShuffle = shuffler1(aWordsList, shuffled, WordTable, firstLetters, 
                                rowInput, colInput, size, *numElem, numLetters);
            if (!doneShuffle)
            { 
                printf("-");
                doneShuffle = shuffler2(aWordsList, shuffled, WordTable, firstLetters,
                                rowInput, colInput, size, *numElem, numLetters);
            }

            if (!doneShuffle)
            {
                // safety net -- sometimes the computer can't generate combinations // 
                printf("\n\n");
                printf("-------------------------------------------------------------\n");
                printf("                           UH OH!\n");
                printf(">> It took too long to load.\n");
                printf(">> Please check entry count and cell count.\n");
                printf(">> Please try again.\n");
                printf("-------------------------------------------------------------\n");
                printf("\n           --------------------------------------------------------------\n");
                doneShuffle = 0;
            }
        }
        // shuffling //

        // GAME PROPER -- will only start if shuffling is successful //
        if (doneShuffle)
        {
            getFirstLetter(WordTable, LetterTable, rowInput, colInput);

            curRow = 0;
            rowFlag = 0;
            endTableFlag = 0;

            P1RowFlag = 0;
            P2RowFlag = 0;

            printf("\n\n"); //spacer
            printf("====================================================================================\n");
            printf("===== >> NOW PLAYING =================================\n");
            printf("====================================================================================\n\n");
            printTable(LetterTable, rowInput, colInput, curRow);
            printf("\n"); //spacer

            do {
                if (playMode == 2)
                    printf(">> CURRENT PLAYER: PLAYER %d\n\n", getCurrPlayer(currPlayer));

                do {
                    printf("Letter: ");
                    scanf(" %c", &letterInput);
                    fflush(stdin); //clearing input buffer

                    if (!(letterInput >= 'a' && letterInput <= 'z') &&
                        !(letterInput >= 'A' && letterInput <= 'Z') &&
                        !(letterInput == '0'))
                    {
                        printf(">> Letters only.\n\n");
                        foundLetter = -1;
                    }
                    else if (letterInput == '0')
                    {
                        printf(">> Exiting...\n\n");
                        endTableFlag = 1;
                    }
                    else
                    {
                        foundLetter = findChar(LetterTable[curRow], letterInput, colInput);

                        if (foundLetter == -1)
                            printf(">> Select letter within the row.\n\n");
                        else
                        {
                            //show clue
                            wordInd = findWord(aWordsList, WordTable[curRow][foundLetter], *numElem);
                            showClue(aWordsList[wordInd].Trivia, aWordsList[wordInd].RelCtr);

                            answerFlag = 1;
                            do {
                                printf("What's the word: ");
                                getInput(WordInput, LEN20);
                                fflush(stdin); //clearing input buffer

                                if (strcmp(WordInput, "0") == 0)
                                {
                                    printf(">> Exiting...\n\n");
                                    endTableFlag = 1;
                                    letterInput = '0';
                                    answerFlag = 3; //force end the loop
                                }
                                else
                                {
                                    foundWord = flagWord(WordTable[curRow][foundLetter], WordInput);

                                    if (!foundWord && playMode == 2 && answerFlag == 1)
                                    {
                                        printf (">> Uh-oh! Player %d answered wrong.\n", getCurrPlayer(currPlayer));
                                        currPlayer++;
                                        answerFlag++;
                                        printf (">> Player %d has a chance to steal.\n\n", getCurrPlayer(currPlayer));
                                    }
                                    else if (!foundWord)
                                    {
                                        printf (">> Uh-oh! You answered wrong.\n");
                                        printf(">> Answer: %s\n\n", WordTable[curRow][foundLetter]);
                                        LetterTable[curRow][foundLetter] = '-';

                                        if (playMode == 2)
                                            currPlayer++;

                                        answerFlag = 3; //force end the loop
                                    }
                                    else
                                    {
                                        printf (">> You guessed it right!\n\n");
                                        if (playMode == 1)
                                            LetterTable[curRow][foundLetter] = '*';
                                        else if (currPlayer % 2 == 1)
                                        {
                                            LetterTable[curRow][foundLetter] = '1';
                                            P1RowFlag = 1;
                                        }
                                        else if (currPlayer % 2 == 0)
                                        {
                                            LetterTable[curRow][foundLetter] = '2';
                                            P2RowFlag = 1;
                                        }

                                        answerFlag = 3; //force end the loop
                                    }
                                }
                            } while (answerFlag <= 2);
                        }
                    }
                } while (foundLetter == -1 && letterInput != '0');

                if (letterInput != '0')
                {
                    if (playMode == 1)
                    {
                        if (foundWord)
                        {
                            curRow++;
                            rowFlag = 0;
                        }
                        else
                            rowFlag++;

                        if (rowFlag == colInput)
                            endTableFlag = 1;
                    }
                    else if (playMode == 2)
                    {
                        if (P1RowFlag && P2RowFlag)
                        {
                            curRow++;
                            rowFlag = 0;
                            currPlayer++;

                            P1RowFlag = 0;
                            P2RowFlag = 0;
                        }
                        else if (P1RowFlag)
                        {
                            currPlayer = 2;
                            rowFlag++;
                        }
                        else if (P2RowFlag)
                        {
                            currPlayer = 1;
                            rowFlag++;
                        }
                        else
                            rowFlag++;

                        if (rowFlag == colInput)
                        {
                            if (P1RowFlag || P2RowFlag)
                            {
                                curRow++;
                                rowFlag = 0;
                                P1RowFlag = 0;
                                P2RowFlag = 0;
                            }
                            else
                                endTableFlag = 1;
                        }
                    }

                    printTable(LetterTable, rowInput, colInput, curRow);
                    printf("\n"); //spacer
                }
            } while (curRow < rowInput && !endTableFlag);

            if (letterInput != '0')
            {
                if (playMode == 1)
                {
                    checkWin = checkTable(LetterTable, rowInput, colInput, 1);

                    if (checkWin)
                        printf("Congrats! You won.\n\n");
                    else
                        printf("Uh-oh. Game over.\n\n");
                }
                if (playMode == 2)
                {
                    checkWin = checkTable(LetterTable, rowInput, colInput, 2);

                    if (checkWin)
                        printf("PLAYER %d won!\n\n", checkWin);
                    else if (curRow == rowInput)
                        printf("It's a tie.\n\n");
                    else if (endTableFlag)
                        printf("Uh-oh. Game over.\n\n");
                }
            }

            // PLAY AGAIN SEGMENT -- asking if the user wants to play again // 
            printf("====================================================================================\n\n");
            printf("                            Play Again [1]     Exit [0]\n\n");
            getInput_int(&gameSelect, 0, 1);
 
            if (gameSelect == 1 && gameMode == 0)
            {
                printf("\n           --------------------------------------------------------------\n\n");
                printf("                               >> Current words: %d/%d. <<\n\n", *numElem, MAX);
                printf("                Add Another Set of Words [1]     Use Current File [2]\n");
                printf("                                 Use Another File [3]\n\n");
                getInput_int(&importSelect, 1, 3);

                if (importSelect == 1)
                    importFlag = 0;
                else if (importSelect == 2)
                    importFlag = 1;
                else
                {
                    clearContent(aWordsList, numElem);
                    importFlag = 0;
                }
            }
            else if (gameSelect == 0)
            {
                printf(">> Thank you for playing!\n\n");
                mainGameFlag = 1;
                clearContent(aWordsList, numElem);
            }
            // asking if the user wants to play again // 
        }
    }
}

// BONUS FEATURE 1 //
/*
    BON_ADMIN() allows users (or admins) to make accounts.

    @param admins[]: struct array where admin details are stored
    @param *nadmins: pointer to the number of admins
    @param *adminsign: pointer to the index of current admin signed in
    @param selection:   1 - sign in
                        2 - make new account
                        3 - delete account

    @return 1: succes sign in
    @return 2: success make new account + sign in
    @return 3: success delete account
    @return 0: no changes

    Precondition:   selection should be 1 to 3 only
                    *nadmins can be 0 up to 5 only
*/
int
BON_ADMIN(accountDetail admins[], int *nadmins, int *adminsign, int selection)
{
    int adminInd;
    int success, deleteFlag, changeFlag;
    String30 userInput;

    changeFlag = 0;
    if (*nadmins == 0 && selection != 2)
        printf(">> No existing user.\n\n");
    else if (selection == 3)
    {
        if (*nadmins == 0)
            printf(">> No existing user.\n\n");

        deleteFlag = 0;
        while (!deleteFlag && *nadmins > 0) 
        {
            printAdmins(admins, *nadmins);

            printf("Delete User -- ");
            getInput_int(&adminInd, 0, *nadmins);

            adminInd -= 1;

            if (adminInd != -1)
            {
                printf("\n-- Enter password to confirm\n\n");
                success = passInput(admins, adminInd);

                if (success)
                {
                    printf("\n>> User %s successfuly deleted.\n", admins[adminInd].username);
                    deleteAdmin(admins, nadmins, adminInd);
                    changeFlag = 3;
                }
                else
                {
                    printf("\n>> No changes made.\n\n");
                    deleteFlag = 1;
                }
            }
            else
            {
                printf(">> Exiting...\n");
                deleteFlag = 1;
            }

            if (*nadmins == 0)
            {
                deleteFlag = 1;
                printf("\n>> All users have been deleted.\n\n");
            }
        } 
    }
    else if (selection == 1)
    {
        printf("\nEnter Username: ");
        scanf("%s", userInput);

        if (strcmp(userInput, "0") != 0)
        {
            adminInd = findAdmin(admins, userInput, *nadmins);

            if (adminInd != -1)
            {
                printf("\n");
                success = passInput(admins, adminInd);

                if (success)
                {
                    *adminsign = adminInd;
                    changeFlag = 1;
                }
                else
                {
                    changeFlag = 3;
                    printf(">> User %s has been deleted.\n\n", admins[adminInd].username);
                    deleteAdmin(admins, nadmins, adminInd);
                }
            }
            else
                printf(">> User does not exists. Try making new account.\n");
        }
        else
            printf(">> Exiting...\n\n");
    }
    else if (selection == 2 && *nadmins < 5)
    {
        printf("\nEnter Username: ");
        scanf("%s", userInput);

        if (strcmp(userInput, "0") == 0)
            printf(">> Exiting...\n\n");
        else
        {
            adminInd = findAdmin(admins, userInput, *nadmins);
            if (adminInd == -1)
            {
                strcpy(admins[*nadmins].username, userInput);
                printf("Enter Password: ");
                scanf("%s", userInput);
                strcpy(admins[*nadmins].password, userInput);

                adminInd = *nadmins;
                *adminsign = adminInd;
                *nadmins += 1;

                changeFlag = 2;
            }
            else
                printf(">> User already exists.\n\n");
        }
    }
    else if (*nadmins == 5 && selection != 0)
        printf(">> Admin count has reached limit. Delete an admin to proceed.\n\n");

    return changeFlag;
}

// BONUS FEATURE 2 //
/*
    BON_CATEGORY() allows admins to manage categories; this also adds another
        game mode for the game phase.

    @param *aCat: struct array of the category details
    @param *nCat: a pointer to the number of categories

    @return 1: success add category or delete category
    @return -1: exit

    Precondition:   *ncat can be 0 up to 5 only
*/
int
BON_CATEGORY(categoryDetail *aCat, int *ncat)
{
    int select1, select2;
    String30 catInput;
    int find, ctr;
    String30 genFile;
    int changeFlag;
    FILE *newFile;

    printf("\n             =================== MANAGE CATEGORIES ===================\n\n");
    printf("                            >> [1] Add Category    <<\n");
    printf("                            >> [2] Delete Category <<\n");
    printf("                            >> [3] Show Categories <<\n");
    printf("                            >> [0] Back            <<\n\n");

    getInput_int(&select1, 0, 3);
    fflush(stdin);

    changeFlag = 0;
    switch (select1)
    {
        case 1:
        {
            ctr = *ncat;
            if (*ncat < MAX5)
            {
                printf("\n");
                printf("Enter Category Name: ");
                getInput(catInput, 30);
                convertCase(catInput, strlen(catInput), 2);

                if (strcmp(catInput, "0") != 0)
                {
                    find = findCategory(aCat, catInput, *ncat);

                    if (find == -1)
                    {
                        strcpy(aCat[ctr].catName, catInput);

                        convertCase(catInput, strlen(catInput), 1);
                        generateFileName(catInput, genFile);
                        strcpy(aCat[ctr].catFile, genFile);

                        printf(">> Category %s successfuly added.\n", aCat[ctr].catName);
                        printf(">> Access through %s.\n", aCat[ctr].catFile);

                        newFile = fopen(aCat[ctr].catFile, "w");
                        fclose(newFile);

                        ctr++;
                        *ncat = ctr;

                        changeFlag = 1;
                    }
                    else
                        printf(">> Category already exists.\n\n");
                }
                else
                    printf(">> Exiting...\n\n");
            }
            else
                printf(">> Limit reached.\n\n");
            break;
        }
        case 2:
        {
            if (*ncat > 0)
            {
                printCategories(aCat, *ncat, 1);

                printf("\nCategory to Delete -- ");
                getInput_int(&select2, 0, *ncat);

                if (select2 != 0)
                {
                    deleteCategory(aCat, ncat, select2 - 1);
                    remove(aCat[select2 - 1].catFile);

                    printf(">> %s successfully deleted.\n", aCat[select2 - 1].catName);

                    changeFlag = 1;
                }
                else
                    printf(">> Exiting...\n\n");
            }
            else
                printf(">> No existing categories.\n\n");
            
            break;
        }
        case 3:
        {
            if (*ncat > 0)
                printCategories(aCat, *ncat, 2);
            else
                printf("\n>> No categories yet.\n\n");
            break;
        }
        default:
        {
            printf(">> Exiting...\n\n");
            changeFlag = -1;
        }
    }

    return changeFlag;
}
