#include <stdlib.h>
#include <stdio.h>
#include "client.h"

int main() {
    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");
    envoyer("login 12305101 GAUDRY");


    envoyer("load challenge");

    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}