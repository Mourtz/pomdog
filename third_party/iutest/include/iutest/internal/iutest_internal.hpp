//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_internal.hpp
 * @brief		iris unit test ������` �t�@�C��
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
#ifndef INCG_IRIS_iutest_internal_HPP_A5BD9FBB_B57A_4c1d_B205_0ADB7798DBF9_
#define INCG_IRIS_iutest_internal_HPP_A5BD9FBB_B57A_4c1d_B205_0ADB7798DBF9_

//======================================================================
// include
#include "../iutest_pred.hpp"
#include "../iutest_package.hpp"

//======================================================================
// define
/**
 * @internal
 * @brief	�e�X�g���쐬�}�N��
*/
#define IUTEST_TEST_CLASS_NAME_(testcase_, testname_)	IIUT_TEST_CLASS_NAME_I(IUTEST_TO_VARNAME_(testcase_), IUTEST_TO_VARNAME_(testname_))
#define IIUT_TEST_CLASS_NAME_I(testcase_, testname_)	IIUT_TEST_CLASS_NAME_I_(testcase_, testname_)
#define IIUT_TEST_CLASS_NAME_I_(testcase_, testname_)	iu_##testcase_##_x_##testname_##_Test

#define IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)	IIUT_TEST_INSTANCE_NAME_I(IUTEST_TO_VARNAME_(testcase_), IUTEST_TO_VARNAME_(testname_))
#define IIUT_TEST_INSTANCE_NAME_I(testcase_, testname_)		IIUT_TEST_INSTANCE_NAME_I_(testcase_, testname_)
#define IIUT_TEST_INSTANCE_NAME_I_(testcase_, testname_)	s_##testcase_##_##testname_##_Instance

#if IUTEST_HAS_TESTNAME_ALIAS

#define IUTEST_TO_VARNAME_(name_)				IIUT_TO_VARNAME_I( (IIUT_JAPANESE_NAME_PP_##name_, name_, dummy_) )
#define IIUT_TO_VARNAME_I(tuple_)				IUTEST_PP_EXPAND( IIUT_TO_VARNAME_I_ tuple_ )
#define IIUT_TO_VARNAME_I_(dummy, name_, ...)	name_

#define IUTEST_TO_NAME_(name_)					IIUT_TO_NAME_I( (IIUT_JAPANESE_NAME_PP_##name_, name_, name_, dummy_) )
#define IIUT_TO_NAME_I(tuple_)					IUTEST_PP_EXPAND( IIUT_TO_NAME_I_ tuple_ )
#define IIUT_TO_NAME_I_(dummy, dummy_2, name_, ...)	name_

#define IUTEST_TO_NAME_STR_(name_)				IUTEST_PP_TOSTRING( IUTEST_TO_NAME_(name_) )

#define IIUT_JAPANESE_NAME_PP_UNPAREN_(...)		__VA_ARGS__

#if	defined(_MSC_VER)
#  define IUTEST_ALIAS_TESTNAME_(name_)			name_
#  define IUTEST_ALIAS_TESTNAME_F_(var_, name_)	UNPAREN_(dummy, var_, name_)
#else
#  define IUTEST_ALIAS_TESTNAME_(name_)			UNPAREN_(dummy, IUTEST_PP_CAT(iutest_japanese_var, __LINE__), name_)
#  define IUTEST_ALIAS_TESTNAME_F_(var_, name_)	UNPAREN_(dummy, var_, name_)
#endif

#else

#define IUTEST_TO_VARNAME_(name_)				name_
#define IUTEST_TO_NAME_(name_)					name_
#define IUTEST_TO_NAME_STR_(name_)				#name_

#endif

#define IUTEST_TEST_F_(testfixture_, testname_)		IUTEST_TEST_(testfixture_, testname_, IUTEST_TO_VARNAME_(testfixture_)	\
														, ::iutest::internal::GetTypeId< IUTEST_TO_VARNAME_(testfixture_) >())

#define IUTEST_TEST_F_IGNORE_(testfixture_, testname_)	IUTEST_TEST_IGNORE_(testfixture_, testname_, IUTEST_TO_VARNAME_(testfixture_)	\
															, ::iutest::internal::GetTypeId< IUTEST_TO_VARNAME_(testfixture_) >())
/**
 * @internal
 * @brief	�e�X�g�N���X��`�}�N��
