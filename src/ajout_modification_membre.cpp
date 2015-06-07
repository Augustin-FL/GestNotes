#include "ajout_modification_membre.h"


Frame_ajout_modification_membre::Frame_ajout_modification_membre(wxWindow* parent,connexion_bdd*& bdd_arg, int matricule_arg,int matiere_arg, int classe_arg) : wxDialog(parent, wxID_ANY,_T("GestNotes - Ajouter"),wxDefaultPosition,wxSize(670,510))
{
	bdd=bdd_arg;
	matricule=matricule_arg;
	matiere=matiere_arg;
	classe=classe_arg;

	this->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

	while(bdd->exec("SELECT nom FROM matieres")) texte_select.Add(bdd->getColumn_text(0));
	texte_select.Add(_T("<Ajouter Une Matière>"));
	while(bdd->exec("SELECT nom FROM classes")) texte_classes.Add(bdd->getColumn_text(0));
	texte_classes.Add(_T("<Ajouter Une Classe>"));

	wxString string_texte_header_ajouter=_T("\nAjouter un membre de GestNotes : \n");
	if(matricule!=-1)
	{
		string_texte_header_ajouter=_T("\nModifier un membre de GestNotes : \n");
		string_texte_header_ajouter<<_T("Matricule du membre modifié : ")<<matricule<<_T("\n");
		this->SetSize(670,530);
	}

	wxPanel          *fenetre					= new wxPanel(this,-1);
	wxBoxSizer       *contenu_fenetre_sans_marge= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout		= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout_2	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout_2_horisontal= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		 *conteneur_ajout_horisontal= new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer *texte_conteneur_ajout 	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Ajouter : "));
	wxFlexGridSizer  *conteneur_ajout_gauche	= new wxFlexGridSizer(2,8,5);
	wxFlexGridSizer  *conteneur_ajout_droite	= new wxFlexGridSizer(2,11,5);
	wxStaticLine     *separarion_horisontale 	= new wxStaticLine(fenetre, -1);
	wxStaticLine     *separarion_verticale	 	= new wxStaticLine(fenetre, -1,wxDefaultPosition, wxDefaultSize,wxLI_VERTICAL);

	wxStaticText* texte_header_ajouter		= new wxStaticText(fenetre, -1, string_texte_header_ajouter);
	wxStaticText* label_ajouter_matricule 	= new wxStaticText(fenetre, -1, _T("\nLier cette personne à un profil existant : \n"));
	wxStaticText* label_ajout_prenom		= new wxStaticText(fenetre, -1, _T("Prénom : "));
	wxStaticText* label_ajout_nom 			= new wxStaticText(fenetre, -1, _T("Nom : "));
	wxStaticText* label_ajout_mdp 			= new wxStaticText(fenetre, -1, _T("Mot de Passe: "));
	wxStaticText* label_ajout_radio			= new wxStaticText(fenetre, -1, _T("Ajouter un : "));
	label_ajouter_prof__matiere				= new wxStaticText(fenetre, -1, _T("Matière : "));
	label_ajout_eleve__prenom_responsable	= new wxStaticText(fenetre, -1, _T("Prénom du Responsable : "));
	label_ajout_eleve__tel_responsable		= new wxStaticText(fenetre, -1, _T("Tel. du Responsable : "));
	label_ajout_eleve__mail_responsable		= new wxStaticText(fenetre, -1, _T("Email du responsable : "));
	label_ajout_eleve__sexe					= new wxStaticText(fenetre, -1, _T("Sexe : "));

	label_ajout_eleve__rue					= new wxStaticText(fenetre, -1, _T("Rue : "));
	label_ajout_eleve__num_rue				= new wxStaticText(fenetre, -1, _T("Numero de Rue : "));
	label_ajout_eleve__code_postal			= new wxStaticText(fenetre, -1, _T("Code Postal : "));
	label_ajout_eleve__ville				= new wxStaticText(fenetre, -1, _T("Ville : "));
	label_ajout_eleve__tel_mobile			= new wxStaticText(fenetre, -1, _T("Tel. : "));
	label_ajout_eleve__groupe				= new wxStaticText(fenetre, -1, _T("Groupe : "));
	label_ajout_eleve__nom_responsable 		= new wxStaticText(fenetre, -1, _T("Nom du responsable : "));
	label_ajout_eleve__classe		 		= new wxStaticText(fenetre, -1, _T("Classe : "));
	input_ajout_matricule					= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS|wxFILTER_EMPTY));
	input_ajout_prenom						= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_nom							= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator());

	input_ajout_mdp							= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_eleve__prenom_responsable	= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_eleve__tel_responsable		= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS|wxFILTER_EMPTY));
	input_ajout_eleve__mail_responsable		= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextRegexpValidator("[-0-9a-zA-Z.+_]+@[-0-9a-zA-Z.+_]+\\.[a-zA-Z]{2,4}"));

	input_ajout_eleve__nom_responsable		= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_eleve__rue					= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_eleve__num_rue				= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));
	input_ajout_eleve__code_postal			= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));
	input_ajout_eleve__ville				= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	input_ajout_eleve__tel_mobile			= new wxTextCtrl(fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));

	wxArrayString strings_sexes;
	wxArrayString strings_groupes;
	strings_sexes.Add(_T("Fille"));
	strings_sexes.Add(_T("Garçon"));
	strings_groupes.Add(_T("Groupe A"));
	strings_groupes.Add(_T("Groupe B"));

	input_ajout_eleve__sexe		= new wxChoice     (fenetre, -1, wxDefaultPosition,wxDefaultSize,strings_sexes);
	input_ajout_eleve__groupe	= new wxChoice     (fenetre, -1, wxDefaultPosition,wxDefaultSize,strings_groupes);

	input_radio_matricule_oui	= new wxRadioButton(fenetre, -1, _T("Oui"));
	input_radio_matricule_non	= new wxRadioButton(fenetre, -1, _T("Non"));
	input_radio_prof  			= new wxRadioButton(fenetre, -1, _T("Professeur"),wxDefaultPosition,wxDefaultSize,wxRB_GROUP);
	input_radio_admin 			= new wxRadioButton(fenetre, -1, _T("Administrateur"));
	input_radio_eleve 			= new wxRadioButton(fenetre, -1, _T("Élève"));

	input_ajout_eleve__classe	= new wxComboBox   (fenetre, -1, _T("<séléctionner>"), wxDefaultPosition,wxDefaultSize,texte_classes,0);
	input_select_matiere_ajout	= new wxComboBox   (fenetre, -1, _T("<séléctionner>"), wxDefaultPosition,wxDefaultSize,texte_select,0);
	bouton_valider_ajout		= new wxButton     (fenetre, -1, _T("Valider"));


	contenu_fenetre_sans_marge->Add(texte_conteneur_ajout,0,  wxALL, 5);

	texte_conteneur_ajout->Add(texte_header_ajouter,0,wxALIGN_CENTER);
	texte_conteneur_ajout->Add(conteneur_ajout_horisontal);

	conteneur_ajout_horisontal->Add(conteneur_ajout_gauche);
	conteneur_ajout_horisontal->Add(separarion_verticale,0, wxALL | wxEXPAND, 5);
	conteneur_ajout_horisontal->Add(conteneur_ajout_droite);

	conteneur_ajout_gauche->Add(label_ajout_prenom);
	conteneur_ajout_gauche->Add(input_ajout_prenom);
	conteneur_ajout_gauche->Add(label_ajout_nom);
	conteneur_ajout_gauche->Add(input_ajout_nom);
	conteneur_ajout_gauche->Add(label_ajout_mdp);
	conteneur_ajout_gauche->Add(input_ajout_mdp);
	conteneur_ajout_gauche->Add(label_ajout_radio);
	conteneur_ajout_gauche->Add(contenur_radio_ajout);
	conteneur_ajout_gauche->Add(label_ajouter_prof__matiere);
	conteneur_ajout_gauche->Add(input_select_matiere_ajout);
	conteneur_ajout_gauche->Add(label_ajouter_matricule,wxALIGN_CENTER);
	conteneur_ajout_gauche->Add(contenur_radio_ajout_2_horisontal);
	conteneur_ajout_gauche->Add(label_ajout_eleve__classe);
	conteneur_ajout_gauche->Add(input_ajout_eleve__classe);

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


	this->onClick_radio(*(new wxCommandEvent()));
	this->onChange_select(*(new wxCommandEvent()));


	conteneur_ajout_droite->Add(label_ajout_eleve__prenom_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__prenom_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__nom_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__nom_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__tel_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__tel_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__mail_responsable);
	conteneur_ajout_droite->Add(input_ajout_eleve__mail_responsable);
	conteneur_ajout_droite->Add(label_ajout_eleve__sexe);
	conteneur_ajout_droite->Add(input_ajout_eleve__sexe);
	conteneur_ajout_droite->Add(label_ajout_eleve__num_rue);
	conteneur_ajout_droite->Add(input_ajout_eleve__num_rue);
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

	input_ajout_eleve__tel_responsable->SetMaxLength(10);
	input_ajout_eleve__tel_mobile->SetMaxLength(10);
	input_ajout_eleve__code_postal->SetMaxLength(5);


	input_select_matiere_ajout->MoveAfterInTabOrder(input_radio_prof); // l'ordre de déplacement à l'aide de la touche TAB
	input_ajout_eleve__classe->MoveAfterInTabOrder(input_radio_eleve);

	input_ajout_eleve__prenom_responsable->MoveAfterInTabOrder(input_ajout_eleve__classe);
	input_ajout_eleve__nom_responsable->MoveAfterInTabOrder(input_ajout_eleve__prenom_responsable);
	input_ajout_eleve__tel_responsable->MoveAfterInTabOrder(input_ajout_eleve__nom_responsable);
	input_ajout_eleve__mail_responsable->MoveAfterInTabOrder(input_ajout_eleve__tel_responsable);
	input_ajout_eleve__sexe->MoveAfterInTabOrder(input_ajout_eleve__mail_responsable);
	input_ajout_eleve__num_rue->MoveAfterInTabOrder(input_ajout_eleve__sexe);
	input_ajout_eleve__rue->MoveAfterInTabOrder(input_ajout_eleve__num_rue);
	input_ajout_eleve__code_postal->MoveAfterInTabOrder(input_ajout_eleve__rue);
	input_ajout_eleve__ville->MoveAfterInTabOrder(input_ajout_eleve__code_postal);
	input_ajout_eleve__tel_mobile->MoveAfterInTabOrder(input_ajout_eleve__ville);
	input_ajout_eleve__groupe->MoveAfterInTabOrder(input_ajout_eleve__tel_mobile);

	if(matricule!=-1)
	{
		input_radio_matricule_oui->Disable();
		input_radio_matricule_non->Disable();
		input_ajout_matricule->Disable();
		this->remplir_champs();
	}

	bouton_valider_ajout->Bind(      wxEVT_BUTTON,		&Frame_ajout_modification_membre::onClick,			this);
	input_select_matiere_ajout->Bind(wxEVT_COMBOBOX,    &Frame_ajout_modification_membre::onChange_select, 	this);
	input_ajout_eleve__classe->Bind( wxEVT_COMBOBOX,    &Frame_ajout_modification_membre::onChange_select, 	this);
	input_radio_prof->Bind(          wxEVT_RADIOBUTTON, &Frame_ajout_modification_membre::onClick_radio, 	this);
	input_radio_eleve->Bind(         wxEVT_RADIOBUTTON, &Frame_ajout_modification_membre::onClick_radio,	this);
	input_radio_admin->Bind(         wxEVT_RADIOBUTTON, &Frame_ajout_modification_membre::onClick_radio,	this);
	input_radio_matricule_oui->Bind( wxEVT_RADIOBUTTON ,&Frame_ajout_modification_membre::onClick_radio,	this);
	input_radio_matricule_non->Bind( wxEVT_RADIOBUTTON ,&Frame_ajout_modification_membre::onClick_radio,	this);


	fenetre->SetSizer(contenu_fenetre_sans_marge);
	this->ShowModal();
}

