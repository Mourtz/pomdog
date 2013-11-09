//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_typed_tests.hpp
 * @brief		iris unit test typed test �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_typed_tests_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_
#define INCG_IRIS_iutest_typed_tests_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_

//======================================================================
// include
#include "internal/iutest_typed_util.hpp"

#if IUTEST_HAS_TYPED_TEST_P
#  include "internal/iutest_pool.hpp"
#endif

//======================================================================
// define

#if IUTEST_HAS_TYPED_TEST

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST_CASE(testcase_, types_)
 * @brief	�^�t���e�X�g�P�[�X�̓o�^
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	types_		= �^�C�v���X�g
*/
#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IUTEST_TYPED_TEST_CASE(testcase_, ...)	IIUT_TYPED_TEST_CASE_(testcase_, __VA_ARGS__)
#else
#  define IUTEST_TYPED_TEST_CASE(testcase_, types_)	IIUT_TYPED_TEST_CASE_(testcase_, types_)
#endif

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST(testcase_, testname_)
 * @brief	�^�t���e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
*/
#define IUTEST_TYPED_TEST(testcase_, testname_)		IIUT_TYPED_TEST_(testcase_, testname_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_T(testcase_, testname_)
 * @brief	�^�t���e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
*/
#define IUTEST_T(testcase_, testname_)				IIUT_TYPED_TEST_(testcase_, testname_)


/**
 * @private
 * @{
*/
#define IUTEST_TYPED_TEST_PARAMS_(testcase_)		IIUT_TYPED_TEST_PARAMS_I(IUTEST_TO_VARNAME_(testcase_))
#define IIUT_TYPED_TEST_PARAMS_I(testcase_)			IIUT_TYPED_TEST_PARAMS_I_(testcase_)
#define IIUT_TYPED_TEST_PARAMS_I_(testcase_)		iutest_types_params_##testcase_

#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IIUT_TYPED_TEST_CASE_(testcase_, ...)		\
	typedef ::iutest::detail::TypeList< __VA_ARGS__ >::type	IUTEST_TYPED_TEST_PARAMS_(testcase_)
#else
#  define IIUT_TYPED_TEST_CASE_(testcase_, types_)		\
	typedef ::iutest::detail::TypeList< types_ >::type	IUTEST_TYPED_TEST_PARAMS_(testcase_)
#endif

#define IIUT_TYPED_TEST_(testcase_, testname_)										\
	template<typename iutest_TypeParam>												\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_)								\
	: public IUTEST_TO_VARNAME_(testcase_)<iutest_TypeParam> {						\
		typedef IUTEST_TO_VARNAME_(testcase_)<iutest_TypeParam> TestFixture;		\
		typedef iutest_TypeParam	TypeParam;										\
		protected: virtual void Body(void);											\
	};																				\
	::iutest::detail::TypeParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_, testname_)			\
		, IUTEST_TYPED_TEST_PARAMS_(testcase_) > IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(	\
		IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)), IUTEST_TO_NAME_STR_(testname_));		\
	template<typename iutest_TypeParam>												\
	void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)<iutest_TypeParam>::Body(void)

#define IIUT_TYPED_TEST_IGNORE_(testcase_, testname_)								\
	template<typename iutest_TypeParam>												\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_)								\
	: public IUTEST_TO_VARNAME_(testcase_)<iutest_TypeParam> {						\
		typedef IUTEST_TO_VARNAME_(testcase_)<iutest_TypeParam> TestFixture;		\
		typedef iutest_TypeParam	TypeParam;										\
		protected: virtual void Body(void) { IUTEST_SKIP() << "ignored test..."; }	\
		template<typename T>void Body(void);										\
	};																				\
	::iutest::detail::TypeParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_, testname_)			\
		, IUTEST_TYPED_TEST_PARAMS_(testcase_) > IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(	\
		IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)), IUTEST_TO_NAME_STR_(testname_) );		\
	template<typename iutest_TypeParam>												\
	template<typename T>void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)<iutest_TypeParam>::Body(void)

