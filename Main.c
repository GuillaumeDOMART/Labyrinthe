#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <unistd.h>

#include "Labyrinthe.h"
#include "Paramètres.h"
#include "Affichage.h"

int main(int argc, char * argv[]){
    Parametres * param = NULL;
    laby_t labyrinthe;
    MLV_Keyboard_button touche;
    int pion_x, pion_y;
    int choix_menu;
    /*MLV_Image* image;*/

    pion_x = 0;
    pion_y = 0;

    /*Gestion des paramètres*/
    param = initialise_param();

    /*Le labyrinthe sera toujours différent*/
    srand(time(NULL));

    MLV_create_window("Labyrinthe", "Labyrinthe", 1000, 1000);

    while(1){
        choix_menu = affiche_menu();

        if(choix_menu == 0)
            return 0;

        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_actualise_window();

        /*Arrêt du programme si problème lors de l'initialisation du labyrinthe*/
        if(!initialiser_tab(&labyrinthe.cases, *param)){
            return 1;
        }

        /*initialisation des paramètres du labyrinthe*/
        labyrinthe.taille.x = param->taille[1];
        labyrinthe.taille.y = param->taille[0];
        labyrinthe.classes = labyrinthe.taille.x * labyrinthe.taille.y;

        prepare_labyrinthe(&labyrinthe, *param);

        if(choix_menu == 2){
            affichage_graph(labyrinthe);
            MLV_wait_keyboard(&touche, NULL, NULL);

            while(!verification(labyrinthe, 20, 20)){
                MLV_clear_window(MLV_COLOR_BLACK);
                MLV_actualise_window();
                affichage_3D(labyrinthe, pion_x, pion_y, 0);
                MLV_wait_keyboard(&touche, NULL, NULL);

                if((touche == 273) && ((pion_x + 1) < 20) && (labyrinthe.cases[pion_y][pion_x].murEst == 0)){
                    labyrinthe.cases[pion_y][pion_x].presence = 0;
                    labyrinthe.cases[pion_y][pion_x + 1].presence = 1;
                    pion_x += 1;
                }

                if((touche == 274) && ((pion_x - 1) >= 0) && (labyrinthe.cases[pion_y][pion_x - 1].murEst == 0)){
                    labyrinthe.cases[pion_y][pion_x].presence = 0;
                    labyrinthe.cases[pion_y][pion_x - 1].presence = 1;
                    pion_x -= 1;
                }

                if((touche == 275) && ((pion_y + 1) < 20) && (labyrinthe.cases[pion_y][pion_x].murSud == 0)){
                    labyrinthe.cases[pion_y][pion_x].presence = 0;
                    labyrinthe.cases[pion_y + 1][pion_x].presence = 1;
                    pion_y += 1;
                }

                if((touche == 276) && ((pion_y - 1) >= 0) && (labyrinthe.cases[pion_y - 1][pion_x].murSud == 0)){
                    labyrinthe.cases[pion_y][pion_x].presence = 0;
                    labyrinthe.cases[pion_y - 1][pion_x].presence = 1;
                    pion_y -= 1;
                }
            }
            affichage_3D(labyrinthe, pion_x, pion_y, 0);
            MLV_wait_keyboard(&touche, NULL, NULL);
            /*free_lab(&labyrinthe, *param);*/

        }
        else{

            /*affichage du labyrinthe final / valide*/
            affichage_graph(labyrinthe);
            affiche_pion(labyrinthe);


            while(!verification(labyrinthe, 20, 20)){
                MLV_wait_keyboard(&touche, NULL, NULL);

                if((touche == 275) && ((pion_y + 1) < 20) && (labyrinthe.cases[pion_x][pion_y].murEst == 0)){
                    labyrinthe.cases[pion_x][pion_y].presence = 0;
                    labyrinthe.cases[pion_x][pion_y + 1].presence = 1;
                    pion_y += 1;
                }

                if((touche == 276) && ((pion_y - 1) >= 0) && (labyrinthe.cases[pion_x][pion_y - 1].murEst == 0)){
                    labyrinthe.cases[pion_x][pion_y].presence = 0;
                    labyrinthe.cases[pion_x][pion_y - 1].presence = 1;
                    pion_y -= 1;
                }

                if((touche == 274) && ((pion_x + 1) < 20) && (labyrinthe.cases[pion_x][pion_y].murSud == 0)){
                    labyrinthe.cases[pion_x][pion_y].presence = 0;
                    labyrinthe.cases[pion_x + 1][pion_y].presence = 1;
                    pion_x += 1;
                }

                if((touche == 273) && ((pion_x - 1) >= 0) && (labyrinthe.cases[pion_x - 1][pion_y].murSud == 0)){
                    labyrinthe.cases[pion_x][pion_y].presence = 0;
                    labyrinthe.cases[pion_x - 1][pion_y].presence = 1;
                    pion_x -= 1;
                }
                MLV_clear_window(MLV_COLOR_BLACK);
                affichage_graph(labyrinthe);
                affiche_pion(labyrinthe);
            }
            affiche_pion_final(labyrinthe);
            free_lab(&labyrinthe);

        }

        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_actualise_window();
        pion_x = 0;
        pion_y = 0;

    }

    free(param);

    MLV_free_window();

    return 0;
}