*/
#define IUTEST_TEST_(testcase_, testname_, parent_class_, type_id_)							\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public parent_class_ {			\
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));		\
		public:	IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}						\
		protected: virtual void Body(void);													\
	};																						\
	::iutest::detail::TestInstance<IUTEST_TEST_CLASS_NAME_(testcase_, testname_)>			\
	IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(										\
		IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)).c_str(), IUTEST_TO_NAME_STR_(testname_)	\
		, type_id_, parent_class_::SetUpTestCase, parent_class_::TearDownTestCase);			\
	void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

/**
 * @internal
 * @brief	�e�X�g�N���X��`�}�N��
 *			�֐��̒��̓R���p�C���ł��Ȃ��Ă��悢
*/
#define IUTEST_TEST_IGNORE_(testcase_, testname_, parent_class_, type_id_)					\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public parent_class_ {			\
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(	IUTEST_TEST_CLASS_NAME_(testcase_, testname_));		\
		public:	IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}						\
		protected: virtual void Body(void) { IUTEST_SKIP() << "ignored test..."; }			\
		template<typename T>void Body(void);												\
	};																						\
	::iutest::detail::TestInstance<IUTEST_TEST_CLASS_NAME_(testcase_, testname_)>			\
	IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(										\
		IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)).c_str(), IUTEST_TO_NAME_STR_(testname_)	\
		, type_id_, parent_class_::SetUpTestCase, parent_class_::TearDownTestCase);			\
	template<typename T>void IUTEST_TEST_CLASS_NAME_(testcase_, testname_ )::Body(void)

#ifndef IUTEST_NO_VARIADIC_MACROS

