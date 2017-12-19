#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 「shareptr」「weakptr」。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./debugassert.h"
#include "./meta.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include <intrin.h>

#endif


/** include
*/
#if(BLIB_STDSHAREDPTR_ENABLE)

	#include <memory>

#endif


/** NBlib
*/
namespace NBlib
{
	#if(BLIB_STDSHAREDPTR_ENABLE)

		#define sharedptr std::shared_ptr

	#else

		/** sharedptrbase。
	
			カウントの管理。

		*/
		class sharedptrbase
		{
		private:
			/** 使用数。
			*/
			volatile s32	use;

			/** 参照数。
			*/
			volatile s32	weak;

		public:
			/** constructor
			*/
			sharedptrbase()
				:
				use(1),
				weak(1)
			{
			}

			/** constructor
			*/
			sharedptrbase(s32 a_use,s32 a_weak)
				:
				use(a_use),
				weak(a_weak)
			{
			}

			/** destructor
			*/
			virtual ~sharedptrbase() noexcept
			{
			}

		protected:

			/** 確保。
			*/
			static void* Alloc(size_t a_size);

			/** 解放。
			*/
			static void Free(void* a_pointer);

		public:
			/** 使用数の取得。
			*/
			s32 GetUseCount() const
			{
				return this->use;
			}

			/** 参照数の取得。
			*/
			s32 GetWeakCount() const
			{
				return this->weak;
			}

		public:
			/** 削除子の実行。
			*/
			virtual void Delete() = 0;

			/** インスタンスの取得。
			*/
			virtual void* GetInstance() = 0;

			/** 使用数デクリメント。
			*/
			void Use_Decrement()
			{
				bool t_delete = false;

				#if defined(PLATFORM_VCWIN)
				{
					s32 t_ret = _InterlockedDecrement(reinterpret_cast<volatile long*>(&(this->use)));
					if(t_ret <= 0){
						t_delete = true;
					}
				}
				#else
				{
					#error
				}
				#endif

				if(t_delete){
					this->Delete();
				}
			}

			/** 使用数が０でないならば延命。
			*/
			bool Use_Increment_IfNoZero()
			{
				#if defined(PLATFORM_VCWIN)
				{
					for(;;){
						//最新の状態を取得。
						s32 t_count = static_cast<volatile s32&>(this->use);
						if(t_count == 0){
							//すでに死んでいる。
							return false;
						}else{
							//カウントが「t_count」の場合は「t_count+1」にする。
							if(static_cast<s32>(_InterlockedCompareExchange(reinterpret_cast<volatile long*>(&(this->use)),t_count+1,t_count) == t_count)){
								//延命に成功。
								return true;
							}else{
								//「this->use」の初期値が「t_count」以外だった。
							}
						}
					}
				}
				#else
				{
					#error
				}
				#endif
			}

			/** 使用数、参照数をインクリメント。 
			*/
			void UseAndWeak_Increment()
			{
				#if defined(PLATFORM_VCWIN)
				{
					_InterlockedIncrement(reinterpret_cast<volatile long*>(&(this->use)));
					_InterlockedIncrement(reinterpret_cast<volatile long*>(&(this->weak)));
				}
				#else
				{
					#error
				}
				#endif
			}

			/** 参照数をデクリメント。
			*/
			bool Weak_Decrement()
			{
				#if defined(PLATFORM_VCWIN)
				{
					s32 t_ret = _InterlockedDecrement(reinterpret_cast<volatile long*>(&(this->weak)));
					if(t_ret <= 0){
						//※誰も使用していない、誰も参照していない。
						return true;
					}
				}
				#else
				{
					#error
				}
				#endif

				return false;
			}

			/** 参照数をインクリメント。
			*/
			void Weak_Increment()
			{
				#if defined(PLATFORM_VCWIN)
				{
					_InterlockedIncrement(reinterpret_cast<volatile long*>(&(this->weak)));
				}
				#else
				{
					#error
				}
				#endif
			}
		};

