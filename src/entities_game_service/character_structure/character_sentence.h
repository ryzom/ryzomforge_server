/** \character_sentence.h
 * 
 *
 * $Id: character_sentence.h,v 1.5 2004/12/09 14:17:28 besson Exp $
 */



#ifndef RY_CHARACTER_SENTENCE_H
#define RY_CHARACTER_SENTENCE_H


typedef std::vector<NLMISC::CSheetId>	TSheetIdVector;

/// Class for sentences
class CCharacterSentence
{
public:
	std::string					Name;
	TSheetIdVector				BricksIds;
	std::vector<uint8>			BricksIndexInSentence;
	
	/// Serialisation
	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( Name );
		f.serialCont( BricksIds );
		f.serialCont( BricksIndexInSentence );
	}
};

static bool operator==(const CCharacterSentence &a, const CCharacterSentence &b)
{
	return a.BricksIds == b.BricksIds;
}


#endif // RY_CHARACTER_SENTENCE_H
/* character_sentence.h */
