#include "main.h"
//

Frame_admin::Frame_admin(Frame_principale* parent, connexion_bdd* arg_bdd,int &id_arg)
{
	bdd=arg_bdd;
	id=id_arg;
	frame_parente=parent;
	frame_parente->SetSize(wxDefaultCoord,wxDefaultCoord,800,600);


	wxPanel  *fenetre = new wxPanel(frame_parente);

	wxBoxSizer *sizer_principal= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_gauche= new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer *texte_conteneur_ajout 	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Utilisateurs : "));
	wxStaticText *texte=new wxStaticText(fenetre, -1, _T("Gestion des utilisateurs\nde GestNotes :\n\n"));
	wxButton *button_ajouter= new wxButton(fenetre, -1, _T("Ajouter"));
	wxButton *button_modifier= new wxButton(fenetre, -1, _T("Modifier"));
	wxButton *button_supprimer= new wxButton(fenetre, -1, _T("Supprimer"));

	sizer_principal->Add(sizer_gauche);
	sizer_gauche->Add(texte_conteneur_ajout);
	texte_conteneur_ajout->Add(texte,1, wxALIGN_CENTER_HORIZONTAL,5);
	texte_conteneur_ajout->Add(button_ajouter,wxALIGN_LEFT,5);
	texte_conteneur_ajout->Add(button_modifier,wxALIGN_LEFT,5);
	texte_conteneur_ajout->Add(button_supprimer,wxALIGN_LEFT,5);
	frame_parente->SetSizer(sizer_principal);


	button_ajouter->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Frame_admin::onAjouter));
	//button_supprimer->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Frame_admin::onModifier));
	//button_supprimer->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Frame_admin::onSupprimer));
	frame_parente->SetStatusText(_T("GestNotes - Accès Admin"));
	fenetre->SetSize(frame_parente->GetClientSize());
	frame_parente->Show();

}

void Frame_admin::onAjouter(wxCommandEvent &evenement)
{
	Frame_admin_ajouter ajouter(frame_parente,bdd);
}


// -------------

