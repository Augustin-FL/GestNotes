#include <wx/wx.h>
#include <wx/statline.h>
#include <SQLite/sqlite3.h>

class App_GestNote : public wxApp
{
	public :
		
	virtual bool OnInit();
	
};
DECLARE_APP(App_GestNote);
IMPLEMENT_APP(App_GestNote);


class Frame_login : public wxFrame
{
    public:
		Frame_login(const wxString& title);
        virtual ~Frame_login(){};
	private:
		wxTextCtrl *input_login,*input_mdp;
		wxButton *bouton_valider, *bouton_annuler;
		
		void onClick_valider(wxCommandEvent &evenement);
		void onClick_annuler(wxCommandEvent &evenement);
		void onChange(wxCommandEvent &evenement);
		
};



Frame_login::Frame_login(const wxString& titre) : wxFrame(NULL, wxID_ANY, titre,wxDefaultPosition,*(new wxSize(300,220)))
{
	wxPanel         *fenetre					= new wxPanel(this);
	wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer		*conteneur_horisontal_login	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		*conteneur_horisontal_mdp 	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer 		*conteneur_boutons			= new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText	*texte_explicatif			= new wxStaticText(fenetre, -1, _T("\nVeuillez vous authentifier\npour accéder à votre espace GestNote.\n"));
	wxStaticBoxSizer*conteneur_authentification	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Authentification : "));
	
	wxStaticText	*label_login				= new wxStaticText(fenetre, -1, _T("Login : ")); 				
	wxStaticText	*label_mdp					= new wxStaticText(fenetre, -1, _T("Mot de passe : ")); 				
	
	bouton_valider	= new wxButton(    fenetre, -1, _T("Valider"));
	bouton_annuler 	= new wxButton(    fenetre, -1, _T("Quitter"));
	input_mdp		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	input_login		= new wxTextCtrl(  fenetre, -1, _T(""));
	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	
	contenu_fenetre_sans_marge->Add(texte_explicatif, 			1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);//la fenetre contient : 
	contenu_fenetre_sans_marge->Add(conteneur_authentification, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);//un texte explicatif, la zone de
	contenu_fenetre_sans_marge->Add(conteneur_boutons, 			1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 10);//login, et les boutons
	
	conteneur_authentification->Add(conteneur_horisontal_login, 1, wxALIGN_LEFT|wxDOWN,5);//on dit que la zone d'authentification contient 
	conteneur_authentification->Add(conteneur_horisontal_mdp,   1, wxALIGN_LEFT);//un login et un mot de passe
	
	conteneur_horisontal_login->Add(label_login, 1);//la zone login contient un label pour le login, et un champ d'input.
	conteneur_horisontal_login->Add(input_login, 1);
	conteneur_horisontal_mdp->Add(label_mdp, 1);
	conteneur_horisontal_mdp->Add(input_mdp, 1);
	
	conteneur_boutons->Add(bouton_valider,1);//et il y a 2 boutons : valider et annuler
	conteneur_boutons->Add(bouton_annuler,1);
	bouton_valider->Disable();
	
	bouton_valider->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame_login::onClick_valider), NULL, this);
	bouton_annuler->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame_login::onClick_annuler), NULL, this);
	input_login->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frame_login::onChange), NULL, this);
	input_mdp->Connect(   wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frame_login::onChange), NULL, this);

	
}

void Frame_login::onChange(wxCommandEvent &evenement)
{
	if(input_login->IsEmpty() ||input_mdp->IsEmpty()) bouton_valider->Disable();
	else bouton_valider->Enable();	
}

void Frame_login::onClick_valider(wxCommandEvent &evenement)
{
    Hide();
    wxString message= input_login->GetValue() << _T(" ") << input_mdp->GetValue();
    
	
    wxMessageBox(message, _("Récapitulatif"));

    Close();
}

void Frame_login::onClick_annuler(wxCommandEvent &evenement)
{
    int reponse=wxMessageBox(_T("Voulez vous vraiment quitter?"), _T("Quitter"), wxYES_NO | wxCANCEL);
	if (reponse == wxYES) Close();
}

bool App_GestNote::OnInit()
{
	Frame_login *login=new Frame_login(_T("GestNote"));
	login->Show();
	
	
 
    return true;
}
               
