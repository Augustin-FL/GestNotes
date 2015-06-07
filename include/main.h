#ifndef HEADERS_INCLUS_MAIN

	#define HEADERS_INCLUS_MAIN
	#define VERSION "0.0.8-beta"
	
	#include <wx/wx.h>
	#include <wx/hyperlink.h>	// liens dans le about
	
	#include "bdd.h"
	
	class Frame_login;
	
	enum
	{
		PAS_CONNECTE=-1,
		ELEVE=0,
		PROF=1,
		ADMIN=2,
	};


	class App_GestNotes : public wxApp // correspond au "main"
	{
		public :
			virtual bool OnInit();
			virtual int OnExit();
		protected:
			connexion_bdd *bdd;
	};
	DECLARE_APP(App_GestNotes);

	class Frame_principale: public wxFrame
	{
		protected:
			connexion_bdd* bdd;
			int matricule;
			Frame_login *parent;
			wxMenu *menu_fichier, *menu_aide;

		public:
			Frame_principale(Frame_login *parent,int &matricule,connexion_bdd*& bdd);
			virtual void onClose(wxCloseEvent &evenement);
			virtual void onQuit(wxCommandEvent &evenement);
			virtual void onAbout(wxCommandEvent &evenement);
			virtual void onChangeMdp(wxCommandEvent &evenement);

	};

	

	class Frame_modifier_mdp : public wxDialog
	{

		public:
			Frame_modifier_mdp(Frame_principale*,connexion_bdd*&, int &matricule);
			~Frame_modifier_mdp(){}
			void onClick(wxCommandEvent& evenement);
			void onChange(wxCommandEvent& evenement);

		private:
			connexion_bdd* bdd;
			int matricule;
			wxTextCtrl *input_mdp, *input_mdp_confirmation;
			wxButton *bouton_valider;
			wxStaticText *message_mdp,*message_confirmation;

	};


	inline double arrondi(int precision, double nombre)//une fonction inline doit être définie dans le header
	{
		double partie_entiere,partie_decimale;

		if(precision==2)
		{
			partie_decimale = modf(nombre,&partie_entiere);

			if(partie_decimale >= 0.25 && partie_decimale <= 0.74) return (int)nombre + 0.5;
			else return ((int)nombre + (partie_decimale > 0.5));
		}

		modf(nombre*precision,&partie_entiere);

		return partie_entiere/precision;
	}
	
	
	#include "login.h"
	
#endif
