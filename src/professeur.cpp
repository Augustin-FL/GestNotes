#include "main.h"

Frame_prof::Frame_prof(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	bool premiere_fois=true;
	int id_matierere_en_cours=-1,id_classe_en_cours=-1;
	
    wxArrayString texte_choix_matieres;
	wxArrayString texte_choix_classes;
	
	//on parcourt la liste des matières
	requete_sql *req=bdd->prepare("select matieres.nom, matieres.id_matiere, profs.nom,profs.prenom from profs join matieres on matieres.id_matiere=profs.matiere where profs.id=:matricule");
	req->bind(":matricule",matricule);
	while(req->fetch())
	{
		if(premiere_fois) //on retient l'id de la première matière car on la séléctionnera
		{
			id_matierere_en_cours=req->getColumn_int(1);
			premiere_fois=false;
		}
		texte_choix_matieres.Add(wxString(req->getColumn_text(0)));
	}
	req->closeCursor();
	
	premiere_fois=true;
	//On séléctionne les classes correspondant à la matière.
	req=bdd->prepare("select classes.nom, classes.id from profs join classes on classes.id=profs.classe where profs.id=:matricule and profs.matiere=:matiere");
	req->bind(":matricule",matricule);
	req->bind(":matiere",id_matierere_en_cours);
	
	while(req->fetch())
	{
		if(premiere_fois) //on retient l'id de la première matière car on la séléctionnera
		{
			id_classe_en_cours=req->getColumn_int(1);
			premiere_fois=false;
		}
		texte_choix_classes.Add(wxString(req->getColumn_text(0)));
	}
	req->closeCursor(); 
   
   this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);
   
	wxPanel *fenetre = new wxPanel(this);
    wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *conteneur_choix_matiere_classe = new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Choisir la matière et la classe : "));
	wxStaticBoxSizer *conteneur_notes 	             = new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Notes : "));
	
	wxChoice  *liste_matieres	= new wxChoice (fenetre, -1, wxDefaultPosition,wxDefaultSize,texte_choix_matieres);
	wxChoice  *liste_classes	= new wxChoice (fenetre, -1, wxDefaultPosition,wxDefaultSize,texte_choix_classes);
	
	wxStaticText *texte_header=new wxStaticText(fenetre, -1, _T("Gestion des notes")); // boite de choix pour les notes
	
	wxDataViewListCtrl   *liste_notes=new wxDataViewListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize);
	
	liste_matieres->SetSelection(0);
	liste_classes->SetSelection(0);
	
	liste_notes->AppendToggleColumn(_T("Élève"));
	liste_notes->AppendTextColumn(_T("CE"));
	liste_notes->AppendTextColumn(_T("TAI"));
	liste_notes->AppendTextColumn(_T("DE"));
	liste_notes->AppendTextColumn(_T("Commentaires"));
			
	req=bdd->prepare("select eleve.id,eleve.nom,eleve.prenom, 0 as pas_de_note, notes.note,notes.type_note from eleve 	\
															left outer join notes on notes.id_eleve=eleve.id 			\
							where notes.id_matiere=:matiere																\
					UNION																								\
					 select eleve.id,eleve.nom,eleve.prenom, 1 as pas_de_note, notes.note,notes.type_note from eleve  	\
															left outer join notes on notes.id_eleve=eleve.id 			\
							where eleve.classe=:classe and notes.note is null");
	
	req->bind(":classe",id_classe_en_cours);
	req->bind(":matiere",id_matierere_en_cours);
	
	std::map<int,int> liste_eleves;
	std::map<int,int>::iterator it;
	int position_y;
	wxString texte_note;
	
	while(req->fetch())
	{
		texte_note="";
		
		it=liste_eleves.find(req->getColumn_int(0));//si la valeur n'est pas trouvée, it sera = a liste_eleves.end()
		//if(it== liste_eleves.end()) liste_eleves[req->getColumn_int(0)]= liste_notes->InsertItem(liste_eleves.size()+1,string(req->getColumn_text(2))+" "+string(req->getColumn_text(1)));	//if(l'id de la matiere n'est pas dans le vector) vector[id] = la_position_ou_on_ajoute_cette_matiere

		if(req->getColumn_int(3)==0)//si il y a une note a afficher
		{
			position_y=req->getColumn_int(5);
			texte_note<<req->getColumn_int(4);

//			liste_notes->SetItem(liste_eleves[req->getColumn_int(0)], position_y,texte_note);
			//if(il y a une note a afficher) on affiche la note en (position_x/liste_matiere; position_y/le_type_de_note)
		}
	}
	req->closeCursor();
		
	
	sizer_principal->Add(texte_header,0,wxALIGN_CENTER);
	sizer_principal->Add(conteneur_choix_matiere_classe,0,wxALIGN_CENTER);
	sizer_principal->Add(conteneur_notes,1,wxALIGN_CENTER|wxEXPAND,0);
	
	conteneur_choix_matiere_classe->Add(liste_matieres,1,wxALIGN_CENTER|wxALL,5);
	conteneur_choix_matiere_classe->Add(liste_classes,1,wxALIGN_CENTER|wxALL,5);
	
	conteneur_notes->Add(liste_notes,1,wxALIGN_CENTER|wxEXPAND);
	
	
	fenetre->SetSizer(sizer_principal);

	this->SetStatusText(_T("GestNotes - Accès Professeur"));
	this->Show();

	//liste déroulante en haut.->matière

			//saisir notes
			//changer groupe(NON)
			//si accord de l'admin : changer les notes
			//ecrire des commentaires pour les bulletins
}


/*

onModifier notes

->calculer moyenne eleve. Si <10 prévenir prof responsable
*/



