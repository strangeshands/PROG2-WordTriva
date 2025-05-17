// PROPERTY OF HEPHZI-BAH TOLENTINO //

#include "TOLENTINO-phases.c"

int
main()
{
    int menuSelect, adminSelect;
    int mainLoop;

    // --------- main variables ---------- //
    WordDetail aWordsList[MAX];
    int numElemAdmin;
    WordDetail gameWords[MAX];
    int numElemGame;

    // -------- admin phase --------- //
    accountDetail admins[MAX5];
    categoryDetail categories[MAX5];
    int numCategories, numAdmin;
    int adminDataFlag, accountFlag, activeAdminFlag, editCategoryFlag;
    int currAdmin;
    FILE *adminFile, *categoryFile;
    
    // -------- game phase --------- //
    int gameSelect, categorySelect, settingSelect;
    int playMode, playModeSelect;

    // initializing // 
    mainLoop = 0;
    adminDataFlag = 0; 
    accountFlag = 0;
    activeAdminFlag = 0;
    
    numCategories = 0;
    numElemAdmin = 0;
    numElemGame = 0;

    playMode = 1;

    while (!mainLoop)
    {
        printf("\n------------------------------------------------------------------------------------\n");
        printf("================================ WELCOME TO TRIVTER ================================\n");
        printf("------------------------------------------------------------------------------------\n\n");

        printf("                              >> [01] ADMIN PHASE <<\n");
        printf("                              >> [02] GAME PHASE  <<\n");
        printf("                              >> [00] EXIT        <<\n\n");
 
        getInput_int(&menuSelect, 0, 2);

        switch (menuSelect)
        {
            case 1:
            {
                // opening the admin database at first run //
                if (!adminDataFlag)
                {
                    adminFile = fopen("adminDatabase.txt", "r");

                    if (adminFile == NULL) //for safety measures
                        numAdmin = 0;
                    else
                        importAdmin(adminFile, admins, &numAdmin);

                    fclose(adminFile);
                    adminDataFlag = 1;  
                }
                // opening the admin database at first run //

                do {
                    printf("\n                     || ------ WELCOME TO ADMIN PHASE ------ ||\n\n");

                    printf("                             >> [01] Sign In          <<\n");
                    printf("                             >> [02] Make New Account <<\n");
                    printf("                             >> [03] Delete Admins    <<\n");
                    printf("                             >> [04] Guest            <<\n");
                    printf("                             >> [00] Back             <<\n\n");

                    getInput_int (&adminSelect, 0, 4);

                    if (adminSelect != 0 && adminSelect != 4)
                    {
                        accountFlag = BON_ADMIN(admins, &numAdmin, &currAdmin, adminSelect);

                        if (accountFlag == 2 || accountFlag == 3)
                        {
                            adminFile = fopen("adminDatabase.txt", "w");
                            exportAdmin(adminFile, admins, numAdmin);
                            fclose(adminFile);

                            adminDataFlag = 0;
                        }

                        if (accountFlag == 1 || accountFlag == 2)
                        {
                            adminSelect = 0;
                            printf(">> Signing in...\n\n");
                        }

                        if (accountFlag == 3)
                            accountFlag = 0;
                    }
                    else if (adminSelect == 4)
                    {
                        accountFlag = 3;
                        adminSelect = 0;
                    }
                    else if (adminSelect == 0)
                        printf(">> Exiting...\n");
                } while (adminSelect != 0);

                if (accountFlag >= 1 && accountFlag <= 3)
                {
                    activeAdminFlag = 1;

                    do {
                        printf("====================================================================================\n\n");

                        if (accountFlag != 3)
                            printf("-------------- >> WELCOME ADMIN %s <<\n\n", admins[currAdmin].username);
                        else
                            printf("-------------- >> WELCOME GUEST    <<\n\n");

                        printf("                     || ------ WELCOME TO ADMIN PHASE ------ ||\n\n");

                        printf("                            >> [01] Word Editor       <<\n");
                        printf("                            >> [02] Manage Categories <<\n");
                        printf("                            >> [00] Back/Log Out      <<\n\n");
                        getInput_int(&adminSelect, 0, 2);

                        if (adminSelect == 1)
                        {
                            printf("\n====================================================================================\n\n");
                            adminPhase(aWordsList, &numElemAdmin);
                        }
                        else if (adminSelect == 2)
                        {
                            do {
                                // initial reading of the categoryFile // 
                                categoryFile = fopen("categoryDatabase.txt", "r");

                                if (categoryFile != NULL) //for safety measures
                                    importCategory(categoryFile, categories, &numCategories);
                                else
                                    numCategories = 0;

                                fclose(categoryFile);
                                // initial reading of the categoryFile // 

                                editCategoryFlag = BON_CATEGORY(categories, &numCategories);

                                if (editCategoryFlag == 1)
                                {
                                    categoryFile = fopen("categoryDatabase.txt", "w");
                                    exportCategory(categoryFile, categories, numCategories); 
                                    fclose(categoryFile);
                                }
                            } while (editCategoryFlag != -1);
                        }
                        else
                        {
                            if (accountFlag != 3)
                                printf(">> Thank you %s! Signing out...\n", admins[currAdmin].username);
                            else
                                printf(">> Thank you GUEST! Signing out...\n");

                            activeAdminFlag = 0;
                            accountFlag = 0;
                        }
                    } while (activeAdminFlag);
                }

                break;
            }
            case 2:
            {
                do {
                    printf("\n                     || ------ WELCOME TO GAME PHASE ------ ||\n\n");
                    printf("                            >> [01] Start Game         <<\n");
                    printf("                            >> [02] Categorized Game   <<\n");
                    printf("                            >> [03] Game Settings      <<\n");
                    printf("                            >> [00] Back               <<\n\n");

                    getInput_int(&gameSelect, 0, 3);

                    switch (gameSelect)
                    {
                        case 1:
                        {
                            gamePhase(gameWords, &numElemGame, 0, categories, playMode);
                            break;
                        }
                        case 2:
                        {
                            // reading of the categoryFile // 
                            categoryFile = fopen("categoryDatabase.txt", "r");

                            if (categoryFile != NULL)
                                importCategory(categoryFile, categories, &numCategories);
                            else
                                numCategories = 0;

                            fclose(categoryFile);
                            // reading of the categoryFile // 

                            if (numCategories == 0)
                                printf("\n>> No categories available.\n\n");
                            else
                            {
                                printCategories(categories, numCategories, 1);
                                printf("\n");

                                getInput_int(&categorySelect, 0, numCategories);
                                fflush(stdin);

                                if (categorySelect != 0)
                                    gamePhase(gameWords, &numElemGame, categorySelect, categories, playMode);
                            }

                            break;
                        }
                        case 3:
                        {
                            do {
                                printf("\n                    || ------ WELCOME TO GAME SETTINGS ------ ||\n\n");
                                printf("                            >> [01] Player Mode        <<\n");
                                printf("                            >> [00] Back               <<\n\n");
                                getInput_int(&settingSelect, 0, 1);

                                switch (settingSelect)
                                {
                                    case 1:
                                    {
                                        printf("\n>> CURRENT MODE: %d player/s.\n\n", playMode);

                                        if (playMode == 1)
                                        {
                                            printf("[1] Set to 2 Players       [0] Back\n");
                                            getInput_int(&playModeSelect, 0, 1);

                                            if (playModeSelect == 1)
                                            {
                                                playMode = 2;
                                                printf("\n>> CURRENT MODE: %d player/s.\n", playMode);
                                            }
                                            else
                                                printf(">> Going back...\n");

                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("[1] Set to 1 Player        [0] Back\n");
                                            getInput_int(&playModeSelect, 0, 1);

                                            if (playModeSelect == 1)
                                            {
                                                playMode = 1;
                                                printf("\n>> CURRENT MODE: %d player/s.\n", playMode);
                                            }
                                            else
                                                printf(">> Going back...\n");

                                            printf("\n");
                                        }

                                        break;
                                    }
                                    case 0:
                                        printf(">> Going back...\n\n");
                                }
                            } while (settingSelect != 0);

                            break;
                        }
                        default:
                            printf(">> Exiting...\n\n");
                    }
                } while (gameSelect != 0);
                break;
            }
            default:
            {
                printf("\n------------------------------ Thank you for playing! ------------------------------\n");
                mainLoop = 1;
            }
        }
    }
    return 0;
}
