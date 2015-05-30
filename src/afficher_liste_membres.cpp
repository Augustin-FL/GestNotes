#include "main.h"

#ifndef __WXMSW__
	#include "ressources.xpm"//ressources linux
#else
	#include <Commctrl.h> // pour ré-ordonner les listes
	
	#ifndef HDF_SORTUP
		#define HDF_SORTUP    0x0400
	#endif

	#ifndef HDF_SORTDOWN
		#define HDF_SORTDOWN  0x0200
	#endif
#endif

Frame_afficher_liste_membres::Frame_afficher_liste_membres(Frame_principale* parent_arg, connexion_bdd*& bdd_arg,int acces_arg=0) : wxFrame(parent_arg, wxID_ANY,_T("GestNotes - Liste Des Utilisateurs"),wxDefaultPosition,wxSize(600,500))
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
	
	liste_eleves->AppendColumn(_T("Matricule"),wxLIST_FORMAT_CENTER);
	liste_eleves->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_eleves->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_profs->AppendColumn(_T("Matricule"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Matière"),wxLIST_FORMAT_CENTER);
	liste_profs->AppendColumn(_T("Classe"),wxLIST_FORMAT_CENTER);
	
	liste_admins->AppendColumn(_T("Matricule"),wxLIST_FORMAT_CENTER);
	liste_admins->AppendColumn(_T("Nom"),wxLIST_FORMAT_CENTER);
	
	this->changer_onglet(*new wxCommandEvent());
	
	sizer_haut->Add(sizer_texte,1,wxALIGN_CENTER,5);
	sizer_haut->Add(sizer_rechercher,1,wxALIGN_RIGHT,5);
	
	sizer_texte->Add(texte,1,wxALIGN_CENTER);
	sizer_rechercher->Add(rechercher,1,wxALIGN_RIGHT);
	
	onglets->AddPage(liste_eleves,_T("Élèves"));
	onglets->AddPage(liste_profs,_T("Professeurs"));
	onglets->AddPage(liste_admins,_T("Administrateurs"));
	
	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxALL,8);
	sizer_principal->Add(onglets,1,wxEXPAND);
	
	onglets->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &Frame_afficher_liste_membres::changer_onglet,this);
	rechercher->Bind(wxEVT_TEXT, &Frame_afficher_liste_membres::afficher_liste,this);
	
	liste_profs->Bind(wxEVT_LIST_COL_CLICK, &Frame_afficher_liste_membres::changer_ordre,this);
	liste_eleves->Bind(wxEVT_LIST_COL_CLICK, &Frame_afficher_liste_membres::changer_ordre,this);
	liste_admins->Bind(wxEVT_LIST_COL_CLICK, &Frame_afficher_liste_membres::changer_ordre,this);
	
	if(acces==1)
	{
		liste_profs->Bind(wxEVT_LIST_ITEM_ACTIVATED,  &Frame_admin::onModifier_id_selectionne, (Frame_admin*)parent);
		liste_eleves->Bind(wxEVT_LIST_ITEM_ACTIVATED, &Frame_admin::onModifier_id_selectionne, (Frame_admin*)parent);
		liste_admins->Bind(wxEVT_LIST_ITEM_ACTIVATED, &Frame_admin::onModifier_id_selectionne, (Frame_admin*)parent);
	}
	else if(acces==2)
	{
		liste_profs->Bind(wxEVT_LIST_ITEM_ACTIVATED,  &Frame_admin::onSupprimer_id_selectionne, (Frame_admin*)parent);
		liste_eleves->Bind(wxEVT_LIST_ITEM_ACTIVATED, &Frame_admin::onSupprimer_id_selectionne, (Frame_admin*)parent);
		liste_admins->Bind(wxEVT_LIST_ITEM_ACTIVATED, &Frame_admin::onSupprimer_id_selectionne, (Frame_admin*)parent);

	}
	this->Bind(wxEVT_CLOSE_WINDOW, &Frame_afficher_liste_membres::onClose,this);
	
	fenetre->SetSizer(sizer_principal);
	this->Show();
	parent->Disable();
	
}

