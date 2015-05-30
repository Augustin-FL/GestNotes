#include "main.h"

#ifndef __WXMSW__
	#include "ressources.xpm"//ressources linux
#endif



Frame_imprimer_buletins::Frame_imprimer_buletins(wxWindow* parent_arg, connexion_bdd*& bdd_arg) : wxFrame(parent_arg, wxID_ANY,_T("GestNotes - Buletin scolaire"),wxDefaultPosition,wxSize(610,510))
{
	parent=parent_arg;
	bdd=bdd_arg;
	wxPanel *fenetre=new wxPanel(this);
	wxBoxSizer *sizer_principal=new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_haut= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_haut_doite= new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *sizer_haut_centre= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_bas= new wxBoxSizer(wxVERTICAL);
	wxButton *imprimer=new wxButton(fenetre, -1, _T("Imprimer"));
	wxButton *enregistrer=new wxButton(fenetre, -1, _T("Enregistrer Sous"));
	
	this->generer_html5();
	
	fenetre_html = wxWebView::New(fenetre, wxID_ANY, wxWebViewDefaultURLStr,wxDefaultPosition, wxSize(50,50));
	fenetre_html->RegisterHandler( wxSharedPtr<wxWebViewHandler>(new wxWebViewFSHandler( "memory" )));
	fenetre_html->LoadURL("memory:dialog.html");
	 wxMemoryFSHandler::RemoveFile( "dialog.html" );
	
	sizer_haut_doite->Add(enregistrer);
	sizer_haut_centre->Add(imprimer);
	
	imprimer->Bind(   wxEVT_BUTTON, &Frame_imprimer_buletins::onImprimer,    this);
	enregistrer->Bind(wxEVT_BUTTON, &Frame_imprimer_buletins::onEnregistrer, this);
	
	sizer_haut->Add(sizer_haut_doite,1,wxALIGN_LEFT);
	sizer_haut->Add(sizer_haut_centre,1,wxALIGN_CENTER);
	sizer_bas->Add(fenetre_html,1),
	
	sizer_principal->Add(sizer_haut,0,wxEXPAND|wxTOP, 5);
	sizer_principal->Add(sizer_bas,1,wxEXPAND|wxTOP, 10);
	
	fenetre->SetSizer(sizer_principal);
	this->Show();
}
void Frame_imprimer_buletins::onImprimer(wxCommandEvent& evenement)
{
	fenetre_html->Print();
}

