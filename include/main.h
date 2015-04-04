#ifndef HEADERS_INCLUS
	
	#define HEADERS_INCLUS
	
	#include <wx/wx.h>
	#include <wx/statline.h>
	#include <wx/stdpaths.h>
	#include <wx/hyperlink.h>
	#include <wx/filename.h>
	#include <iostream>
	
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
	
	
	class App_GestNotes : public wxApp
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
		private:
			int type;
			int id, nombre_matiere;
			connexion_bdd* bdd;
			bool veto_autorise;
	
		public:
			Frame_principale(connexion_bdd*& arg_bdd);
			~Frame_principale(){};
			void afficher_apres_login(int type_arg, int id_arg);
			void onClose(wxCloseEvent &evenement);
			void onQuit(wxCommandEvent &evenement);
			void onAbout(wxCommandEvent &evenement);
	};
	
	class Frame_admin : public wxEvtHandler
	{
		private:
			int id, nombre_matiere;
			connexion_bdd* bdd;
			bool veto_autorise;
				
				
			wxRadioButton 	*input_radio_prof,
							*input_radio_admin,
							*input_radio_eleve,
							*input_radio_matricule_oui,
							*input_radio_matricule_non;
							
				wxTextCtrl *input_ajout_nom, *input_ajout_prenom, *input_ajout_mdp, 
						*input_ajout_eleve__nom_responsable,
						*input_ajout_eleve__prenom_responsable,
						*input_ajout_eleve__tel_responsable,
						*input_ajout_eleve__mail_responsable,
						*input_ajout_eleve__nom_rue,
						*input_ajout_eleve__rue,
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
						*label_ajout_eleve__nom_rue,
						*label_ajout_eleve__rue,
						*label_ajout_eleve__code_postal,
						*label_ajout_eleve__ville,
						*label_ajout_eleve__tel_mobile,
						*label_ajout_eleve__groupe;
			
			wxChoice *input_ajout_eleve__sexe,
					 *input_ajout_eleve__groupe;
			
			wxComboBox *input_select_matiere_ajout;
			
			wxButton *bouton_valider_ajout;
			wxArrayString texte_select;
			Frame_principale* frame_parente;
			
		public:
			Frame_admin(Frame_principale* parent, connexion_bdd*& arg_bdd,int &id_arg);
			
			void onAjouter(wxCommandEvent &evenement);
			void onClick_radio_ajout(wxCommandEvent &evenement);
			void onChange_select_matiere(wxCommandEvent &evenement);
			void onClick_ajouter(wxCommandEvent &evenement);	
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