#ifndef HEADERS_INCLUS_AFFICHER_LISTE_MEMBRES
	#define HEADERS_INCLUS_AFFICHER_LISTE_MEMBRES
	
	#include <wx/wx.h>
	#include <wx/srchctrl.h>	//listing des membres : champ de recherche
	#include <wx/notebook.h> 	//listing des membres : onglets
	#include <wx/listctrl.h> 	//listcrl et dataviewListCtrl
	#include "main.h"
	#include "admin.h"
	

	
	class Frame_afficher_liste_membres : public wxFrame
	{
		public:
			Frame_afficher_liste_membres(Frame_principale*,connexion_bdd*&, int);
			~Frame_afficher_liste_membres(){};
			void afficher_liste(wxCommandEvent &evenement);
			void onChange_onglet(wxCommandEvent &evenement);
			void onClose(wxCloseEvent &evenement);
			bool ongletProfs_selected();
			bool ongletEleves_selected();
			wxListCtrl* getListCtrl();
			void changer_onglet(wxCommandEvent &evenement);
			void changer_ordre(wxListEvent &evenement);
			void Ajouter_curseur(int,bool);


		private:
			connexion_bdd* bdd;
			Frame_principale* parent;

			wxNotebook* onglets;
			wxSearchCtrl *rechercher;
			wxListCtrl *liste_eleves,*liste_profs,*liste_admins;
			int acces, ordre_colonne1,ordre_colonne2,ordre_colonne3,ordre_colonne4;

	};
#endif