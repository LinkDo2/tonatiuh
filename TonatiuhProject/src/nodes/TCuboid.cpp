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

The development of Tonatiuh was started on 2004 by Dr. Manuel J. Blanco,
then Chair of the Department of Engineering of the University of Texas at
Brownsville. From May 2004 to July 2008, it was supported by the Department
of Energy (DOE) and the National Renewable Energy Laboratory (NREL) under
the Minority Research Associate (MURA) Program Subcontract ACQ-4-33623-06.
During 2007, NREL also contributed to the validation of Tonatiuh under the
framework of the Memorandum of Understanding signed with the Spanish
National Renewable Energy Centre (CENER) on February, 20, 2007 (MOU#NREL-07-117).
Since June 2006, the development of Tonatiuh is being led by the CENER, under the
direction of Dr. Blanco, now Director of CENER Solar Thermal Energy Department.

Developers: Manuel J. Blanco (mblanco@cener.com), Amaia Mutuberria, Victor Martin.

Contributors: Javier Garcia-Barberena, Inaki Perez, Inigo Pagola,  Gilda Jimenez,
Juana Amieva, Azael Mancillas, Cesar Cantu.
***************************************************************************/

#include "TCuboid.h"


TNodeType TCuboid::m_nodeType = TNodeType::CreateEmptyType();


/*!
 * Creates a new instance of the class type corresponding object.
 */
void* TCuboid::CreateInstance( )
{
  return ( new TCuboid() );
}

/*!
 * Initializes TShape type.
 */
void TCuboid::Init()
{
	TCuboid::m_nodeType = TNodeType::CreateType( TNodeType::FromName( "Shape" ), QString( "Cuboid" ), &TCuboid::CreateInstance );
}

/*!
 * Constructor
 */
TCuboid::TCuboid()
:TShape(),
 m_depth( 1 ),
 m_height( 1 ),
 m_width( 1 )
{
	setObjectName(GetType().GetName());
}


/*!
 * Destroys object.
 */
TCuboid::~TCuboid()
{

}


QString TCuboid::GetIcon()
{
	return ( QLatin1String( ":/icons/tcuboid.png" ) );
}


/*!
 * Returns bonding box for the cuboid dimensions values.
 */
BBox TCuboid::GetBondingBox() const
{
	BBox bBox;

	// Compute the half-width, half-height, and half-depth of
     // the pyramid. We'll use this info to set the min and max
     // points.
    double halfWidth = 0.5 * m_width;
    double halfHeight = 0.5 * m_height;
    double halfDepth = 0.5 * m_depth;

    bBox.pMin = Point3D( -halfWidth, -halfHeight, -halfDepth );
    bBox.pMax = Point3D( halfWidth, halfHeight, halfDepth );

    return ( bBox  );
}

/*!
 * Returns the type of node.
 */
TNodeType TCuboid::GetType() const
{
	return ( TCuboid::m_nodeType );
}


bool TCuboid::Intersect( const Ray& /*objectRay*/, double* /*tHit*/, DifferentialGeometry* /*dg*/, bool* /*isShapeFront*/ ) const
{
	return ( false );
}

void TCuboid::Draw() const
{

}