#ifndef MYSQLCPPAPI_SHAREDPTR_H
#define MYSQLCPPAPI_SHAREDPTR_H

#include "mysqlcppapi/smartpointer/Allocator.h"

namespace mysqlcppapi
{

/**A ref-counting smart-pointer for the underlying C object.
 * Use derived allocators to use e.g. mysql_init() and mysql_close().
 * You can copy these smarpointers-of-C-resources, and therefore the C++ classes can
 * have simple copy constructors which just share the underlying C resources.
 *
 * The default allocator does a simple new and delete, which is suitable for normal C++ instances.
 */
template< typename T_obj, typename T_allocator = Allocator_NewDelete<T_obj> >
class SharedPtr
{
public:
  typedef size_t size_type;

  ///Allocate a new instance.
  SharedPtr();
  
  ///Take ownership
  explicit SharedPtr(T_obj* pobj);

  ///Share ownership
  SharedPtr(const SharedPtr& src);

  ///Share ownership
  SharedPtr& operator=(const SharedPtr& src);

  virtual ~SharedPtr();

  ///Forget the instance and allocate a new one.
  virtual void clear();


  /** Dereferencing.
   */
  inline T_obj& operator*();

  /** Dereferencing.
   */
  inline const T_obj& operator*() const;
  
  /** Dereferencing.
   *
   * Use the methods of the underlying instance like so:
   * <code>refptr->memberfun()</code>.
   */
  inline T_obj* operator->() const;

  /** Test whether the RefPtr<> points to any underlying instance.
   *
   * Mimics usage of ordinary pointers:
   * @code
   *   if (ptr)
   *     do_something();
   * @endcode
   */
  inline operator bool() const;

  ///Get the underlying instance:
  inline T_obj* obj();

  ///Get the underlying instance:
  inline const T_obj* obj() const;


protected:
  inline void ref();
  inline void unref();

  void initialize();

  size_type* m_pRefCount; //Shared between instances, by copying.
  T_obj* m_pobj; //The underlying instance.
};

template< typename T_obj, typename T_allocator>
SharedPtr<T_obj, T_allocator>::SharedPtr()
: m_pRefCount(0), m_pobj(0)
{
  //Allocate a new instance:  
  initialize();
}

template< typename T_obj, typename T_allocator>
SharedPtr<T_obj, T_allocator>::SharedPtr(T_obj* pobj)
: m_pRefCount(0), m_pobj(pobj)
{
    //Start refcounting:
    ref();
}

template< typename T_obj, typename T_allocator>
SharedPtr<T_obj, T_allocator>::SharedPtr(const SharedPtr<T_obj, T_allocator>& src)
: m_pRefCount(src.m_pRefCount), m_pobj(src.m_pobj)
{
    ref();
}

template< typename T_obj, typename T_allocator>
SharedPtr<T_obj, T_allocator>& SharedPtr<T_obj, T_allocator>::operator=(const SharedPtr<T_obj, T_allocator>& src)
{
  //std::cout << "SharedPtr& operator=(const SharedPtr& src)" << std::endl;
  if(&src != this)
  {
    //Unref any existing stuff.
    //operator= can never run before a constructor, so these values will be initialized already.
    if(m_pobj) //The if() might not be required.
    {
      unref(); //Could cause a deallocation.
    }

    //Copy:
    m_pobj = src.m_pobj;

    m_pRefCount = src.m_pRefCount;
    ref();
  }

  return *this;
}

template< typename T_obj, typename T_allocator>
SharedPtr<T_obj, T_allocator>::~SharedPtr()
{
   unref();
}

template< typename T_obj, typename T_allocator>
void SharedPtr<T_obj, T_allocator>::clear()
{
  initialize();
}

template< typename T_obj, typename T_allocator>
inline
T_obj* SharedPtr<T_obj, T_allocator>::obj()
{
  return m_pobj;
}

template< typename T_obj, typename T_allocator>
inline
const T_obj* SharedPtr<T_obj, T_allocator>::obj() const
{
  return m_pobj;
}

template< typename T_obj, typename T_allocator>
inline
T_obj& SharedPtr<T_obj, T_allocator>::operator*()
{
  return *m_pobj;
}

template< typename T_obj, typename T_allocator>
inline
const T_obj& SharedPtr<T_obj, T_allocator>::operator*() const
{
  return *m_pobj;
}
  
template< typename T_obj, typename T_allocator>
inline
T_obj* SharedPtr<T_obj, T_allocator>::operator->() const
{
  return m_pobj;
}

template <class T_obj, typename T_allocator>
inline
SharedPtr<T_obj, T_allocator>::operator bool() const
{
  return (m_pobj != 0);
}


template <class T_obj, typename T_allocator>
inline
void SharedPtr<T_obj, T_allocator>::ref()
{
  if(m_pobj) //Don't waste time on invalid instances. These would be very rare anyway, and intentionally created with (0,0) construction.
  {
    if(m_pRefCount == 0)
    {
      //std::cout << "SharedPtr::ref(): first ref" << std::endl;
      //First ref, so allocate the shared count:
      m_pRefCount = new size_type();
      *m_pRefCount = 1;
    }
    else
    {
      //std::cout << "SharedPtr::ref(): starting at" << *m_pRefCount << std::endl;
      (*m_pRefCount)++;
    }
  }
}

template <class T_obj, typename T_allocator>
inline
void SharedPtr<T_obj, T_allocator>::unref()
{
  if(m_pRefCount)
  {
    //std::cout << "SharedPtr::unref(): starting at " << *m_pRefCount << std::endl;

    if( (*m_pRefCount) > 0 )
       (*m_pRefCount)--;

    //Unalloc if this is the last user of the obj:
    if(*m_pRefCount == 0)
    {
      if(m_pobj)
       {
         try
         {
          //std::cout << "SharedPtr::unref(): deallocating " << *m_pRefCount << std::endl;
           T_allocator::deallocate(m_pobj);
           m_pobj = 0;
         }
         catch(ex_base&)
         {
          //std::cout << "SharedPtr::unref(): exception thrown during deallocation." << std::endl;
           //Ignore it. Can't throw an expection up to the destructor.
         }

         m_pobj = 0;
      }

       //Clear ref count:
       delete m_pRefCount;
       m_pRefCount = 0;
    }
  }
  else
  {
    //std::cout << "SharedPtr::unref(): ref not setup." << std::endl;
  }

}

template <class T_obj, typename T_allocator>
void SharedPtr<T_obj, T_allocator>::initialize()
{
  //Forget any previous instance:
  if(m_pobj)
  {
    unref();
    m_pobj = 0;
    m_pRefCount = 0;
  }

  //Allocate a new instance:
  if(!m_pobj)
  {
    m_pobj = T_allocator::allocate();

    //Start ref counting:
    m_pRefCount = 0;
    ref();
  }
}


} //namespace

#endif //MYSQLCPPAPI_SHAREDPTR_H

