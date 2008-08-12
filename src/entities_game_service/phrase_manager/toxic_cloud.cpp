/** \file toxic_cloud.cpp
 * <File description>
 *
 * $Id: toxic_cloud.cpp,v 1.14 2006/07/12 14:37:34 boucher Exp $
 */



#include "stdpch.h"
#include "phrase_manager/toxic_cloud.h"
#include "egs_mirror.h"
#include "egs_globals.h"
#include "phrase_manager/phrase_utilities_functions.h"
#include "phrase_utilities_functions.h"
#include "range_selector.h"
#include "game_share/mode_and_behaviour.h"
#include "egs_variables.h"

#include "r2_share/r2_vision.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;

NL_INSTANCE_COUNTER_IMPL(CToxicCloud);

NLMISC::TGameCycle CToxicCloud::ToxicCloudDefaultLifetime = 600; // 1 min

/*
 *
 */
class CToxicCloudRangeSelector : public CRangeSelector
{
public:
	void buildTargetList( sint32 x, sint32 y, float radius /*, float minFactor*/ )
	{
		buildDisc( 0, x, y, radius, EntityMatrix, true );
	}

	float getFactor( uint entityIdx )
	{
		return 1.0f;
	}
};


/*
 * Spawn the source as an entity in mirror. Return false in case of failure.
 */
bool CToxicCloud::spawn( const NLMISC::CSheetId &sheet )
{
	// Add into mirror
	CEntityId entityId = CEntityId::getNewEntityId( RYZOMID::fx_entity );
	if ( ! Mirror.createEntity( entityId ) )
		return false;
	_DataSetRow = TheDataset.getDataSetRow( entityId );

	// Set the sheet id
	CMirrorPropValue<TYPE_SHEET> sheetMirror( TheDataset, _DataSetRow, DSPropertySHEET );
	sheetMirror = sheet.asInt();

	// Set the initial position
	CMirrorPropValue<TYPE_POSX> posX( TheDataset, _DataSetRow, DSPropertyPOSX );
	CMirrorPropValue<TYPE_POSY> posY( TheDataset, _DataSetRow, DSPropertyPOSY );
	posX = (TYPE_POSX)(_Pos.x * 1000.0f);
	posY = (TYPE_POSY)(_Pos.y * 1000.0f);

	// Set the mode
	MBEHAV::TMode md;
	md.setModeAndPos( MBEHAV::NORMAL, _DataSetRow );
	CMirrorPropValue<MBEHAV::TMode> mode( TheDataset, _DataSetRow, DSPropertyMODE );
	mode = md;

	// Set the WhoSeesMe bitfield (every bit set to 1)
	const uint64 bitfield = IsRingShard? R2_VISION::buildWhoSeesMe(R2_VISION::WHOSEESME_VISIBLE_PLAYER,true): UINT64_CONSTANT(0xffffffffffffffff);
	CMirrorPropValue<TYPE_WHO_SEES_ME> whoSeesMe(TheDataset, _DataSetRow, DSPropertyWHO_SEES_ME );
	whoSeesMe = bitfield;

	// Contextual properties init
	CMirrorPropValue<TYPE_CONTEXTUAL> contextualProperties(TheDataset, _DataSetRow, DSPropertyCONTEXTUAL );
	contextualProperties = 0;

	TheDataset.declareEntity( _DataSetRow );
	return true;
}


/*
 * Tick update. Return false if the source's life is ended.
 */
bool CToxicCloud::update()
{
	// Make damage to entities passing by (not every tick)
	if ( (_TimeToLive % _UpdateFrequency == 0) && HarvestAreaEffectOn )
	{
		// Get entities around the source
		CToxicCloudRangeSelector targetSelector;
		targetSelector.buildTargetList( (sint32)(_Pos.x * 1000.0f), (sint32)(_Pos.y * 1000.0f), _Radius );
		const vector<CEntityBase*>& targets = targetSelector.getEntities();
		for ( vector<CEntityBase*>::const_iterator it=targets.begin(); it!=targets.end(); ++it )
		{
			CEntityBase *entity = (*it);
			if ( entity && isTargetValid( entity ) )
			{
				// test invulnerability auras and powers
				bool invulnerable = false;
				CSEffect *effect = entity->lookForActiveEffect( EFFECT_FAMILIES::PowerInvulnerability );
				if (effect)
					invulnerable = true;
				else
				{
					effect = entity->lookForActiveEffect( EFFECT_FAMILIES::Invincibility );
					if (effect)
						invulnerable = true;
				}
				
				if (invulnerable)
					continue;

				if ( !entity->isDead())
				{
					bool killed = entity->changeCurrentHp( -_DmgPerHit ); // is not blocked by any armor
					PHRASE_UTILITIES::sendNaturalEventHitMessages( RYZOMID::fx_entity, entity->getEntityRowId(), _DmgPerHit, _DmgPerHit );
					if ( killed )
					{
						PHRASE_UTILITIES::sendDeathMessages( TDataSetRow(), entity->getEntityRowId() );
					}
				}
			}
		}
	}

	// Test toxic cloud clearing
	return CEnvironmentalEffect::update();
}


NLMISC_COMMAND( spawnToxicCloud, "Spawn a toxic cloud", "<posXm> <posYm> <iRadius{0,1,2}=0> <dmgPerHit=0> <updateFrequency=ToxicCloudUpdateFrequency> <lifetimeInTicks=ToxicCloudDefaultLifetime>" )
{
	NL_ALLOC_CONTEXT(CMD_STC);
	if ( args.size() < 2 )
		return false;
	CVector cloudPos( (float)atof( args[0].c_str() ), (float)atof( args[1].c_str() ), 0.0f );
	sint iRadius = 0;
	sint32 dmgPerHit = 0;
	TGameCycle updateFrequency = ToxicCloudUpdateFrequency;
	TGameCycle lifetime = CToxicCloud::ToxicCloudDefaultLifetime;
	if ( args.size() > 2 )
	{
		iRadius = atoi( args[2].c_str() );
		if ( args.size() > 3 )
		{
			dmgPerHit = atoi( args[3].c_str() );
			if ( args.size() > 4 )
			{
				updateFrequency = atoi( args[4].c_str() );
				if ( args.size() > 5 )
					lifetime = atoi( args[4].c_str() );
			}
		}
	}
	
	CToxicCloud *tc = new CToxicCloud();
	float radius = (float)(iRadius*2 + 1); // {1, 3, 5} corresponding to the 3 sheets
	tc->init( cloudPos, radius, dmgPerHit, updateFrequency, lifetime );
	CSheetId sheet( toString( "toxic_cloud_%d.fx", iRadius ));
	if ( tc->spawn( sheet ) )
	{
		CEnvironmentalEffectManager::getInstance()->addEntity( tc );
		log.displayNL( "Toxic cloud spawned (radius %g)", radius );
	}
	else
	{
		log.displayNL( "Unable to spawn toxic cloud (mirror range full?)" );
	}
	return true;
}

NLMISC_DYNVARIABLE( NLMISC::TGameCycle, ToxicCloudDefaultLifetime, "Default lifetime of a toxic cloud, in ticks" )
{
	if ( get )
		*pointer = CToxicCloud::ToxicCloudDefaultLifetime;
	else
		CToxicCloud::ToxicCloudDefaultLifetime = *pointer;
}
