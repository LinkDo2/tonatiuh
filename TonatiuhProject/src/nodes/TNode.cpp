/***************************************************************************
Copyright (C) 2008 by the Tonatiuh Software Development Team.

This file is part of Tonatiuh.

Tonatiuh program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Acknowledgments:

The development of Tonatiuh was started on 2004 by Dr. Manuel Blanco,
at the time Chair of the Department of Engineering of the University of Texas
at Brownsville. From May 2004 to August 2008 Tonatiuh's development was
supported by the Department of Energy (DOE) and the National Renewable
Energy Laboratory (NREL) under the Minority Research Associate (MURA)
Program Subcontract ACQ-4-33623-06. During 2007, NREL also contributed to
the validation of Tonatiuh under the framework of the Memorandum of
Understanding signed with the Spanish National Renewable Energy Centre (CENER)
on February, 20, 2007 (MOU#NREL-07-117). Since June 2006, the development of
Tonatiuh is being led by CENER, under the direction of Dr. Blanco, now
Manager of the Solar Thermal Energy Department of CENER.

Developers: Manuel J. Blanco (mblanco@cener.com), Amaia Mutuberria, Victor Martin.

Contributors: Javier Garcia-Barberena, Inaki Perez, Inigo Pagola,  Gilda Jimenez,
Juana Amieva, Azael Mancillas, Cesar Cantu.
***************************************************************************/

#include "TNode.h"
#include "TNodeType.h"
#include "TParameterList.h"

TNodeType TNode::m_nodeType = TNodeType::CreateEmptyType();

/*!
 * Initializes node class.
 */
void TNode::Init()
{
	TNode::m_nodeType = TNodeType::CreateType( TNodeType::CreateEmptyType(), "Node" );
}

/*!
 * Creates a TNode object as a child of \a parent node.
 * The initial reference count will be set to zero.
 */
TNode::TNode()
: QObject(),
  //m_parametersList( 0 ),
  m_id( 0 ),
  m_referenceCount( 0 )
{

	static int nodeIndex = 0;
	m_id = nodeIndex;
	nodeIndex++;

	setObjectName(GetType().GetName());
	m_parametersList = new TParameterList;
}

/*!
 * Destroys node object.
 */
TNode::~TNode()
{
	//delete m_parametersList;
	//m_parametersList = 0;
}

/*!
 * Creates a copy of the node.
 */
TNode* TNode::Copy() const
{
	TNode* node = new TNode();

	/*
	const QMetaObject* metaobject = metaObject();
	int count = metaobject->propertyCount();

	for( int p = 0; p < count; ++p)
	{
		QMetaProperty mproperty = metaobject->property( p );
		//const char *name = mproperty.name();
	    QVariant value = property( mproperty.name() );
	    node->setProperty( mproperty.name(), value );
	}
	*/

	TParameterList* parametersList = node->m_parametersList;

	QStringList parameterNames = m_parametersList->GetParametersNames();

	for( int p = 0; p < parameterNames.count(); p++ )
	{
		QVariant parameterValue = m_parametersList->GetValue( parameterNames[p] );
		bool parameterVisibility = m_parametersList->GetVisibility( parameterNames[p] );
		parametersList->Append(parameterNames[p], parameterValue, parameterVisibility );
	}


	return ( node );
}

/*!
 * Returns node identifier.
 */
int TNode::GetID() const
{
	return ( m_id );
}

/*!
 * Returns node object name.
 */
QString TNode::GetName() const
{
	return ( objectName() );
}

/*!
 * Returns the list of the parameters accesible exteranlly to the node.
 */
QStringList TNode::GetVisibleParametersName() const
{
	QStringList allParametersNames = m_parametersList->GetParametersNames();
	for( int i = 0; i < allParametersNames.count(); i++ )
	{
		if( !m_parametersList->GetVisibility( allParametersNames[i] ) )
			allParametersNames.removeAt( i );
	}
	return ( allParametersNames );

	/*
	QStringList allParametersNames;

	const QMetaObject* metaobject = metaObject();
	int count = metaobject->propertyCount();
	for( int p = 0; p < count; ++p)
	{
		QMetaProperty mproperty = metaobject->property( p );
		allParametersNames<<mproperty.name();
	}

	return ( allParametersNames );
	*/
}

/*!
 * Returns the value of the parameter \a name.
 */
QVariant TNode::GetParameterValue( QString name ) const
{

	if(!m_parametersList )	return( QVariant() );
	if( !m_parametersList->Contains( name ) || !m_parametersList->GetVisibility( name ) )
		return( QVariant() );
	return (m_parametersList->GetValue( name ) );


	/*
	const char* nameChar = name.toLatin1().data();
    QVariant value = property( nameChar );

	return ( value );
	*/
}

/*!
 * Returns the number of references.
 */
int TNode::GetReferences() const
{
	return ( m_referenceCount );
}

/*!
 * Returns node type.
 */
TNodeType TNode::GetType() const
{
	return ( TNode::m_nodeType );
}

/*!
 * Increases in one the number of references to the node.
 */
void TNode::IncreaseReference()
{
	m_referenceCount++;
}

void TNode::RemoveReference()
{
	m_referenceCount--;
	if( m_referenceCount < 1 )
		delete this;
}

/*!
 * Sets \a name to the node object.
 */
void TNode::SetName( QString name )
{
	setObjectName(name);
}

/*!
 * Sets to the parameter \a name the \a value.
 */
bool TNode::SetParameterValue( const QString& name, const QVariant& value )
{

	if( !m_parametersList )	return ( false );
	if( !m_parametersList->Contains( name ) || !m_parametersList->GetVisibility( name ) )
		return ( false );
	if( !m_parametersList->SetValue( name, value ) ) 	return ( false );

	return (true);



    //setProperty( name.toLatin1().data(), value );

	return (true);
}