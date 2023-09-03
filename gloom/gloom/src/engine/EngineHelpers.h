#pragma once

#define gNameOf(x) #x

#define ARGUMENT_IS_NULLPTR(x) "Argument `" gNameOf(x) "` is nullptr."
#define ARGUMENT_CONTAINS_NULLPTR(x) "Argument `" gNameOf(x) "` contains nullptr."

#define ENUM_VALUE_IS_UNKNOWN "Enum value is unknown."

#define INDEX_OUT_OF_RANGE "Index is out of range."