#define IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_)	IIUT_PMZ_TEST_CLASS_NAME_I(IUTEST_TO_VARNAME_(testcase_), IUTEST_TO_VARNAME_(testname_))
#define IIUT_PMZ_TEST_CLASS_NAME_I(testcase_, testname_)	IIUT_PMZ_TEST_CLASS_NAME_I_(testcase_, testname_)
#define IIUT_PMZ_TEST_CLASS_NAME_I_(testcase_, testname_)	IUTEST_PP_CAT( IUTEST_PP_CAT(iu_##testcase_##_x_Test_, testname_), __LINE__)
/**
 * @internal
 * @brief	�p�����^���C�Y�e�X�g��`�}�N��
*/
#define IIUT_TEST_PMZ_(testcase_, testname_, method_, parent_class_, type_id_, ...)				\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_);										\
	class IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_)	: public parent_class_ {			\
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_));		\
		public:	IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_)(void) {}						\
		static ::std::string MakeTestName(void) { return ::iutest::detail::MakeIndexTestName(	\
			IUTEST_TO_NAME_STR_(testname_), ::iutest::detail::GetTypeUniqueCounter<				\
				IUTEST_TEST_CLASS_NAME_(testcase_, testname_)>()); }							\
		protected: virtual void Body(void) { method_(__VA_ARGS__); }							\
	};																							\
	::iutest::detail::TestInstance<IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_)>			\
	IUTEST_PP_CAT( IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_), __LINE__)(					\
		IUTEST_CONCAT_PACKAGE_(IUTEST_TO_NAME_(testcase_)).c_str()								\
		, IUTEST_PMZ_TEST_CLASS_NAME_(testcase_, testname_)::MakeTestName().c_str()				\
		, #__VA_ARGS__, type_id_, parent_class_::SetUpTestCase, parent_class_::TearDownTestCase)

#endif

/**
 * @internal
 * @brief	ASSERTION ���b�Z�[�W����
*/
#define IUTEST_MESSAGE_AT(file_, line_, msg_, result_type_)	::iutest::AssertionHelper(file_, line_, msg_, result_type_) = ::iutest::AssertionHelper::Fixed()
#define IUTEST_MESSAGE(msg_, result_type_)					IUTEST_MESSAGE_AT(__FILE__, __LINE__, msg_, result_type_)

/**
 * @internal
 * @brief	ASSERT ���b�Z�[�W����
*/
#define IUTEST_ASSERT_FAILURE(msg)					IUTEST_ASSERT_FAILURE_AT(msg, __FILE__, __LINE__)

#if !defined(IUTEST_NO_VOID_RETURNS)
#  define IUTEST_ASSERT_FAILURE_AT(msg, file, line)	return IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kFatalFailure)
#else
#  define IUTEST_ASSERT_FAILURE_AT(msg, file, line)	IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kFatalFailure)
#endif

/**
 * @internal
 * @brief	EXPECT ���b�Z�[�W����
*/
#define IUTEST_EXPECT_FAILURE(msg)					IUTEST_EXPECT_FAILURE_AT(msg, __FILE__, __LINE__)

#define IUTEST_EXPECT_FAILURE_AT(msg, file, line)	IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kNonFatalFailure)

/**
 * @internal
 * @brief	INFORM ���b�Z�[�W����
*/
#define IUTEST_INFORM_FAILURE(msg)					IUTEST_INFORM_FAILURE_AT(msg, __FILE__, __LINE__)

#define IUTEST_INFORM_FAILURE_AT(msg, file, line)	IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kWarning)

/**
 * @internal
 * @brief	ASSUME ���b�Z�[�W����
*/
#define IUTEST_ASSUME_FAILURE(msg)					IUTEST_ASSUME_FAILURE_AT(msg, __FILE__, __LINE__)

#define IUTEST_ASSUME_FAILURE_AT(msg, file, line)	return IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kAssumeFailure)


#ifndef IUTEST_MAKE_ASSERTIONRESULT_
#  define IUTEST_MAKE_ASSERTIONRESULT_(ar)	ar
#endif

/**
 * @internal
 * @biref	��r���؃}�N��
*/
#define IUTEST_TEST_ASSERT_(expression, on_failure)	\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_					\
	if( const ::iutest::AssertionResult iutest_ar = IUTEST_MAKE_ASSERTIONRESULT_(expression) )	\
		;											\
	else											\
		on_failure(iutest_ar.message())

#if IUTEST_HAS_EXCEPTIONS
/**
 * @internal
 * @brief	throw �e�X�g�p�}�N��
*/
#define IUTEST_TEST_THROW_(statement, expected_exception, on_failure)		\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( const char* msg = "" ) {											\
		try {																\
			IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING((void)(statement));	\
			msg = "\nExpected: " #statement " throws an exception of type "	\
				  #expected_exception ".\n  Actual: it throws nothing.";	\
			goto IUTEST_PP_CAT(iutest_label_throw, __LINE__);				\
		} catch( expected_exception const& ) {								\
		} catch( ... ) {													\
			msg = "\nExpected: " #statement " throws an exception of type "	\
          #expected_exception ".\n  Actual: it throws a different type.";	\
			goto IUTEST_PP_CAT(iutest_label_throw, __LINE__);				\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_throw, __LINE__):						\
		on_failure(msg)

/**
 * @internal
 * @brief	throw �e�X�g�p�}�N��
*/
#define IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, pred_formatter)	\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_														\
	if( ::iutest::AssertionResult iutest_ar = ::iutest::AssertionSuccess() ) {			\
		try {																			\
			IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING((void)(statement));				\
			iutest_ar << "\nExpected: " #statement " throws an exception of type "		\
				#expected_exception ".\n  Actual: it throws nothing.";					\
			goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);						\
		} catch( expected_exception const& e) {											\
			if( const ::iutest::AssertionResult	ar										\
				= pred_formatter("e", #expected_exception_value, e, expected_exception_value) ) {			\
			} else {																	\
				iutest_ar << "\nExpected: " #statement " throws an exception of value\n" << ar.message();	\
				goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);					\
			}																			\
		} catch( ... ) {																\
			iutest_ar << "\nExpected: " #statement " throws an exception of type "		\
				#expected_exception ".\n  Actual: it throws a different type.";			\
			goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);						\
		}																				\
	} else																				\
		IUTEST_PP_CAT(iutest_label_throw_value, __LINE__):								\
		on_failure(iutest_ar.message())

#define IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_exception_value, on_failure)	\
	IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, ::iutest::internal::EqHelper<IUTEST_IS_NULLLITERAL(expected_exception_value)>::Compare)
#define IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, expected_exception_value, on_failure)	\
	IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, ::iutest::internal::NeHelper<IUTEST_IS_NULLLITERAL(expected_exception_value)>::Compare)
#define IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_exception_value, on_failure)	\
	IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, ::iutest::internal::CmpHelperSTREQ)
#define IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_exception_value, on_failure)	\
	IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, ::iutest::internal::CmpHelperSTRCASEEQ)

