#include "include.h"

SDL_Surface *temp = NULL;
SDL_Surface *my_poke[6];

/*typedef struct
{
  char nom[25];
  int x;
	int y;
  int PV;
}Info;*/

void combat(SDL_Surface *ecran)
{
	SDL_Surface *fond_combat = NULL, *attaque1 = NULL, *attaque2 = NULL, *rect = NULL, *texte_attaques = NULL, *texte_fuite = NULL, *texte_changer = NULL, *fond_noir = NULL;
	SDL_Event event;
	SDL_Rect pos_fond, pos_fond_noir, pos_attaque, pos_attaque2, pos_rect, pos_texte_attaques, pos_texte_fuite, pos_texte_changer, pos_pokemon, pos_mypoke;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0}, couleurRouge = {255, 27, 27};
	int continuer = 1, bouton = 1;
	int longueur = 125, hauteur = 20, longueur2 = 70, longueur3 = 105;
	int i;

	pos_mypoke.x = 280;
	pos_mypoke.y = 300;
	pos_fond.x = 244;
	pos_fond.y = 87;
	pos_fond_noir.x = 0;
	pos_fond_noir.y = 0;
	pos_attaque.x = 472;
	pos_attaque.y = 169;
	pos_rect.x = 709;
	pos_rect.y = 487;
	pos_texte_attaques.x = 734;
	pos_texte_attaques.y = 505;
	pos_texte_fuite.x = 734;
	pos_texte_fuite.y = 535;
	pos_texte_changer.x = 734;
	pos_texte_changer.y = 565;
	pos_pokemon.x = 4;
	pos_pokemon.y = 5;

	police = TTF_OpenFont("combat/king.ttf", 25);
	fond_combat = IMG_Load("combat/plateau_combat.png");
	fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
	rect = IMG_Load("combat/rect_attaque.png");
	texte_attaques = TTF_RenderText_Blended(police, "Attaques", couleurNoire);
	texte_fuite = TTF_RenderText_Blended(police, "Fuite", couleurNoire);
	texte_changer = TTF_RenderText_Blended(police, "Changer", couleurNoire);

	SDL_FillRect(fond_noir,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(fond_noir,NULL,ecran,&pos_fond_noir);

	SDL_BlitSurface(fond_combat, NULL, ecran, &pos_fond);
	SDL_Flip(ecran);
	SDL_Delay(500);

	poke_alea(ecran);
	SDL_Flip(ecran);
	SDL_Delay(500);

	my_pokemons(ecran);
	SDL_BlitSurface(my_poke[0], NULL, ecran, &pos_mypoke);
	SDL_Flip(ecran);
	SDL_Delay(500);

	SDL_BlitSurface(rect, NULL, ecran, &pos_rect);
	SDL_BlitSurface(texte_attaques, NULL, ecran, &pos_texte_attaques);
	SDL_BlitSurface(texte_fuite, NULL, ecran, &pos_texte_fuite);
	SDL_BlitSurface(texte_changer, NULL, ecran, &pos_texte_changer);
	SDL_Flip(ecran);

	while(continuer) //Boucle infini qui s'arrête lorsque continuer = 0
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT: //quitte le programme lorsque l'on appui sur la croix rouge
				continuer = 0;
			break;

			case SDL_KEYDOWN: //appuyer sur une touche du clavier
				switch (event.key.keysym.sym) //évènement concernant les touches du clavier
				{
					case SDLK_ESCAPE: // Appuyer sur échap pour retourner au menu
						menu(ecran);
						continuer = 0;
					break;
				}
			break;

			case SDL_MOUSEMOTION: //déplacement de la souris
				if(bouton)
				{
					if ((pos_texte_attaques.x <= event.button.x) && ((pos_texte_attaques.x + longueur) >= event.button.x) && (pos_texte_attaques.y <= event.button.y) && (pos_texte_attaques.y + hauteur >= event.button.y))
					{
						texte_attaques = TTF_RenderText_Blended(police, "Attaques", couleurRouge);
					}
					else
					{
						texte_attaques = TTF_RenderText_Blended(police, "Attaques", couleurNoire);
					}
					if ((pos_texte_fuite.x <= event.button.x) && ((pos_texte_fuite.x + longueur2) >= event.button.x) && (pos_texte_fuite.y <= event.button.y) && (pos_texte_fuite.y + hauteur >= event.button.y))
					{
						texte_fuite = TTF_RenderText_Blended(police, "Fuite", couleurRouge);
					}
					else
					{
						texte_fuite = TTF_RenderText_Blended(police, "Fuite", couleurNoire);
					}
					if ((pos_texte_changer.x <= event.button.x) && ((pos_texte_changer.x + longueur3) >= event.button.x) && (pos_texte_changer.y <= event.button.y) && (pos_texte_changer.y + hauteur >= event.button.y))
					{
						texte_changer = TTF_RenderText_Blended(police, "Changer", couleurRouge);
					}
					else
					{
						texte_changer = TTF_RenderText_Blended(police, "Changer", couleurNoire);
					}
					SDL_BlitSurface(rect, NULL, ecran, &pos_rect);
					SDL_BlitSurface(texte_attaques, NULL, ecran, &pos_texte_attaques);
					SDL_BlitSurface(texte_fuite, NULL, ecran, &pos_texte_fuite);
					SDL_BlitSurface(texte_changer, NULL, ecran, &pos_texte_changer);
				}
			break;

			case SDL_MOUSEBUTTONDOWN: //clic gauche de la souris
				if (event.button.button == SDL_BUTTON_LEFT) //clic gauche
				{
					if ((pos_texte_attaques.x <= event.button.x) && ((pos_texte_attaques.x + longueur) >= event.button.x) && (pos_texte_attaques.y <= event.button.y) && (pos_texte_attaques.y + hauteur >= event.button.y))
					{
						bouton = 0;
						SDL_BlitSurface(fond_combat, NULL, ecran, &pos_fond);
					}

					if ((pos_texte_fuite.x <= event.button.x) && ((pos_texte_fuite.x + longueur2) >= event.button.x) && (pos_texte_fuite.y <= event.button.y) && (pos_texte_fuite.y + hauteur >= event.button.y))
					{
						continuer = 0;
					}

					if ((pos_texte_changer.x <= event.button.x) && ((pos_texte_changer.x + longueur3) >= event.button.x) && (pos_texte_changer.y <= event.button.y) && (pos_texte_changer.y + hauteur >= event.button.y))
					{
						changer_poke(ecran);
						bouton = 0;
					}
				}
			break;
		}
			SDL_Flip(ecran);
	}

	SDL_FreeSurface(fond_combat);
	SDL_FreeSurface(fond_noir);
	SDL_FreeSurface(attaque1);
	SDL_FreeSurface(rect);
	SDL_FreeSurface(texte_attaques);
	SDL_FreeSurface(texte_fuite);
	SDL_FreeSurface(texte_changer);
	TTF_CloseFont(police);
}