		/** sharedptr_impl。

			カウント、インスタンス、削除子の管理。

		*/
		template <typename T,typename D> class sharedptr_impl
			:
			public sharedptrbase
		{
		private:
			/** インスタンス。
			*/
			T* instance;

			/** 削除子。
			*/
			D deleter;

		public:
			/** constructor
			*/
			sharedptr_impl(const T* a_instance,D a_deleter)
				:
				sharedptrbase(),						// カウントの管理。
				instance(const_cast<T*>(a_instance)),	// インスタンスの管理。
				deleter(a_deleter)						// 削除子の管理。
			{
			}

			/** destructor
			*/
			virtual ~sharedptr_impl() noexcept
			{
			}

		public:

			#if defined(new)
			#undef new
			#endif

			/** operator new
			*/
			static void* operator new(size_t a_size) noexcept
			{
				return sharedptrbase::Alloc(a_size);
			}

			#if defined(custom_new)
			#define new custom_new
			#endif
		
			/** operator delete
			*/
			static void operator delete(void* a_pointer) noexcept
			{
				sharedptrbase::Free(a_pointer);
			}

		private:
			/** 削除子の実行。
			*/
			virtual void Delete()
			{
				this->deleter(this->instance);
				this->instance = nullptr;
			}

			/** インスタンスの取得。
			*/
			virtual void* GetInstance()
			{
				return this->instance;
			}
		};

		/** nullsharedptr。
		*/
		class nullsharedptr_impl : public sharedptrbase
		{
		public:
			/** constructor
			*/
			nullsharedptr_impl()
				:
				sharedptrbase()
			{
				//static constructor.
			}

			/** destructor
			*/
			virtual ~nullsharedptr_impl() noexcept
			{
				//static destructor.
			}

			/** null_impl
			*/
			static nullsharedptr_impl& null_impl()
			{
				static nullsharedptr_impl s_nullsharedptr_impl;
				return s_nullsharedptr_impl;
			}

		public:

			#if defined(new)
			#undef new
			#endif

			/** operator new
			*/
			static void* operator new(size_t /*a_size*/) noexcept
			{
				ASSERT(0);
				return nullptr;
			}

			#if defined(custom_new)
			#define new custom_new
			#endif
		
			/** operator delete
			*/
			static void operator delete(void* /*a_pointer*/) noexcept
			{
				ASSERT(0);
			}

		private:
			/** 削除子の実行。
			*/
			virtual void Delete()
			{
				ASSERT(0);
			}

			/** インスタンスの取得。
			*/
			virtual void* GetInstance()
			{
				return nullptr;
			}
		};

		/** weakptr
		*/
		template <typename T> class weakptr;

		/** sharedptr
		*/
		template <typename T> class sharedptr
		{
		public:
			typedef typename T element_type;

			//カウント、インスタンス、削除子の管理。
			sharedptrbase* impl;

			#if(BLIB_SHAREDPTR_CACHE_ENABLE)
			T* cache;
			#endif

			friend class weakptr<T>;

			/** null。
			*/
			static sharedptr<T>& null()
			{
				static sharedptr<T> s_nullsharedptr(nullsharedptr_impl::null_impl());
				return s_nullsharedptr;
			}

		private:
			/** reset_impl
			*/
			void reset_impl(sharedptrbase* a_sharedptrbase)
			{
				//nullsharedptrチェック。
				#if defined(ROM_MASTER)

				#else

					if(this->impl == &nullsharedptr_impl::null_impl()){
						ASSERT(0);
					}

				#endif

				this->reset_impl_from_destructor(a_sharedptrbase);
			}

			/** reset_impl_from_destructor
			*/
			void reset_impl_from_destructor(sharedptrbase* a_sharedptrbase)
			{
				//現在保持している「sharedptrbase」の参照数、使用数のデクリメント。
				if(this->impl){
					if(this->impl == a_sharedptrbase){
						//変化なし。
						return;
					}else{
						//使用数が０になった場合は削除子が呼び出される。
						this->impl->Use_Decrement();
						//最後の参照の場合は削除。
						if(this->impl->Weak_Decrement()){
							delete this->impl;
						}
					}
				}

				this->impl = a_sharedptrbase;

				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				if(this->impl){
					this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
				}else{
					this->cache = nullptr;
				}
				#endif

				if(this->impl){
					this->impl->UseAndWeak_Increment();
				}
			}

		public:
			/** [constructor]nullptr。
			*/
			sharedptr() noexcept
				:
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)

				impl(nullptr),
				cache(nullptr)

				#else

				impl(nullptr)

