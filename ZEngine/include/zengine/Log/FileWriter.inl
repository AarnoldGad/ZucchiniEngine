#include "zengine/Memory/New.hpp"

inline std::filesystem::path ze::FileWriter::getFilePath() const noexcept
{
   return m_path;
}

inline bool ze::FileWriter::isAtLineBegin() const noexcept
{
   return m_lineStart;
}

#include "zengine/Memory/NewOff.hpp"
