#include "main.h"

connexion_bdd::connexion_bdd()
{
	
	string path_fichier=string(wxStandardPaths::Get().GetExecutablePath().mb_str());// le chemin de l'executable en cours
	
	size_t pos;
	if(path_fichier.rfind("\\")!=string::npos) 
		pos=path_fichier.rfind("\\")+1; //multiplateforme : windows
	else pos=path_fichier.rfind("/")+1;//linux
	
	path_fichier=path_fichier.substr(0,pos)+"bdd.sqlite";
	
	if(sqlite3_open(path_fichier.c_str(), &bdd)!=SQLITE_OK) 
	{
		wxString texte=sqlite3_errmsg(bdd);
		wxMessageBox(_T("Erreur lors de la connexion à la  BDD : ")+texte,"erreur");
		exit(0);
	}
	
};

connexion_bdd::~connexion_bdd()
{
	sqlite3_close(bdd);
}

requete_sql* connexion_bdd::exec(const string &texte)
{
	return new requete_sql(bdd,texte);
}

requete_sql* connexion_bdd::prepare(const string &texte)
{
	return new requete_sql(bdd,texte);
}

requete_sql::requete_sql(sqlite3*& bdd,const string& texte_requete)
{	
	bdd_private=bdd;
	
	sqlite3_prepare_v2(bdd,texte_requete.c_str(),-1,&requete, NULL);
	
	string texte=string(sqlite3_errmsg(bdd_private));
	if(texte.compare("not an error"))	wxMessageBox(texte,"Erreur SQL - Prepare");
		
	// a faire : compter le onmbre de : et de ;
}

int requete_sql::bind(const string &cle,int valeur)
{
	return sqlite3_bind_int(requete, sqlite3_bind_parameter_index(requete,cle.c_str()), valeur);
}


int requete_sql::bind(const string &cle,const string &valeur)
{
	return sqlite3_bind_text(requete,sqlite3_bind_parameter_index(requete,cle.c_str()), valeur.c_str(),strlen(valeur.c_str()),SQLITE_STATIC);
}

int requete_sql::bind(int cle,int valeur)
{
	return sqlite3_bind_int(requete,cle, valeur);
}

int requete_sql::bind(int cle,const string &valeur)
{
	return sqlite3_bind_text(requete,cle, valeur.c_str(),strlen(valeur.c_str()),SQLITE_STATIC);
}

int requete_sql::fetch()
{
	int resultat=sqlite3_step(requete);
	
	if(resultat==SQLITE_ROW)
	{
		nb_colonnes=sqlite3_column_count(requete);
		types=new int[nb_colonnes+1];
		int j;
		
		for(j=0;j<nb_colonnes;j++)	types[j]=sqlite3_column_type(requete,j);
		
		return 1;
	}
	else if(resultat==SQLITE_DONE) return 0;
	else if(resultat==SQLITE_BUSY)
	{
			wxMessageBox("erreur", _T("Erreur ! SQLITE_BUSY"));
			return -1;
	}
	else   
	{
		wxString texte; 
		texte << "Erreur SQL  inconnue ! : \n"<<resultat<<" - "<<sqlite3_errmsg(bdd_private);
		wxMessageBox(texte,"Erreur SQL");	
	}
		
	return -1;
}
int requete_sql::getColumn_int(int numero)
{
	if(numero>nb_colonnes || numero<0 || types[numero]!=SQLITE_INTEGER) return -1;
	
	return sqlite3_column_int(requete,numero);
}
string requete_sql::getColumn_text(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]!=SQLITE_TEXT)  return "erreur - GetColumn_text()";
	return string((const char*)sqlite3_column_text(requete, numero));
}
double requete_sql::getColumn_float(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]!=SQLITE_FLOAT)  return -1.0;
	return sqlite3_column_double(requete,numero);
}
