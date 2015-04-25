#include "main.h"

Frame_prof::Frame_prof(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	bool premiere_fois=true;
	int id_matierere_en_cours=0;
	
    wxArrayString texte_choix_matieres;
	wxArrayString texte_choix_classes;
	
	requete_sql *req=bdd->prepare("select matieres.nom, matieres.id_matiere, profs.nom,profs.prenom from profs join matieres on matieres.id_matiere=profs.matiere where profs.id=:matricule");
	req->bind(":matricule",matricule);
	while(req->fetch())
	{
		if(premiere_fois) 
		{
			id_matierere_en_cours=req->getColumn_int(1);
			premiere_fois=false;
		}
		texte_choix_matieres.Add(wxString(req->getColumn_text(0)));
	}
	req->closeCursor();
	
	//
	req=bdd->prepare("select classes.nom, classes.id from profs join classes on classes.id=profs.classe where profs.id=:matricule and profs.matiere=:matiere");
	req->bind(":matricule",matricule);
	req->bind(":matiere",id_matierere_en_cours);
	
	while(req->fetch()) texte_choix_classes.Add(wxString(req->getColumn_text(0)));
	req->closeCursor();
	// 
   
   this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);
   
	wxPanel *fenetre = new wxPanel(this);
    wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer *sizer_selection_classe_matiere= new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer *conteneur_choix_matiere_classe = new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Choisir la matière et la classe : "));
	wxChoice  *liste_matieres	= new wxChoice (fenetre, -1, wxDefaultPosition,wxDefaultSize,texte_choix_matieres);
	wxChoice  *liste_classes	= new wxChoice (fenetre, -1, wxDefaultPosition,wxDefaultSize,texte_choix_classes);
	
	wxStaticText *texte_header=new wxStaticText(fenetre, -1, _T("Gestion des notes")); // boite de choix pour les notes
	
	wxStaticBoxSizer *conteneur_notes 	= new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Prof : "));
	
	wxListCtrl *liste_notes=new wxListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);

	liste_matieres->SetSelection(0);
	liste_classes->SetSelection(0);
	
	
	sizer_principal->Add(texte_header,0,wxALIGN_CENTER);
	sizer_principal->Add(conteneur_choix_matiere_classe,0,wxALIGN_CENTER);
	sizer_principal->Add(conteneur_notes,1,wxALIGN_CENTER|wxEXPAND,0);
	
	conteneur_choix_matiere_classe->Add(liste_matieres,1,wxALIGN_CENTER|wxALL,5);
	conteneur_choix_matiere_classe->Add(liste_classes,1,wxALIGN_CENTER|wxALL,5);
	
	conteneur_notes->Add(liste_notes,1,wxALIGN_CENTER|wxEXPAND);
	
	liste_notes->AppendColumn(_T("Élève"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("CE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("TAI"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("DE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Commentaires"),wxLIST_FORMAT_CENTER);
	
	
	/*
	
		TODO : requètes SQL pour afficher la liste des élèves avec leurs notes
	
	*/
	
	fenetre->SetSizer(sizer_principal);

	this->SetStatusText(_T("GestNotes - Accès Professeur"));
	this->Show();

	//liste déroulante en haut.->matière

			//saisir notes
			//changer groupe(NON)
			//si accord de l'admin : changer les notes
			//ecrire des commentaires pour les bulletins
}



