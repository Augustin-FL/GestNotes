#ifndef HEADERS_INCLUS
	
	#define HEADERS_INCLUS
	#include <iostream>
	#include <cstdarg> //arguments variables : pour la connexion SQL
	
	#include <wx/wx.h>
	#include <wx/statline.h>
	#include <SQLite/sqlite3.h>

	using namespace std;

	enum 
	{
		ELEVE=0,
		PROF=1,
		ADMIN=2,
		
	};

	class requete_prepare
	{
		public:
			requete_prepare(sqlite3 *&bdd,const string& texte);
			int bind(const char *cle,const char *valeur);
			int bind(char *cle,int valeur);
			int bind(int cle,int valeur); 
			int bind(int cle,char* valeur);
			int fetch();
			int getColumn_int(int numero);
			char *getColumn_text(int numero);
			double getColumn_float(int numero);
			
		private:
			sqlite3_stmt* requete;
			sqlite3* bdd_private;
			int* types;
			int nb_colonnes;
	};
	 
	class connexion_bdd
	{
		private:
			sqlite3* bdd;
			
		public:
			connexion_bdd();
			~connexion_bdd();
			int exec(const string texte);
			requete_prepare* prepare(const string texte);
		
	};
	
	
	class App_GestNote : public wxApp
	{
		public :	
			virtual bool OnInit();
			
		protected:
			connexion_bdd *bdd;
	};
	DECLARE_APP(App_GestNote);
	

	class Frame_login : public wxFrame
	{
		public:
			Frame_login(connexion_bdd*& arg_bdd);
			virtual ~Frame_login(){};
		
		private:
			wxTextCtrl *input_login,*input_mdp;
			wxButton *bouton_valider, *bouton_annuler;
			connexion_bdd* bdd;
			
			void onClick_valider(wxCommandEvent &evenement);
			void onClick_annuler(wxCommandEvent &evenement);
			void onChange(wxCommandEvent &evenement);
	};

#endif