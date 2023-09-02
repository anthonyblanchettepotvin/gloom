#pragma once

#define NAME_OF(x) #x

#define ARGUMENT_IS_NULLPTR(x) "Argument `" NAME_OF(x) "` is nullptr."
#define ARGUMENT_CONTAINS_NULLPTR(x) "Argument `" NAME_OF(x) "` contains nullptr."
