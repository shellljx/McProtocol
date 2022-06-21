//
// Created by 李金祥 on 2022/6/10.
//

#include "Tag.h"
#include "TagByte.h"
#include "TagByteArray.h"
#include "TagCompound.h"
#include "TagDouble.h"
#include "TagFloat.h"
#include "TagInt.h"
#include "TagIntArray.h"
#include "TagList.h"
#include "TagLong.h"
#include "TagLongArray.h"
#include "TagShort.h"
#include "TagString.h"

namespace McProtocol {
std::shared_ptr<Tag> Tag::CreateTag(const TagType type, const std::string &name) {
  switch (type) {
    case TagType::Byte:return std::shared_ptr<TagByte>(new TagByte(name));
    case TagType::Short:return std::shared_ptr<TagShort>(new TagShort(name));
    case TagType::Int:return std::shared_ptr<TagInt>(new TagInt(name));
    case TagType::Long:return std::shared_ptr<TagLong>(new TagLong(name));
    case TagType::Float:return std::shared_ptr<TagFloat>(new TagFloat(name));
    case TagType::Double:return std::shared_ptr<TagDouble>(new TagDouble(name));
    case TagType::ByteArray:return std::shared_ptr<TagByteArray>(new TagByteArray(name));
    case TagType::String:return std::shared_ptr<TagString>(new TagString(name));
    case TagType::List:return std::shared_ptr<TagList>(new TagList(name));
    case TagType::Compound:return std::shared_ptr<TagCompound>(new TagCompound(name));
    case TagType::IntArray:return std::shared_ptr<TagIntArray>(new TagIntArray(name));
    case TagType::LongArray:return std::shared_ptr<TagLongArray>(new TagLongArray(name));
    default:return nullptr;
  }
}
}