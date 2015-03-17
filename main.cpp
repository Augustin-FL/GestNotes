#include <wx/wx.h>
#include <wx/statline.h>

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
		
		
};



Frame_login::Frame_login(const wxString& title) : wxFrame(NULL, wxID_ANY, title,wxDefaultPosition,*(new wxSize(300,210)))
{
	wxPanel         *fenetre					= new wxPanel(this);
	wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL);
	wxStaticText	*texte_explicatif			= new wxStaticText(fenetre, -1, _T("\nVeuillez vous authentifier\npour accéder à votre espace GestNote.\n"));
	wxStaticBoxSizer*conteneur_authentification	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Authentification : "));
	wxBoxSizer		*conteneur_horisontal_login	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		*conteneur_horisontal_mdp 	= new wxBoxSizer(wxHORIZONTAL);
	wxStaticText	*label_login				= new wxStaticText(fenetre, -1, _T("Login : ")); 
	wxTextCtrl		*input_login				= new wxTextCtrl(  fenetre, -1, _T(""));
	wxStaticText	*label_mdp					= new wxStaticText(fenetre, -1, _T("Mot de passe : ")); 
	wxTextCtrl		*input_mdp					= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	wxBoxSizer 		*conteneur_boutons			= new wxBoxSizer(wxHORIZONTAL);
	wxButton 		*bouton_valider 			= new wxButton(    fenetre, -1, _T("Valider"));
	wxButton 		*bouton_annuler 			= new wxButton(    fenetre, -1, _T("Annuler"));
	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	
	contenu_fenetre_sans_marge->Add(texte_explicatif, 			1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	contenu_fenetre_sans_marge->Add(conteneur_authentification, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL , 15);//on met 5px de marge
	conteneur_authentification->Add(conteneur_horisontal_login, 1, wxALIGN_LEFT);
	conteneur_authentification->Add(conteneur_horisontal_mdp,   1, wxALIGN_LEFT);
	
	conteneur_horisontal_login->Add(label_login, 1);
	conteneur_horisontal_login->Add(input_login, 1);
	conteneur_horisontal_mdp->Add(label_mdp, 1);
	conteneur_horisontal_mdp->Add(input_mdp, 1);
	
	contenu_fenetre_sans_marge->Add(conteneur_boutons,1, wxTOP|wxALIGN_CENTER_HORIZONTAL,5);
	
	conteneur_boutons->Add(bouton_valider,1);
	conteneur_boutons->Add(bouton_annuler,1);
	/*
			Connect(ID_BTN_VALIDER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnClick_Valider));
			Connect(ID_BTN_ANNULER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnClick_Annuler));
	*/		
}
bool App_GestNote::OnInit()
{
	Frame_login *login=new Frame_login(_T("GestNote"));
	login->Show();
 
    return true;
}
               