SDL_Surface *poke[16];

void poke_alea(SDL_Surface *ecran)
{
	//Info pokemon[20] = {"", 0, 0, 0};
	SDL_Rect pos_poke;

	//pokemon[0].nom = "BULBIZARRE";

  //pokemon[0].x = 700;
//  pokemon[0].y = 55;
	pos_poke.x = 700;
	pos_poke.y = 55;

    srand(time(NULL));
    int alea = 0;

    poke[0] = IMG_Load("sprites/poke/01.png");
    poke[1] = IMG_Load("sprites/poke/04.png");
    poke[2] = IMG_Load("sprites/poke/07.png");
    poke[3] = IMG_Load("sprites/poke/10.png");
    poke[4] = IMG_Load("sprites/poke/13.png");
    poke[5] = IMG_Load("sprites/poke/16.png");
    poke[6] = IMG_Load("sprites/poke/19.png");
    poke[7] = IMG_Load("sprites/poke/21.png");
    poke[8] = IMG_Load("sprites/poke/23.png");
    poke[9] = IMG_Load("sprites/poke/25.png");
    poke[10] = IMG_Load("sprites/poke/27.png");
    poke[11] = IMG_Load("sprites/poke/29.png");
    poke[12] = IMG_Load("sprites/poke/32.png");
    poke[13] = IMG_Load("sprites/poke/35.png");
    poke[14] = IMG_Load("sprites/poke/37.png");
    poke[15] = IMG_Load("sprites/poke/39.png");


          alea = rand()%16;
					temp = poke[alea];
					SDL_BlitSurface(poke[alea], NULL, ecran, &pos_poke);
}


void my_pokemons(SDL_Surface *ecran)
{
	my_poke[0] = IMG_Load("sprites/poke/dos/01.png");
	my_poke[1] = IMG_Load("sprites/poke/dos/04.png");
	my_poke[2] = IMG_Load("sprites/poke/dos/07.png");
	my_poke[3] = IMG_Load("sprites/poke/dos/10.png");
	my_poke[4] = IMG_Load("sprites/poke/dos/13.png");
	my_poke[5] = IMG_Load("sprites/poke/dos/16.png");
}

void changer_poke(SDL_Surface *ecran)
{
		SDL_Surface *changer = NULL;
		SDL_Rect pos_fond;

		pos_fond.x = 244;
		pos_fond.y = 87;
		changer = IMG_Load("combat/fond_combat.png");
		//SDL_FillRect(changer,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(changer, NULL, ecran, &pos_fond);
		SDL_Flip(ecran);

}
//salameche, carapuce, chenipan, aspicot, roucool, ratata, piafabec, abo;
