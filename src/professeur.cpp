#include "main.h"

Frame_prof::Frame_prof(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	bool premiere_fois=true;
	
    wxArrayString texte_choix_matieres;
	wxArrayString texte_choix_classes;
	
	//on parcourt la liste des matières
	requete_sql *req=bdd->prepare("SELECT matieres.nom, matieres.id_matiere, profs.nom,profs.prenom FROM profs JOIN matieres ON matieres.id_matiere=profs.matiere WHERE profs.id=:matricule");
	req->bind(":matricule",matricule);
	while(req->fetch())
	{
		if(premiere_fois) //on retient l'id de la première matière car ON la séléctionnera
		{
			id_matiere_en_cours=req->getColumn_int(1);
			premiere_fois=false;
		}
		texte_choix_matieres.Add(wxString(req->getColumn_text(0)));
	}
	req->closeCursor();
	
	premiere_fois=true;
	//On séléctionne les classes correspondant à la matière.
	req=bdd->prepare("SELECT classes.nom, classes.id FROM profs JOIN classes ON classes.id=profs.classe WHERE profs.id=:matricule AND profs.matiere=:matiere");
	req->bind(":matricule",matricule);
	req->bind(":matiere",id_matiere_en_cours);
	
	while(req->fetch())
	{
		if(premiere_fois) //on retient l'id de la première matière car ON la séléctionnera
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
	
	liste_notes=new wxDataViewListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize);
	
	liste_matieres->SetSelection(0);
	liste_classes->SetSelection(0);
	
	liste_notes->AppendTextColumn(_T("Élève"));
	liste_notes->AppendTextColumn(_T("CE"),wxDATAVIEW_CELL_EDITABLE);
	liste_notes->AppendTextColumn(_T("TAI"),wxDATAVIEW_CELL_EDITABLE);
	liste_notes->AppendTextColumn(_T("Projet"),wxDATAVIEW_CELL_EDITABLE);
	liste_notes->AppendTextColumn(_T("DE"),wxDATAVIEW_CELL_EDITABLE);
	liste_notes->AppendTextColumn(_T("Commentaires"),wxDATAVIEW_CELL_EDITABLE);
			
	req=bdd->prepare("SELECT eleves.id,eleves.nom,eleves.prenom, 0 AS pas_de_note, notes.note,notes.type_note FROM eleves	\
															LEFT OUTER JOIN notes ON notes.id_eleve=eleves.id 				\
							WHERE notes.id_matiere=:matiere																	\
					UNION																									\
					 SELECT eleves.id,eleves.nom,eleves.prenom, 1 AS pas_de_note, notes.note,notes.type_note FROM eleves  	\
															LEFT OUTER JOIN notes ON notes.id_eleve=eleves.id 				\
							WHERE eleves.classe=:classe AND notes.note IS null");
	
	req->bind(":classe",id_classe_en_cours);
	req->bind(":matiere",id_matiere_en_cours);
	
	std::map<int,int>::iterator it;
	wxVector<wxVariant> ligne;//wxWidgets à besoin d'un vecteur pour créer une ligne. Ce vecteurs doit contenir les champs des colonnes de cette ligne
	
	int position_y;
	wxString texte_note;
	
	for(int i=0;i<6;i++) ligne.push_back(wxVariant(""));
    
	while(req->fetch())
	{
		texte_note="";
		
		it=liste_eleves.find(req->getColumn_int(0));//si la valeur n'est pas trouvée, it sera = a liste_eleves.end()
		if(it== liste_eleves.end())//if(l'id de l'éleve n'est pas dans le vector) vector[id] = la_position_ou_on_ajoute_cette_matiere
		{
			liste_eleves[req->getColumn_int(0)]=liste_eleves.size()-1;
			
			ligne[0]=wxVariant(string(req->getColumn_text(2))+" "+string(req->getColumn_text(1)));//on effectue l'ajout de la ligne
			liste_notes->AppendItem(ligne);	
		}
		
		if(req->getColumn_int(3)==0)//si il y a une note a afficher
		{
			position_y=req->getColumn_int(5);
			texte_note<<req->getColumn_int(4);

			liste_notes->SetTextValue(texte_note,liste_eleves[req->getColumn_int(0)],position_y);
			//if(il y a une note a afficher) ON affiche la note en (position_x/liste_matiere; position_y/le_type_de_note)
		}
	}
	req->closeCursor();
	
	req=bdd->prepare("SELECT * FROM commentaires WHERE id_matiere=:matiere AND id_classe=:classe");
	req->bind(":matiere",id_matiere_en_cours);
	req->bind(":classe",id_classe_en_cours);
	
	while(req->fetch())
	{
		it=liste_eleves.find(req->getColumn_int(0));
		if(it!=liste_eleves.end())
		{
			liste_notes->SetTextValue(req->getColumn_text(2),liste_eleves[req->getColumn_int(0)],6);
		}
	}
	req->closeCursor();
	
	liste_notes->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &Frame_prof::onDbclick_notes,this);
	liste_notes->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &Frame_prof::onChange_notes,this);
	
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

void Frame_prof::onChange_notes(wxDataViewEvent &evenement)
{
	if(evenement.GetColumn()==-1 || evenement.GetColumn()==0) return ;
	
	int id_eleve,note;
	bool pas_trouve=true;
	
	std::string texte_req;
	std::map<int,int>::iterator it=liste_eleves.begin();
	
	while(pas_trouve && it != liste_eleves.end()) 
	{
		if(it->second == liste_notes->GetSelectedRow()) pas_trouve=false;//on récupère l'id de l'élève en cours a partir de la ligne séléctionnée
		else it++;// (on parcourt la map des élèves pour retrouver l'id)
	}
	
	if(pas_trouve==true) return;//si il y a une erreur interne au programme (c'est pas censé arriver mais bon...)
	
	
	note=wxAtoi(liste_notes->GetTextValue(liste_notes->GetSelectedRow(),evenement.GetColumn()));//et on récupère la note modifiée à partir de la ligne/colonne en cours.
	id_eleve=it->first;
	
	requete_sql *req=bdd->prepare("SELECT count(note) FROM notes WHERE id_eleve=:id_eleve AND id_matiere=:id_matiere AND type_note=:type_note");
	req->bind(":id_matiere",id_matiere_en_cours);
	req->bind(":id_eleve",id_eleve);
	req->bind(":type_note",evenement.GetColumn());//on regarde si cette note existe déja
	req->fetch();
	
	texte_req=(req->getColumn_int(0)==1)?// si c'est pas le cas : on l'ajoute;sinon on la crée.
		"UPDATE notes SET note=:note WHERE id_eleve=:id_eleve AND id_matiere=:id_matiere AND type_note=:type_note":
		"INSERT INTO notes VALUES (:id_eleve,:id_matiere,:note,:type_note)";
	req->closeCursor();
	
	
	req=bdd->prepare(texte_req);
	req->bind(":id_matiere",id_matiere_en_cours);
	req->bind(":id_eleve",id_eleve);
	req->bind(":type_note",evenement.GetColumn());
	req->bind(":note",note);
	req->fetch();
	req->closeCursor();
}

void Frame_prof::onDbclick_notes(wxDataViewEvent &evenement)
{
	if(evenement.GetColumn()==-1 || evenement.GetColumn()==0) return ;
		
	wxDataViewItem item=liste_notes->GetCurrentItem();
	wxDataViewColumn *colonne=evenement.GetDataViewColumn();
	
	liste_notes->EditItem(item,colonne);
}

/*

onModifier notes

->calculer moyenne eleve. Si <10 prévenir prof responsable
*/



