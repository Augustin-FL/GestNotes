#ifndef HEADERS_INCLUS_AJOUT_MODIFICATION_MEMBRE
	#define HEADERS_INCLUS_AJOUT_MODIFICATION_MEMBRE
	
	#include <wx/wx.h>
	#include <wx/statline.h>	// Ajout d'un membre :séparations
	#include "validateurs.h"
	#include "main.h"
	
	class Frame_ajout_modification_membre : public wxDialog
	{
		public:
			Frame_ajout_modification_membre(wxWindow* parent_arg,connexion_bdd*& bdd,int matricule_arg=-1,int matiere_arg=-1, int classe_arg=-1);
			void onClick_radio(wxCommandEvent &evenement);
			void onChange_select(wxCommandEvent &evenement);
			void onClick(wxCommandEvent &evenement);
			void remplir_champs();
			bool valider();
			int getAncienType();
			int valider_ajouter_login_centralise();
			void supprimer_prof(int,int,int);
			void supprimer_eleve(int id,int classe);


		private:
			int matricule, nombre_matiere,classe, matiere;
			connexion_bdd* bdd;
			wxFrame* parent;
			wxArrayString texte_select,texte_classes;

			wxRadioButton *input_radio_prof;
			wxRadioButton *input_radio_eleve;
			wxRadioButton *input_radio_admin;
			wxRadioButton *input_radio_matricule_oui;
			wxRadioButton *input_radio_matricule_non;

				wxTextCtrl *input_ajout_nom, *input_ajout_prenom, *input_ajout_mdp,
						*input_ajout_eleve__nom_responsable,
						*input_ajout_eleve__prenom_responsable,
						*input_ajout_eleve__tel_responsable,
						*input_ajout_eleve__mail_responsable,
						*input_ajout_eleve__rue,
						*input_ajout_eleve__num_rue,
						*input_ajout_eleve__code_postal,
						*input_ajout_eleve__ville,
						*input_ajout_eleve__tel_mobile,
						*input_ajout_matricule;

			wxStaticText*  label_ajouter_prof__matiere,
						*label_ajout_eleve__nom_responsable,
						*label_ajout_eleve__prenom_responsable,
						*label_ajout_eleve__tel_responsable,
						*label_ajout_eleve__mail_responsable,
						*label_ajout_eleve__sexe,
						*label_ajout_eleve__rue,
						*label_ajout_eleve__num_rue,
						*label_ajout_eleve__code_postal,
						*label_ajout_eleve__ville,
						*label_ajout_eleve__tel_mobile,
						*label_ajout_eleve__groupe,
						*label_ajout_eleve__classe;

			wxChoice *input_ajout_eleve__sexe,
					 *input_ajout_eleve__groupe;

			wxComboBox *input_select_matiere_ajout,
					   *input_ajout_eleve__classe;

			wxButton *bouton_valider_ajout;
			Frame_principale* frame_parente;
	};
#endif