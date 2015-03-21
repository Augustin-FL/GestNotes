#include "main.h"

connexion_bdd::connexion_bdd()
{
	if(sqlite3_open("bdd.sqlite", &bdd)) 
	{
		wxString texte= sqlite3_errmsg(bdd);
		wxMessageBox(_T("Erreur lors de la connexion à la  BDD : ")+texte,"erreur");
		exit(0);
	}
	
};

connexion_bdd::~connexion_bdd()
{
	sqlite3_close(bdd);
}

int connexion_bdd::exec(const string &texte)
{
	char *texte_erreur;
	if(sqlite3_exec(bdd,(char*)&texte,NULL,0,&texte_erreur)!= SQLITE_OK);
	{
		wxMessageBox("erreur",texte_erreur);//si il est impossible de les creer
		sqlite3_free(texte_erreur);
	}
	return 0;
}



requete_prepare* connexion_bdd::prepare(const string &texte)
{
	return new requete_prepare(bdd,texte);
}

requete_prepare::requete_prepare(sqlite3*& bdd,const string& texte_requete)
{	
	bdd_private=bdd;
	
	sqlite3_prepare_v2(bdd,texte_requete.c_str(),-1,&requete, NULL);
	
	string texte=string(sqlite3_errmsg(bdd_private));
	if(texte.compare("not an error"))	wxMessageBox(texte,"Erreur SQL - Prepare");
		
	// a faire : compter le onmbre de : et de ;
}

int requete_prepare::bind(const string &cle,int valeur)
{
	return sqlite3_bind_int(requete, sqlite3_bind_parameter_index(requete,cle.c_str()), valeur);
}


int requete_prepare::bind(const string &cle,const string &valeur)
{
	return sqlite3_bind_text(requete,sqlite3_bind_parameter_index(requete,cle.c_str()), valeur.c_str(),strlen(valeur.c_str()),SQLITE_STATIC);
}

int requete_prepare::bind(int cle,int valeur)
{
	return sqlite3_bind_int(requete,cle, valeur);
}

int requete_prepare::bind(int cle,const string &valeur)
{
	return sqlite3_bind_text(requete,cle, valeur.c_str(),strlen(valeur.c_str()),SQLITE_STATIC);
}

int requete_prepare::fetch()
{
	int resultat=sqlite3_step(requete);
	
	if(resultat==SQLITE_ROW)
	{
		nb_colonnes=sqlite3_column_count(requete);
		types=new int[nb_colonnes+1];
		int j;
		
		for(j=0;j<nb_colonnes;j++);
			types[j]=sqlite3_column_type(requete,j);
			
		wxString a="";
		a<<types[1];
		wxMessageBox(a,"zz");
		
		return 1;
	}
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
		
	return 0;
}
int requete_prepare::getColumn_int(int numero)
{
	if(numero>nb_colonnes || numero<0 || types[numero]!=SQLITE_TEXT ) 
	{
		wxString a;
	//	a<<types[numero];
		//wxMessageBox(a,"zz");
		return -1;
	}
	return sqlite3_column_int(requete,numero);
}
string requete_prepare::getColumn_text(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]!=SQLITE_TEXT)  return "erreur - tt";
	return (char*)sqlite3_column_text(requete, numero);
}
double requete_prepare::getColumn_float(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]!=SQLITE_FLOAT)  return -1.0;
	return sqlite3_column_double(requete,numero);
}


/*
char* requete_prepare::getColumn(int numero)
{
	if(numero>nb_colonnes || numero<0) return (void)-1;
	
	if     (types[numero]==SQLITE_INTEGER) return ()sqlite3_column_int( requete,numero);
	else if(types[numero]==SQLITE_FLOAT)   return (void)sqlite3_column_double(requete,numero);
	else if(types[numero]==SQLITE_TEXT)    return (void)sqlite3_column_text(requete, numero);
	else if(types[numero]==SQLITE_BLOB)    return (void)sqlite3_column_blob(requete, numero);
	else return NULL;
}*/
//int 

/*	
sqlite3_prepare_v2(bdd,"SELECT COUNT(*) FROM adherents WHERE livre1!=-1 AND retour_livre1<=:retour_max OR livre2!=-1 AND retour_livre2<=:retour_max OR livre3!=-1 AND retour_livre3<=:retour_max",-1,&requete, NULL);
		sqlite3_bind_int(requete,sqlite3_bind_parameter_index(requete,":retour_max"),time(NULL));//1413148270 <- timesamp octobre
sqlite3_step(requete),SQLITE_ROW,bdd,position,""
		*/
