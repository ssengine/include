#pragma once

#define CAT(x, y)  CAT_I((x, y))
#define CAT_I(u)  CAT_II u
#define CAT_II(x, y) CAT_III(x##y)
#define CAT_III(v) v

#define SS_CAT CAT