/**
 * @internal
 * @brief	any throw �e�X�g�p�}�N��
*/
#define IUTEST_TEST_ANY_THROW_(statement, on_failure)						\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::detail::AlwaysTrue() ) {									\
		try {																\
			(void)(statement);												\
			goto IUTEST_PP_CAT(iutest_label_anythrow, __LINE__);			\
		} catch( ... ) {													\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_anythrow, __LINE__):						\
		on_failure("\nExpected: " #statement " throws an exception.\n  Actual: it doesn's throws.")

/**
 * @internal
 * @brief	no throw �e�X�g�p�}�N��
*/
#define IUTEST_TEST_NO_THROW_(statement, on_failure)						\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::AssertionResult iutest_ar = ::iutest::AssertionSuccess() ) {	\
		try {																\
			(void)(statement);												\
		} catch( const ::std::exception& e ) {								\
			iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws. what is \""	\
				<< e.what() << "\"";										\
			goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);				\
		} catch( const char *e ) {											\
			iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws. \""	\
				<< e << "\"";												\
			goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);				\
		} catch( ... ) {													\
			iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws.";	\
			goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);				\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_nothrow, __LINE__):						\
		on_failure(iutest_ar.message())

#endif

#define IUTEST_TEST_BOOLEAN_(expression, text, actual, expected, on_failure)	\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_												\
	if( const ::iutest::AssertionResult iutest_ar = ::iutest::AssertionResult((expression) ? true : false) )	\
		;																		\
	else																		\
		on_failure(::iutest::internal::GetBooleanAssertionFailureMessage(		\
			iutest_ar, text, #actual, #expected).c_str() )

/**
 * @internal
 * @brief	�����I�Ȏ��s
*/
#define IUTEST_ASSERT(cond)					do { if( !(cond) ) {												\
												IUTEST_MESSAGE(#cond, ::iutest::TestPartResult::kFatalFailure);	\
												exit(1);														\
											} } while(::iutest::detail::AlwaysFalse())

#define IIUT_SUCCEED()						IUTEST_MESSAGE("Succeeded.\n", ::iutest::TestPartResult::kSuccess)
#define IIUT_FAIL()							IUTEST_ASSERT_FAILURE("Failed.\n")
#define IIUT_ADD_FAILURE()					IUTEST_EXPECT_FAILURE("Failed.\n")
#define IIUT_ADD_FAILURE_AT(file_, line_)	IUTEST_EXPECT_FAILURE_AT("Failed.\n", file_, line_)

/**
 * @internal
 * @brief	���b�Z�[�W���M���O
*/
#define IIUT_SCOPED_MESSAGE(msg_)			\
	const ::iutest::AssertionHelper::ScopedMessage IUTEST_PP_CAT(scoped_message_, IUTEST_PP_COUNTER) = ::iutest::detail::iuCodeMessage(__FILE__, __LINE__, ::iutest::Message() << (msg_))

/**
 * @internal
 * @brief	IUTEST_ANALYSIS_ASSUME_ ��ʂ�
*/
#if defined(_MSC_VER) && _MSC_VER >= 1500

#define IUTEST_THROUGH_ANALYSIS_ASSUME_(expr, todo)					\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_									\
	if( bool b = true ) {											\
		IUTEST_UNUSED_VAR(b);										\
		__analysis_assume(expr);									\
		goto IUTEST_PP_CAT(iutest_label_analysis_assume, __LINE__);	\
	} else															\
		IUTEST_PP_CAT(iutest_label_analysis_assume, __LINE__):		\
		todo

#else

#define IUTEST_THROUGH_ANALYSIS_ASSUME_(expr, todo)	todo

#endif

/**
 * @internal
 * @brief	�e�X�g�}�N��
 * @{
*/
#define	IUTEST_TEST_EQ(expected, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iutest::internal::EqHelper<IUTEST_IS_NULLLITERAL(expected)>::Compare, expected, actual, on_failure )
#define	IUTEST_TEST_NE(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::NeHelper<IUTEST_IS_NULLLITERAL(v1)>::Compare, v1, v2, on_failure )
//#define	IUTEST_TEST_NE(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperNE, v1, v2, on_failure )
#define	IUTEST_TEST_LE(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperLE, v1, v2, on_failure )
#define	IUTEST_TEST_LT(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperLT, v1, v2, on_failure )
#define	IUTEST_TEST_GE(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperGE, v1, v2, on_failure )
#define	IUTEST_TEST_GT(v1, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperGT, v1, v2, on_failure )

#define IUTEST_TEST_TRUE(expr, text, on_failure)		IUTEST_TEST_BOOLEAN_( expr, text, false, true, on_failure)
#define IUTEST_TEST_FALSE(expr, text, on_failure)		IUTEST_TEST_BOOLEAN_( !(expr), text, true, false, on_failure)

#define IUTEST_TEST_FLOAT_EQ(expected, actual, on_failure)		IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointEQ<float> , expected, actual, on_failure )
#define IUTEST_TEST_DOUBLE_EQ(expected, actual, on_failure)		IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointEQ<double>, expected, actual, on_failure )

#define IUTEST_TEST_NEAR(v1, v2, abs_v, on_failure)		IUTEST_PRED_FORMAT3_( ::iutest::internal::CmpHelperNear, v1, v2, abs_v, on_failure )

#define	IUTEST_TEST_STREQ(expected_str, actual_str, on_failure)		IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTREQ, expected_str, actual_str, on_failure )
#define	IUTEST_TEST_STRNE(v1, v2, on_failure)						IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRNE, v1, v2, on_failure )
#define	IUTEST_TEST_STRCASEEQ(expected_str, actual_str, on_failure)	IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRCASEEQ, expected_str, actual_str, on_failure )
#define	IUTEST_TEST_STRCASENE(v1, v2, on_failure)					IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRCASENE, v1, v2, on_failure )

#define IUTEST_TEST_HRESULT_SUCCEEDED(hr, on_failure)	IUTEST_PRED_FORMAT1_( ::iutest::internal::IsHRESULTSuccess, hr, on_failure )
#define IUTEST_TEST_HRESULT_FAILED(hr, on_failure)		IUTEST_PRED_FORMAT1_( ::iutest::internal::IsHRESULTFailure, hr, on_failure )

#define IUTEST_TEST_NULL(v, on_failure)					IUTEST_THROUGH_ANALYSIS_ASSUME_(v==NULL, IUTEST_PRED_FORMAT1_( ::iutest::internal::CmpHelperNull, v, on_failure ))
#define IUTEST_TEST_NOTNULL(v, on_failure)				IUTEST_THROUGH_ANALYSIS_ASSUME_(v!=NULL, IUTEST_PRED_FORMAT1_( ::iutest::internal::CmpHelperNotNull, v, on_failure ))

#define IUTEST_TEST_SAME(v1, v2, on_failure)			IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSame, v1, v2, on_failure )

#define IUTEST_TEST_NO_FAILURE_(statement, on_failure)				\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::detail::AlwaysTrue() ) {									\
		::iutest::detail::NewTestPartResultCheckHelper::Counter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondNe<			\
			::iutest::TestPartResult::kSuccess> >	iutest_failure_checker;	\
		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING( { (void)0; statement; } )	\
		if( iutest_failure_checker.count() > 0 ) {							\
			goto IUTEST_PP_CAT(iutest_label_test_no_failure_, __LINE__);	\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_test_no_failure_, __LINE__):			\
		on_failure("\nExpected: " #statement " doesn't generate new failure.\n  Actual: it does.")

#define IUTEST_TEST_NO_FATAL_FAILURE_(statement, on_failure)				\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::detail::AlwaysTrue() ) {									\
		::iutest::detail::NewTestPartResultCheckHelper::Counter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondEq<			\
			::iutest::TestPartResult::kFatalFailure> >	iutest_failure_checker;	\
		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING( { (void)0; statement; } )	\
		if( iutest_failure_checker.count() > 0 ) {							\
			goto IUTEST_PP_CAT(iutest_label_test_no_fatalfailure_, __LINE__);	\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_test_no_fatalfailure_, __LINE__):		\
		on_failure("\nExpected: " #statement " doesn't generate new fatal failure.\n  Actual: it does.")

#define IUTEST_TEST_SKIP()					\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_			\
	if( !::iutest::Test::HasFailure() )		\
		::iutest::UnitTest::SkipTest();		\
	if( ::iutest::detail::AlwaysTrue() )	\
		return IUTEST_MESSAGE( ::iutest::Test::HasFailure() ? "Skipped. but already failed. " : "Skipped. ", ::iutest::TestPartResult::kSkip)

/**
 * @}
*/

#endif