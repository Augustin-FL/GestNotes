#include "main.h"


wxTextRegexpValidator::wxTextRegexpValidator(wxString regexp, wxString* pointeur) : m_regEx(regexp)//constructeur : création d'un wxValidator
{
   m_stringValue = pointeur;
   m_regexp_texte = regexp;
}

wxObject* wxTextRegexpValidator::Clone() const // le constructeur de clonage
{
   return new wxTextRegexpValidator(m_regexp_texte, m_stringValue);
}

bool wxTextRegexpValidator::TransferToWindow()//la validation.
{
   if (m_stringValue == NULL)
      return true;

   if (m_regEx.Matches(*m_stringValue))
      return wxTextValidator::TransferToWindow();
   
   return false;
}

bool wxTextRegexpValidator::TransferFromWindow()//la validation.
{
   wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
   wxString tmp = control->GetValue();

   if (m_regEx.Matches(tmp))
      return wxTextRegexpValidator::TransferFromWindow();

    return false;
}





