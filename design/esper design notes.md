# esper design notes

## terms

- **load:** instance method to load all data necessary for class initialization from memory
- **loadX:** instance method to load specific data for class initialization from memory
- **build:** static method to construct a new instance of the class and load it
- **buildX:** instance method to construct a new instance of X and load it

## `PluginFile::load`

1. `PluginFile::loadFileHeader`
2. `MainRecord::build`
3. `PluginFile::loadGroups`
4. `GroupRecord::build`

## `GroupRecord::build`

1. `GroupRecord::GroupRecord`
2. `GroupRecord::loadGroupHeader`
3. `GroupRecord::loadRecords`
4. `MainRecord::build`
5. `GroupRecord::build`

## `MainRecord::build`

1. `MainRecord::MainRecord`
2. `MainRecord::loadHeader`
3. `MainRecord::loadSubrecords`

## `MainRecord::buildElements`

1. `Container::initElements`
2. `Def::subrecordFound`

## `MembersDef::subrecordFound`

1. `MembersDef::getMemberDef`
2. `Def::buildElement`
3. `Def::subrecordFound`

