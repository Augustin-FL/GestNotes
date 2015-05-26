#include "main.h"

/*
ToDO : 
> Réfléchif comment s'y prendre

*/

Frame_imprimer_buletins::Frame_imprimer_buletins(wxWindow* parent_arg, connexion_bdd*& bdd_arg) : wxFrame(parent_arg, wxID_ANY,_T("GestNotes - Buletin scolaire"),wxDefaultPosition,wxSize(600,500))
{
	parent=parent_arg;
	bdd=bdd_arg;
	
	
	this->Show();
}