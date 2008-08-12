#ifndef _SCRIPT_COMP_H_
#define _SCRIPT_COMP_H_


struct ReadFightActionException	:public	NLMISC::Exception
{
	ReadFightActionException(const	std::string	&reason):NLMISC::Exception(reason){}
};

class	CSpawnBot;

class	CFightScriptComp
		:public	NLMISC::CRefCount
{
public:
	CFightScriptComp()
	{}
	virtual ~CFightScriptComp()
	{}
	virtual	std::string	toString() const = 0;

	virtual	bool	update(CSpawnBot	&bot)	const = 0;	//	returns true if it behaves normally, false if there a problem and callers may not consider it behaves normally.
																	//	for instance ONCE may not consider that this call happened.
	virtual	void	remove(CFightScriptComp	*child)
	{}
protected:
private:
};

class CFightScriptCompReader
	:public	NLMISC::CRefCount
{
public:
	CFightScriptCompReader()
	{}
	virtual ~CFightScriptCompReader()
	{}
	virtual	CFightScriptComp	*create	(const	std::string	&inStr)	throw	(ReadFightActionException) = 0;
	virtual	std::string	getName	()	const =0;

	static	CFightScriptCompReader	*getScriptReader	(const std::string &str) throw (ReadFightActionException);
	
	static	CFightScriptComp	*createScriptComp	(const std::string &str)	throw	(ReadFightActionException);
protected:
private:
};


class CFightScript
{
public:
	CFightScript();
	virtual ~CFightScript()
	{}

	void	add(CFightScriptCompReader	*reader);

	typedef	std::hash_map<std::string, NLMISC::CSmartPtr<CFightScriptCompReader> >	TFightScriptMap;

	static	TFightScriptMap	_ScriptCompList;
protected:	
private:
};


//////////////////////////////////////////////////////////////////////////
//	Select Filter


class	CFightSelectFilter
		:public	CFightScriptComp
{
public:
	CFightSelectFilter(CFightScriptComp	*customComp, std::string param)
		:_CustomComp(customComp)
		,_Param(param)
	{}

	virtual ~CFightSelectFilter()
	{}
	bool	update	(CSpawnBot	&bot)	const;
	const	std::string	&getParam()	const
	{
		return	_Param;
	}

	std::string	toString() const;

protected:
private:
	NLMISC::CSmartPtr<CFightScriptComp>	_CustomComp;
	std::string	_Param;
};


class	CFightSelectFilterReader
		:public	CFightScriptCompReader
{
public:
	CFightSelectFilterReader()			{}
	virtual ~CFightSelectFilterReader()	{}

	CFightScriptComp	*create	(const	std::string	&inStr)	throw	(ReadFightActionException);
	std::string	getName	()	const
	{
		return	std::string("SELECT");
	}

};

#endif