void Frame_ajout_modification_membre::remplir_champs()
{
	requete_sql* req=bdd->prepare("SELECT type FROM login_centralise WHERE matricule=:matricule");

	req->bind(":matricule",matricule);
	req->fetch();
	int type_tmp=req->getColumn_int(0);
	req->closeCursor();

	input_ajout_mdp->SetValue(std::string("*******"));


	if(type_tmp==ADMIN)
	{
		input_radio_admin->SetValue(true);
		req=bdd->prepare("SELECT * FROM admins WHERE id=:matricule");
		req->bind(":matricule",matricule);
		req->fetch();

		input_ajout_nom->SetValue(std::string(req->getColumn_text(1)));
		input_ajout_prenom->SetValue(std::string(req->getColumn_text(2)));

		req->closeCursor();
	}
	else if(type_tmp==PROF)
	{
		input_radio_prof->SetValue(true);

		req=bdd->prepare("SELECT * FROM profs WHERE id=:matricule AND matiere=:matiere AND classe=:classe");
		req->bind(":matricule", matricule);
		req->bind(":matiere", matiere);
		req->bind(":classe",classe);
		req->fetch();

		input_ajout_nom->SetValue(std::string(req->getColumn_text(1)));
		input_ajout_prenom->SetValue(std::string(req->getColumn_text(2)));

		input_ajout_eleve__classe->SetSelection(classe);
		input_select_matiere_ajout->SetSelection(matiere);

		req->closeCursor();
	}
	else if(type_tmp==ELEVE)
	{
		input_radio_eleve->SetValue(true);
		req=bdd->prepare("SELECT * FROM eleves WHERE id=:matricule");
		req->bind(":matricule", matricule);
		req->fetch();

		input_ajout_nom->SetValue(std::string(req->getColumn_text(2)));
		input_ajout_prenom->SetValue(std::string(req->getColumn_text(1)));

		input_ajout_eleve__classe->SetSelection(req->getColumn_int(3));
		input_ajout_eleve__groupe->SetSelection(req->getColumn_int(4));

		input_ajout_eleve__sexe->SetSelection(req->getColumn_int(4));
		input_ajout_eleve__rue->SetValue(std::string(req->getColumn_text(7)));
		input_ajout_eleve__num_rue->SetValue(wxString::Format("%d",req->getColumn_int(8)));//aleat
		input_ajout_eleve__code_postal->SetValue(wxString::Format("%d",req->getColumn_int(9)));
		input_ajout_eleve__ville->SetValue(std::string(req->getColumn_text(10)));
		input_ajout_eleve__tel_mobile->SetValue(std::string(req->getColumn_text(11)));//cp
		input_ajout_eleve__nom_responsable->SetValue(std::string(req->getColumn_text(12)));
		input_ajout_eleve__prenom_responsable->SetValue(std::string(req->getColumn_text(13)));
		input_ajout_eleve__tel_responsable->SetValue(std::string(req->getColumn_text(14)));//cp
		input_ajout_eleve__mail_responsable->SetValue(std::string(req->getColumn_text(15)));

		req->closeCursor();
	}

	this->onClick_radio(*(new wxCommandEvent()));
	this->onChange_select(*(new wxCommandEvent()));

}
void Frame_ajout_modification_membre::onClick_radio(wxCommandEvent &evenement)
{

	if(input_radio_matricule_non->GetValue())
	{
		input_ajout_matricule->Disable();

		input_ajout_nom->Enable();
		input_ajout_prenom->Enable();
		input_ajout_mdp->Enable();

		input_radio_admin->Enable();
		input_radio_eleve->Enable();
	}
	else if(input_radio_matricule_oui->GetValue())
	{
		input_ajout_matricule->Enable();

		input_radio_admin->Disable();
		input_radio_eleve->Disable();
		input_radio_prof->SetValue(true);

		input_ajout_nom->Disable();
		input_ajout_prenom->Disable();
		input_ajout_mdp->Disable();
	}

	if(input_radio_eleve->GetValue())
	{
		label_ajout_eleve__nom_responsable->Enable();
		input_ajout_eleve__nom_responsable->Enable();
		input_ajout_eleve__nom_responsable->Disable();
		input_ajout_eleve__prenom_responsable->Enable();
		input_ajout_eleve__tel_responsable->Enable();
		input_ajout_eleve__mail_responsable->Enable();
		input_ajout_eleve__nom_responsable->Enable();
		input_ajout_eleve__rue->Enable();
		input_ajout_eleve__num_rue->Enable();
		input_ajout_eleve__code_postal->Enable();
		input_ajout_eleve__ville->Enable();
		input_ajout_eleve__tel_mobile->Enable();
		input_ajout_eleve__sexe->Enable();
		input_ajout_eleve__groupe->Enable();
		input_ajout_eleve__classe->Enable();

		label_ajout_eleve__classe->Enable();
		label_ajout_eleve__sexe->Enable();
		label_ajout_eleve__groupe->Enable();
		label_ajout_eleve__nom_responsable->Enable();
		label_ajout_eleve__prenom_responsable->Enable();
		label_ajout_eleve__tel_responsable->Enable();
		label_ajout_eleve__mail_responsable->Enable();
		label_ajout_eleve__sexe->Enable();
		label_ajout_eleve__rue->Enable();
		label_ajout_eleve__num_rue->Enable();
		label_ajout_eleve__code_postal->Enable();
		label_ajout_eleve__ville->Enable();
		label_ajout_eleve__tel_mobile->Enable();
		label_ajout_eleve__groupe->Enable();
		label_ajout_eleve__nom_responsable->Enable();

		input_select_matiere_ajout->Disable();
		label_ajouter_prof__matiere->Disable();
	}
	else
	{
		if(input_radio_prof->GetValue())
		{
			input_select_matiere_ajout->Enable();
			label_ajouter_prof__matiere->Enable();
			input_ajout_eleve__classe->Enable();
			label_ajout_eleve__classe->Enable();

		}
		else if(input_radio_admin->GetValue())
		{
			input_select_matiere_ajout->Disable();
			label_ajouter_prof__matiere->Disable();
			input_ajout_eleve__classe->Disable();
			label_ajout_eleve__classe->Disable();
		}

		input_ajout_eleve__nom_responsable->Disable();
		input_ajout_eleve__prenom_responsable->Disable();
		input_ajout_eleve__tel_responsable->Disable();
		input_ajout_eleve__mail_responsable->Disable();
		input_ajout_eleve__nom_responsable->Disable();
		input_ajout_eleve__rue->Disable();
		input_ajout_eleve__num_rue->Disable();
		input_ajout_eleve__code_postal->Disable();
		input_ajout_eleve__ville->Disable();
		input_ajout_eleve__tel_mobile->Disable();
		input_ajout_eleve__sexe->Disable();
		input_ajout_eleve__groupe->Disable();

		label_ajout_eleve__sexe->Disable();
		label_ajout_eleve__groupe->Disable();
		label_ajout_eleve__nom_responsable->Disable();
		label_ajout_eleve__prenom_responsable->Disable();
		label_ajout_eleve__tel_responsable->Disable();
		label_ajout_eleve__mail_responsable->Disable();
		label_ajout_eleve__sexe->Disable();
		label_ajout_eleve__rue->Disable();
		label_ajout_eleve__num_rue->Disable();
		label_ajout_eleve__code_postal->Disable();
		label_ajout_eleve__ville->Disable();
		label_ajout_eleve__tel_mobile->Disable();
		label_ajout_eleve__groupe->Disable();
		label_ajout_eleve__nom_responsable->Disable();
	}
}



