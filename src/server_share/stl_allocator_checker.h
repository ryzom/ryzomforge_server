/**
 *  file: stl_allocator_checker.h
 */

/*
  This file provides systems for verifying that STL allocators have not been damaged

  The firt implementation only tests the allocator for blocks of <= 8 bytes.
  This is because this is the only allocator causing code crashes at the time of writing.
  This allocator is reffered to as Allocator '0'

  The following macros are provided to facilitate code instrumentaion:
  STL_ALLOC_TEST - performs a punctual test at the indicated position in the code
  STL_ALLOC_CONTEXT - instantiates an object of type CStlAllocatorChecker that performs a test at construction time and another test at destruction time

  The NLMISC variable 'EnableStlAllocatorChecker' can be used to enable and dissable the tests provided by the above macros
*/

extern bool EnableStlAllocatorChecker;

void testStlMemoryAllocator(const char* context);

class CStlAllocatorChecker
{
public:
	CStlAllocatorChecker(const char* startContextName,const char* endContextName);
	~CStlAllocatorChecker();
private:
	const char* _StartContextName;
	const char* _EndContextName;
};

inline CStlAllocatorChecker::CStlAllocatorChecker(const char* startContextName,const char* endContextName): _StartContextName(startContextName), _EndContextName(endContextName)
{
	if (EnableStlAllocatorChecker)
		testStlMemoryAllocator(_StartContextName);
}

inline CStlAllocatorChecker::~CStlAllocatorChecker()
{
	if (EnableStlAllocatorChecker)
		testStlMemoryAllocator(_EndContextName);
}

#define STL_ALLOC_CONTEXT _STL_ALLOC_CONTEXT1(__FILE__,__LINE__)
#define _STL_ALLOC_CONTEXT1(file,line) _STL_ALLOC_CONTEXT2(file,line)
#define _STL_ALLOC_CONTEXT2(file,line) _STL_ALLOC_CONTEXT3(file ":" #line)
#define _STL_ALLOC_CONTEXT3(fileLine) CStlAllocatorChecker __StlAllocatorChecker__(fileLine ": @construction",fileLine ": @destruction");

#define STL_ALLOC_TEST _STL_ALLOC_TEST1(__FILE__,__LINE__)
#define _STL_ALLOC_TEST1(file,line) _STL_ALLOC_TEST2(file,line)
#define _STL_ALLOC_TEST2(file,line) if (!EnableStlAllocatorChecker) {} else testStlMemoryAllocator(file ":" #line);
