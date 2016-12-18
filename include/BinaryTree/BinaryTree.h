/** @file *//********************************************************************************************************

                                                     BinaryTree.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/BinaryTree/BinaryTree.h#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include <memory>
#include <boost/noncopyable.hpp>

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! A binary tree.
//

template < typename N >
class BinaryTree : public boost::noncopyable
{
public:

	class Node;		// Declared below

	//! Constructor
	BinaryTree();

	//! Constructor
	BinaryTree( N const & data );

	//! Destructor
	virtual ~BinaryTree();

	//! Returns the root node
	Node * Root();

	//! Returns the root node
	Node const * Root() const;

	//! Returns the first leaf in the tree, or 0 if the tree is empty
	Node * FirstLeaf();

	//! Returns the first leaf in the tree, or 0 if the tree is empty
	Node const * FirstLeaf() const;

	//! Returns the next leaf depth-first (leftmost leaf to the right of this node), or 0 if there is none.
	Node * NextLeaf( Node * pNode );

	//! Returns the next leaf depth-first (leftmost leaf to the right of this node), or 0 if there is none.
	Node const * NextLeaf( Node const * pNode ) const;

	// Grows a root node for the tree
	void GrowRoot( N const & data );

	// Grows a node as a left child of this node.
	void GrowLeft( Node * pNode, N const & left );

	// Grows a node as a right child of this node.
	void GrowRight( Node * pNode, N const & right );

	// Grows two nodes as children of this node.
	void Grow( Node * pNode, N const & left, N const & right );

	// Inserts two BinaryTree's as children of this node.
	void Insert( Node * pNode, BinaryTree * pLeft, BinaryTree * pRight );

	// Inserts a BinaryTree as a left child of this node.
	void InsertLeft( Node * pNode, BinaryTree * pLeft );

	// Inserts a BinaryTree as a right child of this node.
	void InsertRight( Node * pNode, BinaryTree * pRight );

	// Deletes the node (and all of its children)
	void Erase( Node * pNode = 0 );

private:

	//! Returns @c true if the node is in this tree
	bool Contains( Node const * pNode ) const;

	//! Returns the leftmost leaf in the tree rooted at a node.
	Node * LeftmostLeaf( Node * pNode );

	//! Returns the leftmost leaf in the tree rooted at a node.
	Node const * LeftmostLeaf( Node const * pNode ) const;

	Node *	m_pRoot;		//!< Root node
};



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! A node of a BinaryTree.

template < typename N >
class BinaryTree<N>::Node : boost::noncopyable
{
	friend class BinaryTree<N>;

public:

	//! Constructor
	explicit Node( N const & data, Node * pParent = 0, Node * pLeft = 0, Node * pRight = 0 );

	//! Destructor
	virtual ~Node() = 0;

	//! Returns the parent node
	Node * Parent();

	//! Returns the parent node
	Node const * Parent() const;
	
	//! Returns the left child node
	Node * Left();

	//! Returns the left child node
	Node const * Left() const;
										
	//! Returns the right child node
	Node * Right();

	//! Returns the right child node
	Node const * Right() const;

	//! Return true if the node has no children
	bool IsALeaf() const;

private:

	//! Sets the parent node
	void SetParent( Node * pParent );

	//! Sets the left child node
	void SetLeft( Node * pLeft );

	//! Sets the right child node
	void SetRight( Node * pRight );

public:

	N		m_data;				//!< Node data

private:

	Node *	m_pParent;			//!< Parent
	Node *	m_pLeftChild;		//!< Left child
	Node *	m_pRightChild;		//!< Right child
};


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

// Inline functions

#include "BinaryTree.inl"
