#include "main.h"

Frame_eleve::Frame_eleve(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	wxString texte_groupe(_T("Groupe : ")),string_classe(_T("Classe : "));
	int classe=0;
	
	requete_sql* req=bdd->prepare("select * from eleve join classes on classes.id=eleve.classe where eleve.id=:matricule");
	req->bind(":matricule",matricule);
	req->fetch();
	if(req->getColumn_int(3)==0) texte_groupe<<_T("A");
	else if(req->getColumn_int(3)==1)texte_groupe<<_T("B");
	classe=req->getColumn_int(4);
	string_classe<<req->getColumn_text(17);
	req->closeCursor();
	
	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);

	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut      = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_modifier  = new wxBoxSizer(wxVERTICAL);//il est impossible de centrer correctement
	wxBoxSizer *sizer_buletin   = new wxBoxSizer(wxVERTICAL);//dans un sizer Horizontal.
	wxBoxSizer *sizer_infos    = new wxBoxSizer(wxVERTICAL);// on dois donc faire 3 sizers verticaux inutiles...
	wxBoxSizer *sizer_infos_2   = new wxBoxSizer(wxVERTICAL);// pour les infos : on les aligne sur plusieurs lignes (d'ou les 2 sizers: l'un sera dans l'autre)...

	
	wxStaticBoxSizer *sizer_notes= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));

	bouton_modifier=new wxButton(fenetre, -1, _T("Modifier mes coordonnées"));
	bouton_imprimer_buletin=new wxButton(fenetre, -1, _T("Imprimer le buletin Scolaire"));
	wxStaticText *affichage_texte_classe= new wxStaticText(fenetre,-1,string_classe);
	wxStaticText *affichage_texte_groupe= new wxStaticText(fenetre,-1,texte_groupe);
	wxListCtrl *liste_notes=new wxListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);


	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(sizer_notes,1,wxEXPAND|wxALL,8);

	sizer_haut->Add(sizer_modifier,1,wxALIGN_LEFT,5);
	sizer_haut->Add(sizer_buletin,1,wxALIGN_CENTER,5);
	sizer_haut->Add(sizer_infos,1,wxALIGN_RIGHT,5);

	sizer_modifier->Add(bouton_modifier);
	sizer_buletin->Add(bouton_imprimer_buletin,0,wxALIGN_CENTER);
	sizer_infos->Add(sizer_infos_2,0,wxALIGN_RIGHT);
	
	sizer_infos_2->Add(affichage_texte_classe);
	sizer_infos_2->Add(affichage_texte_groupe);
	


	sizer_notes->Add(liste_notes,1,wxEXPAND);
	liste_notes->AppendColumn(_T("Matière"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("CE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("TAI"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Projet"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("DE"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Moyenne"),wxLIST_FORMAT_CENTER);
	liste_notes->AppendColumn(_T("Commentaires"),wxLIST_FORMAT_CENTER);

	req=bdd->prepare("select matieres.id_matiere,matieres.nom,0 as pas_de_note, notes.note,notes.type_note from matieres \
															left outer join profs on matieres.id_matiere=profs.matiere	 \
															left outer join notes on notes.id_matiere=matieres.id_matiere\
								where classe=:classe and id_eleve=:matricule															 \
				UNION select matieres.id_matiere,matieres.nom,1 as pas_de_note, notes.note,notes.type_note from matieres \
															left outer join profs on matieres.id_matiere=profs.matiere	 \
															left outer join notes on notes.id_matiere=matieres.id_matiere\
								where classe=:classe and id_eleve is null");
								
	req->bind(":classe",classe);
	req->bind(":matricule",matricule);
	
	std::map<int,int> liste_matiere;
	std::map<int,int>::iterator it;
	int position_y;
	wxString texte_note;
	
	while(req->fetch())
	{
		texte_note="";
		
		it=liste_matiere.find(req->getColumn_int(0));//si la valeur n'est pas trouvée, it sera = a liste_matiere.end()
		
		if(it== liste_matiere.end()) liste_matiere[req->getColumn_int(0)]=  liste_notes->InsertItem(liste_matiere.size()+1,req->getColumn_text(1));	//if(l'id de la matiere n'est pas dans le vector) vector[id] = la_position_ou_on_ajoute_cette_matiere
		
		if(req->getColumn_int(2)==0)//si il y a une note à afficher
		{
			if(req->getColumn_int(4)==5)
			{
				texte_note<<req->getColumn_text(3);
				position_y=6;
			}
			else 
			{
				position_y=req->getColumn_int(4);
				texte_note<<req->getColumn_int(3);
			}
			
			liste_notes->SetItem(liste_matiere[req->getColumn_int(0)], position_y,texte_note);
			//if(il y a une note a afficher) on affiche la note en (position_x/liste_matiere; position_y/le_type_de_note)
		}
	}
	req->closeCursor();
	
	
	for(it=liste_matiere.begin();it!=liste_matiere.end();it++)
	{
		int moyenne=-1;
		wxString note_en_cours;
		
		for(int i=1;i<4;i++)
		{
			note_en_cours=liste_notes->GetItemText(it->second,i);
			if(note_en_cours!="")moyenne= (moyenne==-1)?atoi(note_en_cours):(moyenne+atoi(note_en_cours))/2;
		}
		if(moyenne!=-1) liste_notes->SetItem(it->second,5,wxString::Format("%d",moyenne));
	}
	
	
	//TODO : imprimer buletin de notes
	//voir (modifier?) contacts

	bdd->exec("select * from reglages");
	if(bdd->getColumn_int(2)==0) bouton_imprimer_buletin->Disable();//affichage buletins si autorisé
	

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