Frame_admin_ajouter::Frame_admin_ajouter(Frame_principale* parent,connexion_bdd* bdd_arg) : wxDialog(parent, wxID_ANY,_T("GestNotes - Ajouter"),wxDefaultPosition,wxSize(670,510))
{
	bdd=bdd_arg;
	wxArrayString texte_select;
	while(bdd->exec("select nom, id_matiere from matieres")){} //texte_select.Add(bdd->getColumn_text(0));
//	texte_select.Add(_T("<Ajouter Une Matière>"));
	
	wxPanel          *fenetre					= new wxPanel(this,-1);
	wxBoxSizer       *contenu_fenetre_sans_marge= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout		= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout_2	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout_2_horisontal= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		 *conteneur_ajout_horisontal= new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer *texte_conteneur_ajout 	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Ajouter : "));
	wxFlexGridSizer  *conteneur_ajout_gauche	= new wxFlexGridSizer(2,7,5);
	wxFlexGridSizer  *conteneur_ajout_droite	= new wxFlexGridSizer(2,11,5);
	wxStaticLine     *separarion_horisontale 	= new wxStaticLine(fenetre, -1);
	wxStaticLine     *separarion_verticale	 	= new wxStaticLine(fenetre, -1,wxDefaultPosition, wxDefaultSize,wxLI_VERTICAL);
	
	wxStaticText* texte_ajouter_prof 		= new wxStaticText(fenetre, -1, _T("\nAjouter un professeur, ou un admin : \n"));
	wxStaticText* label_ajouter_matricule 	= new wxStaticText(fenetre, -1, _T("\nLier cette personne à un profil existant : \n"));
	wxStaticText* label_ajout_nom 			= new wxStaticText(fenetre, -1, _T("Nom : "));
	wxStaticText* label_ajout_prenom		= new wxStaticText(fenetre, -1, _T("Prénom : "));
	wxStaticText* label_ajout_mdp 			= new wxStaticText(fenetre, -1, _T("Mot de Passe: "));
	wxStaticText* label_ajout_radio			= new wxStaticText(fenetre, -1, _T("Ajouter un : "));
	label_ajouter_prof__matiere				= new wxStaticText(fenetre, -1, _T("Matière : "));
	label_ajout_eleve__prenom_responsable	= new wxStaticText(fenetre, -1, _T("Prénom du Responsable : "));
	label_ajout_eleve__tel_responsable		= new wxStaticText(fenetre, -1, _T("Tel. du Responsable : "));
	label_ajout_eleve__mail_responsable		= new wxStaticText(fenetre, -1, _T("Email du responsable : "));
	label_ajout_eleve__sexe					= new wxStaticText(fenetre, -1, _T("Sexe : "));

	label_ajout_eleve__nom_rue				= new wxStaticText(fenetre, -1, _T("Rue : "));
	label_ajout_eleve__rue					= new wxStaticText(fenetre, -1, _T("Numero de Rue : "));
	label_ajout_eleve__code_postal			= new wxStaticText(fenetre, -1, _T("Code Postal : "));
	label_ajout_eleve__ville				= new wxStaticText(fenetre, -1, _T("Ville : "));
	label_ajout_eleve__tel_mobile			= new wxStaticText(fenetre, -1, _T("Tel. : "));
	label_ajout_eleve__groupe				= new wxStaticText(fenetre, -1, _T("Groupe : "));
	label_ajout_eleve__nom_responsable 		= new wxStaticText(fenetre, -1, _T("Nom du responsable : "));

	input_ajout_matricule					= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_nom							= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_prenom						= new wxTextCtrl(fenetre, -1, _T(""));
	
	input_ajout_mdp							= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	input_ajout_eleve__prenom_responsable	= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__tel_responsable		= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__mail_responsable		= new wxTextCtrl(fenetre, -1, _T(""));

	input_ajout_eleve__nom_responsable		= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__nom_rue				= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__rue					= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__code_postal			= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__ville				= new wxTextCtrl(fenetre, -1, _T(""));
	input_ajout_eleve__tel_mobile			= new wxTextCtrl(fenetre, -1, _T(""));

	wxArrayString strings_sexes;
	wxArrayString strings_groupes;
	strings_sexes.Add(_T("Fille"));
	strings_sexes.Add(_T("Garçon"));
	strings_groupes.Add(_T("Groupe A"));
	strings_groupes.Add(_T("Groupe B"));

	input_ajout_eleve__sexe					= new wxChoice(fenetre,-1,wxDefaultPosition,wxDefaultSize,strings_sexes);
	input_ajout_eleve__groupe				= new wxChoice(fenetre,-1,wxDefaultPosition,wxDefaultSize,strings_groupes);

	input_radio_prof  			= new wxRadioButton(fenetre, -1, _T("Professeur"));
	input_radio_admin 			= new wxRadioButton(fenetre, -1, _T("Administrateur"));
	input_radio_eleve 			= new wxRadioButton(fenetre, -1, _T("Élève"));
	input_radio_matricule_oui	= new wxRadioButton(fenetre, -1, _T("Oui"),wxDefaultPosition,wxDefaultSize,wxRB_GROUP);
	input_radio_matricule_non	= new wxRadioButton(fenetre, -1, _T("Non"));
	//input_select_matiere_ajout	= new wxComboBox(fenetre, -1,_T("<séléctionner>"), wxDefaultPosition,wxDefaultSize,texte_select);
	bouton_valider_ajout		= new wxButton(fenetre, -1, _T("Valider"));
	
	
	contenu_fenetre_sans_marge->Add(texte_conteneur_ajout,0,  wxALL, 5);
	
	texte_conteneur_ajout->Add(texte_ajouter_prof,0,wxALIGN_CENTER);
	texte_conteneur_ajout->Add(conteneur_ajout_horisontal);

	conteneur_ajout_horisontal->Add(conteneur_ajout_gauche);
	conteneur_ajout_horisontal->Add(separarion_verticale,0, wxALL | wxEXPAND, 5);
	conteneur_ajout_horisontal->Add(conteneur_ajout_droite);

	conteneur_ajout_gauche->Add(label_ajout_nom);
	conteneur_ajout_gauche->Add(input_ajout_nom);
	conteneur_ajout_gauche->Add(label_ajout_prenom);
	conteneur_ajout_gauche->Add(input_ajout_prenom);
	conteneur_ajout_gauche->Add(label_ajout_mdp);
	conteneur_ajout_gauche->Add(input_ajout_mdp);
	conteneur_ajout_gauche->Add(label_ajout_radio);
	conteneur_ajout_gauche->Add(contenur_radio_ajout);
	conteneur_ajout_gauche->Add(label_ajouter_prof__matiere);
//	conteneur_ajout_gauche->Add(input_select_matiere_ajout);
	conteneur_ajout_gauche->Add(label_ajouter_matricule,wxALIGN_CENTER);
	conteneur_ajout_gauche->Add(contenur_radio_ajout_2_horisontal);

	contenur_radio_ajout_2_horisontal->Add(contenur_radio_ajout_2);

	texte_conteneur_ajout->Add(separarion_horisontale,0, wxALL | wxEXPAND, 5);
	texte_conteneur_ajout->Add(bouton_valider_ajout,1, wxALIGN_CENTER_HORIZONTAL,5);
	
	contenur_radio_ajout->Add(input_radio_prof,1);
	contenur_radio_ajout->Add(input_radio_admin,1);
	contenur_radio_ajout->Add(input_radio_eleve,1);
	contenur_radio_ajout_2->Add(input_radio_matricule_non);
	contenur_radio_ajout_2->Add(input_radio_matricule_oui);

	contenur_radio_ajout_2_horisontal->Add(input_ajout_matricule,0,wxALIGN_CENTER);
	input_radio_prof->SetValue(true);
	input_radio_matricule_non->SetValue(true);

/*
	this->onClick_radio_ajout(*(new wxCommandEvent()));
	this->onChange_select_matiere(*(new wxCommandEvent()));
*/

	conteneur_ajout_droite->Add(label_ajout_eleve__nom_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__nom_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__prenom_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__prenom_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__tel_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__tel_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__mail_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__mail_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__sexe);
	conteneur_ajout_droite->Add(input_ajout_eleve__sexe);
	conteneur_ajout_droite->Add(label_ajout_eleve__nom_rue);
	conteneur_ajout_droite->Add(input_ajout_eleve__nom_rue);
	conteneur_ajout_droite->Add(label_ajout_eleve__rue);
	conteneur_ajout_droite->Add(input_ajout_eleve__rue);
	conteneur_ajout_droite->Add(label_ajout_eleve__code_postal);
	conteneur_ajout_droite->Add(input_ajout_eleve__code_postal);
	conteneur_ajout_droite->Add(label_ajout_eleve__ville);
	conteneur_ajout_droite->Add(input_ajout_eleve__ville);
	conteneur_ajout_droite->Add(label_ajout_eleve__tel_mobile);
	conteneur_ajout_droite->Add(input_ajout_eleve__tel_mobile);
	conteneur_ajout_droite->Add(label_ajout_eleve__groupe);
	conteneur_ajout_droite->Add(input_ajout_eleve__groupe);

	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	this->ShowModal();
}

Frame_admin::~Frame_admin()
{	
}
	