#ifndef __BHJLIB_H__
#define __BHJLIB_H__
#pragma warning( disable : 4786 )
#define BOOST_THREAD_USE_DLL
#include <map>
#include <list>
#include <string>
#include <vector>

extern "C" int strncasecmp(const char *s1, const char *s2, size_t n);
extern "C" char *strcasestr(const char *S, const char *FIND);

namespace bhj {
	using std::list;
	using std::string;
	using std::wstring;
	using std::vector;

	
	class cstring : public string {
	public:
		cstring() {};
		cstring(const CString&);
		cstring(const string& str) : string(str) {};
		cstring(const char* c_str) : string(c_str) {};
		operator CString() const;
		operator wstring() const;
		string::reference operator [](string::size_type i) {
			return string::operator [](i);
		}
		string::const_reference operator [](string::size_type i) const {
			return string::operator [](i);
		}
	};
	
	typedef list<cstring> lstring_t;
	
	class cmdline_parser {
	public:
		cmdline_parser(const cstring& cmdline);
		lstring_t get_args();
		cstring get_text_of_args(unsigned int arg_start, unsigned int arg_end = 0);
		cstring get_prefix(unsigned int argi);
		cstring get_postfix(unsigned int argi);
	private:
		vector<int> m_lab; //list of arg begin
		vector<int> m_lae;
		lstring_t m_lsa;
		cstring m_cmd_str;
	};


	list<cstring> split(const cstring& regex, const cstring& src);
	cstring remove_pattern(const cstring& src, const cstring& pat);
	bool fields_match(const cstring& src, const lstring_t& fields);
	bool string_nocase_contains(const cstring& src, const cstring& tgt);
	cstring string_left_of(const cstring& str, int point);
	cstring string_right_of(const cstring& str, int point);

	bool string_contains(const cstring& src, const cstring& tgt);
	cstring string_format(const char* fmt, ...);
	cstring dirname(const cstring& path);
	cstring basename(const cstring& path);

	cstring bce_dirname(const cstring& path); //bce: basename can be empty, take everything before the last '/'.
	cstring bce_basename(const cstring& path);
	bool is_abspath(const cstring& path);

	lstring_t getMatchingFiles(const cstring& dir, const cstring& base);
	lstring_t getPathEnvMatchingFiles(const lstring_t& args);
	cstring getWhichFile(const cstring& file);
	lstring_t getLocateMatchingFiles(const lstring_t& args, bool rerun_locate = false);
	void debug_lstring(const lstring_t& ls);
	cstring get_sh_folder(int csid);
	bool file_exist(const cstring& str);

	lstring_t cmdline2args(const cstring& str);
	cstring format_string(const char* fmt, ...);
	typedef enum which_output_t {
		read_none,
		read_out,
		read_err,
	};

	class program_runner {
	public:
		program_runner(const cstring& cmd, which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   const cstring& arg5, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   const cstring& arg5, 
					   const cstring& arg6, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   const cstring& arg5, 
					   const cstring& arg6, 
					   const cstring& arg7, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   const cstring& arg5, 
					   const cstring& arg6, 
					   const cstring& arg7, 
					   const cstring& arg8, 
					   which_output_t which = read_none, int timeout = -1);
		program_runner(const cstring& cmd, 
					   const cstring& arg1, 
					   const cstring& arg2, 
					   const cstring& arg3, 
					   const cstring& arg4, 
					   const cstring& arg5, 
					   const cstring& arg6, 
					   const cstring& arg7, 
					   const cstring& arg8, 
					   const cstring& arg9, 
					   which_output_t which = read_none, int timeout = -1);

		
		DWORD exit_code();
		cstring get_output();
	private: 
		void ctor_helper(const cstring& cmdline, which_output_t which = read_none, int timeout = -1);
		DWORD m_exit_code;
		cstring m_str_output;
	};
	
	cstring read_program_output(const cstring& exec, const cstring& cmdline, which_output_t which);
	cstring string_from_buffer(const char* buf, int size);
	void fmt_messagebox(const char* fmt, ...);
	cstring get_win_path(const cstring& upath);
	void cmdline_to_file_and_args(const cstring& str, cstring& file, cstring& args);
	lstring_t unique_ls(const lstring_t& ls);
	template <class T> void list_append(list<T>& ls, const list<T>& lt)
	{
		if (!lt.empty()) {
			ls.insert(ls.end(), lt.begin(), lt.end());
		}
	}
	bool is_dir_cyg(const cstring& path);

	cstring unquote_str(const cstring& str);
	cstring quote_str(const cstring& str);

};



#endif

