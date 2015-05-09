#include "main.h"


Afficher_liste_membres::Afficher_liste_membres(Frame_principale* parent_arg, connexion_bdd*& bdd_arg,int acces=0) : wxFrame(NULL, wxID_ANY,_T("GestNotes - Liste Des Utilisateurs"),wxDefaultPosition,wxSize(300,220))
{
	this->parent=parent_arg;
	this->bdd=bdd_arg;
		
	wxPanel *fenetre= new wxPanel(this);
		
	wxBoxSizer *sizer_principal= new wxBoxSizer(wxVERTICAL);
		
	wxNotebook* notebook = new wxNotebook(fenetre,wxID_HIGHEST+5); 
		
	wxWindow *page_eleve=new wxWindow(notebook,wxID_ANY);
		
	notebook->AddPage(page_eleve,_T("Eleve"));
	
	//page_eleve
		
	sizer_principal->Add(notebook);
	
	this->SetSizer(sizer_principal);
	//sizer_principal->Layout();

	this->Show();
}
 