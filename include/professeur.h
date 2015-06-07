#ifndef HEADERS_INCLUS_PROFESSEUR
	#define HEADERS_INCLUS_PROFESSEUR
	
	#include <map>
	#include <wx/wx.h>
	#include <wx/dataview.h>
	#include "main.h"
	#include "bdd.h"


	
	class Frame_prof : public Frame_principale
	{
		public:
			Frame_prof(Frame_login* parent,int &matricule,connexion_bdd*& bdd);
			~Frame_prof(){}
			void onDbclick_notes(wxDataViewEvent &evenement);
			void onChange_notes(wxDataViewEvent &evenement);
			void onChange_commentaires(int id_eleve);
			void preparer_matieres_classes();
			void onChange_matiere(wxCommandEvent &evenement);
			void onChange_classe(wxCommandEvent &evenement);
			void afficher_liste();
			void onEditer_Groupe(wxCommandEvent &evenement);

		private:

			wxDataViewListCtrl   *liste_notes;
			std::map<int,int> liste_eleves;
			int id_matiere_en_cours,id_classe_en_cours, arrondi_affichage_notes;
			bool notes_hors_bareme;
			wxChoice  *liste_matieres,*liste_classes;
			std::map<int,wxString> choix_matieres, choix_classes;
			wxButton *boutons_groupes;
			wxDataViewCellMode autoriser_edition;
	};
	
	
	class Frame_editer_groupes : public wxDialog
	{
		public:
			Frame_editer_groupes(wxWindow* parent_arg,connexion_bdd*& bdd_arg, int classe_arg);
			~Frame_editer_groupes(){}
			void onClick(wxCommandEvent&);
			void afficher_liste(bool detacher=false);

		private:
			connexion_bdd* bdd;
			wxWindow* parent;
			int classe;
			std::map<wxButton*,int> correspondance;
			wxScrolledWindow* fenetre;
			wxGridSizer		*grille;
	};
#endif