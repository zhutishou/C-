#include <iostream> 
#include <mutex>
using namespace std;

//智能指针实现过程：
namespace cx_smart_ptr
{
	//auto_ptr
	template<class T>
	class auto_ptr
	{
	public:	
		//auto_ptr:不防止拷贝，容易出现多个指针指向一个地址，出现一个清理内存其余指针置空的现象
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}
		auto_ptr(auto_ptr<T>& p)
			:_ptr(p._ptr)
		{
			p._ptr = nullptr;
		}
		auto_ptr<T>& operator=(auto_ptr<T>& p)
		{
			if(this != &p)
			{
				if(_ptr)
					delete _ptr;
				_ptr = p._ptr;
				p._ptr = nullptr;
			}
			return *this;
		}
		~auto_ptr()
		{
			if(_ptr)
			{
				delete _ptr;
			}
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
		
	template<class T>
	class unique_ptr
	{
	public:
		//unique_ptr直接防止拷贝，所以不会出现auto_ptr的情况
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}
		
		~unique_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
			}
		}
		
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		//禁止拷贝 
		unique_ptr(const unique_ptr<T>& sp) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& sp) = delete;
	private:
		T* _ptr;	
	};
	
	template<class T>
	class shared_ptr
	{
	public:
		//利用计数方式，只有当==1时才会析构,为了防止多线程，可以加上一个互斥锁 
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr),_pcount(new int(1)),_pmtx(new mutex)
		{
		}
		shared_ptr(const shared_ptr<T>& p)
			:_ptr(p._ptr),_pcount(p._pcount),_pmtx(p._pmtx)
		{
			Addcount();
		}
		shared_ptr<T>& operator=(const shared_ptr<T>& p) 
		{
			if(_ptr != p._ptr)
			{
				Release();
				_ptr = p._ptr;
				_pcount = p._pcount;
				_pmtx = p._pmtx;
				//注意：计数器要++
				Addcount();
			}
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		~shared_ptr()
		{
			Release();
		}
		int use_count()
		{
			return (*_pcount);
		}
		//最后不要直接使用get函数 
		T* get() const
		{
			return _ptr;
		}
	private:
		void Release()
		{
			//注意上锁,否则多线程会影响
			_pmtx->lock();
			bool flag = false;//便于锁的删除
			if(--(*_pcount) == 0 && _ptr)
			{
				flag = true;
				delete _ptr;
				delete _pcount;
				//注意：这里不能直接delete _pmtx; 
			}
			_pmtx->unlock();
			if(flag)
				delete _pmtx;
		}
		void Addcount()
		{
			//计数器++,注意点：上锁
			_pmtx->lock();
			(*_pcount)++;
			_pmtx->unlock();
		} 
		T* _ptr;
		int* _pcount;
		mutex* _pmtx;
	};
	
	template<class T>
	class weak_ptr
	{
	public:
		//作用解决shared_ptr循环引用的问题，本身不拥有对象的所有权，也不会增加对象的引用计数 
		weak_ptr()
			:_ptr(nullptr)
		{}
		weak_ptr(const shared_ptr<T>& p)
			:_ptr(p.get())
		{}
		weak_ptr<T>& operator=(const shared_ptr<T>& p)
		{
			_ptr = p.get();
			return *this;
		}
		
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}


int main()
{
  return 0;
}

