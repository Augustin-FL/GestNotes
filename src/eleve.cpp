#include "main.h"

/*
ToDO : 
> Imprimer le buletin

*/

Frame_eleve::Frame_eleve(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	wxString texte_groupe(_T("Groupe : ")),string_classe(_T("Classe : "));
	int classe=0;
	
	requete_sql* req=bdd->prepare("select eleves.*,classes.nom AS classe FROM eleves JOIN classes ON classes.id=eleves.classe WHERE eleves.id=:matricule");
	req->bind(":matricule",matricule);
	req->fetch();
	if(req->getColumn_int(4)==0) texte_groupe<<_T("A");
	else if(req->getColumn_int(4)==1)texte_groupe<<_T("B");
	classe=req->getColumn_int(3);
	string_classe<<req->getColumn_text(16);
	req->closeCursor();
	
	bdd->exec("select * FROM reglages");
	bool affichages_buletins=(bdd->getColumn_int(2)==0)?false:true;
	int arrondi_affichage_notes=bdd->getColumn_int(1);
	
	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);

	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut      = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_buletin   = new wxBoxSizer(wxVERTICAL);//dans un sizer Horizontal.
	wxBoxSizer *sizer_infos     = new wxBoxSizer(wxVERTICAL);// ON dois donc faire 2 sizers verticaux inutiles...
	wxBoxSizer *sizer_infos_2   = new wxBoxSizer(wxVERTICAL);// pour les infos : ON les aligne sur plusieurs lignes (d'ou les 2 sizers: l'un sera dans l'autre)...

	
	wxStaticBoxSizer *sizer_notes= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));

	bouton_imprimer_buletin=new wxButton(fenetre, -1, _T("Imprimer le buletin Scolaire"));
	wxStaticText *affichage_texte_classe= new wxStaticText(fenetre,-1,string_classe);
	wxStaticText *affichage_texte_groupe= new wxStaticText(fenetre,-1,texte_groupe);
	wxListCtrl *liste_notes=new wxListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);


	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(sizer_notes,1,wxEXPAND|wxALL,8);

	sizer_haut->Add(sizer_buletin,1,wxALIGN_LEFT,8);
	sizer_haut->Add(sizer_infos,1,wxALIGN_RIGHT,5);

	sizer_buletin->Add(bouton_imprimer_buletin,0);
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
	
	req=bdd->prepare("select matieres.id_matiere,matieres.nom,0 AS pas_de_note, notes.note,notes.type_note FROM matieres \
															LEFT OUTER JOIN profs ON matieres.id_matiere=profs.matiere	 \
															LEFT OUTER JOIN notes ON notes.id_matiere=matieres.id_matiere\
								WHERE id_eleve=:matricule																 \
				UNION select matieres.id_matiere,matieres.nom,1 AS pas_de_note, notes.note,notes.type_note FROM matieres \
															LEFT OUTER JOIN profs ON matieres.id_matiere=profs.matiere	 \
															LEFT OUTER JOIN notes ON notes.id_matiere=matieres.id_matiere\
								WHERE classe=:classe and (id_eleve!=:matricule or id_eleve is null)");
	/*
		on récupère 
			- les notes de l'élève concerné (en liant les matières & les profs aux notes)
			- les matières affectés a une classe mais ou le prof n'a encore mis aucune note à l'élève (en liant  les matières & les profs, pareil)
	
	*/
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
			position_y=req->getColumn_int(4);
			liste_notes->SetItem(liste_matiere[req->getColumn_int(0)], position_y,wxString::Format("%g",arrondi(arrondi_affichage_notes,req->getColumn_float(3))));
			//if(il y a une note a afficher) ON affiche la note en (position_x/liste_matiere; position_y/le_type_de_note)
		}
	}
	req->closeCursor();
	
	req=bdd->prepare("SELECT * FROM commentaires WHERE id_eleve=:matricule AND id_matiere!=-1");
	req->bind(":matricule",matricule);
	
	while(req->fetch())
	{
		it=liste_matiere.find(req->getColumn_int(0));// on s'occupe de l'affichage des commentaires correspondants aux matières
		
		if(it!=liste_matiere.end())
		{
			liste_notes->SetItem(liste_matiere[req->getColumn_int(0)],6,req->getColumn_text(2));
		}
	}
	req->closeCursor();
	
	for(it=liste_matiere.begin();it!=liste_matiere.end();it++)
	{
		double moyenne=-1,double_note_en_cours;
		wxString note_en_cours;
		
		for(int i=1;i<5;i++)
		{
			note_en_cours=liste_notes->GetItemText(it->second,i);
			if(note_en_cours!="" && note_en_cours.ToDouble(&double_note_en_cours))
			{
				moyenne=(moyenne==-1)?double_note_en_cours:(moyenne+double_note_en_cours)/2;
			}
		}
		if(moyenne!=-1) liste_notes->SetItem(it->second,5,wxString::Format("%g",arrondi(arrondi_affichage_notes,moyenne)));
	}
	
		liste_notes->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
		liste_notes->SetColumnWidth(6,wxLIST_AUTOSIZE_USEHEADER);
	
	
	if(!affichages_buletins) bouton_imprimer_buletin->Disable();//affichage buletins si autorisé
	
	
	bouton_imprimer_buletin->Bind(wxEVT_BUTTON,&Frame_eleve::OnClick_imprimer_buletin,this);

	fenetre->SetSizer(sizer_principal);
	this->SetStatusText(_T("GestNotes - Accès Élève"));
	this->Show();
}


void Frame_eleve::OnClick_imprimer_buletin(wxCommandEvent &evenement)
{
	frame_imprimer_buletin=new Frame_imprimer_buletins(this,bdd);
}