void Frame_ajout_modification_membre::onChange_select(wxCommandEvent &evenement)
{
	if((unsigned int)input_select_matiere_ajout->GetSelection()==texte_select.GetCount()-1)
	{
		input_select_matiere_ajout->SetEditable(true);
		input_select_matiere_ajout->SetValue("");
	}
	else
	{
		input_select_matiere_ajout->SetEditable(false);
		input_select_matiere_ajout->SetBackgroundColour(0xFFFFFF);
	}
	if((unsigned int)input_ajout_eleve__classe->GetSelection()==texte_classes.GetCount()-1)
	{
		input_ajout_eleve__classe->SetEditable(true);
		input_ajout_eleve__classe->SetValue("");
	}
	else
	{
		input_ajout_eleve__classe->SetEditable(false);
		input_ajout_eleve__classe->SetBackgroundColour(0xFFFFFF);
	}
}

void Frame_ajout_modification_membre::onClick(wxCommandEvent &evenement)
{
	requete_sql *req=NULL;
	int type_ajout=-1,ancien_type=-1;
	int matricule_modif=0;
	bool nessecite_update=false;
	wxString fin;
	std::string texte_req;

	if(input_radio_prof->GetValue())		type_ajout=PROF;// si c'est un prof
	else if(input_radio_admin->GetValue()) 	type_ajout=ADMIN; // un admin
	else if(input_radio_eleve->GetValue()) 	type_ajout=ELEVE;//un éleve



	if(!this->valider())//fonction "controleur"
	{
		wxMessageBox(_T("Erreur ! Avez vous rempli tout les champs?"));//tout n'est pas ok
		return ;
	}

	if(matricule!=-1) // si on update un membre
	{
		ancien_type=this->getAncienType();

		if(input_ajout_mdp->GetValue().Cmp(_T("*******"))!=0)//si le mot de passe a été modifié
		{
			req=bdd->prepare("UPDATE login_centralise SET mdp=:mdp WHERE matricule=:matricule");
			req->bind(":matricule",matricule);
			req->bind(":mdp",std::string(input_ajout_mdp->GetValue().mb_str()));
			req->fetch();
			req->closeCursor();
		}

		if(ancien_type!=type_ajout)
		{

			if(ancien_type==PROF)//|| this->getAncienType()==ELEVE)
			{// s'occuper des classes / matiere

				req=bdd->prepare("SELECT count(id) FROM profs WHERE id=:matricule");
				req->bind(":matricule",matricule);
				req->fetch();
				if(req->getColumn_int(0)>1)
				{
					req->closeCursor();
					if(wxMessageBox(_T("ce proffesseur est affecté à plusieurs matières ou classes. Son accès en tant que professeur sera entièrement révoqué. Continuer?"),_T("Confirmer"),wxYES_NO) == wxNO)
						return ;
				}
				else req->closeCursor();

				req=bdd->prepare("SELECT * FROM profs WHERE id=:matricule");
				req->bind(":matricule",matricule);

				while(req->fetch())
					this->supprimer_prof(matricule, req->getColumn_int(4),req->getColumn_int(3));
				req->closeCursor();
			}
			else if(ancien_type==ADMIN)
			{
				req=bdd->prepare("DELETE FROM admins WHERE id=:matricule");
				req->bind(":matricule",matricule);
				req->fetch();
				req->closeCursor();
			}
			else
			{
				req=bdd->prepare("SELECT classe FROM eleves WHERE id=:matricule");//and eleve
				req->bind(":matricule",matricule);
				req->fetch();
				this->supprimer_eleve(matricule,req->getColumn_int(0));
				req->closeCursor();
			}

			req=bdd->prepare("UPDATE login_centralise set type=:nouveau_type WHERE matricule=:matricule");
			req->bind(":nouveau_type",type_ajout);
			req->bind(":matricule",matricule);
			req->fetch();

			req->closeCursor();
		}
		else nessecite_update=true;


		matricule_modif=matricule;
	}
	else //si on ajoute un membre
	{
		matricule_modif=this->valider_ajouter_login_centralise();
		if(matricule_modif==-1) return ;//si il y a eu une erreur lors de l'ajout.
	}


	if((type_ajout==PROF || type_ajout==ELEVE) && input_ajout_eleve__classe->GetSelection()==wxNOT_FOUND)//si on as une nouvelle classe : on l'ajoute en BDD ! :p
	{																									//l'id d'une classe est texte_classes.GetSelection()-1
		req=bdd->prepare("INSERT INTO classes (nom)  VALUES(:nom_classe)");
		req->bind(":nom_classe", std::string(input_ajout_eleve__classe->GetValue().mb_str()));
		req->fetch();
		req->closeCursor();

		texte_classes.Insert(input_ajout_eleve__classe->GetValue(), texte_classes.GetCount()-1);

		input_ajout_eleve__classe->Clear();
		input_ajout_eleve__classe->Append(texte_classes);
		input_ajout_eleve__classe->SetSelection(texte_classes.GetCount()-2);
		this->onChange_select(*(new wxCommandEvent()));
	}

	if(type_ajout==PROF && input_select_matiere_ajout->GetSelection()==wxNOT_FOUND)//si on as une nouvelle matière : on l'ajoute en BDD ! :p
	{																		    	 //l'id de la matiere est texte_select.GetSelection()-1
		req=bdd->prepare("INSERT INTO matieres (nom) VALUES (:nom_matiere)");
		req->bind(":nom_matiere",std::string(input_select_matiere_ajout->GetValue().mb_str()));
		req->fetch();
		req->closeCursor();

		texte_select.Insert(input_select_matiere_ajout->GetValue(), texte_select.GetCount()-1);

		input_select_matiere_ajout->Clear();
		input_select_matiere_ajout->Append(texte_select);
		input_select_matiere_ajout->SetSelection(texte_select.GetCount()-2);
		this->onChange_select(*(new wxCommandEvent()));
	}

	//----------- ajout proprement dit

	if(type_ajout==PROF)
	{
		if(nessecite_update)
		{

			req=bdd->prepare("UPDATE profs SET matiere=:matiere,classe=:classe WHERE id=:matricule_old AND matiere=:matiere_old AND classe=:classe_old");//met a jours la classe/matiere
			req->bind(":matiere",input_select_matiere_ajout->GetSelection());
			req->bind(":classe",input_ajout_eleve__classe->GetSelection());
			req->bind(":matiere_old",matiere);
			req->bind(":classe_old",classe);
			req->bind(":matricule_old",matricule);
			req->fetch();
			req->closeCursor();

			req=bdd->prepare("UPDATE profs SET id=:matricule,nom=:nom,prenom=:prenom WHERE id=:matricule_old");//met a jour le prénom/nom
			req->bind(":nom",std::string(input_ajout_nom->GetValue().mb_str()));
			req->bind(":prenom",std::string(input_ajout_prenom->GetValue().mb_str()));
			req->bind(":matricule",matricule_modif);
			req->bind(":matricule_old",matricule_modif);
			req->fetch();
			req->closeCursor();

		}
		else
		{
			req=bdd->prepare("INSERT INTO profs VALUES (:matricule,:nom,:prenom,:matiere,:classe)");
			req->bind(":matiere",input_select_matiere_ajout->GetSelection());
			req->bind(":classe",input_ajout_eleve__classe->GetSelection());
			req->bind(":nom",std::string(input_ajout_nom->GetValue().mb_str()));
			req->bind(":prenom",std::string(input_ajout_prenom->GetValue().mb_str()));
			req->bind(":matricule",matricule_modif);

			req->fetch();
			req->closeCursor();
		}


	}
	else if(type_ajout==ELEVE)
	{
		texte_req=(nessecite_update)?
			"UPDATE eleves SET id=:matricule,prenom=:prenom,nom=:nom,classe=:classe,groupe=:groupe,sexe=:sexe,date_inscription=:date_inscription,rue=:rue,num_rue=:num_rue,code_postal=:code_postal,ville=:ville,tel_mobile=:tel_mobile,nom_responsable=:nom_responsable,prenom_responsable=:prenom_responsable,tel_responsable=:tel_responsable,mail_responsable=:mail_responsable WHERE id=:matricule_old":
			"INSERT INTO eleves VALUES (:matricule,:prenom,:nom,:classe,:groupe,:sexe,:date_inscription,:rue,:num_rue,:code_postal,:ville,:tel_mobile,:nom_responsable,:prenom_responsable,:tel_responsable,:mail_responsable)";

		req=bdd->prepare(texte_req);

		req->bind(":groupe",input_ajout_eleve__groupe->GetSelection());
		req->bind(":sexe",  input_ajout_eleve__sexe->  GetSelection());
		req->bind(":date_inscription",(int)time(NULL));

		req->bind(":rue",std::string(input_ajout_eleve__rue->GetValue().mb_str()));
		req->bind(":num_rue",std::string(input_ajout_eleve__num_rue->GetValue().mb_str()));

		req->bind(":code_postal",wxAtoi(input_ajout_eleve__code_postal->GetValue()));
		req->bind(":classe",input_ajout_eleve__classe->GetSelection());
		req->bind(":ville",std::string(input_ajout_eleve__ville->GetValue().mb_str()));
		req->bind(":tel_mobile",std::string(input_ajout_eleve__tel_mobile->GetValue().mb_str()));
		req->bind(":nom_responsable",std::string(input_ajout_eleve__nom_responsable->GetValue().mb_str()));
		req->bind(":prenom_responsable",std::string(input_ajout_eleve__prenom_responsable->GetValue().mb_str()));
		req->bind(":mail_responsable",std::string(input_ajout_eleve__mail_responsable->GetValue().mb_str()));
		req->bind(":tel_responsable",std::string(input_ajout_eleve__tel_responsable->GetValue().mb_str()));
		req->bind(":nom",std::string(input_ajout_nom->GetValue().mb_str()));
		req->bind(":prenom",std::string(input_ajout_prenom->GetValue().mb_str()));
		req->bind(":matricule",matricule_modif);

		if(nessecite_update) req->bind(":matricule_old", matricule);

		req->fetch();
		req->closeCursor();
	}
	else if(type_ajout==ADMIN)
	{
		texte_req=(nessecite_update)?
			"UPDATE admins SET matricule=:matricule,nom=:nom,prenom=:prenom WHERE id=:matricule_old":
			"INSERT INTO admins VALUES (:matricule,:nom,:prenom)";

		req=bdd->prepare(texte_req);

		req->bind(":nom",std::string(input_ajout_nom->GetValue().mb_str()));
		req->bind(":prenom",std::string(input_ajout_prenom->GetValue().mb_str()));
		req->bind(":matricule",matricule_modif);

		if(nessecite_update) req->bind(":matricule_old", matricule);

		req->fetch();
		req->closeCursor();
	}

	if(matricule==-1)
	{
		if(input_radio_matricule_non->GetValue())
			fin<<_T("Le profil a été créé. Son matricule est le : ")<<matricule_modif;
		else
			fin<<_T("Le professeur a été affecté au matricule numéro ")<<matricule_modif<<_(".");
	}
	else
	{
		fin<<_T("Le membre numéro ")<<matricule_modif<<_T(" a bien été modifié ! ");
	}
	wxMessageBox(fin,_T("Succès"));

	this->Close();
}

