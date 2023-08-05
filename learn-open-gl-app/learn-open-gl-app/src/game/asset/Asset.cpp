#include "Asset.h"

Asset::Asset()
	: m_Id(AssetID::Generate()), m_Name("")
{
}
