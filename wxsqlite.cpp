#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#ifdef __GNUG__
    #pragma implementation "wxsqlite.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sqlite.h"
#include "wx/wxsqlite.h"
#include "wx/dynlib.h"
#include "wx/log.h"

// function prototypes
typedef const char *(*Tsqlite_libversion)(void);
typedef void (*Tsqlite_freemem)(void *p);
typedef sqlite *(*Tsqlite_open)(const char *filename, int mode, char **errmsg);
typedef void (*Tsqlite_close)(sqlite *);
typedef int (*Tsqlite_finalize)(sqlite_vm*, char **pzErrMsg);
typedef int (*Tsqlite_compile)(sqlite *db, const char *zSql, const char **pzTail, sqlite_vm **ppVm, char **pzErrmsg);
typedef int (*Tsqlite_step)(sqlite_vm *pVm, int *pN, const char ***pazValue, const char ***pazColName);
typedef void (*Tsqlite_free_table)(char **result);
typedef int (*Tsqlite_get_table_vprintf)(sqlite*, const char *sqlFormat, char ***resultp, int *nrow, int *ncolumn, char **errmsg, va_list ap);
typedef int (*Tsqlite_changes)(sqlite*);
typedef char *(*Tsqlite_vmprintf)(const char* format, va_list va);
typedef int (*Tsqlite_last_insert_rowid)(sqlite*);
// experimental
typedef int (*Tsqlite_bind)(sqlite_vm*, int idx, const char *value, int len, int copy);
typedef int (*Tsqlite_reset)(sqlite_vm*, char **pzErrMsg);

static wxDynamicLibrary				s_dll;
static Tsqlite_libversion			s_sqlite_libversion = NULL;
static Tsqlite_freemem				s_sqlite_freemem = NULL;
static Tsqlite_open					s_sqlite_open = NULL;
static Tsqlite_close				s_sqlite_close = NULL;
static Tsqlite_finalize				s_sqlite_finalize = NULL;
static Tsqlite_compile				s_sqlite_compile = NULL;
static Tsqlite_step					s_sqlite_step = NULL;
static Tsqlite_free_table			s_sqlite_free_table = NULL;
static Tsqlite_get_table_vprintf	s_sqlite_get_table_vprintf = NULL;
static Tsqlite_changes				s_sqlite_changes = NULL;
static Tsqlite_vmprintf				s_sqlite_vmprintf = NULL;
static Tsqlite_last_insert_rowid	s_sqlite_last_insert_rowid = NULL;
// experimental
static Tsqlite_bind                 s_sqlite_bind = NULL;
static Tsqlite_reset                s_sqlite_reset = NULL;

