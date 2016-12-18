/** @file *//********************************************************************************************************

                                                    BinaryTree.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/BinaryTree/BinaryTree.inl#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "BinaryTree.h"

#include <cassert>
#include <memory>


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
BinaryTree<N>::BinaryTree()
	: m_pRoot( 0 )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	data	data to be stored in the root node

template < typename N >
BinaryTree<N>::BinaryTree( N const & data )
	: m_pRoot( new Node( data ) )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
BinaryTree<N>::~BinaryTree()
{
	Erase();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @return		A pointer to the root node.

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::Root()
{
	return m_pRoot;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @return		A pointer to the const root node.

template< typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::Root() const
{
	return m_pRoot;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::FirstLeaf() const
{
	return ( m_pRoot != 0 ) ? LeftmostLeaf( m_pRoot ) : 0;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! The first leaf node is the leftmost depth-first leaf node.
//!
//! @return		A pointer to the first leaf node.

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::FirstLeaf()
{
	BinaryTree const * const	pCTree	= const_cast< BinaryTree const * >( this );

	return const_cast< Node * >( pCTree->FirstLeaf() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::NextLeaf( Node const * pNode ) const
{
	assert( pNode != 0 );
	assert( Contains( pNode ) );

	// If this is the root node, then we are done

	if ( pNode == m_pRoot )
	{
		return 0;
	}

	Node const * const	pParent	= pNode->Parent();

	// If this node is the left node and the parent has a right node, then
	// traverse the right side now.

	if ( pNode == pParent->Left() && pParent->Right() != 0 )
	{
		return LeftmostLeaf( pParent->Right() );
	}

	// Otherwise, we are done with this subtree, so go up one level

	else
	{
		return NextLeaf( pParent );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! The next leaf node is the leftmost depth-first leaf node to the right of this node.
//!
//! @param		The reference node
//!
//! @return		A pointer to the next leaf node.

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::NextLeaf( Node * pNode )
{
	assert( Contains( pNode ) );

	BinaryTree const * const	pCTree	= const_cast< BinaryTree * >( this );
	Node const * const		pCNode	= const_cast< Node * >( pNode );

	return const_cast< Node * >( pCTree->NextLeaf( pCNode ) );
}



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	data	Data for the new root node
//!
//! @warning	@a The tree must have no root node.

template< typename N >
void BinaryTree<N>::GrowRoot( N const & data )
{
	assert( m_pRoot == 0 );

	m_pRoot = new Node( data );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	left	Data for the new left child
//!
//! @warning	@a pNode must not have a left child node.

template< typename N >
void BinaryTree<N>::GrowLeft( Node * pNode, N const & left )
{
	assert( pNode != 0 );
	assert( pNode->Left() == 0 );
	assert( Contains( pNode ) );

	pNode->SetLeft( new Node( left ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	right	Data for the right child
//!
//! @warning	@a pNode must not have a right child node.

template< typename N >
void BinaryTree<N>::GrowRight( Node * pNode, N const & right )
{
	assert( pNode != 0 );
	assert( pNode->Right() == 0 );
	assert( Contains( pNode ) );

	pNode->SetRight( new Node( right ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	left	Data for the new left child
//! @param	right	Data for the new right child
//!
//! @warning	@a pNode must point to a @b leaf node.

template< typename N >
void BinaryTree<N>::Grow( Node * pNode, N const & left, N const & right )
{
	assert( pNode != 0 );
	assert( pNode->IsALeaf() );
	assert( Contains( pNode ) );

	pNode->SetLeft( new Node( left ) );
	pNode->SetRight( new Node( right ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	pLeft	The tree to insert as the left child of the parent node
//!
//! @warning	@a pNode must not have a left child node.

template< typename N >
void BinaryTree<N>::InsertLeft( Node * pNode, BinaryTree * pLeft )
{
	assert( pNode != 0 );
	assert( pNode->Left() == 0 );
	assert( Contains( pNode ) );

	pNode->SetLeft( pLeft->m_pRoot );
	pLeft->m_pRoot = 0;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	pRight	The tree to insert as the left child of the parent node
//!
//! @warning	@a pNode must not have a right child node.

template< typename N >
void BinaryTree<N>::InsertRight( Node * pNode, BinaryTree * pRight )
{
	assert( pNode != 0 );
	assert( pNode->Right() == 0 );
	assert( Contains( pNode ) );

	pNode->SetRight( pRight->m_pRoot );
	pRight->m_pRoot = 0;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	pNode	The parent node
//! @param	pLeft	The tree to insert as the left child of the parent node
//! @param	pRight	The tree to insert as the left child of the parent node
//!
//! @warning	@a pNode must point to a @b leaf node.
//! @warning	The source trees will be emptied.

template< typename N >
void BinaryTree<N>::Insert( Node * pNode, BinaryTree * pLeft, BinaryTree * pRight )
{
	assert( pNode != 0 );
	assert( pNode->IsALeaf() );
	assert( Contains( pNode ) );

	pNode->SetLeft( pLeft->m_pRoot );
	pLeft->m_pRoot = 0;

	pNode->SetRight( pRight->m_pRoot );
	pRight->m_pRoot = 0;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
void BinaryTree<N>::Erase( Node * pNode/* = 0*/ )
{
	assert( pNode == 0 || Contains( pNode ) );

	if ( pNode == 0 )
	{
		pNode = m_pRoot;
	}

	if ( pNode )
	{
		if ( pNode->Left() )
		{
			Erase( pNode->Left() );
		}

		if ( pNode->Right() )
		{
			Erase( pNode->Right() );
		}

		delete pNode;
	}

}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
bool BinaryTree<N>::Contains( Node const * pNode ) const
{
	// If this tree does not have any nodes or this is not a node, then it cannot be in this tree.

	if ( m_pRoot == 0 || pNode == 0 )
	{
		return false;
	}

	// Iterate up the node's tree until a root node is found.

	Node const * pParent	= pNode->Parent();
	while ( pParent != 0 )
	{
		// Make sure this node is linked into a tree correctly (it is a left or right child of its parent).
		assert( pParent->Left() == pNode || pParent->Right() == pNode );

		// Up one level
		pNode = pParent;
		pParent	= pNode->Parent();
	}

	// The node is is this tree if it or one of its parents is this tree's root node.
	return ( pNode == m_pRoot );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::LeftmostLeaf( Node const * pNode ) const
{
	assert( pNode != 0 );
	assert( Contains( pNode ) );

	if ( pNode->Left() != 0 )
	{
		return LeftmostLeaf( pNode->Left() );
	}
	else if ( pNode->Right() != 0 )
	{
		return LeftmostLeaf( pNode->Right() );
	}
	else
	{
		return pNode;
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::LeftmostLeaf( Node * pNode )
{
	BinaryTree const * const	pCTree	= const_cast< BinaryTree * >( this );
	Node const * const		pCNode	= const_cast< Node * >( pNode );

	return const_cast< Node * >( pCTree->LeftmostLeaf( pCNode ) );
}


/********************************************************************************************************************/
/********************************************************************************************************************/
/*																													*/
/*												typename BinaryTree<N>::Node													*/
/*																													*/
/********************************************************************************************************************/
/********************************************************************************************************************/


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
BinaryTree<N>::Node::Node( N const & data, Node * pParent/* = 0*/, Node * pLeft/* = 0*/, Node * pRight/* = 0*/ )
	: m_data( data ),
	m_pParent( pParent ),
	m_pLeftChild( pLeft ),
	m_pRightChild( pRight )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template < typename N >
BinaryTree<N>::Node::~Node()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	pParent		The new parent node.

template< typename N >
void  BinaryTree<N>::Node::SetParent( Node * pParent )
{
	m_pParent = pParent;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @return		A pointer to the parent node

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::Node::Parent()
{
	return m_pParent;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @return		A pointer to the const parent node

template< typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::Node::Parent() const
{
	return m_pParent;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
void BinaryTree<N>::Node::SetLeft( Node * pLeft )
{
	m_pLeftChild = pLeft;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::Node::Left()
{
	return m_pLeftChild;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::Node::Left() const
{
	return m_pLeftChild;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
void BinaryTree<N>::Node::SetRight( Node * pRight )
{
	m_pRightChild = pRight;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
typename BinaryTree<N>::Node * BinaryTree<N>::Node::Right()
{
	return m_pRightChild;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
typename BinaryTree<N>::Node const * BinaryTree<N>::Node::Right() const
{
	return m_pRightChild;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

template< typename N >
bool BinaryTree<N>::Node::IsALeaf() const
{
	return ( m_pLeftChild == 0 && m_pRightChild == 0 );
}
