#include "main.h"

Frame_eleve::Frame_eleve(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	wxString texte_groupe(_T("Groupe : "));
	
	requete_sql* req=bdd->prepare("select * from eleve where id=:matricule");
	req->bind(":matricule",matricule);
	req->fetch();
	if(req->getColumn_int(3)==0) texte_groupe<<_T("A");
	else if(req->getColumn_int(3)==1)texte_groupe<<_T("B");
	req->closeCursor();
	

	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);

	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut      = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_modifier  = new wxBoxSizer(wxVERTICAL);//il est impossible de centrer correctement
	wxBoxSizer *sizer_buletin   = new wxBoxSizer(wxVERTICAL);//dans un sizer Horizontal.
	wxBoxSizer *sizer_groupe    = new wxBoxSizer(wxVERTICAL);// on dois donc faire 3 sizers verticaux inutiles...

	wxStaticBoxSizer *sizer_notes= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));

	bouton_modifier=new wxButton(fenetre, -1, _T("Modifier mes coordonnées"));
	bouton_imprimer_buletin=new wxButton(fenetre, -1, _T("Imprimer le buletin Scolaire"));
	wxStaticText *affichage_texte_groupe= new wxStaticText(fenetre,-1,texte_groupe);
	wxListCtrl *liste_notes=new wxListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);


	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(sizer_notes,1,wxEXPAND|wxALL,8);

	sizer_haut->Add(sizer_modifier,1,wxALIGN_LEFT,5);
	sizer_haut->Add(sizer_buletin,1,wxALIGN_CENTER,5);
	sizer_haut->Add(sizer_groupe,1,wxALIGN_RIGHT,5);

	sizer_modifier->Add(bouton_modifier);
	sizer_buletin->Add(bouton_imprimer_buletin,0,wxALIGN_CENTER);
	sizer_groupe->Add(affichage_texte_groupe,0,wxALIGN_RIGHT);


	sizer_notes->Add(liste_notes,1,wxEXPAND);
	liste_notes->AppendColumn(_T("Matière"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("CE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("TAI"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("DE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Moyenne"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Commentaires"),wxLIST_FORMAT_CENTER);
	
	req=bdd->prepare("select nom as nom_matiere, note, type_note,notes.id_matiere from matieres    \
	left outer join notes on notes.id_matiere=matieres.id_matiere where notes.id_eleve=:matricule");
	req->bind(":matricule",matricule);
	
	std::map<int,int> liste_matiere;
	std::map<int,int>::iterator it;
	
	while(req->fetch())
	{
		it=liste_matiere.find(req->getColumn_int(3));//si la valeur n'est pas trouvée, it sera = a liste_matiere.end()
		
		if(it== liste_matiere.end()) liste_matiere[req->getColumn_int(3)]=  liste_notes->InsertItem(liste_matiere.size()+1,req->getColumn_text(0));	
		//if(l'id de la matiere n'est pas dans le vector) vector[id] = la_position_ou_on_ajoute_cette_matiere

		liste_notes->SetItem(liste_matiere[req->getColumn_int(3)], req->getColumn_int(2),wxString::Format(wxT("%i"),req->getColumn_int(1)) );
		
	}
	req->closeCursor();
	
	//consulter les notes (tableau) +imprimer buletin de notes
	//consulter son groupe
	//voir (modifier?) contacts


	bouton_modifier->Bind(wxEVT_BUTTON,&Frame_eleve::OnClick_modifier,this);
	bouton_imprimer_buletin->Bind(wxEVT_BUTTON,&Frame_eleve::OnClick_imprimer_buletin,this);

	fenetre->SetSizer(sizer_principal);
	this->SetStatusText(_T("GestNotes - Accès Élève"));
	this->Show();
}

void Frame_eleve::OnClick_modifier(wxCommandEvent &evenement)
{

}


void Frame_eleve::OnClick_imprimer_buletin(wxCommandEvent &evenement)
{



}
