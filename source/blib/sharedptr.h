#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �ushareptr�v�uweakptr�v�B
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

		/** sharedptrbase�B
	
			�J�E���g�̊Ǘ��B

		*/
		class sharedptrbase
		{
		private:
			/** �g�p���B
			*/
			volatile s32	use;

			/** �Q�Ɛ��B
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

			/** �m�ہB
			*/
			static void* Alloc(size_t a_size);

			/** ����B
			*/
			static void Free(void* a_pointer);

		public:
			/** �g�p���̎擾�B
			*/
			s32 GetUseCount() const
			{
				return this->use;
			}

			/** �Q�Ɛ��̎擾�B
			*/
			s32 GetWeakCount() const
			{
				return this->weak;
			}

		public:
			/** �폜�q�̎��s�B
			*/
			virtual void Delete() = 0;

			/** �C���X�^���X�̎擾�B
			*/
			virtual void* GetInstance() = 0;

			/** �g�p���f�N�������g�B
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

			/** �g�p�����O�łȂ��Ȃ�Ή����B
			*/
			bool Use_Increment_IfNoZero()
			{
				#if defined(PLATFORM_VCWIN)
				{
					for(;;){
						//�ŐV�̏�Ԃ��擾�B
						s32 t_count = static_cast<volatile s32&>(this->use);
						if(t_count == 0){
							//���łɎ���ł���B
							return false;
						}else{
							//�J�E���g���ut_count�v�̏ꍇ�́ut_count+1�v�ɂ���B
							if(static_cast<s32>(_InterlockedCompareExchange(reinterpret_cast<volatile long*>(&(this->use)),t_count+1,t_count) == t_count)){
								//�����ɐ����B
								return true;
							}else{
								//�uthis->use�v�̏����l���ut_count�v�ȊO�������B
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

			/** �g�p���A�Q�Ɛ����C���N�������g�B 
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

			/** �Q�Ɛ����f�N�������g�B
			*/
			bool Weak_Decrement()
			{
				#if defined(PLATFORM_VCWIN)
				{
					s32 t_ret = _InterlockedDecrement(reinterpret_cast<volatile long*>(&(this->weak)));
					if(t_ret <= 0){
						//���N���g�p���Ă��Ȃ��A�N���Q�Ƃ��Ă��Ȃ��B
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

			/** �Q�Ɛ����C���N�������g�B
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

		/** sharedptr_impl�B

			�J�E���g�A�C���X�^���X�A�폜�q�̊Ǘ��B

		*/
		template <typename T,typename D> class sharedptr_impl
			:
			public sharedptrbase
		{
		private:
			/** �C���X�^���X�B
			*/
			T*		instance;

			/** �폜�q�B
			*/
			D		deleter;

		public:
			/** constructor
			*/
			sharedptr_impl(const T* a_instance,D a_deleter)
				:
				sharedptrbase(),						// �J�E���g�̊Ǘ��B
				instance(const_cast<T*>(a_instance)),	// �C���X�^���X�̊Ǘ��B
				deleter(a_deleter)						// �폜�q�̊Ǘ��B
			{
			}

			/** destructor
			*/
			virtual ~sharedptr_impl() noexcept
			{
			}

		public:

			/** operator new
			*/
			static void* operator new(size_t a_size) noexcept
			{
				return sharedptrbase::Alloc(a_size);
			}
		
			/** operator delete
			*/
			static void operator delete(void* a_pointer) noexcept
			{
				sharedptrbase::Free(a_pointer);
			}

		private:
			/** �폜�q�̎��s�B
			*/
			virtual void Delete()
			{
				this->deleter(this->instance);
				this->instance = nullptr;
			}

			/** �C���X�^���X�̎擾�B
			*/
			virtual void* GetInstance()
			{
				return this->instance;
			}
		};

		/** nullsharedptr�B
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

			/** operator new
			*/
			static void* operator new(size_t /*a_size*/) noexcept
			{
				ASSERT(0);
				return nullptr;
			}
		
			/** operator delete
			*/
			static void operator delete(void* /*a_pointer*/) noexcept
			{
				ASSERT(0);
			}

		private:
			/** �폜�q�̎��s�B
			*/
			virtual void Delete()
			{
				ASSERT(0);
			}

			/** �C���X�^���X�̎擾�B
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
			//�J�E���g�A�C���X�^���X�A�폜�q�̊Ǘ��B
			sharedptrbase* impl;

			#if(BLIB_SHAREDPTR_CACHE_ENABLE)
			T* cache;
			#endif

			friend class weakptr<T>;

			/** null�B
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
				//nullsharedptr�`�F�b�N�B
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
				//���ݕێ����Ă���usharedptrbase�v�̎Q�Ɛ��A�g�p���̃f�N�������g�B
				if(this->impl){
					if(this->impl == a_sharedptrbase){
						//�ω��Ȃ��B
						return;
					}else{
						//�g�p�����O�ɂȂ����ꍇ�͍폜�q���Ăяo�����B
						this->impl->Use_Decrement();
						//�Ō�̎Q�Ƃ̏ꍇ�͍폜�B
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
			/** [constructor]nullptr�B
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

			/** [constructor]nullptr�B
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

			/** [constructor]nullsharedptr�B
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

			/** [constructor]�V�K�B�폜�q�Ȃ��B
			*/
			sharedptr(const T* a_instance) noexcept
			{
				//�J�n���͎g�p���P�A�Q�Ɛ��P�B
				if(a_instance != nullptr){
					this->impl = new sharedptr_impl<T,default_delete<T>>(a_instance,default_delete<T>());

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

			/** [constructor]�V�K�B�폜�q����B
			*/
			template <typename T2,typename D> sharedptr(const T2* a_instance,D a_deleter) noexcept
			{
				//�J�n���͎g�p���P�A�Q�Ɛ��P�B
				if(a_instance != nullptr){
					this->impl = new sharedptr_impl<T2,D>(a_instance,a_deleter);

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = const_cast<T2*>(a_instance);
					#endif
				}else{
					this->impl = nullptr;

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = nullptr;
					#endif
				}
			}

			/** [constructor]�uweakptr�v����usharedptr�v���쐬�B
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
				//�c�[���f�X�g���N�^�̌Ăяo���͍s����B
				a_sharedptr.impl = nullptr;
				a_sharedptr.cache = nullptr;
			}
			#endif

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

				//�V�����usharedptrbase�v�̎g�p���A�Q�Ɛ����C���N�������g�B
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
				UNUSED(check);

				//�V�����usharedptrbase�v�̎g�p���A�Q�Ɛ����C���N�������g�B
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

			/** ����B
			*/
			sharedptr<T>& operator =(const sharedptr<T>& a_sharedptr) noexcept
			{
				//�V�����usharedptrbase�v�̎g�p���A�Q�Ɛ����C���N�������g�B

				if(a_sharedptr.get() != nullptr){
					this->reset_impl(a_sharedptr.impl);
				}else{
					this->reset_impl(nullptr);
				}

				return *this;
			}

			/** ���Z�b�g�B
			*/
			void reset()
			{
				this->reset_impl(nullptr);
			}

			/** ���Z�b�g�B
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			void reset(nullptr_t)
			{
				this->reset_impl(nullptr);
			}
			#endif

			/** ���Z�b�g�B�폜�q�Ȃ��B
			*/
			void reset(T* a_instance)
			{
				this->reset_impl(nullptr);

				//�J�n���͎g�p���P�A�Q�Ɛ��P�B
				if(a_instance != nullptr){
					this->impl = new sharedptr_impl<T,default_delete<T>>(a_instance,default_delete<T>());

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = a_instance;
					#endif
				}
			}

			/** �V�K�B�폜�q����B
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			template <typename D> void reset(nullptr_t,D a_deleter)
			{
				this->reset_impl(nullptr);
			}
			#endif

			/** �V�K�B�폜�q����B
			*/
			template <typename T2,typename D> void reset(T2* a_instance,D a_deleter)
			{
				this->reset_impl(nullptr);

				//�J�n���͎g�p���P�A�Q�Ɛ��P�B
				if(a_instance != nullptr){
					this->impl = new sharedptr_impl<T2,D>(a_instance,a_deleter);

					#if(BLIB_SHAREDPTR_CACHE_ENABLE)
					this->cache = a_instance;
					#endif
				}
			}

			/** �X���b�v�B
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
			/** �|�C���^�̎擾�B
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

			/** �R���X�g�|�C���^�̎擾�B
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

			/** �|�C���^�̂悤�ɐU�����B
			*/
			typename reference_type<T>::type operator *() noexcept
			{
				return *(this->get());
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			T* operator ->() noexcept
			{
				return this->get();
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			typename reference_type<const T>::type operator *() const noexcept
			{
				return *(this->get());
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			const T* operator ->() const noexcept
			{
				return this->get();
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			operator bool() const noexcept
			{
				return (this->get()!=nullptr) ? true : false;
			}

			/** ��r�B
			*/
			template <typename T2> bool operator ==(const NBlib::sharedptr<T2>& a_sharedptr_b) const noexcept
			{
				return (this->get() == a_sharedptr_b.get());
			}

			/** ��r�B
			*/
			template <typename T2> bool operator !=(const NBlib::sharedptr<T2>& a_sharedptr_b) const noexcept
			{
				return (this->get() != a_sharedptr_b.get());
			}

			/** ��r�B
			*/
			bool operator ==(const void* a_sharedptr_b) const noexcept
			{
				return (this->get() == a_sharedptr_b);
			}

			/** ��r�B
			*/
			bool operator !=(const void* a_sharedptr_b) const noexcept
			{
				return (this->get() != a_sharedptr_b);
			}

		public:
			/** �g�p�����擾�B
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
			//�J�E���g�A�C���X�^���X�A�폜�q�̊Ǘ��B
			sharedptrbase* impl;
			friend class sharedptr<T>;

		public:
			/** ��B
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
				//�V�����usharedptrbase�v�̎Q�Ɛ����C���N�������g�B
				this->impl = a_sharedptr.impl;
				if(this->impl){
					this->impl->Weak_Increment();
				}
			}

			/** ����B
			*/
			template <class T2> weakptr& operator =(const sharedptr<T2>& a_sharedptr) noexcept
			{
				//���ݕێ����Ă���usharedptrbase�v�̎Q�Ɛ��̃f�N�������g�B
				if(this->impl){
					if(this->impl == a_sharedptr.impl){
						//�ω��Ȃ��B
						return (*this);
					}else{
						//�Ō�̎Q�Ƃ̏ꍇ�͍폜�B
						if(this->impl->Weak_Decrement()){
							delete this->impl;
						}
					}
				}

				//�V�����usharedptrbase�v�̎Q�Ɛ����C���N�������g�B
				this->impl = a_sharedptr.impl;
				if(this->impl){
					this->impl->Weak_Increment();
				}

				return (*this);
			}

			/** �uweakptr�v����usharedptr�v���쐬�B
			*/
			sharedptr<T> lock() noexcept
			{
				return sharedptr<T>(*this);
			}

			/** �uweakptr�v����usharedptr�v���쐬�B
			*/
			const sharedptr<T> lock() const noexcept
			{
				return sharedptr<T>(*this);
			}

			/** reset
			*/
			void reset() noexcept
			{
				//���ݕێ����Ă���usharedptrbase�v�̎Q�Ɛ��̃f�N�������g�B
				if(this->impl){
					//�Ō�̎Q�Ƃ̏ꍇ�͍폜�B
					if(this->impl->Weak_Decrement()){
						delete this->impl;
					}
				}
			}

			/** �g�p�����擾�B
			*/
			s32 use_count() const
			{
				if(this->impl){
					return this->impl->GetUseCount();
				}
				return 0;
			}
		};

		/** [constructor]�uweakptr�v����usharedptr�v���쐬�B
		*/
		template <typename T> inline sharedptr<T>::sharedptr(const weakptr<T>& a_weakptr)
			:
			impl(a_weakptr.impl)
		{
			if(this->impl){
				if(this->impl->Use_Increment_IfNoZero()){
					//�����ɐ����B
					this->impl->Weak_Increment();
				}else{
					//�����Ɏ��s�B
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

		/** scopedptr

		�폜�q�Ȃ��B

		*/
		template <typename T> class scopedptr
		{
		private:
			/** pointer
			*/
			T* pointer;

			/** reset_impl
			*/
			void reset_impl(T* a_pointer)
			{
				if(this->pointer != nullptr){
					STATIC_ASSERT(0<sizeof(T));
					delete this->pointer;
				}
				this->pointer = a_pointer;
			}

		public:
			/** constructor
			*/
			explicit scopedptr(T* a_pointer = nullptr)
				:
				pointer(a_pointer)
			{
			}

			/** destructor
			*/
			nonvirtual ~scopedptr()
			{
				this->reset_impl(nullptr);
			}

			/** reset
			*/
			void reset()
			{
				this->reset_impl(nullptr);
			}

			/** reset
			*/
			#if(BLIB_STDNULLPTR_ENABLE)
			void reset(nullptr_t)
			{
				this->reset_impl(nullptr);
			}
			#endif

			/** reset
			*/
			void reset(T* a_pointer)
			{
				this->reset_impl(a_pointer);
			}
		
			/** 
			*/
			typename reference_type<T>::type operator *()
			{
				return *this->pointer;
			}

			/** 
			*/
			const typename reference_type<T>::type operator *() const
			{
				return *(this->get());
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			T* operator ->()
			{
				return this->get();
			}

			/** �|�C���^�̂悤�ɐU�����B
			*/
			const T* operator ->() const
			{
				return this->get();
			}

			/** get
			*/
			T* get()
			{
				return this->pointer;
			}

			/** get
			*/
			const T* get() const
			{
				return this->pointer;
			}
     
			/** swap
			*/
			void swap(scopedptr<T>& a_scopedptr)
			{
				T* t_temp = this->pointer;
				this->pointer = a_scopedptr.pointer;
				a_scopedptr.pointer = t_temp;
			}
		};

	#endif

}

#if(BLIB_STDSHAREDPTR_ENABLE)

#else

	/** ��r�B
	*/
	template <typename T2> inline bool operator ==(const void* a_sharedptr_a,const NBlib::sharedptr<T2>& a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a == a_sharedptr_b.get());
	}

	/** ��r�B
	*/
	template <typename T2> inline bool operator !=(const void* a_sharedptr_a,const NBlib::sharedptr<T2>& a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a != a_sharedptr_b.get());
	}

	/** ��r�B
	*/
	template <typename T2> inline bool operator ==(const NBlib::sharedptr<T2>& a_sharedptr_a,const void* a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a.get() == a_sharedptr_b);
	}

	/** ��r�B
	*/
	template <typename T2> inline bool operator !=(const NBlib::sharedptr<T2>& a_sharedptr_a,const void* a_sharedptr_b) noexcept
	{
		return (a_sharedptr_a.get() != a_sharedptr_b);
	}

#endif

