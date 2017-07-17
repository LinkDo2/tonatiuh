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

#include <QtConcurrent>
#include <QDateTime>
#include <QFutureWatcher>

#include "ParallelRandomDeviate.h"
#include "Ray.h"
#include "RayTracer.h"
#include "TSunshape.h"


/*!
 * Creates a ray tracer object
 */
RayTracer::RayTracer(  )
:m_pRandomNumberGenerator( 0 ),
 m_pPhotonMap( 0 ),
 m_pSunNode( 0 )
{
}

/*!
 * Destroys ray tracer object.
 */
RayTracer::~RayTracer()
{

}

/*!
 * Executes the ray tracer with current selected algorithm.
 * Returns false if the ray tracer has not been correctly exectued.
 */
bool RayTracer::Run( unsigned long numberOfRays )
{
	if( !m_pSunNode || !m_pPhotonMap  || !m_pRandomNumberGenerator )	return ( false );

	QDateTime startTime = QDateTime::currentDateTime();

	QVector< long > raysPerThread;
	int maximumValueProgressScale = 100;
	unsigned long  t1 = numberOfRays / maximumValueProgressScale;
	for( int progressCount = 0; progressCount < maximumValueProgressScale; ++ progressCount )
	raysPerThread<< t1;

	if( ( t1 * maximumValueProgressScale ) < numberOfRays )	raysPerThread<< ( numberOfRays-( t1* maximumValueProgressScale) );

	// Create a QFutureWatcher and conncect signals and slots.
	//QThreadPool::globalInstance()->setMaxThreadCount(1);
	QFutureWatcher< void > futureWatcher;
	QFuture< void > raytracingResult = QtConcurrent::map( raysPerThread,
			[this] (unsigned long nRays ) { RunRaytracer( nRays ); } );



	futureWatcher.setFuture( raytracingResult );

	// Display the dialog and start the event loop.
	futureWatcher.waitForFinished();

	QDateTime endTime = QDateTime::currentDateTime();
	std::cout <<"Elapsed time: "<< startTime.secsTo( endTime ) << std::endl;

	return ( true );

}

/*!
 * Sets the photon map to be used during ray tracing.
 */
void RayTracer::SetPhotonMap( TPhotonMap* photonMap )
{
	m_pPhotonMap = photonMap;
}


/*!
 * Sets the random number generator object.
 */
void RayTracer::SetRandomNumberGenerator( RandomDeviate* randomNumberGenerator )
{
	m_pRandomNumberGenerator = randomNumberGenerator;
}


/*!
 * Set the scene to simulate for the ray tracer.
 * Returns true if the scene is valid.
 */
bool RayTracer::SetScene( TSceneNode* scene, QStringList /*firstStageNodesURL*/ )
{
	if( !scene )	return false;
	m_pSunNode = scene->GetPart( "light" )->as<TSunNode>();

	return ( true );
}


/*!
 * Generates a new ray.
 */
bool RayTracer::NewRay( Ray* ray, ParallelRandomDeviate& rand )
{
	if( m_lightOriginShape.validSunAreasVector.size() < 1 )	return false;
	int area = int ( rand.RandomDouble() * m_lightOriginShape.validSunAreasVector.size() );

	std::pair< int, int > areaIndex = m_lightOriginShape.validSunAreasVector[area] ;


	double u = rand.RandomDouble();
	double v = rand.RandomDouble();

	//calculate the photon coordinate
	double x = m_lightOriginShape.xMinSunPlane + ( u * m_lightOriginShape.cellWidth ) + ( areaIndex.second * m_lightOriginShape.cellWidth);
	double z = m_lightOriginShape.zMinSunPlane + ( v * m_lightOriginShape.cellHeight ) + ( areaIndex.first * m_lightOriginShape.cellHeight);

	Point3D origin = Point3D( x, 0, z );


	//generating the ray direction
	Vector3D direction;
	TSunshape* sunshape = m_pSunNode->GetPart( QLatin1String( "sunshape" ) )->as<TSunshape>();
	sunshape->GenerateRayDirection( direction, rand );

	//generatin the ray
	*ray =  m_sunTransformSTW( Ray( origin, direction ) );

	return ( true );
}

