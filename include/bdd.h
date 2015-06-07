#ifndef HEADERS_INCLUS_BDD
	#define HEADERS_INCLUS_BDD
	
	#include <wx/wx.h>	
	#include <SQLite/sqlite3.h>// moteur SQLITE.
	
	#include <wx/stdpaths.h>	//accès aux répertoires : StandardPath
	#include <wx/filesys.h>	// accès aux noms de fichiers : filesys

	class requete_sql;
	class connexion_bdd;
	
	
	class connexion_bdd : public wxString
	{
		private:
			sqlite3* bdd;
			std::string requete_precedente;
			requete_sql* req;

		public:
			connexion_bdd();
			~connexion_bdd();
			int exec(const std::string &texte);
			requete_sql* prepare(const std::string &texte);
			requete_sql* prepare(const char *texte);
			int getColumn_int(int numero);
			std::string getColumn_text(int numero);
			double getColumn_float(int numero);
			void close();
	};
	
	
	class requete_sql : public wxString //connexion a la BDD
	{
		public:
			requete_sql(sqlite3 *&bdd,const std::string& texte);
			int bind(const std::string &cle,const std::string &valeur);
			int bind(const std::string &cle,int valeur);
			int bind(const std::string &cle,double valeur);
			int bind(int cle,int valeur);
			int bind(int cle,const std::string &valeur);
			int bind(int cle,double valeur);

			int fetch();
			int getColumn_int(int numero);
			std::string getColumn_text(int numero);
			double getColumn_float(int numero);
			void closeCursor();

		private:
			sqlite3_stmt* requete;
			sqlite3* bdd_private;
			int* types;
			int nb_colonnes;
	};
	
#endif