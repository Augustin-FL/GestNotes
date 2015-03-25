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
		PAS_CONNECTE=-1,
		ELEVE=0,
		PROF=1,
		ADMIN=2,
		
	};

	class requete_sql : public wxString //connexion a la BDD
	{
		public:
			requete_sql(sqlite3 *&bdd,const string& texte);
			int bind(const string &cle,const string &valeur);
			int bind(const string &cle,int valeur);
			int bind(int cle,int valeur); 
			int bind(int cle,const string &valeur);
			int fetch();
			int getColumn_int(int numero);
			string getColumn_text(int numero);
			double getColumn_float(int numero);
			
		private:
			sqlite3_stmt* requete;
			sqlite3* bdd_private;
			int* types;
			int nb_colonnes;
	};
	class connexion_bdd : public wxString
	{
		private:
			sqlite3* bdd;
			
		public:
			connexion_bdd();
			~connexion_bdd();
			requete_sql* exec(const string &texte);
			requete_sql* prepare(const string &texte);
		
	};
	
	
	class App_GestNote : public wxApp
	{
		public :	
			virtual bool OnInit();
			
		protected:
			connexion_bdd *bdd;
	};
	DECLARE_APP(App_GestNote);
	
	
	class Frame_principale: public wxFrame
	{
		private:
			int type;
			int id;
			connexion_bdd* bdd;
			bool veto_autorise;

		public:
			Frame_principale(connexion_bdd*& arg_bdd);
			~Frame_principale(){};
			void afficher_apres_login(int type_arg, int id_arg);
			void onClose(wxCloseEvent &evenement);
			void main_admin();
			void main_eleve();
			void main_prof();
			void onQuit(wxCommandEvent &evenement);
			
		
	};

	class Frame_login : public wxFrame
	{
		public:
			Frame_login(Frame_principale*& parent, connexion_bdd*& arg_bdd);
			virtual ~Frame_login(){};
		
		private:
			wxTextCtrl *input_login,*input_mdp;
			wxButton *bouton_valider, *bouton_annuler;
			connexion_bdd* bdd;
			int type;
			Frame_principale* frame_parente;
			
			void onClick_valider(wxCommandEvent &evenement);
			void onClick_annuler(wxCommandEvent &evenement);
			void onChange(wxCommandEvent &evenement);
			void onClose(wxCloseEvent &evenement);
	};

#endif