/*

	EGS pet interface

*/

const uint32 MaxSimultaneousPlayers=5000;
const uint32 MaxPetsPerPlayer=4;

class CPetInterface
{
public:

	// VERY IMPORTANT COMMAND FOR KEEPING AI INFORMED OF PLAYER WHEREABOUTS
	static void setPlayerLandmap(uint32 playerMirrorRow, uint32 landmap);

	// spawn commands
	static void spawnAtStable(uint32 playerMirrorRow, uint32 petIdx, NLMISC::CSheetId sheet, uint32 stableId);
	static void spawnNearPlayer(uint32 playerMirrorRow,uint32 petIdx, NLMISC::CSheetId sheet);
	static void spawnNearPoint(uint32 playerMirrorRow, uint32 petIdx, NLMISC::CSheetId sheet, uint32 x, uint32 y, uint32 h);

	// despawn commands
	static void despawnPetsOnPlayerLogOff(uint32 playerMirrorRow);
	static void despawnPetsOnPlayerDeath(uint32 playerMirrorRow);
	static void despawnViaStable(uint32 playerMirrorRow, uint32 petIdx, uint32 stableId);

	// player instructions to followers
	static void cmdFollowPlayer(uint32 playerMirrorRow, uint32 petIdx);
	static void cmdStandStill(uint32 playerMirrorRow, uint32 petIdx);
	static void cmdGraze(uint32 playerMirrorRow, uint32 petIdx);
	static void cmdAttackEntity(uint32 playerMirrorRow, uint32 petIdx, uint32 entityMirrorRow);
	static void cmdLetPlayerMount(uint32 playerMirrorRow, uint32 petIdx, uint32 riderMirrorRow);
	static void cmdPlayerHasDismounted(uint32 playerMirrorRow, uint32 petIdx);

	// liberating creatures (they run away and die of a broken heart)
	static void liberate(uint32 playerMirrorRow, uint32 petIdx);

	// interface for retrieving the mirror rows and entity ids for players' pets
	static NLMISC::CEntityId &getPetId(uint32 playerMirrorRow, uint32 petIdx);

private:
	static uint32 _petMirrorRow[MaxSimultaneousPlayers][MaxPetsPerPlayer];

};

// need to think to migrate entitiies as AI landmap managers change

// on service up receive (from AIS) landmaps that AIS manages from PET viewpoint
// convert eids on the fly - changing dynamic id
// construction:
// - low 40 bits:
// - 8 bits type = 'creature'
// - 8 bits	static id = pet idx
// - 8 bits dynamic id = AIS id (defines map) ???

// 20 bits: 16 plr id/ 4 botid