				#endif
			{
			}

			/** [constructor]nullptr。
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			sharedptr(nullptr_t) noexcept
				:
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)

				impl(nullptr),
				cache(nullptr)

				#else

				impl(nullptr)

				#endif
			{
			}
			#endif

			/** [constructor]nullsharedptr。
			*/
			explicit sharedptr(nullsharedptr_impl& a_impl) noexcept
				:
				impl(&a_impl)
			{
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
				#endif

				this->impl->UseAndWeak_Increment();
			}

			/** [constructor]新規。削除子なし。
			*/
			sharedptr(const T* a_instance) noexcept
			{
				//開始時は使用数１、参照数１。
				if(a_instance != nullptr){

					#if defined(new)
					#undef new
					#endif

					this->impl = new sharedptr_impl<T,default_delete<T>>(a_instance,default_delete<T>());

					#if defined(custom_new)
					#define new custom_new
					#endif

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = const_cast<T*>(a_instance);
					#endif
				}else{
					this->impl = nullptr;

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = nullptr;
					#endif
				}
			}

			/** [constructor]新規。削除子あり。
			*/
			template <typename T2,typename D> sharedptr(const T2* a_instance,D a_deleter) noexcept
			{
				//開始時は使用数１、参照数１。
				if(a_instance != nullptr){

					#if defined(new)
					#undef new
					#endif

					//「sharedptr<T>」の削除時に削除子に渡すポインタの型は「T2*」。
					this->impl = new sharedptr_impl<T2,D>(a_instance,a_deleter);

					#if defined(custom_new)
					#define new custom_new
					#endif

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = static_cast<T*>(const_cast<T2*>(a_instance));
					#endif
				}else{
					this->impl = nullptr;

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = nullptr;
					#endif
				}
			}

			/** [constructor]「weakptr」から「sharedptr」を作成。
			*/
			sharedptr(const weakptr<T>& a_weakptr);

			/** [constructor]move constructor
			*/
			#if(BLIB_STDMOVE_ENABLE)
			sharedptr(sharedptr<T>&& a_sharedptr) noexcept
				:
				impl(a_sharedptr.impl)
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				,
				cache(a_sharedptr.cache)
				#endif
			{
				//残骸もデストラクタの呼び出しは行われる。
				a_sharedptr.impl = nullptr;
				a_sharedptr.cache = nullptr;
			}
			#endif

			/** [constructor]constructor cast
			*/
			sharedptr(sharedptrbase* a_impl) noexcept
				:
				impl(a_impl)
			{
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				if(this->impl){
					this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
				}else{
					this->cache = nullptr;
				}
				#endif

				//新しい「sharedptrbase」の使用数、参照数をインクリメント。
				if(this->impl){
					if(this->get() != nullptr){
						this->impl->UseAndWeak_Increment();
					}else{
						this->impl = nullptr;

						#if(BLIB_SHAREDPTR_CACHE_ENABLE)
						this->cache = nullptr;
						#endif
					}
				}
			}

			/** [constructor]copy constructor
			*/
			sharedptr(const sharedptr<T>& a_sharedptr) noexcept
				:
				impl(a_sharedptr.impl)
			{
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				if(this->impl){
					this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
				}else{
					this->cache = nullptr;
				}
				#endif

				//新しい「sharedptrbase」の使用数、参照数をインクリメント。
				if(this->impl){
					if(this->get() != nullptr){
						this->impl->UseAndWeak_Increment();
					}else{
						this->impl = nullptr;

						#if(BLIB_SHAREDPTR_CACHE_ENABLE)
						this->cache = nullptr;
						#endif
					}
				}
			}

			/** [constructor]copy constructor
			*/
			template <class T2> sharedptr(const sharedptr<T2>& a_sharedptr,typename enable_if<is_convertible<T2*,T*>::value,bool>::type a_check=true) noexcept
				:
				impl(a_sharedptr.impl)
			{
				UNUSED(a_check);

				//新しい「sharedptrbase」の使用数、参照数をインクリメント。
				if(this->impl){

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
					#endif

					this->impl->UseAndWeak_Increment();
				}else{

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = nullptr;
					#endif
				}
			}

			/** destructor
			*/
			nonvirtual ~sharedptr()
			{
				this->reset_impl_from_destructor(nullptr);
			}