void Frame_imprimer_buletins::onEnregistrer(wxCommandEvent& evenement)
{
    wxFileDialog* selection_emplacement=new wxFileDialog(this, _("Sauvegarder le buletin"), "", "", "Fichier HTML (*.html)|*.html", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
   
   if (selection_emplacement->ShowModal() == wxID_CANCEL) return;    //si l'utilisateur annule
    
    wxFileOutputStream output_stream(selection_emplacement->GetPath());
    if (!output_stream.IsOk())
    {
        wxMessageBox("Erreur : impossible de Sauvegarder à cet emplacement !");
        return;
    }
	
	wxString html=this->generer_html5();
	output_stream.Write(html,html.Length());
	output_stream.Close();
}



wxString Frame_imprimer_buletins::generer_html5()
{
	wxString html=
	"<html>																															\
\n	<head>																															\
\n		<title>																														\
\n			Buletin Scolaire																										\
\n		</title>																													\
\n 		<meta charset=\"utf-8\">																									\
\n		<style type=\"text/css\">																									\
\n			p,footer																												\
\n			{																														\
\n				font-size:8pt;																										\
\n				line-height:107%;																									\
\n				font-family:Arial,sans-serif;																						\
\n			}																														\
\n			td																														\
\n			{																														\
\n				height:9.9pt;																										\
\n				border:solid black 1.0pt;																							\
\n			}																														\
\n			table																													\
\n			{																														\
\n				border-collapse:collapse;																							\
\n			}																														\
\n			.min_moy_max td																											\
\n			{																														\
\n				vertical-align:top;																									\
\n				width:22.7pt;																										\
\n				padding:1.9pt 4.75pt 0 0;																							\
\n			}																														\
\n			.min_moy_max p																											\
\n			{																														\
\n				margin:2.85pt 0 0 0;																								\
\n				text-align:center;																									\
\n			}																														\
\n			.moyenne_generale td																									\
\n			{																														\
\n				padding:1.9pt 4.75pt 0 0;																							\
\n			}																														\
\n			.moyenne_generale p																										\
\n			{																														\
\n				margin:0 0 0 2.85pt;																								\
\n				font-size:7.0pt;																									\
\n				text-align:center;																									\
\n			}																														\
\n			.moyenne																												\
\n			{																														\
\n				font-weight:bold;																									\
\n			}																														\
\n			.header_info_eleve																										\
\n			{																														\
\n				margin-bottom:1.4pt;																								\
\n			}																														\
\n			.headers_table																											\
\n			{																														\
\n				padding:1.9pt 4.75pt 0 0;																							\
\n			}																														\
\n			.nom_matiere																											\
\n			{																														\
\n				margin:1.9pt 0 17.6pt 1.4pt;																						\
\n				font-weight:bold;																									\
\n			}																														\
\n			.nom_prof																												\
\n			{																														\
\n				margin:0 0 0 3.85pt;																								\
\n				font-style:italic;																									\
\n			}																														\
\n			.entete_nouvelle_ligne																									\
\n			{																														\
\n				vertical-align:top;																									\
\n				height:36.85pt;																										\
\n			}																														\
\n			#header																													\
\n			{																														\
\n				border-collapse:collapse;																							\
\n				margin-bottom:4.55pt;																								\
\n				font-size:13.0pt;																									\
\n				text-align:center;																									\
\n				font-weight:bold;																									\
\n 				line-height:107%;																									\
\n				border:solid black 1.0pt;																							\
\n				font-family:Arial,sans-serif;																						\
\n			}																														\
\n			#appreciation_generale																									\
\n			{																														\
\n				width:100%;height:75.0pt;																							\
\n				border-collapse:collapse;																							\
\n				border:solid black 1.0pt;																							\
\n				margin-top:15pt;																									\
\n				position:relative;																									\
\n			}																														\
\n		</style>																													\
\n	</head>																															\
\n	<body>																															\
\n		<header id=\"header\">																										\
\n			Bulletin de notes du 1er trimestre de l'année scolaire 2014-2015														\
\n		</header>																													\
\n																																	\
\n		<aside style=\"float:right\">																									\
\n			<p style=\"padding-left:100pt;font-weight:bold;font-size:12.0pt;\">														\
\n				NOM5 PRÉNOM5																										\
\n			</p>																													\
\n																																	\
\n																																	\
\n			<p class=\"header_info_eleve\">																							\
\n				Date d'inscription à GestNotes : 05 juin 1987																		\
\n			</p>																													\
\n																																	\
\n																																	\
\n			<p class=\"header_info_eleve\">																							\
\n				Classe : 1èreS																										\
\n			</p>																													\
\n																																	\
\n																																	\
\n			<p class=\"header_info_eleve\">																							\
\n			Effectif de la classe : 1 élève																							\
\n			</p>																													\
\n																																	\
\n			<table style=\"width:275pt;\">																							\
\n				<tr>																												\
\n					<td style=\"padding:0cm 5.75pt 17.35pt 31.2pt;height:96.4pt;\">													\
\n																																	\
\n						<span style=\"font-size:12.0pt;font-weight:bold;\">															\
\n							M. et Mme NOM R5<br />																					\
\n						</span>																										\
\n						<span style=\"font-size:11.0pt;\">																			\
\n							Adresse R5																								\
\n						</span>																										\
\n																																	\
\n						<span style=\"font-size:12.0pt;\">																			\
\n								R5R5R Ville R5																						\
\n						</span>																										\
\n																																	\
\n					</td>																											\
\n				</tr>																												\
\n			</table>																												\
\n		</aside>																													\
\n																																	\
\n		<div style=\"clear:both;padding-top:10pt;\"></div>																			\
\n																																	\
\n		<table style=\"width:100%;\">																								\
\n			<tr >																													\
\n				<td class=\"headers_table\" rowspan=\"2\" style=\"width:110.9pt;\">													\
\n					<p style=\"margin:0 0 0 2.85pt;font-weight:bold;\">																\
\n						Matières																									\
\n					</p>																											\
\n																																	\
\n					<p style=\"margin:0 0 0 3.85pt;font-style:italic\">																\
\n						Enseignants																									\
\n					</p>																											\
\n				</td>																												\
\n																																	\
\n				<td rowspan=\"2\" class=\"headers_table\" style=\"vertical-align:top;width:1cm;\">									\
\n																																	\
\n					<p style=\"margin:5pt 0 0 0;text-align:center\">																\
\n						Moy.																										\
\n						élève																										\
\n					</p>																											\
\n				</td>																												\
\n				<td colspan=\"3\" style=\"width:68.05pt;padding:1.9pt 4.75pt 0 0;\">												\
\n					<p style=\"margin:0 0 0 2.85pt;text-align:center;\">															\
\n						Moyenne Classe																								\
\n					</p>																											\
\n				</td>																												\
\n				<td rowspan=\"2\" style=\"vertical-align:top;width:297.65pt;padding:1.9pt 4.75pt 0 0\">								\
\n																																	\
\n					<p style=\"margin:3.5pt 0 0 60pt;font-weight:bold;\">															\
\n						APPRÉCIATIONS DES ENSEIGNANTS																				\
\n					</p>																											\
\n				</td>																												\
\n			</tr>																													\
\n																																	\
\n			<tr class=\"min_moy_max\">																								\
\n				<td>																												\
\n					<p>																												\
\n						Min																											\
\n					</p>																											\
\n				</td>																												\
\n				<td>																												\
\n					<p>																												\
\n						Moy																											\
\n					</p>																											\
\n				</td>																												\
\n				<td>																												\
\n					<p>																												\
\n						Max																											\
\n					</p>																											\
\n				</td>																												\
\n			</tr>																													\
\n																																	\
\n			<!--matiere : -->																										\
\n	";
	bool a=true;
			
	while(a)
	{
		a=false;	
			
			html+=
			"<tr>																													\
				<td class=\"entete_nouvelle_ligne\">																				\
\n					<p class=\"nom_matiere\">																						\
\n						Mathématiques (TD)																							\
\n					</p>																											\
\n					<p class=\"nom_prof\">																							\
\n						M. Cosinus																									\
\n					</p>																											\
\n				</td>																												\
\n																																	\
\n																																	\
\n																																	\
\n				<td class=\"min_moy_max moyenne\">																					\
\n					<p>																												\
\n						14																											\
\n					</p>																											\
\n				</td>																												\
\n																																	\
\n				<td class=\"min_moy_max\">																							\
\n					<p>																												\
\n						14																											\
\n					</p>																											\
\n				</td>																												\
\n				<td class=\"min_moy_max\">																							\
\n					<p>																												\
\n						14																											\
\n					</p>																											\
\n				</td>																												\
\n				<td class=\"min_moy_max\">																							\
\n					<p>																												\
\n						14																											\
\n					</p>																											\
\n				</td>																												\
\n																																	\
\n				<td style=\"padding:1.9pt 4.75pt 0 0;\">																			\
\n					<p style=\"margin:0 0 0 2.85pt;\">																				\
\n						Bilan positif, bon travail.																					\
\n					</p>																											\
\n				</td>																												\
\n			</tr>																													\
\n		";
	}
	
	html+=
	"<tr class=\"moyenne_generale\">																								\
\n				<td style=\"vertical-align:top;padding:1.9pt 4.75pt 0 0;\">															\
\n					<p style=\"margin:0 0 0 2.85pt;font-size:8pt;text-align:left;\">												\
\n						Moyenne générale																							\
\n					</p>																											\
\n				</td>																												\
\n				<td class=\"moyenne\">																								\
\n					<p>																												\
\n						12,4																										\
\n					</p>																											\
\n				</td>																												\
\n				<td>																												\
\n					<p>																												\
\n						8,5																											\
\n					</p>																											\
\n				</td>																												\
\n																																	\
\n				<td>																												\
\n					<p>																												\
\n						12,4																										\
\n					</p>																											\
\n				</td>																												\
\n				<td>																												\
\n					<p>																												\
\n						14																											\
\n					</p>																											\
\n				</td>																												\
\n				<td style=\"display:none;\">																						\
\n				</td>																												\
\n		 </tr>																														\
\n		</table>";
		
		html+="																														\
\n		<div id=\"appreciation_generale\">																							\
\n			<div style=\"margin:0 0 0 6.5pt;\">																						\
\n				<p style=\"font-weight:bold\">																						\
\n					Appréciation de l'équipe pédagogique :																			\
\n				</p>  																												\
\n				<p style=\"margin:20pt 0 0 6.5pt;\">																				\
\n					test																											\
\n				</p>																												\
\n			</div>																													\
\n																																	\
\n			<p style=\"float:right;position:absolute;bottom:15pt;right:30pt;\">														\
\n			  Le proviseur																											\
\n			</p>																													\
\n																																	\
\n		</div>																														\
\n																																	\
\n		<footer style=\"margin-top:15pt;font-size:6pt;\">																			\
\n			ATTENTION : Ce bulletin est un original, il doit être conservé par la famille.<br/> © GestNotes 2014-2015				\
\n		</footer>																													\
\n	</body>																															\
\n</html>																															\
";	
	wxMemoryFSHandler::AddFile("dialog.html",html);
	return html;
}