void Frame_afficher_liste_membres::changer_onglet(wxCommandEvent &evenement)
{
	ordre_colonne1=1;
	ordre_colonne2=0;
	ordre_colonne3=0;
	
	this->afficher_liste(*new wxCommandEvent());
}

void Frame_afficher_liste_membres::changer_ordre(wxListEvent &evenement)
{
	int col = evenement.GetColumn();
	
	if(col==0) 
	{
		ordre_colonne2=0;
		ordre_colonne3=0;
		ordre_colonne4=0;
		if(ordre_colonne1!=1)
		{
			ordre_colonne1=1;
			this->Ajouter_curseur(0,true);
		}
		else 
		{
			ordre_colonne1=-1;
			this->Ajouter_curseur(0,false);
		}
	}
	else if(col==1)
	{	
		ordre_colonne1=0;
		ordre_colonne3=0;
		ordre_colonne4=0;
		if(ordre_colonne2!=1)
		{
			ordre_colonne2=1;
			this->Ajouter_curseur(1,true);
		}
		else
		{
			ordre_colonne2=-1;
			this->Ajouter_curseur(1,false);
		}
	}
	else if(col==2)
	{
		ordre_colonne1=0;
		ordre_colonne2=0;
		ordre_colonne4=0;
		if(ordre_colonne3!=1)
		{
			ordre_colonne3=1;
			this->Ajouter_curseur(2,true);
		}
		else
		{
			ordre_colonne3=-1;
			this->Ajouter_curseur(2,false);
		}
	}
	else 
	{
		ordre_colonne1=0;
		ordre_colonne2=0;
		ordre_colonne3=0;
		if(ordre_colonne4!=1)
		{
			ordre_colonne4=1;
			this->Ajouter_curseur(3,true);
		}
		else
		{
			ordre_colonne4=-1;
			this->Ajouter_curseur(3,false);
		}
	}
	
	this->afficher_liste(*new wxCommandEvent());
}
 
