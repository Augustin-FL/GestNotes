#ifndef HEADERS_INCLUS
	
	#define HEADERS_INCLUS
	
	#include <wx/wx.h>
	#include <wx/statline.h>
	#include <wx/stdpaths.h>
	#include <wx/hyperlink.h>
	
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
			void closeCursor();
			
			
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
			bool requete_en_cours;
			string requete_precedente;
			requete_sql* req;
			
		public:
			connexion_bdd();
			~connexion_bdd();
			int exec(const string &texte);
			requete_sql* prepare(const string &texte);
			int getColumn_int(int numero);
			string getColumn_text(int numero);
			double getColumn_float(int numero);
			void close();
		
	};
	
	
	class App_Gestnotes : public wxApp
	{
		public :	
			virtual bool OnInit();
			virtual int OnExit();
		protected:
			connexion_bdd *bdd;
	};
	DECLARE_APP(App_Gestnotes);
	
	
	class Frame_principale: public wxFrame
	{
		private:
			int type;
			int id, nombre_matiere;
			connexion_bdd* bdd;
			bool veto_autorise;

			wxRadioButton *input_radio_prof, *input_radio_admin,*input_radio_eleve;
			wxTextCtrl *input_ajout_nom, *input_ajout_prenom, *input_ajout_mdp, 
				*input_ajout_eleve__nom_responsable;
			wxStaticText*  label_ajouter_prof_matiere,
				*label_ajout_eleve__nom_responsable;
			wxComboBox *input_select_matiere_ajout;
			wxButton *bouton_valider_ajout_prof;
	
		public:
			Frame_principale(connexion_bdd*& arg_bdd);
			~Frame_principale(){};
			void afficher_apres_login(int type_arg, int id_arg);
			void onClose(wxCloseEvent &evenement);
			void onQuit(wxCommandEvent &evenement);
			void onClick_radio_ajout_prof(wxCommandEvent &evenement);
			void onChange_select_matiere(wxCommandEvent &evenement);
			void onClick_ajouter_prof(wxCommandEvent &evenement);
			void onAbout(wxCommandEvent &evenement);
			void main_admin();
			void main_eleve();
			void main_prof();
			
			
		
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