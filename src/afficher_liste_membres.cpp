#include "main.h"

/*
	TODO : rechercher un membre
*/

Afficher_liste_membres::Afficher_liste_membres(Frame_principale* parent_arg, connexion_bdd*& bdd_arg,int acces=0) : wxFrame(parent_arg, wxID_ANY,_T("GestNotes - Liste Des Utilisateurs"),wxDefaultPosition,wxSize(600,500))
{
	this->parent=parent_arg;
	this->bdd=bdd_arg;
		
	wxPanel *fenetre= new wxPanel(this);
	
	wxBoxSizer *sizer_principal= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_rechercher = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_texte= new wxBoxSizer(wxVERTICAL);
	
	wxStaticText *texte=new wxStaticText(fenetre,-1,_T("Voici la liste des utilisateurs :"));
	//wxStaticText *texte_modifier=new wxStaticText(fenetre,-1,_T("Pour modifier les informations d'un utilisateur de GestNotes\nDouble-Cliquez sur son nom :\n"));
	
	wxNotebook* onglets = new wxNotebook(fenetre,wxID_ANY); 
	wxListCtrl *liste_eleves= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	wxListCtrl *liste_profs	= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	wxListCtrl *liste_admins= new wxListCtrl(onglets,-1, wxDefaultPosition, wxDefaultSize,wxLC_REPORT);
	
	wxSearchCtrl *rechercher=new wxSearchCtrl(fenetre,-1);
	
	
	liste_eleves->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_eleves->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_profs->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Matière"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_admins->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	
	
	int ligne = 0;
	std::map<int,int> correspondance_id_position_eleve,correspondance_id_position_profs,correspondance_id_position_admins;
	
	while(bdd->exec("SELECT eleves.id, prenom, eleves.nom, classes.nom FROM eleves JOIN classes ON eleves.classe=classes.id order by eleves.nom"))
	{
		liste_eleves->InsertItem(0,wxString(bdd->getColumn_text(1))<<" "<<wxString(bdd->getColumn_text(2)));
		liste_eleves->SetItem(ligne,1,bdd->getColumn_text(3));
		
		correspondance_id_position_eleve[bdd->getColumn_int(0)]=ligne;
		ligne++;
	}
	
	ligne=0;
	while(bdd->exec("SELECT profs.id,profs.prenom,profs.nom,matieres.nom,classes.nom FROM profs JOIN matieres ON matieres.id_matiere=profs.matiere JOIN classes ON classes.id=profs.classe ORDER BY profs.nom"))
	{
		liste_profs->InsertItem(ligne,wxString(bdd->getColumn_text(1))<<" "<<wxString(bdd->getColumn_text(2)));
		liste_profs->SetItem(ligne,1,bdd->getColumn_text(3));
		liste_profs->SetItem(ligne,2,bdd->getColumn_text(4));
		
		correspondance_id_position_profs[bdd->getColumn_int(0)]=ligne;
		ligne++;
	}
	
	ligne=0;
	while(bdd->exec("SELECT id,prenom,nom FROM admin ORDER BY nom"))
	{
		liste_admins->InsertItem(ligne,wxString(bdd->getColumn_text(1))<<" "<<wxString(bdd->getColumn_text(2)));
	
		correspondance_id_position_admins[bdd->getColumn_int(0)]=ligne;
		ligne++;
	}
	
	sizer_haut->Add(sizer_texte,1,wxALIGN_CENTER,5);
	sizer_haut->Add(sizer_rechercher,1,wxALIGN_RIGHT,5);
	
	sizer_texte->Add(texte,1,wxALIGN_CENTER);
	sizer_rechercher->Add(rechercher,1,wxALIGN_RIGHT);
	
	onglets->AddPage(liste_eleves,_T("Élèves"));
	onglets->AddPage(liste_profs,_T("Professeurs"));
	onglets->AddPage(liste_admins,_T("Administrateurs"));
	
	
	liste_eleves->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
	liste_profs-> SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
	liste_profs-> SetColumnWidth(1,wxLIST_AUTOSIZE_USEHEADER);
	liste_admins->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
	
	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(onglets,1,wxEXPAND);
	fenetre->SetSizer(sizer_principal);
	this->Show();
}
 