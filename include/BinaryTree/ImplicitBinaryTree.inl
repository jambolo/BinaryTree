/** @file *//********************************************************************************************************

                                                ImplicitBinaryTree.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/BinaryTree/ImplicitBinaryTree.inl#2 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "ImplicitBinaryTree.h"

#include <memory>
#include <cassert>


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
ImplicitBinaryTree<N>::ImplicitBinaryTree( int depth )
	: m_data( ( 1 << depth ) - OFFSET )
{
	assert( depth > 0 );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
ImplicitBinaryTree<N>::ImplicitBinaryTree( std::vector<N> & data )
{
	m_data.swap( data );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
ImplicitBinaryTree<N>::~ImplicitBinaryTree()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
N & ImplicitBinaryTree<N>::operator []( NodeRef const & i )
{
	assert_limits( 0, i - OFFSET, m_data.size()-1 );

	return m_data[ i - OFFSET ];	// To avoid wasting space, data is shifted left
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
N const & ImplicitBinaryTree<N>::operator []( NodeRef const & i ) const
{
	assert_limits( 0, i - OFFSET, m_data.size()-1 );

	return m_data[ i - OFFSET ];	// To avoid wasting space, data is shifted left
}


/********************************************************************************************************************/
/*																													*/
/*														NodeRef														*/
/*																													*/
/********************************************************************************************************************/


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
ImplicitBinaryTree<N>::NodeRef::NodeRef( size_t i )
	: m_i( i )
{
	assert( i != INVALID );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename ImplicitBinaryTree<N>::NodeRef ImplicitBinaryTree<N>::NodeRef::Left() const
{
	return ( m_i << 1 ) + 0;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename ImplicitBinaryTree<N>::NodeRef ImplicitBinaryTree<N>::NodeRef::Right() const
{
	return ( m_i << 1 ) + 1;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename ImplicitBinaryTree<N>::NodeRef ImplicitBinaryTree<N>::NodeRef::Parent() const
{
	return ( m_i != ROOT ) ? ( m_i >> 1 ) : INVALID;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
ImplicitBinaryTree<N>::NodeRef::operator size_t() const
{
	return m_i;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
bool ImplicitBinaryTree<N>::NodeRef::IsLeft() const
{
	return ( ( m_i & 1 ) == 0 );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
bool ImplicitBinaryTree<N>::NodeRef::IsRight() const
{
	return !IsLeft();
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

template < typename N >
bool ImplicitBinaryTree<N>::NodeRef::IsRoot() const
{
	return ( m_i == ROOT );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

template < typename N >
int ImplicitBinaryTree<N>::NodeRef::Depth() const
{
	int		depth	= 0;
	size_t	i		= m_i;

	do
	{
		i >>= 1;
		++depth;
	} while ( i != 0 );
}