bool Frame_ajout_modification_membre::valider()
{
	if( (input_ajout_mdp->IsEmpty() || input_ajout_nom->IsEmpty() ||input_ajout_prenom->IsEmpty()) && input_radio_matricule_non->GetValue())
		return false;

	else if( input_ajout_matricule->IsEmpty() && input_radio_matricule_oui->GetValue() )
		return false;

	if(input_radio_admin->GetValue())
		return true;

	if(input_radio_prof->GetValue())
	{
		if(input_ajout_eleve__classe->GetSelection()!=wxNOT_FOUND // si la la classe est correcte
		|| (input_ajout_eleve__classe->GetValue().Cmp(_T("<séléctionner>"))!=0
		&& input_ajout_eleve__classe->GetValue().Cmp(_T(""))!=0))
		{
			if(input_select_matiere_ajout->GetSelection()!=wxNOT_FOUND// si la matiere est correcte
			|| (input_select_matiere_ajout->GetValue().Cmp(_T("<séléctionner>"))!=0
			&& input_select_matiere_ajout->GetValue().Cmp(_T(""))!=0))
				return true;
		}
	}
	else if(input_radio_eleve->GetValue())
	{
		if(input_ajout_eleve__classe->GetSelection()!=wxNOT_FOUND // si la la classe est correcte
		|| (input_ajout_eleve__classe->GetValue().Cmp(_T("<séléctionner>"))!=0
		&& input_ajout_eleve__classe->GetValue().Cmp(_T(""))!=0))
		{
			if(input_ajout_eleve__groupe->GetSelection()!=wxNOT_FOUND && input_ajout_eleve__sexe->GetSelection()!=wxNOT_FOUND)
			{//si le groupe et le sexe ne sont pas vide

				if(!input_ajout_eleve__nom_responsable->IsEmpty() // si les champs ne sont pas vides
				&& !input_ajout_eleve__rue->IsEmpty()
				&& !input_ajout_eleve__num_rue->IsEmpty()
				&& !input_ajout_eleve__code_postal->IsEmpty()
				&& !input_ajout_eleve__ville->IsEmpty()
				&& !input_ajout_eleve__tel_mobile->IsEmpty()
				&& !input_ajout_eleve__nom_responsable->IsEmpty()
				&& !input_ajout_eleve__prenom_responsable->IsEmpty()
				&& !input_ajout_eleve__tel_responsable->IsEmpty()
				&& !input_ajout_eleve__mail_responsable->IsEmpty())
				{
					if(input_ajout_eleve__code_postal->GetValue().length()==5
					&& input_ajout_eleve__tel_mobile->GetValue().length()==10
					&& input_ajout_eleve__tel_responsable->GetValue().length()==10)
					return true;
				}
			}
		}
	}

	return false;
}


