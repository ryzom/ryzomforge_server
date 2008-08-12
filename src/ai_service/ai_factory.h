/** \file factory.h
 *
 * $Id: ai_factory.h,v 1.2 2006/12/06 17:22:05 boucher Exp $
 */



#ifndef AI_FACTORY_H
#define AI_FACTORY_H

#include <nel/misc/types_nl.h>
#include <map>


template <class BaseClass>
class IAiFactory
	:public	NLMISC::CDbgRefCount<IAiFactory<BaseClass> >
{
public:
	virtual BaseClass *createObject(const	typename BaseClass::CtorParam&	ctorParam) = 0;
};


template <class BaseClass, class KeyType = std::string>
class CAiFactoryContainer
{
	typedef std::map<KeyType, NLMISC::CDbgPtr<IAiFactory<BaseClass> > > TRegisterCont;

public:
		
	static CAiFactoryContainer &instance()
	{
		if (!_Instance)
		{
			_Instance = new CAiFactoryContainer();
		}
		return *_Instance;
	}

	virtual ~CAiFactoryContainer() 
	{
	}

	void release()
	{
		delete this;
		_Instance = NULL;
	}

	void	registerFactory(const KeyType &key, IAiFactory<BaseClass> *factoryRegister)
	{
		nlassert(_FactoryRegisters.find(key) == _FactoryRegisters.end());
		_FactoryRegisters.insert(std::make_pair(key, factoryRegister));
	}


	IAiFactory<BaseClass>*	getFactory	(const KeyType &key)
	{
		typename TRegisterCont::iterator it (_FactoryRegisters.find(key));
		if	(it!=_FactoryRegisters.end())
			return	it->second;
		return	NULL;
	}

protected:
	static CAiFactoryContainer	*_Instance;
private:
	TRegisterCont	_FactoryRegisters;
};


template <class BaseClass, class SpecializedClass>
class CAiFactory : public IAiFactory<BaseClass>
{
public:
	CAiFactory	()
	{
	}

	BaseClass *createObject(const	typename BaseClass::CtorParam&	ctorParam)
	{
		return new SpecializedClass(ctorParam);
	}
};

/////////////////////////////////////////////////////////
// Factory indirect

template <class BaseFactoryClass>
class IAiFactoryIndirectRegister
{
public:
	virtual BaseFactoryClass *getFactory() = 0;
};



template <class BaseFactoryClass, class KeyType = std::string>
class CAiFactoryIndirect
{
	typedef std::map<KeyType, IAiFactoryIndirectRegister<BaseFactoryClass>*> TRegisterCont;

public:
	static CAiFactoryIndirect &instance()
	{
		if (!_Instance)
		{
			_Instance = new CAiFactoryIndirect();
		}
		return *_Instance;
	}

	void registerClass(const KeyType &key, IAiFactoryIndirectRegister<BaseFactoryClass> *factoryRegister)
	{
		nlassert(_FactoryRegisters.find(key) == _FactoryRegisters.end());
		_FactoryRegisters.insert(std::make_pair(key, factoryRegister));
	}

	BaseFactoryClass *getFactory(const KeyType &key)
	{
		typename TRegisterCont::const_iterator it (_FactoryRegisters.find(key));
		if (it == _FactoryRegisters.end())
			return NULL;
		else
			return it->second->getFactory();
	}
private:
	static CAiFactoryIndirect	*_Instance;

	TRegisterCont	_FactoryRegisters;
};


template <class IndirectFactoryClass, class BaseFactoryClass, class SpecializedFactoryClass, class KeyType>
class CAiFactoryIndirectRegister : public IAiFactoryIndirectRegister<BaseFactoryClass>
{
	SpecializedFactoryClass	_FactoryClass;
public:
	CAiFactoryIndirectRegister(const KeyType &key)
	{
		IndirectFactoryClass::instance().registerClass(key, this);
	}

	BaseFactoryClass *getFactory()
	{
		return &_FactoryClass;
	}
};

#define RYAI_IMPLEMENT_FACTORY_INDIRECT(baseFactoryClass, keyType)	template <> CAiFactoryIndirect<baseFactoryClass, keyType>	*CAiFactoryIndirect<baseFactoryClass, keyType>::_Instance = NULL

#define RYAI_REGISTER_FACTORY(baseFactoryClass, specializedFactoryClass, keyType, keyValue)	CAiFactoryIndirectRegister<CAiFactoryIndirect<baseFactoryClass, keyType>, baseFactoryClass, specializedFactoryClass, keyType>	RegisterIndirect##specializedFactoryClass(keyValue)
#define RYAI_DECLARE_FACTORY(baseFactoryClass, specializedFactoryClass, keyType)	extern CAiFactoryIndirectRegister<CAiFactoryIndirect<baseFactoryClass, keyType>, baseFactoryClass, specializedFactoryClass, keyType>	RegisterIndirect##specializedFactoryClass

#define RYAI_GET_FACTORY(specializedFactoryClass) RegisterIndirect##specializedFactoryClass.getFactory()

#endif // FACTORY_H
