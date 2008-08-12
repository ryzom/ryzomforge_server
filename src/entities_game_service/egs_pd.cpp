/** \file egs_pd.cpp
 * Initialisation of the EGSPD database, implementation
 * 
 * 
 * $Id: egs_pd.cpp,v 1.27 2007/05/09 15:33:06 boucher Exp $
 */


#include "stdpch.h"

#include "egs_pd.h"

namespace EGSPD
{
	
RY_PDS::CPDSLib	PDSLib;
void							init(uint32 overrideDbId)
{
	PDSLib.registerClassMapping(0, "CFameContainerEntryPD");
	CFameContainerEntryPD::pds_static__init();
	PDSLib.registerClassMapping(1, "CFameContainerPD");
	CFameContainerPD::pds_static__init();
	PDSLib.registerClassMapping(2, "CGuildFameContainerPD");
	CGuildFameContainerPD::pds_static__init();
	PDSLib.registerClassMapping(3, "CGuildMemberPD");
	CGuildMemberPD::pds_static__init();
	PDSLib.registerClassMapping(4, "CGuildPD");
	CGuildPD::pds_static__init();
	PDSLib.registerClassMapping(5, "CGuildContainerPD");
	CGuildContainerPD::pds_static__init();
	PDSLib.registerClassMapping(6, "CActiveStepStatePD");
	CActiveStepStatePD::pds_static__init();
	PDSLib.registerClassMapping(7, "CActiveStepPD");
	CActiveStepPD::pds_static__init();
	PDSLib.registerClassMapping(8, "CDoneStepPD");
	CDoneStepPD::pds_static__init();
	PDSLib.registerClassMapping(9, "CMissionCompassPD");
	CMissionCompassPD::pds_static__init();
	PDSLib.registerClassMapping(10, "CMissionTeleportPD");
	CMissionTeleportPD::pds_static__init();
	PDSLib.registerClassMapping(11, "CMissionInsidePlacePD");
	CMissionInsidePlacePD::pds_static__init();
	PDSLib.registerClassMapping(12, "CMissionOutsidePlacePD");
	CMissionOutsidePlacePD::pds_static__init();
	PDSLib.registerClassMapping(13, "CHandledAIGroupPD");
	CHandledAIGroupPD::pds_static__init();
	PDSLib.registerClassMapping(14, "CMissionPD");
	CMissionPD::pds_static__init();
	PDSLib.registerClassMapping(15, "CMissionGuildPD");
	CMissionGuildPD::pds_static__init();
	PDSLib.registerClassMapping(16, "CMissionTeamPD");
	CMissionTeamPD::pds_static__init();
	PDSLib.registerClassMapping(17, "CMissionSoloPD");
	CMissionSoloPD::pds_static__init();
	PDSLib.registerClassMapping(18, "CMissionContainerPD");
	CMissionContainerPD::pds_static__init();
	std::string	xmlDescription;
	xmlDescription += "<?xml version='1.0'?>\n";
	xmlDescription += "<dbdescription version='0.0'>\n";
	xmlDescription += "<db name='EGSPD' types='23' classes='19'>\n";
	xmlDescription += "<typedef name='bool' id='0' size='1' storage='bool' type='type'/>\n";
	xmlDescription += "<typedef name='char' id='1' size='1' storage='char' type='type'/>\n";
	xmlDescription += "<typedef name='ucchar' id='2' size='2' storage='ucchar' type='type'/>\n";
	xmlDescription += "<typedef name='uint8' id='3' size='1' storage='uint8' type='type'/>\n";
	xmlDescription += "<typedef name='sint8' id='4' size='1' storage='sint8' type='type'/>\n";
	xmlDescription += "<typedef name='uint16' id='5' size='2' storage='uint16' type='type'/>\n";
	xmlDescription += "<typedef name='sint16' id='6' size='2' storage='sint16' type='type'/>\n";
	xmlDescription += "<typedef name='uint32' id='7' size='4' storage='uint32' type='type'/>\n";
	xmlDescription += "<typedef name='sint32' id='8' size='4' storage='sint32' type='type'/>\n";
	xmlDescription += "<typedef name='uint64' id='9' size='8' storage='uint64' type='type'/>\n";
	xmlDescription += "<typedef name='sint64' id='10' size='8' storage='sint64' type='type'/>\n";
	xmlDescription += "<typedef name='float' id='11' size='4' storage='float' type='type'/>\n";
	xmlDescription += "<typedef name='double' id='12' size='8' storage='double' type='type'/>\n";
	xmlDescription += "<typedef name='CEntityId' id='13' size='8' storage='CEntityId' type='type'/>\n";
	xmlDescription += "<typedef name='CSheetId' id='14' size='4' storage='CSheetId' type='type'/>\n";
	xmlDescription += "<typedef name='TCharacterId' id='15' size='8' storage='CEntityId' type='type'/>\n";
	xmlDescription += "<typedef name='TGuildId' id='16' size='4' storage='uint32' type='type'/>\n";
	xmlDescription += "<typedef name='TPeople' id='17' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='Humanoid' value='0'/>\n";
	xmlDescription += "<enumvalue name='Playable' value='0'/>\n";
	xmlDescription += "<enumvalue name='Fyros' value='0'/>\n";
	xmlDescription += "<enumvalue name='Matis' value='1'/>\n";
	xmlDescription += "<enumvalue name='Tryker' value='2'/>\n";
	xmlDescription += "<enumvalue name='Zorai' value='3'/>\n";
	xmlDescription += "<enumvalue name='EndPlayable' value='4'/>\n";
	xmlDescription += "<enumvalue name='Karavan' value='4'/>\n";
	xmlDescription += "<enumvalue name='Tribe' value='5'/>\n";
	xmlDescription += "<enumvalue name='Common' value='6'/>\n";
	xmlDescription += "<enumvalue name='EndHumanoid' value='7'/>\n";
	xmlDescription += "<enumvalue name='Creature' value='7'/>\n";
	xmlDescription += "<enumvalue name='Fauna' value='7'/>\n";
	xmlDescription += "<enumvalue name='Arma' value='7'/>\n";
	xmlDescription += "<enumvalue name='Balduse' value='8'/>\n";
	xmlDescription += "<enumvalue name='Bul' value='9'/>\n";
	xmlDescription += "<enumvalue name='Capryni' value='10'/>\n";
	xmlDescription += "<enumvalue name='Chonari' value='11'/>\n";
	xmlDescription += "<enumvalue name='Clapclap' value='12'/>\n";
	xmlDescription += "<enumvalue name='Cococlaw' value='13'/>\n";
	xmlDescription += "<enumvalue name='Cute' value='14'/>\n";
	xmlDescription += "<enumvalue name='Dag' value='15'/>\n";
	xmlDescription += "<enumvalue name='Diranak' value='16'/>\n";
	xmlDescription += "<enumvalue name='Estrasson' value='17'/>\n";
	xmlDescription += "<enumvalue name='Filin' value='18'/>\n";
	xmlDescription += "<enumvalue name='Frahar' value='19'/>\n";
	xmlDescription += "<enumvalue name='Gibbai' value='20'/>\n";
	xmlDescription += "<enumvalue name='Hachtaha' value='21'/>\n";
	xmlDescription += "<enumvalue name='Jungler' value='22'/>\n";
	xmlDescription += "<enumvalue name='Kakty' value='23'/>\n";
	xmlDescription += "<enumvalue name='Kalab' value='24'/>\n";
	xmlDescription += "<enumvalue name='Kami' value='25'/>\n";
	xmlDescription += "<enumvalue name='Kazoar' value='26'/>\n";
	xmlDescription += "<enumvalue name='Kitin' value='27'/>\n";
	xmlDescription += "<enumvalue name='Kitins' value='28'/>\n";
	xmlDescription += "<enumvalue name='Kitifly' value='28'/>\n";
	xmlDescription += "<enumvalue name='Kitihank' value='29'/>\n";
	xmlDescription += "<enumvalue name='Kitiharak' value='30'/>\n";
	xmlDescription += "<enumvalue name='Kitikil' value='31'/>\n";
	xmlDescription += "<enumvalue name='Kitimandib' value='32'/>\n";
	xmlDescription += "<enumvalue name='Kitinagan' value='33'/>\n";
	xmlDescription += "<enumvalue name='Kitinega' value='34'/>\n";
	xmlDescription += "<enumvalue name='Kitinokto' value='35'/>\n";
	xmlDescription += "<enumvalue name='EndKitins' value='36'/>\n";
	xmlDescription += "<enumvalue name='Lightbird' value='36'/>\n";
	xmlDescription += "<enumvalue name='Mektoub' value='37'/>\n";
	xmlDescription += "<enumvalue name='MektoubPacker' value='38'/>\n";
	xmlDescription += "<enumvalue name='MektoubMount' value='39'/>\n";
	xmlDescription += "<enumvalue name='Pucetron' value='40'/>\n";
	xmlDescription += "<enumvalue name='Regus' value='41'/>\n";
	xmlDescription += "<enumvalue name='Ryzerb' value='42'/>\n";
	xmlDescription += "<enumvalue name='Ryzoholo' value='43'/>\n";
	xmlDescription += "<enumvalue name='Ryzoholok' value='44'/>\n";
	xmlDescription += "<enumvalue name='Vampignon' value='45'/>\n";
	xmlDescription += "<enumvalue name='Varinx' value='46'/>\n";
	xmlDescription += "<enumvalue name='Yber' value='47'/>\n";
	xmlDescription += "<enumvalue name='Zerx' value='48'/>\n";
	xmlDescription += "<enumvalue name='race_c1' value='49'/>\n";
	xmlDescription += "<enumvalue name='race_c2' value='50'/>\n";
	xmlDescription += "<enumvalue name='race_c3' value='51'/>\n";
	xmlDescription += "<enumvalue name='race_c4' value='52'/>\n";
	xmlDescription += "<enumvalue name='race_c5' value='53'/>\n";
	xmlDescription += "<enumvalue name='race_c6' value='54'/>\n";
	xmlDescription += "<enumvalue name='race_c7' value='55'/>\n";
	xmlDescription += "<enumvalue name='race_h1' value='56'/>\n";
	xmlDescription += "<enumvalue name='race_h2' value='57'/>\n";
	xmlDescription += "<enumvalue name='race_h3' value='58'/>\n";
	xmlDescription += "<enumvalue name='race_h4' value='59'/>\n";
	xmlDescription += "<enumvalue name='race_h5' value='60'/>\n";
	xmlDescription += "<enumvalue name='race_h6' value='61'/>\n";
	xmlDescription += "<enumvalue name='race_h7' value='62'/>\n";
	xmlDescription += "<enumvalue name='race_h8' value='63'/>\n";
	xmlDescription += "<enumvalue name='race_h9' value='64'/>\n";
	xmlDescription += "<enumvalue name='race_h10' value='65'/>\n";
	xmlDescription += "<enumvalue name='race_h11' value='66'/>\n";
	xmlDescription += "<enumvalue name='race_h12' value='67'/>\n";
	xmlDescription += "<enumvalue name='EndFauna' value='68'/>\n";
	xmlDescription += "<enumvalue name='Flora' value='68'/>\n";
	xmlDescription += "<enumvalue name='Cephaloplant' value='68'/>\n";
	xmlDescription += "<enumvalue name='Electroalgs' value='69'/>\n";
	xmlDescription += "<enumvalue name='Phytopsy' value='70'/>\n";
	xmlDescription += "<enumvalue name='SapEnslaver' value='71'/>\n";
	xmlDescription += "<enumvalue name='SpittingWeeds' value='72'/>\n";
	xmlDescription += "<enumvalue name='Swarmplants' value='73'/>\n";
	xmlDescription += "<enumvalue name='EndFlora' value='74'/>\n";
	xmlDescription += "<enumvalue name='Goo' value='74'/>\n";
	xmlDescription += "<enumvalue name='GooFauna' value='74'/>\n";
	xmlDescription += "<enumvalue name='GooArma' value='74'/>\n";
	xmlDescription += "<enumvalue name='GooBalduse' value='75'/>\n";
	xmlDescription += "<enumvalue name='GooBul' value='76'/>\n";
	xmlDescription += "<enumvalue name='GooCapryni' value='77'/>\n";
	xmlDescription += "<enumvalue name='GooChonari' value='78'/>\n";
	xmlDescription += "<enumvalue name='GooClapclap' value='79'/>\n";
	xmlDescription += "<enumvalue name='GooCococlaw' value='80'/>\n";
	xmlDescription += "<enumvalue name='GooCute' value='81'/>\n";
	xmlDescription += "<enumvalue name='GooDag' value='82'/>\n";
	xmlDescription += "<enumvalue name='GooDiranak' value='83'/>\n";
	xmlDescription += "<enumvalue name='GooEstrasson' value='84'/>\n";
	xmlDescription += "<enumvalue name='GooFilin' value='85'/>\n";
	xmlDescription += "<enumvalue name='GooFrahar' value='86'/>\n";
	xmlDescription += "<enumvalue name='GooGibbai' value='87'/>\n";
	xmlDescription += "<enumvalue name='GooHachtaha' value='88'/>\n";
	xmlDescription += "<enumvalue name='GooJungler' value='89'/>\n";
	xmlDescription += "<enumvalue name='GooKakty' value='90'/>\n";
	xmlDescription += "<enumvalue name='GooKalab' value='91'/>\n";
	xmlDescription += "<enumvalue name='GooKami' value='92'/>\n";
	xmlDescription += "<enumvalue name='GooKazoar' value='93'/>\n";
	xmlDescription += "<enumvalue name='GooKitifly' value='94'/>\n";
	xmlDescription += "<enumvalue name='GooKitihank' value='95'/>\n";
	xmlDescription += "<enumvalue name='GooKitiharak' value='96'/>\n";
	xmlDescription += "<enumvalue name='GooKitikil' value='97'/>\n";
	xmlDescription += "<enumvalue name='GooKitimandib' value='98'/>\n";
	xmlDescription += "<enumvalue name='GooKitin' value='99'/>\n";
	xmlDescription += "<enumvalue name='GooKitinagan' value='100'/>\n";
	xmlDescription += "<enumvalue name='GooKitinega' value='101'/>\n";
	xmlDescription += "<enumvalue name='GooKitinokto' value='102'/>\n";
	xmlDescription += "<enumvalue name='GooLightbird' value='103'/>\n";
	xmlDescription += "<enumvalue name='GooMektoub' value='104'/>\n";
	xmlDescription += "<enumvalue name='GooMektoubPacker' value='105'/>\n";
	xmlDescription += "<enumvalue name='GooMektoubMount' value='106'/>\n";
	xmlDescription += "<enumvalue name='GooPucetron' value='107'/>\n";
	xmlDescription += "<enumvalue name='GooRegus' value='108'/>\n";
	xmlDescription += "<enumvalue name='GooRyzerb' value='109'/>\n";
	xmlDescription += "<enumvalue name='GooRyzoholo' value='110'/>\n";
	xmlDescription += "<enumvalue name='GooRyzoholok' value='111'/>\n";
	xmlDescription += "<enumvalue name='GooVampignon' value='112'/>\n";
	xmlDescription += "<enumvalue name='GooVarinx' value='113'/>\n";
	xmlDescription += "<enumvalue name='GooYber' value='114'/>\n";
	xmlDescription += "<enumvalue name='GooZerx' value='115'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c1' value='116'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c2' value='117'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c3' value='118'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c4' value='119'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c5' value='120'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c6' value='121'/>\n";
	xmlDescription += "<enumvalue name='Goorace_c7' value='122'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h1' value='123'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h2' value='124'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h3' value='125'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h4' value='126'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h5' value='127'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h6' value='128'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h7' value='129'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h8' value='130'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h9' value='131'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h10' value='132'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h11' value='133'/>\n";
	xmlDescription += "<enumvalue name='Goorace_h12' value='134'/>\n";
	xmlDescription += "<enumvalue name='EndGooFauna' value='135'/>\n";
	xmlDescription += "<enumvalue name='GooPlant' value='135'/>\n";
	xmlDescription += "<enumvalue name='GooCephaloplant' value='135'/>\n";
	xmlDescription += "<enumvalue name='GooElectroalgs' value='136'/>\n";
	xmlDescription += "<enumvalue name='GooPhytopsy' value='137'/>\n";
	xmlDescription += "<enumvalue name='GooSapEnslaver' value='138'/>\n";
	xmlDescription += "<enumvalue name='GooSpittingWeeds' value='139'/>\n";
	xmlDescription += "<enumvalue name='GooSwarmplants' value='140'/>\n";
	xmlDescription += "<enumvalue name='EndGooPlant' value='141'/>\n";
	xmlDescription += "<enumvalue name='EndGoo' value='141'/>\n";
	xmlDescription += "<enumvalue name='EndCreature' value='141'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<typedef name='TClassificationType' id='18' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='TypeHumanoid' value='0'/>\n";
	xmlDescription += "<enumvalue name='TypeHomin' value='1'/>\n";
	xmlDescription += "<enumvalue name='TypeDegenerated' value='2'/>\n";
	xmlDescription += "<enumvalue name='TypeFauna' value='3'/>\n";
	xmlDescription += "<enumvalue name='TypeFlora' value='4'/>\n";
	xmlDescription += "<enumvalue name='TypeDog' value='5'/>\n";
	xmlDescription += "<enumvalue name='TypeRunner' value='6'/>\n";
	xmlDescription += "<enumvalue name='TypeHorse' value='7'/>\n";
	xmlDescription += "<enumvalue name='TypeBird' value='8'/>\n";
	xmlDescription += "<enumvalue name='TypeKitin' value='9'/>\n";
	xmlDescription += "<enumvalue name='TypeLandKitin' value='10'/>\n";
	xmlDescription += "<enumvalue name='TypeFlyingKitin' value='11'/>\n";
	xmlDescription += "<enumvalue name='TypeFish' value='12'/>\n";
	xmlDescription += "<enumvalue name='TypeRyzomian' value='13'/>\n";
	xmlDescription += "<enumvalue name='TypeGreatRyzomian' value='14'/>\n";
	xmlDescription += "<enumvalue name='TypePachyderm' value='15'/>\n";
	xmlDescription += "<enumvalue name='TypeShellfish' value='16'/>\n";
	xmlDescription += "<enumvalue name='TypeKami' value='17'/>\n";
	xmlDescription += "<enumvalue name='TypeKaravan' value='18'/>\n";
	xmlDescription += "<enumvalue name='TypeAll' value='19'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<typedef name='TSPType' id='19' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='Fight' value='0'/>\n";
	xmlDescription += "<enumvalue name='Magic' value='1'/>\n";
	xmlDescription += "<enumvalue name='Craft' value='2'/>\n";
	xmlDescription += "<enumvalue name='Harvest' value='3'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<typedef name='TGuildGrade' id='20' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='Leader' value='0'/>\n";
	xmlDescription += "<enumvalue name='HighOfficer' value='1'/>\n";
	xmlDescription += "<enumvalue name='Officer' value='2'/>\n";
	xmlDescription += "<enumvalue name='Member' value='3'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<typedef name='TSeason' id='21' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='Spring' value='0'/>\n";
	xmlDescription += "<enumvalue name='Summer' value='1'/>\n";
	xmlDescription += "<enumvalue name='Autumn' value='2'/>\n";
	xmlDescription += "<enumvalue name='Winter' value='3'/>\n";
	xmlDescription += "<enumvalue name='Invalid' value='4'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<typedef name='TFameTrend' id='22' size='4' storage='uint32' type='enum'>\n";
	xmlDescription += "<enumvalue name='FameUpward' value='0'/>\n";
	xmlDescription += "<enumvalue name='FameDownward' value='1'/>\n";
	xmlDescription += "<enumvalue name='FameSteady' value='2'/>\n";
	xmlDescription += "</typedef>\n";
	xmlDescription += "<classdef name='CFameContainerEntryPD' id='0' key='0' columns='5'>\n";
	xmlDescription += "<attribute name='Sheet' id='0' columnid='0' columns='1' type='type' typeid='14'/>\n";
	xmlDescription += "<attribute name='Fame' id='1' columnid='1' columns='1' type='type' typeid='8'/>\n";
	xmlDescription += "<attribute name='FameMemory' id='2' columnid='2' columns='1' type='type' typeid='8'/>\n";
	xmlDescription += "<attribute name='LastFameChangeTrend' id='3' columnid='3' columns='1' type='type' typeid='22'/>\n";
	xmlDescription += "<attribute name='Parent' id='4' columnid='4' columns='1' type='backref' classid='1' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CFameContainerPD' id='1' key='0' mapped='1' columns='4'>\n";
	xmlDescription += "<attribute name='ContId' id='0' columnid='0' columns='1' type='type' typeid='13'/>\n";
	xmlDescription += "<attribute name='Entries' id='1' columnid='1' columns='1' type='set' classid='0' forwardreferedid='4' key='0' />\n";
	xmlDescription += "<attribute name='LastGuildStatusChange' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='LastFameChangeDate' id='3' columnid='3' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CGuildFameContainerPD' id='2' inherit='1' key='0' mapped='1' columns='5'>\n";
	xmlDescription += "<attribute name='ContId' id='0' columnid='0' columns='1' type='type' typeid='13'/>\n";
	xmlDescription += "<attribute name='Entries' id='1' columnid='1' columns='1' type='set' classid='0' forwardreferedid='4' key='0' />\n";
	xmlDescription += "<attribute name='LastGuildStatusChange' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='LastFameChangeDate' id='3' columnid='3' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Parent' id='4' columnid='4' columns='1' type='backref' classid='4' backreferentid='8'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CGuildMemberPD' id='3' key='0' columns='4'>\n";
	xmlDescription += "<attribute name='Id' id='0' columnid='0' columns='1' type='type' typeid='15'/>\n";
	xmlDescription += "<attribute name='Grade' id='1' columnid='1' columns='1' type='type' typeid='20'/>\n";
	xmlDescription += "<attribute name='EnterTime' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Guild' id='3' columnid='3' columns='1' type='backref' classid='4' backreferentid='7' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CGuildPD' id='4' key='0' columns='10'>\n";
	xmlDescription += "<attribute name='Id' id='0' columnid='0' columns='1' type='type' typeid='16'/>\n";
	xmlDescription += "<attribute name='Money' id='1' columnid='1' columns='1' type='type' typeid='9'/>\n";
	xmlDescription += "<attribute name='CreationDate' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Race' id='3' columnid='3' columns='1' type='type' typeid='17'/>\n";
	xmlDescription += "<attribute name='Icon' id='4' columnid='4' columns='1' type='type' typeid='9'/>\n";
	xmlDescription += "<attribute name='Building' id='5' columnid='5' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Version' id='6' columnid='6' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Members' id='7' columnid='7' columns='1' type='set' classid='3' forwardreferedid='3' key='0' />\n";
	xmlDescription += "<attribute name='FameContainer' id='8' columnid='8' columns='1' type='forwardref' classid='2' forwardreferedid='4'/>\n";
	xmlDescription += "<attribute name='Parent' id='9' columnid='9' columns='1' type='backref' classid='5' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CGuildContainerPD' id='5' key='2' mapped='5' columns='3'>\n";
	xmlDescription += "<attribute name='GMGuild' id='0' columnid='0' columns='1' type='type' typeid='16'/>\n";
	xmlDescription += "<attribute name='Guilds' id='1' columnid='1' columns='1' type='set' classid='4' forwardreferedid='9' key='0' />\n";
	xmlDescription += "<attribute name='Dummy' id='2' columnid='2' columns='1' type='type' typeid='3'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CActiveStepStatePD' id='6' key='0' columns='3'>\n";
	xmlDescription += "<attribute name='Index' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='State' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Step' id='2' columnid='2' columns='1' type='backref' classid='7' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CActiveStepPD' id='7' key='0' columns='3'>\n";
	xmlDescription += "<attribute name='IndexInTemplate' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='States' id='1' columnid='1' columns='1' type='set' classid='6' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Mission' id='2' columnid='2' columns='1' type='backref' classid='14' backreferentid='17' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CDoneStepPD' id='8' key='0' columns='2'>\n";
	xmlDescription += "<attribute name='Index' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='1' columnid='1' columns='1' type='backref' classid='14' backreferentid='19' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionCompassPD' id='9' key='0' columns='4'>\n";
	xmlDescription += "<attribute name='Index' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Place' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='BotId' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='3' columnid='3' columns='1' type='backref' classid='14' backreferentid='18' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionTeleportPD' id='10' key='0' columns='2'>\n";
	xmlDescription += "<attribute name='Index' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='1' columnid='1' columns='1' type='backref' classid='14' backreferentid='20' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionInsidePlacePD' id='11' key='0' columns='3'>\n";
	xmlDescription += "<attribute name='Alias' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Delay' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='2' columnid='2' columns='1' type='backref' classid='14' backreferentid='21' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionOutsidePlacePD' id='12' key='0' columns='3'>\n";
	xmlDescription += "<attribute name='Alias' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Delay' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='2' columnid='2' columns='1' type='backref' classid='14' backreferentid='22' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CHandledAIGroupPD' id='13' key='0' columns='3'>\n";
	xmlDescription += "<attribute name='GroupAlias' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='DespawnTime' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Mission' id='2' columnid='2' columns='1' type='backref' classid='14' backreferentid='23' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionPD' id='14' key='0' columns='25'>\n";
	xmlDescription += "<attribute name='TemplateId' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='MainMissionTemplateId' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Giver' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='HourLowerBound' id='3' columnid='3' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='HourUpperBound' id='4' columnid='4' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='Season' id='5' columnid='5' columns='1' type='type' typeid='21'/>\n";
	xmlDescription += "<attribute name='MonoEndDate' id='6' columnid='6' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='EndDate' id='7' columnid='7' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CriticalPartEndDate' id='8' columnid='8' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='BeginDate' id='9' columnid='9' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='FailureIndex' id='10' columnid='10' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CrashHandlerIndex' id='11' columnid='11' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='PlayerReconnectHandlerIndex' id='12' columnid='12' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Finished' id='13' columnid='13' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='MissionSuccess' id='14' columnid='14' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='DescIndex' id='15' columnid='15' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='WaitingQueueId' id='16' columnid='16' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Steps' id='17' columnid='17' columns='1' type='set' classid='7' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Compass' id='18' columnid='18' columns='1' type='set' classid='9' forwardreferedid='3' key='0' />\n";
	xmlDescription += "<attribute name='StepsDone' id='19' columnid='19' columns='1' type='set' classid='8' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='Teleports' id='20' columnid='20' columns='1' type='set' classid='10' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='InsidePlaces' id='21' columnid='21' columns='1' type='set' classid='11' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='OutsidePlaces' id='22' columnid='22' columns='1' type='set' classid='12' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='HandledAIGroups' id='23' columnid='23' columns='1' type='set' classid='13' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Container' id='24' columnid='24' columns='1' type='backref' classid='18' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionGuildPD' id='15' inherit='14' key='0' columns='25'>\n";
	xmlDescription += "<attribute name='TemplateId' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='MainMissionTemplateId' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Giver' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='HourLowerBound' id='3' columnid='3' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='HourUpperBound' id='4' columnid='4' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='Season' id='5' columnid='5' columns='1' type='type' typeid='21'/>\n";
	xmlDescription += "<attribute name='MonoEndDate' id='6' columnid='6' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='EndDate' id='7' columnid='7' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CriticalPartEndDate' id='8' columnid='8' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='BeginDate' id='9' columnid='9' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='FailureIndex' id='10' columnid='10' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CrashHandlerIndex' id='11' columnid='11' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='PlayerReconnectHandlerIndex' id='12' columnid='12' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Finished' id='13' columnid='13' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='MissionSuccess' id='14' columnid='14' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='DescIndex' id='15' columnid='15' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='WaitingQueueId' id='16' columnid='16' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Steps' id='17' columnid='17' columns='1' type='set' classid='7' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Compass' id='18' columnid='18' columns='1' type='set' classid='9' forwardreferedid='3' key='0' />\n";
	xmlDescription += "<attribute name='StepsDone' id='19' columnid='19' columns='1' type='set' classid='8' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='Teleports' id='20' columnid='20' columns='1' type='set' classid='10' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='InsidePlaces' id='21' columnid='21' columns='1' type='set' classid='11' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='OutsidePlaces' id='22' columnid='22' columns='1' type='set' classid='12' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='HandledAIGroups' id='23' columnid='23' columns='1' type='set' classid='13' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Container' id='24' columnid='24' columns='1' type='backref' classid='18' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionTeamPD' id='16' inherit='14' key='0' columns='25'>\n";
	xmlDescription += "<attribute name='TemplateId' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='MainMissionTemplateId' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Giver' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='HourLowerBound' id='3' columnid='3' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='HourUpperBound' id='4' columnid='4' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='Season' id='5' columnid='5' columns='1' type='type' typeid='21'/>\n";
	xmlDescription += "<attribute name='MonoEndDate' id='6' columnid='6' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='EndDate' id='7' columnid='7' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CriticalPartEndDate' id='8' columnid='8' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='BeginDate' id='9' columnid='9' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='FailureIndex' id='10' columnid='10' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CrashHandlerIndex' id='11' columnid='11' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='PlayerReconnectHandlerIndex' id='12' columnid='12' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Finished' id='13' columnid='13' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='MissionSuccess' id='14' columnid='14' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='DescIndex' id='15' columnid='15' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='WaitingQueueId' id='16' columnid='16' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Steps' id='17' columnid='17' columns='1' type='set' classid='7' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Compass' id='18' columnid='18' columns='1' type='set' classid='9' forwardreferedid='3' key='0' />\n";
	xmlDescription += "<attribute name='StepsDone' id='19' columnid='19' columns='1' type='set' classid='8' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='Teleports' id='20' columnid='20' columns='1' type='set' classid='10' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='InsidePlaces' id='21' columnid='21' columns='1' type='set' classid='11' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='OutsidePlaces' id='22' columnid='22' columns='1' type='set' classid='12' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='HandledAIGroups' id='23' columnid='23' columns='1' type='set' classid='13' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Container' id='24' columnid='24' columns='1' type='backref' classid='18' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionSoloPD' id='17' inherit='14' key='0' columns='25'>\n";
	xmlDescription += "<attribute name='TemplateId' id='0' columnid='0' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='MainMissionTemplateId' id='1' columnid='1' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Giver' id='2' columnid='2' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='HourLowerBound' id='3' columnid='3' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='HourUpperBound' id='4' columnid='4' columns='1' type='type' typeid='11'/>\n";
	xmlDescription += "<attribute name='Season' id='5' columnid='5' columns='1' type='type' typeid='21'/>\n";
	xmlDescription += "<attribute name='MonoEndDate' id='6' columnid='6' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='EndDate' id='7' columnid='7' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CriticalPartEndDate' id='8' columnid='8' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='BeginDate' id='9' columnid='9' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='FailureIndex' id='10' columnid='10' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='CrashHandlerIndex' id='11' columnid='11' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='PlayerReconnectHandlerIndex' id='12' columnid='12' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Finished' id='13' columnid='13' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='MissionSuccess' id='14' columnid='14' columns='1' type='type' typeid='0'/>\n";
	xmlDescription += "<attribute name='DescIndex' id='15' columnid='15' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='WaitingQueueId' id='16' columnid='16' columns='1' type='type' typeid='7'/>\n";
	xmlDescription += "<attribute name='Steps' id='17' columnid='17' columns='1' type='set' classid='7' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Compass' id='18' columnid='18' columns='1' type='set' classid='9' forwardreferedid='3' key='0' />\n";
	xmlDescription += "<attribute name='StepsDone' id='19' columnid='19' columns='1' type='set' classid='8' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='Teleports' id='20' columnid='20' columns='1' type='set' classid='10' forwardreferedid='1' key='0' />\n";
	xmlDescription += "<attribute name='InsidePlaces' id='21' columnid='21' columns='1' type='set' classid='11' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='OutsidePlaces' id='22' columnid='22' columns='1' type='set' classid='12' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='HandledAIGroups' id='23' columnid='23' columns='1' type='set' classid='13' forwardreferedid='2' key='0' />\n";
	xmlDescription += "<attribute name='Container' id='24' columnid='24' columns='1' type='backref' classid='18' backreferentid='1' key='0'/>\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "<classdef name='CMissionContainerPD' id='18' key='0' mapped='18' columns='2'>\n";
	xmlDescription += "<attribute name='CharId' id='0' columnid='0' columns='1' type='type' typeid='13'/>\n";
	xmlDescription += "<attribute name='Missions' id='1' columnid='1' columns='1' type='set' classid='14' forwardreferedid='24' key='0' />\n";
	xmlDescription += "</classdef>\n";
	xmlDescription += "</db>\n";
	xmlDescription += "</dbdescription>\n";
	PDSLib.init(xmlDescription, overrideDbId);
}

bool							ready()
{
	return PDSLib.PDSReady();
}

void							update()
{
	PDSLib.update();
}

void							logChat(const ucstring& sentence, const NLMISC::CEntityId& from, const std::vector<NLMISC::CEntityId>& to)
{
	PDSLib.logChat(sentence, from, to);
}

void							logTell(const ucstring& sentence, const NLMISC::CEntityId& from, const NLMISC::CEntityId& to)
{
	std::vector<NLMISC::CEntityId>	ids;
	ids.push_back(to);
	PDSLib.logChat(sentence, from, ids);
}

void							release()
{
	PDSLib.release();
}

	
} // End of EGSPD
