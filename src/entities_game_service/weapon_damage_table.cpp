/** \file weapon_damage_table.cpp
 * <File description>
 *
 * $Id: weapon_damage_table.cpp,v 1.11 2006/05/31 12:17:10 boucher Exp $
 */



/////////////
// INCLUDE 
/////////////
#include "stdpch.h"
//
#include "nel/misc/variable.h"
//
#include "weapon_damage_table.h"
#include "egs_mirror.h"
#include "egs_variables.h"

/////////////
// USING
/////////////
using namespace std;
using namespace NLMISC;


/////////////
// GLOBALS 
/////////////


//--------------------------------------------------------------
//				init()  
//--------------------------------------------------------------
void CWeaponDamageTable::init()
{
//	nlinfo("Weapon damage table config :\nMinDamage = %.2f\t\tDamageStep = %.2f\t\tExponentialPower = %.2f\t\tSmoothingFactor = %.2f", MinDamage, DamageStep, ExponentialPower, SmoothingFactor);
	for (uint reference = 0 ; reference <= MaxRefenceSkillValue ; ++reference )
	{
		if (reference  == 50)
		{
//			nlinfo("\n\nNew table, recommended skill value = %u\n", reference);
//			nlinfo("Skill\t\tDamage");
		}

		const float dmgLimit = MinDamage + DamageStep*reference;

		for (uint skill = 0 ; skill <= MaxSkillValue ; ++skill )
		{
			// compute ref damage value, linear progression
			const float ref = MinDamage + DamageStep*skill;			
			
			/// % of reference reached by skill (max 100%)
			const float pos = (skill>=reference) ? 1.0f : float(skill)/reference;

			float value;
			if (pos < 1.0f)
			{
				value = (float) ((MinDamage + (dmgLimit-MinDamage)*pow(pos, ExponentialPower) + ref) / 2.0f);
			}
			else
			{
				if (skill <= 1)
				{
					value = ref;
				}
				else
				{
					value = _DamageTable[reference][skill-1] + (_DamageTable[reference][skill-1] - _DamageTable[reference][skill-2]) * SmoothingFactor;
				}				
			}

			_DamageTable[reference][skill] = value;

			if (reference  == 50)
			{				
//				nlinfo("%u\t\t%.2f", skill, value);
			}
		}
	}
//	nlinfo("\n\n");
	
} // init //


