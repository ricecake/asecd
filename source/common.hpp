#include <stddef.h>  // defines NULL
#include <mutex>

template <class T> class Singleton {
	public:
		Singleton() {
			if(!m_pInstance) m_pInstance = new T;
		}
		Singleton(T value) {
			if(!m_pInstance) m_pInstance = new T(value);
		}
		T * operator -> () const throw() {
			return m_pInstance;
		}
		T & operator * () const throw () {
			return *m_pInstance;
		}
	protected:
	private:
		Singleton(Singleton const&);
		Singleton& operator=(Singleton const&);
		static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance=NULL;

template<class T, class M> class locking_ptr {
	public:
		locking_ptr(T* ptr): m_ptr(ptr) {
			m_mutex = new M;
			m_mutex->lock();
		}
		locking_ptr(T* ptr, M* lock): m_ptr(ptr), m_mutex(lock) {
			m_mutex->lock();
		}
		~locking_ptr() {
			if (m_mutex)
				m_mutex->unlock();
		}
		locking_ptr(locking_ptr<T, M>&& ptr)
			: m_ptr(ptr.m_ptr)
			, m_mutex(ptr.m_mutex) {
			ptr.m_ptr = nullptr;
			ptr.m_mutex = nullptr;
		}

		T* operator ->() {
			return m_ptr;
		}
		T const* operator ->() const {
			return m_ptr;
		}
		T* operator * () const throw () {
			return m_ptr;
		}

	private:
		// disallow copy/assignment
		locking_ptr(locking_ptr<T, M> const& ptr) {}
		locking_ptr& operator = (locking_ptr<T, M> const& ptr) {
			return *this;
		}
		T* m_ptr;
		M* m_mutex; // whatever implementation you use
};

