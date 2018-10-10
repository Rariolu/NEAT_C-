#ifndef _URGH_H
#define _URGH_H

#ifdef EXTERN_TEMPLATES
#define EXTERN_TEMPLATE __declspec(dllexport)
#else
#define EXTERN_TEMPLATE __declspec(dllimport)
#endif

#endif