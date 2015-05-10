#include "main.h"
#ifndef __WXMSW__
	#include "ressources.xpm"//ressources linux
#endif


/*
	TODO : rechercher un membre
*/

Afficher_liste_membres::Afficher_liste_membres(Frame_principale* parent_arg, connexion_bdd*& bdd_arg,int acces_arg=0) : wxFrame(parent_arg, wxID_ANY,_T("GestNotes - Liste Des Utilisateurs"),wxDefaultPosition,wxSize(600,500))
{
	SetIcon(wxICON(icone));
	this->parent=parent_arg;
	this->bdd=bdd_arg;
	this->acces=acces_arg;
		
	wxPanel *fenetre= new wxPanel(this);
	
	wxBoxSizer *sizer_principal= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_rechercher = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_texte= new wxBoxSizer(wxVERTICAL);
	
	wxString string_conditionelle=_T("Voici la liste des utilisateurs :");
	if(acces_arg==1) string_conditionelle=_T("Pour modifier les informations d'un utilisateur de GestNotes\nDouble-Cliquez sur son nom :\n");
	if(acces_arg==2) string_conditionelle=_T("Pour supprimer un utilisateur de GestNotes\nDouble-Cliquez sur son nom :\n");
	
	wxStaticText *texte= new wxStaticText(fenetre,-1,string_conditionelle);

	onglets = new wxNotebook(fenetre,wxID_ANY); 
	liste_eleves= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	liste_profs	= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	liste_admins= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	
	rechercher=new wxSearchCtrl(fenetre,-1);
	
	rechercher->SetDescriptiveText(_T("Rechercher"));
	
	liste_eleves->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_eleves->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_profs->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Matière"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_admins->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	
	this->afficher_liste(*new wxCommandEvent());
	
	sizer_haut->Add(sizer_texte,1,wxALIGN_CENTER,5);
	sizer_haut->Add(sizer_rechercher,1,wxALIGN_RIGHT,5);
	
	sizer_texte->Add(texte,1,wxALIGN_CENTER);
	sizer_rechercher->Add(rechercher,1,wxALIGN_RIGHT);
	
	onglets->AddPage(liste_eleves,_T("Élèves"));
	onglets->AddPage(liste_profs,_T("Professeurs"));
	onglets->AddPage(liste_admins,_T("Administrateurs"));
	
	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(onglets,1,wxEXPAND);
	
	onglets->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &Afficher_liste_membres::afficher_liste,this);
	rechercher->Bind(wxEVT_TEXT, &Afficher_liste_membres::afficher_liste,this);
	this->Bind(wxEVT_CLOSE_WINDOW, &Afficher_liste_membres::onClose,this);
	
	fenetre->SetSizer(sizer_principal);
	this->Show();
	parent->Disable();
	
}
 
 
void Afficher_liste_membres::afficher_liste(wxCommandEvent &evenement)
{
	wxListCtrl *liste=liste_eleves;
	std::map<int,int> *correspondance=&correspondance_id_position_eleve;
	std::string string_req=(rechercher->IsEmpty())?
				"SELECT eleves.id, prenom, eleves.nom, classes.nom FROM eleves JOIN classes ON eleves.classe=classes.id ORDER BY eleves.nom":
				"SELECT eleves.id, prenom, eleves.nom, classes.nom FROM eleves JOIN classes ON eleves.classe=classes.id WHERE eleves.nom LIKE :rechercher OR eleves.prenom LIKE :rechercher ORDER BY eleves.nom";
	
	if(onglets->GetSelection()==2)
	{
		liste=liste_admins;
		correspondance=&correspondance_id_position_admins;
		string_req=(rechercher->IsEmpty())?
				"SELECT id,prenom,nom FROM admin ORDER BY nom":
				"SELECT id,prenom,nom FROM admin WHERE nom LIKE %:rechercher% OR prenom LIKE :rechercher ORDER BY nom";
	}
	else if(onglets->GetSelection()==1)
	{
		liste=liste_profs;
		correspondance=&correspondance_id_position_profs;
		string_req=(rechercher->IsEmpty())?
				"SELECT profs.id,profs.prenom,profs.nom,matieres.nom,classes.nom FROM profs JOIN matieres ON matieres.id_matiere=profs.matiere JOIN classes ON classes.id=profs.classe ORDER BY profs.nom":
				"SELECT profs.id,profs.prenom,profs.nom,matieres.nom,classes.nom FROM profs JOIN matieres ON matieres.id_matiere=profs.matiere JOIN classes ON classes.id=profs.classe WHERE profs.nom LIKE :rechercher OR profs.prenom LIKE :rechercher ORDER BY profs.nom";
	}
	
	liste->DeleteAllItems();
	correspondance->clear();

	requete_sql *req=bdd->prepare(string_req);
	
	if(!rechercher->IsEmpty())req->bind(":rechercher","%"+string(rechercher->GetValue().mb_str())+"%");
	
	int ligne=0;
	while(req->fetch())
	{
		liste->InsertItem(ligne,wxString(req->getColumn_text(1))<<" "<<wxString(req->getColumn_text(2)));
		
		if(onglets->GetSelection()==1 || onglets->GetSelection()==0 || onglets->GetSelection()==wxNOT_FOUND) liste->SetItem(ligne,1,req->getColumn_text(3));
		if(onglets->GetSelection()==1) liste->SetItem(ligne,2,req->getColumn_text(4));
			
		(*correspondance)[req->getColumn_int(0)]=ligne;
		ligne++;
	}
	req->closeCursor();

	if(rechercher->IsEmpty())
	{
		liste->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
		
		if(onglets->GetSelection()==1)
			liste->SetColumnWidth(1,wxLIST_AUTOSIZE_USEHEADER);//les profs ont 2 champs a resizer  : leur nom et leur matière
	}
}

void Afficher_liste_membres::onChange_onglet(wxCommandEvent &evenement)
{
	rechercher->SetValue("");
	this->afficher_liste(*new wxCommandEvent());
}


void Afficher_liste_membres::onClose(wxCloseEvent &evenement)
{
	parent->Enable();
	this->Destroy();
}