int Frame_ajout_modification_membre::getAncienType()
{
	requete_sql* req=bdd->prepare("SELECT type FROM login_centralise WHERE matricule=:matricule");

	req->bind(":matricule",matricule);
	req->fetch();
	int type_tmp=req->getColumn_int(0);
	req->closeCursor();

	return type_tmp;
}



int Frame_ajout_modification_membre::valider_ajouter_login_centralise()
{
	requete_sql* req;
	int type_ajout=-1;
	int retour=-1;

	if(input_radio_prof->GetValue())		type_ajout=PROF;// si c'est un prof
	else if(input_radio_admin->GetValue()) 	type_ajout=ADMIN; // un admin
	else if(input_radio_eleve->GetValue()) 	type_ajout=ELEVE;//un éleve


	if(input_radio_matricule_oui->GetValue())// si on demande a associer le professeur a un matricule existant
	{
		req=bdd->prepare("SELECT count(*) AS nbr, type FROM login_centralise WHERE matricule=:matricule");
		req->bind(":matricule",std::string(input_ajout_matricule->GetValue().mb_str()));
		req->fetch();

		if(req->getColumn_int(0)!=1)
		{
			req->closeCursor();
			wxMessageBox(_T("Erreur ! Ce matricule n'existe pas"));
			return -1;
		}

		if(req->getColumn_int(1)!=type_ajout)
		{
			req->closeCursor();
			wxMessageBox(_T("Erreur ! Le matricule entré n'est pas un professeur"));
			return -1;
		}

		retour=wxAtoi(input_ajout_matricule->GetValue());
		req->closeCursor();

		req=bdd->prepare("SELECT nom, prenom FROM profs WHERE id=?");
		req->bind(1,retour);
		req->fetch();
		input_ajout_nom->SetValue(req->getColumn_text(0));
		input_ajout_prenom->SetValue(req->getColumn_text(1));

		req->closeCursor();
	}
	else
	{
		req=bdd->prepare("INSERT INTO login_centralise (mdp, type) VALUES(:mdp,:type)");
		req->bind(":mdp",std::string(input_ajout_mdp->GetValue().mb_str()));
		req->bind(":type",type_ajout);

		req->fetch();
		req->closeCursor();
		bdd->exec("SELECT last_insert_rowid() AS ligne FROM login_centralise LIMIT 1");
		retour=bdd->getColumn_int(0);
	}

	return retour;
}

