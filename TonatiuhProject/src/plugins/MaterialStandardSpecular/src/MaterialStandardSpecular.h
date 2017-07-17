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

#ifndef MATERIALSTANDARDSPECULAR_H_
#define MATERIALSTANDARDSPECULAR_H_

#include <QString>

#include "TMaterial.h"
#include "TParameterList.h"

//!  MaterialStandardSpecular class is the the representation of a specular material.
/*!
  MaterialStandardSpecular class provides to the scene the possibility to create specular surfaces having the incident ray and reflected ray the same angle to the surface normal.
  In addition, this material contemplates a reflectivity value and the theoretical normal deviation by a distribution function:
  * - reflectivity: Percentage incident rays that the surface reflects.
  * - sigmaSlope: probability distribution function parameter in mrad.
  * - distribution: probability distribution function that defines the normal deviations.NORMAL or PILLBOX
*/


class MaterialStandardSpecular : public TMaterial
{
	Q_OBJECT
    //Q_ENUMS( Distribution )
	//Q_PROPERTY( Distribution dist READ Value WRITE SetDistributionValue )

private:
	Q_DISABLE_COPY(MaterialStandardSpecular)

public:
	static void* CreateInstance();
	static void Init();

	MaterialStandardSpecular( );


	//enum Distribution { PILLBOX = 0, NORMAL = 1, };
	//enum Distribution { PILLBOX, NORMAL, };

    QString GetIcon();
	TNodeType GetType() const;
	bool OutputRay( const Ray& incident, DifferentialGeometry* dg, RandomDeviate& rand, Ray* outputRay ) const;

	/*
	void SetDistributionValue( Distribution dist)
	{
		m_parametersList->SetValue( QLatin1String("distribution"), dist );
	}
	Distribution Value() const
	{
		return 	( m_parametersList->GetValue( QLatin1String("distribution") ).value<Distribution>() );
	}
	*/
/*
	trt::TONATIUH_REAL m_reflectivity;
	trt::TONATIUH_REAL m_sigmaSlope;
	SoSFEnum m_distribution;

	SoMFColor  m_ambientColor;
	SoMFColor  m_diffuseColor;
	SoMFColor  m_specularColor;
	SoMFColor  m_emissiveColor;
	SoMFFloat m_shininess;
	SoMFFloat m_transparency ;
	*/

protected:
   	virtual ~MaterialStandardSpecular();

private:
	static TNodeType m_nodeType;

};

//Q_DECLARE_METATYPE( MaterialStandardSpecular::Distribution );

#endif /*MATERIALSTANDARDSPECULAR_H_*/