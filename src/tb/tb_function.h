#pragma once

namespace tb
{
	namespace Internal
	{
		template<typename Result, typename ...Args>
		struct abstract_function
		{
			virtual Result operator()(Args... args) = 0;
			virtual abstract_function *clone() const = 0;
			virtual ~abstract_function() {}
		};

		template<typename Func, typename Result, typename ...Args>
		class concrete_function : public abstract_function<Result, Args...>
		{
		private:
			Func m_func;

		public:
			concrete_function(const Func &x)
				: m_func(x)
			{
			}

			virtual Result operator()(Args... args)
			{
				return m_func(args...);
			}

			virtual concrete_function* clone() const
			{
				return new concrete_function(m_func);
			}
		};

		template<typename Func>
		struct func_filter
		{
			typedef Func type;
		};

		template<typename Result, typename ...Args>
		struct func_filter<Result(Args...)>
		{
			typedef Result(*type)(Args...);
		};
	}

	template<typename signature>
	class Function;

	template<typename Result, typename ...Args>
	class Function<Result(Args...)>
	{
	private:
		Internal::abstract_function<Result, Args...>* m_func;

	public:
		Function()
		{
			m_func = nullptr;
		}

		template<typename Func>
		Function(const Func &x)
		{
			m_func = new Internal::concrete_function<typename Internal::func_filter<Func>::type, Result, Args...>(x);
		}

		Function(const Function &rhs)
		{
			m_func = nullptr;
			if (rhs.m_func != nullptr) {
				m_func = rhs.m_func->clone();
			}
		}

		~Function()
		{
			if (m_func != nullptr) {
				delete m_func;
			}
		}

		Function &operator=(const Function &rhs)
		{
			if (&rhs != this && rhs.m_func != nullptr)
			{
				auto temp = rhs.m_func->clone();
				if (m_func != nullptr) {
					delete m_func;
				}
				m_func = temp;
			}
			return *this;
		}

		template<typename Func>
		Function &operator=(const Func &x)
		{
			auto temp = new Internal::concrete_function<typename Internal::func_filter<Func>::type, Result, Args...>(x);
			if (m_func != nullptr) {
				delete m_func;
			}
			m_func = temp;
			return *this;
		}

		Result operator()(Args... args)
		{
			if (m_func == nullptr) {
				return Result();
			}
			return (*m_func)(args...);
		}
	};
}