void Frame_ajout_modification_membre::supprimer_prof(int id, int classe, int matiere)
{
	int count;
	requete_sql* req;
	req=bdd->prepare("SELECT count(profs.id) FROM profs WHERE id=:matricule AND classe=:classe");//and eleve
	req->bind(":matricule",id);
	req->bind(":classe",classe);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();

	if(count==1)
	{
		req=bdd->prepare("SELECT count(eleves.id) FROM eleves WHERE classe=:classe");
		req->bind(":classe",classe);
		req->fetch();
		count=req->getColumn_int(0);
		req->closeCursor();

		if(count==0)
		{
			//supprimer la classe / supprimer les notes
			req=bdd->prepare("DELETE FROM classes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();

			req=bdd->prepare("DELETE FROM notes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
		}
	}

	req=bdd->prepare("SELECT count(id) FROM profs WHERE matiere=:matiere");
	req->bind(":matiere",matiere);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();

	if(count==1)//supprimer la matiere / supprimer les notes
	{
		req=bdd->prepare("DELETE FROM matieres WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();

		req=bdd->prepare("DELETE FROM notes WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();

		req=bdd->prepare("DELETE FROM commentaires WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();
	}

	req=bdd->prepare("DELETE FROM profs WHERE id=:matricule AND matiere=:matiere AND classe=:classe");
	req->bind(":matricule",id);
	req->bind(":matiere",matiere);
	req->bind(":classe",classe);
	req->fetch();
	req->closeCursor();
}



void Frame_ajout_modification_membre::supprimer_eleve(int id,int classe)
{
	requete_sql* req;
	int count;

	req=bdd->prepare("SELECT count(eleves.id) FROM eleves WHERE classe=:classe");//and eleve
	req->bind(":classe",classe);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();

	if(count==1)
	{
		req=bdd->prepare("SELECT count(profs.id) FROM profs WHERE classe=:classe");
		req->bind(":classe",classe);
		req->fetch();
		count=req->getColumn_int(0);
		req->closeCursor();

		if(count==0)
		{
			//supprimer la classe / supprimer les notes
			req=bdd->prepare("DELETE FROM classes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();

			req=bdd->prepare("DELETE FROM notes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
		}
	}

	req=bdd->prepare("DELETE FROM eleves WHERE id=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();


	req=bdd->prepare("DELETE FROM notes WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();

	req=bdd->prepare("DELETE FROM commentaires WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();

	req=bdd->prepare("DELETE FROM commentaires WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();
}
