#ifndef HEADERS_INCLUS_ADMIN
	#define HEADERS_INCLUS_ADMIN
	
	#include <map>
	#include <wx/wx.h>
	#include <wx/listctrl.h> 	//listcrl et dataviewListCtrl
	#include <wx/dataview.h> 	//dataviewEvent
	#include "main.h"
	#include "afficher_liste_membres.h"
	#include "ajout_modification_membre.h"
	
	class Frame_afficher_liste_membres;
	
	class Frame_admin : public Frame_principale
	{
		public:
			Frame_admin(Frame_login* parent,int &matricule,connexion_bdd*& bdd);
			void onAjouter(wxCommandEvent &evenement);
			void onCheck_Buletins(wxCommandEvent &evenement);
			void onCheck_Modif_notes(wxCommandEvent &evenement);
			void onSupprimer(wxCommandEvent &evenement);
			void onModifier(wxCommandEvent &evenement);
			void onClick_hors_bareme(wxCommandEvent &evenement);
			void onChange_arrondi(wxCommandEvent &evenement);
			void onModifier_id_selectionne(wxListEvent &evenement);
			void onSupprimer_id_selectionne(wxListEvent &evenement);
			void onAfficherMembres(wxCommandEvent &evenement);
			void supprimer_eleve(int,int);
			void supprimer_prof(int,int,int);
			void onChanger_ordre(wxDataViewEvent &evenement);
			void Afficher_liste(wxDataViewEvent &evenement);
			void onChange_commentaires(wxDataViewEvent &evenement);
			void Ajouter_curseur(int colonne, bool haut);
			void onDbclick_commentaires(wxDataViewEvent &evenement);


		private:
			wxCheckBox *input_checkbox__notes_hors_bareme,
					   *input_checkbox__afficher_buletins,
					   *input_checkbox__autoriser_modif_notes;

			wxRadioButton *input_radio__arrondi_cent,
						  *input_radio__arrondi_dix,
						  *input_radio__arrondi_demi,
						  *input_radio__arrondi_un;
			Frame_afficher_liste_membres *liste_membres;
			wxDataViewListCtrl *liste_appreciations;

			int ordre_colonne1,ordre_colonne2,ordre_colonne3,ordre_colonne4;

	};
	
#endif