			/** 代入。
			*/
			sharedptr<T>& operator =(const sharedptr<T>& a_sharedptr) noexcept
			{
				//新しい「sharedptrbase」の使用数、参照数をインクリメント。

				if(a_sharedptr.get() != nullptr){
					this->reset_impl(a_sharedptr.impl);
				}else{
					this->reset_impl(nullptr);
				}

				return *this;
			}

			/** リセット。
			*/
			void reset()
			{
				this->reset_impl(nullptr);
			}

			/** リセット。
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			void reset(nullptr_t)
			{
				this->reset_impl(nullptr);
			}
			#endif

			/** リセット。削除子なし。
			*/
			void reset(T* a_instance)
			{
				this->reset_impl(nullptr);

				//開始時は使用数１、参照数１。
				if(a_instance != nullptr){

					#if defined(new)
					#undef new
					#endif

					this->impl = new sharedptr_impl<T,default_delete<T>>(a_instance,default_delete<T>());

					#if defined(custom_new)
					#define new custom_new
					#endif

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = a_instance;
					#endif
				}
			}

			/** 新規。削除子あり。
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			template <typename D> void reset(nullptr_t)
			{
				this->reset_impl(nullptr);
			}
			#endif

			/** 新規。削除子あり。
			*/
			template <typename T2,typename D> void reset(T2* a_instance,D a_deleter)
			{
				this->reset_impl(nullptr);

				//開始時は使用数１、参照数１。
				if(a_instance != nullptr){

					#if defined(new)
					#undef new
					#endif

					//「sharedptr<T>」の削除時に削除子に渡すポインタの型は「T2*」。
					this->impl = new sharedptr_impl<T2,D>(a_instance,a_deleter);

					#if defined(custom_new)
					#define new custom_new
					#endif

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = a_instance;
					#endif
				}
			}

			/** スワップ。
			*/
			void swap(sharedptr<T>& a_sharedptr)
			{
				sharedptrbase* t_temp = this->impl;
				this->impl = a_sharedptr->impl;
				a_sharedptr->impl = t_temp;

				#if(BLIB_SHAREDPTR_CACHE_ENABLE)
				if(this->impl != nullptr){
					this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
				}else{
					this->cache = nullptr;
				}
				#endif
			}

		public:
			/** ポインタの取得。
			*/
			T* get()
			{
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)

				return this->cache;

				#else

				if(this->impl){
					return reinterpret_cast<T*>(this->impl->GetInstance());
				}
				return nullptr;