void Frame_afficher_liste_membres::afficher_liste(wxCommandEvent &evenement)
{
	wxListCtrl *liste=liste_eleves;
	
	std::string string_req;
	
	if(onglets->GetSelection()==2)
	{
		liste=liste_admins;
		string_req="SELECT id,prenom,nom FROM admins";
		
		if(!rechercher->IsEmpty()) string_req+=" WHERE nom LIKE :rechercher OR prenom LIKE :rechercher";
		
		if     (ordre_colonne1!=0) string_req+=" ORDER BY id";
		else if(ordre_colonne2!=0) string_req+=" ORDER BY nom";
		
		if(ordre_colonne1==-1 || ordre_colonne2==-1) string_req+=" DESC";
	}
	else if(onglets->GetSelection()==1)
	{
		liste=liste_profs;
		string_req="SELECT profs.id,profs.prenom,profs.nom,matieres.nom,classes.nom FROM profs JOIN matieres ON matieres.id_matiere=profs.matiere JOIN classes ON classes.id=profs.classe";
		
		if(!rechercher->IsEmpty()) string_req+=" WHERE profs.nom LIKE :rechercher OR profs.prenom LIKE :rechercher OR matieres.nom LIKE :rechercher OR classes.nom LIKE :rechercher";
		
		if(ordre_colonne1!=0) 	   string_req+=" ORDER BY profs.id";
		else if(ordre_colonne2!=0) string_req+=" ORDER BY profs.nom";
		else if(ordre_colonne3!=0) string_req+=" ORDER BY matieres.nom";
		else if(ordre_colonne4!=0) string_req+=" ORDER BY classes.nom";
		
		if(ordre_colonne1==-1 || ordre_colonne2==-1 || ordre_colonne3==-1 || ordre_colonne4==-1) string_req+=" DESC";
	}
	else 
	{
		string_req="SELECT eleves.id, prenom, eleves.nom, classes.nom FROM eleves JOIN classes ON eleves.classe=classes.id";
		
		if(!rechercher->IsEmpty()) string_req+=" WHERE eleves.nom LIKE :rechercher OR eleves.prenom LIKE :rechercher OR classes.nom LIKE :rechercher";
		
		if(ordre_colonne1!=0) 	   string_req+=" ORDER BY eleves.id";
		else if(ordre_colonne2!=0) string_req+=" ORDER BY eleves.nom";
		else if(ordre_colonne3!=0) string_req+=" ORDER BY classes.nom";
		
		if(ordre_colonne1==-1 || ordre_colonne2==-1 || ordre_colonne3==-1) string_req+=" DESC";
	}
	
	liste->DeleteAllItems();
	
	requete_sql *req=bdd->prepare(string_req);
	
	if(!rechercher->IsEmpty()) req->bind(":rechercher","%"+std::string(rechercher->GetValue().mb_str())+"%");
	
	int ligne=0;
	while(req->fetch())
	{
		liste->InsertItem(ligne,wxString::Format("%d",req->getColumn_int(0)));//matricule
		liste->SetItem(ligne,1,wxString(req->getColumn_text(1))<<" "<<wxString(req->getColumn_text(2)));//prénom nom
		
		if(onglets->GetSelection()==1 || onglets->GetSelection()==0 || onglets->GetSelection()==wxNOT_FOUND) liste->SetItem(ligne,2,req->getColumn_text(3));//classe
		if(onglets->GetSelection()==1) liste->SetItem(ligne,3,req->getColumn_text(4));//matiere

		ligne++;
	}
	req->closeCursor();

	if(rechercher->IsEmpty())
	{
		liste->SetColumnWidth(1,wxLIST_AUTOSIZE_USEHEADER);
		
		if(onglets->GetSelection()==1)
			liste->SetColumnWidth(2,wxLIST_AUTOSIZE_USEHEADER);//les profs ont 2 champs a resizer  : leur nom et leur matière
	}
	
}

void Frame_afficher_liste_membres::onChange_onglet(wxCommandEvent &evenement)
{
	rechercher->SetValue("");
	this->Ajouter_curseur(-1,true);
	this->afficher_liste(*new wxCommandEvent());
}

bool Frame_afficher_liste_membres::ongletProfs_selected()
{
	if(onglets->GetSelection()==1) return true;
	else return false;
}

bool Frame_afficher_liste_membres::ongletEleves_selected()
{
	if(onglets->GetSelection()==0) return true;
	else return false;
}
wxListCtrl*  Frame_afficher_liste_membres::getListCtrl()
{
	return liste_profs;
}

void Frame_afficher_liste_membres::onClose(wxCloseEvent &evenement)
{
	parent->Enable();
	this->Destroy();
}



void Frame_afficher_liste_membres::Ajouter_curseur(int colonne, bool haut)
{
	#ifdef __WXMSW__	
		wxListCtrl *liste=liste_eleves;
		if(onglets->GetSelection()==1) liste=liste_profs;
		else if(onglets->GetSelection()==2) liste=liste_admins;
		
		HWND hwnd = (HWND) liste->GetHWND();
		HWND header = ListView_GetHeader(hwnd);
		int nb_colonnes = Header_GetItemCount(header);

		for (int i = 0; i<nb_colonnes; i++)
		{
			HDITEM fleche = {0};
			fleche.mask = HDI_FORMAT;
			Header_GetItem(header, i, &fleche);

			fleche.fmt &= ~(HDF_SORTDOWN|HDF_SORTUP);
				
			if (i == colonne)
			{
				if(haut) fleche.fmt |= HDF_SORTUP;
				else fleche.fmt |= HDF_SORTDOWN;
			}
			
			Header_SetItem(header, i, &fleche);
		}
	#endif
}