#define GET_PROC(proc)\
	s_##proc = (T##proc) s_dll.GetSymbol(wxT(#proc));\
	if (! s_##proc)\
	{\
		s_dll.Unload();\
		throw wxSQLiteException(wxT("error getting symbol <") wxT(#proc) wxT(">"));\
	}

#define GET_PROC_NOEX(proc)\
	s_##proc = (T##proc) s_dll.GetSymbol(wxT(#proc))

static void InitDLL()
{
	if (s_dll.IsLoaded())
		return;

#ifdef __WIN32__
	if (! s_dll.Load(wxT("sqlite")))
		throw wxSQLiteException(wxT("error loading dynamic library"));
#else
	if (! s_dll.Load(wxT("libsqlite")))
		throw wxSQLiteException(wxT("error loading dynamic library"));
#endif

	// get procs
	GET_PROC(sqlite_libversion);
	GET_PROC(sqlite_freemem);
	GET_PROC(sqlite_open);
	GET_PROC(sqlite_close);
	GET_PROC(sqlite_finalize);
	GET_PROC(sqlite_compile);
	GET_PROC(sqlite_step);
	GET_PROC(sqlite_free_table);
	GET_PROC(sqlite_get_table_vprintf);
	GET_PROC(sqlite_changes);
	GET_PROC(sqlite_vmprintf);
	GET_PROC(sqlite_last_insert_rowid);

    // experimental
	GET_PROC_NOEX(sqlite_bind);
	GET_PROC_NOEX(sqlite_reset);
};


const char *wxsqlite_libversion(void)
{
	InitDLL();

	return s_sqlite_libversion();
};

void wxsqlite_freemem(void *p)
{
	InitDLL();

	s_sqlite_freemem(p);
};

sqlite *wxsqlite_open(const char *filename, int mode, char **errmsg)
{
	InitDLL();

	return s_sqlite_open(filename, mode, errmsg);

};

void wxsqlite_close(sqlite *s)
{
	InitDLL();

	s_sqlite_close(s);
};

int wxsqlite_finalize(sqlite_vm* vm, char **pzErrMsg)
{
	InitDLL();

	return s_sqlite_finalize(vm, pzErrMsg);

};

int wxsqlite_compile(sqlite *db, const char *zSql, const char **pzTail, sqlite_vm **ppVm, char **pzErrmsg)
{
	InitDLL();

	return s_sqlite_compile(db, zSql, pzTail, ppVm, pzErrmsg);
};

int wxsqlite_step(sqlite_vm *pVm, int *pN, const char ***pazValue, const char ***pazColName)
{
	InitDLL();

	return s_sqlite_step(pVm, pN, pazValue, pazColName);
};

void wxsqlite_free_table(char **result)
{
	InitDLL();

	s_sqlite_free_table(result);
};

int wxsqlite_get_table_vprintf(sqlite* sq, const char *sqlFormat, char ***resultp, int *nrow, int *ncolumn, char **errmsg, va_list ap)
{
	InitDLL();

	return s_sqlite_get_table_vprintf(sq, sqlFormat, resultp, nrow, ncolumn, errmsg, ap);
};

int wxsqlite_changes(sqlite* sq)
{
	InitDLL();

	return s_sqlite_changes(sq);

};

char *wxsqlite_vmprintf(const char* format, va_list va)
{
	InitDLL();

	return s_sqlite_vmprintf(format, va);
};


int wxsqlite_last_insert_rowid(sqlite* db)
{
	InitDLL();

	return s_sqlite_last_insert_rowid(db);
};

// experimental
int wxsqlite_bind(sqlite_vm* db, int idx, const char *value, int len, int copy)
{
	InitDLL();

    if (! s_sqlite_bind)
    {
        wxLogWarning(wxT("Experimental api sqlite_bind not found"));
        return SQLITE_MISUSE;
    }
    else
    	return s_sqlite_bind(db, idx, value, len, copy);
};

int wxsqlite_reset(sqlite_vm* db, char **pzErrMsg)
{
	InitDLL();

    if (! s_sqlite_reset)
    {
        wxLogWarning(wxT("Experimental api sqlite_reset not found"));
        return SQLITE_MISUSE;
    }
    else
    	return s_sqlite_reset(db, pzErrMsg);
};

const char *wxSQLiteVersion()
{
	return wxsqlite_libversion();
};


//////////////////////////////////////////////////////
class wxSQLiteDatabaseLocker
{
private:
    wxSQLiteDatabase&        m_DB;
    wxCriticalSectionLocker  cs;

public:
    wxSQLiteDatabaseLocker(wxSQLiteDatabase& DB);
    ~wxSQLiteDatabaseLocker();

    sqlite *GetDB();
};


wxSQLiteDatabase::wxSQLiteDatabase(wxString fname) :
	db(NULL), m_lastIErr(SQLITE_OK)
{
	if (fname != wxT(""))
		Open(fname);
};

wxSQLiteDatabase::~wxSQLiteDatabase()
{
	Close();
};

bool wxSQLiteDatabase::Open(wxString fname)
{
	Close();
	char *errmsg = NULL;


    {
        wxSQLiteDatabaseLocker locker(*this);
	    db = wxsqlite_open(fname.mb_str(), 0, &errmsg);
    };

	if (! db)
	{
		if (errmsg)
		{
			m_lastErr = wxString(errmsg, wxConvUTF8);
            wxSQLiteDatabaseLocker locker(*this);
			wxsqlite_freemem(errmsg);
		};
		return false;
	};

	return true;
};

bool wxSQLiteDatabase::Close()
{
	if (db)
    {
        wxSQLiteDatabaseLocker locker(*this);
		wxsqlite_close(db);
	
    	db = NULL;
    };

	return true;
};


bool wxSQLiteDatabase::TableExists(wxString tableName)
{
	wxString sql;

	// quote type = 'table' using %Q because I dislike using escape sequences in strings
	sql << "SELECT count(name) FROM sqlite_master WHERE ((type = %Q) and (name = %Q))";


	wxSQLiteQueryResult q(*this);

	if (! q.Execute(sql, "table", (const char *) tableName))
		throw wxSQLiteException(q.m_lastErr);

	return q.Fields(0, 0).AsLong() != 0;
};

void wxSQLiteDatabase::BeginTransaction()
{
	wxSQLiteQueryResult q(*this);

	if (! q.Execute("BEGIN TRANSACTION;"))
		throw wxSQLiteException(q);
};

void wxSQLiteDatabase::Commit()
{
	wxSQLiteQueryResult q(*this);

	if (! q.Execute("COMMIT TRANSACTION;"))
		throw wxSQLiteException(q);
};

void wxSQLiteDatabase::Rollback()
{
	wxSQLiteQueryResult q(*this);

	if (! q.Execute("ROLLBACK TRANSACTION;"))
		throw wxSQLiteException(q);
};

int wxSQLiteDatabase::LastInsertRowId()
{
	if (db)
		return wxsqlite_last_insert_rowid(db);
	else
		return -1;
};


wxSQLiteDatabaseLocker::wxSQLiteDatabaseLocker(wxSQLiteDatabase& DB) :
    m_DB(DB), cs(DB.csDB)
{
};

wxSQLiteDatabaseLocker::~wxSQLiteDatabaseLocker()
{
};

sqlite *wxSQLiteDatabaseLocker::GetDB()
{
    return m_DB.db;
};

wxSQLiteQueryBase::wxSQLiteQueryBase(wxSQLiteDatabase& db) :
	db(db), m_lastIErr(SQLITE_OK)
{
};

void wxSQLiteQueryBase::InitCols(const char **pazColNames, int ncols)
{
	colNames.clear();
	for (int i = 0; i < ncols; i++)
	{
		wxString name = wxString(pazColNames[i], wxConvUTF8);
		name.MakeLower();
		colNames[name] = i;
	};
};

// returns -1 if not found
int wxSQLiteQueryBase::GetFieldIndex(wxString fieldName)
{
	fieldName.MakeLower();
	ColNamesMap::iterator it = colNames.find(fieldName);
	if (it == colNames.end())
		return -1;
	
	return it->second;
};

const char * wxSQLiteQueryBase::TField::AsChar() const
{
    return data;
};

wxString wxSQLiteQueryBase::TField::AsString() const
{
    return wxString(data, wxConvUTF8);
};

long wxSQLiteQueryBase::TField::AsLong() const
{
    return atol(data);
};

bool wxSQLiteQueryBase::TField::AsBool() const
{
    return AsLong() != 0;
};

wxDateTime wxSQLiteQueryBase::TField::AsDate() const
{
    time_t t = AsLong();
    return t;
};

wxSQLiteQuery::wxSQLiteQuery(wxSQLiteDatabase& db) : 
	wxSQLiteQueryBase(db),
    pVm(NULL),
	ncol(-1), pazValue(NULL), pazColName(NULL)
{
}

wxSQLiteQuery::~wxSQLiteQuery()
{
	Close();
};


void wxSQLiteQuery::Close()
{
	if (! pVm)
		return;

    m_lastErr = wxT("");
	char *pzErrMsg = NULL;
	m_lastIErr = wxsqlite_finalize(pVm, &pzErrMsg);
	if (m_lastIErr != SQLITE_OK)
	{
		if (pzErrMsg)
		{
			m_lastErr = wxString(pzErrMsg, wxConvUTF8);
			wxsqlite_freemem(pzErrMsg);
		};

		throw wxSQLiteException(*this);
	};

	pVm = NULL;
};

void wxSQLiteQuery::Prepare(const char *sqlstr, va_list args)
{
	Close();

    m_lastErr = wxT("");

	const char *pzTail = NULL;  /* OUT: Part of zSQL not compiled */
	char *pzErrMsg = NULL;

	char *sql = wxsqlite_vmprintf(sqlstr, args);


	wxSQLiteDatabaseLocker dbl(db);

	m_lastIErr = wxsqlite_compile(dbl.GetDB(), sql, &pzTail, &pVm, &pzErrMsg);
	wxsqlite_freemem(sql);

	if (m_lastIErr != SQLITE_OK)
	{
		if (pzErrMsg)
		{
			m_lastErr = wxString(pzErrMsg, wxConvUTF8);
			wxsqlite_freemem(pzErrMsg);
		};

		throw wxSQLiteException(*this);
	}
};

void wxSQLiteQuery::Prepare(const char *sqlstr, ...)
{
	va_list args;
	va_start(args, sqlstr);

	try
	{
		Prepare(sqlstr, args);
	}
	catch (...)
	{
		va_end(args);
		throw;
	};

	va_end(args);
};

void wxSQLiteQuery::Exec()
{
	int nc = 0;
	m_lastIErr = wxsqlite_step(pVm, &nc, &pazValue, &pazColName);

	if (nc != ncol)
	{
		ncol = nc;
		InitCols(pazColName, ncol);
	};

	if (m_lastIErr == SQLITE_ROW || m_lastIErr == SQLITE_DONE)
		Reset();
	else
		throw wxSQLiteException(*this);
};

void wxSQLiteQuery::Execute(const char *sqlstr, ...)
{
	va_list args;
	va_start(args, sqlstr);

	try
	{
		Prepare(sqlstr, args);
	}
	catch (...)
	{
		va_end(args);
		throw;
	};

	va_end(args);

	Fetch();
};

void wxSQLiteQuery::Bind(int idx, const char *value, int len, bool copy)
{
    int icopy = (copy ? TRUE : FALSE);
    m_lastIErr = wxsqlite_bind(pVm, idx, value, len, icopy);

    if (m_lastIErr != SQLITE_OK)
		throw wxSQLiteException(*this);
};

void wxSQLiteQuery::Reset()
{
    m_lastErr = wxT("");
	char *pzErrMsg = NULL;
    m_lastIErr = wxsqlite_reset(pVm, &pzErrMsg);

    if (m_lastIErr != SQLITE_OK)
	{
		if (pzErrMsg)
		{
			m_lastErr = wxString(pzErrMsg, wxConvUTF8);
			wxsqlite_freemem(pzErrMsg);
		};

		throw wxSQLiteException(*this);
	}
};

bool wxSQLiteQuery::eof() const
{
	return pVm == NULL;
};

bool wxSQLiteQuery::Fetch()
{
	int nc = 0;
	m_lastIErr = wxsqlite_step(pVm, &nc, &pazValue, &pazColName);

	if (nc != ncol)
	{
		ncol = nc;
		InitCols(pazColName, ncol);
	};

	if (m_lastIErr == SQLITE_ROW)
		return true;
	else
	{
		Close();
		return false;
	};
};


int wxSQLiteQuery::NumFields() const
{
    return ncol;
};

const char *wxSQLiteQuery::GetFieldName(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncol);
    wxASSERT(pazColName != NULL);

    return pazColName[fieldIdx];
};

wxSQLiteQueryBase::TField wxSQLiteQuery::Fields(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncol);
    wxASSERT(pazValue != NULL);

    return TField(pazValue[fieldIdx]);
};

// raise exception if not found
wxSQLiteQueryBase::TField wxSQLiteQuery::FieldByName(wxString fieldName)
{
	int idx = GetFieldIndex(fieldName);
	if (idx < 0)
	{
		wxString err;
		err.Printf(wxT("Unknown field name <%s>"), fieldName.c_str());
		throw wxSQLiteException(err);
	};

	return Fields(idx);
};


////////////////////////////////////////////////

wxSQLiteQueryResult::wxSQLiteQueryResult(wxSQLiteDatabase& db) :
    wxSQLiteQueryBase(db),
    result(NULL), nrow(0), ncolumn(0)
{
};

wxSQLiteQueryResult::~wxSQLiteQueryResult()
{
    wxsqlite_free_table(result);
};

bool wxSQLiteQueryResult::Execute(const char *sql, ...)
{
    wxsqlite_free_table(result);
    m_lastErr = wxT("");
    char *errmsg = NULL;

    va_list args;

    va_start(args, sql);
    m_lastIErr = SQLITE_ERROR;

    {
        wxSQLiteDatabaseLocker locker(db);
        m_lastIErr = wxsqlite_get_table_vprintf(locker.GetDB(), sql, &result, &nrow, &ncolumn, &errmsg, args);
    };

    va_end(args);

    if (m_lastIErr != SQLITE_OK)
    {
        if (errmsg)
        {
            m_lastErr = wxString(errmsg, wxConvUTF8);
            wxSQLiteDatabaseLocker locker(db);
            wxsqlite_freemem(errmsg);
        };

        return false;
    };

	InitCols((const char **) result, ncolumn);

    return true;
};

int wxSQLiteQueryResult::NumChanges()
{
    wxSQLiteDatabaseLocker locker(db);

    return wxsqlite_changes(locker.GetDB());
};

int wxSQLiteQueryResult::NumRows()
{
    return nrow;
};

int wxSQLiteQueryResult::NumCols()
{
    return ncolumn;
};

char *wxSQLiteQueryResult::GetFieldName(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncolumn);
    wxASSERT(result != NULL);

    return result[fieldIdx];
};

wxSQLiteQueryBase::TField wxSQLiteQueryResult::Fields(int rowIdx, int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncolumn);
    wxASSERT(result != NULL);
    wxASSERT(rowIdx >= 0 && rowIdx < nrow);

    return TField(result[(rowIdx + 1) * ncolumn + fieldIdx]);
};

// raise exception if not found
wxSQLiteQueryBase::TField wxSQLiteQueryResult::FieldByName(int rowIdx, wxString fieldName)
{
	int idx = GetFieldIndex(fieldName);
	if (idx < 0)
	{
		wxString err;
		err.Printf(wxT("Unknown field name <%s>"), fieldName.c_str());
		throw wxSQLiteException(err);
	};

	return Fields(rowIdx, idx);
};