				#endif
			}

			/** コンストポインタの取得。
			*/
			const T* get() const
			{
				#if(BLIB_SHAREDPTR_CACHE_ENABLE)

				return this->cache;

				#else

				if(this->impl){
					return reinterpret_cast<const T*>(this->impl->GetInstance());
				}
				return nullptr;

				#endif
			}

			/** ポインタのように振舞う。
			*/
			typename reference_type<T>::type operator *() noexcept
			{
				return *(this->get());
			}

			/** ポインタのように振舞う。
			*/
			T* operator ->() noexcept
			{
				return this->get();
			}

			/** ポインタのように振舞う。
			*/
			typename reference_type<const T>::type operator *() const noexcept
			{
				return *(this->get());
			}

			/** ポインタのように振舞う。
			*/
			const T* operator ->() const noexcept
			{
				return this->get();
			}

			/** ポインタのように振舞う。
			*/
			operator bool() const noexcept
			{
				return (this->get()!=nullptr) ? true : false;
			}

			/** 比較。
			*/
			template <typename T2> bool operator ==(const NBlib::sharedptr<T2>& a_sharedptr_b) const noexcept
			{
				return (this->get() == a_sharedptr_b.get());
			}

			/** 比較。
			*/
			template <typename T2> bool operator !=(const NBlib::sharedptr<T2>& a_sharedptr_b) const noexcept
			{
				return (this->get() != a_sharedptr_b.get());
			}

			/** 比較。
			*/
			bool operator ==(const void* a_sharedptr_b) const noexcept
			{
				return (this->get() == a_sharedptr_b);
			}

			/** 比較。
			*/
			bool operator !=(const void* a_sharedptr_b) const noexcept
			{
				return (this->get() != a_sharedptr_b);
			}

		public:
			/** 使用数を取得。
			*/
			s32 use_count() const
			{
				if(this->impl){
					return this->impl->GetUseCount();
				}
				return 0;
			}
		};

		/** weakptr
		*/
		template <typename T> class weakptr
		{
		public:
			//カウント、インスタンス、削除子の管理。
			sharedptrbase* impl;
			friend class sharedptr<T>;

		public:
			/** 空。
			*/
			weakptr()
				:
				impl(nullptr)
			{
			}

			/** [constructor]copy constructor
			*/
			template <class T2> weakptr(const sharedptr<T2>& a_sharedptr,typename enable_if<is_convertible<T2*,T*>::value,bool>::type a_check=true) noexcept
			{
				//新しい「sharedptrbase」の参照数をインクリメント。
				this->impl = a_sharedptr.impl;
				if(this->impl){
					this->impl->Weak_Increment();
				}
			}

			/** 代入。
			*/
			template <class T2> weakptr& operator =(const sharedptr<T2>& a_sharedptr) noexcept
			{
				//現在保持している「sharedptrbase」の参照数のデクリメント。
				if(this->impl){
					if(this->impl == a_sharedptr.impl){
						//変化なし。
						return (*this);
					}else{
						//最後の参照の場合は削除。
						if(this->impl->Weak_Decrement()){
							delete this->impl;
						}
					}
				}

				//新しい「sharedptrbase」の参照数をインクリメント。
				this->impl = a_sharedptr.impl;
				if(this->impl){
					this->impl->Weak_Increment();
				}

				return (*this);
			}

			/** 「weakptr」から「sharedptr」を作成。
			*/
			sharedptr<T> lock() noexcept
			{
				return sharedptr<T>(*this);
			}

			/** 「weakptr」から「sharedptr」を作成。
			*/
			const sharedptr<T> lock() const noexcept
			{
				return sharedptr<T>(*this);
			}

			/** reset
			*/
			void reset() noexcept
			{
				//現在保持している「sharedptrbase」の参照数のデクリメント。
				if(this->impl){
					//最後の参照の場合は削除。
					if(this->impl->Weak_Decrement()){
						delete this->impl;
					}
				}
			}

			/** 使用数を取得。
			*/
			s32 use_count() const
			{
				if(this->impl){
					return this->impl->GetUseCount();
				}
				return 0;
			}
		};

		/** [constructor]「weakptr」から「sharedptr」を作成。
		*/
		template <typename T> inline sharedptr<T>::sharedptr(const weakptr<T>& a_weakptr)
			:
			impl(a_weakptr.impl)
		{
			if(this->impl){
				if(this->impl->Use_Increment_IfNoZero()){
					//延命に成功。
					this->impl->Weak_Increment();
				}else{
					//延命に失敗。
					this->impl = nullptr;
				}
			}

			#if(BLIB_SHAREDPTR_CACHE_ENABLE)
			if(this->impl){
				this->cache = reinterpret_cast<T*>(this->impl->GetInstance());
			}else{
				this->cache = nullptr;
			}
			#endif
		}

	#endif

}

#if(BLIB_STDSHAREDPTR_ENABLE)

#else

	/** static_pointer_cast
	*/
	template <typename TO,class FROM> inline NBlib::sharedptr<TO> static_pointer_cast(const NBlib::sharedptr<FROM>& a_shaderptr) noexcept
	{
		return NBlib::sharedptr<TO>(a_shaderptr.impl);
	}

	/** 比較。
	*/
	template <typename T2> inline bool operator ==(const void* a_sharedptr_a,const NBlib::sharedptr<T2>& a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a == a_sharedptr_b.get());
	}

	/** 比較。
	*/
	template <typename T2> inline bool operator !=(const void* a_sharedptr_a,const NBlib::sharedptr<T2>& a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a != a_sharedptr_b.get());
	}

	/** 比較。
	*/
	template <typename T2> inline bool operator ==(const NBlib::sharedptr<T2>& a_sharedptr_a,const void* a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a.get() == a_sharedptr_b);
	}

	/** 比較。
	*/
	template <typename T2> inline bool operator !=(const NBlib::sharedptr<T2>& a_sharedptr_a,const void* a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a.get() != a_sharedptr_b);
	}

#endif

