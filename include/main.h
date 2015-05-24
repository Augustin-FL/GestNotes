#ifndef HEADERS_INCLUS

	#define HEADERS_INCLUS
	#include <map>
	
	#include <wx/wx.h>
	#include <wx/statline.h>
	#include <wx/stdpaths.h>
	#include <wx/hyperlink.h>
	#include <wx/regex.h>
	#include <wx/filename.h>
	#include <wx/listctrl.h>
	#include <wx/dataview.h>
	#include <wx/notebook.h>
	#include <wx/srchctrl.h>
	

	#include <SQLite/sqlite3.h>
	
	#define VERSION "0.0.6-alpha"

	using namespace std;
	
	class requete_sql;
	class connexion_bdd;
	class App_GestNotes;
	
	class Frame_principale;
	class Frame_admin;
	class Frame_ajout_modification_membre;
	class Frame_login;
	class wxTextRegexpValidator;
	class wxComboBoxValidator;
	class Afficher_liste_membres;

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
			int bind(const string &cle,double valeur);
			int bind(int cle,int valeur);
			int bind(int cle,const string &valeur);
			int bind(int cle,double valeur);
			
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

	
	
		
	class wxTextRegexpValidator : public wxTextValidator//Classe permettant un wxValidator via regexp
	{
		protected:
		   wxRegEx m_regEx;
		   wxString m_regexp_texte;
		   

		public:
		   wxTextRegexpValidator(wxString regexp, wxString* valeur = NULL);
		   ~wxTextRegexpValidator(){}

		   wxObject* Clone() const;

		   virtual bool TransferToWindow();
		   virtual bool TransferFromWindow();
	};
	
		
	class wxComboBoxValidator : public wxValidator//Classe permettant un wxValidator via regexp
	{
		protected:
		    wxString* m_pointeur;

		public:
		   wxComboBoxValidator(wxString* valeur=NULL);
		   ~wxComboBoxValidator(){}

		   wxObject* Clone() const;

		   virtual bool TransferToWindow();
		   virtual bool TransferFromWindow();
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

	class Frame_ajout_modification_membre : public wxDialog
	{
		public:
			Frame_ajout_modification_membre(wxWindow* parent_arg,connexion_bdd*& bdd,int matricule_arg=-1,int matiere_arg=-1, int classe_arg=-1);
			void onClick_radio(wxCommandEvent &evenement);
			void onChange_select(wxCommandEvent &evenement);
			void onClick(wxCommandEvent &evenement);
			void remplir_champs();
			bool valider();
			void Supprimer_ancien_membre();
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
			
		private:
			
			wxDataViewListCtrl   *liste_notes;
			std::map<int,int> liste_eleves;
			int id_matiere_en_cours,id_classe_en_cours, arrondi_affichage_notes;
			bool notes_hors_bareme;
			wxChoice  *liste_matieres,*liste_classes;
			std::map<int,wxString> choix_matieres;
			std::map<int,wxString> choix_classes;
	
	
		
	};
	
	class Frame_eleve: public Frame_principale
	{
		public:
			Frame_eleve(Frame_login* parent,int &matricule,connexion_bdd*& bdd);
			void OnClick_modifier(wxCommandEvent &evenement);
			void OnClick_imprimer_buletin(wxCommandEvent &evenement);
			
			
		private:
			wxButton *bouton_modifier,*bouton_imprimer_buletin;
		
	};

	class Frame_admin : public Frame_principale
	{
		private:
			wxCheckBox *input_checkbox__notes_hors_bareme,
					   *input_checkbox__afficher_buletins;
					   
			wxRadioButton *input_radio__arrondi_cent,
						  *input_radio__arrondi_dix,
						  *input_radio__arrondi_demi,
						  *input_radio__arrondi_un;
			Afficher_liste_membres *liste_membres;
			
		public:
			Frame_admin(Frame_login* parent,int &matricule,connexion_bdd*& bdd);
			void onAjouter(wxCommandEvent &evenement);
			void onCheck_Buletins(wxCommandEvent &evenement);
			void onSupprimer(wxCommandEvent &evenement);
			void onModifier(wxCommandEvent &evenement);
			void onClick_hors_bareme(wxCommandEvent &evenement);
			void onChange_arrondi(wxCommandEvent &evenement);
			void onModifier_id_selectionne(wxListEvent &evenement);
			void onSupprimer_id_selectionne(wxListEvent &evenement);
			void onAfficherMembres(wxCommandEvent &evenement);
			void supprimer_eleve(int,int);
			void supprimer_prof(int,int,int);
	};

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
	
	
	class Afficher_liste_membres : public wxFrame
	{
		public:
			Afficher_liste_membres(Frame_principale*,connexion_bdd*&, int);
			~Afficher_liste_membres(){};
			void afficher_liste(wxCommandEvent &evenement);
			void onChange_onglet(wxCommandEvent &evenement);
			void onClose(wxCloseEvent &evenement);
			bool ongletProfs_selected();
			bool ongletEleves_selected();
			wxListCtrl* getListCtrl();
			void changer_onglet(wxCommandEvent &evenement);
			void changer_ordre(wxListEvent &evenement);
			
			
		private:
			connexion_bdd* bdd;
			Frame_principale* parent;
			
			wxNotebook* onglets;
			wxSearchCtrl *rechercher;
			wxListCtrl *liste_eleves,*liste_profs,*liste_admins;
			int acces, ordre_colonne1,ordre_colonne2,ordre_colonne3,ordre_colonne4;
			
	};
	
	inline double arrondi(int precision, double nombre)//une fonction inline doit être définie dans le header
	{
		double partie_entiere,partie_decimale;
		
		if(precision==2) 
		{
			partie_decimale = modf(nombre,&partie_entiere);
		 
			if(partie_decimale >= 0.25 && partie_decimale <= 0.74) return  (int)nombre + 0.5;
			else return ((int)nombre + (partie_decimale > 0.5));
		}
		
		modf(nombre*precision,&partie_entiere);
		
		return partie_entiere/precision;
	}


#endif
