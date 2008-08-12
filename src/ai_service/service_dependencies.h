#ifndef __SERVICE_DEPENDENCIES__
#define __SERVICE_DEPENDENCIES__


class CServiceEvent
{
public:
	enum TType
	{
		SERVICE_UP = 0,
		SERVICE_DOWN
	};
	
	class CHandler
	{
	public:
		virtual ~CHandler() { }
		virtual void serviceEvent(CServiceEvent const& info) = 0;
	};
	
public:
	CServiceEvent(NLNET::TServiceId serviceId, std::string const& serviceName, TType const& eventType);
	virtual ~CServiceEvent() { }
	
	NLNET::TServiceId getServiceId() const { return _serviceId; }
	std::string const& getServiceName() const { return _serviceName; }
	TType const& getEventType()	const { return _eventType; }
	
private:
	NLNET::TServiceId const _serviceId;
	std::string		const _serviceName;
	TType		const _eventType;
};

inline
CServiceEvent::CServiceEvent(NLNET::TServiceId serviceId, std::string const& serviceName, TType const& eventType)
	:	_serviceId(serviceId),
		_serviceName(serviceName),
		_eventType(eventType)
{
}

#endif
