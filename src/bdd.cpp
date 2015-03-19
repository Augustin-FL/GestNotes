#include "main.h"

connexion_bdd::connexion_bdd()
{
	if(sqlite3_open("bdd.sqlite", &bdd)) 
	{
		wxString texte= sqlite3_errmsg(bdd);
		throw  wxMessageBox("erreur", _T("Erreur lors de la connexion à la  BDD : ")+texte);
		exit(0);
	}
	
};

connexion_bdd::~connexion_bdd()
{
	sqlite3_close(bdd);
}

int connexion_bdd::exec(const string texte)
{
	char *texte_erreur;
	if(sqlite3_exec(bdd,(char*)&texte,NULL,0,&texte_erreur)!= SQLITE_OK);
	{
		wxMessageBox("erreur",texte_erreur);//si il est impossible de les creer
		sqlite3_free(texte_erreur);
	}
	return 0;
}



requete_prepare* connexion_bdd::prepare(const string texte)
{
	return new requete_prepare(bdd,texte);
}

requete_prepare::requete_prepare(sqlite3*& bdd,const string& texte_requete)
{	
	bdd_private=bdd;
	sqlite3_prepare_v2(bdd,(char*)&texte_requete,-1,&requete, NULL);
	
	
	// a faire : compter le onmbre de : et de ;
}

int requete_prepare::bind(char *cle,int valeur)
{
	return sqlite3_bind_int(requete, sqlite3_bind_parameter_index(requete,cle), valeur);
}

int requete_prepare::bind(const char *cle,const char *valeur)
{
	return sqlite3_bind_text(requete,sqlite3_bind_parameter_index(requete,cle), valeur,strlen(valeur),SQLITE_STATIC);
}

int requete_prepare::bind(int cle,int valeur)
{
	return sqlite3_bind_int(requete,cle, valeur);
}

int requete_prepare::bind(int cle,char *valeur)
{
	return sqlite3_bind_text(requete,cle, valeur,strlen(valeur),SQLITE_STATIC);
}

int requete_prepare::fetch()
{
	int resultat=sqlite3_step(requete);
	
	if(resultat==SQLITE_ROW)
	{
		nb_colonnes=sqlite3_column_count(requete);
		types=new int[nb_colonnes];
		for(int i=0;i<nb_colonnes;i++)  types[i]=sqlite3_column_type(requete,i);
		
		return 1;
	}
	else if(resultat==SQLITE_BUSY)
	{
			throw  wxMessageBox("erreur", _T("Erreur ! SQLITE_BUSY"));
			return -1;
	}
//	else   wxMessageBox("test",resultat);
		
	return 0;
}
int requete_prepare::getColumn_int(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]==SQLITE_INTEGER) return -1;
	return sqlite3_column_int(requete,numero);
}
char *requete_prepare::getColumn_text(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]==SQLITE_TEXT)  return NULL;
	return (char*)sqlite3_column_text(requete, numero);
}
double requete_prepare::getColumn_float(int numero)
{
	if(numero>nb_colonnes || numero<0  || types[numero]==SQLITE_FLOAT)  return -1.0;
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
