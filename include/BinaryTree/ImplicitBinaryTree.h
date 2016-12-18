/** @file *//********************************************************************************************************

                                                 ImplicitBinaryTree.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/BinaryTree/ImplicitBinaryTree.h#2 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include <vector>


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < class N >
class ImplicitBinaryTree
{
public:

	class NodeRef
	{
	public:

		enum
		{
			INVALID		= 0,	// This is an invalid NodeRef value
			ROOT		= 1
		};

		NodeRef( size_t i );

		operator size_t() const;

		NodeRef	Left() const;
		NodeRef	Right() const;
		NodeRef	Parent() const;

		bool	IsLeft() const;
		bool	IsRight() const;
		bool	IsRoot() const;

		int		Depth() const;

	private:

		size_t	m_I;
	};

	explicit ImplicitBinaryTree( int depth );

	ImplicitBinaryTree( std::vector<N> & data );

	~ImplicitBinaryTree();

	N &			operator []( NodeRef const & i );
	N const &	operator []( NodeRef const & i ) const;

	NodeRef	Root() const	{ return NodeRef::ROOT; }
	size_t	Size() const	{ return m_size; }

private:

	enum { OFFSET = 1 };	// In order to avoid wasting space, the data is shifted left by 1

	std::vector<N>		m_data;
	size_t				m_size;
};


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

// inline functions

#include "ImplicitBinaryTree.inl"