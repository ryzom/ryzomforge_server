/** \file debug_history.h
 *
 * $Id: debug_history.h,v 1.4 2005/07/04 13:01:38 vuarand Exp $
 */

#ifndef RYAI_DEBUG_HISTORY_H
#define RYAI_DEBUG_HISTORY_H

class CDebugHistory
{
private:
	typedef std::deque<std::string> THistoryContainer;
public:
	explicit CDebugHistory()
	: _Recording(false)
	{
	}
	virtual	~CDebugHistory() { }
	void addHistory(std::string const& txt)
	{
		if (_Recording)
			_History.push_back(txt);
	}
	void addHistory(char const* txt)
	{
		if (_Recording)
			addHistory(NLMISC::toString(txt));
	}
	
	template <class A>
	void addHistory(char const* txt, A a) { if (_Recording) addHistory(NLMISC::toString(txt, a)); }
	template <class A, class B>
	void addHistory(char const* txt, A a, B b) { if (_Recording) addHistory(NLMISC::toString(txt, a, b)); }
	template <class A, class B, class C>
	void addHistory(char const* txt, A a, B b, C c) { if (_Recording) addHistory(NLMISC::toString(txt, a, b, c)); }
	template <class A, class B, class C, class D>
	void addHistory(char const* txt, A a, B b, C c, D d) { if (_Recording) addHistory(NLMISC::toString(txt, a, b, c, d)); }
	
	void setRecording(bool val) { _Recording = val; }
	
	void writeAsInfo()
	{
		int j = 0;
		FOREACH(itHistory, THistoryContainer, _History)
		{
			nlinfo("HIST %3i: %s", j, itHistory->c_str());
			++j;
		}
	}
	
private:
	bool _Recording;
	THistoryContainer _History;
};

#endif
