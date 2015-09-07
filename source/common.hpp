#ifndef __COMMON_HPP_
#define __COMMON_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <stddef.h>  // defines NULL

#include <exception.hpp>

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
		Singleton(Singleton const&) {}
		Singleton& operator=(Singleton const&);
		static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance=NULL;

#endif