/**
 * @}
*/

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST_CASE_P(testcase_)
 * @brief	�^�p�����[�^�e�X�g�P�[�X�̓o�^
 * @param	testcase_	= �e�X�g�P�[�X��
*/
#define IUTEST_TYPED_TEST_CASE_P(testcase_)				IIUT_TYPED_TEST_CASE_P_(testcase_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TYPED_TEST_P(testcase_, testname_)
 * @brief	�^�p�����[�^�e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
*/
#define IUTEST_TYPED_TEST_P(testcase_, testname_)		IIUT_TYPED_TEST_P_(testcase_, testname_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_TP(testcase_, testname_)
 * @brief	�^�p�����[�^�e�X�g�֐���`�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	testname_	= �e�X�g��
*/
#define IUTEST_TP(testcase_, testname_)					IIUT_TYPED_TEST_P_(testcase_, testname_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_REGISTER_TYPED_TEST_CASE_P(testcase_, ...)
 * @brief	�^�p�����[�^�e�X�g�֐��o�^�}�N��
 * @param	testcase_	= �e�X�g�P�[�X��
*/
#define IUTEST_REGISTER_TYPED_TEST_CASE_P(testcase_, ...)	IIUT_REGISTER_TYPED_TEST_CASE_P_(testcase_, __VA_ARGS__)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(prefix_, testcase_, types_)
 * @brief	�^�p�����[�^�e�X�g�o�^�}�N��
 * @param	prefix_		= �C���X�^���X��
 * @param	testcase_	= �e�X�g�P�[�X��
 * @param	...			= �^�C�v���X�g
*/
#define IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(prefix_, testcase_, ...)	IIUT_INSTANTIATE_TYPED_TEST_CASE_P_(prefix_, testcase_, __VA_ARGS__)


/**
 * @private
 * @{
*/

#define IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_)	s_iutest_typed_test_case_p_state_##testcase_##_
#define IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_)		iutest_typed_test_case_p_name_##testcase_##_

#define IIUT_TYPED_TEST_CASE_P_(testcase_)		\
	static ::iutest::detail::TypedTestCasePState	IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_)

#define IIUT_TYPED_TEST_P_(testcase_, testname_)				\
	namespace IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_) {		\
	template<typename iutest_TypeParam>							\
	class testname_ : public testcase_<iutest_TypeParam> {		\
		typedef testcase_<iutest_TypeParam> TestFixture;		\
		typedef iutest_TypeParam	TypeParam;					\
		protected: virtual void Body(void);						\
	};															\
	static const int s_iutest_##testname_##_defined_dummy_ IUTEST_ATTRIBUTE_UNUSED_ =	\
	IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).AddTestName(__FILE__, __LINE__, #testcase_, #testname_);		\
	}															\
	template<typename iutest_TypeParam>							\
	void IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_)::testname_<iutest_TypeParam>::Body(void)

#define IIUT_TYPED_TEST_P_IGNORE_(testcase_, testname_)			\
	namespace IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_) {		\
	template<typename iutest_TypeParam>							\
	class testname_ : public testcase_<iutest_TypeParam> {		\
		typedef testcase_<iutest_TypeParam> TestFixture;		\
		typedef iutest_TypeParam	TypeParam;					\
		protected: virtual void Body(void) { IUTEST_SKIP() << "ignored test..."; }		\
		template<typename T>void Body(void);					\
	};															\
	static const int s_iutest_##testname_##_defined_dummy_ IUTEST_ATTRIBUTE_UNUSED_ =	\
	IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).AddTestName(__FILE__, __LINE__, #testcase_, #testname_);		\
	}															\
	template<typename iutest_TypeParam>template<typename T>		\
	void IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_)::testname_<iutest_TypeParam>::Body(void)

#define IIUT_REGISTER_TYPED_TEST_CASE_P_(testcase_, ...)								\
	namespace IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_) {								\
		typedef ::iutest::detail::Templates< __VA_ARGS__ >::type	iutest_AllTests_;	\
	}																					\
	static const bool s_iutest_##testcase_##_register_dummy_ IUTEST_ATTRIBUTE_UNUSED_ =	\
	IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).VerifyTestNames(__FILE__, __LINE__, #__VA_ARGS__)

#define IIUT_INSTANTIATE_TYPED_TEST_CASE_P_(prefix_, testcase_, ...)		\
	const bool iutest_##prefix_##_##testcase_ IUTEST_ATTRIBUTE_UNUSED_ =	\
		::iutest::detail::TypeParameterizedTestCase< testcase_				\
		, IUTEST_TYPED_TEST_P_NAMESPACE_(testcase_)::iutest_AllTests_		\
		, ::iutest::detail::TypeList< __VA_ARGS__ >::type >::Register(		\
			#prefix_, IUTEST_TO_NAME_STR_(testcase_), IUTEST_GET_PACKAGENAME_()	\
		, IUTEST_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).names())

/**
 * @}
*/

#endif

namespace iutest
{

//======================================================================
// class
namespace detail
{

#if IUTEST_HAS_TYPED_TEST
/**
 * @private
 * @internal
 * @brief	Type�p�����[�^�P�̃e�X�g�C���X�^���X
 * @tparam	Tester		= �e�X�g�N���X
 * @tparam	TypeParams	= �^
*/
template<template <typename T> class Tester, typename TypeParams>
class TypeParamTestInstance
{
	/**
	 * @brief	�e�e�X�g�̃C���X�^���X
	*/
	template<typename TT, typename DMY>
	class EachTest
	{
		typedef typename TT::Head			TypeParam;
		typedef Tester<TypeParam>			TestBody;
		typedef TypedTestCase<TypeParam>	_MyTestCase;
	public:
		// �R���X�g���N�^
		EachTest(const char* testcase, const char* name, int index)
			: m_mediator(UnitTest::instance().AddTestCase<_MyTestCase>(
				detail::MakeIndexTestName(testcase, index).c_str()
				//detail::MakeIndexTypedTestName<TypeParam>(testcase, index).c_str()
				, internal::GetTypeId<detail::None>()	// TypeId �𓝈ꂷ�邽�߃_�~�[������n��
				, TestBody::SetUpTestCase
				, TestBody::TearDownTestCase))
			, m_info(&m_mediator, name, &m_factory)
			, m_next(testcase, name, index+1)
		{
		}
	public:
		// �e�X�g�̓o�^
		void	AddTest(void)
		{
			// ���Ԓʂ�ɂȂ�悤�ɑO����o�^
			UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
			m_next.AddTest();
		}
	private:
		TestCaseMediator			m_mediator;
		TestInfo					m_info;
		detail::iuFactory<TestBody>	m_factory;

		EachTest<typename TT::Tail, void>	m_next;
	};

	// �I�[
	template<typename DMY>
	class EachTest<detail::TypeList0, DMY>
	{
	public:
		EachTest(const char* /*testcase*/, const char* /*name*/, int /*index*/)	{}
		void	AddTest(void) {}
	};

public:
	// �R���X�g���N�^
	TypeParamTestInstance(const ::std::string& testcase, const char* name)
		: m_tests(testcase.c_str(), name, 0)
	{
		m_tests.AddTest();
	}

private:
	EachTest<TypeParams, void>	m_tests;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeParamTestInstance);
};

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @private
 * @internal
 * @brief	Typed TestCase �ݒ�ێ� 
*/
class TypedTestCasePState
{
public:
	TypedTestCasePState(void) : m_names(NULL) {}
public:
	const char*	names(void) const { return m_names; }

public:
	bool	AddTestName(const char* file, int line, const char* testcase_name, const char* test_name)
	{
		if( m_names != NULL )
		{
			fprintf(stderr, "%s Test %s must be defined before IUTEST_REGISTER_TYPED_TEST_CASE_P(%s, ...).\n"
				, detail::FormatCompilerIndependentFileLocation(file, line).c_str(), test_name, testcase_name);
			fflush(stderr);
		}
#if IUTEST_TYPED_TEST_P_STRICT
		m_list.insert(test_name);
#endif
		return true;
	}
	bool	VerifyTestNames(const char* file, int line, const char* test_names)
	{
		m_names = test_names;
		IUTEST_UNUSED_VAR(file);
		IUTEST_UNUSED_VAR(line);
		return Verify(test_names);
	}

private:
	bool	Verify(const char* names)
	{
#if IUTEST_TYPED_TEST_P_STRICT
		if( names == NULL ) return true;
		const char* comma = FindComma(names);
		::std::string name;
		if( comma == NULL ) name = names;
		else
		{
			name.append(names, comma - names);
			++comma;
		}
		if( m_list.find(name.c_str()) == m_list.end() ) return false;
		return Verify(SkipSpace(comma));
#else
		return true;
#endif
	}

private:
	const char* m_names;

#if IUTEST_TYPED_TEST_P_STRICT
	::std::set<const char*>	m_list;
#endif

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypedTestCasePState);
};

/**
 * @private
 * @brief	�^�p�����[�^�e�X�g�̃C���X�^���X���N���X
*/
template<IUTEST_TEMPLATE_TPARAM1 Fixture, typename Tests, typename Types>
class TypeParameterizedTestCase
{
	class IEachTest
	{
	public:
		virtual ~IEachTest(void) {}
	};

	template<typename TypeParam, typename TestsList>
	class EachTest : public IEachTest
	{
		typedef typename TestsList::Head	TypeSel;
		typedef typename TypeSel::template bind<TypeParam>::type	TestBody;
		typedef detail::iuFactory<TestBody>	Factory;
		typedef EachTest<TypeParam, TestsList>	_Myt;

		EachTest(TestCase* testcase, const char* name)
			: m_mediator(testcase)
			, m_info(&m_mediator, name, &m_factory)
		{
			UnitTest::instance().AddTestInfo(testcase, &m_info);
		}
	public:
		// �e�X�g�̓o�^
		static void Register(TestCase* testcase, const char* test_names)
		{
			const char* str = detail::SkipSpace(test_names);
			const char* comma = strchr(str, ',');
			::std::string test_name;
			if( comma == NULL ) 
			{
				test_name = str;
			}
			else
			{
				test_name.append(str, comma - str);
				++comma;
			}
			_Myt* test = new EachTest(testcase, test_name.c_str());
			// new �I�u�W�F�N�g���Ǘ����Ă��炤
			detail::iuPool<IEachTest>::GetInstance().push(test);

			EachTest<TypeParam, typename TestsList::Tail>::Register(testcase, detail::SkipSpace(comma));
		}
	private:
		TestCaseMediator	m_mediator;
		Factory				m_factory;
		TestInfo			m_info;
	};

	template<typename TypeParam>
	class EachTest<TypeParam, detail::TemplateTypeList0>
	{
	public:
		static void Register(TestCase* /*testcase*/, const char* /*test_names*/) {}
	};

public:
	/**
	 * @brief	�e�X�g�̓o�^
	*/
	static bool Register(const char* prefix, const char* testcase_name, const::std::string& package_name, const char* names, int index=0)
	{
		typedef typename Types::Head	TypeParam;
		typedef typename Tests::Head	Head;
		typedef Fixture<Head>			FixtureClass;
		typedef TypedTestCase<TypeParam>	_MyTestCase;
		TestCase* testcase = UnitTest::instance().AddTestCase<_MyTestCase>(
			(package_name + detail::MakePrefixedIndexTestName(prefix, testcase_name, index)).c_str()
			//detail::MakePrefixedIndexTypedTestName<TypeParam>(prefix, testcase_name, index).c_str()
			, internal::GetTypeId<FixtureClass>()
			, FixtureClass::SetUpTestCase, FixtureClass::TearDownTestCase);

		EachTest<TypeParam, Tests>::Register(testcase, names);

		return TypeParameterizedTestCase<Fixture, Tests, typename Types::Tail>::Register(prefix, testcase_name, package_name, names, index + 1);
	}
};

/**
 * @private
 * @brief	�^�p�����[�^�e�X�g�̃C���X�^���X���N���X
 *			�I�[���ꉻ
*/
template<IUTEST_TEMPLATE_TPARAM1 Fixture, typename Tests>
class TypeParameterizedTestCase<Fixture, Tests, detail::TypeList0>
{
public:
	static bool Register(const char* /*prefix*/, const char* /*testcase_name*/, const ::std::string& /*package_name*/, const char* /*names*/, int index=0)
	{
		IUTEST_UNUSED_VAR(index);
		return true;
	}
};

#endif

}	// end of namespace detail
}	// end of namespace iutest

#endif