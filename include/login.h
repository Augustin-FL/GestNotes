#ifndef HEADERS_INCLUS_LOGIN
	#define HEADERS_INCLUS_LOGIN
	
	class Frame_login;
	
	#include <wx/wx.h>
	#include "bdd.h"
	
	class Frame_login;
	class Frame_admin;
	class Frame_prof;
	class Frame_principale;
	
	#include "main.h"

	
	class Frame_login : public wxFrame
	{
		public:
			Frame_login(connexion_bdd*& arg_bdd);
			virtual ~Frame_login(){};
			void onClick_annuler(wxCommandEvent &evenement);
			void onClose(wxCloseEvent &evenement);
		private:
			wxTextCtrl *input_login,*input_mdp;
			wxButton *bouton_valider, *bouton_annuler;
			connexion_bdd* bdd;
			int type;
			Frame_principale* frame_enfant;
			Frame_login* frame_actuelle;

			void onChange(wxCommandEvent&);
			void onClick_valider(wxCommandEvent&);

	};
	
	#include "eleve.h"
	#include "admin.h"
	#include "professeur.h"
	
#endif