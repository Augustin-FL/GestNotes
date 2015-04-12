#include "main.h"

Frame_prof::Frame_prof(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	this->SetSize(wxDefaultCoord,wxDefaultCoord,400,400);
    wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);

    wxArrayString texte_select;
    texte_select.Add(_T("Maths Du réel"));

	wxPanel *fenetre = new wxPanel(this);
    wxStaticBoxSizer *texte_conteneur_matiere 	= new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Choisir la matière : "));
	wxChoice  *liste_matiere	= new wxChoice (fenetre, -1, wxDefaultPosition,wxDefaultSize,texte_select);
	texte_conteneur_matiere->Add(liste_matiere);
	wxStaticText *texte=new wxStaticText(fenetre, -1, _T("Gestion des notes")); // boite de choix pour les notes
	sizer_principal->Add(texte,0,wxALIGN_CENTER);
	sizer_principal->Add(liste_matiere,0,wxALIGN_CENTER|wxEXPAND|wxRIGHT|wxLEFT,10);


	wxBoxSizer *sizer_note= new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *texte_conteneur_note 	= new wxStaticBoxSizer(wxHORIZONTAL,fenetre,_T("Prof : "));
	wxButton *button_ajouter= new wxButton(fenetre, -1, _T("Ajouter"));
	wxButton *button_modifier= new wxButton(fenetre, -1, _T("Modifier"));
	wxButton *button_supprimer= new wxButton(fenetre, -1, _T("Supprimer"));

	sizer_principal->Add(sizer_note,0, wxALIGN_CENTER,0);

	sizer_note->Add(texte_conteneur_note,1,wxALIGN_CENTER|wxEXPAND,0);
	texte_conteneur_note->Add(button_ajouter,0,wxALIGN_CENTER,5);
	texte_conteneur_note->Add(button_modifier,0,wxALIGN_CENTER,5);
	texte_conteneur_note->Add(button_supprimer,0,wxALIGN_CENTER,5);

	fenetre->SetSizer(sizer_principal);

	this->SetStatusText(_T("GestNotes - Accès Professeur"));
	this->Show();

	//liste déroulante en haut.->matière

			//saisir notes
			//changer groupe(NON)
			//si accord de l'admin : changer les notes
			//ecrire des commentaires pour les bulletins
}



